/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: rfidmonitor.cpp

    Author: Anthony Naggs, 2014

    Copyright (c) 2014 Anthony Naggs.
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
#include <cfgmgr32.h>
#include <dbt.h>
#include <devguid.h>
#define INITGUID
#include <DEVPKEY.H>
#include <ShlObj.h>
#include <ShlGuid.h>
#include <assert.h>
#include <strsafe.h>
#include <WinError.h>
#include <uxtheme.h> 

#include "resource.h"


/*
 * This program needs to be linked with these libraries:
 * NB if any are missing from Windows SDK the Windows Driver Kit is required.
 */
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "uxtheme.lib")

/* proclaim support for "Visual Styles" / i.e. Windows Vista Themes
 Ensure we only run on Windows XP with Common Control v6 installed,
 or later Windows version. This gives us the Tile View and glowing
 colour effects.
*/
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


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


// various global constant
// arbitrary different numbers for different imers
#define DEV_RESCAN_TIMER_MAGICNUMBER    19
#define ARRIVAL_TIMER_MAGICNUMBER       53
#define ICON_REFRESH_MAGICNUMBER        72
#define REGISTRY_SAVE_MAGICNUMBER       91



static const TCHAR *szAppName = _T("RFIDler Monitor");
static const TCHAR *szRfidlerHwUsbId = _T("USB\\VID_1D50&PID_6098");
static const TCHAR *szMicrochipSerialHwUsbId = _T("USB\\VID_04D8&PID_000A");
static const TCHAR *szMicrochipBootHwUsbId = _T("USB\\VID_04D8&PID_003C");
static const TCHAR *szMicrochipBootHidId = _T("HID\\VID_04D8&PID_003C");


/* ******************** PROGRAM CONFIGURATION ********************* */
/* nominal minimum window size is 300 * 250 */
static const SIZE KMinimiumWindowSize = { 300, 250 };

/* how long a device is shown in Removed or Arrived state */
/* Note that the value in the Options dialog text should be kept in sync */
static const DWORD KArrivalOrRemovalTimeLimit = 5;



class MonOptions;
class DeviceInfo;
class DeviceTracker;
class ControlPos;
class WindowPos;


enum lvCol { lvDispName = 0, lvDispType, lvDispState, lvDispLocus, lvDispSernum, lvDispMaxSort = lvDispSernum };


// Collection of RFIDler Monitor configuration that is accessed by Options dialog etc
// Getters, Setters and registry serialisation
class MonOptions {
public:
    // new instance with default values
    MonOptions() :                  
        optShowFlags(0), optNotifyFlags(0), optHaveValueFlags(0), optNeedSaveFlags(0),        
        optViewSortOrder(lvDispName), optViewStyleButton(ID_VIEW_DETAILS),
        optTimerRegistrySave(0)
        {
            // initial options: aShowNonConfig aShowNotPresent aShowDevBoards aShowRecentDisc
            optShowNonConfig = FALSE;
            optShowNotPresent = FALSE;
            optShowDevBoards = TRUE;
            optShowRecentDisc = TRUE;
            optShowAnySerial = FALSE;
            // initial notifications: aRfidlerArrFlash aBootArrFlash aSerialArrFlash
            optNotifyRfidlerArrFlash = FALSE;
            optNotifyBootArrFlash = FALSE;
            optNotifyMicrochipArrFlash = FALSE;

            optWindowPlace.left = 0;
            optWindowPlace.top = 0;
            optWindowPlace.right = 0;
            optWindowPlace.bottom = 0;
        }

    void ReadRegistryValues();
    void SetShowOptionsAndRegistrySave(HWND hWndMain, const MonOptions &newValues, BOOL &aShowSettingsChanged);
    void SetNotifyOptionsAndRegistrySave(HWND hWndMain, const MonOptions &newValues);
    void RegistrySaveChangedValues(HWND hWndMain);

    void KickRegSaveTimer(HWND hWndMain);
    void CancelRegSaveTimer(HWND hWndMain);
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
    void SetShowNonConfig(BOOL value) { optShowNonConfig = value; }
    void SetShowNotPresent(BOOL value) { optShowNotPresent = value; }
    void SetShowDevBoards(BOOL value) { optShowDevBoards = value; }
    void SetShowRecentDisc(BOOL value) { optShowRecentDisc = value; }
    void SetShowAnySerial(BOOL value) { optShowAnySerial = value; }

    BOOL NotifyRfidlerArrFlash() const { return optNotifyRfidlerArrFlash; }
    BOOL NotifyBootArrFlash() const { return optNotifyBootArrFlash; }
    BOOL NotifyMicrochipArrFlash() const { return optNotifyMicrochipArrFlash; }
    void SetNotifyRfidlerArrFlash(BOOL value) { optNotifyRfidlerArrFlash = value; }
    void SetNotifyBootArrFlash(BOOL value) { optNotifyBootArrFlash = value; }
    void SetNotifyMicrochipArrFlash(BOOL value) { optNotifyMicrochipArrFlash = value; }

    // save changed values
    void SaveWindowInfo(HWND hWndMain, const RECT &rc);
    void SaveViewSortOrder(HWND hWndMain, int order);
    void SaveViewStyleButton(HWND hWndMain, int newStyleButton);

private:
    // disable warning about anonymous struct/union
#pragma warning(disable: 4201)
    // device list & notify options
    union {
        int     optShowFlags;
        struct {
            BOOL optShowNonConfig:1;    // IDC_SHOW_UNCONFIG
            BOOL optShowNotPresent:1;   // IDC_SHOWALL
            BOOL optShowDevBoards:1;    // IDC_SHOWBITWHACKER
            BOOL optShowRecentDisc:1;   // IDC_SHOW_RECENTDISC
            BOOL optShowAnySerial:1;    // IDC_XYZ
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
        };
    };
    // values
    RECT        optWindowPlace;
    int         optViewSortOrder;
    int         optViewStyleButton;    // LV_VIEW_ICON, LV_VIEW_SMALLICON, LV_VIEW_DETAILS, LV_VIEW_TILE

    unsigned    optTimerRegistrySave;
};


enum DevState { DevArrived, DevPresent, DevRemoved, DevAbsent, DevNotConnected };
enum DevType { DevRfidler, DevMicroDevBoard, DevMicroBoot, DevRfidUnconfig, DevMicroUnconfig,
            /* temporary USB parent for HID Bootloader, gives access to USB location */
                DevMicroBootShadow, 
                DevOtherSerial, DevUnknwown };
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
    const TCHAR *StateName();
    const TCHAR *DevTypeName();
    const TCHAR *LocationString();
    const TCHAR *DisplayName();
    const TCHAR *InfoTip();
    // manage delete and allow GUI to lock against delete eg whilst showing Context Menu
    DeviceInfo *DeleteDevice();
    void LockForContextMenu();
    void UnlockForContextMenu();
    
    // getters
    enum DevType DeviceType() { return devType; }
    enum DevState DeviceState() { return devState; }
    const wchar_t *SerialNumber() { return devSerialNumber; }
    const wchar_t *ContainerId() { return devContainerId; }
    const wchar_t *PortName() { return devPortName; }
    int PortNumber() { return devPortName ? devPortNumber : -1; }
    unsigned LastScanId() { return devScanId; }
    DeviceInfo *DeviceNext() { return devNext; }
    // sorting
    static int CALLBACK CompareProc(DeviceInfo *dev1, DeviceInfo *dev2, LPARAM primaryKey);

    // device counts
    static int GetCountRfidlers() { return iCountRfidlers; }
    static int GetCountDevBoards() { return iCountDevBoards; }
    static int GetCountBootloaders() { return iCountBootloaders; }

private:
    DeviceInfo(enum DevType aDevType, enum DevState aDevState, FILETIME aNow,
        wchar_t *aSerialnumber, wchar_t *aPortName, int aPortNumber, wchar_t *aContainerId,
        wchar_t *aFriendlyName, wchar_t *aHardwareId, unsigned aUsbHub, unsigned aUsbPort,
        BOOL aUsbValid, unsigned aScanId, DeviceInfo *aDevNext, BOOL aIsWinSerial,
        SerialType aSerialType) :
#ifdef _DEBUG
        devMagic(0x316f666e49766544),           // "DevInfo1"
#endif
        devTimestamp(aNow), devType(aDevType), devState(aDevState), devImage((enum DevImage)-1),
        devSerialNumber(aSerialnumber), devPortName(aPortName), devContainerId(aContainerId),
        devFriendlyName(aFriendlyName), devHardwareId(aHardwareId),
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

private:
    static DeviceTracker *gdevTracker;
    static int iCountRfidlers;
    static int iCountDevBoards;
    static int iCountBootloaders;
    static int iCountUnconRfidlers;
    static int iCountUnconDevBoards;
    static int iCountOtherSerial;

#ifdef _DEBUG
    unsigned long long devMagic;        // 64 bit magic number
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


class DeviceTracker {
public:
    DeviceTracker(HWND HWndMain, HWND HWndListView, HWND HWndStatusBar, HINSTANCE HInst) :        
        mHWndMain(HWndMain), mHWndListView(HWndListView), mHWndStatusBar(HWndStatusBar), mHInst(HInst),
        mOptions(),
        mListDevices(NULL), mNeedDevicesResort(FALSE), mSortType(lvDispName),
        mInitialiseRfidler(TRUE), mInitialiseUnconfig(TRUE), mInitialiseMicroSer(TRUE),
        mInitialiseAnySerial(TRUE),
#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
        mSetupDiGetDevicePropertyW(NULL),
#endif
        mNeedDevScan(FALSE),
        mDevicesInArrivalState(FALSE), mNeedIconUpdate(TRUE),
        mNeedFlashWindow(FALSE), mHNotifyHid(NULL),
        mHNotifySerial(NULL), mTimerDevScan(0), mTimerArrival(0), mTimerIconRefresh(0),
        mIcoMonitor00(0), mIcoMonitor01(0), mIcoMonitor02(0), mIcoMonitor03(0),
        mIcoMonitor10(0), mIcoMonitor11(0), mIcoMonitor12(0), mIcoMonitor13(0),
        mIcoMonitor20(0), mIcoMonitor21(0), mIcoMonitor22(0), mIcoMonitor23(0),
        mIcoMonitor30(0), mIcoMonitor31(0), mIcoMonitor32(0), mIcoMonitor33(0),
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
                                        mOptions.SaveViewSortOrder(mHWndMain, sortkey); }
    void AppIconRefresh();

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
    void UpdateWndIconAndNotifications();
    BOOL DetermineAppNewIcon(); 
    void ScanForDevChanges();
    void KickIconRefreshTimer();
    void CancelIconRefreshTimer();
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
    HICON       mCurrIcon;
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
    BOOL        mNeedIconUpdate;        // need to update 'LED lights' icon
    BOOL        mNeedFlashWindow;
    // WM_DEVICECHANGE notification handles
    HDEVNOTIFY  mHNotifyHid;
    HDEVNOTIFY  mHNotifySerial;
    unsigned    mTimerDevScan;
    unsigned    mTimerArrival;
    unsigned    mTimerIconRefresh;

    // initialised by loading resources
    HICON       mIcoMonitor00;          // IDI_MONITOR00
    HICON       mIcoMonitor01;          // IDI_MONITOR01
    HICON       mIcoMonitor02;          // IDI_MONITOR02
    HICON       mIcoMonitor03;          // IDI_MONITOR03
    HICON       mIcoMonitor10;          // IDI_MONITOR10
    HICON       mIcoMonitor11;          // IDI_MONITOR11
    HICON       mIcoMonitor12;          // IDI_MONITOR12
    HICON       mIcoMonitor13;          // IDI_MONITOR13
    HICON       mIcoMonitor20;          // IDI_MONITOR20
    HICON       mIcoMonitor21;          // IDI_MONITOR21
    HICON       mIcoMonitor22;          // IDI_MONITOR22
    HICON       mIcoMonitor23;          // IDI_MONITOR23
    HICON       mIcoMonitor30;          // IDI_MONITOR30
    HICON       mIcoMonitor31;          // IDI_MONITOR31
    HICON       mIcoMonitor32;          // IDI_MONITOR32
    HICON       mIcoMonitor33;          // IDI_MONITOR33
    HIMAGELIST  mImageList;
    HIMAGELIST  mImageListSm;
};



static BOOL CALLBACK MonitorDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static void ReleaseString(TCHAR *&string);
static BOOL CALLBACK OptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static HWND InitTabbedDialog(HWND hWndTab, int itemId, TCHAR *tabTitle, LPCWSTR lpTemplateName,
        DLGPROC lpDialogFunc, LPARAM dwInitParam);
static HWND InitShowControls(MonOptions *aOptions, HWND hWndTab);
static HWND InitNotificationControls(MonOptions *aOptions, HWND hWndTab);
static BOOL CALLBACK ShowOptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK NotificationsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
static BOOL GetProgramFilename(TCHAR **fname);
static void CheckProgramShortcuts(const wchar_t *shortcut, BOOL *aDeskLinkExists, BOOL *aStartlinkExists);
static BOOL CheckLinkname(const wchar_t *shortcut, int csidl);
static wchar_t *CreateLinkname(const wchar_t *shortcut, int csidl);
static void CreateOrBreakLink(IShellLink *psl, const wchar_t *shortcut, int csidl, BOOL aMakeShortcut);
static void CreateProgramShortcuts(const TCHAR *fname, const wchar_t *shortcut, BOOL aDesktopShortcut, BOOL aStartupShortcut,
    BOOL aDeskLinkExists, BOOL aStartlinkExists);
