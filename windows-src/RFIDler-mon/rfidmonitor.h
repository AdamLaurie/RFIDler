/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: rfidmonitor.h

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

#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <tchar.h>
#include <SetupAPI.h>
#include <CommCtrl.h>

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
  ENABLE_BOOTLOADER_FLASH - menu for talking to RFIDler (or Bitwhacker32) in Bootloader mode

  Any features listed here are not complete or tested!
  */
//#define ENABLE_BOOTLOADER_FLASH


// arbitrary different numbers for different timers
#define DEV_RESCAN_TIMER_MAGICNUMBER    19
#define ARRIVAL_TIMER_MAGICNUMBER       53
#define REGISTRY_SAVE_MAGICNUMBER       91


// a few classes & such need declaring before the class definitions
class MonOptions;
class DeviceInfo;
class DeviceTracker;


enum lvCol { lvDispName = 0, lvDispType, lvDispState, lvDispLocus, lvDispSernum, 
             lvRevDispName, lvRevDispType, lvRevDispState, lvRevDispLocus, lvRevDispSernum, lvDispMaxSort = lvRevDispSernum };


// Collection of RFIDler Monitor configuration that is accessed by Options dialog etc
// Getters, Setters and registry serialisation
class MonOptions {
public:
    // new instance with default values
    MonOptions(HWND hWndMain) :                  
        optHwndMain(hWndMain), // window to send timer messages too
        optDefaultShowFlags(0), optShowFlags(0), optDefaultNotifyFlags(0), optNotifyFlags(0), optHaveValueFlags(0),
        optNeedSaveFlags(0),
        optViewSortOrder(lvDispName), optViewStyleButton(ID_VIEW_DETAILS),
        optHexFileHistoryCount(0), optTimerRegistrySave(0)
        {
            // initial What to show options (bit flags):
            optDefShowNonConfig = TRUE;
            optDefShowNotPresent = FALSE;
            optDefShowDevBoards = TRUE;
            optDefShowRecentDisc = TRUE;
            optDefShowAnySerial = FALSE;

            optShowFlags = optDefaultShowFlags;

            // initial notifications: aRfidlerArrFlash aBootArrFlash aSerialArrFlash
            optDefNotifyRfidlerArrFlash = TRUE;
            optDefNotifyBootArrFlash = FALSE;
            optDefNotifyMicrochipArrFlash = FALSE;

            optNotifyFlags = optDefaultNotifyFlags;

            // which default registry should be saved
            // individual flags are cleared if previously saved values are recovered
            // first save is triggered by first user change of settings
            optNeedSaveShowFlags = TRUE;
            optNeedSaveNotifyFlags = TRUE;
            optNeedSaveWindowPlace = TRUE;
            optNeedSaveViewSortOrder = TRUE;
            optNeedSaveViewStyleButton = TRUE;
            optNeedSaveHexFileHistory = FALSE;

            optWindowPlace.left = 0;
            optWindowPlace.top = 0;
            optWindowPlace.right = 0;
            optWindowPlace.bottom = 0;

            for (int i = 0; i < optKMaxHexFileHistoryCount; i++) {
                optHexFileHistory[i] = NULL;
            }
        }

    void ReadRegistryValues();
    void SetShowOptionsAndRegistrySave(const MonOptions &newValues, BOOL &aShowSettingsChanged);
    void SetNotifyOptionsAndRegistrySave(const MonOptions &newValues);
    void RegistrySaveChangedValues();

