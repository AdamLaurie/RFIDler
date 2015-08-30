/*
    Project: Windows RFIDler Driver Install v0.3
             Graphical interface to install driver .inf & .cat files
             for Aperture Labs RFIDler LF.

    File: rfidinstall.cpp (renamed from rfidinstall.c)

    Author: Anthony Naggs, 2014-2015

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
   http://support.microsoft.com/kb/2670561 but do not have a functioning way to actually obtain the fix.)

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
static const TCHAR *szAppName = L"RFIDler LF Driver Install - x64";
#elif defined(_M_IA64)
// HP / Intel Itanium (IA64) => Win 64
// Note that the last version of tools to support IA64 was MS Visual Studio 2010.
static const TCHAR *szAppName = L"RFIDler LF Driver Install - Itanium";
#error Itanium build not tested
#elif defined(_M_IX86)
// Intel x86 => Win 32
static const TCHAR *szAppName = L"RFIDler LF Driver Install - x86";
#elif defined(_M_ARM)
#error ARM cpu build not currently supported
#else
#error build not supported
#endif


// details specific to RFIDler
#define RFIDLER_INF_NAME        L"rfidlercdc.inf"
static const TCHAR *szRfidlerInfName = RFIDLER_INF_NAME;
static const TCHAR *szRfidlerHardwareId = L"USB\\VID_1D50&PID_6098";

// name of AMD64 version of installer
#define RFIDLER_INSTALLER64_NAME    L"rfidlerinstall-x64.exe"
static const TCHAR *szRfidlerInstallerX64 = RFIDLER_INSTALLER64_NAME;

// install update messages
enum installUpdates {
    UPDATE_COPIED,
    UPDATE_CONNECTED,
    UPDATE_PREVIOUS,
};

// action for each enumerated RFIDler
enum UpdateAction {
    MarkNotPresentRfidlersForReinstall,
    UninstallAllRfidlers,
    UninstallNotPresentRfidlers,
    DebugLogDevice,                     // debug aid
};

// tests to try on Windows Version Info
enum WinVersion {
    WinAtLeastXP,
    WinAtLeastVista,
    WinAtLeast7,
    WinAtLeast8,
    WinAtLeast10,
};

// config & result info for install / uninstall thread
typedef struct {
    BOOL    rebootRequired;         // out: reboot required
    int     uninstallType;          // in: button Id for uninstall action
    TCHAR   *infpath;               // in: full path & filename for installing .inf file
    DWORD   insError;               // out: Windows error code for function that failed
    HWND    hWndMain;               // in: main Installer window
    BOOL    devConnected;           // out: whether any Rfidlers were found during install
} InstallInfo;

enum ProgBarState {     // control the progress bar state
    PROG_START,
    PROG_ERROR,
    PROG_COMPLETE,
    PROG_HIDE,
    PROG_MAX            // for test button
};


void MoveMainWindow(HWND hWnd, HINSTANCE hInst);
INT_PTR CALLBACK InstallerDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL LaunchInstallOrUninstall(BOOL installAction, HWND hWnd, HWND hWndStatus, HWND hWndProg, ITaskbarList3* pTbList, InstallInfo *pInsInfo, int wID);
void StartOrStopProgressMarquee(HWND hWnd, HWND hWndProgBar, ITaskbarList3* pTbList, ProgBarState pbState);
void EnableAndFocusOnFinishButton(HWND hWnd);
INT_PTR CALLBACK AboutDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
UINT_PTR CALLBACK OFNHookCheckFilenameProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam);

void ReportStatus(HWND hWndStatus, const TCHAR *format, ...);
ATOM RegisterMainWindow (HINSTANCE hInstance);
BOOL FindInfPath(HWND hWnd, TCHAR **aPath);
BOOL GetProgramFilename(TCHAR **fname);
BOOL IsSafeToInstall(DWORD dwTimeout);
DWORD WINAPI DriverInstallThreadProc(LPVOID lpParameter);
DWORD WINAPI DriverUninstallThreadProc(LPVOID lpParameter);
BOOL UserSearchForInfFile(HWND hWnd, TCHAR **aPath, TCHAR *aInitialPath);
void UpdateDriverWithAction(InstallInfo *pInsInfo, const GUID *classGuid, enum UpdateAction action);
BOOL CheckHardwareIdMatch(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *pDeviceInfoData, const TCHAR *szHardwareId);
void MarkDeviceConfigForReinstall(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *pDeviceInfoData);
void RemoveRfidlerDevice(InstallInfo *pInsInfo, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *pDeviceInfoData);
BOOL TestFileNameAndPath(const TCHAR *basePath, const TCHAR *fileName, TCHAR **outPath, const TCHAR **subDirList);
//TCHAR *GetWinDir();
wchar_t *FindInstalledInf(HWND hWndMain);
void TrimDirectoryLevel(TCHAR *namebuff, size_t dirLen);
BOOL TestPathAndFileNameHelper(TCHAR *namebuff, size_t newsz, const TCHAR *basePath, const TCHAR *fileName, const TCHAR *subdir);

#if !defined(_WIN64)
BOOL IsWow64();
BOOL IsSystemAMD64();
#endif
BOOL CheckWindowsVersion(enum WinVersion);

#if defined(_DEBUG)
static void PrintDebugStatus(const TCHAR *format, ...);
#endif


// private internal WM_ notifications
#define WM_PRIVATE_UNINSTALL_INF        (WM_APP + 424)
#define WM_PRIVATE_UNINSTALL_COMPORT    (WM_APP + 425)
#define WM_PRIVATE_UPDATE_PROGRESS      (WM_APP + 426)
#define WM_PRIVATE_UPDATE_COMPLETE      (WM_APP + 427)
#define WM_PRIVATE_UNINSTALL_COMPLETE   (WM_APP + 428)


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
        MessageBox(NULL, L"Unable to create main window", szAppName, MB_OK | MB_ICONWARNING);
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
    WndClass.lpszClassName = L"RFIDinstall";
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
        HWND hW = CreateWindow(L"RFIDinstall", L"Invisible Window", WS_OVERLAPPEDWINDOW,
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
        insInfo.hWndMain = hWnd;
        insInfo.uninstallType = 0;
#if defined(_DEBUG)
        ShowWindow(GetDlgItem(hWnd, IDC_TESTBUTTON), SW_NORMAL);
#endif

        // check Windows version; set appropriate text for IDC_WINVER_EXPLAIN and enable/disable buttons
        // for reference old static text said "Drivers for RFIDler LF to be recognised as a serial (COM) port can install in Windows XP, Vista or 7, but in any case require Windows to accept unsigned drivers."
        if (CheckWindowsVersion(WinAtLeast10)) {
            SetWindowText(GetDlgItem(hWnd, IDC_WINVER_EXPLAIN),
                L"Windows 10 supports RFIDler LF without needing to install the" RFIDLER_INF_NAME L" file.");
            EnableWindow(GetDlgItem(hWnd, IDC_INSTALL), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), FALSE);
        } else if (CheckWindowsVersion(WinAtLeast8)) {
            SetWindowText(GetDlgItem(hWnd, IDC_WINVER_EXPLAIN),
                L"Windows 8.x is not supported at this time, as it requires " RFIDLER_INF_NAME L" to have a Microsoft approved signature, although we just ask to use Microsoft's own usbser driver.");
            EnableWindow(GetDlgItem(hWnd, IDC_INSTALL), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), FALSE);
        } else if (CheckWindowsVersion(WinAtLeastVista)) {
            SetWindowText(GetDlgItem(hWnd, IDC_WINVER_EXPLAIN),
                L"Windows Vista or 7 need to be configured to accept unsigned drivers in order to accept our " RFIDLER_INF_NAME L" file.");
        } else { // Win XP
            SetWindowText(GetDlgItem(hWnd, IDC_WINVER_EXPLAIN),
                L"Windows XP requires our " RFIDLER_INF_NAME L" file to be installed, it simnply directs Windows to use Microsoft's own usbser driver.");
            // Full driver uninstall works on XP, but not >= Win Vista
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), TRUE);
        }

        // Check for Windows >= 7
        if (CheckWindowsVersion(WinAtLeast7)) {
            TbCreatedNotification = RegisterWindowMessage(L"TaskbarButtonCreated");
            if (TbCreatedNotification) {
                // obscurely documented secret sauce to actually get the notification
                ChangeWindowMessageFilterEx(hWnd, TbCreatedNotification, MSGFLT_ALLOW, NULL);
            }
        }

#if !defined(_WIN64)
        // catch Win32 Installer running on Win x64
        isWow64 = IsWow64();
        if (isWow64) {
            ReportStatus(hWndStatus, L"Security error: 32-bit Installer does work on 64-bit Windows");
            EnableWindow(GetDlgItem(hWnd, IDC_INSTALL), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALL_NOT_PRESENT), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALL_ALL_RFIDLERS), FALSE);
            EnableWindow(GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), FALSE);

            // wait until after window is drawn to display error in a MessageBox
            SetTimer(hWnd, KWow64TimerMagicNumber, 500, NULL);
        }
#endif

        // simulate CW_USEDEFAULT positioning
        MoveMainWindow(hWnd, hInst);

        // return TRUE unless you set the focus to a control
        return TRUE;

#if !defined(_WIN64)
    case WM_TIMER:
        // running Win32 installer on Windows x64 => MessageBox & then (non-debug build only) Quit 
        if ((wParam == KWow64TimerMagicNumber) && isWow64) {
            BOOL  isAMD64 = IsSystemAMD64();
            UINT  mbflags = MB_OK;
            TCHAR errorText[1024];
            TCHAR *errorTitle = L"Incompatible version of RFIDler Installer";

            // kill one-shot timer
            KillTimer(hWnd, wParam);

            // compose message depending if system is AMD64
            StringCbPrintf(errorText, sizeof(errorText),
                L"This (32-bit) Installer version is not allowed to change your (64-bit) system.\n\n"
                // NB %s below
                L"%sithout the installer you can:\n"
                L"1. connect your RFIDler LF,\n"
                L"2. wait for driver install to fail,\n"
                L"3. find the RFIDler in the Windows Device Manager\n"
                L"4. update the driver there.\n"
                L"(Install can fail due to Signed Driver policy settings,"
                L"see Help About text for more details.)",

                isAMD64 ? L"For AMD or Intel x64 sytems you can run " RFIDLER_INSTALLER64_NAME L" instead.\n\nAlternatively w"
                : L"W" );

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
            PrintDebugStatus(L"wID %i  wNotification %i  hChild %p\n", wID, wNotification, hChild);
#endif

            if (wNotification == BN_CLICKED) {
                switch (wID) {
                case IDC_INSTALL:
                    if (!CheckWindowsVersion(WinAtLeast8)) {
                        installing = LaunchInstallOrUninstall(TRUE, hWnd, hWndStatus, hWndProg, pTbList, &insInfo, wID);
                    }
                    handled++;
                    break;

                case IDC_UNINSTALL_ALL_RFIDLERS:
                case IDC_UNINSTALL_NOT_PRESENT:
                    installing = LaunchInstallOrUninstall(FALSE, hWnd, hWndStatus, hWndProg, pTbList, &insInfo, wID);
                    handled++;
                    break;

                case IDC_UNINSTALLDRIVER:
                    if (!CheckWindowsVersion(WinAtLeast8)) {
                        installing = LaunchInstallOrUninstall(FALSE, hWnd, hWndStatus, hWndProg, pTbList, &insInfo, wID);
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
                            L"Reboot to complete RFIDler LF Driver install",
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
                        wchar_t *infPath = FindInstalledInf(hWnd);

                        ReportStatus(hWndStatus, L"FindInstalledInf() = %s", infPath);
                        if (infPath) {
                            free(infPath);
                        }

                        if (!FindInfPath(hWnd, &insInfo.infpath)) {
                            ReportStatus(hWndStatus, L"Error: Cannot find rfidlercrc.inf");
                        } else {
                            ReportStatus(hWndStatus, L"Found %s", insInfo.infpath);
                            if (insInfo.infpath) {
                                free(insInfo.infpath);
                                insInfo.infpath = NULL;
                            }
                        }

                        // toggle marquee progress bar, & for Win >= 7 the progress bar on the icon
                        StartOrStopProgressMarquee(hWnd, hWndProg, pTbList, ProgBarState (testCount % PROG_MAX));

                        if (testCount++ == 1) {
                            ShowWindow(hRebootButton, SW_SHOWNORMAL);
                            EnableWindow(hRebootButton, TRUE);
                        }
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

    case WM_PRIVATE_UNINSTALL_INF:
        {
            wchar_t *infPath = (wchar_t*) lParam;

            if (infPath) {
                ReportStatus(hWndStatus, L"Removed installed %s file", infPath);
                free(infPath);
            }
        }
        handled++;
        break;

    case WM_PRIVATE_UNINSTALL_COMPORT:
        // wParam should indicate the removed COM port number
        if (installing) {
            ReportStatus(hWndStatus, L"Uninstalling RFIDler LF on COM%u", wParam);
        }
        handled++;
        break;

    case WM_PRIVATE_UPDATE_PROGRESS:
        // wParam should indicate how the .inf file was copied, message to display
        if (installing) {
            const int n_messages = 3;
            const TCHAR *updateMessage [n_messages] = {
                L"%s copied by Windows for unconnected RFIDlers",
                L"%s installed for connected RFIDlers ...",
                L"updating previously installed RFIDlers",
            };

            if (wParam < n_messages) {
                ReportStatus(hWndStatus, updateMessage[wParam]);
            }
        }
        handled++;
        break;

    case WM_PRIVATE_UPDATE_COMPLETE:
        if (installing) {
            installing = FALSE;
            if (insInfo.infpath) {
                free(insInfo.infpath);
                insInfo.infpath = NULL;
            }
            /* notification from installer thread: install success (or previously installed) => Complete, otherwise error */
            StartOrStopProgressMarquee(hWnd, hWndProg, pTbList, (wParam != 0) ? PROG_COMPLETE : PROG_ERROR);

            EnableAndFocusOnFinishButton(hWnd);

            if (wParam) {
                if (insInfo.rebootRequired) {
                    ReportStatus(hWndStatus, L"Windows reboot required to complete installation");
                    ShowWindow(hRebootButton, SW_SHOWNORMAL);
                    EnableWindow(hRebootButton, TRUE);
                } else {
                    ReportStatus(hWndStatus,
                        (insInfo.insError == ERROR_SUCCESS) ? L"Driver install complete" : L"Driver already installed");
                    if (!insInfo.devConnected) {
                        ReportStatus(hWndStatus, L"Connect your RFIDler LF now");
                    }
                }
            } else {
                TCHAR *errmsg = NULL;
                switch (insInfo.insError)
                {
                case ERROR_FILE_NOT_FOUND:
                    errmsg = L"Error: " RFIDLER_INF_NAME L" file not found";
                    break;
                case ERROR_IN_WOW64:
                    errmsg = L"Error: x86 installer failed on 64-bit Windows";
                    break;
                default:
                    errmsg = L"Error: driver install failed (error = %X)";
                    break;
                }
                ReportStatus(hWndStatus, errmsg, insInfo.insError);
                MessageBeep(0xFFFFFFFF);
            }
        }
        handled++;
        break;

    case WM_PRIVATE_UNINSTALL_COMPLETE:
        if (installing) {
            installing = FALSE;

            StartOrStopProgressMarquee(hWnd, hWndProg, pTbList, (insInfo.insError == NO_ERROR) ? PROG_COMPLETE : PROG_ERROR);

            EnableAndFocusOnFinishButton(hWnd);

            if (insInfo.insError == NO_ERROR) {
                if (insInfo.rebootRequired) {
                    ReportStatus(hWndStatus, L"Windows reboot required to complete uninstall");
                    ShowWindow(hRebootButton, SW_SHOWNORMAL);
                    EnableWindow(hRebootButton, TRUE);
                } else {
                    ReportStatus(hWndStatus,
                        (insInfo.uninstallType == IDC_UNINSTALLDRIVER) ?
                        L"Driver uninstall complete" : L"Uninstall of RFIDlers complete");
                }
            } else if (insInfo.insError == ERROR_FILE_NOT_FOUND) {
                ReportStatus(hWndStatus, L"Uninstall complete, " RFIDLER_INF_NAME L" was not found");
            } else {
                ReportStatus(hWndStatus, L"Error: %s failed (error = %X)",
                    (insInfo.uninstallType == IDC_UNINSTALLDRIVER) ?
                    L"Driver uninstall" : L"Uninstall of RFIDlers",
                    insInfo.insError);
                MessageBeep(0xFFFFFFFF);
            }
            handled++;
        }
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
                ReportStatus(hWndStatus, L"Info: received unhandled Msg (0x%X)", iMsg);
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


