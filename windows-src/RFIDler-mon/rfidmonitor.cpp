/* 

    Project: RFIDler Monitor v0.2
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: rfidmonitor.cpp

    Author: Anthony Naggs, 2014, 2015, 2016

    Copyright (c) 2014-2016 Anthony Naggs.
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

#include <ShlObj.h>
//#include <uxtheme.h>


/*
 * This program needs to be linked with these libraries:
 * NB if any are missing from Windows SDK the Windows Driver Kit is required.
 */
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma comment(lib, "version.lib")
#if defined(ENABLE_BOOTLOADER_FLASH_DIALOGS) || defined(_DEBUG)
// todo review
#pragma comment(lib, "hid.lib")
#endif

/* proclaim support for "Visual Styles" / i.e. Windows Vista Themes
 Ensure we only run on Windows XP with Common Controls v6 installed,
 or later Windows version. This gives e.g. Tile View and glowing focus
 effects.
*/
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


// various global constant

const wchar_t *szAppName = L"RFIDler Monitor";
const wchar_t *szRfidlerHwUsbId = L"USB\\VID_1D50&PID_6098";
const wchar_t *szMicrochipSerialHwUsbId = L"USB\\VID_04D8&PID_000A";
const wchar_t *szMicrochipBootHidId = L"HID\\VID_04D8&PID_003C";
const wchar_t *szTeensyHalfKayBootHidId = L"HID\\VID_16C0&PID_0478";

const wchar_t *KStartupArgument = L"/STARTUP";

// singleton DeviceTracker
DeviceTracker DevTracker;


/* ******************** PROGRAM CONFIGURATION ********************* */
/* nominal minimum window size is 300 * 250 */
// FIXME? have min sizes for controls & then calc overall min
static const SIZE KMinimiumWindowSize = { 300, 250 };

/* how long a device is shown in Removed or Arrived state */
const DWORD KArrivalOrRemovalTimeDefault = 5;
const DWORD KArrivalOrRemovalTimeMaximum = 30;



class AppControlPos;
class AppWindowPos;


class BootloaderParams
{
public:
    DeviceInfo *blDev;
};


BOOL CALLBACK MonitorDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
BOOL NotifyRfidlerList(HINSTANCE hInst, HWND hWnd, NM_LISTVIEW *pNm);
BOOL NotifyRfidlerHeader(LPNMHEADER pNmHdr);
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DeviceDetailsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

#if defined(ENABLE_BOOTLOADER_FLASH_DIALOGS) || defined(_DEBUG)
INT_PTR CALLBACK BootloaderDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
#endif

BOOL GetProgramFilename(wchar_t **fname);
void CheckProgramShortcuts(const wchar_t *shortcut, BOOL *aDeskLinkExists, BOOL *aStartlinkExists);
BOOL CheckLinkname(const wchar_t *shortcut, int csidl);
wchar_t *CreateLinkname(const wchar_t *shortcut, int csidl);
void CreateOrBreakLink(IShellLink *psl, const wchar_t *shortcut, int csidl, BOOL aMakeShortcut);
void CreateProgramShortcuts(const wchar_t *fname, const wchar_t *shortcut, BOOL aDesktopShortcut, BOOL aStartupShortcut,
    BOOL aDeskLinkExists, BOOL aStartlinkExists);
BOOL CALLBACK InstallConfigDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
ATOM RegisterMainWindow (HINSTANCE hInstance);
void GetInitialControlPositions(HWND hWnd, AppWindowPos *wnd);
void RecalcControlPositions(HWND hWnd, AppWindowPos *wnd);
void MoveMainWindow(HWND hWnd, HINSTANCE hInst);
void LVColumnClickAndSort(int newOrder, HWND hwndFrom);
void LVInfoTip(LPNMLVGETINFOTIP pGetInfoTip);
void LVRightClickContextMenu(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem);
void LVSelectedItemContextMenu(HINSTANCE hInst, HWND hWnd, HWND hWndLV);
void LVItemDoubleClick(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem);
void LVEmptyViewTest(NMLVEMPTYMARKUP *emptyMarkup);
void ContextMenuClipboardSelect(HWND hWndLV, DeviceInfo *dev, int selection);
void ContextMenuPopup(HINSTANCE hInst, HWND hWnd, HWND hWndLV, DeviceInfo *dev, POINT scrPt);
void DefaultContextMenuPopup(HINSTANCE hInst, HWND hWnd, HWND hWndLV, POINT lvWndPt);
DeviceInfo *DevInfoFromListItem(HWND hWndLV, int iItem);
DeviceInfo *DevInfoFromListPoint(HWND hWndLV, int iItem, POINT pt);


struct LaunchParams {
    HINSTANCE   launchInstance;
    BOOL        launchFromStartup;
};


/*
    Crib notes on how ListView should work
    ======================================

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


/* real code begins here ... */

int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE /* hPrevInstance */,
    PSTR /* szCmdLine not useful on Win32 as we don't get Unicode parameters */,
    int /* iCmdShow, does not seem useful to do anythingh with this */
)
{
    ATOM ClassId;
    INITCOMMONCONTROLSEX ccInit;

    /* Initialisation */
    ClassId = RegisterMainWindow (hInstance);

    if (!ClassId) {
        MessageBox(NULL, L"Unable to create main window", szAppName, MB_OK | MB_ICONWARNING);
        return 3;
    }

    // we use the listview & imagelist from 'Common Controls'
    ZeroMemory(&ccInit, sizeof(ccInit));
    ccInit.dwSize = sizeof(ccInit);
    ccInit.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&ccInit);
    // need Microsoft COM setup for handling shortcuts
    CoInitialize(NULL);

    // create a parameter block, eg including launch from Startup flag
    LaunchParams launch = { hInstance, FALSE };

    // use to identify when launched from Startup Shortcut, or use GetCommandLineW()
    LPWSTR cmdLine = GetCommandLineW();
    if (wcsstr(cmdLine, KStartupArgument)) {
        launch.launchFromStartup = TRUE;
    }

    // simply use DialogBoxParam to show window
    INT_PTR result = DialogBoxParam (hInstance, MAKEINTRESOURCE(IDD_MONITOR), 0, MonitorDlgProc, (LPARAM) &launch);

    CoUninitialize();
    return result;
}   /* WinMain() */



ATOM RegisterMainWindow (HINSTANCE hInstance)
{
    WNDCLASSEX  WndClass;

    WndClass.cbSize        = sizeof (WndClass);
    WndClass.style         = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc   = DefDlgProc;                // MainWndProc;
    WndClass.cbClsExtra    = 0;
    WndClass.cbWndExtra    = DLGWINDOWEXTRA;
    WndClass.hInstance     = hInstance;
    // Visual Studio 2010 bug - does not allow setting Class of Dialog template, so icon given here wont be used for our main window
    WndClass.hIcon         = NULL;
                            /* (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_RFIDLER),
                                    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR); */
    WndClass.hCursor       = LoadCursor (NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH) GetStockObject (LTGRAY_BRUSH);
    WndClass.lpszMenuName  = NULL;
    WndClass.lpszClassName = L"RFIDmonitor";
    WndClass.hIconSm       = NULL;
    return RegisterClassEx (&WndClass);
}   /* RegisterMainWindow() */


#if defined(_DEBUG)
// printf formatted messages to debug port
void PrintDebugStatus(const wchar_t *format, ...)
{
    HRESULT hr;
    static wchar_t msgbuff[1024];
    va_list argptr;
    va_start(argptr, format);

    hr = StringCbVPrintf(msgbuff, sizeof(msgbuff), format, argptr);
    if (SUCCEEDED(hr)) {
        OutputDebugString(msgbuff);
    }
}
#endif


