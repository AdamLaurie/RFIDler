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




// new DeviceInfo object, transfers ownership of strings
BOOL DeviceInfo::AddDeviceToList(enum DevType aDevType, enum DevState aDevState, FILETIME aNow,
    DevicePortDetails& aPortDetails, DeviceLocation& aLocation, DeviceSerialNumber& aSerialNumber, unsigned aScanId,
    SerialPortType aPortType)
{
    DeviceInfo *devNext = DeviceTracker::GetPortList();
    DeviceInfo *newDev = NULL;

    // decide if new device should be DevArrived rather than DevPresent
    if ((aDevState == DevPresent) && !DevTracker.CheckInitialScanFlag(aDevType)) {
        aDevState = DevArrived;
    }

    newDev = new DeviceInfo(aDevType, aDevState, aNow, aPortDetails, aLocation, aSerialNumber, aScanId, devNext, aPortType);

    if (newDev) {
        wchar_t buffer[20];

        // update double linked list
        if (devNext) {
            devNext->devPrev = newDev;
        }
        DeviceTracker::SetPortList(newDev);

        StringCbPrintf(buffer, sizeof(buffer), 
            (newDev->DeviceState() == DevArrived) ? _T("%s 0 min") : _T("%s"), newDev->StateName());

        // display update shouldn't fail, but check anyway
        if (!DevTracker.AddViewItem(newDev->DisplayName(), newDev->devImage,
                newDev->DevTypeName(), buffer, newDev->LocationString(), aSerialNumber.devSerialString,
                (LPARAM)newDev)) {
            newDev->Destroy();
            newDev = NULL;
        } else {
            if ((aDevState == DevArrived) || (aDevState == DevPresent)) {
                // update count
                newDev->IncDeviceTypeCount();
            }

            // update DeviceTracker counts, decide on notifications 
            DevTracker.DetermineArrivalNotifications(aDevType, aDevState);
        }
    }

    return newDev ? TRUE : FALSE;
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


DeviceInfo *DeviceInfo::DeleteDevice(BOOL skipNotifications)
{
    DeviceInfo *next = devNext;

    if (devPresent) {
        // update count
        DecDeviceTypeCount();
    }

    // update DeviceTracker counts, decide on notifications
    if (!skipNotifications) {
        DevTracker.DetermineRemovalNotifications(devType, devState, DevNotConnected);
    }

    // remove device from display
    DevTracker.RemoveViewItem((LPARAM)this);

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
        ReleaseString(devSerialNumber.devSerialString);
        ReleaseString(devPortDetails.devPortName);
        ReleaseString(devPortDetails.devFriendlyName);
        ReleaseString(devSerialNumber.devHardwareId);
        ReleaseString(devDevicePath);

        // unlink
        if (devNext) {
            devNext->devPrev = devPrev;
        }
        if (devPrev) {
            devPrev->devNext = devNext;
        } else {
            DeviceTracker::SetPortList(devNext);
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


const wchar_t *DeviceInfo::StateName()
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


const wchar_t *DeviceInfo::DevTypeName()
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
        // distinguish modems & serial ports
        switch (devPortType)
        {
        case SerialModem:
            return _T("modem");
        case SerialMultiport:
            return _T("multiport");
        default:
            return _T("serial");
        }
    case DevMicroBootloader:
        return _T("Bootloader");
    default:
        assert(0);
        return NULL;
    }
}


const wchar_t *DeviceInfo::LocationString()
{
    static wchar_t  locus[30];

    switch (devLocation.devBusType)
    {
    case BusUSB:
        ZeroMemory(locus, sizeof(locus));
        StringCbPrintf(locus, sizeof(locus), _T("USB hub %i port %i"), devLocation.devUsbHub, devLocation.devUsbPort);
        return locus;

    case BusBluetooth:
        return _T("Bluetooth");

    case BusPCI:
        return _T("PCI bus");

    case BusPCMCIA:
        return _T("PCMCIA bus");

    case BusISAPNP:
        return _T("ISA PNP");

    case BusEISA:
        return _T("EISA bus");

    case BusMCA:
        return _T("MCA bus");

    case BusFirewire:
        return _T("Firewire");

    case BusSD:
        return _T("SD card");

    default:
        return NULL;
    }
}


const wchar_t *DeviceInfo::DisplayName()
{
    switch (devType)
    {
    case DevRfidlerCom:
    case DevMicroDevBoard:
    case DevOtherSerial:
        return devPortDetails.devPortName;
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
const wchar_t *DeviceInfo::InfoTip()
{
    static wchar_t  infotipBuffer[1024];
    wchar_t *desc = NULL;

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
        desc = devPortDetails.devFriendlyName;
        break;
    default:
        assert(0);
    }

    if (desc) {
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc);
    }

    // describe serial port type, based on Windows GUID for ports, modem or multiport serial card
    desc = NULL;
    switch (devPortType)
    {
    case SerialPort:
        desc = _T("\nSerial Port");
        break;
    case SerialModem:
        desc = _T("\nModem");
        break;
    case SerialMultiport:
        desc = _T("\nMultiport Serial Device");
        break;
    }
    if (desc) {
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc);
    }

    if (devSerialNumber.devHardwareId) {
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nHardwareId = "));
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), devSerialNumber.devHardwareId);
    }

    if (devSerialNumber.devSerialString) {
        if (devSerialNumber.devIsWinSerial) {
            desc = _T("\nWindows generated serial number");
        } else {
            desc = _T("\nSerial number from device");
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
        if (dev1->devPortDetails.devPortName) {
            if (!dev2 ->devPortDetails.devPortName) {
                result = -1;
            } else {
                result = dev1->devPortDetails.devPortNumber - dev2->devPortDetails.devPortNumber;
            }
        } else {
            if (dev2 ->devPortDetails.devPortName) {
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
        if (dev1->devLocation.devBusType == BusUSB) {
            if (dev2->devLocation.devBusType == BusUSB) {
                result = dev1->devLocation.devUsbHub - dev2->devLocation.devUsbHub;
                if (result == 0) {
                    result = dev1->devLocation.devUsbPort - dev2->devLocation.devUsbPort;
                }
            } else {
                result = -1;
            }
        } else {
            // arbitrary order for bus types
            result = (int)dev2->devLocation.devBusType;
            result -= (int)dev1->devLocation.devBusType;
        }
        break;

    case lvDispSernum: // serialnumber
    case lvRevDispSernum:
    default:
        if (dev1->devSerialNumber.devSerialString) {
            if (dev2->devSerialNumber.devSerialString) {
                result = wcscmp(dev1->devSerialNumber.devSerialString, dev2->devSerialNumber.devSerialString);
            } else {
                result = -1;
            }
        } else {
            if (dev2->devSerialNumber.devSerialString) {
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


void DeviceInfo::SetDeviceAbsent()
{
    assert(devState == DevRemoved);
    devState = DevAbsent;
}


void DeviceInfo::SetDevicePresent()
{
    assert(devState == DevArrived);
    devState = DevPresent;
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
                DevTracker.DetermineRemovalNotifications(devType, devState, DevRemoved);

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
                DevTracker.DetermineArrivalNotifications(devType, aDevState);

                devState = DevTracker.CheckInitialScanFlag(devType) ? DevPresent : DevArrived;
                devTimestamp = aNow;
                devElapsed = 0;
                chgState = TRUE;
                // update counts
                IncDeviceTypeCount();
            }
        }

        if (chgState) {
            wchar_t buffer[20];

            StringCbPrintf(buffer, sizeof(buffer), _T("%s 0min"), StateName());
            SetDeviceIcon();

            // update port status & icon on display
            DevTracker.UpdateViewItemIconAndState(devImage, buffer, (LPARAM)this);
        }
    }

    devScanId = aScanId;
}


void DeviceInfo::UpdateDevice(enum DevType aDevType, enum DevState aDevState,
        FILETIME aNow, DevicePortDetails& aPortDetails, DeviceLocation& aLocation,
        DeviceSerialNumber& aSerialNumber, unsigned aScanId)
{
    // change of device type happens when installing/removing device drivers
    if (devType != aDevType) {
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
        DevTracker.DetermineRemovalNotifications(devType, devState, DevRemoved);
        DevTracker.DetermineArrivalNotifications(aDevType, devState);

        // rely on FindDevMatchBySernum() to enforce type change restrictions
        SetDeviceIcon();

        // update port status & icon on display
        DevTracker.UpdateViewItemIconAndType(devImage, DevTypeName(), (LPARAM)this);

        // installing driver can add/change name
        if ((devPortDetails.devPortName && !aPortDetails.devPortName) || 
                ((aPortDetails.devPortName) && (!devPortDetails.devPortName || wcscmp(devPortDetails.devPortName, aPortDetails.devPortName)))) {
#ifdef _DEBUG
            PrintDebugStatus(_T("Changing PortName (%s)\n"), aPortDetails.devPortName ? aPortDetails.devPortName : devPortDetails.devPortName);
#endif
            // swap new & old port details (simplifies memory management this way)
            DevicePortDetails temp(devPortDetails);
            devPortDetails = aPortDetails;
            aPortDetails = temp;

            DevTracker.UpdateViewItemPortName(DisplayName(), (LPARAM)this);
        }
    }

    // check for change of state, eg removed etc...
    UpdateDeviceState(aDevState, aNow, aScanId);


    if ((devState == DevArrived) || (devState == DevPresent)) {
        // portname has changed? eg by user in Device Manager
        if ((aPortDetails.devPortName) && (!devPortDetails.devPortName || wcscmp(devPortDetails.devPortName, aPortDetails.devPortName))) {
            // swap new & old port details (simplifies memory management this way)
            DevicePortDetails temp(devPortDetails);
            devPortDetails = aPortDetails;
            aPortDetails = temp;

            DevTracker.UpdateViewItemPortName(DisplayName(), (LPARAM)this);
        }
    }

    if ((devLocation.devBusType != aLocation.devBusType) || (devLocation.devUsbHub != aLocation.devUsbHub) || (devLocation.devUsbPort != aLocation.devUsbPort)) {
        devLocation = aLocation;
        // update displayed bus, usb hub/port location
        DevTracker.UpdateViewItemLocation(LocationString(), (LPARAM)this);
    }

    // TODO is this required?
    if (!devSerialNumber.devSerialString && aSerialNumber.devSerialString) {
        DeviceSerialNumber temp(devSerialNumber);
        devSerialNumber = aSerialNumber;
        aSerialNumber = temp;

        // NB should reorder devices to reflect updated serial number
        DevTracker.UpdateViewItemSerialNumber(devSerialNumber.devSerialString, (LPARAM)this);
    }

    devScanId = aScanId;
}


// update time, returns TRUE device is still valid FALSE if no longer visible
BOOL DeviceInfo::UpdateTimeInState(FILETIME now, DWORD limit)
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
            wchar_t buffer[20];

            devElapsed = t2.LowPart;
            StringCbPrintf(buffer, sizeof(buffer), _T("%s %i min"), StateName(), t2.LowPart);
            DevTracker.UpdateViewItemState(buffer, (LPARAM)this);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}


// DevicePath is used to open HID devices
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
                    const wchar_t *match = wcs_istr(devDetails->DevicePath, devSerialNumber.devSerialString);
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