static BOOL CALLBACK InstallConfigDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static ATOM RegisterMainWindow (HINSTANCE hInstance);
static void GetInitialControlPositions(HWND hWnd, WindowPos *wnd);
static void RecalcControlPositions(HWND hWnd, WindowPos *wnd);
static void MoveMainWindow(HWND hWnd, HINSTANCE hInst, DeviceTracker *DevTracker);
static void SetStatusBarPartitions(HWND hWndStatusBar, int parts);
static void LVColumnClickAndSort(DeviceTracker *DevTracker, NM_LISTVIEW *pNm);
static void LVInfoTip(LPNMLVGETINFOTIP pGetInfoTip);
static void LVRightClickContextMenu(HINSTANCE hInst, LPNMITEMACTIVATE lpnmitem);
static void LVSelectedItemContextMenu(HINSTANCE hInst, HWND hWndLV);
static void LVEmptyViewTest(NMLVEMPTYMARKUP *emptyMarkup);
static void ContextMenuPopup(HINSTANCE hInst, HWND hWndLV, DeviceInfo *dev, POINT scrPt);
static DeviceInfo *DevInfoFromListItem(HWND hWndLV, int iItem);
static DeviceInfo *DevInfoFromListPoint(HWND hWndLV, int iItem, POINT pt);
static wchar_t* wcs_dupsubstr(const wchar_t* string, size_t length);


#if defined(_DEBUG)
void PrintDebugStatus(const TCHAR *format, ...);
#endif


/* real code begins here ... */

int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE /* hPrevInstance */,
    PSTR /*szCmdLine*/,
    int /*iCmdShow*/
)
{
    ATOM ClassId;
    INITCOMMONCONTROLSEX ccInit;

    /* Initialisation */
    ClassId = RegisterMainWindow (hInstance);

    if (!ClassId) {
        MessageBox(NULL, _T("Unable to create main window"), szAppName, MB_OK | MB_ICONWARNING);
        return 3;
    }

    // we use the listview & imagelist from 'Common Controls'
    ZeroMemory(&ccInit, sizeof(ccInit));
    ccInit.dwSize = sizeof(ccInit);
    ccInit.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&ccInit);
    // need Microsoft COM setup for handling shortcuts
    CoInitialize(NULL);

    // simply use DialogBox to show window
    INT_PTR result = DialogBoxParam (hInstance, MAKEINTRESOURCE(IDD_MONITOR), 0, MonitorDlgProc, (LPARAM) hInstance);

    CoUninitialize();
    return result;
}   /* WinMain() */



ATOM RegisterMainWindow (HINSTANCE hInstance)
{
    WNDCLASSEX	WndClass;

    WndClass.cbSize        = sizeof (WndClass);
    WndClass.style         = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc   = DefDlgProc;		//MainWndProc;
    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = DLGWINDOWEXTRA;
    WndClass.hInstance     = hInstance;
    WndClass.hIcon         = (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_MONITOR00),
                                    IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
    WndClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH) GetStockObject (LTGRAY_BRUSH);
    WndClass.lpszMenuName  = NULL;
    WndClass.lpszClassName = _T("RFIDmonitor");
    WndClass.hIconSm       = NULL;
    return RegisterClassEx (&WndClass);
}   /* RegisterMainWindow() */


#if defined(_DEBUG)
// printf formatted messages to debug port
void PrintDebugStatus(const TCHAR *format, ...)
{
    HRESULT hr;
    static TCHAR msgbuff[1024];
    va_list argptr;
    va_start(argptr, format);

    hr = StringCbVPrintf(msgbuff, sizeof(msgbuff), format, argptr);
    if (SUCCEEDED(hr)) {
        OutputDebugString(msgbuff);
    }
}
#endif


/* info for managing main window during resize */
/* maybe use Horizontal & Vertical alignments specified in the dialog editor instead? */
#define FLAG_TOP_NOMOVE             0x0001
#define FLAG_HEIGHT_FIXED           0x0002
#define FLAG_BOTTOM_TRACK           0x0004
#define FLAG_LEFT_NOMOVE            0x0010
#define FLAG_WIDTH_FIXED            0x0020
#define FLAG_RIGHT_TRACK            0x0040


class ControlPos {
public:
    int         ctlId;          /* item id on dialog */
    unsigned    ctlPosRules;    /* our repositioning rules */
    HWND        ctlHWnd;        /* control's handle */
    RECT        ctlRect;        /* initial control position & dimensions */
    BOOL        ctlHidden;      /* hidden because current size is too small */
};


class WindowPos {
public:
    ControlPos  *wndCtrls;
    unsigned    wndCtlCount;
    SIZE        wndSize;
};


static void GetInitialControlPositions(HWND hWnd, WindowPos *wnd)
{
    RECT wndRect;

    /* get control initial positions */
    if (GetClientRect(hWnd, &wndRect)) {
        unsigned idx;
        ControlPos *ctl;

        wnd->wndSize.cx = wndRect.right - wndRect.left;
        wnd->wndSize.cy = wndRect.bottom - wndRect.top;

        for (idx = 0; idx < wnd->wndCtlCount; idx++) {
            HWND hCtl;

            ctl = wnd->wndCtrls + idx;
            hCtl= GetDlgItem(hWnd, ctl->ctlId);

            if (hCtl) {
                ctl->ctlHWnd = hCtl;

                /* get control corners */
                GetWindowRect(hCtl, &ctl->ctlRect);
                /* convert screen co-ordinates to positions in dialog client area */
                MapWindowPoints(NULL, hWnd, (LPPOINT) &ctl->ctlRect, 2);
            } /* valid hCtl handle */
        } /* for */
    }
}   /* GetInitialControlPositions() */


static void RecalcControlPositions(HWND hWnd, WindowPos *wnd)
{
    unsigned idx;
    HDWP hdwp;
    RECT newRect;
    int  increaseW;
    int  increaseH;
    
    GetClientRect(hWnd, &newRect);
    increaseW = newRect.right - wnd->wndSize.cx;
    increaseH = newRect.bottom - wnd->wndSize.cy;

    /* need to resize/reposition controls? */
    if ( (increaseW == 0) && (increaseH == 0) ) {
        return;
    }

    // remember new client area
    wnd->wndSize.cx = newRect.right;
    wnd->wndSize.cy = newRect.bottom;

    hdwp = BeginDeferWindowPos(wnd->wndCtlCount);

    for (idx = 0; idx < wnd->wndCtlCount; idx++) {
        UINT       uFlags = SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE;
        ControlPos *ctl = wnd->wndCtrls + idx;
        RECT       *rt = &ctl->ctlRect;

        // width change?
        if (increaseW != 0) {
            if (ctl->ctlPosRules & FLAG_WIDTH_FIXED) {
                // not fixed pos X?
                if (!(ctl->ctlPosRules & FLAG_LEFT_NOMOVE)) {
                    // move right
                    rt->left += increaseW;
                    uFlags &= ~SWP_NOMOVE;
                }
            } else {
                rt->right += increaseW;
                uFlags &= ~SWP_NOSIZE;
            }
        }
    
        if (increaseH != 0) {
            if (ctl->ctlPosRules & FLAG_HEIGHT_FIXED) {
                // not fixed pos Y?
                if (!(ctl->ctlPosRules & FLAG_TOP_NOMOVE)) {
                    // move down
                    rt->top += increaseH;
                    uFlags &= ~SWP_NOMOVE;
                }
            } else {
                rt->bottom += increaseH;
                uFlags &= ~SWP_NOSIZE;
            }
        }

        // reposition / resize ctl->ctlHWnd
        DeferWindowPos(hdwp, ctl->ctlHWnd, NULL, rt->left, rt->top, rt->right - rt->left, rt->bottom - rt->top, uFlags);
    }

    EndDeferWindowPos(hdwp);
}


void MoveMainWindow(HWND hWnd, HINSTANCE hInst, DeviceTracker *DevTracker)
{
    RECT rc;

    // get stored position/size from registry
    const MonOptions &opt = DevTracker->GetOptions();
    // check window parameters are recalled, & minimum window size
    if (opt.GetWindowInfo(rc) &&
            ((rc.right - rc.left) >= KMinimiumWindowSize.cx) && ((rc.bottom - rc.top) >= KMinimiumWindowSize.cy) ) {
        // check that window pos is on screen
        HMONITOR mon;
        WINDOWPLACEMENT wp;
        wp.length = sizeof(WINDOWPLACEMENT);
        wp.rcNormalPosition = rc;
        wp.showCmd = SW_SHOWNORMAL;

        // rc is 'workspace co-ords' should be close enough to screen coords for testing visibility
        mon = MonitorFromRect(&rc, MONITOR_DEFAULTTONULL);
        if (mon) {
            // seems to be visible, restore window pos
            SetWindowPlacement(hWnd, &wp);
            return;
        }
    }


    // find out where CW_USEDEFAULT would place new window (not available for dialogs)
    if (GetWindowRect(hWnd, &rc)) {
        // make invisible window the same size as this, positioned with CW_USEDEFAULT
        // NB need to reference a valid Window class
        HWND hW = CreateWindow(_T("RFIDmonitor"), _T("Invisible Touch"), WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
            NULL, NULL, hInst, NULL);
        if (hW) {
            RECT rc2;

            if (GetWindowRect(hW, &rc2)) {
                // move program window to this location
                SetWindowPos(hWnd, HWND_TOP, rc2.left, rc2.top, 0, 0, SWP_NOSIZE);
            }
            // cleanup
            DestroyWindow(hW);
        }
    }
}