/* info for managing main window during resize */
#define FLAG_GROUP_VERTICAL_POS     0x000000FF
#define FLAG_TOP_NOMOVE             0x00000001
#define FLAG_HEIGHT_FIXED           0x00000002
#define FLAG_BOTTOM_TRACK           0x00000004

#define FLAG_GROUP_HORIZONTAL_POS   0x0000FF00
#define FLAG_LEFT_NOMOVE            0x00000100
#define FLAG_WIDTH_FIXED            0x00000200
#define FLAG_RIGHT_TRACK            0x00000400


class AppControlPos {
public:
    int         ctlId;          /* item id on dialog */
    unsigned    ctlPosRules;    /* our repositioning rules */
    HWND        ctlHWnd;        /* control's handle */
    RECT        ctlRect;        /* initial control position & dimensions */
    BOOL        ctlHidden;      /* hidden because current window size is too small */
    // TODO? add minimum control size
};


class AppWindowPos {
public:
    AppControlPos   *wndCtrls;
    unsigned        wndCtlCount;
    SIZE            wndSize;
};


void GetInitialControlPositions(HWND hWnd, AppWindowPos *wnd)
{
    RECT wndRect;

    /* get control initial positions */
    if (GetClientRect(hWnd, &wndRect)) {
        unsigned idx;
        AppControlPos *ctl;

        wnd->wndSize.cx = wndRect.right - wndRect.left;
        wnd->wndSize.cy = wndRect.bottom - wndRect.top;

        for (idx = 0; idx < wnd->wndCtlCount; idx++) {
            ctl = wnd->wndCtrls + idx;
            // if valid control
            if (ctl->ctlId) {
                HWND hCtl= GetDlgItem(hWnd, ctl->ctlId);

                if (hCtl) {
                    ctl->ctlHWnd = hCtl;

                    /* get control corners */
                    GetWindowRect(hCtl, &ctl->ctlRect);
                    /* convert screen co-ordinates to positions in dialog client area */
                    MapWindowPoints(NULL, hWnd, (LPPOINT) &ctl->ctlRect, 2);
                } /* valid hCtl handle */
            }
        } /* for */
    }
}   /* GetInitialControlPositions() */


// stretch / move controls in response to window resize
void RecalcControlPositions(HWND hWnd, AppWindowPos *wnd)
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
        UINT           uFlags = SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE;
        AppControlPos  *ctl = wnd->wndCtrls + idx;
        RECT           *rt = &ctl->ctlRect;

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
    
        // height change?
        if ((increaseH != 0) && (ctl->ctlPosRules & FLAG_GROUP_VERTICAL_POS)) {
            if (ctl->ctlPosRules & FLAG_BOTTOM_TRACK) {
                rt->bottom += increaseH;
                if (ctl->ctlPosRules & FLAG_HEIGHT_FIXED) {
                    rt->top += increaseH;
                    uFlags &= ~SWP_NOMOVE;
                } else { // ctl->ctlPosRules & FLAG_TOP_NOMOVE
                    uFlags &= ~SWP_NOSIZE;
                }
            }
        }

        // reposition / resize ctl->ctlHWnd
        DeferWindowPos(hdwp, ctl->ctlHWnd, NULL, rt->left, rt->top, rt->right - rt->left, rt->bottom - rt->top, uFlags);
    }

    EndDeferWindowPos(hdwp);
}


/*
  If possible restore position of the window from last time it is was run.
  Otherwise hacky stuff to position main window because CW_USERDEFAULT positioning does not work for dialog based windows,
  as we don't want to be in top left corner of the screen.
  */
