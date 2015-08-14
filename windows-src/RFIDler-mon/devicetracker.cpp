/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: devicetracker.cpp

    Author: Anthony Naggs, 2014

    Copyright (c) 2014-2015 Anthony Naggs.
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
#include <wdmguid.h>


/*
    ListView notes
    ==============

    keyboard shortcuts
    SPACE              Locates new selection and anchor for the item.
    SHIFT + SPACE      Extends the selection from anchor to the item.
    CTRL + SPACE       Invoke additional selection or deselection and move the anchor to the selected item.
    Arrow keys         Move focus and remove all selection and the anchor previously made.
    CTRL + NUM+ (Control with Numberpad +)
                       In details view resizes the colmuns to content width
    Drop Menu key (VK_APPS) or SHIFT + F10
                       WM_CONTEXTMENU is processed if the ListView has an item selected

    currently non-functioning shortcuts
    CTRL+arrow keys    Move focus without move of selection or the anchor.
    Any printable key  Moves the selection to the item matching prefix letters in the beginning of the label.
                       (generates LVN_INCREMENTALSEARCHW message, not currently handled)
*/


DeviceInfo *DeviceTracker::mListDevices = NULL;


void DeviceTracker::SetViewStyle(int viewButton)
{
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

    ListView_SetView(mHWndListView, newStyle);
    mOptions.SaveViewStyleButton(viewButton);

    /* Re-sort ListView if changing to Details View, as documentation
        implies sorting does not affect other view styles.
    */
    if (newStyle == LV_VIEW_DETAILS) {
        mNeedDevicesResort = FALSE;
        ListView_SortItems(mHWndListView, DeviceInfo::CompareProc, mSortType);
    }
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


BOOL DeviceTracker::AddViewItem(const wchar_t *aName, enum DevImage aImage, const wchar_t *aDevType, 
            const wchar_t *aState, const wchar_t *aUsbLocation, const wchar_t *aSerialNumber, LPARAM lParam)
{
    LVITEM lvItem;
    int    itemId = -1;
    // Tile View stuff
    unsigned int tileColumns[] = { lvDispType, lvDispState, lvDispLocus, lvDispSernum };
    int tileFormat[] = { LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT };


    ZeroMemory(&lvItem, sizeof(LVITEM));
    lvItem.iItem = 0;
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
        if (mSortType == lvDispName) {
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
        if (mSortType == lvDispState) {
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
        if (mSortType == lvDispType) {
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
        if (mSortType == lvDispState) {
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
        if (mSortType == lvDispLocus) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::UpdateViewItemSerialNumber(const wchar_t *aSerialNumber, LPARAM lParam)
{
    int itemId = FindViewItem(lParam);

    if (itemId > -1) {
        ListView_SetItemText(mHWndListView, itemId, lvDispSernum, (LPWSTR)aSerialNumber);
        // need to re-sort View?
        if (mSortType == lvDispSernum) {
            mNeedDevicesResort = TRUE;
        }
    }
}


void DeviceTracker::RegisterForDevNotifications()
{
    DEV_BROADCAST_DEVICEINTERFACE dbc;

    ZeroMemory(&dbc, sizeof(DEV_BROADCAST_DEVICEINTERFACE));
    dbc.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);

    // use DBT_DEVTYP_HANDLE if you have an open handle & want to watch device removal
    dbc.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    // set dbc.dbcc_classguid if only interested in 1 device type

    if (!mHNotifyHid) {
        dbc.dbcc_classguid = GUID_DEVCLASS_HIDCLASS;
        mHNotifyHid = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE);
    }

    if (!mHNotifySerial) {
        dbc.dbcc_classguid = GUID_DEVCLASS_PORTS;
        mHNotifySerial = RegisterDeviceNotification(mHWndMain, &dbc, DEVICE_NOTIFY_WINDOW_HANDLE);
    }
}


void DeviceTracker::UnregisterForDevNotifications()
{
    if (mHNotifyHid) {
        UnregisterDeviceNotification(mHNotifyHid);
        mHNotifyHid = 0;
    }
    if (mHNotifySerial) {
        UnregisterDeviceNotification(mHNotifySerial);
        mHNotifySerial = 0;
    }
}


/*
    DBT_DEVNODES_CHANGED => device tree changes, set timer for a rescan.

    DBT_DEVICEARRIVAL || DBT_DEVICEREMOVECOMPLETE => Device arrival / removal
    We currently only pay attention if accompanied by a DBT_DEVTYP_DEVICEINTERFACE
    structure, and check for HID and whether it is Mictochip Bootloader.

    In theory we could be interested in a DBT_DEVTYP_PORT structure, referring to
    a COM port ...
            
    However we don't process this for now, as we have never seen usbser.sys
    generate these, and the 'friendly name' given in the notification is anway
    hard to test if it is a specific RFIDler / Microchip USB port.

    With a DBT_DEVTYP_DEVICEINTERFACE a typical dbcc_name =
    "\\?\USB#VID_04D8&PID_003C#6&33d1b76f&0&1#{a5dcbf10-6530-11d2-901f-00c04fb951ed}"
    or "\\?\HID#VID_04D8&PID_003C#7&f4c61c5&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"
        "\\?\USB#VID_04D8&PID_003C" -> HardwareId "USB\VID_04D8&PID_003C"
        #                    separator
        "6&33d1b76f&0&1"     Windows generated serial number
        #
        "{a5dcbf10-6530-11d2-901f-00c04fb951ed}" -> GUID_DEVINTERFACE_USB_DEVICE
 */
void DeviceTracker::OnDeviceChange(UINT uiType, LPARAM lParam)
{
    BOOL interesting = FALSE;

    if (uiType == DBT_DEVNODES_CHANGED) {
        // set timer to rescan device tree for changes
        interesting = TRUE;
    } else {
        if (uiType == DBT_DEVICEARRIVAL || uiType == DBT_DEVICEREMOVECOMPLETE) {
            DEV_BROADCAST_HDR *dbh = (DEV_BROADCAST_HDR*) lParam;

#ifdef _DEBUG
            PrintDebugStatus(_T("DevChange %s, Device Type %i\n"), 
                uiType == DBT_DEVICEARRIVAL ? _T("DBT_DEVICEARRIVAL") : _T("DBT_DEVICEREMOVECOMPLETE"),
                dbh->dbch_devicetype);
#endif

            if (dbh->dbch_devicetype == DBT_DEVTYP_PORT) {
                interesting = TRUE;
            } else if (dbh->dbch_devicetype == DBT_DEVTYP_DEVICEINTERFACE) {
                DEV_BROADCAST_DEVICEINTERFACE *dbdi = (DEV_BROADCAST_DEVICEINTERFACE*) dbh;

                // check if notification is for a device we are interested in
                if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVCLASS_HIDCLASS)) {
                    interesting = TRUE;
                } else if (IsEqualGUID(dbdi->dbcc_classguid, GUID_DEVCLASS_PORTS)) {
                    interesting = TRUE;
                }
            }
        }
    }

    // set timer to rescan device tree for changes
    if (interesting) {
        KickDevScanTimer();
    }
}


// put device icons in image list
HIMAGELIST DeviceTracker::InitImageList(int cx, int cy, unsigned count, const int *iconlist)
{
    HIMAGELIST iList = ImageList_Create(cx, cy, ILC_MASK, count, count);

    if (iList) {
        unsigned i;
        BOOL fail = FALSE;

        for (i = 0; (i < count) && !fail; i++) {
            HICON hi = (HICON) LoadImage(mHInst, MAKEINTRESOURCE(iconlist[i]),
                IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
            if (hi) {
                if (-1 == ImageList_AddIcon(iList, hi)) {
                    fail = TRUE;
                }
                DestroyIcon(hi);
            } else {
                fail = TRUE;
            }
        }
        if (fail) {
            ImageList_Destroy(iList);
            iList = NULL;
        }
    }

    return iList;
}


void DeviceTracker::InitListColumns(const wchar_t **columns, const int *widths, unsigned count)
{
    LVCOLUMN lvcol;
    unsigned i;

    lvcol.mask = LVCF_FMT | LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
    lvcol.fmt = LVCFMT_LEFT;
    for (i = 0; i < count; i++) {
        lvcol.pszText = (LPWSTR) columns[i];
        lvcol.cx = widths[i];
        lvcol.iSubItem = i;
        ListView_InsertColumn(mHWndListView, i, &lvcol);
    }
}


void DeviceTracker::Initialize(HWND HWndMain, HWND HWndListView, HWND HWndStatusBar, HINSTANCE HInst)
{
    // icons for device view
    const int iconList[] = { IDI_RFIDOKAY, IDI_RFIDBAD, IDI_RFIDREMOVE,
            IDI_RFIDBOOT, IDI_DEVBOARD, IDI_DEVBOARDREMOVE, IDI_DEVBOARDBAD,
            IDI_OTHERSERIALOK, IDI_OTHERSERIALREMOVE };
    // column headings for view
    const wchar_t *columns[] = { _T("Name"), _T("Device"), _T("State"), _T("Location"),
            _T("Serial number") };
    // TODO? use these as defaults, but persist & restore col widths
    const int    colwidth[] = { 100, 70, 100, 100, 122 };

    mHWndMain = HWndMain;
    mHWndListView = HWndListView;
    mHWndStatusBar = HWndStatusBar;
    mHInst = HInst;
    mOptions.SetHwndMain(HWndMain);

    // read any saved options from registry
    mOptions.ReadRegistryValues();

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    /* SetupDiGetDeviceProperty() api is new in Windows Vista
       There are a lot of Win XP systems around still, so don't unnecessarily
       be incompatible with them.
    */
    {
        HMODULE hModule = GetModuleHandle(TEXT("setupapi.dll"));
        if (hModule) {
            mSetupDiGetDevicePropertyW = (LPFNSetupDiGetDevicePropertyW)
                GetProcAddress(hModule, "SetupDiGetDevicePropertyW");
        }
    }
#endif

    // enable tooltips, in all display views, also full row select
    ListView_SetExtendedListViewStyle(mHWndListView, LVS_EX_INFOTIP  | LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT);

    RegisterForDevNotifications();

    // create image lists
    mImageList = InitImageList(32, 32, ARRAYSIZE(iconList), iconList);
    if (mImageList) {
        ListView_SetImageList(mHWndListView, mImageList, LVSIL_NORMAL);
    }
    mImageListSm = InitImageList(16, 16, ARRAYSIZE(iconList), iconList);
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
    assert(ARRAYSIZE(columns) == ARRAYSIZE(colwidth));

    InitListColumns(columns, colwidth, ARRAYSIZE(columns));

    int restoredStyle = mOptions.GetViewStyleButton();
    SetViewStyle(restoredStyle);
    // initial menu check mark
    HMENU hMenu = GetMenu(mHWndMain);
    CheckMenuItem(hMenu, restoredStyle, MF_CHECKED);

    // init ListView sort order from saved values
    SetViewSortOrder(mOptions.GetSortOrder());

    HWND hWndHdr = ListView_GetHeader(mHWndListView);
    if (hWndHdr) {
        int sortColumn = mSortType;
        BOOL reverse = false;
        HDITEM hdrItem;
        hdrItem.mask = HDI_FORMAT;

        if (sortColumn >= lvRevDispName) {
            sortColumn -= lvRevDispName;
            reverse = true;
        }

        if (Header_GetItem(hWndHdr, sortColumn, &hdrItem)) {
            hdrItem.fmt |= reverse ? HDF_SORTDOWN : HDF_SORTUP;
            Header_SetItem(hWndHdr, sortColumn, &hdrItem);
        }
    }

    // kick timer to do initial device scan
    KickDevScanTimer();

    StatusBarRefresh();
}


// Windows should cleanup resources on exit, but it is good practice to do our own.
void DeviceTracker::Cleanup()
{
    CancelArrivalTimer();
    CancelDevScanTimer();
    mOptions.CancelRegSaveTimer();

    if (mImageList) {
        ImageList_Destroy(mImageList);
    }
    if (mImageListSm) {
        ImageList_Destroy(mImageListSm);
    }

    // free our device list (an object is orphaned if somehow locked for Context Menu tracking at this point)
    while (mListDevices) {
        mListDevices = mListDevices->DeleteDevice(TRUE);
    }

    UnregisterForDevNotifications();
}


// return TRUE if any devices are in Arrived or Removed states
void DeviceTracker::ScanRfidlerDevices()
{
    // use timer as a one-shot
    CancelDevScanTimer();

    // update scanned device lists
    ScanForDevChanges();
    mInitialiseRfidler = FALSE;
    mInitialiseUnconfig = FALSE;
    mInitialiseMicroSer = FALSE;
    mInitialiseAnySerial = FALSE;

    // if there any devices in Arrived or Removed state ensure disp refresh timer is running
    if (mListDevices) {
        if (!mDevicesInArrivalState) {
            for (DeviceInfo *devList = mListDevices; devList; devList = devList->DeviceNext()) {
                enum DevState dState = devList->DeviceState();

                if ((dState == DevRemoved) || (dState == DevArrived)) {
                    mDevicesInArrivalState = TRUE;
                    break;
                }
            }
        }

        if (mDevicesInArrivalState) {
            KickArrivalTimer();
        }

        // re-sort ListView if necessary
        if (mNeedDevicesResort) {
            mNeedDevicesResort = FALSE;
            ListView_SortItems(mHWndListView, DeviceInfo::CompareProc,
                    mSortType);
        }
    }
}


void DeviceTracker::ScanForDevChanges()
{
    // unique id for each scan, to allow old entries to be identified
    static unsigned scanId = 31415926;  // arbitrary initial value
    SYSTEMTIME st;
    FILETIME   ft;

    GetSystemTime(&st);              // current system time (UTC)
    SystemTimeToFileTime(&st, &ft);  // file time format

    if (mOptions.ShowNonConfig()) {
        // have to scan all devices in order to check for unconfigured
        ScanIncludingUnconfigDevs(ft, scanId);
    } else {
        // check for device types we are specifically interested in
        ScanHidDevices(ft, scanId);
        ScanSerialDevices(ft, scanId);
    }

    CleanupOrphanedDevices(ft, scanId);

    UpdateStatusBarAndWinFlashNotifications();
    scanId++;
}


BOOL DeviceTracker::GetDeviceGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid,
    CONST DEVPROPKEY PropKey, DWORD Property)
{
    DWORD size;
    BOOL result;

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
        // use Windows XP api, note gets GUID in REG_SZ form
        DWORD type;
        wchar_t guidStringBuffer[40];

        result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, Property,
            &type, (PBYTE) guidStringBuffer, sizeof(guidStringBuffer), &size) && (type == REG_SZ);
        // convert guid string to GUID (Unicode build only)
        if (result && (S_OK != IIDFromString(guidStringBuffer, &DevGuid))) {
            result = FALSE;
        }
    }

    return result;
}