BOOL CALLBACK MonitorDlgProc (
    HWND hWnd,
    UINT iMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    /* statics keep state between Windows messages */
    static HINSTANCE  hInst = 0;
    static DeviceTracker *DevTracker;
    static HWND hWndLV = NULL;
    static HWND hWndStatusBar = NULL;
    // data to support resizing of window
    static ControlPos MainControls[] =
    {
        { IDC_RFIDLERLIST, FLAG_TOP_NOMOVE | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
        { IDC_STATUSBAR,  FLAG_HEIGHT_FIXED | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
    };
    static WindowPos MainWnd = {
        MainControls,
        sizeof(MainControls) / sizeof(ControlPos),
    };


    /* locals */
    int  handled = 0;

    switch (iMsg) {
    case WM_INITDIALOG:	/* from CreateDialog() */
        hInst = (HINSTANCE) lParam;
        hWndLV = GetDlgItem(hWnd, IDC_RFIDLERLIST);
        // Create Status Bar with sizing grip at bottom of window
        hWndStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP, 
            _T(""), hWnd, IDC_STATUSBAR);
        GetInitialControlPositions(hWnd, &MainWnd);
        // create device tracking stuff
        DevTracker = new DeviceTracker(hWnd, hWndLV, hWndStatusBar, hInst);
        if (DevTracker) {
            // Setting are restored in DeviceTracker constructor, so we can test them now
            if (hWndStatusBar) {
                if (DevTracker->GetOptions().ShowDevBoardsOrAnySerial()) {
                    SetStatusBarPartitions(hWndStatusBar, 3);
                } else {
                    SetStatusBarPartitions(hWndStatusBar, 2);
                }
            }
            DevTracker->Initialize();
            // restore window position & size, or use CW_USEDEFAULT positioning
            MoveMainWindow(hWnd, hInst, DevTracker);
        } else {
            MessageBox(hWnd, _T("out of memory error"), szAppName, MB_OK);
            EndDialog (hWnd, 0);
        }
        return TRUE;

    case WM_WINDOWPOSCHANGED:
        {
            const WINDOWPOS *winpos = (WINDOWPOS *) lParam;

            if (!(winpos->flags & SWP_NOSIZE)) {
                // Note ListView will rearrange its items, so long as LVS_AUTOARRANGE style is set
                RecalcControlPositions(hWnd, &MainWnd);
            }

            if (!(winpos->flags & SWP_NOMOVE) || !(winpos->flags & SWP_NOSIZE)) {
                WINDOWPLACEMENT place;

                // save position & size if 'normal' display (not maximized or minimized)
                place.length = sizeof(WINDOWPLACEMENT);
                if (GetWindowPlacement(hWnd, &place) && (place.showCmd == SW_SHOWNORMAL)) {
                    // save window placement
                    DevTracker->GetOptions().SaveWindowInfo(hWnd, place.rcNormalPosition);
                }
            }
        }
        handled++;
        break;

    case WM_GETMINMAXINFO: // set minimum window resize values
        {
            MINMAXINFO *minmax = (MINMAXINFO *)lParam;
            if (minmax->ptMinTrackSize.x < KMinimiumWindowSize.cx) {
                minmax->ptMinTrackSize.x = KMinimiumWindowSize.cx;
            }
            if (minmax->ptMinTrackSize.y < KMinimiumWindowSize.cy) {
                minmax->ptMinTrackSize.y = KMinimiumWindowSize.cy;
            }
        }
        break;

    case WM_COMMAND: // handle button, menu selections, ...
        {
            int wID = LOWORD (wParam);
            //int wNotification = HIWORD(wParam);
            //HWND hChild = (HWND) lParam;

            switch (wID) {
            case ID_HELP_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_HELP_ABOUT), hWnd, AboutDlgProc);
                handled++;
                break;

                // handle different ListView views
            case ID_VIEW_LARGE_ICONS:
            case ID_VIEW_SMALL_ICONS:
            case ID_VIEW_DETAILS:
            case ID_VIEW_TILES: // Tiles view okay as we specify comctrl32 DLL v6.0 in manifest
                {
                    int currentView = DevTracker->GetOptions().GetViewStyleButton();
                    if (wID != currentView) {
                        // move menu check mark
                        HMENU hMenu = GetMenu(hWnd);

                        CheckMenuItem(hMenu, currentView, MF_UNCHECKED);
                        CheckMenuItem(hMenu, wID, MF_CHECKED);
                        DevTracker->SetViewStyle(wID);
                    }
                }
                handled++;
                break;

            case ID_INSTALL_CONFIG: // dialog IDD_CONFIGSHORTCUTS
                DialogBoxParam (hInst, MAKEINTRESOURCE(IDD_CONFIGSHORTCUTS), hWnd,
                    InstallConfigDlgProc, (LPARAM) DevTracker);
                break;

            case ID_MONITOR_OPTIONS:
                DialogBoxParam (hInst, MAKEINTRESOURCE(IDD_OPTIONS), hWnd,
                    OptionsDlgProc, (LPARAM) DevTracker);
                break;

            case ID_MONITOR_EXIT:
                EndDialog (hWnd, 0);
                handled++;
                break;
            }
        } // WM_COMMAND
        break;

    case WM_NOTIFY:
        if (wParam == IDC_RFIDLERLIST) {
            NM_LISTVIEW *pNm = (NM_LISTVIEW *) lParam;

            switch(pNm->hdr.code) {
            case LVN_COLUMNCLICK:
                LVColumnClickAndSort(DevTracker, pNm);
                handled++;
                break;

            case LVN_GETINFOTIP:
                // tooltip when mouse hovers over device in view
                LVInfoTip((LPNMLVGETINFOTIP)lParam);
                handled++;
                break;

            case NM_RCLICK: // right click: device menu
                LVRightClickContextMenu(hInst, (LPNMITEMACTIVATE) lParam);
                handled++;
                break;

            case LVN_GETEMPTYMARKUP:
                // bug: documented way of setting empty ListView text, no apparent effect on Windows 7
                LVEmptyViewTest((NMLVEMPTYMARKUP *) lParam);
                handled++;
                break;

            case (LVN_FIRST-61):
                // LVN_GETEMPTYTEXTW undocumented way of setting empty ListView text, no apparent effect on Windows 7
                {
                    NMLVDISPINFO *nm = (NMLVDISPINFO *)lParam;
                    if (nm->item.mask == LVIF_TEXT && nm->item.pszText) {
                        StringCchCopy(nm->item.pszText, nm->item.cchTextMax, _T("No RFIDlers connected."));
                    }
                }
                handled++;
                break;

#ifdef _DEBUG
            case LVN_ITEMCHANGING: // notifications we want to ignore on Debug build
            case LVN_ITEMCHANGED:
            case LVN_INSERTITEM: 
            case LVN_DELETEITEM:
            case LVN_DELETEALLITEMS:
            case LVN_HOTTRACK:
            case LVN_KEYDOWN:
                break;

            default: // report unhandled notifications
                if (pNm->hdr.code <= LVN_FIRST) {
                    PrintDebugStatus(_T("WM_NOTIFY ListView hdr.code = %u = (LVN_FIRST-%u)\n"),
                        pNm->hdr.code, LVN_FIRST - pNm->hdr.code);
                }
                break;
#else
            default:
                break;
#endif
            }
        }
        break;

    case WM_CONTEXTMENU: // Context Menu for ListView (should only be VK_APPS or Shift+F10 come here)
        if (wParam == (WPARAM) hWndLV) {
            if ((lParam == 0xFFFFFFFF) && (ListView_GetSelectedCount(hWndLV) > 0)) {
                LVSelectedItemContextMenu(hInst, hWndLV);
            }
        }
        break;

    case WM_DEVICECHANGE:
        if (DevTracker) {
            DevTracker->OnDeviceChange((UINT) wParam, lParam);
        }
        handled++;
        break;

    case WM_TIMER:
        switch (wParam)
        {
        case DEV_RESCAN_TIMER_MAGICNUMBER:
            if (DevTracker) {
                DevTracker->ScanRfidlerDevices();
            }
            handled++;
            break;
        case ARRIVAL_TIMER_MAGICNUMBER:
            if (DevTracker) {
                DevTracker->UpdateArrivedAndRemovedDevices();
            }
            handled++;
            break;
        case ICON_REFRESH_MAGICNUMBER:
            /* Windows Bug: Sometimes window icon updates but big taskbar one doesn't.
               Attempt to workaround: Try using timer to ensure at least 1 minute between changes.
               */
            if (DevTracker) {
                DevTracker->AppIconRefresh();
            }
            handled++;
            break;
        case REGISTRY_SAVE_MAGICNUMBER:
            if (DevTracker) {
                DevTracker->GetOptions().RegistrySaveChangedValues(hWnd);
            }
            handled++;
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog (hWnd, 0);
        handled++;
        break;

    case WM_DESTROY: /* cleanup & exit */
        if (DevTracker) {
            DevTracker->GetOptions().RegistrySaveChangedValues(hWnd);
            DevTracker->Cleanup();
            delete DevTracker;
            DevTracker = NULL;
        }
        // close program
        PostQuitMessage (0);
        handled++;
        break;
    }
    	
    // 1 = handled here, 0 = pass to default handling
    return handled;
}   /* MonitorDlgProc() */


HWND InitTabbedDialog(HWND hWndTab, int itemId, TCHAR *tabTitle, LPCWSTR lpTemplateName,
        DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
    TCITEM tcItem;

    tcItem.mask = TCIF_TEXT;
    tcItem.pszText = tabTitle;
    TabCtrl_InsertItem(hWndTab, itemId, &tcItem);

    HWND child = CreateDialogParam( GetModuleHandle( NULL ),
        lpTemplateName, hWndTab, lpDialogFunc, dwInitParam);

    if (child) {
        // move child dialog away from tabs
        RECT rc;

        GetClientRect(hWndTab, &rc);
        TabCtrl_AdjustRect(hWndTab, FALSE, &rc);
        SetWindowPos(child, 0, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER);
        // show first tab
        if (itemId == 0) {
            ShowWindow(child, SW_SHOW);
        }
    }
    return child;
}


HWND InitShowControls(MonOptions *aOptions, HWND hWndTab)
{
    return InitTabbedDialog(hWndTab, 0, _T("Show Devices"), MAKEINTRESOURCE( IDD_WHATTOWATCH ),
        ShowOptionsDlgProc, (LPARAM) aOptions);
}


HWND InitNotificationControls(MonOptions *aOptions, HWND hWndTab)
{
    return InitTabbedDialog(hWndTab, 1, _T("Device Notifications"), MAKEINTRESOURCE( IDD_NOTIFICATIONS ),
        NotificationsDlgProc, (LPARAM) aOptions);
}


BOOL CALLBACK ShowOptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static MonOptions *newOptions;
    static HWND       hWndParentDlg = NULL;

    int handled = 0;

    switch(iMsg) {
    case WM_INITDIALOG:
        hWndParentDlg = GetParent(GetParent(hWnd));
        newOptions = (MonOptions *) lParam;
        if (newOptions->ShowNonConfig()) {
            SendMessage(GetDlgItem(hWnd, IDC_SHOW_UNCONFIG), BM_SETCHECK, BST_CHECKED, 0);
        }
        if (newOptions->ShowNotPresent()) {
            SendMessage(GetDlgItem(hWnd, IDC_SHOW_ALL), BM_SETCHECK, BST_CHECKED, 0);
        }
        if (newOptions->ShowDevBoards()) {
            SendMessage(GetDlgItem(hWnd, IDC_SHOW_BITWHACKER), BM_SETCHECK, BST_CHECKED, 0);
        }
        if (newOptions->ShowRecentDisc()) {
            SendMessage(GetDlgItem(hWnd, IDC_SHOW_RECENTDISC), BM_SETCHECK, BST_CHECKED, 0);
        }
        if (newOptions->ShowAnySerial()) {
            SendMessage(GetDlgItem(hWnd, IDC_OTHERSERIAL), BM_SETCHECK, BST_CHECKED, 0);
        }
        EnableThemeDialogTexture(hWnd, ETDT_ENABLETAB);
        return TRUE;

    case WM_NOTIFYFORMAT:
        return NFR_UNICODE;

    case WM_COMMAND:
        {
            int wID = LOWORD (wParam);
            BOOL enableApply = FALSE; // whether change of options should enable Apply button

            switch (wID) 
            {
            case IDC_CHECK_SHOW_ALL:                
                if (!newOptions->ShowNonConfig()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_UNCONFIG), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetShowNonConfig(TRUE);
                    enableApply = TRUE;
                }
                if (!newOptions->ShowNotPresent()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_ALL), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetShowNotPresent(TRUE);
                    enableApply = TRUE;
                }
                if (!newOptions->ShowDevBoards()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_BITWHACKER), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetShowDevBoards(TRUE);
                    enableApply = TRUE;
                }
                if (!newOptions->ShowRecentDisc()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_RECENTDISC), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetShowRecentDisc(TRUE);
                    enableApply = TRUE;
                }
                if (!newOptions->ShowAnySerial()) {
                    SendMessage(GetDlgItem(hWnd, IDC_OTHERSERIAL), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetShowAnySerial(TRUE);
                    enableApply = TRUE;
                }
                break;
            case IDC_CHECK_SHOW_NONE:
                if (newOptions->ShowNonConfig()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_UNCONFIG), BM_SETCHECK, BST_UNCHECKED, 0);
                    newOptions->SetShowNonConfig(FALSE);
                    enableApply = TRUE;
                }
                if (newOptions->ShowNotPresent()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_ALL), BM_SETCHECK, BST_UNCHECKED, 0);
                    newOptions->SetShowNotPresent(FALSE);
                    enableApply = TRUE;
                }
                if (newOptions->ShowDevBoards()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_BITWHACKER), BM_SETCHECK, BST_UNCHECKED, 0);
                    newOptions->SetShowDevBoards(FALSE);
                    enableApply = TRUE;
                }
                if (newOptions->ShowRecentDisc()) {
                    SendMessage(GetDlgItem(hWnd, IDC_SHOW_RECENTDISC), BM_SETCHECK, BST_UNCHECKED, 0);
                    newOptions->SetShowRecentDisc(FALSE);
                    enableApply = TRUE;
                }
                if (newOptions->ShowAnySerial()) {
                    SendMessage(GetDlgItem(hWnd, IDC_OTHERSERIAL), BM_SETCHECK, BST_UNCHECKED, 0);
                    newOptions->SetShowAnySerial(FALSE);
                    enableApply = TRUE;
                }
                break;
            case IDC_SHOW_UNCONFIG:
                newOptions->SetShowNonConfig((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_UNCONFIG));
                enableApply = TRUE;
                break;
            case IDC_SHOW_ALL:
                newOptions->SetShowNotPresent((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_ALL));
                enableApply = TRUE;
                break;
            case IDC_SHOW_BITWHACKER:
                newOptions->SetShowDevBoards((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_BITWHACKER));
                enableApply = TRUE;
                break;
            case IDC_SHOW_RECENTDISC:
                newOptions->SetShowRecentDisc((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_RECENTDISC));
                enableApply = TRUE;
                break;
            case IDC_OTHERSERIAL:
                newOptions->SetShowAnySerial((BOOL) IsDlgButtonChecked(hWnd, IDC_OTHERSERIAL));
                enableApply = TRUE;
                break;
            }
            if (enableApply && hWndParentDlg) {
                SendMessage(hWndParentDlg, WM_APP, 0, 0);
            }
        }
        break;
    }

    return handled;
}