void MoveMainWindow(HWND hWnd, HINSTANCE hInst)
{
    RECT rc;

    // get stored position/size from registry
    const MonOptions &opt = DevTracker.GetOptions();

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
        HWND hW = CreateWindow(L"RFIDmonitor", L"Invisible Touch", WS_OVERLAPPEDWINDOW,
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
    static HINSTANCE        hInst = 0;
    static HWND             hWndLV = NULL;
    static HWND             hWndStatusBar = NULL;
    static HWND             hWndListHeader = NULL;
    static UINT             TbCreatedNotification = 0;
    static UINT             currentTab = 0; // Tab 0 is always DeviceView
    static ITaskbarList3*   pTbList = NULL; // Windows >= 7 Taskbar COM interface
    // data to support resizing of window
    static AppControlPos    MainControls[] =
    {
        { IDC_MAIN_TAB_CONTROL, FLAG_TOP_NOMOVE | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
        { IDC_RFIDLERLIST, FLAG_TOP_NOMOVE | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
        { IDC_STATUSBAR,  FLAG_HEIGHT_FIXED | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
    };

    static AppWindowPos MainWnd = {
        MainControls,
        sizeof(MainControls) / sizeof(AppControlPos),
    };


    /* locals */
    BOOL handled = FALSE;

    switch (iMsg) {
    case WM_INITDIALOG: /* from CreateDialog() */
        {
            struct LaunchParams *pLaunch = (struct LaunchParams*) lParam;

            hInst = pLaunch->launchInstance;

            // set System Menu Icon for dialog
            SetClassLong(hWnd, GCL_HICON, (LONG) LoadIcon(hInst, MAKEINTRESOURCE(IDI_RFIDLER)));

            // create / remember key child windows
            hWndLV = GetDlgItem(hWnd, IDC_RFIDLERLIST);
            hWndListHeader = ListView_GetHeader(hWndLV);

            // Create Status Bar with sizing grip at bottom of window
            hWndStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP, L"", hWnd, IDC_STATUSBAR);

            // prepare support for resizing / moving child controls when dialog is resized
            GetInitialControlPositions(hWnd, &MainWnd);

            // Check for Windows >= 7
            if (CheckWindowsVersion(WinAtLeast7)) {
                /* Request notification when our Taskbar button is created,
                   can occur multiple times if Windows Shell restarts.
                 */
                TbCreatedNotification = RegisterWindowMessage(L"TaskbarButtonCreated");
                if (TbCreatedNotification) {
                    // obscurely documented secret sauce to actually get the notification
                    ChangeWindowMessageFilterEx(hWnd, TbCreatedNotification, MSGFLT_ALLOW, NULL);
                }
            }

            // create Plug & Play device tracking stuff
            DevTracker.Initialize(hWnd, hWndLV, hWndStatusBar, hWndListHeader, hInst, pLaunch->launchFromStartup);

            // restore old window position & size if any, or use CW_USEDEFAULT positioning
            MoveMainWindow(hWnd, hInst);
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
                if (GetWindowPlacement(hWnd, &place)) {
                    // save window placement
                    DevTracker.GetOptions().SaveWindowInfo(place.showCmd, place.rcNormalPosition);
                }
#if defined(_DEBUG)
                // log Window Min/Normal/Max
                PrintDebugStatus(L"place.showCmd %i\n", place.showCmd);
#endif
            }
        }
        handled = TRUE;
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
        handled = TRUE;
        break;

    case WM_COMMAND: // handle button, menu selections, ...
        {
            int wID = LOWORD (wParam);
            //int wNotification = HIWORD(wParam);
            //HWND hChild = (HWND) lParam;

            switch (wID) {
            case ID_HELP_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_HELP_ABOUT), hWnd, AboutDlgProc);
                handled = TRUE;
                break;

                // change type of view
            case ID_VIEW_LARGE_ICONS:
            case ID_VIEW_SMALL_ICONS:
            case ID_VIEW_DETAILS:
            case ID_VIEW_TILES: // Tile view must be supported, as we specify comctrl32 DLL v6.0 in manifest
                if (0 == currentTab) {
                    DevTracker.SetViewStyle(wID, FALSE);
                }
                handled = TRUE;
                break;

            case ID_VIEW_DEF_COL_WIDTHS:
                if (0 == currentTab) {
                    // restore default column widths
                    DevTracker.DefaultListColumnWidths();
                }
                handled = TRUE;
                break;

            case ID_VIEW_FIT_COL_WIDTHS:
                if (0 == currentTab) {
                    DevTracker.FitListColumnWidths();
                }
                handled = TRUE;
                break;

            case ID_SETTINGS_CONFIG_SHORTCUTS: // dialog IDD_CONFIGSHORTCUTS
                DialogBoxParam (hInst, MAKEINTRESOURCE(IDD_CONFIGSHORTCUTS), hWnd,
                    InstallConfigDlgProc, 0);
                handled = TRUE;
                break;

            case ID_SETTINGS_DEVTYPES:
            case ID_SETTINGS_DEVNOTIFICATIONS:
                DialogBoxParam (hInst, MAKEINTRESOURCE(IDD_OPTIONS), hWnd,
                    OptionsDlgProc, wID);
                handled = TRUE;
                break;

            case ID_MONITOR_EXIT:
                EndDialog (hWnd, 0);
                handled = TRUE;
                break;
            }
        } // WM_COMMAND
        break;

    case WM_NOTIFY:
        {
            NMHDR *pNm = (NMHDR *) lParam;

            if (IDC_RFIDLERLIST == wParam) {
                handled = NotifyRfidlerList(hInst, hWnd, (NM_LISTVIEW *) pNm);
            } else if (IDC_MAIN_TAB_CONTROL == wParam) {
                /* TODO? handle TTN_GETDISPINFO (display tooltip text) for the new Tab Control
                LPNMTTDISPINFO nmtdi = (LPNMTTDISPINFO) lParam;
                */
#if defined(_DEBUG)
                TabControlNotificationDebugReport(L"IDC_MAIN_TAB_CONTROL", pNm);
#endif
            } else if (!wParam && lParam) {
                // no wParam, probably from ListView's Header?
                if (pNm->hwndFrom == hWndListHeader) {
                    handled = NotifyRfidlerHeader((LPNMHEADER) pNm);
                }
            }

#if defined(_DEBUG)
            if (!handled && (NM_CUSTOMDRAW != pNm->code) && (WM_KILLFOCUS != pNm->code) && (WM_SETFOCUS != pNm->code) && (LVN_HOTTRACK != pNm->code)) {
                PrintDebugStatus(L"MonitorDlgProc WM_NOTIFY code 0x%x\n", pNm->code);
            }
#endif
        }
        break;

    case WM_CONTEXTMENU: // Context Menu for ListView (should only be that VK_APPS or Shift+F10 come here)
        if (0 == currentTab) {
            if ((wParam == (WPARAM) hWndLV) && (lParam == 0xFFFFFFFF)) {
                if (ListView_GetSelectedCount(hWndLV) > 0) {
                    LVSelectedItemContextMenu(hInst, hWnd, hWndLV);
                } else {
                    // default Context Menu when Device List is displayed
                    POINT lvPoint;
                    lvPoint.x = 50;
                    lvPoint.y = 50;

                    // find current size of ListView, & calc centre
                    for (unsigned idx = 0; idx < MainWnd.wndCtlCount; idx++) {
                        AppControlPos  *ctl = MainWnd.wndCtrls + idx;
                        if (ctl->ctlHWnd == hWndLV) {
                            lvPoint.x = ctl->ctlRect.right / 3;
                            lvPoint.y = ctl->ctlRect.bottom / 3;
                            break;
                        }
                    }

                    // display default context menu
                    DefaultContextMenuPopup(hInst, hWnd, hWndLV, lvPoint);
                }
            }
        }
        // TODO context menu for Bootloader, Serial Terminal tabs
        handled = TRUE;
        break;

    case WM_DEVICECHANGE:
        DevTracker.OnDeviceChange((UINT) wParam, lParam);
        handled = TRUE;
        break;

    case WM_SETTINGCHANGE:
#if defined(_DEBUG)
        // TODO check if time / date format has changed, reformat ArrivalTime column
        if (wParam == 0) {
            // could be locale change
            if (lParam == NULL) {
                PrintDebugStatus(L"WM_SETTINGCHANGE wParam Null, lParam NULL\n");
            } else {
                PrintDebugStatus(L"WM_SETTINGCHANGE wParam Null, lParam %.16s\n", lParam);
            }
        }
#endif
        break;

    case WM_TIMECHANGE:
        // TODO check if timezone or daylight saings status details have changed
#if defined(_DEBUG)
        PrintDebugStatus(L"WM_TIMECHANGE wParam 0x%x, lParam %p\n", wParam, lParam);
#endif
        break;

    case WM_TIMER:
        switch (wParam)
        {
        case DEV_FAST_SCAN_TIMER_MAGICNUMBER:
        case DEV_LAZY_SCAN_TIMER_MAGICNUMBER:
            DevTracker.ScanRfidlerDevices();
            handled = TRUE;
            break;
        case ARRIVAL_TIMER_MAGICNUMBER:
            DevTracker.UpdateArrivedAndRemovedDevices();
            handled = TRUE;
            break;
        case REGISTRY_SAVE_MAGICNUMBER:
            DevTracker.GetOptions().RegistrySaveChangedValues(FALSE);
            handled = TRUE;
            break;
        case CANCEL_CONTEXTMENU_MAGICNUMBER:
            SendMessage(hWnd, WM_CANCELMODE, WPARAM(0), LPARAM(0));
            DevTracker.CancelContextMenuTimer();
            handled = TRUE;
            break;
        }
        break;

    case WM_CLOSE:
        EndDialog (hWnd, 0);
        handled = TRUE;
        break;

    case WM_DESTROY: /* cleanup & exit */
        DevTracker.GetOptions().RegistrySaveChangedValues(TRUE);
        DevTracker.Cleanup();

        // release Taskbar COM interface
        if (pTbList) {
            pTbList->Release();
            pTbList = NULL;
        }
        // close program
        PostQuitMessage (0);
        handled = TRUE;
        break;

    default:
        if ((TbCreatedNotification != 0) && (TbCreatedNotification == iMsg)) {
            // initial Taskbar button creation, or Windows Explorer has restarted
            pTbList = NULL;

            // if we get the interface then intialise (note using C++ here)
            if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_ALL, IID_ITaskbarList3, (void**)&pTbList))) {
                pTbList->HrInit();
            }
            handled = TRUE;
        }
        break;
    }

    // TRUE = handled here, FALSE = pass to default handling
    return handled;
}   /* MonitorDlgProc() */


BOOL NotifyRfidlerList(HINSTANCE hInst, HWND hWnd, NM_LISTVIEW *pNm)
{
    switch(pNm->hdr.code) {
    case LVN_COLUMNCLICK:
        LVColumnClickAndSort(pNm->iSubItem, pNm->hdr.hwndFrom);
        return TRUE;

    case LVN_GETINFOTIP:
        // tooltip when mouse hovers over device in view
        LVInfoTip((LPNMLVGETINFOTIP)pNm);
        return TRUE;

    case NM_RCLICK: // right click: device menu
        LVRightClickContextMenu(hInst, hWnd, (LPNMITEMACTIVATE) pNm);
        return TRUE;

    case LVN_ITEMACTIVATE:
        LVItemDoubleClick(hInst, hWnd, (LPNMITEMACTIVATE)pNm);
        return TRUE;

    case LVN_GETEMPTYMARKUP:
        // bug: documented way of setting empty ListView text, not working for me (Windows 7)
        LVEmptyViewTest((NMLVEMPTYMARKUP *) pNm);
        return TRUE;

    case (LVN_FIRST-61):
        // LVN_GETEMPTYTEXTW undocumented way of setting empty ListView text, not working for me (Windows 7)
        {
            NMLVDISPINFO *nm = (NMLVDISPINFO *)pNm;
            if (nm->item.mask == LVIF_TEXT && nm->item.pszText) {
                StringCchCopy(nm->item.pszText, nm->item.cchTextMax, L"No RFIDlers connected.");
            }
        }
        return TRUE;

    default:
#if defined(_DEBUG)
        ListViewNotificationDebugReport(L"DeviceList", pNm);
#endif
        break;
    }
    return FALSE;
}


