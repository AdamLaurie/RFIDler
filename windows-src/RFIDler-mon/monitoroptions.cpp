/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: monitoroptions.cpp

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


// store / retrieve setting from registry in SOFTWARE\\TonyNaggs\\RfidlerMonitor
static const wchar_t *KRegistryBase = _T("SOFTWARE");
static const wchar_t *KRegVendor = _T("TonyNaggs");
static const wchar_t *KRegProgramName = _T("RfidlerMonitor");
static const wchar_t *KRegFullProgramName = _T("SOFTWARE\\TonyNaggs\\RfidlerMonitor");

static const wchar_t *KRegKeyShowFlags = _T("ShowFlags");
static const wchar_t *KRegKeyNotifyFlags = _T("Notifications");
static const wchar_t *KRegKeySortOrder = _T("SortOrder");
static const wchar_t *KRegKeyViewStyle = _T("ViewStyle");
static const wchar_t *KRegKeyWinPosX = _T("WinPosX");
static const wchar_t *KRegKeyWinPosY = _T("WinPosY");
static const wchar_t *KRegKeyWinLayoutVer = _T("WinLayout");
static const wchar_t *KRegKeyWinSizeCX = _T("WinSizeCX");
static const wchar_t *KRegKeyWinSizeCY = _T("WinSizeCY");
static const wchar_t *KRegKeyMRUHexFile = _T("MRU_HexFile");
static const wchar_t *KRegKeyArrivalTime = _T("ArrivalTime");



void MonOptions::ReadRegistryValues()
{
    // read registry values
    HKEY programKey;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, KRegFullProgramName, 0, KEY_READ, &programKey)) {
        // vendor and application keys exist
        DWORD temp;
        DWORD valtype;
        DWORD valsize = sizeof(temp);
        int tint; // temp converted to int
        HKEY hk;

        // what optional stuff to show
        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyShowFlags, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
            tint = (int) temp;
            if (0 == (tint & ~optKAllShowFlags)) {
                optShowFlags = temp;
                optNeedSaveShowFlags = FALSE;
            }
        }

        // when to flash window title for notifications
        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyNotifyFlags, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
            tint = (int) temp;
            if (0 == (tint & ~optKAllNotifyFlags)) {
                optNotifyFlags = temp;
                optNeedSaveNotifyFlags = FALSE;
            }
        }

        // previous window position, size, and layout
        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyWinPosX, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
            optWindowPlace.left = temp;
            if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyWinPosY, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
                optWindowPlace.top = temp;
                if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyWinSizeCX, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
                    optWindowPlace.right = temp;
                    if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyWinSizeCY, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
                        optWindowPlace.bottom = temp;
                        // check that saved window position / size from same window layout?
                        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyWinLayoutVer, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype) && (temp == optWindowLayoutVer)) {
                            optHaveWindowPlace = TRUE;
                            optNeedSaveWindowPlace = FALSE;
                        }
                    }
                }
            }
        }

        // device Arrival / removal time
        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyArrivalTime, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
            if (temp <= KArrivalOrRemovalTimeMaximum) {
                optArrivalOrRemovalTime = temp;
                optNeedSaveArrivalTime = FALSE;
            }
        }

        // device list sort order
        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeySortOrder, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype) && (temp <= lvDispMaxSort)) {
            optViewSortOrder = temp;
            optNeedSaveViewSortOrder = FALSE;
        }

        // device list style
        if ((ERROR_SUCCESS == RegQueryValueEx(programKey, KRegKeyViewStyle, 0, &valtype, (BYTE*)&temp, &valsize)) && (REG_DWORD == valtype)) {
            switch (temp) {
            case ID_VIEW_LARGE_ICONS:
            case ID_VIEW_SMALL_ICONS:
            case ID_VIEW_DETAILS:
            case ID_VIEW_TILES: // valid value
                optViewStyleButton = temp;
                optNeedSaveViewStyleButton = FALSE;
                break;
            }
        }

        if (ERROR_SUCCESS == RegOpenKeyEx(programKey, KRegKeyMRUHexFile, 0, KEY_READ, &hk)) {
            wchar_t fnamebuff[1024];
            wchar_t numbuff[4];

            for (int j = 0; j < optHexFileHistoryCount; j++) {
                DWORD strsize = sizeof(fnamebuff);

                StringCchPrintf(numbuff, ARRAYSIZE(numbuff), _T("%i"), j);
                if ((ERROR_SUCCESS == RegQueryValueEx(hk, numbuff, 0, &valtype, (BYTE*)&fnamebuff, &strsize)) && (REG_SZ == valtype)) {
                    optHexFileHistory[j] = wcs_dupsubstr(fnamebuff, strsize);
                    optHexFileHistoryCount = j;
                    continue;
                }
                break;
            }
            RegCloseKey(hk);
        }
        RegCloseKey(programKey);

        // plan save to registry any state that was missing or invalid on reading
        if (optNeedSaveFlags) {
            KickRegSaveTimer();
        }
    }
}


