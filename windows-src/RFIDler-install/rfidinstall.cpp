/*
    Project: Windows RFIDler Driver Install v0.2
             Graphical interface to install driver .inf & .cat files
             for Aperture Labs RFIDler LF.

    File: rfidinstall.cpp (renamed from rfidinstall.c)

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


/* vvvvvv IMPORTANT BUILD NOTES vvvvvv

   Release build requires user to be local administrator in order to install/uninstall drivers.
   Also you must run correct bitness of binary for your Windows, x86 for 32-bit Windows on Intel x86
   or compatible processors, x64 for 64-bit Windows on AMD x64 or compatible processors.
   (This is due to Windows requirements, where important system data on 64-bit Windows is hidden
   from 32-bit applications.)

   Debug build requires Administrator rights only for actual install/uninstall actions, so
   the 'Need Admin rights' setting may be reconfigured from time to time.
   Note that to debug a program running as Administrator require a debugger that is running
   as Administrator too.

   win-compat.manifest must be included in the build, it proclaims that the installer is compatible
   with Windows Vista & Windows 7. It is needed for some install/uninstall behaviour, including
   to stop the Program Compatability Assistant (PCA) from appearing or interferring.
   Some older versions of the manifest tools warn about '81010002 Unrecognized Element "compatibility"'
   this is fine, and just means the tools are a little old. (Microsoft claim to have a hotfix for this
   http://support.microsoft.com/kb/2670561 but not do have an obvious way to actually obtain the fix.)

   ^^^^^^ IMPORTANT BUILD NOTES ^^^^^^
*/



#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <ShlObj.h>
#include <ShObjIdl.h>

#include <tchar.h>
#include <assert.h>
#include <SetupAPI.h>
#include <Cfgmgr32.h>
#include <CommCtrl.h>
#include <CommDlg.h>
#include <newdev.h>
#include <RegStr.h>
#include <devguid.h>
#include <Uxtheme.h>
#include <vssym32.h>
#include <strsafe.h>

#include "resource.h"


/*
 * This program needs to be linked with these libraries:
 * NB if any are missing from Windows SDK the Windows Driver Kit is required.
 */
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "newdev.lib")
// NB Cfgmgr32.lib is in the Windows Developer Kit / Driver Development Kit not the SDK
#pragma comment(lib, "Cfgmgr32.lib")
#pragma comment(lib, "uxtheme.lib")


/* enable use of "Visual Styles" */
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


/*
 Windows NT (Win 32 API) applications run on all 32 & 64 bit versions
 of Windows XP and later, and on a x86, x64 or IA64 CPU.

 However installing device drivers requires an installer for the
 specific CPU. (Requirement is to ensure Windows-on-Windows layer
 is not messing around with Windows directory path names, and
 therefore causing installation to go to the wrong directory.)

 Hence this tool can be built different CPUs, currently Intel x86 and AMD64

 Note Windows RT (running on ARM) is not supported (at the moment):
 I don't have tools to build for Windows RT, the installer UI is not Metro,
 and I don't have Windows RT hardware to test with.
 */
#if defined(_M_AMD64)
// AMD / Intel 64 bit version of x86 => Win 64
static const TCHAR *szAppName = _T("RFIDler LF Driver Install - x64");
#elif defined(_M_IA64)
// HP / Intel Itanium (IA64) => Win 64
// Note that the last version of tools to support IA64 was MS Visual Studio 2010.
static const TCHAR *szAppName = _T("RFIDler LF Driver Install - Itanium");
#error Itanium build not tested
#elif defined(_M_IX86)
// Intel x86 => Win 32
static const TCHAR *szAppName = _T("RFIDler LF Driver Install - x86");
#elif defined(_M_ARM)
#error ARM cpu build not supported
#else
#error build not supported
#endif


// details specific to RFIDler
#define RFIDLER_INF_NAME        _T("rfidlercdc.inf")
static const TCHAR *szRfidlerInfName = RFIDLER_INF_NAME;
static const TCHAR *szRfidlerHardwareId = _T("USB\\VID_1D50&PID_6098");

// name of AMD64 version of installer
#define RFIDLER_INSTALLER64_NAME    _T("rfidlerinstall-x64.exe")
static const TCHAR *szRfidlerInstallerX64 = RFIDLER_INSTALLER64_NAME;


// action for each enumerated RFIDler
enum UpdateAction {
    MarkNonPresentForReinstall,
    UninstallDriverWinXP,
    DebugLogDevice,
};

// tests to try on Windows Version Info
enum WinVersion {
    WinAtLeastVista,
    WinAtLeast7,
};

// config & result info for install / uninstall thread
typedef struct {
    BOOL    rebootRequired;
    int     uninstallType;
    TCHAR   *infpath;
    DWORD   insError;
    HWND    hWnd;
    BOOL    devConnected;
} InstallInfo;


static void MoveMainWindow(HWND hWnd, HINSTANCE hInst);
static INT_PTR CALLBACK InstallerDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static void StartOrStopProgressMarquee(HWND hWnd, HWND hWndProgBar, BOOL bStart, ITaskbarList3* pTbList, BOOL bFail);
static void EnableAndFocusOnFinishButton(HWND hWnd);
static INT_PTR CALLBACK AboutDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static UINT_PTR CALLBACK OFNHookCheckFilenameProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