BOOL NotifyRfidlerHeader(LPNMHEADER pNmHdr)
{
    if ((pNmHdr->hdr.code == HDN_ITEMCHANGEDW) && (HDI_WIDTH & pNmHdr->pitem->mask)) {
        DevTracker.GetOptions().SetDetailsColumnWidth(pNmHdr->iItem, pNmHdr->pitem->cxy);
        return TRUE;
    }

    // event logging is noisy, only do this in Debug build
#if _DEBUG
    HeaderNotificationDebugReport(L"DeviceView", pNmHdr);
#endif

    return FALSE;
}


HWND InitTabbedDialog(HWND hWndTab, int itemId, wchar_t *tabTitle, LPCWSTR lpTemplateName,
        DLGPROC lpDialogFunc, LPARAM dwInitParam, BOOL showDialog)
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
        // select & show initial tab
        if (showDialog) {
            if (itemId != 0) {
                TabCtrl_SetCurSel(hWndTab, itemId);
            }
            ShowWindow(child, SW_SHOW);
        }
    }
    return child;
}


/* retry wrapper around GetModuleFileName() with growing buffer */
BOOL GetProgramFilename(wchar_t **fname)
{
    unsigned sz = 64;
    DWORD    res;
    wchar_t  *f;

    do {
        f = (wchar_t *) calloc(sz, sizeof(wchar_t));
        if (f == NULL) {
            /* OOM */
            return FALSE;
        }

        res = GetModuleFileName(NULL, f, sz);
        if ((res > 0) && (res < sz)) {
            res += 1; // account for null terminator

            // try to shrink allocation 
            if ( (sz - res) >= 16) {
                wchar_t *f2 = (wchar_t *) realloc(f, res * sizeof(wchar_t));
                if (f2) {
                    f = f2;
                }
            }

            *fname = f;
            return TRUE;
        }

        free(f);
        f = NULL;
        if (res == 0) {
            // function error
            break;
        }

        sz = (sz + (sz / 2) + 15) & ~15; // increase buffer a bit, rounding to nice binary values
    } while (sz < 50000);

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
    wchar_t lpPath[MAX_PATH];   // buffer for receiving Folder path
    wchar_t *link = NULL;

    HRESULT hRes = SHGetSpecialFolderLocation(NULL, csidl, &pidl);
    if (SUCCEEDED(hRes)) {
        if (SHGetPathFromIDList( pidl, lpPath )) {
            // +3 for '\' and double nil terminator
            size_t len = 3 + wcslen(lpPath) + wcslen(shortcut);

            link = (wchar_t *) calloc(len, sizeof(wchar_t));
            if (link) {
                wcscpy_s(link, len, lpPath);
                wcscat_s(link, len, L"\\");
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
#if defined(_DEBUG)
        PrintDebugStatus(L"linkname = %s\n", linkname);
#endif
        if (aMakeShortcut) {
            hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
            if (SUCCEEDED(hres)) {
                // Save the link by calling IPersistFile::Save.
                hres = ppf->Save(linkname, FALSE);
#if defined(_DEBUG)
                if (!SUCCEEDED(hres)) {
                    PrintDebugStatus(L"IID_IPersistFile.Save fail 0x%x\n", hres);
                }
#endif
                ppf->Release();
#if defined(_DEBUG)
            } else {
                PrintDebugStatus(L"QueryInterface(IID_IPersistFile... fail 0x%x\n", hres);
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


void CreateProgramShortcuts(const wchar_t *fname, const wchar_t *shortcut, BOOL aDesktopShortcut, BOOL aStartupShortcut,
    BOOL aDeskLinkExists, BOOL aStartlinkExists)
{
    const wchar_t *desc = L"RFIDler Monitor";

    // something has changed from old settings?
    if (fname && ((aDesktopShortcut != aDeskLinkExists) || (aStartupShortcut != aStartlinkExists))) {
        IShellLink *psl;

        // connect to Windows Shell
        HRESULT hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
            IID_IShellLink, (void**)&psl);

        if (SUCCEEDED(hres)) {
            // Set the path to the shortcut target and add the description. 
            hres = psl->SetPath(fname); 
#if defined(_DEBUG)
            if (!SUCCEEDED(hres)) {
                PrintDebugStatus(L"SetPath(%s) fail 0x%x\n", fname, hres);
            }
#endif
            hres = psl->SetDescription(desc); 
#if defined(_DEBUG)
            if (!SUCCEEDED(hres)) {
                PrintDebugStatus(L"SetDescription(%s) fail 0x%x\n", desc, hres);
            }
#endif

            // create or remove shortcuts from: current Desktop, Statup Group
            if (aDesktopShortcut != aDeskLinkExists) {
                CreateOrBreakLink(psl, shortcut, CSIDL_DESKTOP, aDesktopShortcut);
            }
            if (aStartupShortcut != aStartlinkExists) {
                if (aStartupShortcut) {
                    // add Argument to indicate launch from Startup Shortcut
                    hres = psl->SetArguments(KStartupArgument);
#if defined(_DEBUG)
                    if (!SUCCEEDED(hres)) {
                        PrintDebugStatus(L"SetArgument(%s) fail 0x%x\n", KStartupArgument, hres);
                    }
#endif
                }

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
    LPARAM // lParam
)
{
    const wchar_t   *shortcut = L"RFIDler Monitor.lnk";
    static wchar_t  *fname = NULL;
    static BOOL     deskLinkExists;
    static BOOL     startlinkExists;

    BOOL handled = FALSE;

    // Dialog for configuring program shortcuts
    switch (iMsg) {
    case WM_INITDIALOG:
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
                handled = TRUE;
                break;
            case IDCANCEL:
                EndDialog(hWnd, 1);
                handled = TRUE;
                break;
            case IDC_APPLY:
                {
                    BOOL newDeskLink = (BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_DESKYES));
                    BOOL newStartLink = (BST_CHECKED == IsDlgButtonChecked(hWnd, IDC_STARTYES));

                    CreateProgramShortcuts(fname, shortcut,
                        newDeskLink, newStartLink, deskLinkExists, startlinkExists);
                    deskLinkExists = newDeskLink;
                    startlinkExists = newStartLink;
                }
                EnableWindow(GetDlgItem(hWnd, IDC_APPLY), FALSE);
                handled = TRUE;
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
                handled = TRUE;
                break;
            }
        }
        break;

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        handled = TRUE;
        break;

    case WM_DESTROY: // dialog closing
        ReleaseString(fname);
        handled = TRUE;
        break;
    }

    // TRUE = handled here, FALSE = pass to default handling
    return handled;
}   /* InatallConfigDlgProc() */


void ReleaseString(wchar_t *&string)
{
    if (string) {
        free(string);
        string = NULL;
    }
}

// program description and copyright licensing info
static const wchar_t *helpTitle = L"Help About RFIDLer Monitor %u.%u.%u";
static const wchar_t *helpText =
    L"RFIDler LF appears to the computer as a USB serial port, and works with a standard \r\n"
    L"Windows driver for USB serial ports, usbser.sys.\r\n"
    L"\r\n"
    L"This RFIDler Monitor presents a list of the currently connected RFIDler LF devices. \r\n"
    L"If an RFIDler LF is connected and working it tells you what COM port name Windows \r\n"
    L"has assigned to the device. If the RFIDler is connected in Bootloader mode, waiting \r\n"
    L"to be programmed this is shown too. (Some other Microchip development tools in \r\n"
    L"Bootloader mode look the same to the Monitor and are therefore shown as well.)\r\n"
    L"\r\n"
    L"Options add to the display such things as Microchip development boards such as UBW32,\r\n"
    L"other serial ports or modems, similar serial devices remembered by Windows but not\r\n"
    L"currently connected. \r\n"
    L"\r\n"
    L"\r\n"
    L"Copyright (c) 2014 - 2016 Anthony Naggs. All rights reserved.\r\n"
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



/* IDD_HELP_ABOUT */
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM /* lParam */)
{
#define KTitleSize 100
    static wchar_t dialogTitle[KTitleSize];

    switch (iMsg) {
    case WM_INITDIALOG:
        {
            wchar_t *fname = NULL;
            BOOL    gotfileversion = FALSE;

            // get version number from exe
            if (GetProgramFilename(&fname)) {
                DWORD verSize = GetFileVersionInfoSize(fname, NULL);
                if (verSize > 0) {
                    void *buffer = calloc(1, verSize);

                    if (buffer) {
                        void *fInfo = NULL;
                        UINT rxInfoSize = 0;

                        if (GetFileVersionInfo(fname, 0, verSize, buffer) && 
                                VerQueryValue(buffer, L"\\", &fInfo, &rxInfoSize) && fInfo && rxInfoSize) {
                            VS_FIXEDFILEINFO *info = (VS_FIXEDFILEINFO *) fInfo;

                            if (info->dwSignature == 0xfeef04bd) {
                                StringCchPrintf(dialogTitle, KTitleSize, helpTitle,
                                    LOWORD(info->dwProductVersionMS),
                                    HIWORD(info->dwProductVersionLS),
                                    LOWORD(info->dwProductVersionLS));
                                gotfileversion = TRUE;
                            }
                        }

                        free(buffer);
                    }
                }
                free(fname);
            }

            if (!gotfileversion) {
                // at least at 2.0.0
                StringCchPrintf(dialogTitle, KTitleSize, helpTitle, 2, 0, 0);
            }
            SetWindowText(hDlg, dialogTitle);

            SetWindowText(GetDlgItem(hDlg, IDC_HELP_TEXT), helpText);
        }
        // return TRUE  unless you set the focus to a control
        return TRUE;

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


void LVColumnClickAndSort(int sortColumn, HWND hwndFrom)
{
    if (sortColumn <= lvDispMaxSort) {
        ColumnSortParameters sortParams = DevTracker.GetViewSortOrder();
        int oldColumn = (int) sortParams.mSortType;

        // user clicked on current column header, so reverse the sort
        if (sortParams.mSortType == sortColumn) {
            sortParams.mSortReverse = !sortParams.mSortReverse;
        } else {
            sortParams.mSortType = (lvColumn) sortColumn;
            sortParams.mSortReverse = 0;
        }

        // remember sort order, trigger timed state save
        DevTracker.SetViewSortOrder(sortParams);
        // actually sort items
        ListView_SortItems(hwndFrom, DeviceInfo::ViewSortCompareProc, (LPARAM)(&sortParams));

        // move sort order mark between columns
        HWND hWndHdr = ListView_GetHeader(hwndFrom);
        if (hWndHdr) {
            HDITEM hdrItem;
            hdrItem.mask = HDI_FORMAT;

            // remove sort up / down mark from old column
            if ((oldColumn != sortColumn) && Header_GetItem(hWndHdr, oldColumn, &hdrItem) && (hdrItem.fmt & (HDF_SORTUP | HDF_SORTDOWN))) {
                hdrItem.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
                Header_SetItem(hWndHdr, oldColumn, &hdrItem);
            }

            // add mark to new column
            if (Header_GetItem(hWndHdr, sortColumn, &hdrItem)) {
                if (sortParams.mSortReverse) {
                    hdrItem.fmt &= ~HDF_SORTUP;
                    hdrItem.fmt |= HDF_SORTDOWN;
                } else {
                    hdrItem.fmt &= ~HDF_SORTDOWN;
                    hdrItem.fmt |= HDF_SORTUP;
                }
                Header_SetItem(hWndHdr, sortColumn, &hdrItem);
            }
        } // valide new values
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

    // found a device under the mouse position?
    if (dev) {
        // with our DeviceInfo pointer we can now get the tooltip message
        const wchar_t *infoTip = dev->InfoTip(TRUE);

        StringCchPrintf(pGetInfoTip->pszText, pGetInfoTip->cchTextMax, L"%s", infoTip);
#if defined(_DEBUG)
        PrintDebugStatus(L"InfoTip = %s\n", infoTip);
#endif
    }
}


void LVRightClickContextMenu(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem)
{
#if defined(_DEBUG)
    PrintDebugStatus(L"NM_RCLICK iItem = %i, iSubItem = %i, lParam = %p, point = %i,%i (hWnd 0x%x, hwndFrom %x, idFrom %u)\n",
        lpnmitem->iItem, lpnmitem->iSubItem, lpnmitem->lParam,
        lpnmitem->ptAction.x, lpnmitem->ptAction.y,
        hWnd, lpnmitem->hdr.hwndFrom, lpnmitem->hdr.idFrom);
#endif

    if (IDC_RFIDLERLIST == lpnmitem->hdr.idFrom) {
        /* 
            lpnmitem->lParam points to something, but doesn't appear to be useful.
            Need to map mouse coordinates to our Device Info.
        */
        DeviceInfo *dev = DevInfoFromListPoint(lpnmitem->hdr.hwndFrom,
            lpnmitem->iItem, lpnmitem->ptAction);

        if (dev) {
            ContextMenuPopup(hInst, hWnd, lpnmitem->hdr.hwndFrom, dev, lpnmitem->ptAction);
        } else {
            DefaultContextMenuPopup(hInst, hWnd, lpnmitem->hdr.hwndFrom, lpnmitem->ptAction);
        }
    }
}


void LVSelectedItemContextMenu(HINSTANCE hInst, HWND hWnd, HWND hWndLV)
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
                ContextMenuPopup(hInst, hWnd, hWndLV, dev, cliPt);
            }
            break;
        }
    }
}


void LVEmptyViewTest(NMLVEMPTYMARKUP *emptyMarkup)
{
    // BUG: this doesn't have any effect, from documentation we expect this text to show when ListView is empty
    StringCchCopy(emptyMarkup->szMarkup, L_MAX_URL_LENGTH, L"No connected RFIDlers");
    emptyMarkup->dwFlags = EMF_CENTERED;
}


void ContextMenuClipboardSelect(HWND hWndLV, DeviceInfo *dev, int selection)
{
    const wchar_t *strings[5] = { NULL, NULL, NULL, NULL, NULL };
    const wchar_t *string;
    int i = 0;

    switch(selection) {
    case ID_CONTEXT_COPYPORT_NAME:
        string = dev->PortName();
        if (string) {
            strings[i++] = string;
        }
        break;
    }

    // found strings to place in Clipboard?
    if (i > 0) {
        int j = 0;
        size_t len = 0;

        for (j = 0; j < i; j++) {
            // count the characters, tab field separators, & NIL
            len += 1 + wcslen(strings[j]);
        }

        HGLOBAL hglbCopy;
        hglbCopy = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(wchar_t));

        if (hglbCopy && OpenClipboard(hWndLV)) {
            EmptyClipboard();

            // Lock the handle and copy the text to the buffer.
            LPTSTR lptstrCopy = (LPTSTR) GlobalLock(hglbCopy); 

            for (j = 0; j < i; j++) {
                if (j > 0) {
                    StringCchCat(lptstrCopy, len, L"\t");
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


void ContextMenuPopup(HINSTANCE hInst, HWND hWnd, HWND hWndLV, DeviceInfo *dev, POINT scrPt)
{
    assert(dev);
    int defaultitem = 0;

    // context menu
    LPCWSTR lpMenuName = NULL;

    ClientToScreen(hWndLV, &scrPt);

    switch (dev->DeviceType()) {
    case DevRfidlerCom:
        lpMenuName = MAKEINTRESOURCE(IDR_RFIDLER_CONTEXT);
        defaultitem = ID_CONTEXT_RFIDLER_DETAILS;
        break;
    case DevMicroDevBoard:
    case DevArduinoSerial:
    case DevOtherSerial:
        lpMenuName = MAKEINTRESOURCE(IDR_COMPORT_CONTEXT);
        defaultitem = ID_CONTEXT_PORT_DETAILS;
        break;
    case DevMicroBootloader:
        lpMenuName = MAKEINTRESOURCE(IDR_BOOTLOADER_CONTEXT);
        defaultitem = ID_CONTEXT_BOOTLOADER_DETAILS;
        break;
    case DevUnconfigRfidlerCom:
    case DevUnconfigMicroDevBoard:
    case DevHalfKayBootloader:
    default:
        // TODO Context Menu for Unconfigured device? Other Bootloader types? Maybe help text?
        break;
    }

    if (lpMenuName) {
        HMENU hMenu = LoadMenu(hInst, lpMenuName);
        if (hMenu) {
            HMENU hMenuTrackPopup  = GetSubMenu(hMenu, 0);

            if (defaultitem) {
                // highlight default menu action in bold
                SetMenuDefaultItem(hMenuTrackPopup, defaultitem, FALSE);
            }

#if !defined(ENABLE_BOOTLOADER_FLASH_DIALOGS) && !defined(_DEBUG)
            // disable development feature for release build
            // TODO bootloader support
            switch (dev->DeviceType()) {
            case DevRfidlerCom:
            case DevMicroBootloader:
                // disable BOOTLOADER FLASH menu item
                RemoveMenu(hMenuTrackPopup, ID_CONTEXT_OPEN_FOR_REFLASH, MF_BYCOMMAND); 
                break;
            }
#endif

            // ensure device node is not freed whilst we are using it
            dev->LockForContextMenu();

            // use timer to limit Popup Menu to 2 minutes
            DevTracker.KickContextMenuTimer();
            int selection = TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
                scrPt.x, scrPt.y, 0, hWnd, NULL);
            DevTracker.CancelContextMenuTimer();

#if defined(_DEBUG)
            PrintDebugStatus(L"Popup selection = %i\n", selection);
#endif
            if (selection > 0) {
                switch(selection) {
                case ID_CONTEXT_COPYPORT_NAME:
                    ContextMenuClipboardSelect(hWnd, dev, selection);
                    break;
                case ID_CONTEXT_PORT_DETAILS:
                case ID_CONTEXT_RFIDLER_DETAILS:
                case ID_CONTEXT_BOOTLOADER_DETAILS:
                        DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DEVICE_DETAILS), hWnd, DeviceDetailsDlgProc,
                            (LPARAM) dev);
                    break;
                case ID_CONTEXT_REBOOT_FOR_REFLASH: // todo implement opening COM port & rebooting Rfidler for Bootloader
                    break;
                case ID_CONTEXT_BOOTLOADER_REBOOT: // todo implement opening Bootloader & rebooting Rfidler
                    break;
#if defined(ENABLE_BOOTLOADER_FLASH_DIALOGS) || defined(_DEBUG)
                case ID_CONTEXT_OPEN_FOR_REFLASH: // TODO support Bootloader Reflash
                    if (!dev->DeleteOnUnlock()) {
                        // launch Bootloader Flash dialog
                        BootloaderParams bl;
                        bl.blDev = dev;
                        DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_BOOTLOADERFLASH), hWnd, BootloaderDlgProc,
                            (LPARAM) &bl);
                    }
                    break;
#endif
                }
            }

            dev->UnlockForContextMenu();
            DestroyMenu(hMenu);
        } // if (hMenu)
    } // if (lpMenuName)
}


// context menu when no device is selected
void DefaultContextMenuPopup(HINSTANCE hInst, HWND hWnd, HWND hWndLV, POINT lvWndPt)
{
    // context menu
    LPCWSTR lpMenuName = MAKEINTRESOURCE(IDR_LISTVIEW_CONTEXT);

    ClientToScreen(hWndLV, &lvWndPt);

    HMENU hMenu = LoadMenu(hInst, lpMenuName);
    if (hMenu) {
        HMENU hMenuTrackPopup  = GetSubMenu(hMenu, 0);
        int selection;
        int currentView = DevTracker.GetOptions().GetViewStyleButton();

        // check mark on current selection
        CheckMenuItem(hMenuTrackPopup, currentView, MF_CHECKED);

        // enable items depending on current view
        if (currentView == ID_VIEW_DETAILS) {
            EnableMenuItem(hMenuTrackPopup, ID_VIEW_DEF_COL_WIDTHS, MF_ENABLED); 
            EnableMenuItem(hMenuTrackPopup, ID_VIEW_FIT_COL_WIDTHS, MF_ENABLED); 
        }

        // use timer to limit Popup Menu to 2 minutes
        DevTracker.KickContextMenuTimer();
        selection = TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            lvWndPt.x, lvWndPt.y, 0, hWnd, NULL);
        DevTracker.CancelContextMenuTimer();

#if defined(_DEBUG)
        PrintDebugStatus(L"Popup selection = %i\n", selection);
#endif

        if (selection != currentView) {
            switch(selection) {
            case ID_VIEW_LARGE_ICONS: // NB use the same view mode identifiers as the main window menu
            case ID_VIEW_SMALL_ICONS:
            case ID_VIEW_DETAILS:
            case ID_VIEW_TILES:
            case ID_VIEW_DEF_COL_WIDTHS:
            case ID_VIEW_FIT_COL_WIDTHS:
                // just pass to window to process
                PostMessage(hWnd, WM_COMMAND, selection, 0);
                break;

            default: // menu cancel
                break;
            }
        }

        DestroyMenu(hMenu);
    }
}


void LVItemDoubleClick(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem)
{
     // launch default menu action, if any
#if defined(_DEBUG)
    PrintDebugStatus(L"LVN_ACTIVATE iItem = %i, iSubItem = %i, lParam = %p, point = %i,%i\n",
        lpnmitem->iItem, lpnmitem->iSubItem, lpnmitem->lParam,
        lpnmitem->ptAction.x, lpnmitem->ptAction.y);
#endif
    // as for Right Click lpnmitem->lParam not useful, need to map mouse coordinates to our Device Info.
    DeviceInfo *dev = DevInfoFromListPoint(lpnmitem->hdr.hwndFrom,
        lpnmitem->iItem, lpnmitem->ptAction);

    if (dev) {
        switch (dev->DeviceType()) {
        case DevRfidlerCom:
        case DevMicroDevBoard:
        case DevArduinoSerial:
        case DevOtherSerial:
            // todo future enhancement, have a default menu item
            break;
        case DevMicroBootloader:
#if defined(ENABLE_BOOTLOADER_FLASH_DIALOGS) || defined(_DEBUG)
            {
                // launch Bootloader Flash dialog
                BootloaderParams bl;
                bl.blDev = dev;
                DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_BOOTLOADERFLASH), hWnd, BootloaderDlgProc,
                    (LPARAM) &bl);
            }
#else
            // suppress unreferenced variable warnings
            hInst;
            hWnd;
#endif
            break;
        case DevUnconfigRfidlerCom:
        case DevUnconfigMicroDevBoard:
        case DevHalfKayBootloader:
        default:
            break;
        }
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
    if (iItem >= 0) {
        return DevInfoFromListItem(hWndLV, iItem);
    }

    // otherwise get item id from point first (iItem < 0)
    lvhti.pt = pt;
    ListView_SubItemHitTest(hWndLV, &lvhti);

#if defined(_DEBUG)
    PrintDebugStatus(L"LVHITTESTINFO iItem = %i, iSubItem = %i, flags = %x\n",
        lvhti.iItem, lvhti.iSubItem, lvhti.flags);
#endif

    if (lvhti.flags & LVHT_ONITEM) {
        return DevInfoFromListItem(hWndLV, lvhti.iItem);
    }

    return NULL;
}


