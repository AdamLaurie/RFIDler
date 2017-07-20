/* 

    Project: RFIDler Monitor v0.2
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: rfidmonitor.h

    Author: Anthony Naggs, 2014, 2015, 2017

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

#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <tchar.h>
#include <assert.h>

#include <SetupAPI.h>
#include <CommCtrl.h>
#include <ShlObj.h>
#include <ShObjIdl.h>
#include <strsafe.h>

#include "resource.h"


/*
  Configure some of the Windows APIs used, affects which Windows versions
  the program is compatible with.
  
  Use only one of these, the first mode is for code testing.
  USE_SETUP_DEVICE_REGISTRY     => test Windows XP support code
    Uses SetupDiGetDeviceRegistryProperty() api
  USE_SETUP_DEVICE_API_ADAPTATION => 'production' chooses api based in availability.
    Uses SetupDiGetDeviceProperty() if available (windows >= Vista), otherwise
    fallback to SetupDiGetDeviceRegistryProperty() for Win XP.
  */
//#define USE_SETUP_DEVICE_REGISTRY
#define USE_SETUP_DEVICE_API_ADAPTATION


#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
// define prototype pointer to SetupDiGetDevicePropertyW()
typedef BOOL (WINAPI *LPFNSetupDiGetDevicePropertyW)(HDEVINFO DeviceInfoSet,
    PSP_DEVINFO_DATA DeviceInfoData, CONST DEVPROPKEY *PropertyKey,
    DEVPROPTYPE *PropertyType, PBYTE PropertyBuffer, DWORD PropertyBufferSize,
    PDWORD RequiredSize, DWORD Flags);
#endif


/* 
  Configure in-development features:
  ENABLE_BOOTLOADER_FLASH_DIALOGS - dialogs & menus for talking to RFIDler (or Bitwhacker32) in Bootloader mode

  Any features listed here are not complete or tested!
  */
//#define ENABLE_BOOTLOADER_FLASH_DIALOGS



/*
   Arbitrary different numbers for different timers.

   DEV_FAST_SCAN_TIMER_MAGICNUMBER timer is 20ms delay from a known interesting WM_DEVICECHANGE
   notification, to scanning installed devices to changes to the connected serial ports, RFIDler Bootloaders.

   DEV_LAZY_SCAN_TIMER_MAGICNUMBER timer is 500ms delay from a potentially interesting WM_DEVICECHANGE
   notification, to scanning installed devices to changes to the connected serial ports, RFIDler Bootloaders.

   ARRIVAL_TIMER_MAGICNUMBER is 5s tick whilst any devices are displayed as newly 'Arrived' or 'Removed',
   to update the minutes displayed for each such device, and so whether to move to the display of 'Present'
   or 'Absent'.

   REGISTRY_SAVE_MAGICNUMBER is 15s delay from changes to settings or Window position before saving
   changes to the registry.

   CANCEL_CONTEXTMENU_MAGICNUMBER this timer is started before showing a popup / context menu,
   and will close the menu after a couple of minutes by sending WM_CANCELMODE.
 */
#define DEV_FAST_SCAN_TIMER_MAGICNUMBER 7
#define DEV_LAZY_SCAN_TIMER_MAGICNUMBER 19
#define ARRIVAL_TIMER_MAGICNUMBER       53
#define REGISTRY_SAVE_MAGICNUMBER       91
#define CANCEL_CONTEXTMENU_MAGICNUMBER  114


// a few classes & such need declaring before the class definitions
class MonOptions;
class DeviceInfo;
class DeviceTracker;

extern const DWORD KArrivalOrRemovalTimeDefault;
extern const DWORD KArrivalOrRemovalTimeMaximum;


// list view columns
enum lvColumn {
    lvDispName = 0,
    lvDispType,
    lvDispState,
    lvDispLocus,
    lvDispSernum,
    lvDispArrivalTime,
    lvDispMaxSort = lvDispArrivalTime
};

struct ColumnSortParameters {
    enum lvColumn   mSortType;
    unsigned        mSortReverse;
};