static void ReportStatus(HWND hWndStatus, const TCHAR *format, ...);
static ATOM RegisterMainWindow (HINSTANCE hInstance);
static BOOL FindInfPath(HWND hWnd, TCHAR **aPath);
static BOOL GetProgramFilename(TCHAR **fname);
static BOOL IsSafeToInstall(DWORD dwTimeout);
static DWORD WINAPI DriverInstallThreadProc(LPVOID lpParameter);
static DWORD WINAPI DriverUninstallThreadProc(LPVOID lpParameter);
static BOOL UserSearchForInfFile(HWND hWnd, TCHAR **aPath, TCHAR *aInitialPath);
static void UpdateDriverWithAction(InstallInfo *pInsInfo, const GUID *classGuid, enum UpdateAction action);
static BOOL CheckHardwareIdMatch(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *DeviceInfoData, const TCHAR *szHardwareId);
static void MarkDeviceConfigForReinstall(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *DeviceInfoData);
static BOOL TestFileNameAndPath(const TCHAR *basePath, const TCHAR *fileName, TCHAR **outPath, const TCHAR **subDirList);
static TCHAR *GetWinDir();
static BOOL CheckIfInstalled();
static void TrimDirectoryLevel(TCHAR *namebuff, size_t dirLen);
static BOOL TestPathAndFileNameHelper(TCHAR *namebuff, size_t newsz, const TCHAR *basePath, 
    const TCHAR *fileName, const TCHAR *subdir);

#if !defined(_WIN64)
static BOOL IsWow64();
static BOOL IsSystemAMD64();
#endif
BOOL CheckWindowsVersion(enum WinVersion);

#if defined(_DEBUG)
static void PrintDebugStatus(const TCHAR *format, ...);
#endif


// private internal WM_ notifications
#define WM_PRIVATE_DRIVER_UPDATE_PROGRESS       (WM_APP + 426)
#define WM_PRIVATE_DRIVER_UPDATE_COMPLETE       (WM_APP + 427)
#define WM_PRIVATE_DRIVER_UNINSTALL_COMPLETE    (WM_APP + 428)


/* real code begins here ... */

int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PSTR szCmdLine,
    int iCmdShow
)
{
    ATOM ClassId;
    INITCOMMONCONTROLSEX ccInit;

    // remove unreferenced parameter warnings
    hPrevInstance;
    szCmdLine;
    iCmdShow;

    /* Initialisation */
    ClassId = RegisterMainWindow (hInstance);

    if (!ClassId) {
        MessageBox(NULL, _T("Unable to create main window"), szAppName, MB_OK | MB_ICONWARNING);
        return 3;
    }

    // we use the progress bar from 'Common Controls'
    ZeroMemory(&ccInit, sizeof(ccInit));
    ccInit.dwSize = sizeof(ccInit);
    ccInit.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&ccInit);

    // simply use DialogBox to show window
    return (int) DialogBoxParam (hInstance, MAKEINTRESOURCE(IDD_INSTALL), 0, InstallerDlgProc, (LPARAM) hInstance);
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
    WndClass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_RFIDINSTALL));
    WndClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH) GetStockObject (LTGRAY_BRUSH);
    WndClass.lpszMenuName  = NULL;
    WndClass.lpszClassName = _T("RFIDinstall");
    WndClass.hIconSm       = NULL;

    return RegisterClassEx (&WndClass);
}   /* RegisterMainWindow() */



// printf formatted messages to report area of installer's window
void ReportStatus(HWND hWndStatus, const TCHAR *format, ...)
{
    HRESULT hr;
    static TCHAR msgbuff[1024];
    va_list argptr;
    va_start(argptr, format);

    hr = StringCbVPrintf(msgbuff, sizeof(msgbuff), format, argptr);
    if (SUCCEEDED(hr)) {
        SendMessage (hWndStatus, LB_ADDSTRING, 0, (LPARAM) msgbuff);
    }
}


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