BOOL DeviceTracker::GetDeviceClassGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid)
{
    return GetDeviceGUID(DeviceInfoSet, DeviceInfoData, DevGuid, DEVPKEY_Device_ClassGuid, SPDRP_CLASSGUID);
}


BOOL DeviceTracker::GetDeviceBusTypeGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &BusGuid)
{
    return GetDeviceGUID(DeviceInfoSet, DeviceInfoData, BusGuid, DEVPKEY_Device_BusTypeGuid, SPDRP_BUSTYPEGUID);
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
        enum DevType dType = mOptions.ShowAnySerial() ? DevOtherSerial : DevUnknown;

        // examine serial device
        if (aPortType == SerialPort) {
            if (CheckDeviceId(devInstanceId, size, szRfidlerHwUsbId)) {
                dType = DevRfidlerCom;
            } else if (mOptions.ShowDevBoardsOrAnySerial() && CheckDeviceId(devInstanceId, size, szMicrochipSerialHwUsbId)) {
                dType = DevMicroDevBoard;
            }
        }

        // note separation of COM or LPT ports occurs in AddOrUpdateDevice()
        if (dType != DevUnknown) {
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
        }
    }
}


// if serial device does not yet have driver configured it has no class set
void DeviceTracker::CheckClassNoneDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        enum DevType dType = DevUnknown;

        // check USB hardware id for unconfigured RFIDler, Microchip devboard
        if (CheckDeviceId(devInstanceId, size, szRfidlerHwUsbId)) {
            // Get RFIDler dev details
            dType = DevUnconfigRfidlerCom;
        } else if (mOptions.ShowDevBoardsOrAnySerial() &&
                CheckDeviceId(devInstanceId, size, szMicrochipSerialHwUsbId)) {
            // Get Microchip USB Serial device details
            dType = DevUnconfigMicroDevBoard;
        }

        if (dType != DevUnknown) {
            // Get RFIDler or Get Microchip USB Serial device details
            AddOrUpdateDevice(dType, DeviceInfoSet, DeviceInfoData, devInstanceId, size, SerialPort, aNow, aScanId);
        }
    }
}