// Collection of RFIDler Monitor configuration that is accessed by Options dialog etc
// Getters, Setters and registry serialisation
class MonOptions {
public:
    // new instance with default values
    MonOptions() :
        optHwndMain(NULL),
        optDefaultShowFlags(0),
        optShowFlags(0),
        optDefaultNotifyFlags(0),
        optNotifyFlags(0),
        optHaveValueFlags(0),
        optNeedSaveFlags(0),
        optViewSortVersion(1), // change this when supported column change, maybe also support conversion for setting read from registry
        optViewStyleButton(ID_VIEW_DETAILS),
        optArrivalOrRemovalTime(KArrivalOrRemovalTimeDefault),
        optWindowState(SW_NORMAL),
        optWindowLayoutVer( 0 ), // change this when main window layout changes - used to validate restored Window position/size
        optHexFileHistoryCount(0),
        optTimerRegistrySave(0)
        {
            // these are default column widths, but we persist & restore any user changes
            int    colwidth[6] = { 100, 70, 100, 108, 200, 300 };

            // Details view column widths; defaults & restored from registry
            optDetailsColumnWidths[0] = optDefaultDetailsColumnWidths[0] = colwidth[0];
            optDetailsColumnWidths[1] = optDefaultDetailsColumnWidths[1] = colwidth[1];
            optDetailsColumnWidths[2] = optDefaultDetailsColumnWidths[2] = colwidth[2];
            optDetailsColumnWidths[3] = optDefaultDetailsColumnWidths[3] = colwidth[3];
            optDetailsColumnWidths[4] = optDefaultDetailsColumnWidths[4] = colwidth[4];
            optDetailsColumnWidths[5] = optDefaultDetailsColumnWidths[5] = colwidth[5];

            // initial What to show options (bit flags):
            optDefShowNonConfig = TRUE;
            optDefShowNotPresent = FALSE;
            optDefShowDevBoards = TRUE;
            optDefShowRecentDisc = TRUE;
            optDefShowAnyOtherSerial = FALSE;

            optShowFlags = optDefaultShowFlags;

            // initial notifications: aRfidlerArrFlash aBootArrFlash aSerialArrFlash
            optDefNotifyRfidlerArrFlash = TRUE;
            optDefNotifyMicrochipBootloaderArrFlash = FALSE;
            optDefNotifyMicrochipSerialArrFlash = FALSE;
            optDefNotifyArduinoSerialArrFlash = FALSE;
            optDefNotifyAnyOtherSerialArrFlash = FALSE;

            optNotifyFlags = optDefaultNotifyFlags;

            /* Which default registry values should be saved.
               Individual flags are cleared if previously saved values are recovered.
               First save is triggered by first user change of settings,
               or if some of the expected old values were recovered.
            */
            optNeedSaveShowFlags = TRUE;
            optNeedSaveNotifyFlags = TRUE;
            optNeedSaveWindowPlace = TRUE;
            optNeedSaveViewSortOrder = TRUE;
            optNeedSaveViewStyleButton = TRUE;
            optNeedSaveHexFileHistory = FALSE;
            optNeedSaveArrivalTime = TRUE;
            optNeedSaveViewColumns = FALSE;
            optNeedSaveWindowState = FALSE;

            optWindowPlace.left = 0;
            optWindowPlace.top = 0;
            optWindowPlace.right = 0;
            optWindowPlace.bottom = 0;

            for (int i = 0; i < optKMaxHexFileHistoryCount; i++) {
                optHexFileHistory[i] = NULL;
            }

            optViewSortOrder.mSortType = lvDispName;
            optViewSortOrder.mSortReverse = 0;
        }

    // window to send timer messages to
    void SetHwndMain(HWND hWndMain) { optHwndMain = hWndMain; }

    void ReadRegistryValues(BOOL autorunStart);

    BOOL SetShowOptionsAndRegistrySave(const MonOptions &newValues);
    void SetNotifyOptionsAndRegistrySave(const MonOptions &newValues);
    void RegistrySaveChangedValues(BOOL destroyWindow);

    void KickRegSaveTimer();
    void CancelRegSaveTimer();
    // 
    BOOL GetWindowInfo(RECT &rc) const;
    ColumnSortParameters GetSortOrder() const { return optViewSortOrder; }
    int GetViewStyleButton() const { return optViewStyleButton; }
    BOOL ShowNonConfig() const { return optShowNonConfig; }
    BOOL ShowNotPresent() const { return optShowNotPresent; }
    BOOL ShowDevBoards() const { return optShowDevBoards; }
    BOOL ShowDevBoardsOrAnySerial() const { return optShowDevBoards || optShowAnyOtherSerial; }
    BOOL ShowRecentDisc() const { return optShowRecentDisc; }
    BOOL ShowAnyOtherSerial() const { return optShowAnyOtherSerial; }
    BOOL SetShowNonConfig(BOOL value) { BOOL old = optShowNonConfig; optShowNonConfig = value; return old; }
    BOOL SetShowNotPresent(BOOL value) { BOOL old = optShowNotPresent; optShowNotPresent = value; return old; }
    BOOL SetShowDevBoards(BOOL value) { BOOL old = optShowDevBoards; optShowDevBoards = value; return old; }
    BOOL SetShowRecentDisc(BOOL value) { BOOL old = optShowRecentDisc; optShowRecentDisc = value; return old; }
    BOOL SetShowAnyOtherSerial(BOOL value) { BOOL old = optShowAnyOtherSerial; optShowAnyOtherSerial = value; return old; }
    BOOL SetShowFlagsToAll();  // return flag indicates value change
    BOOL SetShowFlagsToNone();
    BOOL SetShowFlagsToDefault();

    BOOL CheckShowFlagsAreDifferent(const MonOptions &newValues) { return optShowFlags != newValues.optShowFlags; }

    BOOL NotifyRfidlerArrFlash() const { return optNotifyRfidlerArrFlash; }
    BOOL NotifyMicrochipBootloaderArrFlash() const { return optNotifyMicrochipBootloaderArrFlash; }
    BOOL NotifyMicrochipSerialArrFlash() const { return optNotifyMicrochipSerialArrFlash; }
    BOOL NotifyArduinoSerialArrFlash() const { return optNotifyArduinoSerialArrFlash; }
    BOOL NotifyAnyOtherSerialArrFlash() const { return optNotifyAnyOtherSerialArrFlash; }

    BOOL SetNotifyRfidlerArrFlash(BOOL value) { BOOL old = optNotifyRfidlerArrFlash; optNotifyRfidlerArrFlash = value; return old; }
    BOOL SetNotifyMicrochipBootloaderArrFlash(BOOL value) { BOOL old = optNotifyMicrochipBootloaderArrFlash; optNotifyMicrochipBootloaderArrFlash = value; return old; }
    BOOL SetNotifyMicrochipSerialArrFlash(BOOL value) { BOOL old = optNotifyMicrochipSerialArrFlash; optNotifyMicrochipSerialArrFlash = value; return old; }
    BOOL SetNotifyArduinoSerialArrFlash(BOOL value) { BOOL old = optNotifyArduinoSerialArrFlash; optNotifyArduinoSerialArrFlash = value; return old; }
    BOOL SetNotifyAnyOtherSerialArrFlash(BOOL value) { BOOL old = optNotifyAnyOtherSerialArrFlash; optNotifyAnyOtherSerialArrFlash = value; return old; }