void MoveMainWindow(HWND hWnd, HINSTANCE hInst)
{
    RECT rc;

    // find out where CW_USEDEFAULT would place new window (not available for dialogs)
    if (GetWindowRect(hWnd, &rc)) {
        // make invisible window the same size as this, positioned with CW_USEDEFAULT
        // NB need to reference a valid Window class
        HWND hW = CreateWindow(_T("RFIDinstall"), _T("Invisible Window"), WS_OVERLAPPEDWINDOW,
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


INT_PTR CALLBACK InstallerDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /* statics to keep state between Windows messages */
    static HINSTANCE  hInst = 0;
    static HWND     hWndStatus; // control to log status messages to
    static HWND     hRebootButton;
    static HWND     hWndProg;   // progress bar
    static BOOL     isWow64 = FALSE;
    static BOOL     isSafe = FALSE;
    static BOOL     installing = FALSE; // set if install or uninstall background thread is running
    static UINT     TbCreatedNotification = 0;
    static ITaskbarList3* pTbList = NULL;
    /* struct to pass to installer/uninstaller thread */
    static InstallInfo     insInfo = { FALSE, 0, NULL, ERROR_SUCCESS, NULL, FALSE };

#if !defined(_WIN64)
    const int KWow64TimerMagicNumber = 76;
#endif

    /* locals */
    int  handled = 0;

    lParam; // suppress unreferenced parameter warnings in release build

    switch (iMsg) {
    case WM_INITDIALOG:	/* from CreateDialog() */
        hInst = (HINSTANCE) lParam;
        hWndStatus = GetDlgItem(hWnd, IDC_STATUS);
        hRebootButton = GetDlgItem(hWnd, IDC_REBOOT);
        hWndProg = GetDlgItem(hWnd, IDC_INST_PROGRESS);
        SetWindowText(hWnd, szAppName);
        insInfo.hWnd = hWnd;
        insInfo.uninstallType = 0;
#if defined(_DEBUG)
        ShowWindow(GetDlgItem(hWnd, IDC_TESTBUTTON), SW_NORMAL);
#endif

        // Check for Windows >= 7
        if (CheckWindowsVersion(WinAtLeast7)) {
            TbCreatedNotification = RegisterWindowMessage(TEXT("TaskbarButtonCreated"));
            if (TbCreatedNotification) {
                // obscurely documented secret sauce to actually get the notification
                ChangeWindowMessageFilterEx(hWnd, TbCreatedNotification, MSGFLT_ALLOW, NULL);
            }
        }

        // enable/disable buttons depending on Windows version
        if (!CheckWindowsVersion(WinAtLeastVista)) {
            // Full driver install works on XP, but not >= Win Vista
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), TRUE);
        }

#if !defined(_WIN64)
        // catch Win32 Installer running on Win x64
        isWow64 = IsWow64();
        if (isWow64) {
            ReportStatus(hWndStatus, _T("Security error: 32-bit Installer does work on 64-bit Windows"));
            EnableWindow(GetDlgItem(hWnd, IDC_INSTALL), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALL), FALSE);
            // wait until after window is drawn to display error in MessageBox
            SetTimer(hWnd, KWow64TimerMagicNumber, 500, NULL);
        }
#endif

        // restore window position & size, or use CW_USEDEFAULT positioning
        MoveMainWindow(hWnd, hInst);

        // return TRUE  unless you set the focus to a control
        return TRUE;

#if !defined(_WIN64)
    case WM_TIMER:
        // running Win32 installer on Windows x64 => MessageBox & then (non-debug build only) Quit 
        if ((wParam == KWow64TimerMagicNumber) && isWow64) {
            BOOL  isAMD64 = IsSystemAMD64();
            UINT  mbflags = MB_OK;
            TCHAR errorText[1024];
            TCHAR *errorTitle = _T("Incompatible version of RFIDler Installer");

            // kill one-shot timer
            KillTimer(hWnd, wParam);

            // compose message depending if system is AMD64
            StringCbPrintf(errorText, sizeof(errorText),
                _T("This (32-bit) Installer version is not allowed to change your (64-bit) system.\n\n")
                // NB %s below
                _T("%sithout the installer you can:\n")
                _T("1. connect your RFIDler LF,\n")
                _T("2. wait for driver install to fail,\n")
                _T("3. find the RFIDler in the Windows Device Manager\n")
                _T("4. update the driver there.\n")
                _T("(Install can fail due to security policy settings.)"),

                isAMD64 ? _T("For AMD or Intel x64 sytems you can run ") RFIDLER_INSTALLER64_NAME _T(" instead.\n\nAlternatively w")
                : _T("W") );

            MessageBox(hWndStatus, errorText, errorTitle, MB_ICONERROR | mbflags);
#if !defined(_DEBUG)
            // close this installer instance
            PostQuitMessage (0);
#endif

            handled++;
        }
        break;
#endif

    case WM_DESTROY: /* exit */
        PostQuitMessage (0);
        handled++;
        if (pTbList) {
            pTbList->Release();
            pTbList = NULL;
        }
        break;

    case WM_COMMAND: // handle button, menu selections, ...
        {
            int wID = LOWORD (wParam);
            int wNotification = HIWORD(wParam);
            BOOL    installAction = FALSE;

#if defined(_DEBUG)
            HWND hChild = (HWND) lParam;
            PrintDebugStatus(_T("wID %i  wNotification %i  hChild %p\n"), wID, wNotification, hChild);
#endif

            if (wNotification == BN_CLICKED) {
                switch (wID) {
                case IDC_INSTALL:
                    installAction = TRUE;
                    // fall through ...
                case IDC_UNINSTALL:
                case IDC_UNINSTALLDRIVER:
                    isSafe = IsSafeToInstall(500);
                    if (!isSafe) {
                        // Found New Hardware Wizard might be active
                        ReportStatus(hWndStatus, _T("Error: Windows Installer is running, retry when it has finished"));
                    } else if (installAction && !FindInfPath(hWnd, &insInfo.infpath)) {
                        ReportStatus(hWndStatus, _T("Error: Cannot find rfidlercrc.inf") );
                    } else if (installAction && CheckIfInstalled()) {
                        ReportStatus(hWndStatus, _T("Driver is already installed"));
                    } else {
                        {
                            // launch background thread for installer/uninstaller
                            HANDLE hThread;

                            // uninstall button id servers to distinguish the 2 uninstall functions
                            insInfo.uninstallType = wID;

                            hThread = CreateThread(NULL, 0,
                                        installAction ? DriverInstallThreadProc : DriverUninstallThreadProc,
                                        &insInfo, 0, NULL);

                            if(hThread) {
                                installing = TRUE;
                                // Okay: close handle & wait for install thread.
                                ReportStatus(hWndStatus,
                                    installAction ? _T("Installing driver and all connected RFIDlers ...") :
                                    _T("Uninstalling, this will take a few moments ...") );
                                CloseHandle(hThread);
                                // enable/show progress bar
                                StartOrStopProgressMarquee(hWnd, hWndProg, TRUE, pTbList, FALSE);
                                EnableWindow (GetDlgItem(hWnd, IDC_INSTALL), FALSE);
                                EnableWindow (GetDlgItem(hWnd, IDC_UNINSTALL), FALSE);
                                EnableWindow (GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), FALSE);
                                EnableWindow (GetDlgItem(hWnd, IDC_EXIT), FALSE);

                            } else {
                                ReportStatus(hWndStatus, _T("Error: %s failed to start (error %X)"),
                                    installAction ? _T("Install") : _T("Uninstall"),
                                    GetLastError());
                            }
                        }
                    }
                    if (!installing) {
                        MessageBeep(0xFFFFFFFF);
                    }
                    handled++;
                    break;
                case IDC_REBOOT:
                        // unlikely that this is needed for RFIDler, nevertheless ..
                        //
                        // attempt reboot - inform system that this is planned hardware install
                        //
                        // warning 28159 is a warning to rearchitect to avoid rebooting.  However,
                        // sometimes during device installation, a reboot is needed, so this warning
                        // is being suppressed for the call to InitiateSystemShutdownEx.
#if !defined(_DEBUG)
                    if (insInfo.rebootRequired) {
                        #pragma warning( suppress: 28159)
                        InitiateSystemShutdownEx(NULL,
                            _T("Reboot to complete RFIDler LF Driver install"),
                            0, FALSE, TRUE, REASON_PLANNED_FLAG | REASON_HWINSTALL);
                    }
                    EndDialog (hWnd, 0);
#endif
                    handled++;
                    break;

                case ID_HELP_ABOUT:
                    // pretty help information
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_HELP_ABOUT), hWnd, AboutDlgProc);
                    handled++;
                    break;

#if defined(_DEBUG)
                case IDC_TESTBUTTON:
                    {   // test various stuff: progress bar marquee mode
                        static BOOL marquee = FALSE;
                        static UINT testCount = 0;

                        ReportStatus(hWndStatus, _T("CheckIfInstalled() = %u"), CheckIfInstalled());

                        if (!FindInfPath(hWnd, &insInfo.infpath)) {
                            ReportStatus(hWndStatus, _T("Error: Cannot find rfidlercrc.inf") );
                        } else {
                            ReportStatus(hWndStatus, _T("Found %s"), insInfo.infpath );
                            if (insInfo.infpath) {
                                free(insInfo.infpath);
                                insInfo.infpath = NULL;
                            }
                        }

                        if (testCount++ == 1) {
                            ShowWindow(hRebootButton, SW_SHOWNORMAL);
                            EnableWindow(hRebootButton, TRUE);
                        }

                        marquee = !marquee;
                        // toggle marquee progress bar, & for Win >= 7 the progress bar on the icon
                        StartOrStopProgressMarquee(hWnd, hWndProg, marquee, pTbList, FALSE);
                    }
                    handled++;
                    break;
#endif
                case IDC_EXIT:
                    // do not allow close whilst install / uninstall thread is in-progress
                    if (!installing) {
                        EndDialog (hWnd, 0);
                    }
                    handled++;
                    break;
                }
            } // BN_CLICKED
        } // WM_COMMAND
        break;

    case WM_PRIVATE_DRIVER_UPDATE_PROGRESS:
        // wParam should indicate how the .inf file was copied
        ReportStatus(hWndStatus,
            wParam ? _T("%s copied by Windows ...") : _T("%s installed for connected RFIDlers ..."),
            szRfidlerInfName);
        handled++;
        break;

    case WM_PRIVATE_DRIVER_UPDATE_COMPLETE:
        installing = FALSE;
        if (insInfo.infpath) {
            free(insInfo.infpath);
            insInfo.infpath = NULL;
        }
        /* notification from installer thread */
        StartOrStopProgressMarquee(hWnd, hWndProg, FALSE, pTbList, (wParam == 0));

        EnableAndFocusOnFinishButton(hWnd);

        if (wParam) {
            if (insInfo.rebootRequired) {
                ReportStatus(hWndStatus, _T("Windows reboot required to complete installation"));
                ShowWindow(hRebootButton, SW_SHOWNORMAL);
                EnableWindow(hRebootButton, TRUE);
            } else {
                ReportStatus(hWndStatus, _T("Driver install complete"));
                if (!insInfo.devConnected) {
                    ReportStatus(hWndStatus, _T("Connect your RFIDler LF now"));
                }
            }
        } else {
            TCHAR *errmsg = NULL;
            switch (insInfo.insError)
            {
            case ERROR_FILE_NOT_FOUND:
                errmsg = _T("Error: ") RFIDLER_INF_NAME _T(" file not found");
                break;
            case ERROR_IN_WOW64:
                errmsg = _T("Error: x86 installer failed on 64-bit Windows");
                break;
            case ERROR_NO_MORE_ITEMS:
            case ERROR_FILE_EXISTS:
                errmsg = _T("Driver already installed");
                break;
            default:
                errmsg = _T("Error: driver install failed (error = %X)");
                break;
            }
            ReportStatus(hWndStatus, errmsg, insInfo.insError);
            MessageBeep(0xFFFFFFFF);
        }
        handled++;
        break;

    case WM_PRIVATE_DRIVER_UNINSTALL_COMPLETE:
        installing = FALSE;

        StartOrStopProgressMarquee(hWnd, hWndProg, FALSE, pTbList, (insInfo.insError != NO_ERROR));

        EnableAndFocusOnFinishButton(hWnd);

        if (insInfo.insError == NO_ERROR) {
            if (insInfo.rebootRequired) {
                ReportStatus(hWndStatus, _T("Windows reboot required to complete uninstall"));
                ShowWindow(hRebootButton, SW_SHOWNORMAL);
                EnableWindow(hRebootButton, TRUE);
            } else {
                ReportStatus(hWndStatus,
                    (insInfo.uninstallType == IDC_UNINSTALLDRIVER) ?
                    _T("Driver uninstall complete") : _T("Uninstall of RFIDlers complete"));
            }
        } else if (insInfo.insError == ERROR_FILE_NOT_FOUND) {
            ReportStatus(hWndStatus, _T("Uninstall complete, ") RFIDLER_INF_NAME _T(" was not found"));
        } else {
            ReportStatus(hWndStatus, _T("Error: %s failed (error = %X)"),
                (insInfo.uninstallType == IDC_UNINSTALLDRIVER) ?
                _T("Driver uninstall") : _T("Uninstall of RFIDlers"),
                insInfo.insError);
            MessageBeep(0xFFFFFFFF);
        }
        handled++;
        break;

    case WM_CLOSE:
        // do not allow close whilst install / uninstall is in-progress
        if (!installing) {
            EndDialog (hWnd, 0);
        }
        handled++;
        break;

    default:
#if defined(_DEBUG)
        if ((iMsg > 0x400) && hWndStatus) {
            if (TbCreatedNotification != iMsg) {
                ReportStatus(hWndStatus, _T("Info: received unhandled Msg (0x%X)"), iMsg);
            }
        }
#endif
        if ((TbCreatedNotification != 0) && (TbCreatedNotification == iMsg)) {
            // initial Taskbar button creation, or Windows Explorer has restarted
            pTbList = NULL;

            // if we get the interface then intialise (note using C++ here)
            if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&pTbList))) {
                pTbList->HrInit();
            }
        }
        break;
    }

    // 1 = handled here, 0 = pass to default handling
    return handled;
}   /* InstallerDlgProc() */


void StartOrStopProgressMarquee(HWND hWnd, HWND hWndProgBar, BOOL bStart, ITaskbarList3* pTbList, BOOL bFail)
{
    // comctrl32 v6 required; set & show or clear & hide progress bar in marquee mode
    SendMessage(hWndProgBar, PBM_SETMARQUEE, bStart, 0);
    ShowWindow(hWndProgBar, bStart ? SW_NORMAL : SW_HIDE);

    if (pTbList) {
        // Windows >= 7, start/stop marquee progress bar on the icon
        TBPFLAG tbFlags = TBPF_INDETERMINATE; // start marquee

        // stop marquee instead?
        if (!bStart) {
            if (!bFail) {
                // remove marquee
                tbFlags = TBPF_NOPROGRESS;
            } else {
                // set progress (default is 0, so red hardly shows)
                pTbList->SetProgressValue(hWnd, 80, 100);
                // stop marquee & display as red
                tbFlags = TBPF_ERROR;
            }
        }
        pTbList->SetProgressState(hWnd, tbFlags);
    }
}