void DeviceTracker::ScanIncludingUnconfigDevs(FILETIME &aNow, unsigned aScanId)
{
    HDEVINFO DeviceInfoSet;
    SP_DEVINFO_DATA DeviceInfoData;
    GUID DevGuid;
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
        BOOL gotClassGuid = GetDeviceClassGUID(DeviceInfoSet, DeviceInfoData, DevGuid);

        DeviceIndex++;
        
        if (gotClassGuid) {
            if (IsEqualGUID(DevGuid, GUID_DEVCLASS_PORTS)) {
                // examine serial device
                CheckSerialDevice(DeviceInfoSet, DeviceInfoData, SerialPort, aNow, aScanId);
            } else if (IsEqualGUID(DevGuid, GUID_DEVCLASS_HIDCLASS)) {
                CheckHidDevice(DeviceInfoSet, DeviceInfoData, aNow, aScanId);
            } else if (mOptions.ShowAnySerial()) {
                if (IsEqualGUID(DevGuid, GUID_DEVCLASS_MODEM)) {
                    CheckSerialDevice(DeviceInfoSet, DeviceInfoData, SerialModem, aNow, aScanId);
                } else if (IsEqualGUID(DevGuid, GUID_DEVCLASS_MULTIPORTSERIAL)) {
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
       'Show Any Serial' needs to include Modems & Multiport Serial devices
    */
    const GUID *serialGuid[] = { &GUID_DEVCLASS_PORTS, &GUID_DEVCLASS_MODEM, &GUID_DEVCLASS_MULTIPORTSERIAL };
    const SerialPortType portTypes[] = { SerialPort, SerialModem, SerialMultiport };
    int maxGuid = mOptions.ShowAnySerial() ? ARRAYSIZE(serialGuid) : 1;

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
enum DevState DeviceTracker::GetDevPresentStatus(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    static  wchar_t pdoNameBuffer[1024];
    BOOL result;
    DWORD size;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &DEVPKEY_Device_PDOName,
                                        &PropType,
                                        (PBYTE)&pdoNameBuffer,
                                        sizeof(pdoNameBuffer),
                                        &size,
                                        0)
                    && (PropType == DEVPROP_TYPE_STRING);
    } else {
#elif defined(USE_SETUP_DEVICE_REGISTRY)
    {
#endif
        DWORD type;
        result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_PHYSICAL_DEVICE_OBJECT_NAME,
            &type, (PBYTE) &pdoNameBuffer, sizeof(pdoNameBuffer), &size)
            && (type == REG_SZ);
    }

    return result ? DevPresent : DevAbsent;
}


void DeviceTracker::UnpackUSBLocation(DeviceLocation& location, wchar_t* devLocationString)
{
    // typical string = "Port_#0001.Hub_#0006"
    wchar_t  *str = NULL;
    unsigned offset = 0;

    if (wcs_consumeprefix(devLocationString, L"Port_#", &offset)) {
        location.devUsbPort = wcstoul(devLocationString + offset, &str, 10);
        if ((errno == 0) && wcs_consumeprefix(str, L".Hub_#", &offset)) {
            location.devUsbHub = wcstoul(str + offset, &str, 10);
            if (errno == 0) {
                location.devBusType = BusUSB; // success
            }
        }
    }
}


DeviceLocation DeviceTracker::GetUSBDeviceLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    static wchar_t  devLocationBuffer[1024];
    DWORD size;
    BOOL result;
    DeviceLocation  location;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &DEVPKEY_Device_LocationInfo,
                                        &PropType,
                                        (PBYTE)&devLocationBuffer,
                                        sizeof(devLocationBuffer),
                                        &size,
                                        0)
                    && (PropType == DEVPROP_TYPE_STRING);
    } else {
#elif defined(USE_SETUP_DEVICE_REGISTRY)
    {
#endif
        DWORD type;
        result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_LOCATION_INFORMATION,
            &type, (PBYTE) &devLocationBuffer, sizeof(devLocationBuffer) - 1, &size)
            && (type == REG_SZ);
    }

    if (result) {
        devLocationBuffer[size/sizeof(wchar_t)] = 0; // safety, should already be 0 terminated
        UnpackUSBLocation(location, devLocationBuffer);
    }

    return location;
}