    BOOL SetNotifyFlagsToAll();  // return flag indicates value change
    BOOL SetNotifyFlagsToNone();
    BOOL SetNotifyFlagsToDefault();

    int DefaultDetailsColumnWidth(unsigned column) 
        { assert(column <= lvDispMaxSort); return optDefaultDetailsColumnWidths[column]; }
    int DetailsColumnWidth(unsigned column) 
        { assert(column <= lvDispMaxSort); return optDetailsColumnWidths[column]; }
    void SetDetailsColumnWidth(unsigned column, int width);

    int HexFileHistoryCount() const { return optHexFileHistoryCount; }
    wchar_t *HexFileHistory(int index) const { return (index < optKMaxHexFileHistoryCount) ? optHexFileHistory[index] : NULL; }
    void SaveHexFileToHistory(const wchar_t *filename);

    // save changed values
    void SaveWindowInfo(UINT showCmd, const RECT &rc);
    void SaveViewSortOrder(ColumnSortParameters &aSortParams);
    void SaveViewStyleButton(int newStyleButton, BOOL aRestore);

    // access values
    unsigned GetArrivalOrRemovalTime() const { return optArrivalOrRemovalTime; }
    BOOL SetArrivalOrRemovalTime(unsigned arrivalOrRemovalTime, BOOL saveChange);

private:
    BOOL ReadRegDword(HKEY hKey, LPCWSTR lpValueName, LPBYTE lpData);
    void DoSaveChangedValues(HKEY programKey);

    BOOL FileHistoryNameIsUnique(unsigned uniqueNames, const wchar_t* string, size_t length);
    static wchar_t *NumToString(unsigned value);

private:
    HWND        optHwndMain;
    // disable warning about anonymous struct/union
#pragma warning(disable: 4201)
    // device list & notify options
    union {
        int     optDefaultShowFlags;
        struct {
            BOOL optDefShowNonConfig:1;         // IDC_SHOW_UNCONFIG
            BOOL optDefShowNotPresent:1;        // IDC_SHOWALL
            BOOL optDefShowDevBoards:1;         // IDC_SHOWBITWHACKER
            BOOL optDefShowRecentDisc:1;        // IDC_SHOW_RECENTDISC
            BOOL optDefShowAnyOtherSerial:1;    // IDC_OTHERSERIAL
        };
    };
    union {
        int     optShowFlags;
        struct {
            BOOL optShowNonConfig:1;
            BOOL optShowNotPresent:1;
            BOOL optShowDevBoards:1;
            BOOL optShowRecentDisc:1;
            BOOL optShowAnyOtherSerial:1;
        };
    };
    union { // Note: bit flags should be the same order as for optNotifyFlags below
        int     optDefaultNotifyFlags;
        struct {
            BOOL optDefNotifyRfidlerArrFlash:1;
            BOOL optDefNotifyMicrochipBootloaderArrFlash:1;
            BOOL optDefNotifyMicrochipSerialArrFlash:1;
            BOOL optDefNotifyArduinoSerialArrFlash:1;
            BOOL optDefNotifyAnyOtherSerialArrFlash:1;
        };
    };
    union {
        int     optNotifyFlags;
        struct { // Note order matters, for settings save & restore
            BOOL optNotifyRfidlerArrFlash:1;                // IDC_RFIDLER_ARR_FLASH
            BOOL optNotifyMicrochipBootloaderArrFlash:1;    // IDC_BOOT_ARR_FLASH
            BOOL optNotifyMicrochipSerialArrFlash:1;        // IDC_MICROCHIP_ARR_FLASH
            BOOL optNotifyArduinoSerialArrFlash:1;          // IDC_ARDUINO_ARR_FLASH
            BOOL optNotifyAnyOtherSerialArrFlash:1;         // IDC_OTHER_SERIAL_ARR_FLASH
        };
    };
    static const int optKAllShowFlags   = 0x001F;
    static const int optKAllNotifyFlags = 0x001F;

    // options we have retrieved from registry
    union {
        int     optHaveValueFlags;
        struct {
            BOOL optHaveWindowPlace:1;
        };
    };
    // options needing save to registry
    union {
        int     optNeedSaveFlags;
        struct {
            BOOL optNeedSaveShowFlags:1;
            BOOL optNeedSaveNotifyFlags:1;
            BOOL optNeedSaveWindowPlace:1;
            BOOL optNeedSaveViewSortOrder:1;
            BOOL optNeedSaveViewStyleButton:1;
            BOOL optNeedSaveHexFileHistory:1;
            BOOL optNeedSaveArrivalTime:1;
            BOOL optNeedSaveViewColumns:1;      // persist Device View Column Widths
            BOOL optNeedSaveWindowState:1;      // save Window min/max/normal state
        };
    };
    static const unsigned optKMaxHexFileHistoryCount = 10;
    // values
    RECT        optWindowPlace;
    unsigned    optWindowState;
    unsigned    optWindowLayoutVer;
    ColumnSortParameters    optViewSortOrder;
    unsigned    optViewSortVersion;
    int         optViewStyleButton;    // LV_VIEW_ICON, LV_VIEW_SMALLICON, LV_VIEW_DETAILS, LV_VIEW_TILE
    unsigned    optArrivalOrRemovalTime;
    unsigned    optHexFileHistoryCount;
    wchar_t     *optHexFileHistory[optKMaxHexFileHistoryCount];
    int         optDetailsColumnWidths[lvDispMaxSort + 1];
    int         optDefaultDetailsColumnWidths[5];

    unsigned    optTimerRegistrySave;
};


