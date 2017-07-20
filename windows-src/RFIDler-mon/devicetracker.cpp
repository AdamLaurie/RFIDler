/* 

    Project: RFIDler Monitor v0.2
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: devicetracker.cpp

    Author: Anthony Naggs, 2014, 2016, 2017

    Copyright (c) 2014-2017 Anthony Naggs.
    All rights reserved.

    Limited assignment of rights under the 'BSD 2-Clause License':

    Redistribution and use in source and binary forms, with or without modification, are
    permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this list of
       conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice, this list
       of conditions and the following disclaimer in the documentation and/or other materials
       provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
    THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
    OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
    EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "rfidmonitor.h"
#include <cfgmgr32.h>
#include <dbt.h>
#include <devguid.h>
#define INITGUID
#include <DEVPKEY.H>
// headers from DDK
#include <hidclass.h>
#include <api/ntddmodm.h>
#include <api/usbiodef.h>
#include <wdmguid.h>


/*
   Notes on tracking COM ports, and default settings in the registry.

   Simple tracking of available COM ports can be done by scanning the keys belonging to
   HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
   which map a logical device to a COM port name (REG_SZ), e.g.:
   \Device\BthModem0        COM5
   \Device\USBSER00         COM7
   (One issue is that this needs Local Admin privilege.)

   We however want to track deeper details, such as 'friendly name', USB VID & PID (to identify
   specific device types, and USB hub & port, etc ...
   So we have a more sophisticated system.

   Another interesting registry key is
   HKEY_LOCAL_MACHINE/SOFTWARE/Microsoft/Windows NT/CurrentVersion/Ports
   Which maps port name plus ":" to default settings string (REG_SZ), if any, e.g.:
   COM1:                    9600,n,8,1

   Potentially interesting but we don't use this
   HKEY_LOCAL_MACHINE/SYSTEM/CurrentControlSet/Control/COM Name Arbiter
   Has one key (ComDB) which is a bit mask of all assigned COM port names
*/


// static members of DeviceTracker
HIMAGELIST  DeviceTracker::mImageList = NULL;
HIMAGELIST  DeviceTracker::mImageListSm = NULL;
// icon resource ids for device view
const int   DeviceTracker::mIconList[DevImageCount] = {
            IDI_RFIDOKAY, IDI_RFIDBAD, IDI_RFIDREMOVE,
            IDI_RFIDBOOT, IDI_DEVBOARD, IDI_DEVBOARDREMOVE, IDI_DEVBOARDBAD,
            IDI_OTHERSERIALOK, IDI_OTHERSERIALREMOVE,
            IDI_ARDUINO_OK, IDI_ARDUINO_REMOVE, IDI_OTHER_BOOTLOADER,
            IDI_MODEM, IDI_MODEM_REMOVED
            };
HINSTANCE   DeviceTracker::mHInst = NULL;


// string constants, registry keynames, ...
const wchar_t *KStringCom = L"COM";


void DeviceTracker::SetViewStyle(int viewButton, BOOL aRestore)
{
    int oldView = mOptions.GetViewStyleButton();

    if (viewButton != oldView) {
        // move menu check mark
        HMENU hMenu = GetMenu(mHWndMain);

        CheckMenuItem(hMenu, oldView, MF_UNCHECKED);
        CheckMenuItem(hMenu, viewButton, MF_CHECKED);

        if (ID_VIEW_DETAILS == oldView) {
            EnableMenuItem(hMenu, ID_VIEW_DEF_COL_WIDTHS, MF_DISABLED);
            EnableMenuItem(hMenu, ID_VIEW_FIT_COL_WIDTHS, MF_DISABLED);
        } else if (ID_VIEW_DETAILS == viewButton) {
            EnableMenuItem(hMenu, ID_VIEW_DEF_COL_WIDTHS, MF_ENABLED);
            EnableMenuItem(hMenu, ID_VIEW_FIT_COL_WIDTHS, MF_ENABLED);
        }

        LONG newStyle;

        switch (viewButton) {
        case ID_VIEW_LARGE_ICONS:
            newStyle = LV_VIEW_ICON;
            break;
        case ID_VIEW_SMALL_ICONS:
            newStyle = LV_VIEW_SMALLICON;
            break;
        case ID_VIEW_DETAILS:
            newStyle = LV_VIEW_DETAILS;
            break;
        case ID_VIEW_TILES:
            newStyle = LV_VIEW_TILE;
            break;
        default:
            assert(0);
            return;
        }

        // change how View is drawn
        ListView_SetView(mHWndListView, newStyle);
        mOptions.SaveViewStyleButton(viewButton, aRestore);

        /* Re-sort ListView if changing to Details View, as documentation
            implies sorting does not affect other view styles.
        */
        if (newStyle == LV_VIEW_DETAILS) {
            SortDeviceListView();
        }
    }
}


void DeviceTracker::SortDeviceListView()
{
    mNeedDevicesResort = FALSE;
    ListView_SortItems(mHWndListView, DeviceInfo::ViewSortCompareProc, &mSortParameters);
}


int DeviceTracker::FindViewItem(LPARAM lParam)
{
    LVFINDINFO findinfo;

    ZeroMemory(&findinfo, sizeof(LVFINDINFO));
    findinfo.flags = LVFI_PARAM;
    findinfo.lParam = lParam;

    return ListView_FindItem(mHWndListView, -1, &findinfo);
}


void DeviceTracker::RemoveViewItem(LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_DeleteItem(mHWndListView, itemId);
    }
}


// add serial device / bootloader / ?? & associated strings to the view
BOOL DeviceTracker::AddViewItem(const wchar_t *aName, enum DevImage aImage, const wchar_t *aDevType, 
            const wchar_t *aState, const wchar_t *aUsbLocation, const wchar_t *aSerialNumber,
            const wchar_t *aArrivalTime, LPARAM lParam)
{
    LVITEM lvItem;
    int    itemId = -1;
    // Tile View stuff
    unsigned int tileColumns[] = { lvDispType, lvDispState, lvDispLocus, lvDispSernum, lvDispArrivalTime };
    int tileFormat[] = { LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT };

    // ensure compiled with correct number of format values for the number of columns
    assert( sizeof(tileColumns) == sizeof(tileFormat) );

    ZeroMemory(&lvItem, sizeof(LVITEM));
    lvItem.iItem = 0; // insert at position 0, we will sort later
    assert(lvDispName == 0);
    lvItem.iSubItem = lvDispName; // must be 0
    lvItem.mask = LVIF_PARAM;
    lvItem.lParam = lParam;
    if (aName) {
        lvItem.mask |= LVIF_TEXT;
        lvItem.pszText = (LPWSTR) aName;
    }
    if (aImage >= 0) {
        lvItem.mask |= LVIF_IMAGE;
        lvItem.iImage = aImage;
    }

    // setup TileView stuff
    // show all fields of this item when in Tile View
    lvItem.cColumns = 2;
    lvItem.puColumns = tileColumns;
    lvItem.piColFmt = tileFormat;
    lvItem.mask |= LVIF_COLUMNS | LVIF_COLFMT;

    // actually update display
    itemId = ListView_InsertItem(mHWndListView, &lvItem);

    if (itemId > -1) {
        if (aDevType) {
            ListView_SetItemText(mHWndListView, itemId, lvDispType, (LPWSTR)aDevType);
        }
        if (aState) {
            ListView_SetItemText(mHWndListView, itemId, lvDispState, (LPWSTR)aState);
        }
        if (aUsbLocation) {
            ListView_SetItemText(mHWndListView, itemId, lvDispLocus, (LPWSTR)aUsbLocation);
        }
        if (aSerialNumber) {
            ListView_SetItemText(mHWndListView, itemId, lvDispSernum, (LPWSTR)aSerialNumber);
        }
        if (aArrivalTime) {
            ListView_SetItemText(mHWndListView, itemId, lvDispArrivalTime, (LPWSTR)aArrivalTime);
        }

        mNeedDevicesResort = TRUE;
        return TRUE;
    }

    return FALSE;
}


void DeviceTracker::UpdateViewItemPortName(const wchar_t *aName, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispName, (LPWSTR)aName);
        // need to re-sort View?
        if (mSortParameters.mSortType == lvDispName) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::UpdateViewItemIconAndState(enum DevImage aImage, const wchar_t *aState, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispState, (LPWSTR)aState);

        // update icon
        if (aImage >= 0) {
            LVITEM lvItem;

            ZeroMemory(&lvItem, sizeof(LVITEM));
            lvItem.iItem = itemId;
            lvItem.iSubItem = 0;
            lvItem.mask |= LVIF_IMAGE;
            lvItem.iImage = aImage;
            ListView_SetItem(mHWndListView, &lvItem);
        }

        // need to re-sort View?
        if (mSortParameters.mSortType == lvDispState) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::UpdateViewItemIconAndType(enum DevImage aImage, const wchar_t *aType, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispType, (LPWSTR)aType);

        // update icon
        if (aImage >= 0) {
            LVITEM lvItem;

            ZeroMemory(&lvItem, sizeof(LVITEM));
            lvItem.iItem = itemId;
            lvItem.iSubItem = 0;
            lvItem.mask |= LVIF_IMAGE;
            lvItem.iImage = aImage;
            ListView_SetItem(mHWndListView, &lvItem);
        }

        // need to re-sort View?
        if (mSortParameters.mSortType == lvDispType) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::UpdateViewItemState(const wchar_t *aState, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispState, (LPWSTR)aState);
        // need to re-sort View?
        if (mSortParameters.mSortType == lvDispState) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::UpdateViewItemLocation(const wchar_t *aUsbLocation, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispLocus, (LPWSTR)aUsbLocation);
        // need to re-sort View?
        if (mSortParameters.mSortType == lvDispLocus) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::UpdateViewItemArrivalTime(const wchar_t *aArrivalTime, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispArrivalTime, (LPWSTR)aArrivalTime);
        // need to re-sort View?
        if (mSortParameters.mSortType == lvDispArrivalTime) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::RegisterForDevNotifications(enum RegisterNotify registerClasses)
{
    DEV_BROADCAST_DEVICEINTERFACE dbc;

    ZeroMemory(&dbc, sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    dbc.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);

    // use DBT_DEVTYP_HANDLE if you have an open handle & want to watch device removal
    dbc.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    // set dbc.dbcc_classguid if only interested in 1 device type

 #if 0 // defined(_DEBUG)
    if (!mHNotifyAll) {
        dbc.dbcc_classguid = GUID_DEVCLASS_HIDCLASS;
        mHNotifyAll = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE | DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);
        if (mHNotifyAll) {
            return;
        }
    }