// aShowSettingsChanged - out parameter
void MonOptions::SetShowOptionsAndRegistrySave(const MonOptions &newValues, BOOL &aShowSettingsChanged)
{
    // check & copy new options, setup auto-save
    if (optShowFlags != newValues.optShowFlags) {
        optShowFlags = newValues.optShowFlags;
        optNeedSaveShowFlags = TRUE;
        aShowSettingsChanged = TRUE;
        KickRegSaveTimer();
    }
}


void MonOptions::SetNotifyOptionsAndRegistrySave(const MonOptions &newValues)
{
    // check & copy new options, setup auto-save

    // sound / window title flash notification settings
    if (optNotifyFlags != newValues.optNotifyFlags) {
        optNotifyFlags = newValues.optNotifyFlags;
        optNeedSaveNotifyFlags = TRUE;
        KickRegSaveTimer();
    }
}


void MonOptions::SetArrivalOrRemovalTime(unsigned arrivalOrRemovalTime, BOOL saveChange)
{
    if ((arrivalOrRemovalTime < KArrivalOrRemovalTimeMaximum) && (optArrivalOrRemovalTime != arrivalOrRemovalTime)) {
        optArrivalOrRemovalTime = arrivalOrRemovalTime;
        if (saveChange) {
            optNeedSaveArrivalTime = TRUE;
            KickRegSaveTimer();
        }
    }
}


void MonOptions::RegistrySaveChangedValues(BOOL destroyWindow)
{
    assert(optNeedSaveFlags || destroyWindow);

#ifndef _DEBUG
    destroyWindow; // unreferenced param warning on release build
#endif

    // use timer as a one-shot
    CancelRegSaveTimer();

    if (optNeedSaveFlags) {
        HKEY hk1, hk2, hk3;
        DWORD disp = 0;

        if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, KRegFullProgramName, 0, KEY_ALL_ACCESS, &hk1)) {
            // keys already exist
            DoSaveChangedValues(hk1);
            RegCloseKey(hk1);
        } else if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, KRegistryBase, 0, KEY_ALL_ACCESS, &hk1)) {
            // first save: need to create vendor and application keys
            if (ERROR_SUCCESS == RegCreateKeyEx(hk1, KRegVendor, 0, _T(""),
                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk2, &disp)) {
                if (ERROR_SUCCESS == RegCreateKeyEx(hk2, KRegProgramName, 0, _T(""), REG_OPTION_NON_VOLATILE,
                            KEY_ALL_ACCESS, NULL, &hk3, &disp)) {
                    DoSaveChangedValues(hk3);
                    RegCloseKey(hk3);
                }
                RegCloseKey(hk2);
            }
            RegCloseKey(hk1);
        }
    } // if optNeedSaveFlags
}


