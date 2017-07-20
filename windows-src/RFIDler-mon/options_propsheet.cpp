/* 

    Project: RFIDler Monitor v0.2
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: options_propsheet.cpp

    Author: Anthony Naggs, 2014, 2015, 2016

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

#define DO_ENABLE_THEME 1

#if DO_ENABLE_THEME
#include <uxtheme.h>
#endif


// this file contains dialog code for Settings / Options property sheets

// local support functions
HWND InitShowControls(MonOptions *newOptions, HWND hWndTab, BOOL showDialog);
HWND InitNotificationControls(MonOptions *newOptions, HWND hWndTab, BOOL showDialog);
void SetShowOptionsArrivalTime(HWND hWnd, MonOptions *aOptions);
void SetShowOptionsCheckBoxes(HWND hWnd, MonOptions *aOptions, BOOL setEditControls);
void SetNotifyOptionsCheckBoxes(HWND hWnd, MonOptions *aOptions);


HWND InitShowControls(MonOptions *newOptions, HWND hWndTab, BOOL showDialog)
{
    return InitTabbedDialog(hWndTab, 0, L"Show Devices", MAKEINTRESOURCE( IDD_OPT_WHATTOWATCH ),
        ShowOptionsDlgProc, (LPARAM) newOptions, showDialog);
}


HWND InitNotificationControls(MonOptions *newOptions, HWND hWndTab, BOOL showDialog)
{
    return InitTabbedDialog(hWndTab, 1, L"Device Notifications", MAKEINTRESOURCE( IDD_OPT_NOTIFICATIONS ),
        NotificationsDlgProc, (LPARAM) newOptions, showDialog);
}


void SetShowOptionsArrivalTime(HWND hWnd, MonOptions *aOptions)
{
    wchar_t arrivalString[8];

    // setup arrival time edit control
    StringCbPrintf(arrivalString, sizeof(arrivalString), L"%u", aOptions->GetArrivalOrRemovalTime());
    SetDlgItemText(hWnd, IDC_ARRIVAL_REMOVAL_TIME, arrivalString);
}


void SetShowOptionsCheckBoxes(HWND hWnd, MonOptions *aOptions, BOOL setEditControls)
{
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_UNCONFIG), BM_SETCHECK, 
        aOptions->ShowNonConfig() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_ALL), BM_SETCHECK, 
        aOptions->ShowNotPresent() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_DEV_BOARDS), BM_SETCHECK, 
        aOptions->ShowDevBoards() ? BST_CHECKED : BST_UNCHECKED, 0);        
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_RECENTDISC), BM_SETCHECK, 
        aOptions->ShowRecentDisc() ? BST_CHECKED : BST_UNCHECKED, 0);        
    SendMessage(GetDlgItem(hWnd, IDC_SHOW_OTHERSERIAL), BM_SETCHECK, 
        aOptions->ShowAnyOtherSerial() ? BST_CHECKED : BST_UNCHECKED, 0);        

    if (setEditControls) {
        SetShowOptionsArrivalTime(hWnd, aOptions);
    }
}


BOOL CALLBACK ShowOptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static MonOptions   *newOptions;
    static HWND         hWndParentDlg = NULL;
    static BOOL         editChanged = FALSE;
    const int           MaxArrivalTimeChars = 6; // space to edit
    BOOL                handled = FALSE;

    switch(iMsg) {
    case WM_INITDIALOG:
        hWndParentDlg = GetParent(GetParent(hWnd));
        newOptions = (MonOptions *) lParam;
        SetShowOptionsCheckBoxes(hWnd, newOptions, TRUE);
        // setup buddy range
        SendDlgItemMessage(hWnd, IDC_ARRIVAL_BUDDY, UDM_SETRANGE, 0, MAKELPARAM(1, KArrivalOrRemovalTimeMaximum));
        SendDlgItemMessage(hWnd, IDC_ARRIVAL_REMOVAL_TIME, EM_LIMITTEXT, MaxArrivalTimeChars, 0);
#if DO_ENABLE_THEME
        EnableThemeDialogTexture(hWnd, ETDT_ENABLETAB);
#endif
        editChanged = FALSE;
        return TRUE;

    case WM_NOTIFYFORMAT:
        return NFR_UNICODE;

    case WM_COMMAND:
        {
            int wID = LOWORD (wParam);
            int notify = HIWORD(wParam);
            BOOL enableApply = FALSE; // whether change of options should enable Apply button

            switch (wID) 
            {
            case IDC_WATCH_ALL:
                if (newOptions->SetShowFlagsToAll()) {
                    enableApply = TRUE;
                    SetShowOptionsCheckBoxes(hWnd, newOptions, FALSE);
                }
                break;
            case IDC_WATCH_NONE:
                if (newOptions->SetShowFlagsToNone()) {
                    enableApply = TRUE;
                    SetShowOptionsCheckBoxes(hWnd, newOptions, FALSE);
                }
                break;
            case IDC_WATCH_DEFAULT:
                if (newOptions->SetShowFlagsToDefault()) {
                    enableApply = TRUE;
                    SetShowOptionsCheckBoxes(hWnd, newOptions, TRUE);
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
            case IDC_SHOW_DEV_BOARDS:
                newOptions->SetShowDevBoards((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_DEV_BOARDS));
                enableApply = TRUE;
                break;
            case IDC_SHOW_RECENTDISC:
                newOptions->SetShowRecentDisc((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_RECENTDISC));
                enableApply = TRUE;
                break;
            case IDC_SHOW_OTHERSERIAL:
                newOptions->SetShowAnyOtherSerial((BOOL) IsDlgButtonChecked(hWnd, IDC_SHOW_OTHERSERIAL));
                enableApply = TRUE;
                break;
            case IDC_ARRIVAL_REMOVAL_TIME:
                // edit control validate values
                if (EN_CHANGE == notify) {
                    editChanged = TRUE;
                } else if (EN_KILLFOCUS == notify) {
                    if (editChanged) {
                        BOOL goodValue = FALSE;
                        wchar_t textbuffer[8]; // longer than the text limit we have set

                        UINT res = GetDlgItemText(hWnd, IDC_ARRIVAL_REMOVAL_TIME, textbuffer, 7);

                        if ((res >= 1) && (res <= MaxArrivalTimeChars)) {
                            unsigned long val = wcstoul(textbuffer, NULL, 0);

                            if ((val >= 1) && (val <= KArrivalOrRemovalTimeMaximum)) {
                                goodValue = TRUE;

                                if (val != newOptions->GetArrivalOrRemovalTime()) {
                                    // arrival time value changed
                                    newOptions->SetArrivalOrRemovalTime(val, FALSE);
                                    enableApply = TRUE;
                                }
                            }
                        }
                        SetShowOptionsArrivalTime(hWnd, newOptions);
                        editChanged = FALSE;
                        if (!goodValue) {
                            MessageBeep(MB_ICONWARNING);
                        }
                    }
                }
                break;
            }

            if (enableApply && hWndParentDlg) {
                // tell parent window to enable Apply button
                SendMessage(hWndParentDlg, WM_APP, 0, 0);
                handled = TRUE;
            }
        }
        break;

    case WM_NOTIFY:
        {
            int wID = LOWORD (wParam);
            int wNotification = ((NMHDR*)lParam)->code;
            //HWND hChild = ((NMHDR*)lParam)->hwndFrom;
            BOOL enableApply = FALSE; // whether change of options should enable Apply button

            if ((wID == IDC_ARRIVAL_BUDDY) && (wNotification == UDN_DELTAPOS)) {
                NMUPDOWN *updown = (NMUPDOWN*) lParam;
                newOptions->SetArrivalOrRemovalTime(updown->iPos + updown->iDelta, FALSE);
                enableApply = TRUE;
                editChanged = FALSE;
            }

            if (enableApply && hWndParentDlg) {
                SendMessage(hWndParentDlg, WM_APP, 0, 0);
                handled = TRUE;
            }
        }
#if defined(_DEBUG)
        if (!handled) {
            DlgProcDebugReport(L"ShowOptionsDlgProc", iMsg, wParam, lParam);
        }
#endif
        break;

#if defined(_DEBUG)
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        DlgProcDebugReport(L"ShowOptionsDlgProc", iMsg, wParam, lParam);
        break;
#endif
    }

    return handled;
}


void SetNotifyOptionsCheckBoxes(HWND hWnd, MonOptions *aOptions)
{
    SendMessage(GetDlgItem(hWnd, IDC_RFIDLER_ARR_FLASH), BM_SETCHECK, 
        aOptions->NotifyRfidlerArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_BOOT_ARR_FLASH), BM_SETCHECK, 
        aOptions->NotifyMicrochipBootloaderArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_MICROCHIP_ARR_FLASH), BM_SETCHECK, 
        aOptions->NotifyMicrochipSerialArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_ARDUINO_ARR_FLASH), BM_SETCHECK,
        aOptions->NotifyArduinoSerialArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
    SendMessage(GetDlgItem(hWnd, IDC_OTHER_SERIAL_ARR_FLASH), BM_SETCHECK,
        aOptions->NotifyAnyOtherSerialArrFlash() ? BST_CHECKED : BST_UNCHECKED, 0);
}


BOOL CALLBACK NotificationsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    static MonOptions *newOptions;
    static HWND       hWndParentDlg = NULL;

    BOOL handled = FALSE;

    switch(iMsg) {
    case WM_INITDIALOG:
        hWndParentDlg = GetParent(GetParent(hWnd));
        newOptions = (MonOptions *) lParam;
        SetNotifyOptionsCheckBoxes(hWnd, newOptions);
#if DO_ENABLE_THEME
        EnableThemeDialogTexture(hWnd, ETDT_ENABLETAB);
#endif
        return TRUE;

    case WM_NOTIFYFORMAT:
        return NFR_UNICODE;

    case WM_COMMAND:
        {
            int wID = LOWORD (wParam);
            BOOL enableApply = FALSE; // whether change of options should enable Apply button

            switch (wID) 
            {
            case IDC_NOTIFY_ALL:
                if (newOptions->SetNotifyFlagsToAll()) {
                    enableApply = TRUE;
                    SetNotifyOptionsCheckBoxes(hWnd, newOptions);
                }
                break;

            case IDC_NOTIFY_NONE:
                if (newOptions->SetNotifyFlagsToNone()) {
                    enableApply = TRUE;
                    SetNotifyOptionsCheckBoxes(hWnd, newOptions);
                }
                break;

            case IDC_NOTIFY_DEFAULT:
                if (newOptions->SetNotifyFlagsToDefault()) {
                    enableApply = TRUE;
                    SetNotifyOptionsCheckBoxes(hWnd, newOptions);
                }
                break;

            case IDC_RFIDLER_ARR_FLASH:
                newOptions->SetNotifyRfidlerArrFlash((BOOL) IsDlgButtonChecked(hWnd, wID));
                enableApply = TRUE;
                break;

            case IDC_BOOT_ARR_FLASH:
                newOptions->SetNotifyMicrochipBootloaderArrFlash((BOOL) IsDlgButtonChecked(hWnd, wID));
                enableApply = TRUE;
                break;

            case IDC_MICROCHIP_ARR_FLASH:
                newOptions->SetNotifyMicrochipSerialArrFlash((BOOL) IsDlgButtonChecked(hWnd, wID));
                enableApply = TRUE;
                break;

            case IDC_ARDUINO_ARR_FLASH:
                newOptions->SetNotifyArduinoSerialArrFlash((BOOL) IsDlgButtonChecked(hWnd, wID));
                enableApply = TRUE;
                break;

            case IDC_OTHER_SERIAL_ARR_FLASH:
                newOptions->SetNotifyAnyOtherSerialArrFlash((BOOL) IsDlgButtonChecked(hWnd, wID));
                enableApply = TRUE;
                break;
            }

            if (enableApply && hWndParentDlg) {
                // some selection changed, tell parent dialog to enable Apply button
                SendMessage(hWndParentDlg, WM_APP, 0, 0);
                handled = TRUE;
            }
        }
        break;

#if defined(_DEBUG)
    case WM_NOTIFY:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        DlgProcDebugReport(L"NotificationsDlgProc", iMsg, wParam, lParam);
        break;
#endif
    }

    return handled;
}


// Tabbed Options dialog
BOOL CALLBACK OptionsDlgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    const int KNumPropPages = 2;
    static HWND hWndOptionsPage[KNumPropPages] = { NULL, NULL };
    static MonOptions   *newOptions;
    static BOOL         ApplyEnabled[KNumPropPages] = { FALSE, FALSE };
    static int          currPage = 0;
    static HWND         hWndTab;

    BOOL handled = FALSE;

    // Option DlgProc works with tab control
    switch (iMsg) {
    case WM_INITDIALOG:
        for (int i = 0; i < KNumPropPages; i++) {
            ApplyEnabled[i] = FALSE;
        }

#if DO_ENABLE_THEME
        EnableThemeDialogTexture(hWnd, ETDT_ENABLETAB);
#endif
        // new copy of current options
        newOptions = new MonOptions(DevTracker.GetOptions());
        hWndTab = GetDlgItem(hWnd, IDC_TABOPTIONS);

        // select initial dialog page
        switch (lParam)
        {
        default:
        case ID_SETTINGS_DEVTYPES:         currPage = 0; break;
        case ID_SETTINGS_DEVNOTIFICATIONS: currPage = 1; break;
        }

        hWndOptionsPage[0] = InitShowControls(newOptions, hWndTab, 0 == currPage);
        hWndOptionsPage[1] = InitNotificationControls(newOptions, hWndTab, 1 == currPage);
        { 
            /* mark Tab control as parent, dialog pages should already have this via DS_CONTROL
               This should ensure tab key moves through all the controls correctly.
               Minor Windows bug: tab key does not select the the tab control, so it is hard
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
                DevTracker.SetOptions(*newOptions, DeviceTracker::SetAll);
                // fall through
            case IDCANCEL:
                EndDialog(hWnd, wID);
                handled = TRUE;
                break;
            case IDC_APPLY:
                EnableWindow(GetDlgItem(hWnd, IDC_APPLY), FALSE);
                ApplyEnabled[currPage] = FALSE;
                // only apply changes to currently visible options page
                {
                    DeviceTracker::SetMode setmode = DeviceTracker::SetNone;

                    switch (currPage)
                    {
                    case 0: setmode = DeviceTracker::SetShowOptions; break;
                    case 1: setmode = DeviceTracker::SetNotifyOptions; break;
                    }

                    DevTracker.SetOptions(*newOptions, setmode);
                }
                handled = TRUE;
                break;
            }
        }
        break;

    case WM_APP: // enable apply button (request from current options page)
        if (!ApplyEnabled[currPage]) {
            EnableWindow(GetDlgItem(hWnd, IDC_APPLY), TRUE);
            ApplyEnabled[currPage] = TRUE;
        }
        handled = TRUE;
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
                handled = TRUE;
                break;
            }
#if defined(_DEBUG)
            if (!handled) {
                DlgProcDebugReport(L"OptionDlgProc", iMsg, wParam, lParam);
            }
#endif
        }
        break;

#if defined(_DEBUG)
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        DlgProcDebugReport(L"OptionsDlgProc", iMsg, wParam, lParam);
        break;
#endif

    case WM_CLOSE:
        EndDialog(hWnd, 0);
        handled = TRUE;
        break;

    case WM_DESTROY:
        // destroy windows & release memory for option pages
        for (int i = 0; i < KNumPropPages; i++) {
            if (hWndOptionsPage[i]) {
                DestroyWindow(hWndOptionsPage[i]);
                hWndOptionsPage[i] = NULL;
            }
        }
        handled = TRUE;
        break;
    }

    // TRUE = handled here, FALSE = pass to default handling
    return handled;
}   /* OptionsDlgProc() */


/* end of file options_propsheet.cpp */