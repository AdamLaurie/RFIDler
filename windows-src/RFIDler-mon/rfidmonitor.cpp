/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: rfidmonitor.cpp

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

#include <ShlObj.h>
#include <assert.h>
#include <strsafe.h>
#include <uxtheme.h> 


/*
 * This program needs to be linked with these libraries:
 * NB if any are missing from Windows SDK the Windows Driver Kit is required.
 */
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib, "SetupAPI.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma comment(lib, "version.lib")
#if defined(ENABLE_BOOTLOADER_FLASH) || defined(_DEBUG)
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

const TCHAR *szAppName = _T("RFIDler Monitor");
const TCHAR *szRfidlerHwUsbId = _T("USB\\VID_1D50&PID_6098");
const TCHAR *szMicrochipSerialHwUsbId = _T("USB\\VID_04D8&PID_000A");
const TCHAR *szMicrochipBootHwUsbId = _T("USB\\VID_04D8&PID_003C");
const TCHAR *szMicrochipBootHidId = _T("HID\\VID_04D8&PID_003C");


/* ******************** PROGRAM CONFIGURATION ********************* */
/* nominal minimum window size is 300 * 250 */
// FIXME? have min sizes for controls & then calc overall min
static const SIZE KMinimiumWindowSize = { 300, 250 };

/* how long a device is shown in Removed or Arrived state */
/* Note that the value in the Options dialog text should be kept in sync */
const DWORD KArrivalOrRemovalTimeLimit = 5;



class AppControlPos;
class AppWindowPos;


class BootloaderParams
{
public:
    DeviceInfo *blDev;
    MonOptions *blOptions;
};


static BOOL CALLBACK MonitorDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK OptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static HWND InitTabbedDialog(HWND hWndTab, int itemId, TCHAR *tabTitle, LPCWSTR lpTemplateName,
        DLGPROC lpDialogFunc, LPARAM dwInitParam);
static HWND InitShowControls(MonOptions *aOptions, HWND hWndTab);
static HWND InitNotificationControls(MonOptions *aOptions, HWND hWndTab);
static BOOL CALLBACK ShowOptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static BOOL CALLBACK NotificationsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

#if defined(ENABLE_BOOTLOADER_FLASH) || defined(_DEBUG)
static INT_PTR CALLBACK BootloaderDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
#endif

static BOOL GetProgramFilename(TCHAR **fname);
static void CheckProgramShortcuts(const wchar_t *shortcut, BOOL *aDeskLinkExists, BOOL *aStartlinkExists);
static BOOL CheckLinkname(const wchar_t *shortcut, int csidl);
static wchar_t *CreateLinkname(const wchar_t *shortcut, int csidl);
static void CreateOrBreakLink(IShellLink *psl, const wchar_t *shortcut, int csidl, BOOL aMakeShortcut);
static void CreateProgramShortcuts(const TCHAR *fname, const wchar_t *shortcut, BOOL aDesktopShortcut, BOOL aStartupShortcut,
    BOOL aDeskLinkExists, BOOL aStartlinkExists);
static BOOL CALLBACK InstallConfigDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
static ATOM RegisterMainWindow (HINSTANCE hInstance);
static void GetInitialControlPositions(HWND hWnd, AppWindowPos *wnd);
static void RecalcControlPositions(HWND hWnd, AppWindowPos *wnd);
static void MoveMainWindow(HWND hWnd, HINSTANCE hInst, DeviceTracker *DevTracker);
static void LVColumnClickAndSort(DeviceTracker *DevTracker, int newOrder, HWND hwndFrom);
static void LVInfoTip(LPNMLVGETINFOTIP pGetInfoTip);
static void LVRightClickContextMenu(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem, MonOptions *aOptions);
static void LVSelectedItemContextMenu(HINSTANCE hInst, HWND hWnd, HWND hWndLV, MonOptions *aOptions);
static void LVItemDoubleClick(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem, MonOptions *aOptions);
static void LVEmptyViewTest(NMLVEMPTYMARKUP *emptyMarkup);
static void ContextMenuClipboardSelect(HWND hWndLV, DeviceInfo *dev, int selection);
static void ContextMenuPopup(HINSTANCE hInst, HWND hWnd, HWND hWndLV, DeviceInfo *dev, POINT scrPt, MonOptions *aOptions);
static DeviceInfo *DevInfoFromListItem(HWND hWndLV, int iItem);
static DeviceInfo *DevInfoFromListPoint(HWND hWndLV, int iItem, POINT pt);


