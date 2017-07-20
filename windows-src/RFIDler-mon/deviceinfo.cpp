/* 

    Project: RFIDler Monitor v0.2
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: deviceinfo.cpp

    Author: Anthony Naggs, 2014, 2017

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


// static members of DeviceInfo
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
int DeviceInfo::iCountOtherBootloader = 0;


DeviceInfo *DeviceInfo::mListDevices = NULL;



// known Arduino variants, some info comes from boards.txt at http://code.google.com/p/arduino/wiki/Platforms
USBdevName ArduinoDeviceList[] = {
    // VID = 0x2341 => Arduino LLC, arduino.cc, Arduino in the USA, Genuino elsewhere
    { 0x2341, 0x0001, 0, L"Arduino Uno" }, // also PID 0x0043 ?
    { 0x2341, 0x0010, 0, L"Arduino Mega" }, // or Mega 2560, also PID 0x0042 ?

    { 0x2341, 0x0036, 0, L"Arduino Leonardo" },
    { 0x2341, 0x0037, 0, L"Arduino Micro" },
    { 0x2341, 0x0038, 0, L"Robot Control" },
    { 0x2341, 0x0039, 0, L"Robot Motor" },

    { 0x2341, 0x003C, 0, L"Arduino Esplora" },

    { 0x2341, 0x003f, 0x0044, L"Arduino Mega ADK" }, // also PID 0x0044 ?
    { 0x2341, 0x0c9f, 0, L"Arduino Gemma" },

    // VID = 0x2A03 => "dog hunter AG" => Arduino SRL (formerly Smart Projects SRL an Arduino board manufacturer), arduino.org
    { 0x2A03, 0x0041, 0, L"Arduino Yun" },
    { 0x2A03, 0x0043, 0, L"Arduino Uno" },

    // VIDs where we do not know the manufacturer name
    { 0x1f3a, 0xefe8, 0, L"pcDuino" },

    // VID = SparkFun Electronics
    { 0x1b4f, 0x9205, 0, L"Pro Micro 5V" },
    { 0x1b4f, 0x9203, 0, L"Pro Micro 3.3V" },
    { 0x1b4f, 0xF100, 0, L"Fio v3" },
    { 0x1B4F, 0x9207, 0x9208, L"LilyPad USB" },
    { 0x1B4F, 0x9209, 0, L"WiFlyin'" },
    { 0x1b4f, 0x514d, 0, L"Qtechknow Qduino Mini" }, // QM
    { 0x1B4F, 0x2B74, 0, L"MaKey MaKey" },

    // Seeedstudio
    { 0x2886, 0x8003, 0, L"Seeeduino Xadow" },

    // obvious device names with OpenMoko VendorID, http://wiki.openmoko.org/wiki/USB_Product_IDs
    { 0x1d50, 0x6004, 0, L"LeoLipo" }, // Arduino Leonardo clone with LiPo charger, 0x6011 for Bootloader?
    { 0x1d50, 0x6077, 0, L"PaintDuino" },
    { 0x1d50, 0x607d, 0, L"Spark Core WiFi Arduino" }, // 0x607f for Bootloader?
    { 0x1d50, 0x608a, 0, L"BLEduino" },
};


const unsigned KArduinoDeviceCount = sizeof(ArduinoDeviceList) /  sizeof(ArduinoDeviceList[0]);


// new DeviceInfo object, transfers ownership of strings
BOOL DeviceInfo::AddDeviceToList(enum DevType aDevType, BOOL aDevPresent, FILETIME aNow,
    SerialPortDetails& aPortDetails, DeviceLocation& aLocation, DeviceSerialNumber& aSerialNumber, unsigned aScanId,
    SerialPortType aPortType, wchar_t *manufacturer, wchar_t *hardwareId, wchar_t *driverName, wchar_t *infPath)
{
    DeviceInfo *newDev = NULL;
    struct USBdevName *nameTypeInfo = NULL;
    enum DevState newDevState;
    
    if (aDevPresent) {
        // decide if new device should be DevArrived rather than DevPresent
        newDevState = DevTracker.CheckInitialScanFlag(aDevType) ? DevPresent : DevArrived;
    } else {
        newDevState = DevAbsent;
    }

    // identify if a known Arduino / Genuino type
    if ((BusUSB == aLocation.devBusType) && (aDevType == DevOtherSerial) && (0 != aLocation.usbPID)) {
        unsigned u;

        for (u = 0; u < KArduinoDeviceCount; u++) {
            if ((aLocation.usbVID == ArduinoDeviceList[u].vid) && 
                    ((aLocation.usbPID == ArduinoDeviceList[u].pid1) || (aLocation.usbPID == ArduinoDeviceList[u].pid2))) {
                aDevType = DevArduinoSerial;
                nameTypeInfo = &ArduinoDeviceList[u];
            }
        }
    }

    newDev = new DeviceInfo(aDevType, newDevState, aNow, aPortDetails, aLocation, aSerialNumber, aScanId, aPortType, nameTypeInfo,
        manufacturer, hardwareId, driverName, infPath);

    if (newDev) {
        wchar_t buffer[20];

        StringCbPrintf(buffer, sizeof(buffer), 
            (newDevState == DevArrived) ? L"%s 0min" : L"%s", newDev->StateName());

        // display update shouldn't fail, but check anyway
        if (!DevTracker.AddViewItem(newDev->DisplayName(), newDev->devImage,
                newDev->DevTypeName(), buffer, newDev->LocationString(), aSerialNumber.devSerialString,
                newDev->ArrivalTimeString(),
                (LPARAM)newDev)) {
            newDev->Destroy();
            newDev = NULL;
        } else if (aDevPresent) {
            // update DeviceTracker counts, decide on notifications 
            DevTracker.DetermineArrivalNotifications(aDevType, newDevState);
        }
        return TRUE;
    }

    return FALSE;
}


DeviceLocation DeviceInfo::DevLocation()
{
    // try to determine USB product revision, if not known already
    if ((BusUSB == devLocation.devBusType) && !devLocation.usbGotRevision && (NULL != devHardwareId)) {
        const wchar_t *KStringRev = L"&REV_";
        const size_t  KStringLength = wcslen(KStringRev);

        // loop with _wcsnicmp() case insensitive version of wcsstr()
        for (unsigned i = 0; devHardwareId[i]; i++) {
            if (!_wcsnicmp(devHardwareId + i, KStringRev, KStringLength)) {
                unsigned long temp = wcstoul(devHardwareId + i + KStringLength, NULL, 16);
                devLocation.usbRevision = (unsigned) temp;
                devLocation.usbGotRevision = TRUE;
                break;
            }
        }

        if (devLocation.usbGotRevision) {
            CheckForUsbFlags();
        }
    }

    return devLocation;
}


enum DevCategory DeviceInfo::DeviceCategoryBasic(enum DevType aDevType)
{
    switch (aDevType)
    {
    case DevRfidlerCom:
        return DevCatRfidler; // RFIDler

    case DevMicroBootloader:
    case DevHalfKayBootloader:
        return DevCatBootloader;

    case DevMicroDevBoard:
        return DevCatMicroDev; // Microchip Dev Board, UBW32, ..

    // non-Rfidler things ...
    case DevArduinoSerial:
    case DevOtherSerial:
        return DevCatSerial;

    case DevUnconfigRfidlerCom:
    case DevUnconfigMicroDevBoard:
        return DevCatUnconfig;

    default:
        assert(0);
        return DevCatUnconfig;
    }
}


enum DevCategory DeviceInfo::DeviceCategoryFoldedUnconfig(enum DevType aDevType)
{
    switch (aDevType)
    {
    case DevRfidlerCom:
    case DevUnconfigRfidlerCom:
        return DevCatRfidler; // RFIDler

    case DevMicroBootloader:
    case DevHalfKayBootloader:
        return DevCatBootloader;

    case DevMicroDevBoard:
    case DevUnconfigMicroDevBoard:
        return DevCatMicroDev; // Microchip Dev Board, UBW32, ..

    // non-Rfidler things ...
    case DevArduinoSerial:
    case DevOtherSerial:
        return DevCatSerial;

    default:
        assert(0);
        return DevCatUnconfig;
    }
}


void DeviceInfo::DecDeviceTypeCount()
{
    devPresent = FALSE;
    UpdateDeviceTypeCount(devType, -1);
}


void DeviceInfo::UpdateDeviceTypeCount(DevType aDevType, int delta)
{
    switch (aDevType) {
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
    case DevArduinoSerial:
    case DevOtherSerial:
        iCountOtherSerial += delta;
        break;
    case DevHalfKayBootloader:
        iCountOtherBootloader += delta;
        break;
    default:
        break;
    }
}


void DeviceInfo::IncDeviceTypeCount()
{
    devPresent = TRUE;
    UpdateDeviceTypeCount(devType, 1);
}


DeviceInfo *DeviceInfo::DeleteDevice(BOOL skipNotifications)
{
    DeviceInfo *next = devNext;

    if (devPresent) {
        // device serial port or bootloader may be open, ensure closed
        CloseResources();

        // update count
        DecDeviceTypeCount();

        // update DeviceTracker counts, decide on notifications
        if (!skipNotifications) {
            DevTracker.DetermineRemovalNotifications(devType, DevNotConnected);
        }
    }

    // remove device from display
    DevTracker.RemoveViewItem((LPARAM)this);

    // delete device object, or if locked mark it for delete
    Destroy();

    return next;
}


void DeviceInfo::LockDevice(DevLockFlags lockFlag)
{
    assert( (KContextMenuLock == lockFlag) || (KUiSerialTabLock == lockFlag) || (KUiBootloaderTabLock == lockFlag) );
    assert(!(devLocked & lockFlag));

    devLocked |= lockFlag;
}


void DeviceInfo::UnlockDevice(DevLockFlags lockFlag)
{
    assert( (KContextMenuLock == lockFlag) || (KUiSerialTabLock == lockFlag) || (KUiBootloaderTabLock == lockFlag) );
    assert(devLocked & lockFlag);

    devLocked &= ~lockFlag;
    if ((0 == devLocked) && devDeleteOnUnlock) {
        Destroy();
    }
}


void DeviceInfo::ReleaseDeviceStrings()
{
    // release all strings here
    ReleaseString(devSerialNumber.devSerialString);
    ReleaseString(devSerialNumber.devInstanceIdRoot);

    ReleaseString(devPortDetails.serPortName);
    ReleaseString(devPortDetails.serFriendlyName);
    ReleaseString(devPortDetails.serDeviceName);

    ReleaseString(devHidDevicePath);
    ReleaseString(devManufacturer);
    ReleaseString(devHardwareId);
    ReleaseString(devDriverName);
    ReleaseString(devInfPath);
}


void DeviceInfo::Destroy()
{
    if (devLocked) {
        devDeleteOnUnlock = TRUE;
    } else {
        ReleaseDeviceStrings();

        if (devCommProp) {
            free(devCommProp);
        }
        if (devDCB) {
            free(devDCB);
        }

        // unlink
        if (devNext) {
            devNext->devPrev = devPrev;
        }
        if (devPrev) {
            devPrev->devNext = devNext;
        } else {
            SetPortList(devNext);
        }

        delete this;
    }
}


void DeviceInfo::SetDeviceIcon()
{
    switch(devType)
    {
    case DevRfidlerCom:
        devImage = devPresent ? DevImgRfidlerOk : DevImgRfidlerRemoved;
        break;
    case DevMicroDevBoard:
        devImage = devPresent ? DevImgDevBoardOk : DevImgDevBoardRemoved;
        break;
    case DevMicroBootloader:
        devImage = devPresent ? DevImgRfidlerBoot : DevImgRfidlerRemoved;
        break;
    case DevArduinoSerial: // Arduino icons
        devImage = devPresent ? DevImgArduinoOk : DevImgArduinoRemoved;
        break;
    case DevOtherSerial:
        if (SerialModem != devPortType) {
            devImage = devPresent ? DevImgOtherSerialOk : DevImgOtherSerialRemoved;
        } else { // modem
            devImage = devPresent ? DevImgModemSerial : DevImgModemRemoved;
        }
        break;
    case DevUnconfigRfidlerCom:
        devImage = DevImgRfidlerUnconfig;
        break;
    case DevHalfKayBootloader: // icon for HalfKay Bootloader
        devImage = devPresent ? DevImgOtherBootloader :DevImgDevBoardRemoved;
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
        return L"Absent";
    case DevPresent:
        return L"Present";
    case DevArrived: 
        return L"Arrived";
    case DevRemoved:
        return L"Removed";
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
        return L"RFIDler";
    case DevMicroDevBoard:
    case DevUnconfigMicroDevBoard:
        return L"dev board";
    case DevArduinoSerial:
        if (devNameTypeInfo) {
            return devNameTypeInfo->name;
        }
        // fall through
    case DevOtherSerial:
        // distinguish modems & serial ports
        switch (devPortType)
        {
        case SerialModem:
            return L"modem";
        case SerialMultiport:
            return L"multiport";
        default:
            return L"serial";
        }
    case DevMicroBootloader:
        return L"Microchip Bootloader";
    case DevHalfKayBootloader:
        return L"HalfKay Bootloader";
    default:
        assert(0);
        return NULL;
    }
}


void DeviceInfo::CustomLocationString(DeviceLocation aLocus, wchar_t *buffer, size_t buffSpace)
{
    wchar_t *busName = NULL;

    switch (aLocus.devBusType)
    {
    case BusUSB:
        StringCbPrintf(buffer, buffSpace, L"USB hub %u port %u",
            aLocus.devUsbHub, aLocus.devUsbPort);
        break;

    case BusBluetooth:
        busName = L"Bluetooth";
        break;
    case BusPCI:
        busName = L"PCI bus";
        break;
    case BusPCMCIA:
        busName = L"PCMCIA bus";
        break;
    case BusISAPNP:
        busName = L"ISA PNP";
        break;
    case BusEISA:
        busName = L"EISA bus";
        break;
    case BusMCA:
        busName = L"MCA bus";
        break;
    case BusFirewire:
        busName = L"Firewire";
        break;
    case BusSD:
        busName = L"SD card";
        break;

    default:
        busName = L"unknown bus";
        break;
    }

    if (busName) {
        wcscpy_s(buffer, buffSpace, busName);
    }
}


const wchar_t *DeviceInfo::LocationString()
{
    static wchar_t  locus[30];
    wchar_t *buffer = locus;
    size_t  buffSpace = sizeof(locus);

    ZeroMemory(locus, sizeof(locus));

    // place brackets around USB location depending on presence / absence
    if (!devPresent) {
        wcscpy_s(buffer, sizeof(locus), L"(");
        buffer++;
        buffSpace--;
    }

    CustomLocationString(devLocation, buffer, buffSpace);

    if (!devPresent) {
        wcscat_s(locus, L")");
    }
    return locus;
}


// BUG narrow window at Daylight Savings transition for wrong format to be used
// TODO check DST state for the time stamp, not now as we create the string, probably use GetTimeZoneInformationForYear? 
// TODO get locale date format
const wchar_t *DeviceInfo::ArrivalTimeString()
{
    const unsigned  MaxStringLength = 255;
    static wchar_t  arrString[MaxStringLength];

    arrString[0] = 0;

    if (devHasArrivalTime) {
        FILETIME                localTime;
        TIME_ZONE_INFORMATION   timezoneInfo;
        LONG                    tzBias;
        wchar_t                 *tzName = NULL;
        DWORD                   dstState = GetTimeZoneInformation(&timezoneInfo);

        switch (dstState) {
        default:
        case TIME_ZONE_ID_UNKNOWN:
            tzBias = timezoneInfo.Bias;
            tzName = timezoneInfo.StandardName;
            break;
        case TIME_ZONE_ID_STANDARD:
            tzBias = timezoneInfo.StandardBias;
            tzName = timezoneInfo.StandardName;
            break;
        case TIME_ZONE_ID_DAYLIGHT:
            tzBias = timezoneInfo.DaylightBias;
            tzName = timezoneInfo.DaylightName;
            break;
        }

//        localTime = devTimestamp; maybe do timezone stuff manually to detect Daylight savings better?

        SYSTEMTIME  sysTime;
        int         result;
        int         offset = 0;

        // timezone conversion
        FileTimeToLocalFileTime( &devTimestamp, &localTime);
        FileTimeToSystemTime(&localTime, &sysTime );

        // strings from date & time, via Windows API
        // NOTE that timezone short names (GMT, BST, WET, CDT, ..) seem unavailable through Windows API or C runtime

        // day of the week
        result = GetDateFormat(LOCALE_USER_DEFAULT, 0, &sysTime, L"ddd',' ", arrString, MaxStringLength);
        if (!result) {
#if _DEBUG
            DWORD error = GetLastError();
            // ERROR_INSUFFICIENT_BUFFER, ERROR_INVALID_FLAGS, ERROR_INVALID_PARAMETER
            assert (error == 0);
#endif
            return NULL;
        }
        offset = (result - 1); // ignore the zero byte

        // localised format for the rest of the date
        result = GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &sysTime, NULL, arrString + offset, MaxStringLength - offset);
        if (!result) {
#if _DEBUG
            DWORD error = GetLastError();
            // ERROR_INSUFFICIENT_BUFFER, ERROR_INVALID_FLAGS, ERROR_INVALID_PARAMETER
            assert (error == 0);
#endif
            return NULL;
        }
        wcscat_s(arrString, L" ");
        offset += result;

        // localised time 12h or 24h clock
        result = GetTimeFormat(LOCALE_USER_DEFAULT, 0, &sysTime, NULL, arrString + offset, MaxStringLength - offset);
        if (!result) {
#if _DEBUG
            DWORD error = GetLastError();
            // ERROR_INSUFFICIENT_BUFFER, ERROR_INVALID_FLAGS, ERROR_INVALID_PARAMETER
            assert (error == 0);
#endif
            return NULL;
        }

        // add Timezone ident, typically "GMT Standard Time" or "GMT Daylight Time" or in that vein
        if (tzName) {
            wcscat_s(arrString, L" ");
            wcscat_s(arrString, tzName);
        }

        return arrString;
    }

    return NULL;
}


const wchar_t *DeviceInfo::DisplayName()
{
    switch (devType)
    {
    case DevRfidlerCom:
    case DevMicroDevBoard:
    case DevArduinoSerial:
    case DevOtherSerial:
        return devPortDetails.serPortName;
    case DevMicroBootloader:
    case DevHalfKayBootloader:
        return L"HID Bootloader";
    case DevUnconfigRfidlerCom:
    case DevUnconfigMicroDevBoard:
        return L"Unconfigured";
    default:
        assert(0);
        return NULL;
    }
}


// compose details about device into infotip/tooltip
const wchar_t *DeviceInfo::InfoTip(BOOL longInfoTip)
{
    static wchar_t  infotipBuffer[250];
    const wchar_t *desc1 = NULL;
    const wchar_t *desc2 = NULL;

    infotipBuffer[0] = 0;

    switch (devType)
    {
    case DevRfidlerCom:
        desc1 = L"RFIDler COM port";
        break;
    case DevMicroDevBoard:
        desc1 = L"Microchip USB COM port";
        desc2 = L"\nDevelopment board";
        break;
    case DevMicroBootloader:
        desc1 = L"Microchip HID bootloader";
        desc2 = L"\nRFIDler or similar development board";
        break;
    case DevUnconfigRfidlerCom:
        desc1 = L"RFIDler COM port, driver not installed";
        break;
    case DevUnconfigMicroDevBoard:
        desc1 = L"Microchip USB COM port, driver not installed";
        break;
    case DevArduinoSerial:
    case DevOtherSerial:
        desc1 = DeviceFriendlyName();
        if (!desc1 && !longInfoTip) {
            // short description for Device Details Dialog
            desc1 = (devType == DevArduinoSerial) ? L"Arduino/Genuino/..." : L"Serial port";
        }
        break;
    case DevHalfKayBootloader:
        desc1 = L"HalfKay HID Bootloader for PJRC Teensy";
        break;
    default:
        assert(0);
    }

    wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc1);

    if (longInfoTip) {
        if (desc2) {
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc2);
        }

        // describe serial port type, based on Windows GUID for ports, modem or multiport serial card
        desc1 = NULL;
        switch (devPortType)
        {
        case SerialPort:
            desc1 = L"\nSerial Port";
            break;
        case SerialModem:
            desc1 = L"\nModem";
            break;
        case SerialMultiport:
            desc1 = L"\nMultiport Serial Device";
            break;
        }
        if (desc1) {
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), desc1);
        }

        /* USB / .inf Maunfacturer & Product names */
        if (devManufacturer) {
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), L"\nManufacturer = ");
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), devManufacturer);
        }
    }

    return infotipBuffer;
}