BOOL CALLBACK NotificationsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static MonOptions *newOptions;
    static HWND       hWndParentDlg = NULL;

    int handled = 0;

    switch(iMsg) {
    case WM_INITDIALOG:
        hWndParentDlg = GetParent(GetParent(hWnd));
        newOptions = (MonOptions *) lParam;
        if (newOptions->NotifyRfidlerArrFlash()) {
            SendMessage(GetDlgItem(hWnd, IDC_RFID_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
        }
        if (newOptions->NotifyBootArrFlash()) {
            SendMessage(GetDlgItem(hWnd, IDC_BOOT_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
        }
        if (newOptions->NotifyMicrochipArrFlash()) {
            SendMessage(GetDlgItem(hWnd, IDC_MICROCHIP_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
        }
        EnableThemeDialogTexture(hWnd, ETDT_ENABLETAB);
        return TRUE;

    case WM_NOTIFYFORMAT:
        return NFR_UNICODE;

    case WM_COMMAND:
        {
            int wID = LOWORD (wParam);
            BOOL enableApply = FALSE; // whether change of options should enable Apply button

            switch (wID) 
            {
            case IDC_CHECK_SHOW_ALL:                
                if (!newOptions->NotifyRfidlerArrFlash()) {
                    SendMessage(GetDlgItem(hWnd, IDC_RFID_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetNotifyRfidlerArrFlash(TRUE);
                    enableApply = TRUE;
                }
                if (!newOptions->NotifyBootArrFlash()) {
                    SendMessage(GetDlgItem(hWnd, IDC_BOOT_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetNotifyBootArrFlash(TRUE);
                    enableApply = TRUE;
                }
                if (!newOptions->NotifyMicrochipArrFlash()) {
                    SendMessage(GetDlgItem(hWnd, IDC_MICROCHIP_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetNotifyMicrochipArrFlash(TRUE);
                    enableApply = TRUE;
                }
                break;
            case IDC_CHECK_SHOW_NONE:
                if (newOptions->NotifyRfidlerArrFlash()) {
                    SendMessage(GetDlgItem(hWnd, IDC_RFID_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetNotifyRfidlerArrFlash(FALSE);
                    enableApply = TRUE;
                }
                if (newOptions->NotifyBootArrFlash()) {
                    SendMessage(GetDlgItem(hWnd, IDC_BOOT_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetNotifyBootArrFlash(FALSE);
                    enableApply = TRUE;
                }
                if (newOptions->NotifyMicrochipArrFlash()) {
                    SendMessage(GetDlgItem(hWnd, IDC_MICROCHIP_ARR_FLASH), BM_SETCHECK, BST_CHECKED, 0);
                    newOptions->SetNotifyMicrochipArrFlash(FALSE);
                    enableApply = TRUE;
                }
                break;
            case IDC_RFID_ARR_FLASH:
                newOptions->SetNotifyRfidlerArrFlash((BOOL) IsDlgButtonChecked(hWnd, IDC_RFID_ARR_FLASH));
                enableApply = TRUE;
                break;
            case IDC_BOOT_ARR_FLASH:
                newOptions->SetNotifyBootArrFlash((BOOL) IsDlgButtonChecked(hWnd, IDC_BOOT_ARR_FLASH));
                enableApply = TRUE;
                break;
            case IDC_MICROCHIP_ARR_FLASH:
                newOptions->SetNotifyMicrochipArrFlash((BOOL) IsDlgButtonChecked(hWnd, IDC_MICROCHIP_ARR_FLASH));
                enableApply = TRUE;
                break;
            }
            if (enableApply && hWndParentDlg) {
                SendMessage(hWndParentDlg, WM_APP, 0, 0);
            }
        }
        break;
    }

    return handled;
}


BOOL CALLBACK OptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    const int KNumPropPages = 2;
    static HWND hWndOptionsPage[KNumPropPages] = { NULL, NULL };
    static DeviceTracker *DevTracker;
    static MonOptions   *newOptions;
    static BOOL         ApplyEnabled[KNumPropPages] = { FALSE, FALSE };
    static int          currPage = 0;
    static HWND         hWndTab;
    int handled = 0;

    // Option DlgProc works with tab control
    switch (iMsg) {
    case WM_INITDIALOG:
        for (int i = 0; i < KNumPropPages; i++) {
            ApplyEnabled[i] = FALSE;
        }
        DevTracker = (DeviceTracker*) lParam;
        // new copy of current options
        newOptions = new MonOptions(DevTracker->GetOptions());
        hWndTab = GetDlgItem(hWnd, IDC_TABOPTIONS);

        currPage = 0;
        hWndOptionsPage[0] = InitShowControls(newOptions, hWndTab);
        hWndOptionsPage[1] = InitNotificationControls(newOptions, hWndTab);
        { // mark Tab control as parent
            LONG_PTR value = GetWindowLongPtr(hWndTab, GWL_EXSTYLE);
            value |= WS_EX_CONTROLPARENT;
            SetWindowLongPtr(hWndTab, GWL_EXSTYLE, value);
        }
        return TRUE;

    case WM_COMMAND:
        {
            int wID = LOWORD (wParam);

            switch (wID) 
            {
            case IDOK:
                DevTracker->SetOptions(*newOptions, DeviceTracker::SetAll);
                EndDialog(hWnd, 0);
                handled++;
                break;
            case IDCANCEL:
                EndDialog(hWnd, 1);
                handled++;
                break;
            case IDC_APPLY:
                EnableWindow(GetDlgItem(hWnd, IDC_APPLY), FALSE);
                ApplyEnabled[currPage] = FALSE;
                // only apply changes to currently visible options page
                DevTracker->SetOptions(*newOptions,
                    (currPage == 0) ? DeviceTracker::SetShowOptions : DeviceTracker::SetNotifyOptions);
                handled++;
                break;
            case IDC_CHECK_SHOW_ALL:                
            case IDC_CHECK_SHOW_NONE:
                // send to the options page
                PostMessage(hWndOptionsPage[currPage], iMsg, wParam, lParam);
                handled++;
                break;
            }
        }
        break;

    case WM_APP: // enable apply button
        if (!ApplyEnabled[currPage]) {
            EnableWindow(GetDlgItem(hWnd, IDC_APPLY), TRUE);
            ApplyEnabled[currPage] = TRUE;
        }
        handled++;
        break;

    case WM_NOTIFY:
        if (wParam == IDC_TABOPTIONS) {
            NMHDR *pNm = (NMHDR *) lParam;
            switch(pNm->code) {
            case TCN_SELCHANGE:
                int index = TabCtrl_GetCurSel(hWndTab);
                switch (index) {
                case 0:
                case 1:
                    // flip tabs
                    ShowWindow(hWndOptionsPage[0], index == 0 ? SW_SHOWNA :SW_HIDE);
                    ShowWindow(hWndOptionsPage[1], index == 1 ? SW_SHOWNA :SW_HIDE);
                    currPage = index;
                    EnableWindow(GetDlgItem(hWnd, IDC_APPLY), ApplyEnabled[currPage]);
                    break;
                }
                handled++;
                break;
            }
        }
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        handled++;
        break;

    case WM_DESTROY:
        for (int i = 0; i < KNumPropPages; i++) {
            if (hWndOptionsPage[i]) {
                DestroyWindow(hWndOptionsPage[i]);
                hWndOptionsPage[i] = NULL;
            }
        }
        break;
    }

    // 1 = handled here, 0 = pass to default handling
    return handled;
}   /* OptionsDlgProc() */


/* retry wrapper around GetModuleFileName() with growing buffer */
BOOL GetProgramFilename(TCHAR **fname)
{
    unsigned sz = 128;
    DWORD    res;
    TCHAR    *f;

    do {
        sz *= 2;
        f = (TCHAR *) calloc(sz, sizeof(TCHAR));
        if (f == NULL) {
            /* OOM */
            return FALSE;
        }

        res = GetModuleFileName(NULL, f, sz);
        if ((res > 0) && (res < (sz - 1))) {
            *fname = f;
            return TRUE;
        }

        free(f);
        f = NULL;
    } while ( (res != 0) && (sz < 32768) );

    /* function failed or buffer is ridiculously large */
    return FALSE;
}


void CheckProgramShortcuts(const wchar_t *shortcut, BOOL *aDeskLinkExists, BOOL *aStartlinkExists)
{
    // check if shortcuts already exist
    *aDeskLinkExists = CheckLinkname(shortcut, CSIDL_DESKTOP);
    *aStartlinkExists = CheckLinkname(shortcut, CSIDL_STARTUP);
}


BOOL CheckLinkname(const wchar_t *shortcut, int csidl)
{
    wchar_t *linkname = CreateLinkname(shortcut, csidl);
    BOOL result = FALSE;

    if (linkname) {
        if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(linkname)) {
            result = TRUE;
        }
        free(linkname);
    }
    return result;
}


wchar_t *CreateLinkname(const wchar_t *shortcut, int csidl)
{
    ITEMIDLIST* pidl;
    wchar_t lpPath[1024];
    wchar_t *link = NULL;

    HRESULT hRes = SHGetSpecialFolderLocation(NULL, csidl, &pidl);
    if (SUCCEEDED(hRes)) {
        if (SHGetPathFromIDList( pidl, lpPath )) {
            // +3 for '\' and double nil terminator
            size_t len = 3 + wcslen(lpPath) + wcslen(shortcut);
            link = (wchar_t *) calloc(len, sizeof(wchar_t));
            if (link) {
                wcscpy_s(link, len, lpPath);
                wcscat_s(link, len, _T("\\"));
                wcscat_s(link, len, shortcut);
                link[len-1] = 0; // repair the nil placed by calloc & zapped by _s() functions
            }
        }

        // release memory for PIDL list
        IMalloc* palloc;
        hRes = SHGetMalloc(&palloc);
        palloc->Free( (void*)pidl );
        palloc->Release();
    }
    return link;
}


void CreateOrBreakLink(IShellLink *psl, const wchar_t *shortcut, int csidl, BOOL aMakeShortcut)
{
    IPersistFile *ppf;
    wchar_t     *linkname = CreateLinkname(shortcut, csidl);
    HRESULT     hres;

    if (linkname) {
#ifdef _DEBUG
        PrintDebugStatus(_T("linkname = %s\n"), linkname);
#endif
        if (aMakeShortcut) {
            hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
            if (SUCCEEDED(hres)) {
                // Save the link by calling IPersistFile::Save.
                hres = ppf->Save(linkname, FALSE);
#ifdef _DEBUG
                if (!SUCCEEDED(hres)) {
                    PrintDebugStatus(_T("IID_IPersistFile.Save fail 0x%x\n"), hres);
                }
#endif
                ppf->Release();
#ifdef _DEBUG
            } else {
                PrintDebugStatus(_T("QueryInterface(IID_IPersistFile... fail 0x%x\n"), hres);
#endif
            }
        } else {
            // use shell to remove shortcut
            SHFILEOPSTRUCT sfos;

            ZeroMemory(&sfos, sizeof(sfos));
            sfos.wFunc = FO_DELETE;
            sfos.pFrom = linkname;
            sfos.fFlags = FOF_FILESONLY | FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI;
            SHFileOperation(&sfos);
        }
        free(linkname);
    }
}


void CreateProgramShortcuts(const TCHAR *fname, const wchar_t *shortcut, BOOL aDesktopShortcut, BOOL aStartupShortcut,
    BOOL aDeskLinkExists, BOOL aStartlinkExists)
{
    const wchar_t *desc = _T("RFIDler Monitor");

    if (fname && ((aDesktopShortcut != aDeskLinkExists) || (aStartupShortcut != aStartlinkExists))) {
        IShellLink *psl;
        HRESULT hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
            IID_IShellLink, (void**)&psl);

        if (SUCCEEDED(hres)) {
            // Set the path to the shortcut target and add the description. 
            hres = psl->SetPath(fname); 
#ifdef _DEBUG
            if (!SUCCEEDED(hres)) {
                PrintDebugStatus(_T("SetPath(%s) fail 0x%x\n"), fname, hres);
            }
#endif
            hres = psl->SetDescription(desc); 
#ifdef _DEBUG
            if (!SUCCEEDED(hres)) {
                PrintDebugStatus(_T("SetDescription(%s) fail 0x%x\n"), desc, hres);
            }
#endif

            // create or remove shortcuts
            if (aDesktopShortcut != aDeskLinkExists) {
                CreateOrBreakLink(psl, shortcut, CSIDL_DESKTOP, aDesktopShortcut);
            }
            if (aStartupShortcut != aStartlinkExists) {
                CreateOrBreakLink(psl, shortcut, CSIDL_STARTUP, aStartupShortcut);
            }
            psl->Release();
        }
    }
}


BOOL CALLBACK InstallConfigDlgProc (
    HWND hWnd,
    UINT iMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    const wchar_t *shortcut = _T("RFIDler Monitor.lnk");
    static DeviceTracker *DevTracker;
    static TCHAR        *fname = NULL;
    static BOOL         deskLinkExists;
    static BOOL         startlinkExists;

    int handled = 0;

    // Dialog for configuring program shortcuts
    switch (iMsg) {
    case WM_INITDIALOG:
        DevTracker = (DeviceTracker*) lParam;
        // init displayed path
        if (!fname) {
            GetProgramFilename(&fname);
        }
        if (fname) {
            SetWindowText(GetDlgItem(hWnd, IDC_PROGPATH), fname);
        }
        // init radio buttons set deskLinkExists & startlinkExists
        CheckProgramShortcuts(shortcut, &deskLinkExists, &startlinkExists);
        CheckRadioButton(hWnd, IDC_DESKNO, IDC_DESKYES, deskLinkExists ? IDC_DESKYES : IDC_DESKNO);
        CheckRadioButton(hWnd, IDC_STARTNO, IDC_STARTYES, startlinkExists ? IDC_STARTYES : IDC_STARTNO);
        return TRUE;

    case WM_COMMAND:
        {
            int wID = LOWORD (wParam);
            //int wNotification = HIWORD(wParam);
            //HWND hChild = (HWND) lParam;

            switch (wID) 
            {
            case IDOK:
                CreateProgramShortcuts(fname, shortcut,
                    BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_DESKYES), 
                    BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_STARTYES),
                    deskLinkExists, startlinkExists);
                EndDialog(hWnd, 0);
                handled++;
                break;
            case IDCANCEL:
                EndDialog(hWnd, 1);
                handled++;
                break;
            case IDC_APPLY:
                CreateProgramShortcuts(fname, shortcut,
                    BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_DESKYES), 
                    BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_STARTYES),
                    deskLinkExists, startlinkExists);
                EnableWindow(GetDlgItem(hWnd, IDC_APPLY), FALSE);
                handled++;
                break;
            case IDC_DESKNO:
            case IDC_DESKYES:
            case IDC_STARTNO:
            case IDC_STARTYES:
                if ( (deskLinkExists != (BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_DESKYES))) ||
                        (startlinkExists != (BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_STARTYES)))) {
                    EnableWindow(GetDlgItem(hWnd, IDC_APPLY), TRUE);
                } else {
                    EnableWindow(GetDlgItem(hWnd, IDC_APPLY), FALSE);
                }
                break;
            }
        }
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        handled++;
        break;

    case WM_DESTROY: // dialog closing
        ReleaseString(fname);
        handled++;
        break;
    }

    // 1 = handled here, 0 = pass to default handling
    return handled;
}   /* InatallConfigDlgProc() */


void ReleaseString(TCHAR *&string)
{
    if (string) {
        free(string);
        string = NULL;
    }
}

// program description and copyright licensing info
static const TCHAR *helpTitle = _T("Help About RFIDLer Monitor");
static const TCHAR *helpText =
    _T("RFIDler LF appears to the computer as a USB serial port, and works with a standard \r\n")
    _T("Windows driver for USB serial ports, usbser.sys.\r\n")
    _T("\r\n")
    _T("This RFIDler Monitor presents a list of the currently connected RFIDler LF devices. \r\n")
    _T("If an RFIDler LF is connected and working it tells you what COM port name Windows \r\n")
    _T("has assigned to the device. If the RFIDler is connected in Bootloader mode, waiting \r\n")
    _T("to be programmed this is shown too. (Some other Microchip development tools in \r\n")
    _T("Bootloader mode look the same to the Monitor and are therefore shown as well.)\r\n")
    _T("\r\n")
    _T("Options add to the display such things as Microchip development boards such as UBW32,\r\n")
    _T("other serial ports or modems, similar serial devices remembered by Windows but not\r\n")
    _T("currently connected. \r\n")
    _T("\r\n")
    _T("\r\n")
    _T("Copyright (c) 2014 Anthony Naggs, all rights reserved.\r\n")
    _T("\r\n")
    _T("Limited assignment of rights under the 'BSD 2-Clause License':\r\n")
    _T("\r\n")
    _T("Redistribution and use in source and binary forms, with or without modification, are \r\n")
    _T("permitted provided that the following conditions are met:\r\n")
    _T("\r\n")
    _T("1. Redistributions of source code must retain the above copyright notice, this list of\r\n")
    _T("     conditions and the following disclaimer.\r\n")
    _T("\r\n")
    _T("2. Redistributions in binary form must reproduce the above copyright notice, this list\r\n")
    _T("     list of conditions and the following disclaimer in the documentation and/or other\r\n")
    _T("     materials provided with the distribution.\r\n")
    _T("\r\n")
    _T("THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \r\n")
    _T("\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \r\n")
    _T("LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR \r\n")
    _T("A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT \r\n")
    _T("HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, \r\n")
    _T("SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT \r\n")
    _T("LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, \r\n")
    _T("DATA, ORPROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY \r\n")
    _T("THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \r\n")
    _T("(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE \r\n")
    _T("OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.");


INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /* IDD_HELP_ABOUT */

    lParam; // suppress unreferenced parameter warning

    switch (iMsg) {
    case WM_INITDIALOG:
        SetWindowText(hDlg, helpTitle);
        SetWindowText(GetDlgItem(hDlg, IDC_HELP_TEXT), helpText);
        SetFocus( GetDlgItem (hDlg, IDOK));
        // return TRUE  unless you set the focus to a control
        return FALSE;

    case WM_COMMAND: 
        switch (LOWORD(wParam)) {
        case IDOK :
	    EndDialog (hDlg, wParam);
	    /* handled message */
	    return 1;
        }
        break;
    }

    return 0;
}   /* AboutDlgProc() */


void SetStatusBarPartitions(HWND hWndStatusBar, int parts)
{
    int sbWidths[4] = { 150, 350, 510, 0 };
    SendMessage(hWndStatusBar, SB_SETPARTS, parts, (LPARAM) sbWidths);
}


void LVColumnClickAndSort(DeviceTracker *DevTracker, NM_LISTVIEW *pNm)
{
    int oldOrder = DevTracker->GetViewSortOrder();
    int newOrder = pNm->iSubItem;

    // user clicked on column header, so sort by chosen criterion
    if (oldOrder != newOrder) {
        DevTracker->SetViewSortOrder(newOrder);
        ListView_SortItems(pNm->hdr.hwndFrom, DeviceInfo::CompareProc,
            (LPARAM)(newOrder));

        // move sort order mark between columns
        HWND hWndHdr = ListView_GetHeader(pNm->hdr.hwndFrom);
        if (hWndHdr) {
            HDITEM hdrItem;
            hdrItem.mask = HDI_FORMAT;
            if (Header_GetItem(hWndHdr, oldOrder, &hdrItem) && (hdrItem.fmt & (HDF_SORTUP | HDF_SORTDOWN))) {
                hdrItem.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
                Header_SetItem(hWndHdr, oldOrder, &hdrItem);
            }
            if (Header_GetItem(hWndHdr, newOrder, &hdrItem)) {
                hdrItem.fmt |= HDF_SORTUP;
                Header_SetItem(hWndHdr, newOrder, &hdrItem);
            }
        }
    }
}


void LVInfoTip(LPNMLVGETINFOTIP pGetInfoTip)
{
    /* LVN_GETINFOTIP is broken as lParam member field is zero, not the value
        set when the List View Item was created.
        So we need to ask for the lParam, to get the pointer to DeviceInfo,
        so we know what infotip text to send back!
    */
    DeviceInfo *dev = DevInfoFromListItem(pGetInfoTip->hdr.hwndFrom, pGetInfoTip->iItem);

    if (dev) {
        // with our DeviceInfo pointer we can now get the tooltip message
        const TCHAR *infoTip = dev->InfoTip();

        StringCchPrintf(pGetInfoTip->pszText, pGetInfoTip->cchTextMax, _T("%s"), infoTip);
#ifdef _DEBUG
        PrintDebugStatus(_T("InfoTip = %s\n"), infoTip);
#endif
    }
}


void LVRightClickContextMenu(HINSTANCE hInst, LPNMITEMACTIVATE lpnmitem)
{
#ifdef _DEBUG
    PrintDebugStatus(_T("NM_RCLICK iItem = %i, iSubItem = %i, lParam = %p, point = %i,%i\n"),
        lpnmitem->iItem, lpnmitem->iSubItem, lpnmitem->lParam,
        lpnmitem->ptAction.x, lpnmitem->ptAction.y);
#endif
    /* 
        lpnmitem->lParam points to something, but doesn't appear to be useful.
        Need to map mouse coordinates to our Device Info.
    */
    DeviceInfo *dev = DevInfoFromListPoint(lpnmitem->hdr.hwndFrom,
        lpnmitem->iItem, lpnmitem->ptAction);

    if (dev) {
        ContextMenuPopup(hInst, lpnmitem->hdr.hwndFrom, dev, lpnmitem->ptAction);
    }
}


void LVSelectedItemContextMenu(HINSTANCE hInst, HWND hWndLV)
{
    int count = ListView_GetItemCount(hWndLV);
    int i;

    for (i = 0; i < count; i++) {
        if (ListView_GetItemState(hWndLV, i, LVIS_SELECTED)) {
            DeviceInfo *dev = NULL;
            POINT cliPt;

            dev = DevInfoFromListItem(hWndLV, i);
            if (dev && ListView_GetItemPosition(hWndLV, i, &cliPt)) {
                cliPt.x += 40;  // move menu origin to not hide item text
                cliPt.y += 8;
                ContextMenuPopup(hInst, hWndLV, dev, cliPt);
            }
            break;
        }
    }
}


void LVEmptyViewTest(NMLVEMPTYMARKUP *emptyMarkup)
{
    // BUG: this doesn't have any effect
    StringCchCopy(emptyMarkup->szMarkup, L_MAX_URL_LENGTH, _T("No connected RFIDlers"));
    emptyMarkup->dwFlags = EMF_CENTERED;
}


void ContextMenuPopup(HINSTANCE hInst, HWND hWndLV, DeviceInfo *dev, POINT scrPt)
{
    assert(dev);

    // context menu
    LPCWSTR lpMenuName = NULL;

    ClientToScreen(hWndLV, &scrPt);

    switch (dev->DeviceType()) {
    case DevRfidler:
    case DevMicroDevBoard:
    case DevOtherSerial:
        lpMenuName = MAKEINTRESOURCE(IDR_PORT_CONTEXT);
        break;
    case DevMicroBoot:
    case DevRfidUnconfig:
    case DevMicroUnconfig:
    default:
        lpMenuName = MAKEINTRESOURCE(IDR_DEV_CONTEXT);
        break;
    }

    HMENU hMenu = LoadMenu(hInst, lpMenuName);
    if (hMenu) {
        HMENU hMenuTrackPopup  = GetSubMenu(hMenu, 0);

        // ensure device is not freed whilst we are using it
        dev->LockForContextMenu();

        int selection = TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            scrPt.x, scrPt.y, 0, hWndLV, NULL);
#ifdef _DEBUG
        PrintDebugStatus(_T("Popup selection = %i\n"), selection);
#endif
        if (selection > 0) {
            const TCHAR *strings[5] = { NULL, NULL, NULL, NULL, NULL };
            int i = 0;

            switch(selection) {
            case ID_CONTEXT_COPYDEV_DETAILS: // skip Bootloader typename, as it just repeats DisplayName info
                strings[i++] = dev->DisplayName();
                strings[i++] = dev->StateName();
                strings[i++] = dev->LocationString();
                strings[i++] = dev->SerialNumber();
                break;
            case ID_CONTEXT_COPYPORT_DETAILS:
                strings[i++] = dev->DisplayName();
                strings[i++] = dev->DevTypeName();
                strings[i++] = dev->StateName();
                strings[i++] = dev->LocationString();
                strings[i++] = dev->SerialNumber();
                break;
            case ID_CONTEXT_COPYPORT_NAME:
                strings[i++] = dev->PortName();
                break;
            //case ID_CONTEXT_COPYALL_DETAILS: // possible future fn, needs ListView iterator & string info buffers
            }

            // menu selection copies to Clipboard?
            if (i > 0) {
                int j = 0;
                size_t len = 0;

                for (j = 0; j < i; j++) {
                    // count the tab field separator, & NIL
                    len += 1 + wcslen(strings[j]);
                }

                HGLOBAL hglbCopy;
                hglbCopy = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(TCHAR));

                if (hglbCopy && OpenClipboard(hWndLV)) {
                    EmptyClipboard();

                    // Lock the handle and copy the text to the buffer. 
 
                    LPTSTR lptstrCopy = (LPTSTR) GlobalLock(hglbCopy); 

                    for (j = 0; j < i; j++) {
                        if (j > 0) {
                            StringCchCat(lptstrCopy, len, _T("\t"));
                            StringCchCat(lptstrCopy, len, strings[j]);
                        } else {
                            StringCchCopy(lptstrCopy, len, strings[j]);
                        }
                    }

                    GlobalUnlock(hglbCopy); 
 
                    // Place the handle on the clipboard.
#ifdef _UNICODE
                    SetClipboardData(CF_UNICODETEXT, hglbCopy);
#else
                    SetClipboardData(CF_TEXT, hglbCopy);
#endif

                    CloseClipboard();
                }
            }
        }

        dev->UnlockForContextMenu();
    }
}


// List View utility functions ...
DeviceInfo *DevInfoFromListItem(HWND hWndLV, int iItem)
{
    if (iItem >= 0) {
        LVITEM lvi;

        ZeroMemory(&lvi, sizeof(LVITEM));
        lvi.iItem = iItem;
        lvi.mask = LVIF_PARAM;
        if (ListView_GetItem(hWndLV, &lvi)) {
            return (DeviceInfo *)lvi.lParam;
        }
    }
    return NULL;
}


DeviceInfo *DevInfoFromListPoint(HWND hWndLV, int iItem, POINT pt)
{
    LVHITTESTINFO lvhti;

    // iItem is already valid if clicked on left hand colmun
    // otherwise get item id from point first
    if (iItem < 0) {
        lvhti.pt = pt;
        ListView_SubItemHitTest(hWndLV, &lvhti);

#ifdef _DEBUG
        PrintDebugStatus(_T("LVHITTESTINFO iItem = %i, iSubItem = %i, flags = %x\n"),
            lvhti.iItem, lvhti.iSubItem, lvhti.flags);
#endif

        if (lvhti.flags & LVHT_ONITEM) {
            iItem = lvhti.iItem;
        }
    }

    if (iItem >= 0) {
        return DevInfoFromListItem(hWndLV, iItem);
    }
    return NULL;
}


// duplicate a substring, max of length wide chars
// protects when copying registry strings that are not NIL terminated
wchar_t* wcs_dupsubstr(const wchar_t* string, size_t length)
{
    size_t alloclen; // = (string[length] == L'\0') ? length : (length + 1);
    wchar_t* buff = NULL;
    
    if (string != NULL) {
        for (alloclen = 0; (alloclen < length) && (string[alloclen] != L'\0'); alloclen++)
            ;

        if (alloclen > 0) {
            buff = (wchar_t*)calloc(alloclen + 1, sizeof(wchar_t));

            if (buff) {
                wcsncpy_s(buff, alloclen + 1, string, alloclen);
            }
        }
    }
    return buff;
}


//static 
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
        aPortNumber, aContainerId, aFriendlyName, aHardwareId, aUsbHub, aUsbPort, aUsbValid, aScanId, aDevNext,
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
    switch (devType) {
    case DevRfidler:        iCountRfidlers--; break;
    case DevMicroDevBoard:  iCountDevBoards--; break;
    case DevMicroBoot:      iCountBootloaders--; break;
    case DevRfidUnconfig:   iCountUnconRfidlers--; break;
    case DevMicroUnconfig:  iCountUnconDevBoards--; break;
    case DevOtherSerial:    iCountOtherSerial--; break;
    default:                break;
    }
}


void DeviceInfo::IncDeviceTypeCount()
{
    devPresent = TRUE;
    switch (devType) {
    case DevRfidler:        iCountRfidlers++; break;
    case DevMicroDevBoard:  iCountDevBoards++; break;
    case DevMicroBoot:      iCountBootloaders++; break;
    case DevRfidUnconfig:   iCountUnconRfidlers++; break;
    case DevMicroUnconfig:  iCountUnconDevBoards++; break;
    case DevOtherSerial:    iCountOtherSerial++; break;
    default:                break;
    }
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
    case DevRfidler:
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
    case DevMicroBoot:
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
    case DevRfidUnconfig:
        devImage = DevImgRfidlerUnconfig;
        break;
    case DevMicroUnconfig:
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
    case DevRfidler:
    case DevRfidUnconfig:
        return _T("RFIDler");
    case DevMicroDevBoard:
    case DevMicroUnconfig:
        return _T("dev board");
    case DevOtherSerial:
        return _T("serial");
    case DevMicroBoot:
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
    case DevRfidler:
    case DevMicroDevBoard:
    case DevOtherSerial:
        return devPortName;
    case DevMicroBoot:
        return _T("HID bootloader");
    case DevRfidUnconfig:
    case DevMicroUnconfig:
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

    switch (devType)
    {
    case DevRfidler:
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("RFIDler COM port"));
        break;
    case DevMicroDevBoard:
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("Microchip USB COM port\nDevelopment board"));
        break;
    case DevMicroBoot:
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer),
            _T("Microchip HID bootloader\nRFIDler or other development board"));
        break;
    case DevRfidUnconfig:
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("RFIDler, COM port drivers not installed"));
        break;
    case DevMicroUnconfig:
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), 
            _T("Microchip USB COM port, COM port drivers not installed"));
        break;
    case DevOtherSerial:
        wcscpy_s(infotipBuffer, ARRAYSIZE(infotipBuffer), devFriendlyName);
        break;
    default:
        assert(0);
        infotipBuffer[0] = 0;
    }

    // describe serial port type, based on Windows GUID for ports, modem or multiport serial card
    switch (devSerialType) {
    case SerialPort:
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nSerial Port"));
        break;
    case SerialModem:
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nModem"));
        break;
    case SerialMultiport:
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nMultiport Serial Device"));
        break;
    case SerialNone:
    default:
        break; // nothing to say
    }

    if (devHardwareId) {
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nHardwareId = "));
        wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), devHardwareId);
    }

    if (devSerialNumber) {
        if (devIsWinSerial) {
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nWindows generated serial number"));
        } else {
            wcscat_s(infotipBuffer, ARRAYSIZE(infotipBuffer), _T("\nBuilt-in device serial number"));
        }
    }
    return infotipBuffer;
}


