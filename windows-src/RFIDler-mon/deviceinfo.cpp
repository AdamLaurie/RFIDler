/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: deviceinfo.cpp

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

#include <assert.h>
#include <strsafe.h>


DeviceTracker *DeviceInfo::gdevTracker;
// Configured & listed RFIDlers
int DeviceInfo::iCountRfidlers = 0;
// Microchip USB serial if enabled
int DeviceInfo::iCountDevBoards = 0;
// Configured & listed Bootloaders
int DeviceInfo::iCountBootloaders = 0;
// Unconfigured & listed RFIDlers, plus Microchip USB serial if enabled
int DeviceInfo::iCountUnconRfidlers = 0;
int DeviceInfo::iCountUnconDevBoards = 0;
// count of other serial devices
int DeviceInfo::iCountOtherSerial = 0;





// init class static data
void DeviceInfo::SetDeviceTracker(DeviceTracker *devTracker)
{
    gdevTracker = devTracker;
}


// new DeviceInfo object, transfers ownership of strings, 
DeviceInfo *DeviceInfo::NewDevice(enum DevType aDevType, 
    enum DevState aDevState, FILETIME aNow, wchar_t *aSerialnumber, wchar_t *aPortName,
    wchar_t *aFriendlyName, wchar_t *aHardwareId, int aPortNumber, wchar_t *aContainerId,
    unsigned aUsbHub, unsigned aUsbPort, BOOL aUsbValid, unsigned aScanId, DeviceInfo *aDevNext,
    BOOL aIsWinSerial, SerialType aSerialType)
{
    DeviceInfo *newDev = NULL;

    // decide if new device should be DevArrived rather than DevPresent
    if ((aDevState == DevPresent) && !gdevTracker->CheckInitialScanFlag(aDevType)) {
        aDevState = DevArrived;
    }

    newDev = new DeviceInfo(aDevType, aDevState, aNow, aSerialnumber, aPortName,
        aPortNumber, aContainerId, aFriendlyName, aHardwareId,
        aUsbHub, aUsbPort, aUsbValid, aScanId, aDevNext,
        aIsWinSerial, aSerialType);

    if (newDev) {
        TCHAR   buffer[20];

        // update double linked list
        if (aDevNext) {
            aDevNext->devPrev = newDev;
        }
        gdevTracker->SetPortList(newDev);

        StringCbPrintf(buffer, sizeof(buffer), 
            (newDev->DeviceState() == DevArrived) ? _T("%s 0min") : _T("%s"), newDev->StateName());

        // display update shouldn't fail, but check anyway
        if (!gdevTracker->AddViewItem(newDev->DisplayName(), newDev->devImage,
                newDev->DevTypeName(), buffer, newDev->LocationString(), aSerialnumber,
                (LPARAM)newDev)) {
            newDev->Destroy();
            newDev = NULL;
        } else {
            if ((aDevState == DevArrived) || (aDevState == DevPresent)) {
                // update count
                newDev->IncDeviceTypeCount();
            }

            // update DeviceTracker counts, decide on notifications 
            gdevTracker->DetermineArrivalNotifications(aDevType, aDevState);
        }
    }

    return newDev;
}


void DeviceInfo::DecDeviceTypeCount()
{
    devPresent = FALSE;
    UpdateDeviceTypeCount(-1);
}


void DeviceInfo::UpdateDeviceTypeCount(int delta)
{
    switch (devType) {
    case DevRfidlerCom:
        iCountRfidlers += delta;
        break;
    case DevMicroDevBoard:
        iCountDevBoards += delta;
        break;
    case DevMicroBootloader:
        iCountBootloaders += delta;
        break;
    case DevUnconfigRfidlerCom:
        iCountUnconRfidlers += delta;
        break;
    case DevUnconfigMicroDevBoard:
        iCountUnconDevBoards += delta;
        break;
    case DevOtherSerial:
        iCountOtherSerial += delta;
        break;
    default:
        break;
    }
}


void DeviceInfo::IncDeviceTypeCount()
{
    devPresent = TRUE;
    UpdateDeviceTypeCount(1);
}