#endif

    switch (registerClasses)
    {
    case RegisterHidAndPorts:
        if (!mHNotifyHid) {
            dbc.dbcc_classguid = GUID_DEVINTERFACE_HID;
            mHNotifyHid = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE);
        }

        if (!mHNotifyComPort) {
            dbc.dbcc_classguid = GUID_DEVINTERFACE_COMPORT;
            mHNotifyComPort = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE);
        }

        if (!mHNotifyModem) {
            dbc.dbcc_classguid = GUID_DEVINTERFACE_MODEM;
            mHNotifyModem = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE);
        }

        if (!mHNotifyUsbDevice) {
            dbc.dbcc_classguid = GUID_DEVINTERFACE_USB_DEVICE;
            mHNotifyUsbDevice = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE);
        }
        break;
    // TODO case RegisterUsbHubs:
    }
}


void DeviceTracker::UnregisterForDevNotifications()
{
    if (mHNotifyHid) {
        UnregisterDeviceNotification(mHNotifyHid);
        mHNotifyHid = 0;
    }

    if (mHNotifyComPort) {
        UnregisterDeviceNotification(mHNotifyComPort);
        mHNotifyComPort = 0;
    }

    if (mHNotifyModem) {
        UnregisterDeviceNotification(mHNotifyModem);
        mHNotifyModem = 0;
    }

    if (mHNotifyUsbDevice) {
        UnregisterDeviceNotification(mHNotifyUsbDevice);
        mHNotifyUsbDevice = 0;
    }

#if defined(_DEBUG)
    if (mHNotifyAll) {
        UnregisterDeviceNotification(mHNotifyAll);
        mHNotifyAll = 0;
    }
#endif
}


/*
    DBT_DEVNODES_CHANGED => device tree changes, set timer for a rescan.

    DBT_DEVICEARRIVAL || DBT_DEVICEREMOVECOMPLETE => Device arrival / removal
    We currently only pay attention if accompanied by a DBT_DEVTYP_DEVICEINTERFACE
    structure, and check for HID and whether it is Microchip Bootloader.

    In theory we could be interested in a DBT_DEVTYP_PORT structure, referring to
    a COM port ...
            
    However we don't process this for now, as we have never seen usbser.sys
    generate these, and the 'friendly name' given in the notification is anyway
    hard to test if it is a specific RFIDler / Microchip USB port.

    With a DBT_DEVTYP_DEVICEINTERFACE a typical dbcc_name =
    "\\?\USB#VID_04D8&PID_003C#6&33d1b76f&0&1#{a5dcbf10-6530-11d2-901f-00c04fb951ed}"
    or "\\?\HID#VID_04D8&PID_003C#7&f4c61c5&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"
    which is looks like "\\?\" + DeviceInstanceID + '#' + Device interface GUID

        "\\?\USB#VID_04D8&PID_003C" -> InstanceIdRoot "USB\VID_04D8&PID_003C"
        #                    separator
        "6&33d1b76f&0&1"     Windows generated serial number
        #
        "{a5dcbf10-6530-11d2-901f-00c04fb951ed}" -> GUID_DEVINTERFACE_USB_DEVICE
 */
void DeviceTracker::OnDeviceChange(UINT uiType, LPARAM lParam)
{
    bool fastdevscan = false;   // set if we recognise HID (eg Bootloader) or COM port changes
    bool lazydevscan = false;   // set for DBT_DEVNODESCHANGED etc that non-COM port specific changes

    if (uiType == DBT_DEVNODES_CHANGED) {
        // set timer to rescan device tree for changes
        lazydevscan = true;
    } else {
        BOOL newDeviceArrival = (uiType == DBT_DEVICEARRIVAL);
        BOOL oldDeviceRemoval = (uiType == DBT_DEVICEREMOVECOMPLETE);

        if (newDeviceArrival || oldDeviceRemoval) {
            DEV_BROADCAST_HDR *dbh = (DEV_BROADCAST_HDR*) lParam;

#if defined(_DEBUG)
            wchar_t *devTypes [8] = 
                { L"DBT_DEVTYP_OEM", L"DBT_DEVTYP_DEVNODE",
                L"DBT_DEVTYP_VOLUME", L"DBT_DEVTYP_PORT",
                L"DBT_DEVTYP_NET", L"DBT_DEVTYP_DEVICEINTERFACE",
                L"DBT_DEVTYP_HANDLE", L"DBT_DEVTYP_DEVINST" };

            PrintDebugStatus(L"DevChange %s, Device Type %s (%i)\n",
                newDeviceArrival ? L"DBT_DEVICEARRIVAL" : L"DBT_DEVICEREMOVECOMPLETE",
                (dbh->dbch_devicetype <= DBT_DEVTYP_DEVINST) ? devTypes[dbh->dbch_devicetype] : L"unknown",
                dbh->dbch_devicetype);
#endif

            /*
                Check if notification is for a device we are interested in:
                * always interested in Ports (for Rfidlers) and HID (for Rfidler Bootloader)
                * sometimes interested in Modems & Multiport Serial cards
            */
            if (dbh->dbch_devicetype == DBT_DEVTYP_PORT) {
                DEV_BROADCAST_PORT *dbp = (DEV_BROADCAST_PORT*) dbh;

#if defined(_DEBUG)
                PrintDebugStatus(L"    Port Name \"%s\"\n", dbp->dbcp_name);
#endif

                // process notifications when they happen
                if (wcsncmp(KStringCom, dbp->dbcp_name, 3) == 0) {
                    if (newDeviceArrival) {
                        // TODO handle port arrival: note an old (remembered) name could be assigned to new hardware, or device could move USB hub & port
                        // for now, kickoff a scan soon full details
                        fastdevscan = TRUE;
                    } else {
                        // removal
                        UpdatePortStateFromNotification(dbp->dbcp_name, newDeviceArrival);
                        lazydevscan = TRUE; // ensure removal timer starts
                    }
                }
            } else if (dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
                DEV_BROADCAST_DEVICEINTERFACE *dbdi = (DEV_BROADCAST_DEVICEINTERFACE*) dbh;

                if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_HID) ||
                        IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_COMPORT) ||
                        (mOptions.ShowAnyOtherSerial() && IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_MODEM))) {
                    /*
                        TODO handle, but remove details before shipping:
                        DevChange DBT_DEVICEREMOVECOMPLETE, Device Type DBT_DEVTYP_DEVICEINTERFACE (5)
                            Device GUID == GUID_DEVINTERFACE_MODEM, 
                            Dev Name "\\?\BTHENUM#{00001103-0000-1000-8000-00805f9b34fb}_VID&00010001_PID&00ff#8&c90a654&0&90CF15A61862_C00000000#{2c7089aa-2e0e-11d1-b114-00c04fc2aae4}"
                        DevChange DBT_DEVICEREMOVECOMPLETE, Device Type DBT_DEVTYP_DEVICEINTERFACE (5)
                            Device GUID == GUID_DEVINTERFACE_COMPORT, 
                            Dev Name "\\?\BTHENUM#{00001103-0000-1000-8000-00805f9b34fb}_VID&00010001_PID&00ff#8&c90a654&0&90CF15A61862_C00000000#{86e0d1e0-8089-11d0-9ce4-08003e301f73}"
                    */
                    fastdevscan = true;
                } else if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_USB_DEVICE)) {
                    /*
                        USB arrival /  removal - wait briefly to stabilise & then scan devices
                        TODO respond to device arrival
                        TODO respond to USB device removal
                        Typical names we would be interested in ..
                        RFIDler LF:
                            "\?\USB#VID_1D50&PID_6098#61EE3A8F0040#{a5dcbf10-6530-11d2-901f-00c04fb951ed}"
                        Microchip Bootloader:
                            "\\?\HID#VID_04D8&PID_003C#7&f4c61c5&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"
                        Arduino Uno
                            "\\?\USB#VID_2A03&PID_0043#55639303734351916110#{a5dcbf10-6530-11d2-901f-00c04fb951ed}"
                    */
                    if (oldDeviceRemoval) {
                        // removal
                        // TODO UpdateUsbDeviceStateFromNotification(dbdi->dbcc_name);
                    }
                    lazydevscan = true;
                }