/* real code begins here ... */

int WINAPI WinMain (
    HINSTANCE hInstance,
    HINSTANCE /* hPrevInstance */,
    PSTR /* szCmdLine TODO: use to identify when launched from Startup Shortcut */,
    int /* iCmdShow TODO: review if useful to support this */
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
    ccInit.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
    InitCommonControlsEx(&ccInit);
    // need Microsoft COM setup for handling shortcuts
    CoInitialize(NULL);

    // simply use DialogBoxParam to show window
    // TODO: pass a parameter block, eg including launch from Startup flag
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
    // Visual Studio 2010 does not allow setting Class of Dialog template, so icon given here wont be used for our main window
    WndClass.hIcon         = NULL;
                            /* (HICON) LoadImage(hInstance, MAKEINTRESOURCE(IDI_RFIDLER),
                                    IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR); */
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
#define FLAG_TOP_NOMOVE             0x00000001
#define FLAG_HEIGHT_FIXED           0x00000002
#define FLAG_BOTTOM_TRACK           0x00000004

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


static void GetInitialControlPositions(HWND hWnd, AppWindowPos *wnd)
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
static void RecalcControlPositions(HWND hWnd, AppWindowPos *wnd)
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


/*
  If possible restore position of the window from last time it is was run.
  Otherwise hacky stuff to position main window because CW_USERDEFAULT positioning does not work for dialog based windows,
  as we don't want to be in top left corner of the screen.
  */
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
    static HINSTANCE        hInst = 0;
    static DeviceTracker    *DevTracker;
    static HWND             hWndLV = NULL;
    static HWND             hWndStatusBar = NULL;
    static UINT             TbCreatedNotification = 0;
    static ITaskbarList3*   pTbList = NULL; // Windows >= 7 Taskbar COM interface
    // data to support resizing of window
    static AppControlPos    MainControls[] =
    {
        { IDC_RFIDLERLIST, FLAG_TOP_NOMOVE | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
        { IDC_STATUSBAR,  FLAG_HEIGHT_FIXED | FLAG_BOTTOM_TRACK | FLAG_LEFT_NOMOVE | FLAG_RIGHT_TRACK },
    };

    static AppWindowPos MainWnd = {
        MainControls,
        sizeof(MainControls) / sizeof(AppControlPos),
    };


    /* locals */
    int  handled = 0;

    switch (iMsg) {
    case WM_INITDIALOG:	/* from CreateDialog() */
        hInst = (HINSTANCE) lParam;

        // set System Menu Icon for dialog
        SetClassLong(hWnd, GCL_HICON, (LONG) LoadIcon(hInst, MAKEINTRESOURCE(IDI_RFIDLER)));

        // create / remember key child windows
        hWndLV = GetDlgItem(hWnd, IDC_RFIDLERLIST);

        // Create Status Bar with sizing grip at bottom of window
        hWndStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP, _T(""), hWnd, IDC_STATUSBAR);

        // setup support for resizing / moving child controls when dialog is resized
        GetInitialControlPositions(hWnd, &MainWnd);

        // Check for Windows >= 7
        if (CheckWindowsVersion(WinAtLeast7)) {
            /* Request notification when our Taskbar button is created,
               can occur multiple times if Windows Shell restarts.
             */
            TbCreatedNotification = RegisterWindowMessage(TEXT("TaskbarButtonCreated"));
            if (TbCreatedNotification) {
                // obscurely documented secret sauce to actually get the notification
                ChangeWindowMessageFilterEx(hWnd, TbCreatedNotification, MSGFLT_ALLOW, NULL);
            }
        }

        // create Plug & Play device tracking stuff
        DevTracker = new DeviceTracker(hWnd, hWndLV, hWndStatusBar, hInst);
        if (DevTracker) {
            // Registry Settings etc are restored by DeviceTracker constructor, so we can use them now

            // should StatusBar have 2 or 3 partitions?
            if (hWndStatusBar) {
                if (DevTracker->GetOptions().ShowDevBoardsOrAnySerial()) {
                    SetStatusBarPartitions(hWndStatusBar, 3);
                } else {
                    SetStatusBarPartitions(hWndStatusBar, 2);
                }
            }
            DevTracker->Initialize();

            // restore old window position & size if any, or use CW_USEDEFAULT positioning
            MoveMainWindow(hWnd, hInst, DevTracker);
        } else {
            // Kaboom! major failure creating program resources
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
                    DevTracker->GetOptions().SaveWindowInfo(place.rcNormalPosition);
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
        handled++;
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

                // change type of view
            case ID_VIEW_LARGE_ICONS:
            case ID_VIEW_SMALL_ICONS:
            case ID_VIEW_DETAILS:
            case ID_VIEW_TILES: // Tile view must be supported, as we specify comctrl32 DLL v6.0 in manifest
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
            UINT notifycode = pNm->hdr.code;

            switch(notifycode) {
            case LVN_COLUMNCLICK:
                LVColumnClickAndSort(DevTracker, pNm->iSubItem, pNm->hdr.hwndFrom);
                handled++;
                break;

            case LVN_GETINFOTIP:
                // tooltip when mouse hovers over device in view
                LVInfoTip((LPNMLVGETINFOTIP)lParam);
                handled++;
                break;

            case NM_RCLICK: // right click: device menu
                LVRightClickContextMenu(hInst, hWnd, (LPNMITEMACTIVATE) lParam, &DevTracker->GetOptions());
                handled++;
                break;

            case LVN_ITEMACTIVATE:
                LVItemDoubleClick(hInst, hWnd, (LPNMITEMACTIVATE)lParam, &DevTracker->GetOptions());
                handled++;
                break;

            case LVN_GETEMPTYMARKUP:
                // bug: documented way of setting empty ListView text, not working for me (Windows 7)
                LVEmptyViewTest((NMLVEMPTYMARKUP *) lParam);
                handled++;
                break;

            case (LVN_FIRST-61):
                // LVN_GETEMPTYTEXTW undocumented way of setting empty ListView text, not working for me (Windows 7)
                {
                    NMLVDISPINFO *nm = (NMLVDISPINFO *)lParam;
                    if (nm->item.mask == LVIF_TEXT && nm->item.pszText) {
                        StringCchCopy(nm->item.pszText, nm->item.cchTextMax, _T("No RFIDlers connected."));
                    }
                }
                handled++;
                break;

#ifdef _DEBUG
            case LVN_GETDISPINFOW:
                {   // no action seems to be needed
                    NMLVDISPINFO* pdi = (NMLVDISPINFO*) lParam;

                    PrintDebugStatus(_T("WM_NOTIFY ListView hdr.code = LVN_GETDISPINFOW, iItem %u, mask = 0x%x\n"),
                        pdi->item.iItem, pdi->item.mask);
                }
                break;

            case LVN_ITEMCHANGING: // notifications we don't want Debug prints for
            case LVN_ITEMCHANGED:
            case LVN_INSERTITEM: 
            case LVN_DELETEITEM:
            case LVN_DELETEALLITEMS:
            case LVN_HOTTRACK:
            case LVN_BEGINSCROLL:
            case LVN_ENDSCROLL:
            case LVN_INCREMENTALSEARCHW:
                break;

            case LVN_KEYDOWN:
                { // maybe want to handle some keys?
                    NMLVKEYDOWN* pnkd = (NMLVKEYDOWN*) lParam;

                    PrintDebugStatus(_T("ListView LVN_KEYDOWN hwndFrom 0x%0x, wVKey %u 0x%0x, flags 0x%0x\n"),
                        pNm->hdr.hwndFrom, pnkd->wVKey, pnkd->flags);
                }
                break;

            default: // report unhandled notifications
                if (notifycode <= LVN_FIRST) {
                    PrintDebugStatus(_T("WM_NOTIFY ListView hdr.code = %u = (LVN_FIRST-%u)\n"),
                        notifycode, LVN_FIRST - notifycode);
                }
                break;
#else
            default:
                break;
#endif
            }
        }
        break;

    case WM_CONTEXTMENU: // Context Menu for ListView (should only be that VK_APPS or Shift+F10 come here)
        if (wParam == (WPARAM) hWndLV) {
            if ((lParam == 0xFFFFFFFF) && (ListView_GetSelectedCount(hWndLV) > 0)) {
                LVSelectedItemContextMenu(hInst, hWnd, hWndLV, &DevTracker->GetOptions());
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
        case REGISTRY_SAVE_MAGICNUMBER:
            if (DevTracker) {
                DevTracker->GetOptions().RegistrySaveChangedValues(FALSE);
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
            DevTracker->GetOptions().RegistrySaveChangedValues(TRUE);
            DevTracker->Cleanup();
            delete DevTracker;
            DevTracker = NULL;
        }
        // release Taskbar COM interface
        if (pTbList) {
            pTbList->Release();
            pTbList = NULL;
        }
        // close program
        PostQuitMessage (0);
        handled++;
        break;

    default:
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


void SetShowOptionsCheckBoxes(HWND hWnd, MonOptions *aOptions)
{
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_UNCONFIG), BM_SETCHECK, 
        aOptions->ShowNonConfig() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_ALL), BM_SETCHECK, 
        aOptions->ShowNotPresent() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_BITWHACKER), BM_SETCHECK, 
        aOptions->ShowDevBoards() ? BST_CHECKED : BST_UNCHECKED, 0);        
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_RECENTDISC), BM_SETCHECK, 
        aOptions->ShowRecentDisc() ? BST_CHECKED : BST_UNCHECKED, 0);        
    SendMessage(GetDlgItem(hWnd, IDC_OTHERSERIAL), BM_SETCHECK, 
        aOptions->ShowAnySerial() ? BST_CHECKED : BST_UNCHECKED, 0);        
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
        SetShowOptionsCheckBoxes(hWnd, newOptions);
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
                if (newOptions->SetShowFlagsToAll()) {
                    enableApply = TRUE;
                    SetShowOptionsCheckBoxes(hWnd, newOptions);
                }
                break;
            case IDC_CHECK_SHOW_NONE:
                if (newOptions->SetShowFlagsToNone()) {
                    enableApply = TRUE;
                    SetShowOptionsCheckBoxes(hWnd, newOptions);
                }
                break;
            case IDC_DEFAULT:
                if (newOptions->SetShowFlagsToDefault()) {
                    enableApply = TRUE;
                    SetShowOptionsCheckBoxes(hWnd, newOptions);
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


void SetNotifyOptionsCheckBoxes(HWND hWnd, MonOptions *aOptions)
{
    SendMessage(GetDlgItem(hWnd, IDC_RFID_ARR_FLASH), BM_SETCHECK, 
        aOptions->NotifyRfidlerArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_BOOT_ARR_FLASH), BM_SETCHECK, 
        aOptions->NotifyBootArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_MICROCHIP_ARR_FLASH), BM_SETCHECK, 
        aOptions->NotifyMicrochipArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
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
        SetNotifyOptionsCheckBoxes(hWnd, newOptions);
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
                if (newOptions->SetNotifyFlagsToAll()) {
                    enableApply = TRUE;
                    SetNotifyOptionsCheckBoxes(hWnd, newOptions);
                }
                break;
            case IDC_CHECK_SHOW_NONE:
                if (newOptions->SetNotifyFlagsToNone()) {
                    enableApply = TRUE;
                    SetNotifyOptionsCheckBoxes(hWnd, newOptions);
                }
                break;
            case IDC_DEFAULT:
                if (newOptions->SetNotifyFlagsToDefault()) {
                    enableApply = TRUE;
                    SetNotifyOptionsCheckBoxes(hWnd, newOptions);
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
                // some selection changed, tell parent dialog to enable Apply button
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
        { 
            /* mark Tab control as parent, dialog pages should already have this via DS_CONTROL
               This should ensure tab key moves through all the controls correctly.
               Minor Windows bug: tab key does select the the tab control, so it is hard
               (impossible?) to change pages with keyboard.
               */
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
                // fall through
            case IDCANCEL:
                EndDialog(hWnd, wID);
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
            case IDC_DEFAULT:
                // send to the current options page
                PostMessage(hWndOptionsPage[currPage], iMsg, wParam, lParam);
                handled++;
                break;
            }
        }
        break;

    case WM_APP: // enable apply button (request from current options page)
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
                    // flip tabs, update Apply button state
                    ShowWindow(hWndOptionsPage[0], index == 0 ? SW_SHOWNA :SW_HIDE);
                    ShowWindow(hWndOptionsPage[1], index == 1 ? SW_SHOWNA :SW_HIDE);
                    if (ApplyEnabled[currPage] != ApplyEnabled[index]) {
                        EnableWindow(GetDlgItem(hWnd, IDC_APPLY), ApplyEnabled[index]);
                    }
                    currPage = index;
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
        // destroy windows & release memory for option pages
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
    unsigned sz = 64;
    DWORD    res;
    TCHAR    *f;

    do {
        f = (TCHAR *) calloc(sz, sizeof(TCHAR));
        if (f == NULL) {
            /* OOM */
            return FALSE;
        }

        res = GetModuleFileName(NULL, f, sz);
        if ((res > 0) && (res < sz)) {
            res += 1; // account for null terminator

            // try to shrink allocation 
            if ( (sz - res) >= 16) {
                TCHAR *f2 = (TCHAR *) realloc(f, res * sizeof(TCHAR));
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

    // something has changed from old settings?
    if (fname && ((aDesktopShortcut != aDeskLinkExists) || (aStartupShortcut != aStartlinkExists))) {
        IShellLink *psl;

        // connect to Windows Shell
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
                // TODO: add Argument(s) to indicate launch from Startup Shortcut
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
static const TCHAR *helpTitle = _T("Help About RFIDLer Monitor %u.%u.%u");
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
    _T("Copyright (c) 2014 - 2015 Anthony Naggs. All rights reserved.\r\n")
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



/* IDD_HELP_ABOUT */
INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM /* lParam */)
{
#define KTitleSize 100
    static TCHAR dialogTitle[KTitleSize];

    switch (iMsg) {
    case WM_INITDIALOG:
        {
            TCHAR *fname = NULL;
            BOOL gotfileversion = FALSE;

            // get version number from exe
            if (GetProgramFilename(&fname)) {
                DWORD verSize = GetFileVersionInfoSize(fname, NULL);
                if (verSize > 0) {
                    void *buffer = calloc(1, verSize);

                    if (buffer) {
                        void *fInfo = NULL;
                        UINT rxInfoSize = 0;

                        if (GetFileVersionInfo(fname, 0, verSize, buffer) && 
                                VerQueryValue(buffer, _T("\\"), &fInfo, &rxInfoSize) && fInfo && rxInfoSize) {
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
                // at least at 1.0.3
                StringCchPrintf(dialogTitle, KTitleSize, helpTitle, 1, 0, 3);
            }
            SetWindowText(hDlg, dialogTitle);

            SetWindowText(GetDlgItem(hDlg, IDC_HELP_TEXT), helpText);
            SetFocus( GetDlgItem (hDlg, IDOK));
        }
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


void LVColumnClickAndSort(DeviceTracker *DevTracker, int sortColumn, HWND hwndFrom)
{
    int oldOrder = DevTracker->GetViewSortOrder();
    int sortOrder = sortColumn;
    BOOL reverse = false;

    // user clicked on column header, so sort by chosen criterion
    if (oldOrder == sortColumn) {
        sortOrder = sortColumn + lvRevDispName;
        reverse = true;
    }

    // remember sort order, trigger timed state save
    DevTracker->SetViewSortOrder(sortOrder);
    // actually ysort items
    ListView_SortItems(hwndFrom, DeviceInfo::CompareProc, (LPARAM)(sortOrder));

    // move sort order mark between columns
    HWND hWndHdr = ListView_GetHeader(hwndFrom);
    if (hWndHdr) {
        HDITEM hdrItem;
        hdrItem.mask = HDI_FORMAT;
        int oldColumn = (oldOrder < lvRevDispName) ? oldOrder : (oldOrder - lvRevDispName);

        if ((oldColumn != sortColumn) && Header_GetItem(hWndHdr, oldColumn, &hdrItem) && (hdrItem.fmt & (HDF_SORTUP | HDF_SORTDOWN))) {
            hdrItem.fmt &= ~(HDF_SORTUP | HDF_SORTDOWN);
            Header_SetItem(hWndHdr, oldColumn, &hdrItem);
        }

        if (Header_GetItem(hWndHdr, sortColumn, &hdrItem)) {
            if (reverse) {
                hdrItem.fmt &= ~HDF_SORTUP;
                hdrItem.fmt |= HDF_SORTDOWN;
            } else {
                hdrItem.fmt &= ~HDF_SORTDOWN;
                hdrItem.fmt |= HDF_SORTUP;
            }
            Header_SetItem(hWndHdr, sortColumn, &hdrItem);
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


void LVRightClickContextMenu(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem, MonOptions *aOptions)
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
        ContextMenuPopup(hInst, hWnd, lpnmitem->hdr.hwndFrom, dev, lpnmitem->ptAction, aOptions);
    }
}


void LVSelectedItemContextMenu(HINSTANCE hInst, HWND hWnd, HWND hWndLV, MonOptions *aOptions)
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
                ContextMenuPopup(hInst, hWnd, hWndLV, dev, cliPt, aOptions);
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


void ContextMenuClipboardSelect(HWND hWndLV, DeviceInfo *dev, int selection)
{
    const TCHAR *strings[5] = { NULL, NULL, NULL, NULL, NULL };
    const TCHAR *string;
    int i = 0;

    switch(selection) {
    case ID_CONTEXT_COPYDEV_DETAILS: // skip Bootloader typename, as it just repeats DisplayName info
    case ID_CONTEXT_COPYPORT_DETAILS:
        strings[i++] = dev->DisplayName();
        if (selection == ID_CONTEXT_COPYPORT_DETAILS) {
            strings[i++] = dev->DevTypeName();
        }
        strings[i++] = dev->StateName();
        string = dev->LocationString();
        if (string) {
            strings[i++] = string;
        }
        strings[i++] = dev->SerialNumber();
        break;
    case ID_CONTEXT_COPYPORT_NAME:
        string = dev->PortName();
        if (string) {
            strings[i++] = string;
        }
        break;
    //case ID_CONTEXT_COPYALL_DETAILS: // possible future fn, needs ListView iterator & string info buffers
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


void ContextMenuPopup(HINSTANCE hInst, HWND hWnd, HWND hWndLV, DeviceInfo *dev, POINT scrPt, MonOptions *aOptions)
{
    assert(dev);
    int defaultitem = 0;

    // context menu
    LPCWSTR lpMenuName = NULL;

    ClientToScreen(hWndLV, &scrPt);

    switch (dev->DeviceType()) {
    case DevRfidlerCom:
    case DevMicroDevBoard:
    case DevOtherSerial:
        lpMenuName = MAKEINTRESOURCE(IDR_PORT_CONTEXT);
        break;
    case DevMicroBootloader:
        lpMenuName = MAKEINTRESOURCE(IDR_DEV_CONTEXT);
#if defined(ENABLE_BOOTLOADER_FLASH) || defined(_DEBUG)
        defaultitem = ID_CONTEXT_OPEN_FOR_REFLASH;
#endif
        break;
    case DevUnconfigRfidlerCom:
    case DevUnconfigMicroDevBoard:
    default:
        // TODO Context Menu for Unconfigured device? Maybe help text?
        break;
    }

    HMENU hMenu = LoadMenu(hInst, lpMenuName);
    if (hMenu) {
        HMENU hMenuTrackPopup  = GetSubMenu(hMenu, 0);

        if (defaultitem) {
            // highlight default menu action in bold
            SetMenuDefaultItem(hMenuTrackPopup, defaultitem, FALSE);
        }

#if !defined(ENABLE_BOOTLOADER_FLASH) && !defined(_DEBUG)
        switch (dev->DeviceType()) {
        case DevRfidlerCom:
        case DevMicroDevBoard:
        case DevOtherSerial:
            break;
        case DevMicroBootloader:
            // disable BOOTLOADER FLASH menu item
            RemoveMenu(hMenuTrackPopup, ID_CONTEXT_OPEN_FOR_REFLASH, MF_BYCOMMAND); 
            break;
        case DevUnconfigRfidlerCom:
        case DevUnconfigMicroDevBoard:
        default:
            break;
        }
#endif

        // ensure device is not freed whilst we are using it
        dev->LockForContextMenu();

        int selection = TrackPopupMenu(hMenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD,
            scrPt.x, scrPt.y, 0, hWnd, NULL);
#ifdef _DEBUG
        PrintDebugStatus(_T("Popup selection = %i\n"), selection);
#endif
        if (selection > 0) {
            switch(selection) {
            case ID_CONTEXT_COPYDEV_DETAILS:
            case ID_CONTEXT_COPYPORT_DETAILS:
            case ID_CONTEXT_COPYPORT_NAME:
            //case ID_CONTEXT_COPYALL_DETAILS: // possible future fn, needs ListView iterator & string info buffers
                ContextMenuClipboardSelect(hWnd, dev, selection);
                break;
#if defined(ENABLE_BOOTLOADER_FLASH) || defined(_DEBUG)
            case ID_CONTEXT_OPEN_FOR_REFLASH:
                if (!dev->DeleteOnUnlock()) {
                    // launch Bootloader Flash dialog
                    BootloaderParams bl;
                    bl.blDev = dev;
                    bl.blOptions = aOptions;
                    DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_BOOTLOADERFLASH), hWnd, BootloaderDlgProc,
                        (LPARAM) &bl);
                }
                break;
#else
            // suppress unreferenced variable warnings
            aOptions;
#endif
            }
        }

        dev->UnlockForContextMenu();
    }
}


void LVItemDoubleClick(HINSTANCE hInst, HWND hWnd, LPNMITEMACTIVATE lpnmitem, MonOptions *aOptions)
{
     // launch default menu action, if any
#ifdef _DEBUG
    PrintDebugStatus(_T("LVN_ACTIVATE iItem = %i, iSubItem = %i, lParam = %p, point = %i,%i\n"),
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
        case DevOtherSerial:
            // todo future enhancement, have a default menu item
            break;
        case DevMicroBootloader:
#if defined(ENABLE_BOOTLOADER_FLASH) || defined(_DEBUG)
            {
                // launch Bootloader Flash dialog
                BootloaderParams bl;
                bl.blDev = dev;
                bl.blOptions = aOptions;
                DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_BOOTLOADERFLASH), hWnd, BootloaderDlgProc,
                    (LPARAM) &bl);
            }
#else
            // suppress unreferenced variable warnings
            hInst;
            hWnd;
            aOptions;
#endif
            break;
        case DevUnconfigRfidlerCom:
        case DevUnconfigMicroDevBoard:
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

#ifdef _DEBUG
    PrintDebugStatus(_T("LVHITTESTINFO iItem = %i, iSubItem = %i, flags = %x\n"),
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


BOOL InitHexFileList(HWND hDlg, MonOptions *aOptions)
{
    int historyCount = aOptions->HexFileHistoryCount();
    BOOL result = FALSE;

    if (historyCount) {
        HWND hWndFileList = GetDlgItem(hDlg, IDC_HEX_READFILE);

        // populate file history
        for (int i = 0; i < historyCount; i++) {
            TCHAR *filename = aOptions->HexFileHistory(i);
            if (-1 != SendMessage(hWndFileList, CB_ADDSTRING, 0, (LPARAM) filename)) {
                result = TRUE;
            }
        }
    }
    return result;
}


// printf formatted messages to report area of installer's window
void BootloaderStatus(HWND hWndStatus, const TCHAR *format, ...)
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
            const wchar_t *path = bl->blDev->DevicePath();

            if (path) {
                h = CreateFile(path, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL, OPEN_EXISTING, 0, NULL);
#ifdef _DEBUG
                PrintDebugStatus(_T("tried opening %s, %s\n"), path, (h == INVALID_HANDLE_VALUE) ? _T("fail") : _T("success"));
#endif

                if (h != INVALID_HANDLE_VALUE) {
                    BootloaderEnableBaseControls(hDlg, TRUE);
                    BootloaderStatus(hWndReport, _T("Bootloader device opened"));

                    if (InitHexFileList(hDlg, bl->blOptions)) {
                        BootloaderEnableProgramControls(hDlg, TRUE);
                    }
                } else {
                    // report error
                    BootloaderStatus(hWndReport, _T("Bootloader device open failed (%u)"), GetLastError());
                }
            } else {
                BootloaderStatus(hWndReport, _T("Bootloader device not found"));
            }
        }
        return TRUE; // unless you set the focus to a control

    case WM_COMMAND: 
        switch (LOWORD(wParam)) {
        case IDC_ERASE:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
            }
            break;
        case IDC_PROGRAM:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
            }
            break;
        // IDC_FLASHPROGRESS               
        case IDC_HEX_READFILE:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
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
                /* todo */
            }
            break;
        case IDC_ERASEPROGRAMVERIFY:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
            }
            break;
        case IDC_REBOOT:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
            }
            break;
        case IDC_SAVEHEX:
            if (h != INVALID_HANDLE_VALUE) {
                /* todo */
                // todo SaveHexFileToHistory(const wchar_t *filename)
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


/* end of file rfidmonitor.cpp */