DeviceInfo *DeviceInfo::DeleteDevice()
{
    DeviceInfo *next = devNext;

    if (devPresent) {
        // update count
        DecDeviceTypeCount();
    }

    // update DeviceTracker counts, decide on notifications
    gdevTracker->DetermineRemovalNotifications(devType, devState, DevNotConnected);

    // remove device from display
    gdevTracker->RemoveViewItem((LPARAM)this);

    // delete device object, or if locked mark it for delete
    Destroy();

    return next;
}


void DeviceInfo::LockForContextMenu()
{
    // LockForContextMenu()
    devLocked = TRUE;
}


void DeviceInfo::UnlockForContextMenu()
{
    // UnlockForContextMenu()
    devLocked = FALSE;
    if (devDeleteOnUnlock) {
        Destroy();
    }
}


void DeviceInfo::Destroy()
{
    if (devLocked) {
        devDeleteOnUnlock = TRUE;
    } else {
        // release all strings here
        ReleaseString(devSerialNumber);
        ReleaseString(devPortName);
        ReleaseString(devContainerId);
        ReleaseString(devFriendlyName);
        ReleaseString(devHardwareId);
        ReleaseString(devDevicePath);

        // unlink
        if (devNext) {
            devNext->devPrev = devPrev;
        }
        if (devPrev) {
            devPrev->devNext = devNext;
        } else {
            gdevTracker->SetPortList(devNext);
        }

        delete this;
    }
}


void DeviceInfo::SetDeviceIcon()
{
    switch(devType)
    {
    case DevRfidlerCom:
        if ((devState == DevPresent) || (devState == DevArrived)) {
            devImage = DevImgRfidlerOk;
        } else {
            devImage = DevImgRfidlerRemoved;
        }
        break;
    case DevMicroDevBoard:
        if ((devState == DevPresent) || (devState == DevArrived)) {
            devImage = DevImgDevBoardOk;
        } else {
            devImage = DevImgDevBoardRemoved;
        }
        break;
    case DevMicroBootloader:
        if ((devState == DevPresent) || (devState == DevArrived)) {
            devImage = DevImgRfidlerBoot;
        } else {
            devImage = DevImgRfidlerRemoved;
        }
        break;
    case DevOtherSerial:
        if ((devState == DevPresent) || (devState == DevArrived)) {
            devImage = DevImgOtherSerialOk;
        } else {
            devImage = DevImgOtherSerialRemoved;
        }
        break;
    case DevUnconfigRfidlerCom:
        devImage = DevImgRfidlerUnconfig;
        break;
    case DevUnconfigMicroDevBoard:
    default:
        devImage = DevImgDevBoardUnconfig;
        break;
    }
}


const TCHAR *DeviceInfo::StateName()
{
    switch (devState)
    {
    case DevAbsent:
        return _T("Absent");
    case DevPresent:
        return _T("Present");
    case DevArrived: 
        return _T("Arrived");
    case DevRemoved:
        return _T("Removed");
    case DevNotConnected:
    default:
        assert(0);
        return NULL;
    }
}


const TCHAR *DeviceInfo::DevTypeName()
{
    switch (devType)
    {
    case DevRfidlerCom:
    case DevUnconfigRfidlerCom:
        return _T("RFIDler");
    case DevMicroDevBoard:
    case DevUnconfigMicroDevBoard:
        return _T("dev board");
    case DevOtherSerial:
        return _T("serial");
    case DevMicroBootloader:
        return _T("Bootloader");
    default:
        assert(0);
        return NULL;
    }
}


const TCHAR *DeviceInfo::LocationString()
{
    static TCHAR   locus[30];

    if (devUsbValid) {
        ZeroMemory(locus, sizeof(locus));
        StringCbPrintf(locus, sizeof(locus), _T("USB hub %i port %i"), devUsbHub, devUsbPort);
        return locus;
    }
    return NULL;
}


const TCHAR *DeviceInfo::DisplayName()
{
    switch (devType)
    {
    case DevRfidlerCom:
    case DevMicroDevBoard:
    case DevOtherSerial:
        return devPortName;
    case DevMicroBootloader:
        return _T("HID bootloader");
    case DevUnconfigRfidlerCom:
    case DevUnconfigMicroDevBoard:
        return _T("Unconfigured");
    default:
        assert(0);
        return NULL;
    }
}