#if defined(_DEBUG)
                if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_HID)) {
                    PrintDebugStatus(L"    Device GUID == GUID_DEVINTERFACE_HID");
                } else if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_COMPORT)) {
                    PrintDebugStatus(L"    Device GUID == GUID_DEVINTERFACE_COMPORT");
                } else if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_MODEM)) {
                    PrintDebugStatus(L"    Device GUID == GUID_DEVINTERFACE_MODEM");
                } else if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVINTERFACE_USB_DEVICE)) {
                    PrintDebugStatus(L"    Device GUID == GUID_DEVINTERFACE_USB_DEVICE");
                } else {
                    PrintDebugStatus(L"    Device GUID %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                        dbdi->dbcc_classguid.Data1, dbdi->dbcc_classguid.Data2, dbdi->dbcc_classguid.Data3,
                        dbdi->dbcc_classguid.Data4[0], dbdi->dbcc_classguid.Data4[1],
                        dbdi->dbcc_classguid.Data4[2], dbdi->dbcc_classguid.Data4[3],
                        dbdi->dbcc_classguid.Data4[4], dbdi->dbcc_classguid.Data4[5],
                        dbdi->dbcc_classguid.Data4[6], dbdi->dbcc_classguid.Data4[7]);
                }
                PrintDebugStatus(L", Dev Name \"%s\"\n", dbdi->dbcc_name);
#endif

                // TODO? process more notifications as they happen (dbcc_name should be sufficient info)
           }
        }
    }

    // set timer to rescan device tree for changes
    if (fastdevscan) {
        KickDevFastScanTimer(); // todo? maybe fast device scan should only ever look for newly connected devices
    } else if (lazydevscan) {
        KickDevLazyScanTimer();
    }
}


// put device icons in image list
HIMAGELIST DeviceTracker::InitImageList(int cx, int cy, unsigned count, const int *iconlist)
{
    HIMAGELIST iList = ImageList_Create(cx, cy, ILC_MASK, count, count);

    if (iList) {
        unsigned i;
        bool fail = false;

        for (i = 0; (i < count) && !fail; i++) {
            HICON hi = (HICON) LoadImage(mHInst, MAKEINTRESOURCE(iconlist[i]),
                IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
            if (hi) {
                if (-1 == ImageList_AddIcon(iList, hi)) {
                    fail = true;
                }
                DestroyIcon(hi);
            } else {
                fail = true;
            }
        }
        if (fail) {
            ImageList_Destroy(iList);
            iList = NULL;
        }
    }

    return iList;
}


void DeviceTracker::InitListColumns()
{
    // column headings for view - lvColumn
    const wchar_t *columns[] = { L"Name", L"Device", L"State", L"Location", L"Serial number", L"Arrival Time" };
    LVCOLUMN lvcol;
    unsigned col;

    assert( (sizeof(columns) / sizeof(const wchar_t *)) == (lvDispMaxSort + 1));

    lvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
    lvcol.fmt = LVCFMT_LEFT;
    for (col = 0; col <= lvDispMaxSort; col++) {
        lvcol.pszText = (LPWSTR) columns[col];
        lvcol.cx = mOptions.DetailsColumnWidth(col);
        lvcol.iSubItem = col;
        ListView_InsertColumn(mHWndListView, col, &lvcol);
    }
}


void DeviceTracker::DefaultListColumnWidths()
{
    unsigned col;
    int curWidth;
    int defWidth;

    for (col = 0; col <= lvDispMaxSort; col++) {
        curWidth = ListView_GetColumnWidth(mHWndListView, col);
        defWidth = mOptions.DefaultDetailsColumnWidth(col);
        if (defWidth != curWidth) {
             mOptions.SetDetailsColumnWidth(col, defWidth);
             ListView_SetColumnWidth(mHWndListView, col, defWidth);
        }
    }
}


void DeviceTracker::FitListColumnWidths()
{
    unsigned col;

    for (col = 0; col <= lvDispMaxSort; col++) {
        ListView_SetColumnWidth(mHWndListView, col, (col == 4) ? LVSCW_AUTOSIZE_USEHEADER : LVSCW_AUTOSIZE);
    }
}


void DeviceTracker::Initialize(HWND HWndMain, HWND HWndListView, HWND HWndStatusBar, HWND HWndListHeader, HINSTANCE HInst, BOOL launchStartup)
{
    mHWndMain = HWndMain;
    mHWndListView = HWndListView;
    mHWndStatusBar = HWndStatusBar;
    mHWndListHeader = HWndListHeader;
    mHInst = HInst;
    mOptions.SetHwndMain(HWndMain);

    // read any saved options from registry
    mOptions.ReadRegistryValues(launchStartup); // true if started from Startup Group

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    /* SetupDiGetDeviceProperty() api is new in Windows Vista
       There are a lot of Win XP systems around still, so don't unnecessarily
       be incompatible with them.
    */
    {
        HMODULE hModule = GetModuleHandle(L"setupapi.dll");
        if (hModule) {
            mSetupDiGetDevicePropertyW = (LPFNSetupDiGetDevicePropertyW)
                GetProcAddress(hModule, "SetupDiGetDevicePropertyW");
        }
    }
#endif

    // enable tooltips, in all display views, also full row select
    ListView_SetExtendedListViewStyle(mHWndListView, LVS_EX_INFOTIP  | LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT);

    RegisterForDevNotifications(RegisterHidAndPorts);

    // create image lists
    mImageList = InitImageList(32, 32, DevImageCount, mIconList);
    if (mImageList) {
        ListView_SetImageList(mHWndListView, mImageList, LVSIL_NORMAL);
    }
    mImageListSm = InitImageList(16, 16, DevImageCount, mIconList);
    if (mImageListSm) {
        ListView_SetImageList(mHWndListView, mImageListSm, LVSIL_SMALL);
    }


    SIZE size = { 120, 70 };
    LVTILEVIEWINFO tileViewInfo = {0};

    tileViewInfo.cbSize   = sizeof(tileViewInfo);
    tileViewInfo.dwFlags  = LVTVIF_FIXEDSIZE;
    tileViewInfo.dwMask   = LVTVIM_COLUMNS | LVTVIM_TILESIZE;
    tileViewInfo.cLines   = 2;
    tileViewInfo.sizeTile = size;

    ListView_SetTileViewInfo(mHWndListView, &tileViewInfo);

    // setup display: list view header
    InitListColumns();

    // init ListView sort order from restored values
    {
        ColumnSortParameters sortParams = mOptions.GetSortOrder();
        SetViewSortOrder(sortParams);
    }

    if (mHWndListHeader) {
        HDITEM hdrItem;
        hdrItem.mask = HDI_FORMAT;

        if (Header_GetItem(mHWndListHeader, mSortParameters.mSortType, &hdrItem)) {
            hdrItem.fmt |= mSortParameters.mSortReverse ? HDF_SORTDOWN : HDF_SORTUP;
            Header_SetItem(mHWndListHeader, mSortParameters.mSortType, &hdrItem);
        }
    }

    // kick timer to do initial device scan
    KickDevLazyScanTimer();

    // should StatusBar have 2, 3 or 4 partitions?
    if (mHWndStatusBar) {
        SetStatusBarPartitions(mOptions);
    }

    StatusBarRefresh();
}


// Windows should cleanup resources on exit, but it is good practice to do our own.
void DeviceTracker::Cleanup()
{
    CancelArrivalTimer();
    CancelDevScanTimers();
    mOptions.CancelRegSaveTimer();

    if (mImageList) {
        ImageList_Destroy(mImageList);
    }
    if (mImageListSm) {
        ImageList_Destroy(mImageListSm);
    }

    DeviceInfo::DeleteAllDevices();

    UnregisterForDevNotifications();
}


void DeviceTracker::ScanRfidlerDevices()
{
    DeviceInfo *devList;

    // use timer as a one-shot
    CancelDevScanTimers();

    // update scanned device lists
    ScanForDevChanges();
    mInitialiseRfidler = FALSE;
    mInitialiseUnconfig = FALSE;
    mInitialiseMicrochipSerial = FALSE;
    mInitialiseAnyOtherSerial = FALSE;

    // if any devices are now in Arrived or Removed state ensure arrival refresh timer is running
    devList = DeviceInfo::GetPortList();
    if (devList) {
        while (!mDevicesArrivedOrRemoved && devList) {
            enum DevState dState = devList->DeviceState();

            if ((dState == DevRemoved) || (dState == DevArrived)) {
                mDevicesArrivedOrRemoved = TRUE;
            }

            devList = devList->DeviceNext();
        }

        if (mDevicesArrivedOrRemoved) {
            KickArrivalTimer();
        }

        // re-sort ListView if necessary
        if (mNeedDevicesResort) {
            SortDeviceListView();
        }
    }
}


void DeviceTracker::ScanForDevChanges()
{
    // unique id for each scan, to allow old entries to be identified
    static unsigned scanId = 31415926;  // arbitrary initial value

    FILETIME scanTime = GetTimeAsFileTimeUTC();

    if (mOptions.ShowNonConfig()) {
        // have to scan all devices in order to check for unconfigured
        ScanIncludingUnconfigDevs(scanTime, scanId);
    } else {
        // check for device types we are specifically interested in
        ScanHidDevices(scanTime, scanId);
        ScanSerialDevices(scanTime, scanId);
    }

    CleanupOrphanedDevices(scanTime, scanId);

    UpdateStatusBarAndWinFlashNotifications();
    scanId++;
}


BOOL DeviceTracker::GetDevicePropertyGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid,
    CONST DEVPROPKEY PropKey, DWORD Property)
{
    DWORD size;
    BOOL result = FALSE;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &PropKey,
                                        &PropType,
                                        (PBYTE)&DevGuid,
                                        sizeof(GUID),
                                        &size,
                                        0)
                    && (PropType == DEVPROP_TYPE_GUID);
    } else {
#elif defined(USE_SETUP_DEVICE_REGISTRY)
    {
#endif
        // range check, some values are not available through older(Win <= XP) Setup API
        if (Property < SPDRP_MAXIMUM_PROPERTY) {
            // note receives GUID in REG_SZ form
            DWORD type;
            wchar_t guidStringBuffer[40];

            result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, Property,
                &type, (PBYTE) guidStringBuffer, sizeof(guidStringBuffer), &size) && (type == REG_SZ);
            // convert guid string to GUID (Unicode build only)
            if (result && (S_OK != IIDFromString(guidStringBuffer, &DevGuid))) {
                result = FALSE;
            }
        }
    }

    return result;
}