    void KickRegSaveTimer();
    void CancelRegSaveTimer();
    // 
    BOOL GetWindowInfo(RECT &rc) const;
    int GetSortOrder() const { return optViewSortOrder; }
    int GetViewStyleButton() const { return optViewStyleButton; }
    BOOL ShowNonConfig() const { return optShowNonConfig; }
    BOOL ShowNotPresent() const { return optShowNotPresent; }
    BOOL ShowDevBoards() const { return optShowDevBoards; }
    BOOL ShowDevBoardsOrAnySerial() const { return optShowDevBoards || optShowAnySerial; }
    BOOL ShowRecentDisc() const { return optShowRecentDisc; }
    BOOL ShowAnySerial() const { return optShowAnySerial; }
    BOOL SetShowNonConfig(BOOL value) { BOOL old = optShowNonConfig; optShowNonConfig = value; return old; }
    BOOL SetShowNotPresent(BOOL value) { BOOL old = optShowNotPresent; optShowNotPresent = value; return old; }
    BOOL SetShowDevBoards(BOOL value) { BOOL old = optShowDevBoards; optShowDevBoards = value; return old; }
    BOOL SetShowRecentDisc(BOOL value) { BOOL old = optShowRecentDisc; optShowRecentDisc = value; return old; }
    BOOL SetShowAnySerial(BOOL value) { BOOL old = optShowAnySerial; optShowAnySerial = value; return old; }
    BOOL SetShowFlagsToAll();  // return flag indicates value change
    BOOL SetShowFlagsToNone();
    BOOL SetShowFlagsToDefault();

    BOOL NotifyRfidlerArrFlash() const { return optNotifyRfidlerArrFlash; }
    BOOL NotifyBootArrFlash() const { return optNotifyBootArrFlash; }
    BOOL NotifyMicrochipArrFlash() const { return optNotifyMicrochipArrFlash; }
    BOOL SetNotifyRfidlerArrFlash(BOOL value) { BOOL old = optNotifyRfidlerArrFlash; optNotifyRfidlerArrFlash = value; return old; }
    BOOL SetNotifyBootArrFlash(BOOL value) { BOOL old = optNotifyBootArrFlash; optNotifyBootArrFlash = value; return old; }
    BOOL SetNotifyMicrochipArrFlash(BOOL value) { BOOL old = optNotifyMicrochipArrFlash; optNotifyMicrochipArrFlash = value; return old; }
    BOOL SetNotifyFlagsToAll();  // return flag indicates value change
    BOOL SetNotifyFlagsToNone();
    BOOL SetNotifyFlagsToDefault();

    int HexFileHistoryCount() const { return optHexFileHistoryCount; }
    wchar_t *HexFileHistory(int index) const { return (index < optKMaxHexFileHistoryCount) ? optHexFileHistory[index] : NULL; }
    void SaveHexFileToHistory(const wchar_t *filename);

    // save changed values
    void SaveWindowInfo(const RECT &rc);
    void SaveViewSortOrder(int order);
    void SaveViewStyleButton(int newStyleButton);

private:
    HWND        optHwndMain;
    // disable warning about anonymous struct/union
#pragma warning(disable: 4201)
    // device list & notify options
    union {
        int     optDefaultShowFlags;
        struct {
            BOOL optDefShowNonConfig:1;    // IDC_SHOW_UNCONFIG
            BOOL optDefShowNotPresent:1;   // IDC_SHOWALL
            BOOL optDefShowDevBoards:1;    // IDC_SHOWBITWHACKER
            BOOL optDefShowRecentDisc:1;   // IDC_SHOW_RECENTDISC
            BOOL optDefShowAnySerial:1;    // IDC_OTHERSERIAL
        };
    };
    union {
        int     optShowFlags;
        struct {
            BOOL optShowNonConfig:1;
            BOOL optShowNotPresent:1;
            BOOL optShowDevBoards:1;
            BOOL optShowRecentDisc:1;
            BOOL optShowAnySerial:1;
        };
    };
    union {
        int     optDefaultNotifyFlags;
        struct {
            BOOL optDefNotifyRfidlerArrFlash:1;
            BOOL optDefNotifyBootArrFlash:1;
            BOOL optDefNotifyMicrochipArrFlash:1;
        };
    };
    union {
        int     optNotifyFlags;
        struct {
            BOOL optNotifyRfidlerArrFlash:1;  // IDC_RFID_ARR_FLASH
            BOOL optNotifyBootArrFlash:1;     // IDC_BOOT_ARR_FLASH
            BOOL optNotifyMicrochipArrFlash:1;   // IDC_MICROCHIP_ARR_FLASH
        };
    };
    static const int optKAllShowFlags   = 0x001F;
    static const int optKAllNotifyFlags = 0x0007;

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
        };
    };
    static const int optKMaxHexFileHistoryCount = 10;
    // values
    RECT        optWindowPlace;
    int         optViewSortOrder;
    int         optViewStyleButton;    // LV_VIEW_ICON, LV_VIEW_SMALLICON, LV_VIEW_DETAILS, LV_VIEW_TILE
    int         optHexFileHistoryCount;
    wchar_t    *optHexFileHistory[optKMaxHexFileHistoryCount];

    unsigned    optTimerRegistrySave;
};