enum DevState {
    DevArrived,     // newly connected
    DevPresent,     // connected
    DevRemoved,     // recently removed
    DevAbsent,      // not currently or recently connected, but displayed depending on settings
    DevNotConnected // tracked in our device database, not displayed, node is locked by GUI (context menu is open etc)
};

enum DevType {
    DevRfidlerCom,              // Rfidler COM (serial) port
    DevMicroDevBoard,           // Microchip Dev Board serial port
    DevMicroBootloader,         // Microchip Dev Board bootloader
    DevUnconfigRfidlerCom,      // unconfigured Rfidler COM port, driver not (yet) installed
    DevUnconfigMicroDevBoard,   // unconfigured Microchip Dev Board, driver not (yet) installed
    // non-Rfidler things ...
    DevArduinoSerial,           // Arduino/Genuino and compatibles
    DevOtherSerial,             // com ports with no special attributes
    DevHalfKayBootloader,       // HalfKay Bootloader used by Teensy dev boards: USB VID 16C0 + PID 0478, ref https://www.pjrc.com/teensy/check_halfkay.html
};

// categories of DevType, to determine display rules, ..
enum DevCategory {
    DevCatRfidler = 0,
    DevCatBootloader,
    DevCatMicroDev,
    DevCatSerial,
    DevCatUnconfig,
};

enum DevImage {
    DevImgRfidlerOk = 0,        // Rfidler LF (Green)
    DevImgRfidlerUnconfig,
    DevImgRfidlerRemoved,
    DevImgRfidlerBoot,
    DevImgDevBoardOk,           // Microchip Dev Board (Green)
    DevImgDevBoardRemoved,
    DevImgDevBoardUnconfig,
    DevImgOtherSerialOk,        // generic serial port plug (Blue)
    DevImgOtherSerialRemoved,
    DevImgArduinoOk,            // Arduino/Genuino icons
    DevImgArduinoRemoved,
    DevImgOtherBootloader,      // Non-RFIDler LF Bootloaders
    DevImgModemSerial,          // Modem
    DevImgModemRemoved,
    DevImageCount               // Count of valid DevImgXxx values
};

enum SerialPortType {
    SerialNone,                 // Windows has different interface GUIDs for Serial Port, Modem, and smart multiport interfaces
    SerialPort,
    SerialModem,
    SerialMultiport
};

enum DevBusType {
    BusUnknown,
    BusUSB,
    BusBluetooth,
    BusPCI,
    BusPCMCIA,
    BusISAPNP,
    BusEISA,
    BusMCA,
    BusFirewire,
    BusSD
};


enum UsbFlags {         // bit masks
    KUsbFlag_osvc = 1,
    KUsbFlag_SkipContainerIdQuery = 2,
    KUsbFlag_IgnoreHWSerNum = 4,
    KUsbFlag_ResetOnResume = 8,
    KUsbFlag_NoClearTTBufferOnCancel = 16,
};


struct DeviceLocation {
    DeviceLocation() :
        devBusType(BusUnknown),
        devUsbHub(0),
        devUsbPort(0),
        usbVID(0),
        usbPID(0),
        usbRevision(0),
        usbGotRevision(FALSE),
        usbFlags(0),                            // which usbflags were read from Registry
        usbFlagOsvc(0),
        usbFlagSkipContainerIdQuery(0),
        usbFlagIgnoreHWSerNum(0),
        usbFlagResetOnResume(0),
        usbFlagNoClearTTBufferOnCancel(0),
        usbSegmentCount(0)
#if defined(_DEBUG)
        , debugBusGUID(GUID_NULL)
#endif
        {}

    enum DevBusType devBusType;         // mostly we are interested in Bluetooth / USB / PCMCIA / etc...
    unsigned        devUsbHub;
    unsigned        devUsbPort;
    unsigned        usbVID;
    unsigned        usbPID;

    // extra USB details
    unsigned        usbRevision;        // product revision
    BOOL            usbGotRevision;

    unsigned        usbFlags;           // bits for usbflags we succeeded in reading values for from registry
    unsigned        usbFlagOsvc;
    unsigned        usbFlagSkipContainerIdQuery;
    unsigned        usbFlagIgnoreHWSerNum;
    unsigned        usbFlagResetOnResume;
    unsigned        usbFlagNoClearTTBufferOnCancel;

    // TODO implement USB segment count
    unsigned        usbSegmentCount;

#if defined(_DEBUG)
    GUID            debugBusGUID;
#endif
};


// bundle of serial port details
struct SerialPortDetails {
    SerialPortDetails() :
        serPortName(NULL),
        serFriendlyName(NULL),
        serDeviceName(NULL),
        serPortNumber(0)
        {}

    wchar_t *serPortName; // eg COM12
    wchar_t *serFriendlyName;
    wchar_t *serDeviceName;
    int     serPortNumber;      // COM port number eg 6
};


// for compiled in lists (eg Arduino) of USB devices to identify
// pair display name for a USB device, with a USB VID + HID tuple
struct USBdevName
{
    unsigned    vid;
    unsigned    pid1;
    unsigned    pid2;
    wchar_t     *name;
};


struct DeviceSerialNumber {
    DeviceSerialNumber() :
        devSerialString(NULL),
        devInstanceIdRoot(NULL),
        devIsWinSerial(FALSE)
        {}

    wchar_t *devSerialString;
    wchar_t *devInstanceIdRoot;
    BOOL    devIsWinSerial;
};


class DeviceInfo {
private:
    // bit flags
    enum DevLockFlags {
        KContextMenuLock = 1,
        KUiSerialTabLock = 2,
        KUiBootloaderTabLock = 4
    };

public:
    static BOOL AddDeviceToList(enum DevType aDevType, BOOL aDevPresent, FILETIME aNow,
        SerialPortDetails& aPortDetails, DeviceLocation& aLocation, DeviceSerialNumber& aSerialNumber, unsigned aScanId,
        SerialPortType aPortType, wchar_t *manufacturer, wchar_t *hardwareId, wchar_t *driverName, wchar_t *infPath);