BOOL DeviceTracker::GetDevicePropertyFiletime(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &ft,
    CONST DEVPROPKEY PropKey)
{
    DWORD size;
    BOOL result = FALSE;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &PropKey,
                                        &PropType,
                                        (PBYTE)&ft,
                                        sizeof(FILETIME),
                                        &size,
                                        0)
                    && (PropType == DEVPROP_TYPE_GUID);
    }
#endif

    return result;
}


BOOL DeviceTracker::GetDeviceClassGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid)
{
    return GetDevicePropertyGUID(DeviceInfoSet, DeviceInfoData, DevGuid, DEVPKEY_Device_ClassGuid, SPDRP_CLASSGUID);
}


BOOL DeviceTracker::GetDeviceBusTypeGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &BusGuid)
{
    return GetDevicePropertyGUID(DeviceInfoSet, DeviceInfoData, BusGuid, DEVPKEY_Device_BusTypeGuid, SPDRP_BUSTYPEGUID);
}


wchar_t *DeviceTracker::GetDevicePropertyString(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
    CONST DEVPROPKEY PropKey, DWORD Property, BOOL copyString, BOOL multiString)
{
    static wchar_t  szBuffer[1024];      // reuse this buffer forr all string reads
    DWORD           size;
    BOOL            result = FALSE;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &PropKey,
                                        &PropType,
                                        (PBYTE) szBuffer,
                                        sizeof(szBuffer),
                                        &size,
                                        0)
                    && ((PropType == DEVPROP_TYPE_STRING) || (multiString && (PropType == DEVPROP_TYPE_STRING_LIST)));
    } else {
#elif defined(USE_SETUP_DEVICE_REGISTRY)
    {
#endif
        // range check, some values are not available through older (Win <= XP) Setup API
        if (Property < SPDRP_MAXIMUM_PROPERTY) {
            DWORD type;
            result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, Property,
                &type, (PBYTE) szBuffer, sizeof(szBuffer), &size)
                && ((type == REG_SZ) || (multiString && (type == REG_MULTI_SZ)));
        }
    }

    if (result) {
        // return a copy of (first) string or pointer to static string buffer
        return copyString ? _wcsdup(szBuffer) : szBuffer;
    }
    return NULL;
}


// NB returned string on success is a static buffer. Volatile if not copied.
BOOL DeviceTracker::GetDeviceInstanceId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, wchar_t **DevInstance, DWORD *pSize)
{
    static wchar_t szDevInstanceId[MAX_DEVICE_ID_LEN];

    // Typical DevInstanceID = "USB\VID_04D8&PID_000A\6&33D1B76F&0&2"
    if (SetupDiGetDeviceInstanceId(DeviceInfoSet, &DeviceInfoData, szDevInstanceId, MAX_DEVICE_ID_LEN, pSize)) {
        *DevInstance = (wchar_t*) &szDevInstanceId;
        return TRUE;
    }
    return FALSE;
}


BOOL DeviceTracker::CheckDeviceId(const wchar_t *aHwId, DWORD size, const wchar_t *aRefHwId)
{
    DWORD len = _tcslen(aRefHwId);

    if (size >= len) {
        return 0 == wcsncmp(aHwId, aRefHwId, len);
    }
    return FALSE;
}


/* probe serial device, see if we are interested
   aNormalPort -> GUID_DEVCLASS_PORTS
*/
void DeviceTracker::CheckSerialDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
    SerialPortType aPortType, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    // devInstanceId is set to persistent static buffer
    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        // set default non-match result
        enum DevType dType =  DevOtherSerial;

        // examine serial device
        if (aPortType == SerialPort) {
            if (CheckDeviceId(devInstanceId, size, szRfidlerHwUsbId)) {
                dType = DevRfidlerCom;
            } else if (mOptions.ShowDevBoardsOrAnySerial() && CheckDeviceId(devInstanceId, size, szMicrochipSerialHwUsbId)) {
                dType = DevMicroDevBoard;
            }
        }

        // note separation of COM or LPT ports occurs in AddOrUpdateDevice()
        if (mOptions.ShowAnyOtherSerial() || (dType != DevOtherSerial)) {
            // Get (RFIDler / Microchip / other) USB Serial device details
            AddOrUpdateDevice(dType, DeviceInfoSet, DeviceInfoData, devInstanceId, size, 
                aPortType, aNow, aScanId);
        }
    }
}


void DeviceTracker::CheckHidDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        if (CheckDeviceId(devInstanceId, size, szMicrochipBootHidId)) {
            // found HID Bootloader, process details
            AddOrUpdateDevice(DevMicroBootloader, DeviceInfoSet, DeviceInfoData, devInstanceId, size, SerialNone, aNow, aScanId);
        } else if (CheckDeviceId(devInstanceId, size, szTeensyHalfKayBootHidId)) {
            // found HID Bootloader, process details
            AddOrUpdateDevice(DevHalfKayBootloader, DeviceInfoSet, DeviceInfoData, devInstanceId, size, SerialNone, aNow, aScanId);
        }
    }
}


// if serial device does not yet have driver configured it has no class set
void DeviceTracker::CheckClassNoneDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        enum DevType dType = DevOtherSerial; // dummy non valid value

        // check USB hardware id for unconfigured RFIDler, Microchip devboard
        if (CheckDeviceId(devInstanceId, size, szRfidlerHwUsbId)) {
            // Get RFIDler dev details
            dType = DevUnconfigRfidlerCom;
        } else if (mOptions.ShowDevBoards()) {
            if (CheckDeviceId(devInstanceId, size, szMicrochipSerialHwUsbId)) {
                // Get Microchip USB Serial device details
                dType = DevUnconfigMicroDevBoard;
            }
            // TODO? identify unconfigured Arduino/Genuino too?
        }

        if (dType != DevOtherSerial) {
            // Get RFIDler or Get Microchip USB Serial device details
            AddOrUpdateDevice(dType, DeviceInfoSet, DeviceInfoData, devInstanceId, size, SerialPort, aNow, aScanId);
        }
    }
}


void DeviceTracker::ScanIncludingUnconfigDevs(FILETIME &aNow, unsigned aScanId)
{
    HDEVINFO DeviceInfoSet;
    SP_DEVINFO_DATA DeviceInfoData;
    GUID DevClassGuid;                  // indicates Ports, HID, Modem, etc ...
    DWORD flags = DIGCF_ALLCLASSES;
    DWORD DeviceIndex = 0;

    if (!mOptions.ShowNotPresent()) {
        flags |= DIGCF_PRESENT;
    }
    DeviceInfoSet = SetupDiGetClassDevs(NULL, NULL, NULL, flags);

    if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
        return;
    }

    ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    while (SetupDiEnumDeviceInfo(DeviceInfoSet, DeviceIndex, &DeviceInfoData)) {
        BOOL gotClassGuid = GetDeviceClassGUID(DeviceInfoSet, DeviceInfoData, DevClassGuid);

        DeviceIndex++;
        
        if (gotClassGuid) {
            if (IsEqualGUID(DevClassGuid, GUID_DEVCLASS_PORTS)) {
                // examine serial device
                CheckSerialDevice(DeviceInfoSet, DeviceInfoData, SerialPort, aNow, aScanId);
            } else if (IsEqualGUID(DevClassGuid, GUID_DEVCLASS_HIDCLASS)) {
                CheckHidDevice(DeviceInfoSet, DeviceInfoData, aNow, aScanId);
            } else if (mOptions.ShowAnyOtherSerial()) {
                if (IsEqualGUID(DevClassGuid, GUID_DEVCLASS_MODEM)) {
                    CheckSerialDevice(DeviceInfoSet, DeviceInfoData, SerialModem, aNow, aScanId);
                } else if (IsEqualGUID(DevClassGuid, GUID_DEVCLASS_MULTIPORTSERIAL)) {
                    CheckSerialDevice(DeviceInfoSet, DeviceInfoData, SerialMultiport, aNow, aScanId);
                }
            }
        } else {
            // This device has an unknown device setup class.
            DWORD Error = GetLastError();

            if ((Error == ERROR_NOT_FOUND) || (Error == ERROR_INVALID_DATA)) {
                CheckClassNoneDevice(DeviceInfoSet, DeviceInfoData, aNow, aScanId);
            }
        }                 
    } // while

    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}


void DeviceTracker::ScanHidDevices(FILETIME &aNow, unsigned aScanId)
{
    HDEVINFO DeviceInfoSet;
    SP_DEVINFO_DATA DeviceInfoData;
    DWORD flags;
    DWORD DeviceIndex = 0;
    const GUID *guid = &GUID_DEVCLASS_HIDCLASS;

    if (mOptions.ShowNotPresent()) {
        flags = 0;
    } else {
        flags = DIGCF_PRESENT;
    }
    DeviceInfoSet = SetupDiGetClassDevs(guid, NULL, NULL, flags);

    if (DeviceInfoSet != INVALID_HANDLE_VALUE) {
        ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
        DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

        while (SetupDiEnumDeviceInfo(DeviceInfoSet, DeviceIndex, &DeviceInfoData)) {
            DeviceIndex++;
        
            CheckHidDevice(DeviceInfoSet, DeviceInfoData, aNow, aScanId);
        } // while

        SetupDiDestroyDeviceInfoList(DeviceInfoSet);
    }
}