BOOL LaunchInstallOrUninstall(BOOL installAction, HWND hWnd, HWND hWndStatus, HWND hWndProg, ITaskbarList3* pTbList, InstallInfo *pInsInfo, int wID)
{
    BOOL installing = FALSE;
    BOOL isSafe = IsSafeToInstall(500);

    if (!isSafe) {
        // Found New Hardware Wizard might be active
        ReportStatus(hWndStatus, L"Error: Windows Installer is running, retry when it has finished");
    } else if (installAction && !FindInfPath(hWnd, &pInsInfo->infpath)) {
        ReportStatus(hWndStatus, L"Error: Cannot find rfidlercrc.inf");
    } else {
        // launch background thread for installer/uninstaller
        HANDLE hThread;

        // uninstall button id is used to distinguish the 3 uninstall functions
        pInsInfo->uninstallType = wID;

        SetWindowText(GetDlgItem(hWnd, IDC_STATUS_TITLE), 
            installAction ? L"Install Status:" : L"Uninstall Status:");

        hThread = CreateThread(NULL, 0,
                    installAction ? DriverInstallThreadProc : DriverUninstallThreadProc,
                    pInsInfo, 0, NULL);

        if(hThread) {
            installing = TRUE;
            // Okay: close handle for install thread.
            CloseHandle(hThread);

            // enable/show progress bar, disable buttons
            StartOrStopProgressMarquee(hWnd, hWndProg, pTbList, PROG_START);
            EnableWindow (GetDlgItem(hWnd, IDC_INSTALL), FALSE);
            EnableWindow (GetDlgItem(hWnd, IDC_UNINSTALL_ALL_RFIDLERS), FALSE);
            EnableWindow (GetDlgItem(hWnd, IDC_UNINSTALL_NOT_PRESENT), FALSE);
            EnableWindow (GetDlgItem(hWnd, IDC_UNINSTALLDRIVER), FALSE);
            EnableWindow (GetDlgItem(hWnd, IDC_EXIT), FALSE);

            if (installAction) {
                ReportStatus(hWndStatus, L"Installing driver and all connected RFIDlers ...");
            } else {
                wchar_t * uninstallType = 
                    (IDC_UNINSTALL_ALL_RFIDLERS == wID) ? L"all RFIDlers" : 
                    (IDC_UNINSTALL_NOT_PRESENT == wID) ? L"not connected RFIDlers" : L"RFIDlers and driver";

                ReportStatus(hWndStatus, L"Uninstalling %s ...", uninstallType);
            }
        } else {
            ReportStatus(hWndStatus, L"Error: %s failed to start (error %X)",
                installAction ? L"Install" : L"Uninstall",
                GetLastError());
        }
    }

    if (!installing) {
        MessageBeep(0xFFFFFFFF);
        // TODO? timed MessageBox
    }
    return installing;
}