    void UpdateDevice(enum DevType aDevType, BOOL aDevPresent,
            FILETIME aNow, SerialPortDetails& aPortDetails, DeviceLocation& aLocation, unsigned aScanId);
    void UpdateDeviceState(BOOL aDevPresent, FILETIME aNow, unsigned aScanId, DeviceLocation* aLocation);
    void SetDeviceAbsent();
    void SetDevicePresent();
    BOOL UpdateTimeInState(FILETIME ft, DWORD limit);

    const wchar_t *StateName();
    const wchar_t *DevTypeName();
    const wchar_t *LocationString();
    const wchar_t *DisplayName();
    const wchar_t *InfoTip(BOOL longInfoTip);
    const wchar_t *ArrivalTimeString();
    const wchar_t *DeviceFriendlyName() { return devPortDetails.serFriendlyName ? devPortDetails.serFriendlyName : devPortDetails.serPortName; }

    // manage delete and allow GUI to lock against object delete eg whilst showing Context Menu
    DeviceInfo *DeleteDevice(BOOL skipNotifications);
    void LockForContextMenu()  { LockDevice(KContextMenuLock); }
    void UnlockForContextMenu() { UnlockDevice(KContextMenuLock); }
    /* TODO ui tabs
    void LockForUiSerialTab()  { LockDevice(KUiSerialTabLock); }
    void UnlockForUiSerialTab() { UnlockDevice(KUiSerialTabLock); }
    void LockForUiBootloaderTab()  { LockDevice(KUiBootloaderTabLock); }
    void UnlockForUiBootloaderTab() { UnlockDevice(KUiBootloaderTabLock); }
    */

    // handle Device Changed notification that device is removed
    void AsyncDeviceRemoved();

    // getters
    enum DevType DeviceType() const { return devType; }
    enum DevState DeviceState() const { return devState; }
    const wchar_t *SerialNumber() const { return devSerialNumber.devSerialString; }
    const wchar_t *PortName() const { return devPortDetails.serPortName; }
    const wchar_t *InstanceIdRoot() const { return devSerialNumber.devInstanceIdRoot; }
    const wchar_t *DeviceName() const { return devPortDetails.serDeviceName; }
    const wchar_t *DeviceManufacturer() const { return devManufacturer; }
    const wchar_t *DeviceHardwareId() const { return devHardwareId; }
    const wchar_t *DeviceDriverName() const { return devDriverName; }
    const wchar_t *DeviceInfPath() const { return devInfPath; }
    DeviceLocation DevLocation();
    BOOL DevicePresent() { return devPresent; }
    BOOL DeviceIsWindowsSerialNumber() { return devSerialNumber.devIsWinSerial; }
    int PortNumber() const { return devPortDetails.serPortName ? devPortDetails.serPortNumber : -1; }
    unsigned UsbSegmentCount() const { return devLocation.usbSegmentCount; }

    unsigned LastScanId() const { return devScanId; }
    DeviceInfo *DeviceNext() const { return devNext; }
    DeviceInfo *DeviceNext(BOOL keepDevice, BOOL skipNotifications) { return keepDevice ? devNext : DeleteDevice(skipNotifications); }
    enum DevImage DeviceImage() const { return devImage; }

    BOOL DeleteOnUnlock() const { return devDeleteOnUnlock; }
    const wchar_t *HidDevicePath();
    //enum DevCategory DeviceCategoryBasic() { return DeviceCategoryBasic(devType); }
    enum DevCategory DeviceCategoryFoldedUnconfig() { return DeviceCategoryFoldedUnconfig(devType); }
    BOOL IsDeviceSerialPort() { return IsDeviceSerialPort(devType); }

    static enum DevCategory DeviceCategoryBasic(enum DevType aDevType);
    static enum DevCategory DeviceCategoryFoldedUnconfig(enum DevType aDevType);
    static BOOL IsDeviceSerialPort(enum DevType aDevType)
        { return (aDevType == DevRfidlerCom) || (aDevType == DevMicroDevBoard) || (DeviceCategoryBasic(aDevType) == DevCatSerial); }

    // sorting
    static int CALLBACK ViewSortCompareProc(DeviceInfo *dev1, DeviceInfo *dev2, LPARAM primaryKey);

    // device counts
    static int CountOfRfidlers() { return iCountRfidlers; }
    static int CountOfDevBoards() { return iCountDevBoards; }
    static int CountOfBootloaders() { return iCountBootloaders; }
    static int CountOfOtherSerial() { return iCountOtherSerial; }

private:
    DeviceInfo(
        enum DevType aDevType, enum DevState aDevState, FILETIME aNow,
        SerialPortDetails& aPortDetails, DeviceLocation& aLocation,
        DeviceSerialNumber& aSerialNumber, unsigned aScanId,
        SerialPortType aPortType, struct USBdevName *nameTypeInfo,
        wchar_t *manufacturer, wchar_t *hardwareId, wchar_t *driverName, wchar_t *infPath
        ) :
#if defined(_DEBUG)
        devMagic(0x306f666e49766544),           // "DevInfo0"
#endif
        devTimestamp(aNow),
        devHasArrivalTime(DevArrived == aDevState),
        devType(aDevType),
        devState(aDevState),
        devImage((enum DevImage)0),
        devPortDetails(aPortDetails),
        devLocation(aLocation),
        devSerialNumber(aSerialNumber),
        devElapsed(0),
        devScanId(aScanId),
        devPortType(aPortType),
        devLocked(FALSE),
        devDeleteOnUnlock(FALSE),
        devPresent(FALSE),
        devNameTypeInfo(nameTypeInfo),
        devManufacturer(manufacturer),
        devHardwareId(hardwareId),
        devDriverName(driverName),
        devInfPath(infPath),
        devHidDevicePath(NULL),
        devHandle(INVALID_HANDLE_VALUE),
        devWindow(0),
        devAutoReopen(FALSE),
        devCommProp(NULL),
        devDCB(NULL),
        devNext(mListDevices),
        devPrev(NULL)
        {
            // update count before choosing Icon, as this sets devPresent
            if ((DevPresent == aDevState) || (DevArrived == aDevState)) {
                IncDeviceTypeCount();
            }

            SetDeviceIcon();

            // update double linked list
            if (devNext) {
                devNext->devPrev = this;
            }

            // new start of list
            SetPortList(this);
        }
    void SetDeviceIcon();
    void Destroy();
    void DecDeviceTypeCount();
    void IncDeviceTypeCount();
    void UpdateDeviceIconAndStateText();