void BootloaderEnableBaseControls(HWND hDlg, BOOL enable)
{
     EnableWindow(GetDlgItem(hDlg, IDC_ERASE), enable);
     EnableWindow(GetDlgItem(hDlg, IDC_BROWSE), enable);
     EnableWindow(GetDlgItem(hDlg, IDC_REBOOT), enable);
     EnableWindow(GetDlgItem(hDlg, IDC_SAVEHEX), enable);
}


void BootloaderEnableProgramControls(HWND hDlg, BOOL enable)
{
     EnableWindow(GetDlgItem(hDlg, IDC_PROGRAM), enable);
     EnableWindow(GetDlgItem(hDlg, IDC_VERIFY), enable);
     EnableWindow(GetDlgItem(hDlg, IDC_ERASEPROGRAMVERIFY), enable);
}


BOOL InitHexFileList(HWND hDlg)
{
    MonOptions& options = DevTracker.GetOptions();
    int historyCount = options.HexFileHistoryCount();
    BOOL result = FALSE;

    if (historyCount) {
        HWND hWndFileList = GetDlgItem(hDlg, IDC_HEX_READFILE);

        // populate file history
        for (int i = 0; i < historyCount; i++) {
            wchar_t *filename = options.HexFileHistory(i);
            if (-1 != SendMessage(hWndFileList, CB_ADDSTRING, 0, (LPARAM) filename)) {
                result = TRUE;
            }
        }
    }
    return result;
}