void StartOrStopProgressMarquee(HWND hWnd, HWND hWndProgBar, ITaskbarList3* pTbList, ProgBarState pbState)
{
    // comctrl32 v6 required; set & show or clear & hide progress bar in marquee mode
    // also for Windows >= 7, start/stop marquee progress bar on the icon
    static BOOL marquee = FALSE;

    switch (pbState)
    {
    case PROG_START: // start marquee
        ShowWindow(hWndProgBar, SW_NORMAL);
        if (!marquee) {
            LONG style = GetWindowLong(hWndProgBar, GWL_STYLE);
            if (! (style & PBS_MARQUEE)) {
                SetWindowLong(hWndProgBar, GWL_STYLE, style | PBS_MARQUEE);
            }

            SendMessage(hWndProgBar, PBM_SETMARQUEE, TRUE, 0);
            marquee = TRUE;

            if (pTbList) {
                pTbList->SetProgressState(hWnd, TBPF_INDETERMINATE);
            }
        }
        break;

    case PROG_ERROR: // stop marquee at 100% & display as red
    case PROG_COMPLETE: // stop marquee at 100% & display as green
        if (marquee) {
            LONG style = GetWindowLong(hWndProgBar, GWL_STYLE);
            if (style & PBS_MARQUEE) {
                SetWindowLong(hWndProgBar, GWL_STYLE, style & ~PBS_MARQUEE);
                SendMessage(hWndProgBar, PBM_SETMARQUEE, FALSE, 0);
            }
            marquee = FALSE;
        }
        SendMessage(hWndProgBar, PBM_SETRANGE32, 0, 100);
        SendMessage(hWndProgBar, PBM_SETPOS, 100, 0);
        SendMessage(hWndProgBar, PBM_SETSTATE, (PROG_COMPLETE == pbState) ? PBST_NORMAL : PBST_ERROR, 0);
        if (pTbList) {
            // set progress (default is 0, so e.g. red hardly shows)
            pTbList->SetProgressState(hWnd, (PROG_COMPLETE == pbState) ? TBPF_NORMAL : TBPF_ERROR);
            pTbList->SetProgressValue(hWnd, 100, 100);
        }
        break;

    case PROG_HIDE:
    default:
        // remove marquee
        if (marquee) {
            SendMessage(hWndProgBar, PBM_SETMARQUEE, FALSE, 0);
            marquee = FALSE;
        }
        ShowWindow(hWndProgBar, SW_HIDE);
        if (pTbList) {
            pTbList->SetProgressState(hWnd, TBPF_NOPROGRESS);
        }
        break;
    }
}