void DeviceInfo::CheckForUsbFlags()
{
    assert(devLocation.devBusType == BusUSB);

    /*  Start at HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\usbflags
        Windows XP & later have a key VVVVPPPPRRRR (USB VID, PID, Revision) with values below
          osvc - BOOL whether Microsoft OD USB Descriptors were found e.g. to specify driver without a .inf file
          IgnoreHWSerNum - (Vista & later) BOOL disable Windows from using the Hardware Serial number
          ResetOnResume - (Vista) hardware needs a USB reset after a Suspend
        Windows XP & earlier also stores values directly under usbflags such as
          IgnoreHWSerNum12345678 BOOL (where 1234 is the VID, 5678 is the PID)
    */
    HKEY usbFlagsKey;
    DeviceLocation *locus = &devLocation;

    // TODO put all string constants starting SYSTEM\\CurrentControlSet somewhere
    if (locus->usbRevision && !locus->usbFlags) {
        if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\usbflags", 0, KEY_READ, &usbFlagsKey)) {
            wchar_t  registryKeyName[32];
            DWORD   valtype;
            DWORD   valsize;
            DWORD   dwValue;

            if (CheckWindowsVersion(WinAtLeastXP)) {
                HKEY    hKey;

                StringCchPrintf(registryKeyName, sizeof(registryKeyName), L"%04x%04x%04x",
                    locus->usbVID,
                    locus->usbPID,
                    locus->usbRevision);

                if (ERROR_SUCCESS == RegOpenKeyEx(usbFlagsKey, registryKeyName, 0, KEY_READ, &hKey)) {

                    valsize = sizeof(DWORD);
                    if ((ERROR_SUCCESS == RegQueryValueEx(hKey, L"osvc", 0, &valtype, (LPBYTE) &dwValue, &valsize)) &&
                                (REG_BINARY == valtype) && (valsize == 2)) {
                        locus->usbFlags |= KUsbFlag_osvc;
                        locus->usbFlagOsvc = 0xFFFF & dwValue;
                    }

                    valsize = sizeof(DWORD);
                    if ((ERROR_SUCCESS == RegQueryValueEx(hKey, L"SkipContainerIdQuery", 0, &valtype, (LPBYTE) &dwValue, &valsize)) &&
                                (REG_BINARY == valtype) && (valsize == 4)) {
                        locus->usbFlags |= KUsbFlag_SkipContainerIdQuery;
                        locus->usbFlagSkipContainerIdQuery = 0xFFFFFFFF & dwValue;
                    }

                    valsize = sizeof(DWORD);
                    if ((ERROR_SUCCESS == RegQueryValueEx(hKey, L"IgnoreHWSerNum", 0, &valtype, (LPBYTE) &dwValue, &valsize)) &&
                                (REG_BINARY == valtype) && (valsize == 2)) {
                        locus->usbFlags |= KUsbFlag_IgnoreHWSerNum;
                        locus->usbFlagIgnoreHWSerNum = 0xFFFF & dwValue;
                    }

                    valsize = sizeof(DWORD);
                    if ((ERROR_SUCCESS == RegQueryValueEx(hKey, L"ResetOnResume", 0, &valtype, (LPBYTE) &dwValue, &valsize)) &&
                                (REG_BINARY == valtype) && (valsize == 2)) {
                        locus->usbFlags |= KUsbFlag_ResetOnResume;
                        locus->usbFlagResetOnResume = 0xFFFF & dwValue;
                    }

                    valsize = sizeof(DWORD);
                    if ((ERROR_SUCCESS == RegQueryValueEx(hKey, L"NoClearTTBufferOnCancel", 0, &valtype, (LPBYTE) &dwValue, &valsize)) &&
                                (REG_BINARY == valtype) && (valsize >= 1)) {
                        locus->usbFlags |= KUsbFlag_NoClearTTBufferOnCancel;
                        locus->usbFlagNoClearTTBufferOnCancel = 0xFFFF & dwValue;
                    }
                    RegCloseKey(hKey);
                }
            }

            // IgnoreHWSerNum<vid><pid> key directly below usbflags only expected up to Windows XP
            if (!CheckWindowsVersion(WinAtLeastVista) && !(locus->usbFlags & KUsbFlag_IgnoreHWSerNum)) {
                StringCchPrintf(registryKeyName, sizeof(registryKeyName), L"IgnoreHWSerNum%04x%04x",
                    devLocation.usbVID,
                    devLocation.usbPID);
                // TODO test  this

                valsize = sizeof(DWORD);
                if ((ERROR_SUCCESS == RegQueryValueEx(usbFlagsKey, registryKeyName, 0, &valtype, (LPBYTE) &dwValue, &valsize)) &&
                        (REG_BINARY == valtype) && (valsize >= 1)) {
                    locus->usbFlags |= KUsbFlag_IgnoreHWSerNum;
                    locus->usbFlagIgnoreHWSerNum = dwValue ? 1 : 0;
                }
            }

            RegCloseKey(usbFlagsKey);
        }
    }
}