DeviceLocation DeviceTracker::GetDeviceLocationFromBusGUID(GUID &BusGUID)
{
    DeviceLocation location;

    /* 
        GUID_BUS_TYPE_USB shouldn't reach here.
        Otherwise, we don't handle these bus types:
        GUID_BUS_TYPE_INTERNAL
        GUID_BUS_TYPE_LPTENUM
        GUID_BUS_TYPE_USBPRINT
        GUID_BUS_TYPE_DOT4PRT
        GUID_BUS_TYPE_SERENUM
        GUID_BUS_TYPE_HID
        GUID_BUS_TYPE_AVC
        GUID_BUS_TYPE_IRDA
        */

    // check plausible(?) bus types for a serial port
    if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_PCMCIA)) {
        location.devBusType = BusPCMCIA;
    } else if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_PCI)) {
        location.devBusType = BusPCI;
    } else if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_ISAPNP)) {
        location.devBusType = BusISAPNP;
    } else if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_EISA)) {
        location.devBusType = BusEISA;
    } else if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_MCA)) {
        location.devBusType = BusMCA;
    } else if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_1394)) {
        location.devBusType = BusFirewire;
    } else if (IsEqualGUID(BusGUID, GUID_BUS_TYPE_SD)) {
        location.devBusType = BusSD;
    }

    return location;
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

    // where to look - HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB + \VID_xxxx&PID_xxxx
    locationBuffer[0] = 0;
    StringCbPrintf(registryKeyName, sizeof(registryKeyName), _T("SYSTEM\\CurrentControlSet\\Enum\\USB\\%.17s"), VIDstring);
    StringCbCopy(serialNumberKey, sizeof(serialNumberKey), serialString);

    // crop last '&' and device interface id from serial number
    lastAmp = wcsrchr(serialNumberKey, '&');
    if (lastAmp) {
        *lastAmp = 0;
    }

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, registryKeyName, 0, KEY_READ, &hKey)) {
        // search subkeys for matching serial number
#define MAX_KEY_LENGTH 255
        TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
        DWORD    cbName;                   // size of name string
        TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
        DWORD    cchClassName = MAX_PATH;  // size of class string
        DWORD    cSubKeys=0;               // number of subkeys
        DWORD    cbMaxSubKey;              // longest subkey size
        DWORD    cchMaxClass;              // longest class string
        DWORD    cValues;              // number of values for key
        DWORD    cchMaxValue;          // longest value name
        DWORD    cbMaxValueData;       // longest value data
        DWORD    cbSecurityDescriptor; // size of security descriptor
        FILETIME ftLastWriteTime;      // last write time
        DWORD i, retCode;
        BOOL match = FALSE;

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
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);
            if (ERROR_SUCCESS == retCode) {
                DWORD valtype;
                DWORD valsize = sizeof(locationBuffer);
                HKEY hKey2;

                retCode = RegOpenKeyEx(hKey, achKey, 0, KEY_READ, &hKey2);

                if (ERROR_SUCCESS == retCode) {
                    // get ParentIdPrefix value, & compare with target serial number
                    retCode = RegQueryValueEx(hKey2, _T("ParentIdPrefix"), 0, &valtype, (BYTE*)&locationBuffer, &valsize);
                    if ((ERROR_SUCCESS == retCode) && (REG_SZ == valtype) && (0 == _wcsicmp(locationBuffer, serialNumberKey))) {
                        match = TRUE; // exit loop
                        valsize = sizeof(locationBuffer);

                        // now get usb Location value
                        retCode = RegQueryValueEx(hKey2, _T("LocationInformation"), 0, &valtype, (BYTE*)&locationBuffer, &valsize);
                        if ((ERROR_SUCCESS == retCode) && (REG_SZ == valtype)) {
                            //PrintDebugStatus(TEXT("LocationInformation %s\n"), locationBuffer);
                            UnpackUSBLocation(location, locationBuffer);
                        }
                    }

                    RegCloseKey(hKey2);
                }

                // DEBUG - PrintDebugStatus(TEXT("(%d) %s %u\n"), i+1, achKey, retCode);
            }
        }