void MonOptions::DoSaveChangedValues(HKEY programKey)
{
    DWORD temp;
    DWORD disp = 0;

    if (optNeedSaveShowFlags) {
        temp = optShowFlags;
        RegSetValueEx(programKey, KRegKeyShowFlags, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveShowFlags = FALSE;
    }

    if (optNeedSaveNotifyFlags) {
        temp = optNotifyFlags;
        RegSetValueEx(programKey, KRegKeyNotifyFlags, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveNotifyFlags = FALSE;
    }

    if (optNeedSaveWindowPlace) {
        temp = optWindowPlace.left;
        RegSetValueEx(programKey, KRegKeyWinPosX, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optWindowPlace.top;
        RegSetValueEx(programKey, KRegKeyWinPosY, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optWindowPlace.right;
        RegSetValueEx(programKey, KRegKeyWinSizeCX, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optWindowPlace.bottom;
        RegSetValueEx(programKey, KRegKeyWinSizeCY, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optWindowLayoutVer;
        RegSetValueEx(programKey, KRegKeyWinLayoutVer, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveWindowPlace = FALSE;
    }

    // device Arrival / removal time
    if (optNeedSaveArrivalTime) {
        temp = optArrivalOrRemovalTime;
        RegSetValueEx(programKey, KRegKeyArrivalTime, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveArrivalTime = FALSE;
    }

    if (optNeedSaveViewSortOrder) {
        temp = optViewSortOrder;
        RegSetValueEx(programKey, KRegKeySortOrder, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveViewSortOrder = FALSE;
    }

    if (optNeedSaveViewStyleButton) {
        temp = optViewStyleButton;
        RegSetValueEx(programKey, KRegKeyViewStyle, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveViewStyleButton = FALSE;
    }

    if (optNeedSaveHexFileHistory && optHexFileHistoryCount) {
        HKEY hk;

        optNeedSaveHexFileHistory = FALSE;
        if (ERROR_SUCCESS == RegCreateKeyEx(programKey, KRegKeyMRUHexFile, 0, _T(""),
                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, &disp)) {
            wchar_t numbuff[4];

            for (int j = 0; j < optHexFileHistoryCount; j++) {
                StringCchPrintf(numbuff, ARRAYSIZE(numbuff), _T("%i"), j);
                RegSetValueEx(hk, numbuff, 0, REG_SZ, (BYTE*)&optHexFileHistory[j], 
                    (wcslen(optHexFileHistory[j]) + 1) * sizeof(wchar_t));
            }
            RegCloseKey(hk);
        }
    }
}


BOOL MonOptions::GetWindowInfo(RECT &rc) const
{
    if (optHaveWindowPlace) {
        rc = optWindowPlace;
        return TRUE;
    }
    return FALSE;
}


void MonOptions::SaveWindowInfo(const RECT &rc)
{
    if ((rc.left != optWindowPlace.left) || (rc.top != optWindowPlace.top) ||
            (rc.right != optWindowPlace.right) || (rc.bottom != optWindowPlace.bottom)) {
        optWindowPlace = rc;
        optNeedSaveWindowPlace = TRUE;
        KickRegSaveTimer();
    }
}


void MonOptions::SaveViewSortOrder(int order)
{
    if ((order != optViewSortOrder) && (order <= lvDispMaxSort)) {
        optViewSortOrder = order;
        optNeedSaveViewSortOrder = TRUE;
        KickRegSaveTimer();
    }
}


void MonOptions::SaveViewStyleButton(int newStyle)
{
    if (newStyle != optViewStyleButton) {
        optViewStyleButton = newStyle;
        optNeedSaveViewStyleButton = TRUE;
        KickRegSaveTimer();
    }
}


void MonOptions::KickRegSaveTimer()
{
    if (!optTimerRegistrySave) {
        // run timer after ~15s
        SetTimer (optHwndMain, optTimerRegistrySave = REGISTRY_SAVE_MAGICNUMBER, 15000, NULL);
    }
}


void MonOptions::CancelRegSaveTimer()
{
    if (optTimerRegistrySave) {
        KillTimer(optHwndMain, optTimerRegistrySave);
        optTimerRegistrySave = 0;
    }
}


// note these next 6 functions are only used on temporary copy of the options
BOOL MonOptions::SetShowFlagsToAll()
{
    if (optShowFlags != optKAllShowFlags) {
        optShowFlags = optKAllShowFlags;
        return TRUE;
    }
    return FALSE;
}


BOOL MonOptions::SetShowFlagsToNone()
{
    if (optShowFlags != 0) {
        optShowFlags = 0;
        return TRUE;
    }
    return FALSE;
}


BOOL MonOptions::SetShowFlagsToDefault()
{
    if ((optShowFlags != optDefaultShowFlags) || (optArrivalOrRemovalTime != KArrivalOrRemovalTimeDefault)) {
        optShowFlags = optDefaultShowFlags;
        optArrivalOrRemovalTime = KArrivalOrRemovalTimeDefault;
        return TRUE;
    }
    return FALSE;
}


BOOL MonOptions::SetNotifyFlagsToAll()
{
    if (optNotifyFlags != optKAllNotifyFlags) {
        optNotifyFlags = optKAllNotifyFlags;
        return TRUE;
    }
    return FALSE;
}


BOOL MonOptions::SetNotifyFlagsToNone()
{
    if (optNotifyFlags != 0) {
        optNotifyFlags = 0;
        return TRUE;
    }
    return FALSE;
}


BOOL MonOptions::SetNotifyFlagsToDefault()
{
    if (optNotifyFlags != optDefaultNotifyFlags) {
        optNotifyFlags = optDefaultNotifyFlags;
        return TRUE;
    }
    return FALSE;
}


void MonOptions::SaveHexFileToHistory(const wchar_t *filename)
{
    for (int i = 0; i < optHexFileHistoryCount; i++) {
        if (!wcscmp(optHexFileHistory[i], filename)) {
            return;
        }
    }

    wchar_t *fname = _wcsdup(filename);
    wchar_t *oldname;
    if (!fname) {
        return; // out of memory
    }
    for (int i = 0; i < optHexFileHistoryCount; i++) {

        oldname = optHexFileHistory[i];
        optHexFileHistory[i] = fname;
        fname = oldname;
        optNeedSaveHexFileHistory = TRUE;
    }
    if (optHexFileHistoryCount < optKMaxHexFileHistoryCount) {
        optHexFileHistory[optHexFileHistoryCount++] = fname;
        optNeedSaveHexFileHistory = TRUE;
    } else if (fname) {
        free(fname);
    }

    if (optNeedSaveHexFileHistory) {
        KickRegSaveTimer();
    }
}


/* end of file monitoroptions.cpp */