// (class static) callback function given to ListView_SortItems
// negative result if dev1 precedes dev2, positive for dev2 ahead of dev1
int CALLBACK DeviceInfo::CompareProc(DeviceInfo *dev1, DeviceInfo *dev2, LPARAM primaryKey)
{
    int result = 0;

    switch (primaryKey) {
    case 0: // default ordering: port name/number, then devtype, serialnumber
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
    case 1: // device type
        result = (int)dev1->devType - (int)dev2->devType;
        break;
    case 2: // device state
        result = (int)dev1->devState - (int)dev2->devState;
        break;
    case 3: // USB location
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
    case 4: // serialnumber
        break;
    }

    // finally, use serialnumber to distinguish
    if (result == 0) {
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
    mOptions.SaveViewStyleButton(mHWndMain, viewButton);

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


BOOL DeviceTracker::AddViewItem(const TCHAR *aName, enum DevImage aImage, const TCHAR *aDevType, 
            const TCHAR *aState, const TCHAR *aUsbLocation, const TCHAR *aSerialNumber, LPARAM lParam)
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


void DeviceTracker::UpdateViewItemPortName(const TCHAR *aName, LPARAM lParam)
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


void DeviceTracker::UpdateViewItemIconAndState(enum DevImage aImage, const TCHAR *aState, LPARAM lParam)
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


void DeviceTracker::UpdateViewItemIconAndType(enum DevImage aImage, const TCHAR *aType, LPARAM lParam)
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


void DeviceTracker::UpdateViewItemState(const TCHAR *aState, LPARAM lParam)
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


void DeviceTracker::UpdateViewItemLocation(const TCHAR *aUsbLocation, LPARAM lParam)
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


void DeviceTracker::UpdateViewItemSerialNumber(const TCHAR *aSerialNumber, LPARAM lParam)
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


void DeviceTracker::InitListColumns(const TCHAR **columns, const int *widths, unsigned count)
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


void DeviceTracker::Initialize()
{
    // icons for device view
    const int iconList[] = { IDI_RFIDOKAY, IDI_RFIDBAD, IDI_RFIDREMOVE,
            IDI_RFIDBOOT, IDI_DEVBOARD, IDI_DEVBOARDREMOVE, IDI_DEVBOARDBAD,
            IDI_OTHERSERIALOK, IDI_OTHERSERIALREMOVE };
    // column headings for view
    const TCHAR *columns[] = { _T("Name"), _T("Device"), _T("State"), _T("USB Location"),
            _T("Serial number") };
    const int    colwidth[] = { 100, 70, 100, 100, 122 };


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

    DeviceInfo::SetDeviceTracker(this);

    // enable tooltips
    ListView_SetExtendedListViewStyle(mHWndListView, LVS_EX_INFOTIP  | LVS_EX_LABELTIP);

    // load & prepare icon with different counts of 'lit LEDs'
    mIcoMonitor00 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR00));
    mIcoMonitor01 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR01));
    mIcoMonitor02 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR02));
    mIcoMonitor03 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR03));
    mIcoMonitor10 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR10));
    mIcoMonitor11 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR11));
    mIcoMonitor12 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR12));
    mIcoMonitor13 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR13));
    mIcoMonitor20 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR20));
    mIcoMonitor21 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR21));
    mIcoMonitor22 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR22));
    mIcoMonitor23 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR23));
    mIcoMonitor30 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR30));
    mIcoMonitor31 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR31));
    mIcoMonitor32 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR32));
    mIcoMonitor33 = LoadIcon(mHInst, MAKEINTRESOURCE(IDI_MONITOR33));

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
        HDITEM hdrItem;
        hdrItem.mask = HDI_FORMAT;
        if (Header_GetItem(hWndHdr, mSortType, &hdrItem)) {
            hdrItem.fmt |= HDF_SORTUP;
            Header_SetItem(hWndHdr, mSortType, &hdrItem);
        }
    }

    // kick timer to do initial device scan
    KickDevScanTimer();

    if (DetermineAppNewIcon()) {
        // kick 1s timer to change icon 
        KickIconRefreshTimer();
    }
}