// printf formatted messages to report area of installer's window
void BootloaderStatus(HWND hWndStatus, const wchar_t *format, ...)
{
    HRESULT hr;
    static wchar_t msgbuff[1024];
    va_list argptr;
    va_start(argptr, format);

    hr = StringCbVPrintf(msgbuff, sizeof(msgbuff), format, argptr);
    if (SUCCEEDED(hr)) {
        SendMessage (hWndStatus, LB_ADDSTRING, 0, (LPARAM) msgbuff);
    }
}


const wchar_t *DeviceDescriptionText(DeviceInfo *pDev, const wchar_t *szLineEnding)
{
    // Device Description Strings
    static wchar_t  szBuffer[1500];
    const wchar_t   *szDetail;
    const wchar_t   *szIntro;
    unsigned        iterator;
    DeviceLocation  deviceLocation = pDev->DevLocation();
    BOOL            deviceIsUsb = (BusUSB == deviceLocation.devBusType);

    // reset buffer contents
    szBuffer[0] = 0;

    for (iterator = 0; iterator < 100; iterator++) {
        szDetail = NULL;
        szIntro = NULL;

        switch (iterator) {
        case 0: // needs descriptive text that adapts to device type?
            switch (pDev->DeviceType()) {
            case DevRfidlerCom:
            case DevMicroDevBoard:
            case DevArduinoSerial:
            case DevOtherSerial:
                szDetail = pDev->DisplayName();
                szIntro = L"Serial port: ";
                break;
            case DevMicroBootloader:
            case DevHalfKayBootloader:
            case DevUnconfigRfidlerCom:
            case DevUnconfigMicroDevBoard:
            default:
                break;
            }
            break;

        case 1:
            szDetail = pDev->DevTypeName();
            szIntro = L"Device type: ";
            break;

        case 2:
            if (pDev->DevicePresent()) {
                szDetail = pDev->LocationString();
                szIntro = deviceIsUsb ? L"Device is connected to " : L"Device is connected by ";
            }
            break;

        case 3: // USB: VID, PID, product Revision
            if (deviceIsUsb) {
                size_t offset = wcslen(szBuffer);

                StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                    L"USB Vendor Id (VID) 0x%04x, Product Id (PID) 0x%04x%s%s",
                    deviceLocation.usbVID,
                    deviceLocation.usbPID, 
                    deviceLocation.usbGotRevision ? L"," : L"",
                    szLineEnding);
                if (deviceLocation.usbGotRevision) {
                    size_t offset = wcslen(szBuffer);

                    StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                        L"    Product Revision (REV) 0x%04x%s", deviceLocation.usbRevision, szLineEnding);
                }
            }
            break;

        case 4: // Registry Maunfacturer name (usually from .inf rather than USB descriptor)
            szDetail = pDev->DeviceManufacturer();
            szIntro = L"Manufacturer: ";
            break;

        case 5: // is Device name from Setup API different from Friendly Name?
            szDetail = pDev->DeviceName();
            if (szDetail) {
                const wchar_t   *szTemp = pDev->DeviceFriendlyName();
                if (!szTemp || wcscmp(szTemp, szTemp)) {
                    szIntro = L"Product: ";
                } else {
                    szDetail = NULL;
                }
            }
            break;

        case 6: // driver install .inf file
            szDetail = pDev->DeviceDriverName();
            szIntro = L"Device Driver: ";
            break;

        case 7: // driver file
            szDetail = pDev->DeviceInfPath();
            szIntro = L"Driver install file: ";
            break;

        // TODO ensure these USB details values are read & accessible from dialog
        case 8:
            if (deviceIsUsb && deviceLocation.usbFlags) {
                szDetail = L"usbflags in registry:";
            }
            break;

        case 9:
            if (deviceIsUsb && (deviceLocation.usbFlags & KUsbFlag_osvc)) {
                size_t offset = wcslen(szBuffer);

                StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                    L"    osvc: Microsoft OS Descriptor Read %s (0x%02x), Vendor Id 0x%02x%s",
                    (deviceLocation.usbFlagOsvc & 0xFF) ? L"success" : L"failed",
                    deviceLocation.usbFlagOsvc & 0xFF,
                    (deviceLocation.usbFlagOsvc >> 8) & 0xFF,
                    szLineEnding);
            }
            break;

        case 10:
            if (deviceIsUsb && (deviceLocation.usbFlags & KUsbFlag_SkipContainerIdQuery)) {
                size_t offset = wcslen(szBuffer);

                StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                    L"    SkipContainerIdQuery: 0x%04x%s",
                    deviceLocation.usbFlagSkipContainerIdQuery, szLineEnding);
            }
            break;

        case 11:
            if (deviceIsUsb && (deviceLocation.usbFlags & KUsbFlag_IgnoreHWSerNum)) {
                size_t offset = wcslen(szBuffer);

                StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                    L"   IgnoreHWSerNum: 0x%04x%s",
                    deviceLocation.usbFlagIgnoreHWSerNum, szLineEnding);
            }
            break;

        case 12:
            if (deviceIsUsb && (deviceLocation.usbFlags & KUsbFlag_ResetOnResume)) {
                size_t offset = wcslen(szBuffer);

                StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                    L"    ResetOnResume: 0x%04x%s",
                    deviceLocation.usbFlagResetOnResume, szLineEnding);
            }
            break;

        case 13:
            if (deviceIsUsb && (deviceLocation.usbFlags & KUsbFlag_NoClearTTBufferOnCancel)) {
                size_t offset = wcslen(szBuffer);

                StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                    L"    NoClearTTBufferOnCancel: 0x%04x%s",
                    deviceLocation.usbFlagNoClearTTBufferOnCancel, szLineEnding);
            }
            break;

        case 14: // list USB segment count
            if (pDev->DevicePresent() && deviceIsUsb) {
                unsigned segCount = pDev->UsbSegmentCount();

                switch (segCount) {
                case 0:
                    break;
                case 1:
                    szDetail = L"Directly connected to USB root hub";
                    break;
                default:
                    size_t offset = wcslen(szBuffer) - 1;

                    if (offset < ARRAYSIZE(szBuffer)) {
                        StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset,
                            L"Connected through %u USB hub%s%s",
                            segCount - 1, (segCount > 2) ? L"s" : L"",
                            szLineEnding);
                    }
                    break;
                }
            }
            break;

        case 15:
            szDetail = pDev->SerialNumber();
            if (pDev->DeviceIsWindowsSerialNumber()) {
                szIntro = L"Windows generated serial number: ";
            } else {
                szIntro = L"Serial number from device: ";
            }
            break;

        case 16: // debug info for Bus Location