int DeviceInfo::CompareByDisplayName(DeviceInfo *dev1, DeviceInfo *dev2)
{
    int result = 0;

    if (dev1->devPortDetails.serPortName) {
        if (!dev2 ->devPortDetails.serPortName) {
            result = -1;
        } else {
            result = dev1->devPortDetails.serPortNumber - dev2->devPortDetails.serPortNumber;
        }
    } else {
        if (dev2 ->devPortDetails.serPortName) {
            result = 1;
        }
    }

    return result;
}


int DeviceInfo::CompareByDisplayType(DeviceInfo *dev1, DeviceInfo *dev2)
{
    return (int)dev1->devType - (int)dev2->devType;;
}


int DeviceInfo::CompareByDisplayState(DeviceInfo *dev1, DeviceInfo *dev2)
{
    return (int)dev1->devState - (int)dev2->devState;
}


int DeviceInfo::CompareByDisplayLocus(DeviceInfo *dev1, DeviceInfo *dev2)
{
    int result = 0;

    if (dev1->devLocation.devBusType == BusUSB) {
        if (dev2->devLocation.devBusType == BusUSB) {
            // compare USB locations: hub, port
            result = dev1->devLocation.devUsbHub - dev2->devLocation.devUsbHub;
            if (result == 0) {
                result = dev1->devLocation.devUsbPort - dev2->devLocation.devUsbPort;
            }
        } else {
            result = -1;
        }
    } else {
        // arbitrary, stable order for bus types
        result = (int)dev2->devLocation.devBusType;
        result -= (int)dev1->devLocation.devBusType;
    }
    return result;
}