void EnableAndFocusOnFinishButton(HWND hWnd)
{
    SetWindowText(GetDlgItem(hWnd, IDC_EXIT), L"Finish");
    EnableWindow (GetDlgItem(hWnd, IDC_EXIT), TRUE);

    // set dialog focus
    SendMessage(hWnd, WM_NEXTDLGCTL, (WPARAM)GetDlgItem(hWnd, IDC_EXIT), TRUE);
}


// program description and decide copyright licensing info
static const TCHAR *helpTitle = L"Help About RFIDLer LF Driver Installer v0.3";
static const TCHAR *helpText =
    L"This installer is Copyright (c) 2014-2015 Anthony Naggs, all rights reserved.\r\n"
    L"Limited rights are assigned through BSD 2-Clause License, see bottom of text.\r\n"
    L"\r\n"
    L"RFIDler LF appears to the computer as a USB serial port, and works with a standard \r\n"
    L"Windows driver for USB serial ports, usbser.sys.\r\n"
    L"\r\n"
    L"A simple driver information file (" RFIDLER_INF_NAME L") tells Windows which driver to use, and \r\n"
    L"such details as manufacturer (Aperture Labs Ltd) and product names (RFIDler LF).\r\n"
    L"\r\n"
    L"IMPORTANT: Although " RFIDLER_INF_NAME L"simply tells Windows to use the standard USB\r\n"
    L"serial port driver Windows wants the .inf file to be signed as valid. This is unfortunately\r\n"
    L"expensive. Therefore this install will only work if Windows is configured not to enforce\r\n"
    L"signing of drivers.\r\n"
    L"\r\n"
    L"This installer provides a simple interface to install or uninstall (1) installed RFIDler\r\n"
    L"devices or (2) RFIDler devices and this .inf file. (Note that complete uninstall only\r\n"
    L"works on Windows XP.)\r\n"
    L"\r\n"
    L"Alternatively to using the installer you can connect your RFIDler LF, find it in Windows \r\n"
    L"Device Manager (via the Control Panel) and update the driver there. This program \r\n"
    L"needs to run as local Administrator in order to copy files to, or remove files from, \r\n"
    L"Windows protected directories.\r\n"
    L"\r\n"
    L"Two versions of the installer are supplied:\r\n"
    L"* rfidlerinstall-x86.exe for 32-bit versions of Windows XP to Windows 7, and\r\n"
    L"* rfidlerinstall-x64.exe for 64-bit versions of Windows on AMD64 CPUs.\r\n"
    L"\r\n"
    L".....................................................\r\n\r\n"
    L"More copyright information below ...\r\n"
    L"\r\n"
    L"Limited assignment of rights under the 'BSD 2-Clause License':\r\n"
    L"\r\n"
    L"Redistribution and use in source and binary forms, with or without modification, are \r\n"
    L"permitted provided that the following conditions are met:\r\n"
    L"\r\n"
    L"1. Redistributions of source code must retain the above copyright notice, this list of\r\n"
    L"     conditions and the following disclaimer.\r\n"
    L"\r\n"
    L"2. Redistributions in binary form must reproduce the above copyright notice, this list\r\n"
    L"     list of conditions and the following disclaimer in the documentation and/or other\r\n"
    L"     materials provided with the distribution.\r\n"
    L"\r\n"
    L"THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \r\n"
    L"\"AS IS\" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT \r\n"
    L"LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR \r\n"
    L"A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT \r\n"
    L"HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, \r\n"
    L"SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT \r\n"
    L"LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, \r\n"
    L"DATA, ORPROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY \r\n"
    L"THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT \r\n"
    L"(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE \r\n"
    L"OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.";