enum DevState { DevArrived, DevPresent, DevRemoved, DevAbsent, DevNotConnected };
enum DevType {
                DevRfidlerCom,          // Rfidler COM (serial) port
                DevMicroDevBoard,       // Microchip Dev Board serial port
                DevMicroBootloader,     // Microchip Dev Board bootloader
                DevUnconfigRfidlerCom,  // unconfigured Rfidler COM port, driver not (yet) installed
                DevUnconfigMicroDevBoard,       // unconfigured Microchip Dev Board, driver not (yet) installed
            /* temporary USB parent for HID Bootloader, gives access to USB location */
                DevMicroBootShadow,
                DevOtherSerial,
                DevUnknown };

enum DevImage { DevImgRfidlerOk = 0, DevImgRfidlerUnconfig, DevImgRfidlerRemoved, DevImgRfidlerBoot,
                DevImgDevBoardOk, DevImgDevBoardRemoved, DevImgDevBoardUnconfig,
                DevImgOtherSerialOk, DevImgOtherSerialRemoved };
enum SerialType { SerialNone, SerialPort, SerialModem, SerialMultiport };

class DeviceInfo {
public:
    static void SetDeviceTracker(DeviceTracker *devTracker);
    static DeviceInfo *NewDevice(enum DevType aDevType, 
        enum DevState aDevState, FILETIME aNow, wchar_t *aSerialnumber, wchar_t *aPortname,
        wchar_t *aFriendlyName, wchar_t *aHardwareId, int aPortNumber, wchar_t *aContainerId,
        unsigned aUsbHub, unsigned aUsbPort, BOOL aUsbValid, unsigned aScanId, DeviceInfo *aDevNext,
        BOOL aIsWinSerial, SerialType aSerialType);
    void UpdateDevice(enum DevType aDevType, enum DevState aDevState,
            FILETIME aNow, wchar_t *aPortname, int aPortNumber, unsigned aUsbHub, unsigned aUsbPort,
            BOOL aUsbValid, wchar_t *aSerialNumber, unsigned aScanId, BOOL aIsWinSerial);
    void UpdateDeviceState(enum DevState aDevState, FILETIME aNow, unsigned aScanId);
    BOOL UpdateTimeInState(FILETIME ft, BOOL showNotPresent, DWORD limit);
    void UpdateHardwareId(wchar_t *aHardwareId) { devHardwareId = aHardwareId; }

    const TCHAR *StateName();
    const TCHAR *DevTypeName();
    const TCHAR *LocationString();
    const TCHAR *DisplayName();
    const TCHAR *InfoTip();
    // manage delete and allow GUI to lock against object delete eg whilst showing Context Menu
    DeviceInfo *DeleteDevice();
    void LockForContextMenu();
    void UnlockForContextMenu();
    
    // getters
    enum DevType DeviceType() const { return devType; }
    enum DevState DeviceState() const { return devState; }
    const wchar_t *SerialNumber() const { return devSerialNumber; }
    const wchar_t *ContainerId() const { return devContainerId; }
    const wchar_t *PortName() const { return devPortName; }
    const wchar_t *HardwareId() const { return devHardwareId; }
    int PortNumber() const { return devPortName ? devPortNumber : -1; }
    unsigned LastScanId() const { return devScanId; }
    DeviceInfo *DeviceNext() const { return devNext; }
    BOOL DeleteOnUnlock() const { return devDeleteOnUnlock; }
    const wchar_t *DevicePath();