#undef MAX_KEY_LENGTH
        RegCloseKey(hKey);
    }

    return location;
}


DeviceLocation DeviceTracker::GetDeviceLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, DeviceSerialNumber &aSerialNumber)
{
    unsigned        offsetToVID = 0;
    DeviceLocation  location;

    if (wcs_checkprefix(aSerialNumber.devHardwareId, _T("USB\\"))) {
        location = GetUSBDeviceLocation(DeviceInfoSet, DeviceInfoData);
    } else {
        GUID    BusGuid;

        if (wcs_checkprefix(aSerialNumber.devHardwareId, _T("BTHENUM\\"))) {
            location.devBusType = BusBluetooth; // Widcomm / Broadcom Bluetooth drivers
        } else if (wcs_consumeprefix(aSerialNumber.devHardwareId, _T("HID\\"), &offsetToVID) ||
                    wcs_consumeprefix(aSerialNumber.devHardwareId, _T("NMWCD\\"), &offsetToVID)) {
            // HID or Nokia Mobile Wireless Communications Device
            location = GetDeviceUSBRegistryLocation(aSerialNumber.devHardwareId + offsetToVID, aSerialNumber.devSerialString);
        } else if (GetDeviceBusTypeGUID(DeviceInfoSet, DeviceInfoData, BusGuid)) {
            location = GetDeviceLocationFromBusGUID(BusGuid);
        }
    }

    return location;
}