void EnableAndFocusOnFinishButton(HWND hWnd)
{
    SetWindowText(GetDlgItem(hWnd, IDC_EXIT),_T("Finish"));
    EnableWindow (GetDlgItem(hWnd, IDC_EXIT), TRUE);

    // set dialog focus
    SendMessage(hWnd, WM_NEXTDLGCTL, (WPARAM)GetDlgItem(hWnd, IDC_EXIT), TRUE);
}


// program description and decide copyright licensing info
static const TCHAR *helpTitle = _T("Help About RFIDLer LF Driver Installer v0.2");
static const TCHAR *helpText =
    _T("RFIDler LF appears to the computer as a USB serial port, and works with a standard \r\n")
    _T("Windows driver for USB serial ports, usbser.sys.\r\n")
    _T("\r\n")
    _T("A simple driver information file (") RFIDLER_INF_NAME _T(") tells Windows which driver to use, and \r\n")
    _T("such details as manufacturer (Aperture Labs Ltd) and product names (RFIDler LF).\r\n")
    _T("\r\n")
    _T("This installer provides a simple interface to install or uninstall this file. (Note that \r\n")
    _T("complete uninstall only works on Windows XP, as Windows Vista & 7 keep a private \r\n")
    _T("copy.)\r\n")
    _T("\r\n")
    _T("Alternatively to using the installer you can connect your RFIDler LF, find it in Windows \r\n")
    _T("Device Manager (via the Control Panel) and update the driver there. This program \r\n")
    _T("needs to run as local Administrator in order to copy files to, or remove files from, \r\n")
    _T("Windows protected directories.\r\n")
    _T("\r\n")
    _T("Two versions of the installer are supplied: rfidlerinstall-x86.exe for 32-bit versions of \r\n")
    _T("Windows XP to Windows 7, and rfidlerinstall-x64.exe for 64-bit versions of Windows \r\n")
    _T("on x64 CPUs.\r\n")
    _T("\r\n")
    _T("Copyright (c) 2014-2015 Anthony Naggs, all rights reserved.\r\n")
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


// Find the rfidlercdc.inf file needed for driver install
BOOL FindInfPath(HWND hWnd, TCHAR **aPath)
{
    // NULL terminated list of subirectories to search
    const TCHAR *szIndSubdirList[] =
        { 
            _T("windows driver\\inf"), _T("inf"), 
            _T("..\\windows driver\\inf"), _T("..\\inf"), 
            NULL };
    TCHAR   *fname = NULL;
    BOOL    result = FALSE;

    // start with installer's file & directory path
    if (GetProgramFilename(&fname)) {
        TCHAR *split = _tcsrchr(fname, '\\');

        if (split) {
            split[1] = 0; // truncate after last '\'

            result = TestFileNameAndPath(fname, szRfidlerInfName, aPath, szIndSubdirList);

            // use Open File dialog to find Rfidler .inf file
            if (!result) {
                result = UserSearchForInfFile(hWnd, aPath, fname);
            }
        }
    }

    if (fname) {
        free(fname);
    }

    return result;
}


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


/*
    ask user thru Open File dialog to find missing rfidlercdc.inf

    Use GetOpenFileName() for WinXp compatibility. as IFileOpenDialog()
    is Vista & later only.
    */
BOOL UserSearchForInfFile(HWND hWnd, TCHAR **aPath, TCHAR *aInitialPath)
{
    DWORD        fileNameSize = (DWORD) _tcslen(aInitialPath);
    OPENFILENAME ofn;
    TCHAR        *name;
    BOOL         result = FALSE;

    if (fileNameSize < 1024) {
        fileNameSize = 1024;
    } else {
        fileNameSize += 100;
    }

    name = (TCHAR *)calloc(fileNameSize, sizeof(TCHAR));

    if (name) {
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = hWnd;
        ofn.lpstrInitialDir = aInitialPath;
        ofn.lpstrTitle = _T("Find ") RFIDLER_INF_NAME _T(" required for driver install");
        ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST
            | OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_EXPLORER | OFN_ENABLESIZING;
        ofn.nMaxFile = fileNameSize;
        ofn.lpstrFile = name;
        ofn.lpstrFilter = _T("Driver install info (*.inf)\0*.inf\0\0");
        ofn.lpstrDefExt = _T("inf");
        // Restrict selection to rfidlercdc.inf
        ofn.lpfnHook = OFNHookCheckFilenameProc;

        result = GetOpenFileName(&ofn);

        if (result) {
            // resize buffer, and transfer ownership,
            *aPath = (TCHAR *) realloc(name, (_tcslen(name) + 1) * sizeof(TCHAR));
        } else {
            DWORD err = CommDlgExtendedError();
            free(name);
        }
    }

    return result;
}


// enforce that selected file is named rfidlercdc.inf
UINT_PTR CALLBACK OFNHookCheckFilenameProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    int handled = 0;

    switch(uiMsg)
    {
    case WM_NOTIFY:
        {   
            LPOFNOTIFY notify = (LPOFNOTIFY) lParam;

            if (notify->hdr.code == CDN_FILEOK) {
                // file name is/is not okay?
                TCHAR * filenameElement = notify->lpOFN->lpstrFile + notify->lpOFN->nFileOffset;
                if (_tcscmp(filenameElement, szRfidlerInfName)) {
                    // Note DWL_MSGRESULT undeclared in Win64 builds, use DWLP_MSGRESULT instead
                    SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 1);
                }
                handled++;
            }
        }
        break;
    }
    return handled;
}