    // sorting
    static int CALLBACK CompareProc(DeviceInfo *dev1, DeviceInfo *dev2, LPARAM primaryKey);

    // device counts
    static int CountOfRfidlers() { return iCountRfidlers; }
    static int CountOfDevBoards() { return iCountDevBoards; }
    static int CountOfBootloaders() { return iCountBootloaders; }

private:
    DeviceInfo(enum DevType aDevType, enum DevState aDevState, FILETIME aNow,
        wchar_t *aSerialnumber, wchar_t *aPortName, int aPortNumber, wchar_t *aContainerId,
        wchar_t *aFriendlyName, wchar_t *aHardwareId, unsigned aUsbHub,
        unsigned aUsbPort, BOOL aUsbValid, unsigned aScanId, DeviceInfo *aDevNext,
        BOOL aIsWinSerial, SerialType aSerialType) :
#ifdef _DEBUG
        devMagic(0x316f666e49766544),           // "DevInfo1"
#endif
        devTimestamp(aNow), devType(aDevType), devState(aDevState), devImage((enum DevImage)-1),
        devSerialNumber(aSerialnumber), devPortName(aPortName), devContainerId(aContainerId),
        devFriendlyName(aFriendlyName), devHardwareId(aHardwareId), devDevicePath(NULL),
        devPortNumber(aPortNumber), devUsbHub(aUsbHub), devUsbPort(aUsbPort), devUsbValid(aUsbValid),
        devElapsed(0), devScanId(aScanId), devIsWinSerial(aIsWinSerial), devSerialType(aSerialType),
        devLocked(FALSE),
        devDeleteOnUnlock(FALSE), devPresent(FALSE), devNext(aDevNext), devPrev(NULL)
        {
            SetDeviceIcon();
        }
    void SetDeviceIcon();
    void Destroy();
    void DecDeviceTypeCount();
    void IncDeviceTypeCount();

    // helper
    void UpdateDeviceTypeCount(int delta);

private:
    static DeviceTracker *gdevTracker;
    static int iCountRfidlers;
    static int iCountDevBoards;
    static int iCountBootloaders;
    static int iCountUnconRfidlers;
    static int iCountUnconDevBoards;
    static int iCountOtherSerial;

#ifdef _DEBUG
    unsigned long long devMagic;        // 64 bit magic number to identify objects in memory
#endif

    FILETIME        devTimestamp;
    enum DevType    devType;
    enum DevState   devState;
    enum DevImage   devImage;
    wchar_t         *devSerialNumber;
    wchar_t         *devPortName; // eg COM12
    wchar_t         *devContainerId; // ContainerId used for HID Bootloader devices
    wchar_t         *devFriendlyName;
    wchar_t         *devHardwareId;
    wchar_t         *devDevicePath;
    int             devPortNumber;
    unsigned        devUsbHub;
    unsigned        devUsbPort;
    BOOL            devUsbValid;
    DWORD           devElapsed;   // time since DevRemoved or DevArrived started
    unsigned        devScanId; // last device scan that touched this node
    BOOL            devIsWinSerial;
    SerialType      devSerialType;
    BOOL            devLocked;     // prevent delete whilst GUI is accessing the device
    BOOL            devDeleteOnUnlock;
    BOOL            devPresent;

    // double linked list
    DeviceInfo      *devNext;
    DeviceInfo      *devPrev;
};