void DeviceTracker::ScanSerialDevices(FILETIME &aNow, unsigned aScanId)
{
    HDEVINFO DeviceInfoSet;
    SP_DEVINFO_DATA DeviceInfoData;
    DWORD flags;
    DWORD DeviceIndex = 0;
    int i;

    /* RFIDler & Microchip DevBoard COM ports are in GUID_DEVCLASS_PORTS,
       'Show Any Serial' setting also needs to include Modems & Multiport Serial devices
    */
    const GUID *serialGuid[] = { &GUID_DEVCLASS_PORTS, &GUID_DEVCLASS_MODEM, &GUID_DEVCLASS_MULTIPORTSERIAL };
    const SerialPortType portTypes[] = { SerialPort, SerialModem, SerialMultiport };
    // number of class GUIDs to search for?
    int maxGuid = mOptions.ShowAnyOtherSerial() ? ARRAYSIZE(serialGuid) : 1;

    if (mOptions.ShowNotPresent()) {
        flags = 0;
    } else {
        flags = DIGCF_PRESENT;
    }

    for (i = 0; i < maxGuid; i++) {
        DeviceInfoSet = SetupDiGetClassDevs(serialGuid[i], NULL, NULL, flags);

        if (DeviceInfoSet != INVALID_HANDLE_VALUE) {
            ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
            DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

            while (SetupDiEnumDeviceInfo(DeviceInfoSet, DeviceIndex, &DeviceInfoData)) {
                DeviceIndex++;
        
                CheckSerialDevice(DeviceInfoSet, DeviceInfoData, portTypes[i], aNow, aScanId);
            } // while

            SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        }
    }
}


// returns DevPresent or DevAbsent, optionally returns PDO path too
BOOL DeviceTracker::GetDevPresentStatus(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    // just want to know if PDO path can be read => device is connected
    return NULL != GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_PDOName, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME, FALSE, FALSE);
}


void DeviceTracker::UnpackUSBLocation(DeviceLocation& aLocus, const wchar_t* aLocationString)
{
    // typical string = "Port_#0001.Hub_#0006"
    wchar_t  *str = NULL;
    unsigned offset = 0;

    if (wcs_consumeprefix(aLocationString, L"Port_#", &offset)) {
        aLocus.devUsbPort = wcstoul(aLocationString + offset, &str, 10);
        if ((errno == 0) && wcs_consumeprefix(str, L".Hub_#", &offset)) {
            aLocus.devUsbHub = wcstoul(str + offset, &str, 10);
            if (errno == 0) {
                aLocus.devBusType = BusUSB; // success
            }
        }
    }
}


DeviceLocation DeviceTracker::GetUSBDeviceLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, wchar_t *VIDstring)
{
    wchar_t  *devLocationBuffer;
    DeviceLocation  location;

    devLocationBuffer = GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_LocationInfo, SPDRP_LOCATION_INFORMATION, FALSE, FALSE);

    if (devLocationBuffer) {
        // devLocationBuffer[size/sizeof(wchar_t)] = 0; // safety, should already be 0 terminated
        UnpackUSBLocation(location, devLocationBuffer);

        if (VIDstring && (BusUSB == location.devBusType)) {
            // extract VID & PID from VIDstring ("VID_xxxx&PID_xxxx")
            location.usbVID = (unsigned) wcstoul(VIDstring + 4, NULL, 16);
            location.usbPID = (unsigned) wcstoul(VIDstring + 13, NULL, 16);
        }
    }

    return location;
}


enum DevBusType DeviceTracker::GetDeviceLocationFromBusGUID(GUID &BusGUID)
{
    /* 
        GUID_BUS_TYPE_USB shouldn't reach here.
        Otherwise, we don't handle these bus types:
        GUID_BUS_TYPE_INTERNAL, GUID_BUS_TYPE_LPTENUM, GUID_BUS_TYPE_USBPRINT, GUID_BUS_TYPE_DOT4PRT
        GUID_BUS_TYPE_SERENUM, GUID_BUS_TYPE_HID, GUID_BUS_TYPE_AVC, GUID_BUS_TYPE_IRDA
        */

    struct BusMapItem {
        GUID            busGuid;
        enum DevBusType busType;
    };
    BusMapItem BusTypeMap[] = {
        { GUID_BUS_TYPE_PCMCIA, BusPCMCIA },
        { GUID_BUS_TYPE_PCI, BusPCI },
        { GUID_BUS_TYPE_ISAPNP, BusISAPNP },
        { GUID_BUS_TYPE_EISA, BusEISA },
        { GUID_BUS_TYPE_MCA, BusMCA },
        { GUID_BUS_TYPE_1394, BusFirewire },
        { GUID_BUS_TYPE_SD, BusSD }
    };
    const unsigned maxBusTypeCount = ARRAYSIZE(BusTypeMap);

    // check plausible host bus types for a serial port
    for (unsigned j = 0; j < maxBusTypeCount; j++ ) {
        if (IsEqualGUID(BusGUID, BusTypeMap[j].busGuid)) {
            return BusTypeMap[j].busType;
        }
    }

    return BusUnknown;
}


// HID or NMWCD look for parent USB node in CurrentControlSet of Registry
// HID device, look for parent USB node for hub & port details in CurrentControlSet of Registry
DeviceLocation DeviceTracker::GetDeviceUSBRegistryLocation(const wchar_t *VIDstring, const wchar_t *serialString)
{
    wchar_t  registryKeyName[64];
    wchar_t  locationBuffer[64];
    wchar_t  serialNumberKey[32];

    DeviceLocation location;
    wchar_t *lastAmp;
    HKEY hKey;

    // TODO move key name generation (& open?) to support function
    // where to look - HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\ + VID_xxxx&PID_xxxx
    locationBuffer[0] = 0;
    StringCbPrintf(registryKeyName, sizeof(registryKeyName), L"SYSTEM\\CurrentControlSet\\Enum\\USB\\%.17s", VIDstring);
    StringCbCopy(serialNumberKey, sizeof(serialNumberKey), serialString);

    // crop last '&' and device interface id from serial number
    lastAmp = wcsrchr(serialNumberKey, '&');
    if (lastAmp) {
        *lastAmp = 0;
    }

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, registryKeyName, 0, KEY_READ, &hKey)) {
        // search subkeys for matching serial number
        const unsigned KMaxKeyLength = 255;

        wchar_t  achKey[KMaxKeyLength];   // buffer for subkey name
        DWORD    cbName;                   // size of name string
        wchar_t  achClass[MAX_PATH] = L""; // buffer for class name
        DWORD    cchClassName = MAX_PATH;  // size of class string
        DWORD    cSubKeys=0;               // number of subkeys
        DWORD    cbMaxSubKey;              // longest subkey size
        DWORD    cchMaxClass;              // longest class string
        DWORD    cValues;              // number of values for key
        DWORD    cchMaxValue;          // longest value name
        DWORD    cbMaxValueData;       // longest value data
        DWORD    cbSecurityDescriptor; // size of security descriptor
        FILETIME ftLastWriteTime;      // last write time
        DWORD    i, retCode;
        bool     match = false;

        // Get the class name and the value count.
        retCode = RegQueryInfoKey(
            hKey,                    // key handle
            achClass,                // buffer for class name
            &cchClassName,           // size of class string
            NULL,                    // reserved
            &cSubKeys,               // number of subkeys
            &cbMaxSubKey,            // longest subkey size
            &cchMaxClass,            // longest class string
            &cValues,                // number of values for this key
            &cchMaxValue,            // longest value name
            &cbMaxValueData,         // longest value data
            &cbSecurityDescriptor,   // security descriptor
            &ftLastWriteTime);       // last write time

        // Enumerate the subkeys, until matching serial number found or RegEnumKeyEx fails.
        for (i = 0; (i < cSubKeys) && !match; i++) {
            cbName = KMaxKeyLength;
            retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
            if (ERROR_SUCCESS == retCode) {
                DWORD valtype;
                DWORD valsize = sizeof(locationBuffer);
                HKEY hKey2;

                retCode = RegOpenKeyEx(hKey, achKey, 0, KEY_READ, &hKey2);

                if (ERROR_SUCCESS == retCode) {
                    // get ParentIdPrefix value, & compare with target serial number
                    retCode = RegQueryValueEx(hKey2, L"ParentIdPrefix", 0, &valtype, (BYTE*)&locationBuffer, &valsize);
                    if ((ERROR_SUCCESS == retCode) && (REG_SZ == valtype) && (0 == _wcsicmp(locationBuffer, serialNumberKey))) {
                        match = true; // exit loop
                        valsize = sizeof(locationBuffer);

                        // now get usb Location value
                        retCode = RegQueryValueEx(hKey2, L"LocationInformation", 0, &valtype, (BYTE*)&locationBuffer, &valsize);
                        if ((ERROR_SUCCESS == retCode) && (REG_SZ == valtype)) {
                            //PrintDebugStatus(L"LocationInformation %s\n", locationBuffer);
                            UnpackUSBLocation(location, locationBuffer);
                        }
                    }

                    RegCloseKey(hKey2);
                }

                // DEBUG - PrintDebugStatus(L"(%d) %s %u\n", i+1, achKey, retCode);
            }
        }

        RegCloseKey(hKey);
    }

    if (BusUSB == location.devBusType) {
        // extract VID & PID from VIDstring ("VID_xxxx&PID_xxxx")
        location.usbVID = (unsigned) wcstoul(VIDstring + 4, NULL, 16);
        location.usbPID = (unsigned) wcstoul(VIDstring + 13, NULL, 16);
    }
    return location;
}