/*
    Notes:
    On Windows XP it is to check/change driver signing checks:
    Windows Control Panel select System -> Hardware -> Driver Signing
*/

INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /* IDD_HELP_ABOUT */

    lParam; // suppress unreferenced parameter warning

    switch (iMsg) {
    case WM_INITDIALOG:
        SetWindowText(hDlg, helpTitle);
        SetWindowText(GetDlgItem(hDlg, IDC_HELP_TEXT), helpText);

        // TODO: get .exe file version for use in title eg GetFileVersionInfoSize() & GetFileVersionInfo()

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
            L"windows driver\\inf", L"inf",
            L"..\\windows driver\\inf", L"..\\inf",
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
        ofn.lpstrTitle = L"Find " RFIDLER_INF_NAME L" required for driver install";
        ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST
            | OFN_HIDEREADONLY | OFN_ENABLEHOOK | OFN_EXPLORER | OFN_ENABLESIZING;
        ofn.nMaxFile = fileNameSize;
        ofn.lpstrFile = name;
        ofn.lpstrFilter = L"Driver install info (*.inf)\0*.inf\0\0";
        ofn.lpstrDefExt = L"inf";
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
                    // Note DWL_MSGRESULT not declared in Win64 builds, use DWLP_MSGRESULT instead
                    SetWindowLongPtr(hDlg, DWLP_MSGRESULT, 1);
                }
                handled++;
            }
        }
        break;
    }
    return handled;
}