wchar_t *DeviceTracker::GetFriendlyName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    static  wchar_t friendlyName[50];
    BOOL result;
    DWORD size;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &DEVPKEY_Device_FriendlyName,
                                        &PropType,
                                        (PBYTE)&friendlyName,
                                        sizeof(friendlyName),
                                        &size,
                                        0)
                    && (PropType == DEVPROP_TYPE_STRING);
    } else {
#elif defined(USE_SETUP_DEVICE_REGISTRY)
    {
#endif
        DWORD type;
        result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_FRIENDLYNAME,
            &type, (PBYTE) &friendlyName, sizeof(friendlyName), &size)
            && (type == REG_SZ);
    }

    // on success dupe the string
    return result ? _wcsdup(friendlyName) : NULL;
}


wchar_t* DeviceTracker::GetPortname(HKEY devkey)
{
#define portbuffSize 16
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
        serialNumber.devHardwareId = wcs_dupsubstr(devInstanceId, serpos - 1);
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
   */
DeviceInfo *DeviceTracker::FindDevMatchBySernum(enum DevType aDevType, wchar_t *sernumber)
{
    DeviceInfo *devList = mListDevices;

    while (devList) {
        BOOL cmpSernum = FALSE;
        enum DevType dType = devList->DeviceType();

        if (dType == aDevType) {
            cmpSernum = TRUE;
        } else {
            // control which type transitions are allowed
            switch (aDevType)
            {
            case DevRfidlerCom:
            case DevUnconfigRfidlerCom:
                if ((dType == DevRfidlerCom) || (dType == DevUnconfigRfidlerCom)) {
                    cmpSernum = TRUE;
                }
                break;
            case DevMicroDevBoard:
            case DevUnconfigMicroDevBoard:
                if ((dType == DevMicroDevBoard) || (dType == DevUnconfigMicroDevBoard)) {
                    cmpSernum = TRUE;
                }
                break;
            }
        }

        if (cmpSernum) {
            const wchar_t *temp = devList->SerialNumber();
            if (temp && !wcscmp(temp, sernumber)) {
                return devList;
            }
        }
        devList = devList->DeviceNext();
    }
    return NULL;
}


void DeviceTracker::AddOrUpdateDevice(enum DevType aDevType, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        const wchar_t *devInstanceId, DWORD size, SerialPortType aPortType, FILETIME &aNow, unsigned aScanId)
{
    enum DevState       dState;
    DeviceLocation      location;
    DevicePortDetails   portDetails;
    DeviceSerialNumber  serialNumber;
    BOOL                added = FALSE;
    DeviceInfo          *devItem = NULL;

    if (mOptions.ShowNotPresent()) {
        // get device present status: DevPresent or DevAbsent
        dState = GetDevPresentStatus(DeviceInfoSet, DeviceInfoData);
    } else {
        dState = DevPresent;
    }
    
    // split devInstanceId into HardwareId (bus + vid, pid & function) and Serial Number string (& flag if Windows generated)
    serialNumber = GetSerialnumber(devInstanceId, size);

    devItem = FindDevMatchBySernum(aDevType, serialNumber.devSerialString);

    // get more details for new or Present device
    if ((!devItem) || (dState == DevPresent)) {
        // USB hub & port are easy to get for USB/... devices, harder for HID/...
        location = GetDeviceLocation(DeviceInfoSet, DeviceInfoData, serialNumber);

        switch (aDevType) // get COM port name
        {
        case DevRfidlerCom:
        case DevMicroDevBoard:
        case DevOtherSerial:
            {
                unsigned offset = 0;
                portDetails.devPortName = GetPortname(DeviceInfoSet, DeviceInfoData);
                if (DevOtherSerial == aDevType) {
                    if (!portDetails.devPortName || (0 != wcsncmp(portDetails.devPortName, _T("COM"), 3))) {
                        // LPT port presumably => not interesting
                        return;
                    }
                    // get friendly name, if any
                    portDetails.devFriendlyName = GetFriendlyName(DeviceInfoSet, DeviceInfoData);
                }
                if (portDetails.devPortName && wcs_consumeprefix(portDetails.devPortName, _T("COM"), &offset)) {
                    portDetails.devPortNumber = wcstoul(portDetails.devPortName + offset, NULL, 10);
                }
            }
            break;
        }
    }

    if (devItem) {
        // device in list, so update connected state, COM port name, USB location, ..
        devItem->UpdateDevice(aDevType, dState, aNow, portDetails, location, serialNumber, aScanId);
    } else {
        // create new device object, & add to display
        added = DeviceInfo::AddDeviceToList(aDevType, dState, aNow, portDetails, location, serialNumber, aScanId, aPortType);
    }

    // cleanup memory
    if (!added) {
        ReleaseString(portDetails.devPortName);
        ReleaseString(serialNumber.devSerialString);
        ReleaseString(portDetails.devFriendlyName);
        ReleaseString(serialNumber.devHardwareId);
    }
}


// called when changing Options or on 5s display refresh timer for recently Arrived/Removed devices
void DeviceTracker::UpdateArrivedAndRemovedDevices()
{
    mDevicesInArrivalState = FALSE;

    if (mListDevices) {
        SYSTEMTIME st;
        FILETIME   ft;

        GetSystemTime(&st);              // current system time (UTC)
        SystemTimeToFileTime(&st, &ft);  // file time format

        UpdateArrivalOrRemovalState(ft);
    }

    if (!mDevicesInArrivalState) {
        // cancel timer if no more expected changes (ie no devices in fresh arrival/removal states)
        CancelArrivalTimer();
    }

    // re-sort ListView if necessary
    if (mNeedDevicesResort) {
        mNeedDevicesResort = FALSE;
        ListView_SortItems(mHWndListView, DeviceInfo::CompareProc,
                mSortType);
    }
}


// called after a device scan, (initial or after device changes)
void DeviceTracker::CleanupOrphanedDevices(FILETIME &aNow, unsigned aScanId)
{
    DeviceInfo *item = mListDevices;

    while (item) {
        BOOL unlink = FALSE;

        if (item->LastScanId() != aScanId) {
            // note that new options may have excluded device from scan
            if (!mOptions.ShowNotPresent() && !mOptions.ShowRecentDisc()) {
                unlink = TRUE;
            } else {
                enum DevType dType = item->DeviceType();

                if ( ((dType == DevMicroDevBoard) || (dType == DevUnconfigMicroDevBoard))
                        && !mOptions.ShowDevBoardsOrAnySerial() ) {
                    unlink = TRUE;
                } else if ( ((dType == DevUnconfigRfidlerCom) || (dType == DevUnconfigMicroDevBoard))
                        && !mOptions.ShowNonConfig() ) {
                    unlink = TRUE;
                } else if ( (dType == DevOtherSerial) && !mOptions.ShowAnySerial() ) {
                    unlink = TRUE;
                } else {
                    // update device count, displayed icon & state, etc...
                    item->UpdateDeviceState(DevAbsent, aNow, aScanId);
                }
            }
        }

        if (unlink) {
            item = item->DeleteDevice(FALSE);
        } else {
            item = item->DeviceNext();
        }
    } // while
}


// new options may have excluded devices from scan list
void DeviceTracker::CleanupDevicesAfterOptionsChange()
{
    DeviceInfo *item = mListDevices;

    while (item) {
        BOOL unlink = FALSE;
        enum DevType dType = item->DeviceType();
        enum DevState dState = item->DeviceState();

        if ( ((dType == DevMicroDevBoard) || (dType == DevUnconfigMicroDevBoard))
                && !mOptions.ShowDevBoardsOrAnySerial()) {
            unlink = TRUE;
        } else if ( (dType == DevOtherSerial) && !mOptions.ShowAnySerial() ) {
            unlink = TRUE;
        } else if ( ((dType == DevUnconfigRfidlerCom) || (dType == DevUnconfigMicroDevBoard))
                && !mOptions.ShowNonConfig() ) {
            unlink = TRUE;
        } else if ((dState == DevAbsent) && !mOptions.ShowNotPresent()) {
            unlink = TRUE;
        } else if ((dState == DevRemoved) && !mOptions.ShowRecentDisc()) {
            unlink = TRUE;
        }

        if (unlink) {
            item = item->DeleteDevice(FALSE);
        } else {
            item = item->DeviceNext();
        }
    } // while
}


MonOptions& DeviceTracker::GetOptions()
{
    return mOptions;
}


void DeviceTracker::SetOptions(const MonOptions& aOptions, SetMode setmode)
{
    BOOL showSettingsChanged = FALSE;

     // setting around what items are shown
    if ((SetAll == setmode) || (SetShowOptions == setmode)) {
        if (mOptions.ShowNonConfig() != aOptions.ShowNonConfig()) {
            mInitialiseUnconfig = TRUE; // next scan should handle Unconfig as per initial scan
        }
        if (mOptions.ShowDevBoardsOrAnySerial() != aOptions.ShowDevBoardsOrAnySerial()) {
            mInitialiseMicroSer = TRUE; // next scan should handle Microchip USB serial as per initial scan

            // ensure status bar is updated
            if (aOptions.ShowDevBoardsOrAnySerial()) {
                SetStatusBarPartitions(mHWndStatusBar, 3);
                StatusBarRefresh();
            } else {
                SetStatusBarPartitions(mHWndStatusBar, 2);
            }
        }
        if (mOptions.ShowAnySerial() != aOptions.ShowAnySerial()) {
            mInitialiseAnySerial = TRUE; // next scan should handle other serial ports as per initial scan
        }

        // copy new values, and setup saving changes to the registry 
        mOptions.SetShowOptionsAndRegistrySave(aOptions, showSettingsChanged);
        // handle any change to the Arrival / Removal display time
        mOptions.SetArrivalOrRemovalTime(aOptions.GetArrivalOrRemovalTime(), TRUE);
    }

    if ((SetAll == setmode) || (SetNotifyOptions == setmode)) {
        // copy new values, and setup saving changes to the registry 
        mOptions.SetNotifyOptionsAndRegistrySave(aOptions);
    }

    if (showSettingsChanged) {
        // handle changes where currently displayed devices are no longer needed
        CleanupDevicesAfterOptionsChange();
        // kick timer for a rescan
        KickDevScanTimer();
    }
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
    DeviceInfo *item = mListDevices;

    while (item) {
        enum DevState dState = item->DeviceState();
        BOOL unlink = FALSE;

        switch (dState)
        {
        case DevAbsent:
            if (!mOptions.ShowNotPresent()) {
                unlink = TRUE;
            }
            break;

        case DevPresent:
            break;

        case DevRemoved:
            // update display with elapsed time
            if (!item->UpdateTimeInState(now, mOptions.GetArrivalOrRemovalTime())) {
                // time expired
                if (mOptions.ShowNotPresent()) {
                    item->SetDeviceAbsent();
                    UpdateViewItemState(item->StateName(), (LPARAM)item);
                } else {
                    unlink = TRUE;
                }
            } else {
                // still in DevRemoved state?
                mDevicesInArrivalState = TRUE;
            }
            break;

        case DevArrived:
            // update display with elapsed time, use default time for limit before DevPresent State
            if (!item->UpdateTimeInState(now, KArrivalOrRemovalTimeDefault)) {
                // time expired
                item->SetDevicePresent();
                UpdateViewItemState(item->StateName(), (LPARAM)item);
            } else {
                // still in DevArrived state?
                mDevicesInArrivalState = TRUE;
            }
            break;
        }

        if (unlink) {
            item = item->DeleteDevice(FALSE);
        } else {
            item = item->DeviceNext();
        }
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


 /*
   Refresh device counts for Window Status Bar
  */
void DeviceTracker::StatusBarRefresh()
{
    static wchar_t statusBuffer[1024];

    // TODO? change icon overlay in system tray?

    // also update status bar - mHWndStatusBar
    if (mHWndStatusBar) {
        // status bar could has counts for Dev boards, Bootloaders, etc
        int count = DeviceInfo::CountOfRfidlers();

        if (count) {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("%u RFIDler%s connected"), count,
                (count == 1) ? _T("") : _T("s"));
        } else {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("No RFIDlers connected"));
        }
        SendMessage(mHWndStatusBar, SB_SETTEXT, 0, (LPARAM) statusBuffer);

        count = DeviceInfo::CountOfBootloaders();
        if (count) {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("%u HID Bootloader%s connected"), count,
                (count == 1) ? _T("") : _T("s"));
        } else {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("No HID Bootloaders connected"));
        }
        SendMessage(mHWndStatusBar, SB_SETTEXT, 1, (LPARAM) statusBuffer);

        if (mOptions.ShowDevBoardsOrAnySerial()) {
            count = DeviceInfo::CountOfDevBoards();

            if (count) {
                StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("%u Dev Board%s connected"), count,
                    (count == 1) ? _T("") : _T("s"));
            } else {
                StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("No Dev Boards connected"));
            }
            SendMessage(mHWndStatusBar, SB_SETTEXT, 2, (LPARAM) statusBuffer);
        }
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