#if defined(_DEBUG)
            {
                size_t offset = wcslen(szBuffer) - 1;

                if (!IsEqualGUID(deviceLocation.debugBusGUID, GUID_NULL) && (offset < ARRAYSIZE(szBuffer))) {
                    GUID *g = &deviceLocation.debugBusGUID;

                    StringCchPrintf(szBuffer + offset, ARRAYSIZE(szBuffer) - offset, 
                        L"Debug: BusGUID %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                        g->Data1, g->Data2, g->Data3, g->Data4[0], g->Data4[1], g->Data4[2], 
                        g->Data4[3], g->Data4[4], g->Data4[5], g->Data4[6], g->Data4[7]);
                    // always the last line if present, so we don't currently add a line ending
                }
            }
            // fall through ...
#endif
        default:
            // end of strings, return full buffer
            return szBuffer;

        }

        // may have ptr to a const string to put in buffer
        if (szDetail) {
            if (szIntro) {
                wcscat_s(szBuffer, szIntro);
            }
            wcscat_s(szBuffer, szDetail);
            wcscat_s(szBuffer, szLineEnding);
        }
    };

    // hush compiler warning about no return value, we shouldn't reach here
    return szBuffer;
}


void SetDevDetailsDialogTitle(HWND hDlg, DeviceInfo *pDev)
{
    wchar_t szTitle[60];

    // name text corresponding to the device
    wcscpy_s(szTitle, pDev->InfoTip(FALSE));
    wcscat_s(szTitle, L" device details");
    SetWindowText(hDlg, szTitle);
}