// Windows should cleanup resources on exit, but it is good practice to do our own.
void DeviceTracker::Cleanup()
{
    CancelArrivalTimer();
    CancelDevScanTimer();
    CancelIconRefreshTimer();
    mOptions.CancelRegSaveTimer(mHWndMain);

    if (mImageList) {
        ImageList_Destroy(mImageList);
    }
    if (mImageListSm) {
        ImageList_Destroy(mImageListSm);
    }

    if (mIcoMonitor00) {
        DestroyIcon(mIcoMonitor00);
    }
    if (mIcoMonitor01) {
        DestroyIcon(mIcoMonitor01);
    }
    if (mIcoMonitor02) {
        DestroyIcon(mIcoMonitor02);
    }
    if (mIcoMonitor03) {
        DestroyIcon(mIcoMonitor03);
    }
    if (mIcoMonitor10) {
        DestroyIcon(mIcoMonitor10);
    }
    if (mIcoMonitor11) {
        DestroyIcon(mIcoMonitor11);
    }
    if (mIcoMonitor12) {
        DestroyIcon(mIcoMonitor12);
    }
    if (mIcoMonitor13) {
        DestroyIcon(mIcoMonitor13);
    }
    if (mIcoMonitor20) {
        DestroyIcon(mIcoMonitor20);
    }
    if (mIcoMonitor21) {
        DestroyIcon(mIcoMonitor21);
    }
    if (mIcoMonitor22) {
        DestroyIcon(mIcoMonitor22);
    }
    if (mIcoMonitor23) {
        DestroyIcon(mIcoMonitor23);
    }
    if (mIcoMonitor30) {
        DestroyIcon(mIcoMonitor30);
    }
    if (mIcoMonitor31) {
        DestroyIcon(mIcoMonitor31);
    }
    if (mIcoMonitor32) {
        DestroyIcon(mIcoMonitor32);
    }
    if (mIcoMonitor33) {
        DestroyIcon(mIcoMonitor33);
    }

    // free device list
    {
        DeviceInfo *devPtr = mListDevices;

        while (devPtr) {
            devPtr = devPtr->DeviceNext();
        }
        mListDevices = NULL;
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
    static unsigned scanId = 31415926;
    SYSTEMTIME st;
    FILETIME   ft;

    GetSystemTime(&st);              // current system time (UTC)
    SystemTimeToFileTime(&st, &ft);  // file time format

    if (mOptions.ShowNonConfig()) {
        ScanIncludingUnconfigDevs(ft, scanId);
    } else {
        ScanBootDevices(ft, scanId);
        ScanSerialDevices(ft, scanId);
    }

    CleanupOrphanedDevices(ft, scanId);

    UpdateWndIconAndNotifications();
    scanId++;
}


BOOL DeviceTracker::GetDeviceClassGUID(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, GUID &DevGuid)
{
    DWORD size;
    BOOL result;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &DEVPKEY_Device_ClassGuid,
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
        TCHAR guidStringBuffer[40];
        result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_CLASSGUID,
            &type, (PBYTE) guidStringBuffer, sizeof(guidStringBuffer), &size) && (type == REG_SZ);
        // convert guid string to GUID (Unicode build only)
        if (result && (S_OK != IIDFromString(guidStringBuffer, &DevGuid))) {
            result = FALSE;
        }
    }

    return result;
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


BOOL DeviceTracker::CheckDeviceId(const wchar_t *aHwId, DWORD size, const TCHAR *aRefHwId)
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
    SerialType aSerialType, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        enum DevType dType = DevUnknwown;

        // examine serial device
        if ((aSerialType == SerialPort) && CheckDeviceId(devInstanceId, size, szRfidlerHwUsbId)) {
            dType = DevRfidler;
        } else if ((aSerialType == SerialPort) && mOptions.ShowDevBoardsOrAnySerial() &&
                CheckDeviceId(devInstanceId, size, szMicrochipSerialHwUsbId)) {
            dType = DevMicroDevBoard;
        } else if (mOptions.ShowAnySerial()) {
            // note separation of COM or LPT ports occurs in AddOrUpdateDevice()
            dType = DevOtherSerial;
        }

        if (dType != DevUnknwown) {
            // Get RFIDler or Get Microchip USB Serial device details
            AddOrUpdateDevice(dType, DeviceInfoSet, DeviceInfoData, devInstanceId, size, 
                aSerialType, aNow, aScanId);
        }
    }
}


void DeviceTracker::CheckHidDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        enum DevType dType = DevUnknwown;

        if (CheckDeviceId(devInstanceId, size, szMicrochipBootHidId)) {
            // HID Bootloader
            dType = DevMicroBoot;
        } else if (CheckDeviceId(devInstanceId, size, szMicrochipBootHwUsbId)) {
            // USB parent of Bootloader, give us the USB port & hub
            dType = DevMicroBootShadow;
        }

        if (dType != DevUnknwown) {
            // device details
            AddOrUpdateDevice(dType, DeviceInfoSet, DeviceInfoData, devInstanceId, size, SerialNone, aNow, aScanId);
        }
    }
}


// if serial device does not yet have driver configured it has no class set
void DeviceTracker::CheckClassNoneDevice(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, FILETIME &aNow, unsigned aScanId)
{
    DWORD size = 0;
    wchar_t *devInstanceId = NULL;

    if (GetDeviceInstanceId(DeviceInfoSet, DeviceInfoData, &devInstanceId, &size)) {
        enum DevType dType = DevUnknwown;

        // check USB hardware id for unconfigured RFIDler, Microchip devboard
        if (CheckDeviceId(devInstanceId, size, szRfidlerHwUsbId)) {
            // Get RFIDler dev details
            dType = DevRfidUnconfig;
        } else if (mOptions.ShowDevBoardsOrAnySerial() &&
                CheckDeviceId(devInstanceId, size, szMicrochipSerialHwUsbId)) {
            // Get Microchip USB Serial device details
            dType = DevMicroUnconfig;
        }

        if (dType != DevUnknwown) {
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


void DeviceTracker::ScanBootDevices(FILETIME &aNow, unsigned aScanId)
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
    /* RFIDler & Microchip DevBoards are in GUID_DEVCLASS_PORTS
       'Show Any Serial' needs to include Modems & Multiport Serial devices
    */
    const GUID *serialGuid[] = { &GUID_DEVCLASS_PORTS, &GUID_DEVCLASS_MODEM, &GUID_DEVCLASS_MULTIPORTSERIAL };
    const SerialType serialTypes[] = { SerialPort, SerialModem, SerialMultiport };
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
        
                CheckSerialDevice(DeviceInfoSet, DeviceInfoData, serialTypes[i], aNow, aScanId);
            } // while

            SetupDiDestroyDeviceInfoList(DeviceInfoSet);
        }
    }
}