    void CheckForUsbFlags();
    void CustomLocationString(DeviceLocation aLocus, wchar_t *buffer, size_t buffSpace);
    void CloseResources();
    void ReleaseDeviceStrings();

    void LockDevice(DevLockFlags lockFlag);
    void UnlockDevice(DevLockFlags lockFlag);

public:
    static DeviceInfo *GetPortList() { return mListDevices; }
    static void DeleteAllDevices();

private:
    static void SetPortList(DeviceInfo *listStart) { mListDevices = listStart; }
    static int DeviceInfo::CompareByDisplayName(DeviceInfo *dev1, DeviceInfo *dev2);
    static int DeviceInfo::CompareByDisplayType(DeviceInfo *dev1, DeviceInfo *dev2);
    static int DeviceInfo::CompareByDisplayState(DeviceInfo *dev1, DeviceInfo *dev2);
    static int DeviceInfo::CompareByDisplayLocus(DeviceInfo *dev1, DeviceInfo *dev2);
    static int DeviceInfo::CompareBySerialNumber(DeviceInfo *dev1, DeviceInfo *dev2);
    static int DeviceInfo::CompareByArrivalTime(DeviceInfo *dev1, DeviceInfo *dev2);

    // helper
    static void UpdateDeviceTypeCount(DevType aDevType, int delta);

private:
    static int iCountRfidlers;
    static int iCountDevBoards;
    static int iCountBootloaders;
    static int iCountUnconRfidlers;
    static int iCountUnconDevBoards;
    static int iCountOtherSerial;
    static int iCountOtherBootloader;

    static DeviceInfo *mListDevices;

#if defined(_DEBUG)
    unsigned long long  devMagic;        // 64 bit magic number to identify objects in memory
#endif

    FILETIME            devTimestamp;       // time of last state change
    BOOL                devHasArrivalTime;

    enum DevType        devType;
    enum DevState       devState;
    enum DevImage       devImage;

    // device attributes
    SerialPortDetails   devPortDetails;
    DeviceLocation      devLocation;
    DeviceSerialNumber  devSerialNumber;
    SerialPortType      devPortType;        // None, Port, Modem, Multiport

    // device tracking info
    DWORD               devElapsed;         // time since DevRemoved or DevArrived started
    unsigned            devScanId;          // last device scan that touched this node

    unsigned            devLocked;          // (bit flags) prevent object delete whilst GUI is accessing the device
    BOOL                devDeleteOnUnlock;
    BOOL                devPresent;         // we think device is available, usually connected or Bluetooth adapter enabled
    struct USBdevName   *devNameTypeInfo;   // our structure mapping from USB VID & PID to a device name

    // extra information strings from decvice Setup / registry
    // mostly for show in Device Details dialog, so fetching info could be postponed until needed
    wchar_t             *devManufacturer;
    wchar_t             *devHardwareId;     // TODO do we need to keep this, or just extract product Revision?
    wchar_t             *devDriverName;
    wchar_t             *devInfPath;

    wchar_t             *devHidDevicePath;  // cached HID device path for opening device, e.g.
                                            // \\?\hid#vid_04d8&pid_003c#7&f4c61c5&0&0000#{4d1e55b2-f16f-11cf-88cb-001111000030}
    HANDLE              devHandle;          // COM port or HID handle

    HWND                devWindow;          // Bootloader or terminal/serial window
    BOOL                devAutoReopen;

    // serial port / modem properties
    COMMPROP            *devCommProp;       // variable length structure
    DCB                 *devDCB;            // -"-
    COMSTAT             devCommStat;
    COMMTIMEOUTS        devCommTimeouts;

    // double linked list
    DeviceInfo          *devNext;
    DeviceInfo          *devPrev;
};


class DeviceTracker {
public:
    enum RegisterNotify {
        RegisterHidAndPorts,
        // RegisterUsbHubs
    };

    DeviceTracker() :
        mHWndMain(NULL),
        mHWndListView(NULL),
        mHWndStatusBar(NULL),
        mOptions(),
        mNeedDevicesResort(FALSE),
        mInitialiseRfidler(TRUE),
        mInitialiseUnconfig(TRUE),
        mInitialiseMicrochipSerial(TRUE),
        mInitialiseAnyOtherSerial(TRUE),
#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
        mSetupDiGetDevicePropertyW(NULL),
#endif
        mDevicesArrivedOrRemoved(FALSE),
        mNeedFlashWindow(FALSE),
        mHNotifyHid(NULL),
        mHNotifyComPort(NULL),
        mHNotifyModem(NULL),
        mHNotifyUsbDevice(NULL),
#if defined(_DEBUG)
        mHNotifyAll(NULL),
#endif
        mTimerDevFastScan(0),
        mTimerDevLazyScan(0),
        mTimerArrival(0),
        mTimerContextMenu(0)
        {
            mSortParameters.mSortType = lvDispName;
            mSortParameters.mSortReverse = 0;
        }