class DeviceTracker {
public:
    DeviceTracker(HWND HWndMain, HWND HWndListView, HWND HWndStatusBar, HINSTANCE HInst) :        
        mHWndMain(HWndMain), mHWndListView(HWndListView), mHWndStatusBar(HWndStatusBar), mHInst(HInst),
        mOptions(HWndMain),
        mListDevices(NULL), mNeedDevicesResort(FALSE), mSortType(lvDispName),
        mInitialiseRfidler(TRUE), mInitialiseUnconfig(TRUE), mInitialiseMicroSer(TRUE),
        mInitialiseAnySerial(TRUE),
#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
        mSetupDiGetDevicePropertyW(NULL),
#endif
        mNeedDevScan(FALSE),
        mDevicesInArrivalState(FALSE),
        mNeedFlashWindow(FALSE), mHNotifyHid(NULL),
        mHNotifySerial(NULL), mTimerDevScan(0), mTimerArrival(0),
        mImageList(NULL), mImageListSm(NULL)
        {
            // read any saved options from registry
            mOptions.ReadRegistryValues();
        }

    void Initialize();
    void Cleanup();

    void OnDeviceChange(UINT uiType, LPARAM lParam);
    void UpdateArrivedAndRemovedDevices();
    void ScanRfidlerDevices();
    void CancelArrivalTimer();
    void CancelDevScanTimer();
    void SetViewStyle(int viewButton);
    int GetViewSortOrder() { return (int) mSortType; }
    void SetViewSortOrder(int sortkey) { mSortType = (enum lvCol) sortkey; 
                                        mOptions.SaveViewSortOrder(sortkey); }
    void StatusBarRefresh();

    // Get / Set options
    MonOptions& GetOptions();
    enum SetMode { SetAll, SetShowOptions, SetNotifyOptions };
    void SetOptions(const MonOptions& aOptions, SetMode setmode);

private:
    friend DeviceInfo;
    BOOL CheckInitialScanFlag(enum DevType dType);
    void DetermineArrivalNotifications(enum DevType dType, enum DevState newState);
    void DetermineRemovalNotifications(enum DevType dType, enum DevState oldState, enum DevState newState);
    BOOL AddViewItem(const TCHAR *aName, enum DevImage aImage, const TCHAR *aDevType, 
            const TCHAR *aState, const TCHAR *aUsbLocation, const TCHAR *aSerialNumber, LPARAM lParam);
    int FindViewItem(LPARAM lParam);
    void RemoveViewItem(LPARAM lParam);
    void UpdateViewItemPortName(const TCHAR *aName, LPARAM lParam);
    void UpdateViewItemIconAndState(enum DevImage aImage, const TCHAR *aState, LPARAM lParam);
    void UpdateViewItemIconAndType(enum DevImage aImage, const TCHAR *aType, LPARAM lParam);
    void UpdateViewItemLocation(const TCHAR *aUsbLocation, LPARAM lParam);
    void UpdateViewItemState(const TCHAR *aState, LPARAM lParam);
    void UpdateViewItemSerialNumber(const TCHAR *aSerialNumber, LPARAM lParam);
    void SetPortList(DeviceInfo *listStart) { mListDevices = listStart; }

private:
    void RegisterForDevNotifications();
    void UnregisterForDevNotifications();

    void UpdateArrivalOrRemovalState(FILETIME &now);
    void UpdateStatusBarAndWinFlashNotifications();

