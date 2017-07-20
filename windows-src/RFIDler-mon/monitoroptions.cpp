/* 

    Project: RFIDler Monitor v0.2
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: monitoroptions.cpp

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
// for PathCanonicalize(), PathIsUrl() ..
#include <Shlwapi.h>


// need to link with this library - TODO is this pragma needed #pragma comment(lib, "Shlwapi.lib")


// store / retrieve setting from registry in SOFTWARE\\TonyNaggs\\RfidlerMonitor
static const wchar_t *KRegistryBase = L"SOFTWARE";
static const wchar_t *KRegVendor = L"TonyNaggs";
static const wchar_t *KRegProgramName = L"RfidlerMonitor";
static const wchar_t *KRegFullProgramName = L"SOFTWARE\\TonyNaggs\\RfidlerMonitor";

static const wchar_t *KRegKeyShowFlags = L"ShowFlags";
static const wchar_t *KRegKeyNotifyFlags = L"Notifications";
static const wchar_t *KRegKeySortOrder = L"SortOrder";
static const wchar_t *KRegKeySortReverse = L"SortReverse";
static const wchar_t *KRegKeySortVersion = L"SortVersion";
static const wchar_t *KRegKeyViewStyle = L"ViewStyle";
static const wchar_t *KRegKeyViewColumnName = L"ViewColName";
static const wchar_t *KRegKeyViewColumnDevice = L"ViewColDevice";
static const wchar_t *KRegKeyViewColumnState = L"ViewColState";
static const wchar_t *KRegKeyViewColumnLocus = L"ViewColLocus";
static const wchar_t *KRegKeyViewColumnSerNum = L"ViewColSerNum";
static const wchar_t *KRegKeyViewColumnArrival = L"ViewColDevArrival";
static const wchar_t *KRegKeyWinPosX = L"WinPosX";
static const wchar_t *KRegKeyWinPosY = L"WinPosY";
static const wchar_t *KRegKeyWinLayoutVer = L"WinLayout";
static const wchar_t *KRegKeyWinSizeCX = L"WinSizeCX";
static const wchar_t *KRegKeyWinSizeCY = L"WinSizeCY";
static const wchar_t *KRegKeyWinShow = L"WinShow"; // persist whether window is Normal, Minimized or Maximized
static const wchar_t *KRegKeyMRUHexFile = L"MRU_HexFile";
static const wchar_t *KRegKeyArrivalTime = L"ArrivalTime";


BOOL MonOptions::ReadRegDword(HKEY hKey, LPCWSTR lpValueName, LPBYTE lpData)
{
    DWORD valtype;
    DWORD valsize = sizeof(DWORD);

    return (ERROR_SUCCESS == RegQueryValueEx(hKey, lpValueName, 0, &valtype, lpData, &valsize)) && (REG_DWORD == valtype);
}


wchar_t *MonOptions::NumToString(unsigned value)
{
    static wchar_t numbuff[8];

    StringCchPrintf(numbuff, ARRAYSIZE(numbuff), L"%u", value);
    return numbuff;
}

void MonOptions::ReadRegistryValues(BOOL autorunStart)
{
    // read registry values
    HKEY programKey;

    if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_CURRENT_USER, KRegFullProgramName, 0, KEY_READ, &programKey)) {
        // vendor and application keys exist
        DWORD temp;
        int tint; // temp converted to int
        HKEY hk;

        // what optional stuff to show
        if (ReadRegDword(programKey, KRegKeyShowFlags, (BYTE*)&temp)) {
            tint = (int) temp;
            if (0 == (tint & ~optKAllShowFlags)) {
                optShowFlags = temp;
                optNeedSaveShowFlags = FALSE;
            }
        }

        // when to flash window title for notifications
        if (ReadRegDword(programKey, KRegKeyNotifyFlags, (BYTE*)&temp)) {
            tint = (int) temp;
            if (0 == (tint & ~optKAllNotifyFlags)) {
                optNotifyFlags = temp;
                optNeedSaveNotifyFlags = FALSE;
            }
        }

        // previous window position, size, and layout
        if (ReadRegDword(programKey, KRegKeyWinPosX, (BYTE*)&temp)) {
            optWindowPlace.left = temp;
            if (ReadRegDword(programKey, KRegKeyWinPosY, (BYTE*)&temp)) {
                optWindowPlace.top = temp;
                if (ReadRegDword(programKey, KRegKeyWinSizeCX, (BYTE*)&temp)) {
                    optWindowPlace.right = temp;
                    if (ReadRegDword(programKey, KRegKeyWinSizeCY, (BYTE*)&temp)) {
                        optWindowPlace.bottom = temp;
                        // check that saved window position / size from same window layout?
                        if (ReadRegDword(programKey, KRegKeyWinLayoutVer, (BYTE*)&temp) && (temp == optWindowLayoutVer)) {
                            optHaveWindowPlace = TRUE;
                            optNeedSaveWindowPlace = FALSE;
                        }
                    }
                }
            }
        }

        // device Arrival / removal time
        if (ReadRegDword(programKey, KRegKeyArrivalTime, (BYTE*)&temp)) {
            if ((temp >= 1) && (temp <= KArrivalOrRemovalTimeMaximum)) {
                optArrivalOrRemovalTime = temp;
                optNeedSaveArrivalTime = FALSE;
            }
        }

        // running from Autorun at startup, restore window state: Normal, Max, Min
        if (autorunStart && ReadRegDword(programKey, KRegKeyWinShow, (BYTE*)&temp)) {
            if ((SW_NORMAL == temp ) | (SW_MAXIMIZE == temp) || (SW_SHOWMINIMIZED == temp)) {
                optWindowState = temp;
                optNeedSaveWindowState = FALSE;
                if (SW_SHOWMINIMIZED == optWindowState) {
                    ShowWindowAsync(optHwndMain, SW_MINIMIZE);
                } else if (SW_SHOWMAXIMIZED == optWindowState) {
                    ShowWindowAsync(optHwndMain, SW_MAXIMIZE);
                }
            }
        }

        // device list sort order
        if (ReadRegDword(programKey, KRegKeySortVersion, (BYTE*)&temp)) {
            // check settings version
            if (temp == optViewSortVersion) {
                DWORD reverse = 0;

                if (ReadRegDword(programKey, KRegKeySortReverse, (BYTE*)&reverse) && (reverse <= 1) &&
                        ReadRegDword(programKey, KRegKeySortOrder, (BYTE*)&temp) && (temp <= lvDispArrivalTime)) {
                    optViewSortOrder.mSortType = (lvColumn) temp;
                    optViewSortOrder.mSortReverse = reverse;
                    optNeedSaveViewSortOrder = FALSE;
                }
            }
        } else {
            // original data version included direction in main enum, just range limit enum read in
            if (ReadRegDword(programKey, KRegKeySortOrder, (BYTE*)&temp) && (temp <= lvDispSernum)) {
                optViewSortOrder.mSortType = (lvColumn) temp;
                optViewSortOrder.mSortReverse = 0;
                optNeedSaveViewSortOrder = FALSE;
            }
        }

        // device list style
        if (ReadRegDword(programKey, KRegKeyViewStyle, (BYTE*)&temp)) {
            switch (temp) {
            case ID_VIEW_LARGE_ICONS:
            case ID_VIEW_SMALL_ICONS:
            case ID_VIEW_DETAILS:
            case ID_VIEW_TILES: // valid value
                DevTracker.SetViewStyle(temp, TRUE);
                optNeedSaveViewStyleButton = FALSE;
                break;
            }
        }

        // restore Device View Column widths, working right to ,left
        DWORD KMaxColumnWidth = 1000; // sanity limit on valid column width when we restore REVIEW?

        if (ReadRegDword(programKey, KRegKeyViewColumnSerNum, (BYTE*)&temp)) {
            if ((temp > 0) && (temp <= KMaxColumnWidth)) {
                optDetailsColumnWidths[lvDispSernum] = temp;
            }
        }
        if (ReadRegDword(programKey, KRegKeyViewColumnLocus, (BYTE*)&temp)) {
            if ((temp > 0) && (temp <= KMaxColumnWidth)) {
                optDetailsColumnWidths[lvDispLocus] = temp;
            }
        }
        if (ReadRegDword(programKey, KRegKeyViewColumnState, (BYTE*)&temp)) {
            if ((temp > 0) && (temp <= KMaxColumnWidth)) {
                optDetailsColumnWidths[lvDispState] = temp;
            }
        }
        if (ReadRegDword(programKey, KRegKeyViewColumnDevice, (BYTE*)&temp)) {
            if ((temp > 0) && (temp <= KMaxColumnWidth)) {
                optDetailsColumnWidths[lvDispType] = temp;
            }
        }
        if (ReadRegDword(programKey, KRegKeyViewColumnName, (BYTE*)&temp)) {
            if ((temp > 0) && (temp <= KMaxColumnWidth)) {
                optDetailsColumnWidths[lvDispName] = temp;
            }
        }
        if (ReadRegDword(programKey, KRegKeyViewColumnArrival, (BYTE*)&temp)) {
            if ((temp > 0) && (temp <= KMaxColumnWidth)) {
                optDetailsColumnWidths[lvDispArrivalTime] = temp;
            }
        }

        if (ERROR_SUCCESS == RegOpenKeyEx(programKey, KRegKeyMRUHexFile, 0, KEY_READ, &hk)) {
            wchar_t fnamebuff[1024];
            DWORD valtype;
            unsigned uniqueNames = 0;

            for (unsigned j = 0; j < optKMaxHexFileHistoryCount; j++) {
                DWORD strsize = sizeof(fnamebuff); // NB must set this for each string
                wchar_t *numbuff = NumToString(j);

                if ((ERROR_SUCCESS == RegQueryValueEx(hk, numbuff, 0, &valtype, (BYTE*)&fnamebuff, &strsize)) && (REG_SZ == valtype)) {
                    // TODO: sanitize file list against device names, duplicates

                    // use PathCanonicalize(), PathIsURL(), UrlCanonicalize(), ..

                    // check for duplicate before adding to file list
                    if (FileHistoryNameIsUnique(uniqueNames, fnamebuff, strsize)) {
                        optHexFileHistory[uniqueNames++] = wcs_dupsubstr(fnamebuff, strsize);
                    }
                    continue;
                }
                break; // fail => end of files list
            }
            optHexFileHistoryCount = uniqueNames;
            RegCloseKey(hk);
        }
        RegCloseKey(programKey);

        // plan save to registry any state that was missing or invalid on reading
        if (optNeedSaveFlags) {
            KickRegSaveTimer();
        }
    }
}


BOOL MonOptions::FileHistoryNameIsUnique(unsigned uniqueNames, const wchar_t* string, size_t length)
{
    if (uniqueNames > 0) {
        for (unsigned k = 0; k < uniqueNames; k++) {
            // TODO review use of wcscmp / wcsncmp / if we have canonical name we probably don't need ignore case?
            if (0 == wcscmp(optHexFileHistory[k], string)) {
                return FALSE;
            }
        }
    }

    return TRUE;
}


// return value indicates that some values have changed
BOOL MonOptions::SetShowOptionsAndRegistrySave(const MonOptions &newValues)
{
    // check & copy new options, setup auto-save
    if (optShowFlags != newValues.optShowFlags) {
        optShowFlags = newValues.optShowFlags;
        optNeedSaveShowFlags = TRUE;
        KickRegSaveTimer();
        return TRUE;
    }
    return FALSE;
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


BOOL MonOptions::SetArrivalOrRemovalTime(unsigned arrivalOrRemovalTime, BOOL saveChange)
{
    if (arrivalOrRemovalTime <= KArrivalOrRemovalTimeMaximum) {
        if (optArrivalOrRemovalTime != arrivalOrRemovalTime) {
            optArrivalOrRemovalTime = arrivalOrRemovalTime;
            if (saveChange) {
                optNeedSaveArrivalTime = TRUE;
                KickRegSaveTimer();
            }
        }
        return TRUE; // valid value
    }
    return FALSE;
}


/*
    (timer triggered/exit) save of changed state to the registry.

    Opens or creates registry keys, then call DoSaveChangedValues()
    to actually save values.

    destroyWindow parameter is only used for a Debug assert
*/
void MonOptions::RegistrySaveChangedValues(BOOL destroyWindow)
{
    assert(optNeedSaveFlags || destroyWindow);

#ifndef _DEBUG
    destroyWindow; // suppress unreferenced param warning on release build
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
            if (ERROR_SUCCESS == RegCreateKeyEx(hk1, KRegVendor, 0, L"",
                    REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk2, &disp)) {
                if (ERROR_SUCCESS == RegCreateKeyEx(hk2, KRegProgramName, 0, L"", REG_OPTION_NON_VOLATILE,
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
        temp = optViewSortOrder.mSortType;
        RegSetValueEx(programKey, KRegKeySortOrder, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optViewSortVersion;
        RegSetValueEx(programKey, KRegKeySortVersion, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optViewSortOrder.mSortReverse;
        RegSetValueEx(programKey, KRegKeySortReverse, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveViewSortOrder = FALSE;
    }

    if (optNeedSaveViewStyleButton) {
        temp = optViewStyleButton;
        RegSetValueEx(programKey, KRegKeyViewStyle, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveViewStyleButton = FALSE;
    }

    if (optNeedSaveWindowState) {
        // used if running from Startup Group, restore window state: Normal, Max, Min
        temp = optWindowState;
        RegSetValueEx(programKey, KRegKeyWinShow, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveWindowState = FALSE;
    }

    if (optNeedSaveViewColumns) {
        // save Device View Column widths
        temp = optDetailsColumnWidths[0];
        RegSetValueEx(programKey, KRegKeyViewColumnName, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optDetailsColumnWidths[1];
        RegSetValueEx(programKey, KRegKeyViewColumnDevice, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optDetailsColumnWidths[2];
        RegSetValueEx(programKey, KRegKeyViewColumnState, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optDetailsColumnWidths[3];
        RegSetValueEx(programKey, KRegKeyViewColumnLocus, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        temp = optDetailsColumnWidths[4];
        RegSetValueEx(programKey, KRegKeyViewColumnSerNum, 0, REG_DWORD, (BYTE*)&temp, sizeof(temp));
        optNeedSaveViewColumns = FALSE;
    }

    if (optNeedSaveHexFileHistory && optHexFileHistoryCount) {
        HKEY hk;

        optNeedSaveHexFileHistory = FALSE;
        if (ERROR_SUCCESS == RegCreateKeyEx(programKey, KRegKeyMRUHexFile, 0, L"",
                REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hk, &disp)) {

            for (unsigned j = 0; j < optHexFileHistoryCount; j++) {
                wchar_t *numbuff = NumToString(j);

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


void MonOptions::SaveWindowInfo(UINT showCmd, const RECT &rc)
{
    if ((SW_SHOWNORMAL == showCmd) || (SW_SHOWMINIMIZED == showCmd) || (SW_SHOWMAXIMIZED == showCmd)) {
        if (showCmd != optWindowState) {
            optWindowState = showCmd;
            optNeedSaveWindowState = TRUE;
            KickRegSaveTimer();
        }

        if (SW_SHOWNORMAL == showCmd) {
            if ((rc.left != optWindowPlace.left) || (rc.top != optWindowPlace.top) ||
                    (rc.right != optWindowPlace.right) || (rc.bottom != optWindowPlace.bottom)) {
                optWindowPlace = rc;
                optNeedSaveWindowPlace = TRUE;
                KickRegSaveTimer();
            }
        }
    }
}


void MonOptions::SaveViewSortOrder(ColumnSortParameters &aSortParams)
{
    if ((aSortParams.mSortType != optViewSortOrder.mSortType) && (aSortParams.mSortType <= lvDispMaxSort)) {
        optViewSortOrder.mSortType = aSortParams.mSortType;
        optNeedSaveViewSortOrder = TRUE;
    }
    if ((aSortParams.mSortReverse != optViewSortOrder.mSortReverse) && (aSortParams.mSortReverse <= 1)) {
        optViewSortOrder.mSortReverse = aSortParams.mSortReverse;
        optNeedSaveViewSortOrder = TRUE;
    }

    if (optNeedSaveViewSortOrder) {
        KickRegSaveTimer();
    }
}


void MonOptions::SaveViewStyleButton(int newStyle, BOOL aRestore)
{
    if (newStyle != optViewStyleButton) {
        optViewStyleButton = newStyle;
        if (!aRestore) {
            optNeedSaveViewStyleButton = TRUE;
            KickRegSaveTimer();
        }
    }
}


void MonOptions::KickRegSaveTimer()
{
    assert(optNeedSaveFlags);

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
    for (unsigned i = 0; i < optHexFileHistoryCount; i++) {
        if (!wcscmp(optHexFileHistory[i], filename)) {
            return;
        }
    }

    wchar_t *fname = _wcsdup(filename);
    wchar_t *oldname;
    if (!fname) {
        return; // out of memory
    }

    for (unsigned i = 0; i < optHexFileHistoryCount; i++) {
        if (!_wcsicmp(optHexFileHistory[i], fname)) {
            // replace old capitalisation with new, return
            free(optHexFileHistory[i]);
            optHexFileHistory[i] = fname;
            return;
        }
    }

    // make new name first, and move older filenames down the list
    for (unsigned i = 0; i < optHexFileHistoryCount; i++) {
        oldname = optHexFileHistory[i];
        optHexFileHistory[i] = fname;
        fname = oldname;
        optNeedSaveHexFileHistory = TRUE;
    }

    // extend list if not at limit
    if (optHexFileHistoryCount < optKMaxHexFileHistoryCount) {
        optHexFileHistory[optHexFileHistoryCount++] = fname;
        optNeedSaveHexFileHistory = TRUE;
        fname = NULL;
    }

    if (fname) {
        free(fname);
    }

    if (optNeedSaveHexFileHistory) {
        KickRegSaveTimer();
    }
}


void MonOptions::SetDetailsColumnWidth(unsigned column, int width)
{
    assert(column <= lvDispMaxSort);
#if defined(_DEBUG)
    PrintDebugStatus(L"SetDetailsColumnWidth(column %u, width %i)\n", column, width);
#endif

    if (optDetailsColumnWidths[column] != width) {
        optDetailsColumnWidths[column] = width;
        optNeedSaveViewColumns = TRUE;
    }
}


/* end of file monitoroptions.cpp */