DeviceLocation DeviceTracker::GetDeviceLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, DeviceSerialNumber &aSerialNumber)
{
    wchar_t         *vidString;
    DeviceLocation  location;
    bool            isUsbChild = false;

    // Bluetooth? Standard Bluetooth ports start with "BTHENUM", some Braodcom driver versions use "BLUETOOTHPORT"
    if (wcs_checkprefix(aSerialNumber.devInstanceIdRoot, L"BTHENUM\\") ||
            wcsstr(aSerialNumber.devInstanceIdRoot, L"BLUETOOTHPORT")) {
        location.devBusType = BusBluetooth;
        return location;
    }

    // USB?
    if (wcs_checkprefix(aSerialNumber.devInstanceIdRoot, L"USB\\")) {
        // single interface device?
        if (NULL == wcsstr(aSerialNumber.devInstanceIdRoot, L"&MI")) {
            return GetUSBDeviceLocation(DeviceInfoSet, DeviceInfoData, wcsstr(aSerialNumber.devInstanceIdRoot, L"VID_"));
        }
        isUsbChild = true;
    } else if (wcs_checkprefix(aSerialNumber.devInstanceIdRoot, L"HID\\") || wcs_checkprefix(aSerialNumber.devInstanceIdRoot, L"NMWCD\\")) {
        // HID or Nokia Mobile Wireless Communications Device
        isUsbChild = true;
    }

    if (!isUsbChild) {
        // try to identify bus type for device, eg PCI, PCMCIA, ..
        GUID    BusGuid;
        if (GetDeviceBusTypeGUID(DeviceInfoSet, DeviceInfoData, BusGuid)) {
#if defined(_DEBUG)
            location.debugBusGUID = BusGuid;
#endif
            location.devBusType = GetDeviceLocationFromBusGUID(BusGuid);
            if (location.devBusType != BusUnknown) {
                return location;
            }
        }
    }

    // device has a USB parent if there is a "VID_xxxx&PID_xxxx" element in the InstanceId string
    vidString = wcsstr(aSerialNumber.devInstanceIdRoot, L"VID_");
    if (vidString) {
        location = GetDeviceUSBRegistryLocation(vidString, aSerialNumber.devSerialString);
    }

    return location;
}


wchar_t *DeviceTracker::GetFriendlyName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    return GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_FriendlyName, SPDRP_FRIENDLYNAME, TRUE, FALSE);
}


wchar_t *DeviceTracker::GetManufacturerName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    return GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_Manufacturer, SPDRP_MFG, TRUE, FALSE);
}


wchar_t *DeviceTracker::GetDeviceName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    return GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_DeviceDesc, SPDRP_DEVICEDESC, TRUE, FALSE);
}


wchar_t *DeviceTracker::GetHardwareId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    // API gets a list of strings, we're only interested in the first which include USB, PCI etc product revision
    return GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_HardwareIds, SPDRP_HARDWAREID, TRUE, TRUE);
}


wchar_t *DeviceTracker::GetInfPath(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    // FUTURE FEATURE? get DEVPKEY_Device_DriverInfSection & DEVPKEY_Device_DriverInfSectionExt too?
    return GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_DriverInfPath, SPDRP_MAXIMUM_PROPERTY, TRUE, FALSE);
}


wchar_t *DeviceTracker::GetDriverName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    // TODO debug how to get driver name

    /* Device Manager  -> Devive -> Properties can find the driver name, so we should be able to also

    return GetDevicePropertyString(DeviceInfoSet, DeviceInfoData,
        DEVPKEY_Device_Driver, SPDRP_DRIVER, TRUE, FALSE);
        */

    return NULL;
}


/* TODO ?
FILETIME DeviceTracker::GetInstallDate(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    // BUG BUG value is a DEVPROP_TYPE_FILETIME
    FILETIME ftInstall;

    result = GetDevicePropertyFiletime(DeviceInfoSet, DeviceInfoData, ftInstall,
        DEVPKEY_Device_InstallDate);

    return ftInstall;
}
*/


wchar_t* DeviceTracker::GetPortname(HKEY devkey)
{
    const unsigned portbuffSize = 16;
    static wchar_t portnameBuff[portbuffSize];
    const wchar_t*  keyname = L"PortName";

    //Read the name of the port
    DWORD sizeOut = portbuffSize;
    DWORD type = 0;
    wchar_t* portname = NULL;
    LSTATUS result = RegQueryValueEx(devkey, keyname, NULL, &type, (LPBYTE)portnameBuff, &sizeOut);

    // check type
    if (REG_SZ == type) {
        if (result == ERROR_SUCCESS) {
            portname = wcs_dupsubstr(portnameBuff, sizeOut);
        }
        else if (result == ERROR_MORE_DATA) {
            // use sizeof(wchar_t) to workaround W2K returning size in characters instead of bytes
            wchar_t* tempBuff = (wchar_t*) calloc(sizeOut, sizeof(wchar_t));

            if (tempBuff) {
                if (RegQueryValueEx(devkey, keyname, NULL, &type, (LPBYTE)tempBuff, &sizeOut) == ERROR_SUCCESS) {
                    // copy to new buffer that doesn't waste bytes on W2k workaround
                    portname = wcs_dupsubstr(tempBuff, sizeOut);
                }
                free(tempBuff);
            }
        }
    }

    return portname;
}


wchar_t* DeviceTracker::GetPortname(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    // get the registry key with the device's port settings
    wchar_t *portname = NULL;
    HKEY devkey = SetupDiOpenDevRegKey(DeviceInfoSet, &DeviceInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE);

    if (devkey) {
        portname = GetPortname(devkey);

        // tidy up
        RegCloseKey(devkey);
    }

    return portname;
}


// extract serial number from Device InstanceId, winSernum set if windows (enumerator) generated it
DeviceSerialNumber  DeviceTracker::GetSerialnumber(const wchar_t *devInstanceId, DWORD size)
{
    // extract & dupe serial number
    size_t              i;
    size_t              serpos = 0;
    DeviceSerialNumber  serialNumber;

    // find last '\' in string, carefully in case no zero terminator
    for (i = 0; (i < size) && devInstanceId[i] != L'\0'; i++) {
        switch (devInstanceId[i]) {
        case L'&':
            serialNumber.devIsWinSerial = TRUE;
            break;
        case L'\\':
            serpos = i + 1;
            serialNumber.devIsWinSerial = FALSE;
            break;
        }
    }

    // extract serialnumber
    // Note prefix part of string is similar to hardwareid string, but lacks e.g. USB device revision
    if (serpos) {        
        serialNumber.devSerialString = wcs_dupsubstr(devInstanceId + serpos, size - serpos);
        serialNumber.devInstanceIdRoot = wcs_dupsubstr(devInstanceId, serpos - 1);
    }
    return serialNumber;
}


/*
   NB on older Rfidler (binaries) serial numbers are not necessarily unique!!!
   If device does not carry one preprogrammed, windows generates based on dev type, & USB hub/port.
   (Or PCI location etc..)
   Similar devices can therefore have the same serial number at different times, affects us
   when showing not currently present devices.

   On the other hand later Rfidler binaries use the preprogrammed on-chip unique Ethernet MAC,
   and mangle the byte order to create a unique serial number. So e.g. 'COM5' will be the serial
   port interface to the same Rfidler regardless of which USB hub/port it is plugged into.

   RFIDler LF built / programmed since November 2014 have unique serial numbers:
   https://github.com/ApertureLabsLtd/RFIDler/commit/c42f0640fb5dfceebc615f02157c6fa536de1c18
   */
DeviceInfo *DeviceTracker::FindDevMatchBySernum(enum DevType aDevType, wchar_t *sernumber)
{
    DeviceInfo *devList = DeviceInfo::GetPortList();

    while (devList) {
        enum DevType dType = devList->DeviceType();

        // control which type transitions are allowed, eg during driver install, or return of absent device
        if ((dType == aDevType) || (DeviceInfo::DeviceCategoryFoldedUnconfig(aDevType) == devList->DeviceCategoryFoldedUnconfig())) {
            if (!_wcsicmp(devList->SerialNumber(), sernumber)) {
                return devList;
            }
        }
        devList = devList->DeviceNext();
    }
    return NULL;
}


DeviceInfo *DeviceTracker::FindDevMatchByPortName(const wchar_t *aPortName)
{
    DeviceInfo *devList = DeviceInfo::GetPortList();

    while (devList) {
        if (devList->IsDeviceSerialPort()) {
            if (!_wcsicmp(devList->PortName(), aPortName)) {
                return devList;
            }
        }
        devList = devList->DeviceNext();
    }
    return NULL;
}


// for the time being we are only receiving immediate removal notifications, as arrival is more complex to process
void DeviceTracker::UpdatePortStateFromNotification(const wchar_t *aPortName, BOOL aDeviceArrived)
{
    DeviceInfo  *devItem = FindDevMatchByPortName(aPortName);;

    if (devItem) {
        if (!devItem->DevicePresent()) {
            // device has arrived/returned
            if (aDeviceArrived) {
                // TODO Arrival would call devItem->UpdateDevice(aDevType, deviceIsPresent, aNow, portDetails, location, aScanId);
                ;
            }
        } else {
            // device removed
            if (!aDeviceArrived) {
                devItem->AsyncDeviceRemoved();
            }
        }
    } // devItem found
}