// helpers for TestFileNameAndPath(), trim lowest directory level from path, used for handling "..\"
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
    size_t  dirLen = basePath ? _tcslen(basePath) : 0;
    DWORD   attributes = 0;

    // fill buffer with base path
    if (dirLen) {
        _tcsncpy_s(namebuff, newsz, basePath, _TRUNCATE);
    } else {
        namebuff[0] = 0;
    }

    if (subdir) {
        // handle "..\" in subdirectory
        while (!wcsncmp(subdir, L"..\\", 3)) {
            subdir += 3;
            TrimDirectoryLevel(namebuff, dirLen);
        }
        _tcsncat_s(namebuff, newsz, subdir, _TRUNCATE);
    }

    // ensure '\' at end of path
    dirLen = _tcslen(namebuff);
    if (namebuff[dirLen-1] != L'\\') {
        _tcsncat_s(namebuff, newsz, L"\\", _TRUNCATE);
    }
    
    _tcsncat_s(namebuff, newsz, fileName, _TRUNCATE);
#if defined(_DEBUG)
    PrintDebugStatus( L"\"%s\"\n", namebuff);
#endif
    attributes = GetFileAttributes(namebuff);
    if (INVALID_FILE_ATTRIBUTES == attributes) {
        return FALSE;
    }
    if ((FILE_ATTRIBUTE_DEVICE | FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_ENCRYPTED | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_OFFLINE |
            FILE_ATTRIBUTE_REPARSE_POINT | FILE_ATTRIBUTE_SPARSE_FILE | FILE_ATTRIBUTE_TEMPORARY) & attributes) {
        return FALSE;
    }
    return TRUE; // FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_COMPRESSED | FILE_ATTRIBUTE_NOT_CONTENT_INDEXED | FILE_ATTRIBUTE_READONLY
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


/*
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
*/


#if !defined(_WIN64)
/* this wrapper for IsWow64Process() API is adapted from MSDN help text */
BOOL IsWow64()
{
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    HMODULE hModule;
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    BOOL bIsWow64 = FALSE;

    // IsWow64Process is not available on all supported versions of Windows.
    // Use GetModuleHandle to get a handle to the DLL that contains the function
    // and GetProcAddress to get a pointer to the function if available.
    hModule = GetModuleHandle(L"kernel32");
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
   Program Files directrory.) This is due to the new User Access Control security
   behaviour.
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

    hModule = GetModuleHandle(L"Cfgmgr32.dll");
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

   Not found => search to identify corresponding OEM<random number>.inf
   that Windows renamed the file to on install.