    void ScanForDevChanges();
    void ScanIncludingUnconfigDevs(FILETIME &aNow, unsigned aScanId);
    void ScanBootDevices(FILETIME &aNow, unsigned aScanId);
    void ScanSerialDevices(FILETIME &aNow, unsigned aScanId);
    void AddOrUpdateDevice(enum DevType aDevType, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        const wchar_t *devInstanceId, DWORD size, SerialType aSerialType, FILETIME &aNow, unsigned aScanId);
    void KickArrivalTimer();
    void KickDevScanTimer();
    void CleanupOrphanedDevices(FILETIME &aNow, unsigned aScanId);
    void CleanupDevicesAfterOptionsChange();
    DeviceInfo *FindDevMatchBySernum(enum DevType aDevType, wchar_t *sernumber);
    DeviceInfo *FindDevMatchByContainerId(enum DevType aDevType, wchar_t *aContainerId);
    HIMAGELIST InitImageList(int cx, int cy, unsigned count, const int *iconlist);
    void InitListColumns(const TCHAR **columns, const int *widths, unsigned count);
    BOOL GetDeviceClassGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid);
    enum DevState GetDevPresentStatus(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    BOOL GetDevUsbLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, unsigned &usbHub,
        unsigned &usbPort);
    wchar_t *GetContainerId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    wchar_t *GetFriendlyName(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    void CheckSerialDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        SerialType aSerialType, FILETIME &aNow, unsigned aScanId);
    void CheckHidDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow,
        unsigned aScanId);
    void CheckClassNoneDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow,
        unsigned aScanId);

    static BOOL GetDeviceInstanceId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        TCHAR **DevInstance, DWORD *pSize);
    static BOOL CheckDeviceId(const wchar_t *aHwId, DWORD size, const TCHAR *aRefHwId);
    static wchar_t* GetPortname(HKEY devkey);
    static wchar_t* GetPortname(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData);
    static void GetSerialnumber(const wchar_t *devInstanceId, DWORD size, BOOL &isWinSerial,
        wchar_t **serialNumber, wchar_t **devId);

private:
    MonOptions  mOptions;      // current option flags

    HWND        mHWndMain;      // Main Window, used for eg notifying device arrival/removal if enabled

    HWND        mHWndListView;  // ListView to maintain
    HWND        mHWndStatusBar; // status bar along the bottom of the window
    HINSTANCE   mHInst;
    DeviceInfo *mListDevices;
    BOOL        mNeedDevicesResort;
    enum lvCol  mSortType;
    // flags control whether new devices are DevPresent or DevArrived on arrival
    BOOL        mInitialiseRfidler;
    BOOL        mInitialiseUnconfig;
    BOOL        mInitialiseMicroSer;
    BOOL        mInitialiseAnySerial;

    // function pointer SetupDiGetDevicePropertyW in Windows >= Vista
#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    LPFNSetupDiGetDevicePropertyW mSetupDiGetDevicePropertyW;
#endif

    BOOL        mNeedDevScan;           // need to rescan devices
    BOOL        mDevicesInArrivalState; // need to refresh display e.g. display options changed, arrival state timer
    BOOL        mNeedFlashWindow;
    // WM_DEVICECHANGE notification handles
    HDEVNOTIFY  mHNotifyHid;
    HDEVNOTIFY  mHNotifySerial;
    unsigned    mTimerDevScan;
    unsigned    mTimerArrival;

    // initialised by loading resources
    HIMAGELIST  mImageList;
    HIMAGELIST  mImageListSm;
};


// wcs_utilities.cpp ...

wchar_t* wcs_dupsubstr(const wchar_t* string, size_t length);
const wchar_t* wcs_istr(const wchar_t* pString, const wchar_t* pSubStr);
BOOL wcs_consumeprefix(wchar_t* String, const wchar_t* SubStr, wchar_t** OutStr, DWORD maxsize);


// rfidmonitor.cpp exported data & functions ...

extern const TCHAR *szAppName;
extern const TCHAR *szRfidlerHwUsbId;         // "USB\\VID_1D50&PID_6098"
extern const TCHAR *szMicrochipSerialHwUsbId; // "USB\\VID_04D8&PID_000A"
extern const TCHAR *szMicrochipBootHwUsbId;   // "USB\\VID_04D8&PID_003C"
extern const TCHAR *szMicrochipBootHidId;     // "HID\\VID_04D8&PID_003C"

extern const DWORD KArrivalOrRemovalTimeLimit;

#if defined(_DEBUG)
void PrintDebugStatus(const TCHAR *format, ...);
#endif

void ReleaseString(TCHAR *&string);
void SetStatusBarPartitions(HWND hWndStatusBar, int parts);


/* end of file rfidmonitor.h */