// returns DevPresent or DevAbsent
enum DevState DeviceTracker::GetDevPresentStatus(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    static  wchar_t     pdoNameBuffer[1024];
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


BOOL wcs_consumeprefix(wchar_t* String, const wchar_t* SubStr, wchar_t** OutStr, DWORD maxsize)
{
    size_t len = wcslen(SubStr);

    if ((len <= maxsize) && (0 == _wcsnicmp(String, SubStr, len))) {
        *OutStr = String + len;
        return TRUE;
    }
    *OutStr = NULL;
    return FALSE;
}


BOOL DeviceTracker::GetDevUsbLocation(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData, unsigned &usbHub, unsigned &usbPort)
{
    // XP get SPDRP_LOCATION_INFORMATION
    static  wchar_t     devLocationBuffer[1024];
    DWORD size;
    BOOL result;

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
            &type, (PBYTE) &devLocationBuffer, sizeof(devLocationBuffer), &size)
            && (type == REG_SZ);
    }

    if (result) {
        // typical string = "Port_#0001.Hub_#0006"
        wchar_t* str = NULL;

        size /= sizeof(wchar_t); // bytes to wchar
        if (wcs_consumeprefix(devLocationBuffer, L"Port_#", &str, size)) {
            usbPort = wcstoul(str, &str, 10);
            if ((errno == 0) && wcs_consumeprefix(str, L".Hub_#", &str, size - (str - devLocationBuffer))) {
                usbHub = wcstoul(str, &str, 10);
                if (errno == 0) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}


wchar_t *DeviceTracker::GetContainerId(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData)
{
    static  wchar_t containerIdBuffer[50];
    BOOL result;
    DWORD size;

#if defined(USE_SETUP_DEVICE_API_ADAPTATION)
    if (mSetupDiGetDevicePropertyW) {
        DEVPROPTYPE PropType;
        GUID guidTemp;
        result = mSetupDiGetDevicePropertyW(DeviceInfoSet,
                                        &DeviceInfoData,
                                        &DEVPKEY_Device_BaseContainerId,
                                        &PropType,
                                        (PBYTE)&guidTemp,
                                        sizeof(guidTemp),
                                        &size,
                                        0)
                    && (PropType == DEVPROP_TYPE_GUID);
        if (result) {
            // convert to string
            StringCbPrintf(containerIdBuffer, sizeof(containerIdBuffer),
                L"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
                guidTemp.Data1, guidTemp.Data2, guidTemp.Data3,
                guidTemp.Data4[0], guidTemp.Data4[1], guidTemp.Data4[2],
                guidTemp.Data4[3], guidTemp.Data4[4], guidTemp.Data4[5],
                guidTemp.Data4[6], guidTemp.Data4[7]);
        }
    } else {
#elif defined(USE_SETUP_DEVICE_REGISTRY)
    {
#endif
        DWORD type;
        result = SetupDiGetDeviceRegistryProperty(DeviceInfoSet, &DeviceInfoData, SPDRP_BASE_CONTAINERID,
            &type, (PBYTE) &containerIdBuffer, sizeof(containerIdBuffer), &size)
            && (type == REG_SZ);
    }

    // on success dupe the string
    return result ? _wcsdup(containerIdBuffer) : NULL;
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
void DeviceTracker::GetSerialnumber(const wchar_t *devInstanceId, DWORD size, BOOL &isWinSerial,
    wchar_t **serialNumber, wchar_t **devId)
{
    // extract & dupe serial number
    size_t i;
    size_t serpos = 0;
    
    isWinSerial = FALSE;

    // find last '\' in string, carefully in case no zero terminator
    for (i = 0; (i < size) && devInstanceId[i] != L'\0'; i++) {
        switch (devInstanceId[i]) {
        case L'&':
            isWinSerial = TRUE;
            break;
        case L'\\':
            serpos = i + 1;
            isWinSerial = FALSE;
            break;
        }
    }

    // extract serialnumber
    // Note prefix part of string is similar to hardwareid string, but lacks e.g. USB device revision
    if (serpos) {        
        *serialNumber = wcs_dupsubstr(devInstanceId + serpos, size - serpos);
        *devId = wcs_dupsubstr(devInstanceId, serpos - 1);
    }
}


/*
   NB serial numbers are not necessarily unique!!!
   If device does not carry one preprogrammed, windows generates based on dev type, & USB hub/port.
   (Or PCI location etc..)
   Similar devices can therefore have the same serial number at different times, affects us
   when showing not currently present devices.
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
            case DevRfidler:
            case DevRfidUnconfig:
                if ((dType == DevRfidler) || (dType == DevRfidUnconfig)) {
                    cmpSernum = TRUE;
                }
                break;
            case DevMicroDevBoard:
            case DevMicroUnconfig:
                if ((dType == DevMicroDevBoard) || (dType == DevMicroUnconfig)) {
                    cmpSernum = TRUE;
                }
                break;
            case DevMicroBoot:
            case DevMicroBootShadow:
                if ((dType == DevMicroBoot) || (dType == DevMicroBootShadow)) {
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


DeviceInfo *DeviceTracker::FindDevMatchByContainerId(enum DevType aDevType, wchar_t *aContainerId)
{
    DeviceInfo *devList = mListDevices;

    while (devList) {
        if (aDevType == devList->DeviceType()) {
            const wchar_t *temp = devList->ContainerId();
            if (temp && !wcscmp(temp, aContainerId)) {
                return devList;
            }
        }
        devList = devList->DeviceNext();
    }
    return NULL;
}


void DeviceTracker::AddOrUpdateDevice(enum DevType aDevType, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA &DeviceInfoData,
        const wchar_t *devInstanceId, DWORD size, SerialType aSerialType, FILETIME &aNow, unsigned aScanId)
{
    enum DevState   dState;
    wchar_t         *portname = NULL;
    wchar_t         *serialNumber = NULL;
    wchar_t         *hardwareId = NULL;
    wchar_t         *containerId = NULL;
    wchar_t         *friendlyname = NULL;
    unsigned        usbHub = 0, usbPort = 0;
    BOOL            added = FALSE;
    BOOL            usbValid = FALSE;
    BOOL            isWinSerial = FALSE;
    DeviceInfo      *devItem = NULL;
    int             portnumber = -1;

    if (!mOptions.ShowNotPresent()) {
        dState = DevPresent;
    } else {
        // get device present status: DevPresent or DevAbsent
        dState = GetDevPresentStatus(DeviceInfoSet, DeviceInfoData);
    }
    
    // find serial number element of devInstanceId
    if (aDevType != DevMicroBootShadow) {
        GetSerialnumber(devInstanceId, size, isWinSerial, &serialNumber, &hardwareId);
    }

    if ((aDevType == DevMicroBoot) || (aDevType == DevMicroBootShadow)) {
        // get ContainerId - indicates merged object for HID & USB aspects of Bootloader
        containerId = GetContainerId(DeviceInfoSet, DeviceInfoData);
        devItem = FindDevMatchByContainerId(DevMicroBoot, containerId);
    } else {
        devItem = FindDevMatchBySernum(aDevType, serialNumber);
    }

    // get more details for new or Present device
    if ((!devItem) || (dState == DevPresent) || (aDevType == DevMicroBootShadow)) {
        // USB hub & port are easy to get for USB/... devices but not for HID/...
        if (DevMicroBoot != aDevType) {
            usbValid = GetDevUsbLocation(DeviceInfoSet, DeviceInfoData, usbHub, usbPort);
        }

        if ( (DevRfidler == aDevType) || (DevMicroDevBoard == aDevType) || (DevOtherSerial == aDevType)) {
            wchar_t *valpos = NULL;
            // get COM port name
            portname = GetPortname(DeviceInfoSet, DeviceInfoData);
            if (DevOtherSerial == aDevType) {
                if (!portname || (0 != wcsncmp(portname, _T("COM"), 3))) {
                    // LPT port presumably => not interesting
                    return;
                }
                // get friendlyname
                friendlyname = GetFriendlyName(DeviceInfoSet, DeviceInfoData);
            }
            if (portname && wcs_consumeprefix(portname, _T("COM"), &valpos, wcslen(portname))) {
                portnumber = wcstoul(valpos, NULL, 10);
            }
        }
    }

    if (devItem) {
        // device in list, so update connected state, COM port name, USB location, ..
        devItem->UpdateDevice((aDevType == DevMicroBootShadow) ? DevMicroBoot : aDevType,
            dState, aNow, portname, portnumber, usbHub, usbPort, usbValid, serialNumber,
            aScanId, isWinSerial);
    } else {
        DeviceInfo *item;

        // create new device object, & add to display
        item = DeviceInfo::NewDevice(
            (aDevType == DevMicroBootShadow) ? DevMicroBoot : aDevType, dState, aNow,
            serialNumber, portname, friendlyname, hardwareId, portnumber, containerId, usbHub, usbPort,
            usbValid, aScanId, mListDevices, isWinSerial, aSerialType);

        if (item) {
            added = TRUE;
        }
    }

    if (!added) {
        ReleaseString(portname);
        ReleaseString(serialNumber);
        ReleaseString(containerId);
        ReleaseString(friendlyname);
        ReleaseString(hardwareId);
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

                if ( ((dType == DevMicroDevBoard) || (dType == DevMicroUnconfig))
                        && !mOptions.ShowDevBoardsOrAnySerial() ) {
                    unlink = TRUE;
                } else if ( ((dType == DevRfidUnconfig) || (dType == DevMicroUnconfig))
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
            item = item->DeleteDevice();
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

        if ( ((dType == DevMicroDevBoard) || (dType == DevMicroUnconfig))
                && !mOptions.ShowDevBoardsOrAnySerial()) {
            unlink = TRUE;
        } else if ( (dType == DevOtherSerial) && !mOptions.ShowAnySerial() ) {
            unlink = TRUE;
        } else if ( ((dType == DevRfidUnconfig) || (dType == DevMicroUnconfig))
                && !mOptions.ShowNonConfig() ) {
            unlink = TRUE;
        } else if ((dState == DevAbsent) && !mOptions.ShowNotPresent()) {
            unlink = TRUE;
        } else if ((dState == DevRemoved) && !mOptions.ShowRecentDisc()) {
            unlink = TRUE;
        }

        if (unlink) {
            item = item->DeleteDevice();
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
                KickIconRefreshTimer();
            } else {
                SetStatusBarPartitions(mHWndStatusBar, 2);
            }
        }
        if (mOptions.ShowAnySerial() != aOptions.ShowAnySerial()) {
            mInitialiseAnySerial = TRUE; // next scan should handle other serial ports as per initial scan
        }

        // copy new values, and setup saving changes to the registry 
        mOptions.SetShowOptionsAndRegistrySave(mHWndMain, aOptions, showSettingsChanged);
    }

    if ((SetAll == setmode) || (SetNotifyOptions == setmode)) {
        // copy new values, and setup saving changes to the registry 
        mOptions.SetNotifyOptionsAndRegistrySave(mHWndMain, aOptions);
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
   for X minutes. Set by KArrivalOrRemovalTimeLimit.
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
        case DevArrived:
            // update display with elapsed time
            if (item->UpdateTimeInState(now, mOptions.ShowNotPresent(), KArrivalOrRemovalTimeLimit)) {
                dState = item->DeviceState();
                // still in this state?
                if ((dState == DevRemoved) || (dState == DevArrived)) {
                    mDevicesInArrivalState = TRUE;
                }
            } else {
                unlink = TRUE;
            }
            break;
        }

        if (unlink) {
            item = item->DeleteDevice();
        } else {
            item = item->DeviceNext();
        }
    }
}


void DeviceTracker::UpdateWndIconAndNotifications()
{
    if (mNeedIconUpdate) {
        mNeedIconUpdate = FALSE;
        if (DetermineAppNewIcon()) {
            // kick 1s timer to change timer
            KickIconRefreshTimer();
        }
    }
    if (mNeedFlashWindow) {
        FlashWindow(mHWndMain, FALSE);
        mNeedFlashWindow = FALSE;
    }
}


 /*
  Windows bug: sometimes small icon updates but big taskbar one doesn't 
  Workaround is just to keep refreshing ...
  Unfortunately at some point Windows Shell seems to only use a cached icon
  on the Taskbar. At least the small icon in corner of the window changes
  as intended.
  */
void DeviceTracker::AppIconRefresh()
{
    static TCHAR statusBuffer[1024];

    // update App icon and cancel timer
    DeviceTracker::CancelIconRefreshTimer();

    SetClassLong(mHWndMain, GCL_HICON, (LONG) mCurrIcon);


    // also update status bar - mHWndStatusBar
    if (mHWndStatusBar) {
        // status bar could has counts for Dev boards, Bootloaders, etc
        int count = DeviceInfo::GetCountRfidlers();

        if (count) {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("%u RFIDler%s connected"), count,
                (count == 1) ? _T("") : _T("s"));
        } else {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("No RFIDlers connected"));
        }
        SendMessage(mHWndStatusBar, SB_SETTEXT, 0, (LPARAM) statusBuffer);

        count = DeviceInfo::GetCountBootloaders();
        if (count) {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("%u HID Bootloader%s connected"), count,
                (count == 1) ? _T("") : _T("s"));
        } else {
            StringCbPrintf(statusBuffer, sizeof(statusBuffer), _T("No HID Bootloaders connected"));
        }
        SendMessage(mHWndStatusBar, SB_SETTEXT, 1, (LPARAM) statusBuffer);

        if (mOptions.ShowDevBoardsOrAnySerial()) {
            count = DeviceInfo::GetCountDevBoards();

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


/* 
    Main window icon changes depending on how many RFIDler or Bootloader devices
    are connected.
    Updates mCurrIcon, returns TRUE if changed.
*/
BOOL DeviceTracker::DetermineAppNewIcon()
{
    HICON newIcon = 0;
    int portCount = DeviceInfo::GetCountRfidlers() + DeviceInfo::GetCountDevBoards();
    int bootCount = DeviceInfo::GetCountBootloaders();

    portCount = min(portCount, 3);
    bootCount = min(bootCount, 3);

    HICON iconChoice[4][4] = {
        { mIcoMonitor00, mIcoMonitor01, mIcoMonitor02, mIcoMonitor03, },
        { mIcoMonitor10, mIcoMonitor11, mIcoMonitor12, mIcoMonitor13, },
        { mIcoMonitor20, mIcoMonitor21, mIcoMonitor22, mIcoMonitor23, },
        { mIcoMonitor30, mIcoMonitor31, mIcoMonitor32, mIcoMonitor33, },
    };

    newIcon = iconChoice[portCount][bootCount];

    if (newIcon != mCurrIcon) {
        mCurrIcon = newIcon;
        return TRUE;
    }
    return FALSE;
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


void DeviceTracker::KickIconRefreshTimer()
{
    if (!mTimerIconRefresh) {
        // wait at least 1s, as changes often bunch together seems to fix issue with Taskbar icon glitching
        SetTimer (mHWndMain, mTimerIconRefresh = ICON_REFRESH_MAGICNUMBER, 1000, NULL);
    }
}


void DeviceTracker::CancelIconRefreshTimer()
{
    if (mTimerIconRefresh) {
        KillTimer(mHWndMain, mTimerIconRefresh);
        mTimerIconRefresh = 0;
    }
}


BOOL DeviceTracker::CheckInitialScanFlag(enum DevType dType)
{
    switch(dType)
    {
    case DevRfidler:
        return mInitialiseRfidler;
    case DevMicroDevBoard:
        return mInitialiseMicroSer;
    case DevMicroBoot:
        return mInitialiseRfidler;
    case DevOtherSerial:
        return mInitialiseAnySerial;
    case DevRfidUnconfig:
    case DevMicroUnconfig:
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

        if (dType == DevRfidler) {
            mNeedIconUpdate = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyRfidlerArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
        } else if (dType == DevMicroDevBoard) {
            mNeedIconUpdate = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseMicroSer && mOptions.NotifyMicrochipArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
        } else if (dType == DevMicroBoot) {
            mNeedIconUpdate = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyBootArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
        }
        // future feature, arrival notifications for DevOtherSerial ? 
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

        if (dType == DevRfidler) {
            mNeedIconUpdate = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyRfidlerArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
        } else if (dType == DevMicroDevBoard) {
            mNeedIconUpdate = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseMicroSer && mOptions.NotifyMicrochipArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
        } else if (dType == DevMicroBoot) {
            mNeedIconUpdate = TRUE;
            // notify if wanted (except if Options just changed)
            if (!mInitialiseRfidler && mOptions.NotifyBootArrFlash()) {
                mNeedFlashWindow = TRUE;
            }
        }
        // future feature, removal notifications for DevotherSerial?
    }
}


// store / retrieve setting from registry in SOFTWARE\\TonyNaggs\\RfidlerMonitor
static const TCHAR *KRegistryBase = _T("SOFTWARE");
static const TCHAR *KRegVendor = _T("TonyNaggs");
static const TCHAR *KRegProgramName = _T("RfidlerMonitor");

//static const TCHAR *KRegKeyMask = _T("Mask");
//static const TCHAR *KRegKeyOptions = _T("Options");
static const TCHAR *KRegKeyShowFlags = _T("ShowFlags");
static const TCHAR *KRegKeyNotifyFlags = _T("Notifications");
static const TCHAR *KRegKeySortOrder = _T("SortOrder");
static const TCHAR *KRegKeyViewStyle = _T("ViewStyle");
static const TCHAR *KRegKeyWinPosX = _T("WinPosX");
static const TCHAR *KRegKeyWinPosY = _T("WinPosY");
static const TCHAR *KRegKeyWinSizeCX = _T("WinSizeCX");
static const TCHAR *KRegKeyWinSizeCY = _T("WinSizeCY");



void MonOptions::ReadRegistryValues()
{
    // read registry values
    HKEY hk1, hk2, hk3;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, KRegistryBase, 0, 
            KEY_ALL_ACCESS, &hk1)) {
        // create vendor and application keys
        if (ERROR_SUCCESS == RegOpenKeyEx(hk1, KRegVendor, 0,
                KEY_ALL_ACCESS, &hk2)) {
            if (ERROR_SUCCESS == RegOpenKeyEx(hk2, KRegProgramName, 0,
                    KEY_ALL_ACCESS, &hk3)) {
                DWORD temp;
                DWORD valtype;
                DWORD valsize;

                valsize = sizeof(temp);
                // what optional stuff to show
                RegQueryValueEx(hk3, KRegKeyShowFlags, 0, &valtype, (BYTE*)&temp, &valsize);
                if (REG_DWORD == valtype) {
                    optShowFlags = temp;
                }
                // whether to flash window or chime
                RegQueryValueEx(hk3, KRegKeyNotifyFlags, 0, &valtype, (BYTE*)&temp, &valsize);
                if (REG_DWORD == valtype) {
                    optNotifyFlags = temp;
                }

                RegQueryValueEx(hk3, KRegKeyWinPosX, 0, &valtype, (BYTE*)&temp, &valsize);
                if (REG_DWORD == valtype) {
                    optWindowPlace.left = temp;
                    RegQueryValueEx(hk3, KRegKeyWinPosY, 0, &valtype, (BYTE*)&temp, &valsize);
                    if (REG_DWORD == valtype) {
                        optWindowPlace.top = temp;
                        RegQueryValueEx(hk3, KRegKeyWinSizeCX, 0, &valtype, (BYTE*)&temp, &valsize);
                        if (REG_DWORD == valtype) {
                            optWindowPlace.right = temp;
                            RegQueryValueEx(hk3, KRegKeyWinSizeCY, 0, &valtype, (BYTE*)&temp, &valsize);
                            if (REG_DWORD == valtype) {
                                optWindowPlace.bottom = temp;
                                optHaveWindowPlace = TRUE;
                            }
                        }
                    }
                }
                RegQueryValueEx(hk3, KRegKeySortOrder, 0, &valtype, (BYTE*)&temp, &valsize);
                if ((REG_DWORD == valtype) && (temp <= lvDispMaxSort)) {
                    optViewSortOrder = temp;
                } else {
                    // save good value at some point
                    temp = optViewSortOrder;
                    RegSetValueEx(hk3, KRegKeySortOrder, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                }
                RegQueryValueEx(hk3, KRegKeyViewStyle, 0, &valtype, (BYTE*)&temp, &valsize);
                if (REG_DWORD == valtype) {
                    switch (temp) {
                    case ID_VIEW_LARGE_ICONS:
                    case ID_VIEW_SMALL_ICONS:
                    case ID_VIEW_DETAILS:
                    case ID_VIEW_TILES:
                        optViewStyleButton = temp; break; // valid value
                    default: // save good value at some point
                        temp = optViewStyleButton;
                        RegSetValueEx(hk3, KRegKeyViewStyle, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        break;
                    }
                }

                RegCloseKey(hk3);
            }
            RegCloseKey(hk2);
        }
        RegCloseKey(hk1);
    }
}


// aShowSettingsChanged - out parameter
void MonOptions::SetShowOptionsAndRegistrySave(HWND hWndMain, const MonOptions &newValues, BOOL &aShowSettingsChanged)
{
    // check & copy new options, setup auto-save
    if (optShowFlags != newValues.optShowFlags) {
        optShowFlags = newValues.optShowFlags;
        optNeedSaveShowFlags = TRUE;
        aShowSettingsChanged = TRUE;
        KickRegSaveTimer(hWndMain);
    }
}


void MonOptions::SetNotifyOptionsAndRegistrySave(HWND hWndMain, const MonOptions &newValues)
{
    // check & copy new options, setup auto-save

    // sound / window title flash notification settings
    if (optNotifyFlags != newValues.optNotifyFlags) {
        optNotifyFlags = newValues.optNotifyFlags;
        optNeedSaveNotifyFlags = TRUE;
        KickRegSaveTimer(hWndMain);
    }
}


void MonOptions::RegistrySaveChangedValues(HWND hWndMain)
{
    if (optNeedSaveFlags) {
        HKEY hk1, hk2, hk3;
        DWORD disp;

        if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, KRegistryBase, 0, 
                KEY_ALL_ACCESS, &hk1)) {
            // create vendor and application keys
            if (ERROR_SUCCESS == RegCreateKeyEx(hk1, KRegVendor, 0, _T(""),
                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk2, &disp)) {
                if (ERROR_SUCCESS == RegCreateKeyEx(hk2, KRegProgramName, 0, _T(""),
                        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk3, &disp)) {
                    DWORD temp;

                    if (optNeedSaveShowFlags) {
                        temp = optShowFlags;
                        RegSetValueEx(hk3, KRegKeyShowFlags, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        optNeedSaveShowFlags = FALSE;
                    }
                    if (optNeedSaveNotifyFlags) {
                        temp = optNotifyFlags;
                        RegSetValueEx(hk3, KRegKeyNotifyFlags, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        optNeedSaveNotifyFlags = FALSE;
                    }
                    if (optNeedSaveWindowPlace) {
                        temp = optWindowPlace.left;
                        RegSetValueEx(hk3, KRegKeyWinPosX, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        temp = optWindowPlace.top;
                        RegSetValueEx(hk3, KRegKeyWinPosY, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        temp = optWindowPlace.right;
                        RegSetValueEx(hk3, KRegKeyWinSizeCX, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        temp = optWindowPlace.bottom;
                        RegSetValueEx(hk3, KRegKeyWinSizeCY, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        optNeedSaveWindowPlace = FALSE;
                    }
                    if (optNeedSaveViewSortOrder) {
                        temp = optViewSortOrder;
                        RegSetValueEx(hk3, KRegKeySortOrder, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        optNeedSaveViewSortOrder = FALSE;
                    }
                    if (optNeedSaveViewStyleButton) {
                        temp = optViewStyleButton;
                        RegSetValueEx(hk3, KRegKeyViewStyle, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
                        optNeedSaveViewStyleButton = FALSE;
                    }

                    RegCloseKey(hk3);
                }
                RegCloseKey(hk2);
            }
            RegCloseKey(hk1);
        }
    }
    CancelRegSaveTimer(hWndMain);
}


BOOL MonOptions::GetWindowInfo(RECT &rc) const
{
    if (optHaveWindowPlace) {
        rc = optWindowPlace;
        return TRUE;
    }
    return FALSE;
}


void MonOptions::SaveWindowInfo(HWND hWndMain, const RECT &rc)
{
    if ((rc.left != optWindowPlace.left) || (rc.top != optWindowPlace.top) ||
            (rc.right != optWindowPlace.right) || (rc.bottom != optWindowPlace.bottom)) {
        optWindowPlace = rc;
        optNeedSaveWindowPlace = TRUE;
        KickRegSaveTimer(hWndMain);
    }
}


void MonOptions::SaveViewSortOrder(HWND hWndMain, int order)
{
    if ((order != optViewSortOrder) && (order <= lvDispMaxSort)) {
        optViewSortOrder = order;
        optNeedSaveViewSortOrder = TRUE;
        KickRegSaveTimer(hWndMain);
    }
}


void MonOptions::SaveViewStyleButton(HWND hWndMain, int newStyle)
{
    if (newStyle != optViewStyleButton) {
        optViewStyleButton = newStyle;
        optNeedSaveViewStyleButton = TRUE;
        KickRegSaveTimer(hWndMain);
    }
}


void MonOptions::KickRegSaveTimer(HWND hWndMain)
{
    if (!optTimerRegistrySave) {
        // run timer after ~15s
        SetTimer (hWndMain, optTimerRegistrySave = REGISTRY_SAVE_MAGICNUMBER, 15000, NULL);
    }
}


void MonOptions::CancelRegSaveTimer(HWND hWndMain)
{
    if (optTimerRegistrySave) {
        KillTimer(hWndMain, optTimerRegistrySave);
        optTimerRegistrySave = 0;
    }
}


/* end of file rfidmonitor.cpp */