int DeviceInfo::CompareBySerialNumber(DeviceInfo *dev1, DeviceInfo *dev2)
{
    if (dev1->devSerialNumber.devSerialString) {
        if (dev2->devSerialNumber.devSerialString) {
            return wcscmp(dev1->devSerialNumber.devSerialString, dev2->devSerialNumber.devSerialString);
        } else {
            return -1;
        }
    } else {
        if (dev2->devSerialNumber.devSerialString) {
            return 1;
        }
    }
    return 0;
}


int DeviceInfo::CompareByArrivalTime(DeviceInfo *dev1, DeviceInfo *dev2)
{
    int result = 0;

    // check which of the devices has a valid arrival timee for sorting (ie in Arrived or Present state)
    if (dev1->devPresent) {
        if (dev2->devPresent) {
            if (dev1->devTimestamp.dwHighDateTime == dev2->devTimestamp.dwHighDateTime) {
                if (dev1->devTimestamp.dwLowDateTime == dev2->devTimestamp.dwLowDateTime) {
                    result = 0;
                } else if (dev1->devTimestamp.dwLowDateTime > dev2->devTimestamp.dwLowDateTime) {
                    result = 1;
                } else {
                    result = -1;
                }
            } else if (dev1->devTimestamp.dwHighDateTime > dev2->devTimestamp.dwHighDateTime) {
                result = 1;
            } else {
                result = -1;
            }
        } else {
            result = -1;
        }
    } else {
        if (dev2->devPresent) {
            result = 1;
        }
    }
    return result;
}