INT_PTR CALLBACK DeviceDetailsDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /* IDD_DEVICE_DETAILS */
    static DeviceInfo *pDev;
    static HICON hIcon = NULL;

    switch (iMsg) {
    case WM_INITDIALOG:
        pDev = reinterpret_cast<DeviceInfo *> (lParam);

        // lParam = NULL would be a bug
        if (!pDev) {
#if defined(_DEBUG)
            PrintDebugStatus(L"DeviceDetailsDlgProc bad lParam\n");
#endif
            EndDialog(hDlg, 0);
        }

        // set icon corresponding to the device
        hIcon = DeviceTracker::GetIcon(pDev->DeviceImage());
        SendDlgItemMessage(hDlg, IDC_DEVICE_ICON, STM_SETICON, (WPARAM)hIcon, (LPARAM)0);

        // set Window title
        SetDevDetailsDialogTitle(hDlg, pDev);

        // display device details
        {
            const wchar_t *szDesc = DeviceDescriptionText(pDev, L"\r\n");

            if (szDesc) {
                SetWindowText(GetDlgItem(hDlg, IDC_DEV_DETAILS), szDesc);
            }
        }
        return TRUE; // TRUE unless you set the focus to a control

    case WM_COMMAND: 
        switch (LOWORD(wParam)) {
        case IDOK:
        case IDCANCEL: // Escape key
            EndDialog (hDlg, wParam);
            /* handled message */
            return 1;
        }
        break;

    case WM_DESTROY:
        if (hIcon) {
            DestroyIcon(hIcon);
            hIcon = NULL;
        }
        return TRUE;
    }

    return 0;
}   /* DeviceDetailsDlgProc() */


#if defined(ENABLE_BOOTLOADER_FLASH_DIALOGS) || defined(_DEBUG)
INT_PTR CALLBACK BootloaderDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    /* IDD_BOOTLOADERFLASH */
    static HWND             hWndReport = NULL;
    static HANDLE           h = INVALID_HANDLE_VALUE;
    static BootloaderParams *bl = NULL;

    switch (iMsg) {
    case WM_INITDIALOG:
        hWndReport = GetDlgItem(hDlg, IDC_FLASHREPORT);
        // MonOptions & DeviceInfo from lParam
        bl = (BootloaderParams *) lParam;

        // try to open device
        {
            const wchar_t *path = bl->blDev->HidDevicePath();

            if (path) {
                h = CreateFile(path, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL, OPEN_EXISTING, 0, NULL);
#if defined(_DEBUG)
                PrintDebugStatus(L"tried opening %s, %s\n", path, (h == INVALID_HANDLE_VALUE) ? L"fail" : L"success");
#endif

                if (h != INVALID_HANDLE_VALUE) {
                    BootloaderEnableBaseControls(hDlg, TRUE);
                    BootloaderStatus(hWndReport, L"Bootloader device opened");

                    if (InitHexFileList(hDlg)) {
                        BootloaderEnableProgramControls(hDlg, TRUE);
                    }
                } else {
                    // report error
                    BootloaderStatus(hWndReport, L"Bootloader device open failed (%u)", GetLastError());
                }
            } else {
                BootloaderStatus(hWndReport, L"Bootloader device not found");
            }
        }
        return TRUE; // unless you set the focus to a control

    case WM_COMMAND: 
        switch (LOWORD(wParam)) {
        case IDC_ERASE:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo Bootloader: Erase memory */
            }
            break;
        case IDC_PROGRAM:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo Bootloader: program device */
            }
            break;
        // IDC_FLASHPROGRESS               
        case IDC_HEX_READFILE:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo Bootloader: Open/Read hax file */
            }
            break;
        case IDC_BROWSE:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
                // todo SaveHexFileToHistory(const wchar_t *filename)
            }
            break;
        case IDC_VERIFY:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo Bootloader: Verify memory */
            }
            break;
        case IDC_ERASEPROGRAMVERIFY:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo Bootloader: Erase, Program, and Verify memory */
            }
            break;
        case IDC_REBOOT:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo Bootloader: Reboot device (to run programmed memory) */
            }
            break;
        case IDC_SAVEHEX:
            if (h != INVALID_HANDLE_VALUE) {
                // todo Bootloader: SaveHexFileToHistory(const wchar_t *filename)
            }
            break;

        case IDOK:
            EndDialog (hDlg, wParam);
            /* handled message */
            return 1;
        }
        break;

    case WM_DESTROY:
        if (h != INVALID_HANDLE_VALUE) {
            CloseHandle(h);
            h = INVALID_HANDLE_VALUE;
        }
    }

    return 0;
}   /* BootloaderDlgProc() */
#endif


/* end of file rfidmonitor.cpp */