*/
wchar_t *FindInstalledInf(HWND hWndMain)
{
    //HDEVINFO DeviceInfoSet;
    HKEY hClassKey;

    // try using SetupOpenInfFile to find installed rfidlercdc.inf, should work on Win XP, maybe Vista?
    HINF hh = SetupOpenInfFile(szRfidlerInfName, NULL, INF_STYLE_WIN4, NULL);

    if (hh != INVALID_HANDLE_VALUE) {
        // TODO? check .inf file version
        SetupCloseInfFile(hh);
        return _wcsdup(szRfidlerInfName);
#if _DEBUG
    } else {
        PrintDebugStatus(L"Error: SetupOpenInfFile() (%08X)", GetLastError());
#endif
    }


    // Open registry key HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\ + GUID_DEVCLASS_PORTS
    hClassKey = SetupDiOpenClassRegKey(&GUID_DEVCLASS_PORTS, KEY_READ);

    if (hClassKey) {
        // Iterate through keys looking for value of MatchingDeviceId == usb\vid_1d50&pid_6098
        wchar_t  *infName = NULL;

#define MAX_KEY_LENGTH 255
        wchar_t  valueBuffer[MAX_KEY_LENGTH];
        wchar_t  achKey[MAX_KEY_LENGTH];   // buffer for subkey name
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
        DWORD i, retCode;
        BOOL match = FALSE;

        // Get the class name and the value count.
        retCode = RegQueryInfoKey(
            hClassKey,               // key handle
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

        if (ERROR_SUCCESS == retCode) {
            // Enumerate the subkeys, until matching hwId or RegEnumKeyEx fails.
            for (i = 0; (i < cSubKeys) && !match; i++) {
                cbName = MAX_KEY_LENGTH;
                retCode = RegEnumKeyEx(hClassKey, i, achKey, &cbName, NULL, NULL, NULL, &ftLastWriteTime);

                if (ERROR_SUCCESS == retCode) {
                    DWORD valtype;
                    DWORD valsize = sizeof(valueBuffer);
                    HKEY hKey2;

                    retCode = RegOpenKeyEx(hClassKey, achKey, 0, KEY_READ, &hKey2);

                    if (ERROR_SUCCESS == retCode) {
                        // get  & compare HardwareId with Rfidler
                        retCode = RegQueryValueEx(hKey2, _T("MatchingDeviceId"), 0, &valtype, (BYTE*)&valueBuffer, &valsize);
                        if ((ERROR_SUCCESS == retCode) && (REG_SZ == valtype) && (0 == _wcsicmp(valueBuffer, szRfidlerHardwareId))) {
                            match = TRUE; // exit loop
                            valsize = sizeof(valueBuffer);

                            // query value of InfPath to find corresponding installed oem??.inf file name
                            retCode = RegQueryValueEx(hKey2, _T("InfPath"), 0, &valtype, (BYTE*)&valueBuffer, &valsize);
                            if ((ERROR_SUCCESS == retCode) && (REG_SZ == valtype)) {
                                //PrintDebugStatus(L"LocationInformation %s\n", locationBuffer);
                                infName = _wcsdup(valueBuffer);
                            }
                        }

                        RegCloseKey(hKey2);
                    }

                    // DEBUG - PrintDebugStatus(L"(%d) %s %u\n", i+1, achKey, retCode);
                }
            } // for
        } // if

#undef MAX_KEY_LENGTH

        RegCloseKey(hClassKey);

        if (infName) {
            return infName;
        }
    }

    /*
       TODO:
       Recommended for Windows XP and later versions, use SetupDiBuildDriverInfoList (? maybe SetupDiGetDeviceInstallParams instead)
       with DeviceInstallParams.FlagsEx set to DI_FLAGSEX_INSTALLEDDRIVER to obtain details about the installed driver. 
    */

    return NULL;
}


DWORD WINAPI DriverUninstallThreadProc(LPVOID lpParameter)
{
    InstallInfo *pInsInfo = (InstallInfo *)lpParameter;

    pInsInfo->insError = ERROR_SUCCESS;

    // look for serial ports matching dev
    UpdateDriverWithAction(pInsInfo, &GUID_DEVCLASS_PORTS,
        (pInsInfo->uninstallType != IDC_UNINSTALL_NOT_PRESENT) ? UninstallAllRfidlers : UninstallNotPresentRfidlers);

    // need to fully uninstall driver?
    if (pInsInfo->uninstallType == IDC_UNINSTALLDRIVER) {
        // find & remove the .inf file from the system
        wchar_t *infPath = FindInstalledInf(pInsInfo->hWndMain);

        if (infPath) {
            if (!SetupUninstallOEMInf(szRfidlerInfName, SUOI_FORCEDELETE, NULL)) {
                pInsInfo->insError = GetLastError();
                free(infPath);
            } else {
                PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UNINSTALL_INF, 0, (LPARAM) infPath);
            }
        }
    }

    /* notify UI thread that we have finished, nb advances prog bar to 100%  */
    PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UNINSTALL_COMPLETE, TRUE, 0);
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

    driverInstalled = UpdateDriverForPlugAndPlayDevices(pInsInfo->hWndMain, szRfidlerHardwareId,
        pInsInfo->infpath, 0, &pInsInfo->rebootRequired);

    if (driverInstalled) {
        pInsInfo->devConnected = TRUE;
        // update progress reporting, installed for connected devices
        PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UPDATE_PROGRESS, UPDATE_CONNECTED, 0);
    } else {
        // some issue means driver not fully installed
        pInsInfo->insError = GetLastError();

        /* ERROR_NO_SUCH_DEVINST (0xE000020B) indicates no currently connected RFIDlers
            and therefore .inf was not installed.
            */
        if (ERROR_NO_SUCH_DEVINST== pInsInfo->insError) {
            // install .inf file anyway
            driverInstalled = SetupCopyOEMInfW(pInsInfo->infpath, NULL, SPOST_PATH,
                SP_COPY_NOOVERWRITE, NULL, 0, NULL, NULL);

            if (!driverInstalled) {
                // failed
                pInsInfo->insError = GetLastError();
                switch (pInsInfo->insError)
                {
                case ERROR_FILE_EXISTS:
                case ERROR_NO_MORE_ITEMS:
                    driverInstalled = TRUE;
                    break;
                default: // no action
                    break;
                }
            } else {
                pInsInfo->insError = ERROR_SUCCESS;
                // update progress reporting
                PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UPDATE_PROGRESS, UPDATE_COPIED, 0);
            }
        }
    }

    if (driverInstalled) {
        // iterate thru not present devices, ensure they are updated to the new driver on next connect
        PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UPDATE_PROGRESS, UPDATE_PREVIOUS, 0);
        UpdateDriverWithAction(pInsInfo, NULL, MarkNotPresentRfidlersForReinstall);
    }

    /* notify UI thread that we have finished */
    PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UPDATE_COMPLETE, driverInstalled, 0);
    return pInsInfo->insError;
}