// compose details about device into infotip/tooltip
const TCHAR *DeviceInfo::InfoTip()
{
    static TCHAR   infotipBuffer[1024];
    TCHAR *desc = NULL;

    infotipBuffer[0] = 0;

    switch (devType)
    {
    case DevRfidlerCom:
        desc = _T("RFIDler COM port");
        break;
    case DevMicroDevBoard:
        desc = _T("Microchip USB COM port\nDevelopment board");
        break;
    case DevMicroBootloader:
        desc = _T("Microchip HID bootloader\nRFIDler or other development board");
        break;
    case DevUnconfigRfidlerCom:
        desc = _T("RFIDler COM port, driver not installed");
        break;
    case DevUnconfigMicroDevBoard:
        desc = _T("Microchip USB COM port, driver not installed");
        break;
    case DevOtherSerial:
        desc = devFriendlyName;
        break;
    default:
        assert(0);
    }

    if (desc) {
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc);
    }

    // describe serial port type, based on Windows GUID for ports, modem or multiport serial card
    if (devSerialType != SerialNone) {
        desc = NULL;
        if (devSerialType == SerialPort) {
            desc = _T("\nSerial Port");
        } else if (devSerialType == SerialModem) {
            desc = _T("\nModem");
        } else if (devSerialType == SerialMultiport) {
            desc = _T("\nMultiport Serial Device");
        }
        if (desc) {
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc);
        }
    }

    if (devHardwareId) {
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nHardwareId = "));
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), devHardwareId);
    }

    if (devSerialNumber) {
        if (devIsWinSerial) {
            desc = _T("\nWindows generated serial number");
        } else {
            desc = _T("\nBuilt-in device serial number");
        }
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc);
    }

    return infotipBuffer;
}


// (class static) callback function given to ListView_SortItems
// negative result if dev1 precedes dev2, positive for dev2 ahead of dev1
int CALLBACK DeviceInfo::CompareProc(DeviceInfo *dev1, DeviceInfo *dev2, LPARAM primaryKey)
{
    int result = 0;
    int reverse = (primaryKey >= lvRevDispName);

    // default ordering on first run or if state save disabled: port name/number
    switch (primaryKey) {
    case lvDispName: 
    case lvRevDispName:
        if (dev1->devPortName) {
            if (!dev2 ->devPortName) {
                result = -1;
            } else {
                result = dev1->devPortNumber - dev2->devPortNumber;
            }
        } else {
            if (dev2 ->devPortName) {
                result = 1;
            }
        }
        if (result == 0) {
            result = (int)dev1->devType - (int)dev2->devType;
        }
        break;

    case lvDispType: // device type
    case lvRevDispType:
        result = (int)dev1->devType - (int)dev2->devType;
        break;

    case lvDispState: // device state
    case lvRevDispState:
        result = (int)dev1->devState - (int)dev2->devState;
        break;

    case lvDispLocus: // USB location
    case lvRevDispLocus:
        if (dev1->devUsbValid) {
            if (dev2->devUsbValid) {
                result = dev1->devUsbHub - dev2->devUsbHub;
                if (result == 0) {
                    result = dev1->devUsbPort - dev2->devUsbPort;
                }
            } else {
                result = -1;
            }
        } else {
            if (dev2->devUsbValid) {
                result = 1;
            }
        }
        break;

    case lvDispSernum: // serialnumber
    case lvRevDispSernum:
    default:
        if (dev1->devSerialNumber) {
            if (dev2->devSerialNumber) {
                result = wcscmp(dev1->devSerialNumber, dev2->devSerialNumber);
            } else {
                result = -1;
            }
        } else {
            if (dev2->devSerialNumber) {
                result = 1;
            }
        }
        break;
    }

    if (reverse && (result != 0)) {
        result = -result;
    }

    return result;
}