// helpers for TestFileNameAndPath()
void TrimDirectoryLevel(TCHAR *namebuff, size_t dirLen)
{
    if (dirLen < 2) {
        return;
    }

    // trim lowest directory unless we have hit "x:\" or "\\?\"
    if (namebuff[dirLen - 1] == L'\\') {
        if ((namebuff[dirLen - 2] == L':') || (namebuff[dirLen - 2] == L'?')) {
            return;
        }
        dirLen--;
    }
    while (dirLen) {
        if (namebuff[dirLen - 1] == L'\\') {
            namebuff[dirLen] = 0;
            break;
        }
        dirLen--;
    }
}


BOOL TestPathAndFileNameHelper(TCHAR *namebuff, size_t newsz, const TCHAR *basePath, 
    const TCHAR *fileName, const TCHAR *subdir)
{
    size_t dirLen = basePath ? _tcslen(basePath) : 0;

    // fill buffer with base path
    if (dirLen) {
        _tcsncpy_s(namebuff, newsz, basePath, _TRUNCATE);
    } else {
        namebuff[0] = 0;
    }

    if (subdir) {
        // handle "..\" in subdirectory
        while (!wcsncmp(subdir, _T("..\\"), 3)) {
            subdir += 3;
            TrimDirectoryLevel(namebuff, dirLen);
        }
        _tcsncat_s(namebuff, newsz, subdir, _TRUNCATE);
    }

    // ensure '\' at end of path
    dirLen = _tcslen(namebuff);
    if (namebuff[dirLen-1] != L'\\') {
        _tcsncat_s(namebuff, newsz, _T("\\"), _TRUNCATE);
    }
    
    _tcsncat_s(namebuff, newsz, fileName, _TRUNCATE);
#if defined(_DEBUG)
    PrintDebugStatus( _T("\"%s\"\n"), namebuff);
#endif
    if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(namebuff)) {
        return TRUE;
    }
    return FALSE;
}


/*
    check whether file exists,
    takes optional base directory, and list of subdirectories to search
    optional output the matching full filename

    If any subdirectories begin with ".." are they treated as moving up one level 
    of the base directory path.
*/
BOOL TestFileNameAndPath(const TCHAR *basePath, const TCHAR *fileName, TCHAR **outPath, const TCHAR **subDirList)
{
    BOOL result = FALSE;
    size_t baseLen = basePath ? _tcslen(basePath) : 0;
    size_t fileLen = _tcslen(fileName);
    size_t maxSubDirLen = 0;

    if (subDirList) {
        int i;
        for (i = 0; subDirList[i]; i++) {
            size_t dirLen = _tcslen(subDirList[i]);
            if (dirLen > maxSubDirLen) {
                maxSubDirLen = dirLen;
            }
        }
    }

    if ((maxSubDirLen + baseLen) == 0) {
        // simple test for file presence
        if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(fileName)) {
            result = TRUE;
        }
    } else {
        size_t newsz = 3 + baseLen + fileLen + maxSubDirLen;
        TCHAR *namebuff = (TCHAR *)calloc(newsz, sizeof(TCHAR));
        // beware, _tcsncpy_s & friends piss all over the 0s we asked calloc for :-(

        if (namebuff) {
            // first iter is base plus file, then search subdirectory list
            const TCHAR *subdir = NULL;
            do {
                result = TestPathAndFileNameHelper(namebuff, newsz, basePath, fileName, subdir);
                if (subDirList) {
                    subdir = *(subDirList++);
                }
            } while (!result && subdir);

            if (result && outPath) {
                // resize buffer, and transfer buffer ownership
                *outPath = (TCHAR *) realloc(namebuff, (_tcslen(namebuff) + 1) * sizeof(TCHAR));
            } else {
                free(namebuff);
            }
        }
    }

    return result;
}


TCHAR *GetWinDir()
{
    // get %SystemRoot% eg C:\Windows
    DWORD dirLen = GetWindowsDirectory(NULL, 0);
    TCHAR *windir = NULL;

    if (dirLen) {
        windir = (TCHAR *) calloc(dirLen, sizeof(TCHAR));
        if (windir) {
            GetWindowsDirectory(windir, dirLen);
        }
    }
    return windir;
}


#if !defined(_WIN64)
/* this wrapper for IsWow64Process() API is adapted from MSDN */
BOOL IsWow64()
{
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    HMODULE hModule;
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    BOOL bIsWow64 = FALSE;

    // IsWow64Process is not available on all supported versions of Windows.
    // Use GetModuleHandle to get a handle to the DLL that contains the function
    // and GetProcAddress to get a pointer to the function if available.
    hModule = GetModuleHandle(TEXT("kernel32"));
    if(!hModule)
    {
        // Should never happen
        return FALSE;
    }

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        hModule,"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        // NB ignore error
        fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
    }
    return bIsWow64;
}


// is the native system running on AMD64 (x64)?
BOOL IsSystemAMD64()
{
    SYSTEM_INFO si;

    GetNativeSystemInfo(&si);
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
        return TRUE;
    }
    return FALSE;
}


/*
   Note after some investigation, I don't think we can launch 2nd installer as
   Admin on Vista & later. (At least not unless we are already installed into
   Program Files directrory.) This is due to new User Access Control security behaviour.
   */
#endif


/*
    Check whether another install/uninstall is in-progress.
    This wrapper for CMP_WaitNoPendingInstallEvents() API adapted from MSDN  sample*/
typedef DWORD (WINAPI *CMP_WAITNOPENDINGINSTALLEVENTS_PROC) (DWORD);