void DeviceTracker::AddOrUpdateDevice(enum DevType aDevType, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        const wchar_t *devInstanceId, DWORD size, SerialPortType aPortType, FILETIME &aNow, unsigned aScanId)
{
    BOOL                deviceIsPresent = TRUE;
    DeviceLocation      location;
    SerialPortDetails   portDetails;
    DeviceSerialNumber  serialNumber;
    BOOL                added = FALSE;
    DeviceInfo          *devItem = NULL;

    if (mOptions.ShowNotPresent()) {
        // get device present status: DevPresent or DevAbsent
        deviceIsPresent = GetDevPresentStatus(DeviceInfoSet, DeviceInfoData);
    }
    
    // extract Serial Number string (& flag if Windows generated) from devInstanceId, leaving InstanceIdRoot (bus + vid, pid & function)
    serialNumber = GetSerialnumber(devInstanceId, size);

    // is device serial number new, or already known to us?
    devItem = FindDevMatchBySernum(aDevType, serialNumber.devSerialString);

    // get more details for new or Present device
    if (!devItem || deviceIsPresent) {
        // USB hub & port are easy to get for USB/... devices, harder for HID/...
        location = GetDeviceLocation(DeviceInfoSet, DeviceInfoData, serialNumber);

        if (DeviceInfo::IsDeviceSerialPort(aDevType)) {
            // get COM port name
            unsigned offset = 0;
            portDetails.serPortName = GetPortname(DeviceInfoSet, DeviceInfoData);
            if ((DevOtherSerial == aDevType) &&
                    (!portDetails.serPortName || (0 != wcsncmp(portDetails.serPortName, KStringCom, 3)))) {
                // LPT port presumably => not interesting
                return;
            }

            portDetails.serDeviceName = GetDeviceName(DeviceInfoSet, DeviceInfoData);
            // get friendly name, if any
            portDetails.serFriendlyName = GetFriendlyName(DeviceInfoSet, DeviceInfoData);

            if (portDetails.serPortName && wcs_consumeprefix(portDetails.serPortName, KStringCom, &offset)) {
                portDetails.serPortNumber = wcstoul(portDetails.serPortName + offset, NULL, 10);
            }
        }
    }

    if (devItem) {
        // device in list, so update connected state, COM port name, USB location, ..
        devItem->UpdateDevice(aDevType, deviceIsPresent, aNow, portDetails, location, aScanId);
    } else {
        // decided to add device to tracked status, good time to get / process extra registry strings
        wchar_t *manufacturer = GetManufacturerName(DeviceInfoSet, DeviceInfoData);
        wchar_t *infPath = GetInfPath(DeviceInfoSet, DeviceInfoData);
        wchar_t *driverName = GetDriverName(DeviceInfoSet, DeviceInfoData);
        wchar_t *hardwareId = NULL;
        
        if (BusUSB == location.devBusType) {
            hardwareId = GetHardwareId(DeviceInfoSet, DeviceInfoData);
        }

        // TODO dev HardwareId string (for USB product Revision), driver install .inf, driver file name
        
        // create new device object, & add to display
        added = DeviceInfo::AddDeviceToList(aDevType, deviceIsPresent, aNow, portDetails, location, serialNumber, aScanId, aPortType,
            manufacturer, hardwareId, driverName, infPath);

        if (!added) {
            ReleaseString(manufacturer);
            ReleaseString(hardwareId);
            ReleaseString(infPath);
            ReleaseString(driverName);
        }
    }

    // cleanup memory
    if (!added) {
        ReleaseString(serialNumber.devSerialString);
        ReleaseString(serialNumber.devInstanceIdRoot);

        ReleaseString(portDetails.serPortName);
        ReleaseString(portDetails.serFriendlyName);
        ReleaseString(portDetails.serDeviceName);
    }
}


// called when changing Options or on 5s display refresh timer for recently Arrived/Removed devices
void DeviceTracker::UpdateArrivedAndRemovedDevices()
{
    mDevicesArrivedOrRemoved = FALSE;

    if (DeviceInfo::GetPortList()) {
        FILETIME scanTime = GetTimeAsFileTimeUTC();

        UpdateArrivalOrRemovalState(scanTime);
    }

    if (!mDevicesArrivedOrRemoved) {
        // cancel timer if no more expected changes (ie no devices in fresh arrival/removal states)
        CancelArrivalTimer();
    }

    // re-sort ListView if necessary
    if (mNeedDevicesResort) {
        SortDeviceListView();
    }
}


// called after a device scan, (initial or after device changes)
// decides how to handle devices that have not been touched by scan
void DeviceTracker::CleanupOrphanedDevices(FILETIME &aNow, unsigned aScanId)
{
    DeviceInfo *item = DeviceInfo::GetPortList();

    while (item) {
        BOOL keepdevice = TRUE;

        if (item->LastScanId() != aScanId) {
            // note that changed Show options may exclude device from scan
            keepdevice = mOptions.ShowNotPresent() || mOptions.ShowRecentDisc();

            if (keepdevice) {
                enum DevType dType = item->DeviceType();

                if (dType == DevMicroDevBoard) {
                    keepdevice = mOptions.ShowDevBoardsOrAnySerial();
                } else if (dType == DevUnconfigMicroDevBoard) {
                    keepdevice = mOptions.ShowDevBoards();
                } else if ((dType == DevUnconfigRfidlerCom) || (dType == DevUnconfigMicroDevBoard)) {
                    keepdevice = mOptions.ShowNonConfig();
                } else if ((dType == DevOtherSerial) || (dType == DevArduinoSerial)) {
                    keepdevice = mOptions.ShowAnyOtherSerial();
                }

                if (keepdevice) {
                    // update device count, displayed icon & state, time since removal, etc...
                    item->UpdateDeviceState(FALSE, aNow, aScanId, NULL);
                }
            }
        }

        // next device in list, optionally deleting this device
        item = item->DeviceNext(keepdevice, FALSE);
    }
}


// new options may have excluded devices from scan list
void DeviceTracker::CleanupDevicesAfterOptionsChange()
{
    DeviceInfo *item = DeviceInfo::GetPortList();

    while (item) {
        BOOL keepdevice = TRUE;
        enum DevType dType = item->DeviceType();
        enum DevState dState = item->DeviceState();

        if (dType == DevMicroDevBoard) {
            keepdevice = mOptions.ShowDevBoardsOrAnySerial();
        } else if (dType == DevUnconfigMicroDevBoard) {
            keepdevice = mOptions.ShowDevBoards();
        } else if ((dType == DevOtherSerial) || (dType == DevArduinoSerial)) {
            keepdevice = mOptions.ShowAnyOtherSerial();
        } else if ((dType == DevUnconfigRfidlerCom) || (dType == DevUnconfigMicroDevBoard)) {
            keepdevice = mOptions.ShowNonConfig();
        }

        if (keepdevice) {
            if (dState == DevAbsent) {
                keepdevice = mOptions.ShowNotPresent();
            } else if (dState == DevRemoved) {
                keepdevice = mOptions.ShowRecentDisc();
            }
        }

        // next device in list, optionally deleting this device
        item = item->DeviceNext(keepdevice, FALSE);
    }
}


MonOptions& DeviceTracker::GetOptions()
{
    return mOptions;
}


// SetMode parameter indicates whether to apply changes from one dialog page or all Options/Setting pages
void DeviceTracker::SetOptions(const MonOptions& aOptions, SetMode setmode)
{
     // setting around what items are shown
    if ((SetAll == setmode) || (SetShowOptions == setmode)) {

        if (mOptions.CheckShowFlagsAreDifferent(aOptions)) {
            BOOL showSettingsChanged = FALSE;
            BOOL needSbRefresh = FALSE;

            if (mOptions.ShowNonConfig() != aOptions.ShowNonConfig()) {
                mInitialiseUnconfig = TRUE; // next scan should handle Unconfig as per initial scan
            }

            if (mOptions.ShowDevBoards() != aOptions.ShowDevBoards()) {
                mInitialiseMicrochipSerial = TRUE; // next scan should handle Microchip USB serial as per initial scan

                // ensure status bar is updated
                needSbRefresh = TRUE;
            }

            if (mOptions.ShowAnyOtherSerial() != aOptions.ShowAnyOtherSerial()) {
                mInitialiseAnyOtherSerial = TRUE; // next scan should handle other serial ports as per initial scan
                // TODO validate we don't also need to set mInitialiseMicroSer = TRUE;

                needSbRefresh = TRUE;
            }

            // copy new values, and setup saving changes to the registry 
            showSettingsChanged = mOptions.SetShowOptionsAndRegistrySave(aOptions);

            if (showSettingsChanged) {
                // handle changes where currently displayed devices are no longer needed
                CleanupDevicesAfterOptionsChange();
                // kick timer for a rescan
                KickDevLazyScanTimer();
            }

            if (needSbRefresh) {
                // repartition Status Bar, & refresh text
                SetStatusBarPartitions(aOptions);
                StatusBarRefresh();
            }
        }

        // handle any change to the Arrival / Removal display time
        mOptions.SetArrivalOrRemovalTime(aOptions.GetArrivalOrRemovalTime(), TRUE);
    }

    if ((SetAll == setmode) || (SetNotifyOptions == setmode)) {
        // copy new values, and setup saving changes to the registry 
        mOptions.SetNotifyOptionsAndRegistrySave(aOptions);
    }
}


void DeviceTracker::SetStatusBarPartitions(const MonOptions& aOptions)
{
    int sbWidths[4] = { 150, 0, 0, 0 };
    unsigned parts = 1;

    // dev board status field
    if (aOptions.ShowDevBoards()) {
        sbWidths[parts] = sbWidths[parts-1] + 170;
        parts ++;
    }

    // any serial status field
    if (aOptions.ShowAnyOtherSerial()) {
        sbWidths[parts] = sbWidths[parts-1] + 185;
        parts++;
    }

    sbWidths[parts++] = -1; // allocate the rest of the status bar

    SendMessage(mHWndStatusBar, SB_SETPARTS, parts, (LPARAM) sbWidths);
}