void DeviceInfo::UpdateDeviceState(enum DevState aDevState, FILETIME aNow, unsigned aScanId)
{
    // check for change of state, eg removed etc...
    if (devState != aDevState) {
        BOOL chgState = FALSE;

        if (aDevState == DevAbsent) {
            if ((devState == DevPresent) || (devState == DevArrived)) {
#ifdef _DEBUG
                PrintDebugStatus(_T("Change state to removed\n"));
#endif
                // update DeviceTracker counts, decide on notifications
                gdevTracker->DetermineRemovalNotifications(devType, devState, DevRemoved);

                devState = DevRemoved;
                devElapsed = 0;
                devTimestamp = aNow;
                chgState = TRUE;
                // update counts
                DecDeviceTypeCount();
            }
        } else if (aDevState == DevPresent) {
            if ((devState == DevAbsent) || (devState == DevRemoved)) {
#ifdef _DEBUG
                PrintDebugStatus(_T("Change state to arrived\n"));
#endif
                devDeleteOnUnlock = FALSE; // device has returned, no longer need to delete

                // update DeviceTracker counts, decide on notifications 
                gdevTracker->DetermineArrivalNotifications(devType, aDevState);

                devState = gdevTracker->CheckInitialScanFlag(devType) ? DevPresent : DevArrived;
                devTimestamp = aNow;
                devElapsed = 0;
                chgState = TRUE;
                // update counts
                IncDeviceTypeCount();
            }
        }

        if (chgState) {
            TCHAR   buffer[20];

            StringCbPrintf(buffer, sizeof(buffer), _T("%s 0min"), StateName());
            SetDeviceIcon();

            // update port status & icon on display
            gdevTracker->UpdateViewItemIconAndState(devImage, buffer, (LPARAM)this);
        }
    }

    devScanId = aScanId;
}


void DeviceInfo::UpdateDevice(enum DevType aDevType, enum DevState aDevState,
        FILETIME aNow, wchar_t *aPortName, int aPortNumber, unsigned aUsbHub, unsigned aUsbPort, BOOL aUsbValid,
        wchar_t *aSerialNumber, unsigned aScanId, BOOL aIsWinSerial)
{
    // change of device type happens when installing/removing device drivers
    if (devType != aDevType) {
        BOOL nameChanged = FALSE;

#ifdef _DEBUG
        PrintDebugStatus(_T("DevType changed (%u -> %u)\n"), devType, aDevType);
#endif

        if (devPresent) {
            // update counts
            DecDeviceTypeCount();
            devType = aDevType;
            IncDeviceTypeCount();
        } else {
            devType = aDevType;
        }

        // update DeviceTracker counts, decide on notifications 
        gdevTracker->DetermineRemovalNotifications(devType, devState, DevRemoved);
        gdevTracker->DetermineArrivalNotifications(aDevType, devState);

        // rely on FindDevMatchBySernum() to enforce type change restrictions
        SetDeviceIcon();

        // update port status & icon on display
        gdevTracker->UpdateViewItemIconAndType(devImage, DevTypeName(), (LPARAM)this);

        // installing driver can add/change name
        if ((aPortName) && (!devPortName || wcscmp(devPortName, aPortName))) {
#ifdef _DEBUG
            PrintDebugStatus(_T("Adding PortName (%s)\n"), aPortName);
#endif
            ReleaseString(devPortName);

            devPortName = _wcsdup(aPortName);
            if (devPortName) {
                devPortNumber = aPortNumber;
                nameChanged = TRUE;
            }
        } else if (devPortName && !aPortName) {
#ifdef _DEBUG
            PrintDebugStatus(_T("Release portname (%s)\n"), devPortName);
#endif
            // driver uninstalled, portname removed
            ReleaseString(devPortName);
            nameChanged = TRUE;
        }

        if (nameChanged) {
            gdevTracker->UpdateViewItemPortName(DisplayName(), (LPARAM)this);
        }
    }

    // check for change of state, eg removed etc...
    UpdateDeviceState(aDevState, aNow, aScanId);


    if ((devState == DevArrived) || (devState == DevPresent)) {
        // portname has changed? eg by user in Device Manager
        if ((aPortName) && (!devPortName || wcscmp(devPortName, aPortName))) {
            ReleaseString(devPortName);

            devPortName = _wcsdup(aPortName);
            if (devPortName) {
                devPortNumber = aPortNumber;
                // NB should reorder devices to reflect updated portname
                gdevTracker->UpdateViewItemPortName(devPortName, (LPARAM)this);
            }
        }
    }

    if (aUsbValid) {
        if ((devUsbValid != aUsbValid) || (devUsbHub != aUsbHub) || (devUsbPort != aUsbPort)) {
            devUsbValid = aUsbValid;
            devUsbHub = aUsbHub;
            devUsbPort = aUsbPort;
            // update displayed usb location
            gdevTracker->UpdateViewItemLocation(LocationString(), (LPARAM)this);
        }
    }

    if (!devSerialNumber && aSerialNumber) {
        devSerialNumber = _wcsdup(aSerialNumber);
        if (devSerialNumber) {
            devIsWinSerial = aIsWinSerial;
            // NB should reorder devices to reflect updated serial number
            gdevTracker->UpdateViewItemSerialNumber(devSerialNumber, (LPARAM)this);
        }
    }

    devScanId = aScanId;
}