BOOL IsSafeToInstall(DWORD dwTimeout)
{
    HMODULE hModule;
    CMP_WAITNOPENDINGINSTALLEVENTS_PROC pCMP_WaitNoPendingInstallEvents;

    hModule = GetModuleHandle(TEXT("Cfgmgr32.dll"));
    if(!hModule)
    {
        // Should never happen since we're linked to Cfgmgr32, but...
        return TRUE;
    }

    pCMP_WaitNoPendingInstallEvents =
        (CMP_WAITNOPENDINGINSTALLEVENTS_PROC)GetProcAddress(hModule,
                                             "CMP_WaitNoPendingInstallEvents");
    if(!pCMP_WaitNoPendingInstallEvents)
    {
        // We're running on a release of the operating system that doesn't supply this function.
        // Trust the operating system to suppress AutoRun when appropriate.
        return TRUE;
    }
    return (pCMP_WaitNoPendingInstallEvents(dwTimeout) == WAIT_OBJECT_0);
}


/* look for rfidlercdc.inf already present in %windir%\inf
   Only works on Windows XP.
   Newer Windows versions install as OEM<random number>.inf
   - not going to walk through these & do an content inspection.
*/
BOOL CheckIfInstalled()
{
    BOOL isInstalled = FALSE;

#if 1
    // try using SetupOpeninfFile to find installed rfidlercdc.inf
    HINF hh = SetupOpenInfFile(szRfidlerInfName, NULL, INF_STYLE_WIN4, NULL);

    if (hh != INVALID_HANDLE_VALUE) {
        isInstalled = TRUE;
        SetupCloseInfFile(hh);
    }

#else
    // GetWinDir() alternate code
    TCHAR *windir = NULL;

    windir = GetWinDir();
    if (windir) {
        // NULL terminated list of subirectories to search
        const TCHAR *szIndSubdirList[] =
            { _T("INF"), NULL };

        isInstalled = TestFileNameAndPath(windir, szRfidlerInfName, NULL, szIndSubdirList);
        free(windir);
    }

    /*
        The destination directory for .inf files can be changed, this should be given
        by registry key HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion
        Not currently important enough to handle this further.
    */
#endif

    return isInstalled;
}


DWORD WINAPI DriverUninstallThreadProc(LPVOID lpParameter)
{
    InstallInfo *pInsInfo = (InstallInfo *)lpParameter;

    pInsInfo->insError = ERROR_SUCCESS;

    // look for serial ports matching dev
    UpdateDriverWithAction(pInsInfo, &GUID_DEVCLASS_PORTS, UninstallDriverWinXP);

    // Windows XP? and need to fully uninstall driver?
    if (!CheckWindowsVersion(WinAtLeastVista) && (pInsInfo->uninstallType == IDC_UNINSTALLDRIVER)) {
        // remove the .inf file from the system
        if (!SetupUninstallOEMInf(szRfidlerInfName, SUOI_FORCEDELETE, NULL)) {
            pInsInfo->insError = GetLastError();
        }
    }

    /* notify UI thread that we have finished, nb advances prog bar to 100%  */
    PostMessage(pInsInfo->hWnd, WM_PRIVATE_DRIVER_UNINSTALL_COMPLETE, TRUE, 0);
    return pInsInfo->insError;
}


/*
    Do installation from independent thread to avoid freezing the UI.

    Note: thread created with Windows APIs not C library, so be
    cautious using C runtime library especially alloc/free.
 */
DWORD WINAPI DriverInstallThreadProc(LPVOID lpParameter)
{
    InstallInfo *pInsInfo = (InstallInfo *)lpParameter;
    BOOL driverInstalled = FALSE;

    pInsInfo->insError = ERROR_SUCCESS;


    driverInstalled = UpdateDriverForPlugAndPlayDevices(pInsInfo->hWnd, szRfidlerHardwareId,
        pInsInfo->infpath, 0, &pInsInfo->rebootRequired);

    if (driverInstalled) {
        pInsInfo->devConnected = TRUE;
        // update progress reporting
        PostMessage(pInsInfo->hWnd, WM_PRIVATE_DRIVER_UPDATE_PROGRESS, 0, 0);
    } else {
        // some issue means driver not installed
        pInsInfo->insError = GetLastError();

        /* ERROR_NO_SUCH_DEVINST (0xE000020B) indicates no currently connected RFIDlers
            and therefore .inf was not installed.
            */
        if (pInsInfo->insError == ERROR_NO_SUCH_DEVINST) {
            // install .inf file anyway
            driverInstalled = SetupCopyOEMInfW(pInsInfo->infpath, NULL, SPOST_PATH,
                SP_COPY_NOOVERWRITE, NULL, 0, NULL, NULL);

            if (!driverInstalled) {
                // failed
                pInsInfo->insError = GetLastError();
            } else {
                pInsInfo->insError = ERROR_SUCCESS;
                // update progress reporting
                PostMessage(pInsInfo->hWnd, WM_PRIVATE_DRIVER_UPDATE_PROGRESS, 1, 0);
            }
        }
    }

    if (driverInstalled) {
        // iterate thru not present devices, ensure they are updated to the new driver on next connect
        UpdateDriverWithAction(pInsInfo, NULL, MarkNonPresentForReinstall);
    }

    /* notify UI thread that we have finished */
    PostMessage(pInsInfo->hWnd, WM_PRIVATE_DRIVER_UPDATE_COMPLETE, driverInstalled, 0);
    return pInsInfo->insError;
}


/*
   Note:
   RFIDlers that have a (old) driver have class GUID = GUID_DEVCLASS_PORTS.
   RFIDlers that are not configured have no class GUID, & show as "other devices" in Device Manager.
   So we can search with the GUID during uninstall, but need to search without a GUID, and with
   DIGCF_ALLCLASSES flag to identify previously connected device node during install.
   */