void DeviceTracker::KickDevScanTimer()
{
    if (!mTimerDevScan) {
        // wait at least 100ms, as changes often bunch together
        SetTimer (mHWndMain, mTimerDevScan = DEV_RESCAN_TIMER_MAGICNUMBER, 100, NULL);
    }
}


void DeviceTracker::CancelDevScanTimer()
{
    if (mTimerDevScan) {
        KillTimer(mHWndMain, mTimerDevScan);
        mTimerDevScan = 0;
    }
}


BOOL DeviceTracker::CheckInitialScanFlag(enum DevType dType)
{
    switch(dType)
    {
    case DevRfidlerCom:
        return mInitialiseRfidler;
    case DevMicroDevBoard:
        return mInitialiseMicroSer;
    case DevMicroBootloader:
        return mInitialiseRfidler;
    case DevOtherSerial:
        return mInitialiseAnySerial;
    case DevUnconfigRfidlerCom:
    case DevUnconfigMicroDevBoard:
    default:
        return mInitialiseUnconfig;
    }
}


//  common function for new device or changing state to DevArrived/DevPresent
void DeviceTracker::DetermineArrivalNotifications(enum DevType dType, enum DevState newState)
{
    if ((newState == DevPresent) || (newState == DevArrived)) {
        if (newState == DevArrived) {
            mDevicesInArrivalState = TRUE;
        }
        BOOL updateStatusBar = FALSE;

        switch (dType)
        {
        case DevRfidlerCom:
            updateStatusBar = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyRfidlerArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
            break;
        case DevMicroDevBoard:
            if (mOptions.ShowDevBoardsOrAnySerial()) {
                updateStatusBar = TRUE;
            }
            // notify if wanted (except if Options just changed)
            if (!mInitialiseMicroSer && mOptions.NotifyMicrochipArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
            break;
        case DevMicroBootloader:
            updateStatusBar = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyBootArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
            break;
        default:
            // future feature, arrival notifications for DevOtherSerial ?
            break;
        }

        if (updateStatusBar) {
            StatusBarRefresh();
        }
    }
}


//  common function for forgetting device or changing state to DevRemoved
void DeviceTracker::DetermineRemovalNotifications(enum DevType dType, enum DevState oldState, enum DevState newState)
{
    if (newState == DevRemoved) {
        mDevicesInArrivalState = TRUE;
    }

    if (((oldState == DevPresent) || (oldState == DevArrived)) &&
                (newState != DevPresent) && (newState != DevArrived)) {
        BOOL updateStatusBar = FALSE;

        switch (dType)
        {
        case DevRfidlerCom:
            updateStatusBar = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyRfidlerArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
            break;
        case DevMicroDevBoard:
            if (mOptions.ShowDevBoardsOrAnySerial()) {
                updateStatusBar = TRUE;
            }
            // notify if wanted (except if Options just changed)
            if (!mInitialiseMicroSer && mOptions.NotifyMicrochipArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
            break;
        case DevMicroBootloader:
            updateStatusBar = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyBootArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
            break;
        default:
            // future feature, removal notifications for DevotherSerial?
            break;
        }

        if (updateStatusBar) {
            StatusBarRefresh();
        }
    }
}


/* end of file devicetracker.cpp */