// update time, returns TRUE device is still valid FALSE if no longer visible
BOOL DeviceInfo::UpdateTimeInState(FILETIME now, BOOL showNotPresent, DWORD limit)
{
    ULARGE_INTEGER t1, t2;

    t1.LowPart = devTimestamp.dwLowDateTime;
    t1.HighPart = devTimestamp.dwHighDateTime;
    t2.LowPart = now.dwLowDateTime;
    t2.HighPart = now.dwHighDateTime;

    t2.QuadPart -= t1.QuadPart;
    t2.QuadPart /= 600000000l; // minutes

    if (t2.LowPart <= limit) {
        if (devElapsed != t2.LowPart) {
            TCHAR   buffer[20];

            devElapsed = t2.LowPart;
            StringCbPrintf(buffer, sizeof(buffer), _T("%s %imin"), StateName(), t2.LowPart);
            gdevTracker->UpdateViewItemState(buffer, (LPARAM)this);
        }
        return TRUE;
    } else {
        // > 10s elapsed
        if (devState == DevArrived) {
            devState = DevPresent;
        } else {
            assert(devState == DevRemoved);
            devState = DevAbsent;
            if (!showNotPresent) {
                // device should no longer be listed
                return FALSE;
            }
        }
        gdevTracker->UpdateViewItemState(StateName(), (LPARAM)this);
        return TRUE;
    }
}


wchar_t const *DeviceInfo::DevicePath()
{
    if (!devDevicePath) {
        // GUID_DEVINTERFACE_HID
        GUID HidGuid = { 0x4D1E55B2L, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 };

        HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&HidGuid, 0, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

        if (DeviceInfoSet != INVALID_HANDLE_VALUE) {
            BOOL foundPath = FALSE;
            SP_DEVICE_INTERFACE_DATA deviceInterface;
            DWORD dIndex = 0;

            ZeroMemory(&deviceInterface, sizeof(SP_DEVICE_INTERFACE_DATA));
            deviceInterface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

            while (SetupDiEnumDeviceInterfaces(DeviceInfoSet, 0, &HidGuid, dIndex, &deviceInterface) && !foundPath) {
                SP_DEVICE_INTERFACE_DETAIL_DATA *devDetails = NULL;
                DWORD size;

                dIndex++;
        
                SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &deviceInterface, NULL, 0, &size, NULL);
                devDetails = (SP_DEVICE_INTERFACE_DETAIL_DATA *) calloc(size, 1);
                devDetails->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
                if (SetupDiGetDeviceInterfaceDetail(DeviceInfoSet, &deviceInterface, devDetails, size, &size, NULL)) {
                    // wcsstr variant that ignores case
                    const wchar_t *match = wcs_istr(devDetails->DevicePath, devSerialNumber);
                    if (match) {
                        devDevicePath = wcs_dupsubstr(devDetails->DevicePath, size); // todo size - 4?
                        foundPath = TRUE;
                    }

#ifdef _DEBUG
                    PrintDebugStatus(_T("HID DevicePath = \"%s\", serialnum = \"%s\", foundPath %i\n"),
                        devDetails->DevicePath, devSerialNumber, foundPath);
#endif
                }
                free(devDetails);
            } // while
        
            SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        }
    }

    return devDevicePath;
}


/* end of file deviceinfo.cpp */