/*
   On plugging / unplugging devices are put into DevArrived / DevRemoved state
   for X minutes. Set by ArrivalOrRemovalTime maintained by an options setting.
   Then the devices switches to DevPresent, or DevRemoved/ not listed state, 
   depending on if 'show not present' option is set.
*/
void DeviceTracker::UpdateArrivalOrRemovalState(FILETIME &now)
{
    // update display state for arrived / removed devices
    DeviceInfo *item = DeviceInfo::GetPortList();

    while (item) {
        enum DevState dState = item->DeviceState();
        BOOL keepdevice = TRUE;

        switch (dState)
        {
        case DevAbsent:
            keepdevice = mOptions.ShowNotPresent();
            break;

        case DevPresent:
            break;

        case DevRemoved:
            // update display with elapsed time
            if (!item->UpdateTimeInState(now, mOptions.GetArrivalOrRemovalTime())) {
                // time expired
                keepdevice = mOptions.ShowNotPresent();
                if (keepdevice) {
                    item->SetDeviceAbsent();
                    UpdateViewItemState(item->StateName(), (LPARAM)item);
                }
            } else {
                // still in DevRemoved state
                mDevicesArrivedOrRemoved = TRUE;
            }
            break;

        case DevArrived:
            // update display with elapsed time, use default time for limit before DevPresent State
            if (!item->UpdateTimeInState(now, KArrivalOrRemovalTimeDefault)) {
                // time expired
                item->SetDevicePresent();
                UpdateViewItemState(item->StateName(), (LPARAM)item);
            } else {
                // still in DevArrived state
                mDevicesArrivedOrRemoved = TRUE;
            }
            break;
        }

        // next device in list, optionally deleting this device
        item = item->DeviceNext(keepdevice, FALSE);
    }
}


void DeviceTracker::UpdateStatusBarAndWinFlashNotifications()
{
    StatusBarRefresh();

    if (mNeedFlashWindow) {
        FlashWindow(mHWndMain, FALSE);
        mNeedFlashWindow = FALSE;
    }
}


// StatusBarRefresh() helper
void StringCbPrintStatus(
    __inout_bcount(cbDest) STRSAFE_LPWSTR pszDest,
    __in size_t cbDest,
    int count,
    LPWSTR objectName
    )
{
    if (count) {
        StringCbPrintf(pszDest, cbDest, L"%u %s", count, objectName);
    } else {
        StringCbCopy(pszDest, cbDest, L"No ");
        StringCbCat(pszDest, cbDest, objectName);
    }
    if (count != 1) {
        StringCbCat(pszDest, cbDest, L"s");
    }
    StringCbCat(pszDest, cbDest, L" connected");
}


/*
   Refresh device counts for Window Status Bar
  */
void DeviceTracker::StatusBarRefresh()
{
    static wchar_t statusBuffer[1024];

    // TODO? change icon overlay in system tray?

    // also update status bar - mHWndStatusBar
    if (mHWndStatusBar) {
        int partition = 0;

        // status bar has counts for Dev boards, Bootloaders, etc
        StringCbPrintStatus(statusBuffer, sizeof(statusBuffer), DeviceInfo::CountOfRfidlers(), L"RFIDler");
        SendMessage(mHWndStatusBar, SB_SETTEXT, partition++, (LPARAM) statusBuffer);

        // dev board status field?
        if (mOptions.ShowDevBoards()) {
            StringCbPrintStatus(statusBuffer, sizeof(statusBuffer), DeviceInfo::CountOfDevBoards(), L"Dev Board");
            SendMessage(mHWndStatusBar, SB_SETTEXT, partition++, (LPARAM) statusBuffer);
        }

        // any serial status field
        if (mOptions.ShowAnyOtherSerial()) {
            int count = DeviceInfo::CountOfOtherSerial();

            if (!mOptions.ShowDevBoards()) {
                count += DeviceInfo::CountOfDevBoards();
            }
            StringCbPrintStatus(statusBuffer, sizeof(statusBuffer), count, L"other COM port");
            SendMessage(mHWndStatusBar, SB_SETTEXT, partition++, (LPARAM) statusBuffer);
        }

        StringCbPrintStatus(statusBuffer, sizeof(statusBuffer), DeviceInfo::CountOfBootloaders(), L"HID Bootloader");
        SendMessage(mHWndStatusBar, SB_SETTEXT, partition++, (LPARAM) statusBuffer);
    }
}


void DeviceTracker::KickArrivalTimer()
{
    if (!mTimerArrival) {
        // run timer every ~5s
        SetTimer (mHWndMain, mTimerArrival = ARRIVAL_TIMER_MAGICNUMBER, 5000, NULL);
    }
}


void DeviceTracker::CancelArrivalTimer()
{
    if (mTimerArrival) {
        KillTimer(mHWndMain, mTimerArrival);
        mTimerArrival = 0;
    }
}


void DeviceTracker::KickContextMenuTimer()
{
    if (!mTimerContextMenu) {
        // run timer after ~120s
        SetTimer (mHWndMain, mTimerContextMenu = CANCEL_CONTEXTMENU_MAGICNUMBER, 120000, NULL);
    }
}


void DeviceTracker::CancelContextMenuTimer()
{
    if (mTimerContextMenu) {
        KillTimer(mHWndMain, mTimerContextMenu);
        mTimerContextMenu = 0;
    }
}


void DeviceTracker::KickDevFastScanTimer()
{
    if (!mTimerDevFastScan) {
        // wait at least 20ms
        SetTimer (mHWndMain, mTimerDevFastScan = DEV_FAST_SCAN_TIMER_MAGICNUMBER, 20, NULL);
    }
}


void DeviceTracker::KickDevLazyScanTimer()
{
    if (!mTimerDevLazyScan) {
        // wait at least 500ms, as changes often bunch together
        SetTimer (mHWndMain, mTimerDevLazyScan = DEV_LAZY_SCAN_TIMER_MAGICNUMBER, 500, NULL);
    }
}


void DeviceTracker::CancelDevScanTimers()
{
    if (mTimerDevFastScan) {
        KillTimer(mHWndMain, mTimerDevFastScan);
        mTimerDevFastScan = 0;
    }
    if (mTimerDevLazyScan) {
        KillTimer(mHWndMain, mTimerDevLazyScan);
        mTimerDevLazyScan = 0;
    }
}


BOOL DeviceTracker::CheckInitialScanFlag(enum DevType dType)
{
    switch(DeviceInfo::DeviceCategoryBasic(dType))
    {
    case DevCatRfidler:
    case DevCatBootloader:
        return mInitialiseRfidler;
    case DevCatMicroDev:
        return mInitialiseMicrochipSerial;
    case DevCatSerial:
        return mInitialiseAnyOtherSerial;
    case DevCatUnconfig:
    default:
        return mInitialiseUnconfig;
    }
}


// core notifications logic or Arrival / Removal
void DeviceTracker::NotificationLogic(enum DevType dType)
{
    BOOL updateStatusBar = FALSE;

    switch (dType)
    {
    case DevRfidlerCom:
        updateStatusBar = TRUE;
        // notify if wanted (except if Options just changed)
        mNeedFlashWindow = !mInitialiseRfidler && mOptions.NotifyRfidlerArrFlash();
        break;

    case DevMicroDevBoard:
        updateStatusBar = mOptions.ShowDevBoardsOrAnySerial();
        // notify if wanted (except if Options just changed)
        if (updateStatusBar) {
            if (mOptions.ShowDevBoards()) {
                mNeedFlashWindow = !mInitialiseMicrochipSerial && mOptions.NotifyMicrochipSerialArrFlash();
            } else {
                mNeedFlashWindow = !mInitialiseAnyOtherSerial && mOptions.NotifyAnyOtherSerialArrFlash();
            }
        }
        break;

    case DevMicroBootloader:
        updateStatusBar = TRUE;
        // notify if wanted (except if Options just changed)
        mNeedFlashWindow = !mInitialiseRfidler && mOptions.NotifyMicrochipBootloaderArrFlash();
        break;

    case DevArduinoSerial:
        updateStatusBar = mOptions.ShowAnyOtherSerial();
        // notify if wanted (except if Options just changed)
        mNeedFlashWindow = updateStatusBar && !mInitialiseAnyOtherSerial && mOptions.NotifyArduinoSerialArrFlash();
        break;

    case DevOtherSerial:
        updateStatusBar = mOptions.ShowAnyOtherSerial();
        // notify if wanted (except if Options just changed)
        mNeedFlashWindow = updateStatusBar && !mInitialiseAnyOtherSerial && mOptions.NotifyAnyOtherSerialArrFlash();
        break;

    default:
        // future feature, arrival notifications for DevOtherSerial, DevHalfKayBootloader ?
        break;
    }

    if (updateStatusBar) {
        StatusBarRefresh();
    }
}


// common function for new device or changing state to DevArrived/DevPresent
void DeviceTracker::DetermineArrivalNotifications(enum DevType dType, enum DevState newState)
{
    assert((newState == DevPresent) || (newState == DevArrived));

    if (newState == DevArrived) {
        mDevicesArrivedOrRemoved = TRUE;
    }

    NotificationLogic(dType);
}


// common function for forgetting device or changing state to DevRemoved
void DeviceTracker::DetermineRemovalNotifications(enum DevType dType, enum DevState newState)
{
    assert((newState != DevPresent) && (newState != DevArrived));

    if (newState == DevRemoved) {
        mDevicesArrivedOrRemoved = TRUE;
    }

    NotificationLogic(dType);
}


FILETIME DeviceTracker::GetTimeAsFileTimeUTC()
{
    SYSTEMTIME st;
    FILETIME   ft;
    BOOL res;

    GetSystemTime(&st);              // current system time (UTC)
    res = SystemTimeToFileTime(&st, &ft);  // file time format

    assert(res);

    return ft;
}


/* end of file devicetracker.cpp */