void UpdateDriverWithAction(InstallInfo *pInsInfo, const GUID *classGuid, enum UpdateAction action)
{
    HDEVINFO DeviceInfoSet;
    SP_DEVINFO_DATA DeviceInfoData;
    DWORD DeviceIndex = 0;
    ULONG Status, Problem;


    DeviceInfoSet = SetupDiGetClassDevs(classGuid, NULL, pInsInfo->hWnd, 
        classGuid ? 0 : DIGCF_ALLCLASSES);

    if (DeviceInfoSet == INVALID_HANDLE_VALUE) {
        return;
    }

    ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    while (SetupDiEnumDeviceInfo(DeviceInfoSet, DeviceIndex, &DeviceInfoData)) {
        DeviceIndex++;

        if (CheckHardwareIdMatch(DeviceInfoSet, &DeviceInfoData, szRfidlerHardwareId)) {
            switch (action) {
            case MarkNonPresentForReinstall:
                // failure to fetch status => device not present
                if (CR_SUCCESS != CM_Get_DevNode_Status(&Status, &Problem, (DEVNODE)DeviceInfoData.DevInst, 0)) {
                    // mark for re-install
                    MarkDeviceConfigForReinstall(DeviceInfoSet, &DeviceInfoData);
                 }
               break;
            case UninstallDriverWinXP:
                // remove RFIDler devices
                if (SetupDiCallClassInstaller(DIF_REMOVE, DeviceInfoSet, &DeviceInfoData)) {
                    // check whether Windows wants a Reboot to enact changes
                    SP_DEVINSTALL_PARAMS params;

                    ZeroMemory(&params, sizeof(SP_DEVINSTALL_PARAMS));
                    params.cbSize = sizeof(SP_DEVINSTALL_PARAMS);
                    if (SetupDiGetDeviceInstallParams(DeviceInfoSet, &DeviceInfoData, &params)) {
                        if (!pInsInfo->rebootRequired && (params.Flags & (DI_NEEDREBOOT | DI_NEEDRESTART))) {
                            pInsInfo->rebootRequired = TRUE;
                        }
                    }
                } else {
                    pInsInfo->insError = GetLastError();
                }
                break;
            case DebugLogDevice:
                OutputDebugStringA("Found a Rfidler device instance\n");
                break;
            }
        }
    } // while

    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}


BOOL CheckHardwareIdMatch(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *DeviceInfoData, const TCHAR *szHardwareId)
{
    LPWSTR HwIdBuffer = NULL;
    DWORD HwIdBufferLen = 0;
    DWORD RequiredSize = 0;
    BOOL  match = FALSE;
    DWORD RegDataType;

    // get the HardwareID property for this device
    while (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet,
                                            DeviceInfoData,
                                            SPDRP_HARDWAREID,
                                            &RegDataType,
                                            (PBYTE)HwIdBuffer,
                                            HwIdBufferLen,
                                            &RequiredSize)) {
        if (HwIdBuffer) {
            free(HwIdBuffer);
        }

        if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
            // skip to next device
            break;
        }

        HwIdBuffer = (PWSTR) calloc(RequiredSize, 1);
        HwIdBufferLen = RequiredSize;
    }

    // sanity checks
    if (HwIdBuffer && (RegDataType == REG_MULTI_SZ) && (RequiredSize > sizeof(TCHAR))) {
        LPWSTR idStr;
        // compare each MULTI_SZ string with reference
        for (idStr = HwIdBuffer; idStr && *idStr; idStr += (lstrlen(idStr) + 1)) {
            if (!lstrcmpi(idStr, szHardwareId)) {
                match = TRUE;
                break;
            }
        }
    }

    if (HwIdBuffer) {
        free(HwIdBuffer);
    }
    return match;
}


void MarkDeviceConfigForReinstall(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *DeviceInfoData)
{
    DWORD ConfigFlags = 0;
    DWORD RegDataType;

    // try to get ConfigFlags value, may not be present
    (void) SetupDiGetDeviceRegistryProperty(DeviceInfoSet,
                                         DeviceInfoData,
                                         SPDRP_CONFIGFLAGS,
                                         &RegDataType,
                                         (PBYTE)&ConfigFlags,
                                         sizeof(ConfigFlags),
                                         NULL);

    /* Re-install flag is should already be set if no driver
       was previously installed.
       */
    if ( !(ConfigFlags & CONFIGFLAG_REINSTALL)) {
        // set Device Driver Re-install flag
        ConfigFlags |= CONFIGFLAG_REINSTALL;

        // just write value, nothing more to do even if it fails
        (void) SetupDiSetDeviceRegistryProperty(DeviceInfoSet,
                                         DeviceInfoData,
                                         SPDRP_CONFIGFLAGS,
                                         (PBYTE)&ConfigFlags,
                                         sizeof(ConfigFlags)
                                        );
    }
}


BOOL CheckWindowsVersion(enum WinVersion request)
{
    static int gotVerInfo = 0; // 1 => full OSVERSIONINFOEX, 2 => old style OSVERSIONINFO
    static OSVERSIONINFOEX winVer;

    BOOL checkResult = FALSE;

    if (gotVerInfo == 0) {
        BOOL success = FALSE;

        // winVer is static so will be initialised to 0
        winVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
        success = GetVersionEx((LPOSVERSIONINFO) &winVer);

        if (success) {
            gotVerInfo = 1;
        } else {
            // fallback to basic OSVERSIONINFO data
            winVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
            success = GetVersionEx((LPOSVERSIONINFO) &winVer);
            if (success) {
                gotVerInfo = 2;
            }
        }
    }

    if (gotVerInfo != 0) {
        switch (request)
        {
        case WinAtLeastVista:
            if (winVer.dwPlatformId == VER_PLATFORM_WIN32_NT) {
                // Windows Vista returns version 6.0 from GetVersionEx
                if (winVer.dwMajorVersion >= 6) {
                    checkResult = TRUE;
                }
            }
            break;
        case WinAtLeast7:
            if (winVer.dwPlatformId == VER_PLATFORM_WIN32_NT) {
                // Windows 7 returns version 6.1 from GetVersionEx
                if ((winVer.dwMajorVersion > 6) || ((winVer.dwMajorVersion == 6) && (winVer.dwMinorVersion > 0))) {
                    checkResult = TRUE;
                }
            }
            break;
        default: assert(0);
        }
    }

    return checkResult;
}


/* end of file rfidinstall.cpp */