// (class static) callback function given to ListView_SortItems
// negative result if dev1 precedes dev2, positive for dev2 ahead of dev1
int CALLBACK DeviceInfo::ViewSortCompareProc(DeviceInfo *dev1, DeviceInfo *dev2, LPARAM primaryKey)
{
    int                     result = 0;
    ColumnSortParameters    *sortParams = reinterpret_cast<ColumnSortParameters *> (primaryKey);

    // default ordering on first run or if state save disabled: port name/number
    switch (sortParams->mSortType) {
    case lvDispName: // NB lvDispName (port name) comparison is default sorting order
    default:
        // name ordering is done below the switch
        result = CompareByDisplayName(dev1, dev2);
        break;

    case lvDispType: // device type
        result = CompareByDisplayType(dev1, dev2);
        break;

    case lvDispState: // device state, exact order of each state is not importantt - but sort should be stable
        result = CompareByDisplayState(dev1, dev2);
        break;

    case lvDispLocus: // how the device is connected. eg PCI, PCCard, USB
        result = CompareByDisplayLocus(dev1, dev2);
        break;

    case lvDispSernum: // serialnumber
        result = CompareBySerialNumber(dev1, dev2);
        break;

    // sort by arrival (connection) time
    case lvDispArrivalTime:
        result = CompareByArrivalTime(dev1, dev2);
        break;
    }

    // only apply reverse ordering if sorted by primary key
    if (0 != result) {
        if (sortParams->mSortReverse) {
            result = -result;
        }
        return result;
    }

    // result == 0, so find an akternate that works:
    // fall back to standard order of compares DisplayName, DisplayState, Device Type, Serial Number
    if (lvDispName != sortParams->mSortType) {
        result = CompareByDisplayName(dev1, dev2);
    }

    if (!result && (lvDispState != sortParams->mSortType)) {
        result = CompareByDisplayState(dev1, dev2);
    }

    if (!result && (lvDispType != sortParams->mSortType)) {
        result = CompareByDisplayType(dev1, dev2);
    }

    if (!result && (lvDispSernum != sortParams->mSortType)) {
        result = CompareBySerialNumber(dev1, dev2);
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


void DeviceInfo::UpdateDeviceState(BOOL aDevPresent, FILETIME aNow, unsigned aScanId, DeviceLocation* aLocation)
{
    devScanId = aScanId;

    // check for change of state, eg removed etc...
    if (aDevPresent != devPresent) {
        if (devPresent) { // => !aDevPresent
            assert(!aDevPresent);
#if defined(_DEBUG)
            PrintDebugStatus(L"Change state to removed\n");
#endif
            // update DeviceTracker counts, decide on notifications
            enum DevState newState = DevRemoved;
            DevTracker.DetermineRemovalNotifications(devType, newState);

            devState = newState;
            devElapsed = 0;
            devTimestamp = aNow;

            // hereafter arrival time column in device list view should be blank
            devHasArrivalTime = FALSE;

            // update counts
            DecDeviceTypeCount();

            // location has changed?
            if (aLocation && (BusUnknown != aLocation->devBusType) && (devLocation.devBusType != aLocation->devBusType)) {
                devLocation = *aLocation;
            }
        } else {
            assert(aDevPresent);
#if defined(_DEBUG)
            PrintDebugStatus(L"Change state to arrived/present\n");
#endif
            devDeleteOnUnlock = FALSE; // device has returned, no longer need to delete

            // choose initial state, update DeviceTracker counts, decide on notifications 
            devState = DevTracker.CheckInitialScanFlag(devType) ? DevPresent : DevArrived;
            DevTracker.DetermineArrivalNotifications(devType, devState);

            devTimestamp = aNow;
            devElapsed = 0;
            // update counts
            IncDeviceTypeCount();
            devHasArrivalTime = TRUE;
        }

        UpdateDeviceIconAndStateText();
    }
}


void DeviceInfo::AsyncDeviceRemoved()
{
    if (devPresent) {
#if defined(_DEBUG)
        PrintDebugStatus(L"Async change state to removed\n");
#endif

        // common code for making device removed, closing handles, etc..
        CloseResources();

        // update DeviceTracker counts, decide on notifications
        enum DevState newState = DevRemoved;
        DevTracker.DetermineRemovalNotifications(devType, newState);

        devState = newState;
        devElapsed = 0;
        devTimestamp = DeviceTracker::GetTimeAsFileTimeUTC();
        // update counts
        DecDeviceTypeCount();
        devHasArrivalTime = FALSE;

        UpdateDeviceIconAndStateText();
    }
}


void DeviceInfo::UpdateDeviceIconAndStateText()
{
    wchar_t buffer[20];

    StringCbPrintf(buffer, sizeof(buffer), L"%s 0min", StateName());
    SetDeviceIcon();

    // update port status & icon on display
    DevTracker.UpdateViewItemIconAndState(devImage, buffer, (LPARAM)this);

    // device location changed, or reformat location for device removal/arrival
    DevTracker.UpdateViewItemLocation(LocationString(), (LPARAM)this);

    // removed device has returned, or device has been unplugged so Arrival time has changed
    DevTracker.UpdateViewItemArrivalTime(ArrivalTimeString(), (LPARAM)this);
}


void DeviceInfo::CloseResources()
{
    // common code for making device removed, closing handles, etc..
    if (INVALID_HANDLE_VALUE != devHandle) {
        CloseHandle(devHandle);
        devHandle = INVALID_HANDLE_VALUE;
    }

    // TODO? other common actions for handling device removal? e.g. Bootloader GUI, or Serial Terminal window 
}


void DeviceInfo::UpdateDevice(enum DevType aDevType, BOOL aDevPresent,
        FILETIME aNow, SerialPortDetails& aPortDetails, DeviceLocation& aLocation,
        unsigned aScanId)
{
#if defined(_DEBUG)
    //PrintDebugStatus(L"UpdateDevice(aDevType %u, aDevPresent %u ...)\n", aDevType, aDevPresent);
#endif

    if (aDevType == DevOtherSerial) {
        // preserve identified serial port types
        if (devType == DevArduinoSerial) {
            aDevType = devType;
        }
    }

    // change of device type happens when installing/removing device drivers
    if (devType != aDevType) {
#if defined(_DEBUG)
        PrintDebugStatus(L"DevType changed (%u -> %u)\n", devType, aDevType);
#endif

        if (devPresent) {
            // update counts
            UpdateDeviceTypeCount(devType, -1);
            UpdateDeviceTypeCount(aDevType, 1);

            // in case device handle was open when device type changed (driver removed)
            CloseResources();

            // update DeviceTracker counts, decide on notifications 
            DevTracker.DetermineRemovalNotifications(devType, DevRemoved);
            DevTracker.DetermineArrivalNotifications(aDevType, devState);
        }

        // change device
        devType = aDevType;

        // rely on FindDevMatchBySernum() to enforce type change restrictions
        SetDeviceIcon();

        // update port status & icon on display
        DevTracker.UpdateViewItemIconAndType(devImage, DevTypeName(), (LPARAM)this);

        // installing driver can add/change name
        if ((devPortDetails.serPortName && !aPortDetails.serPortName) || 
                ((aPortDetails.serPortName) && (!devPortDetails.serPortName || wcscmp(devPortDetails.serPortName, aPortDetails.serPortName)))) {
#if defined(_DEBUG)
            PrintDebugStatus(L"Changing PortName (%s)\n", aPortDetails.serPortName ? aPortDetails.serPortName : devPortDetails.serPortName);
#endif
            // swap new & old port details (simplifies memory management this way)
            SerialPortDetails temp(devPortDetails);
            devPortDetails = aPortDetails;
            aPortDetails = temp;

            DevTracker.UpdateViewItemPortName(DisplayName(), (LPARAM)this);
        }
    }

    // check for change of state, eg removed or arrived
    UpdateDeviceState(aDevPresent, aNow, aScanId, &aLocation);

    if (devPresent) {
        // portname has changed? eg by user in Device Manager
        if ((aPortDetails.serPortName) && (!devPortDetails.serPortName || wcscmp(devPortDetails.serPortName, aPortDetails.serPortName))) {
            // swap new & old port details (simplifies memory management this way)
            SerialPortDetails temp(devPortDetails);
            devPortDetails = aPortDetails;
            aPortDetails = temp;

            DevTracker.UpdateViewItemPortName(DisplayName(), (LPARAM)this);
        }
    }

    // Note call to UpdateDeviceState() includes: devScanId = aScanId;
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
            StringCbPrintf(buffer, sizeof(buffer), L"%s %i min", StateName(), t2.LowPart);
            DevTracker.UpdateViewItemState(buffer, (LPARAM)this);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}


// DevicePath is used to open HID devices
wchar_t const *DeviceInfo::HidDevicePath()
{
    if (!devHidDevicePath) {
#if 1
        wchar_t     hidPath[128];

        // create Device Path from the Bootloader VID & PID, device serial number and GUID_DEVINTERFACE_HID
        StringCchPrintf(hidPath, ARRAYSIZE(hidPath),
            L"\\\\?\\hid#vid_%04x&pid_%04x#%s#{4d1e55b2-f16f-11cf-88cb-001111000030}",
            devLocation.usbVID, devLocation.usbPID,    // VID & PID part of string
            devSerialNumber.devSerialString);
        devHidDevicePath = _wcsdup(hidPath);
#else
        // GUID_DEVINTERFACE_HID
        GUID HidGuid = { 0x4D1E55B2L, 0xF16F, 0x11CF, 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 };

        HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(&HidGuid, 0, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

        if (DeviceInfoSet != INVALID_HANDLE_VALUE) {
            bool foundPath = false;
            SP_DEVICE_INTERFACE_DATA deviceInterface;
            DWORD dIndex = 0;

            ZeroMemory(&deviceInterface, sizeof(SP_DEVICE_INTERFACE_DATA));
            deviceInterface.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

            // iterate through HID devices until we find matching serial number
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
                        devHidDevicePath = wcs_dupsubstr(devDetails->DevicePath, size);
                        foundPath = true;
                    }

#if defined(_DEBUG)
                    PrintDebugStatus(L"HID DevicePath = \"%s\", serialnum = \"%s\", foundPath %i\n",
                        devDetails->DevicePath, devSerialNumber, foundPath);
#endif
                }
                free(devDetails);
            } // while
        
            SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        }
#endif
    }

    return devHidDevicePath;
}


// program shutdown, release all resources
void DeviceInfo::DeleteAllDevices()
{
    // free our device list (an object is orphaned if somehow locked for Context Menu tracking at this point)
    while (mListDevices) {
        mListDevices = mListDevices->DeleteDevice(TRUE);
    }
}


/* end of file deviceinfo.cpp */