    void Initialize(HWND HWndMain, HWND HWndListView, HWND HWndStatusBar, HWND HWndListHeader, HINSTANCE HInst, BOOL launchStartup);
    void Cleanup();

    void OnDeviceChange(UINT uiType, LPARAM lParam);
    void UpdateArrivedAndRemovedDevices();
    void ScanRfidlerDevices();
    void CancelArrivalTimer();
    void KickContextMenuTimer();
    void CancelContextMenuTimer();
    void CancelDevScanTimers();
    void SetViewStyle(int viewButton, BOOL aRestore);
    ColumnSortParameters GetViewSortOrder() { return mSortParameters; }
    void SetViewSortOrder(ColumnSortParameters &aSortParams) { mSortParameters = aSortParams;
                                        mOptions.SaveViewSortOrder(mSortParameters); }
    void StatusBarRefresh();
    void DefaultListColumnWidths();
    void FitListColumnWidths();

    // Get / Set options
    MonOptions& GetOptions();
    enum SetMode { SetNone, SetShowOptions, SetNotifyOptions, SetAll };
    void SetOptions(const MonOptions& aOptions, SetMode setmode);
    void SetStatusBarPartitions(const MonOptions& aOptions);

    // static helper functions
    static FILETIME GetTimeAsFileTimeUTC();

    // access to icons in the image list etc, for dialog boxes
    static HICON GetIcon(int index) { return ImageList_GetIcon(mImageList, index, ILD_NORMAL); }
    static const int GetIconResourceId(int index) { return mIconList[index]; }
    static HINSTANCE GetHInstance() { return mHInst; }

private:
    friend DeviceInfo;
    BOOL CheckInitialScanFlag(enum DevType dType);
    void DetermineArrivalNotifications(enum DevType dType, enum DevState newState);
    void DetermineRemovalNotifications(enum DevType dType, enum DevState newState);
    void NotificationLogic(enum DevType dType);

    BOOL AddViewItem(const wchar_t *aName, enum DevImage aImage, const wchar_t *aDevType, 
            const wchar_t *aState, const wchar_t *aUsbLocation, const wchar_t *aSerialNumber,
            const wchar_t *aArrivalTime, LPARAM lParam);
    void SortDeviceListView();
    int FindViewItem(LPARAM lParam);
    void RemoveViewItem(LPARAM lParam);
    void UpdateViewItemPortName(const wchar_t *aName, LPARAM lParam);
    void UpdateViewItemIconAndState(enum DevImage aImage, const wchar_t *aState, LPARAM lParam);
    void UpdateViewItemIconAndType(enum DevImage aImage, const wchar_t *aType, LPARAM lParam);
    void UpdateViewItemLocation(const wchar_t *aUsbLocation, LPARAM lParam);
    void UpdateViewItemState(const wchar_t *aState, LPARAM lParam);
    void UpdateViewItemArrivalTime(const wchar_t *aArrivaltime, LPARAM lParam);

private:
    void RegisterForDevNotifications(enum RegisterNotify registerClasses);
    void UnregisterForDevNotifications();

    void UpdateArrivalOrRemovalState(FILETIME &now);
    void UpdateStatusBarAndWinFlashNotifications();

    void ScanForDevChanges();
    void ScanIncludingUnconfigDevs(FILETIME &aNow, unsigned aScanId);
    void ScanHidDevices(FILETIME &aNow, unsigned aScanId);
    void ScanSerialDevices(FILETIME &aNow, unsigned aScanId);
    void UpdatePortStateFromNotification(const wchar_t *aPortName, BOOL aDeviceArrived);
    void AddOrUpdateDevice(enum DevType aDevType, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        const wchar_t *devInstanceId, DWORD size, SerialPortType aPortType, FILETIME &aNow, unsigned aScanId);
    void KickArrivalTimer();
    void KickDevFastScanTimer();
    void KickDevLazyScanTimer();
    void CleanupOrphanedDevices(FILETIME &aNow, unsigned aScanId);
    void CleanupDevicesAfterOptionsChange();
    DeviceInfo *FindDevMatchBySernum(enum DevType aDevType, wchar_t *sernumber);
    DeviceInfo *FindDevMatchByPortName(const wchar_t *aPortName);