/*
   Note:
   RFIDlers that have a (old/new) driver have class GUID = GUID_DEVCLASS_PORTS.
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


    DeviceInfoSet = SetupDiGetClassDevs(classGuid, NULL, pInsInfo->hWndMain,
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
            case MarkNotPresentRfidlersForReinstall:
                // failure to fetch status => device not present
                if (CR_SUCCESS != CM_Get_DevNode_Status(&Status, &Problem, (DEVNODE)DeviceInfoData.DevInst, 0)) {
                    // mark for re-install
                    MarkDeviceConfigForReinstall(DeviceInfoSet, &DeviceInfoData);
                 }
               break;

            case UninstallNotPresentRfidlers:
                // failure to fetch status => device not present
                if (CR_SUCCESS != CM_Get_DevNode_Status(&Status, &Problem, (DEVNODE)DeviceInfoData.DevInst, 0)) {
                    RemoveRfidlerDevice(pInsInfo, DeviceInfoSet, &DeviceInfoData);
                }
                break;

            case UninstallAllRfidlers:
                RemoveRfidlerDevice(pInsInfo, DeviceInfoSet, &DeviceInfoData);
                break;

            case DebugLogDevice:
                OutputDebugStringA("Found a Rfidler device instance\n");
                break;
            }
        }
    } // while

    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
}


// tell Windows to forget an RFIDler device, and release its COM port number
void RemoveRfidlerDevice(InstallInfo *pInsInfo, HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *pDeviceInfoData)
{
    // get the registry key with the device's port settings
    HKEY devkey = SetupDiOpenDevRegKey(DeviceInfoSet, pDeviceInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE);

    if (devkey) {
        //Read the name of the port from the registry
        wchar_t portnameBuff[16];
        const wchar_t*  keyname = L"PortName";
        DWORD sizeOut = 16;
        DWORD type = 0;
        LSTATUS result = RegQueryValueEx(devkey, keyname, NULL, &type, (LPBYTE)portnameBuff, &sizeOut);

        // tidy up
        RegCloseKey(devkey);

        // check registry value type, and port is COMxx
        if ((result == ERROR_SUCCESS) && (REG_SZ == type) && (0 == wcsncmp(portnameBuff, _T("COM"), 3))) {
            // Determine COM port number, for notification to user via WM_PRIVATE_UNINSTALL_COMPORT
            unsigned portNumber = wcstoul(portnameBuff + 3, NULL, 10);

            if (portNumber) {
                PostMessage(pInsInfo->hWndMain, WM_PRIVATE_UNINSTALL_COMPORT, portNumber, 0);
            }

            // remove the Rfidler
            if (SetupDiCallClassInstaller(DIF_REMOVE, DeviceInfoSet, pDeviceInfoData)) {
                // now check whether Windows wants a Reboot to enact changes
                SP_DEVINSTALL_PARAMS params;

                ZeroMemory(&params, sizeof(SP_DEVINSTALL_PARAMS));
                params.cbSize = sizeof(SP_DEVINSTALL_PARAMS);
                if (SetupDiGetDeviceInstallParams(DeviceInfoSet, pDeviceInfoData, &params)) {
                    if (!pInsInfo->rebootRequired && (params.Flags & (DI_NEEDREBOOT | DI_NEEDRESTART))) {
                        pInsInfo->rebootRequired = TRUE;
                    }
                }

                return; // success
            }
        }
    }

    // something failed
    pInsInfo->insError = GetLastError();
}


BOOL CheckHardwareIdMatch(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *pDeviceInfoData, const TCHAR *szHardwareId)
{
    LPWSTR HwIdBuffer = NULL;
    DWORD HwIdBufferLen = 0;
    DWORD RequiredSize = 0;
    BOOL  match = FALSE;
    DWORD RegDataType;

    // get the HardwareID property for this device
    while (!SetupDiGetDeviceRegistryProperty(DeviceInfoSet,
                                            pDeviceInfoData,
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
            if (!_wcsicmp(idStr, szHardwareId)) {
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


void MarkDeviceConfigForReinstall(HDEVINFO DeviceInfoSet, SP_DEVINFO_DATA *pDeviceInfoData)
{
    DWORD ConfigFlags = 0;
    DWORD RegDataType;

    // try to get ConfigFlags value, may not be present
    (void) SetupDiGetDeviceRegistryProperty(DeviceInfoSet,
                                         pDeviceInfoData,
                                         SPDRP_CONFIGFLAGS,
                                         &RegDataType,
                                         (PBYTE)&ConfigFlags,
                                         sizeof(ConfigFlags),
                                         NULL);

    /* Re-install flag should already be set if no driver
       was previously installed.
       */
    if ( !(ConfigFlags & CONFIGFLAG_REINSTALL)) {
        // set Device Driver Re-install flag
        ConfigFlags |= CONFIGFLAG_REINSTALL;

        // just write value, nothing more to do even if it fails
        (void) SetupDiSetDeviceRegistryProperty(DeviceInfoSet,
                                         pDeviceInfoData,
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
        case WinAtLeastXP:
            if (winVer.dwPlatformId == VER_PLATFORM_WIN32_NT) {
                // Windows XP returns version 5.1 from GetVersionEx
                if ((winVer.dwMajorVersion > 5) || ((winVer.dwMajorVersion == 5) && (winVer.dwMinorVersion >= 1))) {
                    checkResult = TRUE;
                }
            }
            break;

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
                if ((winVer.dwMajorVersion > 6) || ((winVer.dwMajorVersion == 6) && (winVer.dwMinorVersion >= 1))) {
                    checkResult = TRUE;
                }
            }
            break;

        case WinAtLeast8:
            if (winVer.dwPlatformId == VER_PLATFORM_WIN32_NT) {
                // Windows 8.0 returns version 6.2 from GetVersionEx
                if ((winVer.dwMajorVersion > 6) || ((winVer.dwMajorVersion == 6) && (winVer.dwMinorVersion >= 2))) {
                    checkResult = TRUE;
                }
            }
            break;

        case WinAtLeast10:
            if (winVer.dwPlatformId == VER_PLATFORM_WIN32_NT) {
                // Windows 10 returns version 10.0 from GetVersionEx, *but only if Manifested for version 10* otherwise 6.2
                if (winVer.dwMajorVersion >= 10) {
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