    HIMAGELIST InitImageList(int cx, int cy, unsigned count, const int *iconlist);
    void InitListColumns();
    BOOL GetDevicePropertyGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid,
        CONST DEVPROPKEY PropKey, DWORD Property);
    wchar_t *GetDevicePropertyString(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        CONST DEVPROPKEY PropKey, DWORD Property, BOOL copyString, BOOL multiString);
    BOOL GetDevicePropertyFiletime(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &ft,
        CONST DEVPROPKEY PropKey);

    BOOL GetDeviceClassGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid);
    BOOL GetDeviceBusTypeGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &BusGuid);
    BOOL GetDevPresentStatus(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);

    void UnpackUSBLocation(DeviceLocation& aLocus, wchar_t const *aLocationString);
    DeviceLocation GetDeviceUSBRegistryLocation(const wchar_t *VIDstring, const wchar_t *serialString);

    DeviceLocation GetUSBDeviceLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, wchar_t *VIDstring);
    enum DevBusType GetDeviceLocationFromBusGUID(GUID &BusGuid);
    DeviceLocation GetDeviceLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, DeviceSerialNumber &aSerialNumber);

    wchar_t *GetFriendlyName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    wchar_t *GetManufacturerName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    wchar_t *GetDeviceName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    wchar_t *GetHardwareId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    wchar_t *GetInfPath(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    wchar_t *GetDriverName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);

    void CheckSerialDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        SerialPortType aPortType, FILETIME &aNow, unsigned aScanId);
    void CheckHidDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow,
        unsigned aScanId);
    void CheckClassNoneDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow,
        unsigned aScanId);

    static BOOL GetDeviceInstanceId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        wchar_t **DevInstance, DWORD *pSize);
    static BOOL CheckDeviceId(const wchar_t *aHwId, DWORD size, const wchar_t *aRefHwId);
    static wchar_t* GetPortname(HKEY devkey);
    static wchar_t* GetPortname(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    static DeviceSerialNumber GetSerialnumber(const wchar_t *devInstanceId, DWORD size);

private:
    MonOptions  mOptions;      // current option flags

    HWND        mHWndMain;      // Main Window, used for eg notifying device arrival/removal if enabled

    HWND        mHWndListView;  // ListView to maintain
    HWND        mHWndStatusBar; // status bar along the bottom of the window
    HWND        mHWndListHeader; // ListView's Header

    BOOL        mNeedDevicesResort;

    ColumnSortParameters    mSortParameters;    // list view sort column & direction

    // flags control whether new devices are DevPresent or DevArrived on arrival
    BOOL        mInitialiseRfidler;
    BOOL        mInitialiseUnconfig;
    BOOL        mInitialiseMicrochipSerial;
    BOOL        mInitialiseAnyOtherSerial;

    // function pointer SetupDiGetDevicePropertyW in Windows >= Vista
#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    LPFNSetupDiGetDevicePropertyW mSetupDiGetDevicePropertyW;
#endif

    BOOL        mDevicesArrivedOrRemoved; // need to refresh display e.g. display options changed, arrival state timer
    BOOL        mNeedFlashWindow;
    // WM_DEVICECHANGE notification handles
    HDEVNOTIFY  mHNotifyHid;
    HDEVNOTIFY  mHNotifyComPort;
    HDEVNOTIFY  mHNotifyModem;
    HDEVNOTIFY  mHNotifyUsbDevice;
#if defined(_DEBUG)
    HDEVNOTIFY  mHNotifyAll;
#endif
    unsigned    mTimerDevFastScan;
    unsigned    mTimerDevLazyScan;
    unsigned    mTimerArrival;
    unsigned    mTimerContextMenu;

    // initialised by loading resources
    static  HINSTANCE   mHInst;
    static  HIMAGELIST  mImageList;
    static  HIMAGELIST  mImageListSm;
    static  const int   mIconList[DevImageCount];
};


// deviceinfo.cpp data structures ...
extern struct USBdevName ArduinoDeviceList[];
extern const unsigned KArduinoDeviceCount;


// wcs_utilities.cpp ...

wchar_t* wcs_dupsubstr(const wchar_t* string, size_t length);
const wchar_t* wcs_istr(const wchar_t* pString, const wchar_t* pSubStr);
BOOL wcs_checkprefix(const wchar_t* String, const wchar_t* SubStr);
BOOL wcs_consumeprefix(const wchar_t* String, const wchar_t* SubStr, unsigned* Offset);


// rfidmonitor.cpp exported data & functions ...

extern const wchar_t *szAppName;
extern const wchar_t *szRfidlerHwUsbId;         // "USB\\VID_1D50&PID_6098"
extern const wchar_t *szMicrochipSerialHwUsbId; // "USB\\VID_04D8&PID_000A"
//extern const wchar_t *szMicrochipBootHwUsbId;   // "USB\\VID_04D8&PID_003C"
extern const wchar_t *szMicrochipBootHidId;     // "HID\\VID_04D8&PID_003C"
extern const wchar_t *szTeensyHalfKayBootHidId; // "HID\\VID_16C0&PID_0478"


// singleton DeviceTracker
extern DeviceTracker DevTracker;


HWND InitTabbedDialog(HWND hWndTab, int itemId, wchar_t *tabTitle, LPCWSTR lpTemplateName,
        DLGPROC lpDialogFunc, LPARAM dwInitParam, BOOL showDialog);

void ReleaseString(wchar_t *&string);


// windowsversion.cpp

// tests to try on Windows Version Info
enum WinVersion {
    WinAtLeastXP,
    WinAtLeastVista,
    WinAtLeast7,
    WinAtLeast8,
    WinAtLeast10,
};

BOOL CheckWindowsVersion(enum WinVersion);


// taskbarfeatures.cpp

enum ProgBarState {
    PROG_START,
    PROG_ERROR,
    PROG_COMPLETE,
    PROG_HIDE,
    PROG_MAX
};

void StartOrStopProgressMarquee(HWND hWnd, HWND hWndProgBar, ITaskbarList3* pTbList, ProgBarState pbState);


// options_propsheet.cpp
HWND InitShowControls(MonOptions *newOptions, HWND hWndTab, BOOL showDialog);
HWND InitNotificationControls(MonOptions *newOptions, HWND hWndTab, BOOL showDialog);
BOOL CALLBACK OptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ShowOptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK NotificationsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);


// debugsupport.cpp

#if defined(_DEBUG)
void PrintDebugStatus(const wchar_t *format, ...);

void DlgProcDebugReport(wchar_t *WindowName, UINT iMsg, WPARAM wParam, LPARAM lParam);
void ListViewNotificationDebugReport(wchar_t *WindowName, NM_LISTVIEW *pNm);
void HeaderNotificationDebugReport(wchar_t *WindowName, LPNMHEADER pNmHdr);
void TabControlNotificationDebugReport(wchar_t *WindowName, NMHDR *pNm);
#endif


/* end of file rfidmonitor.h */