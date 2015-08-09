/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: windowsversion.cpp

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

#include "rfidmonitor.h"


/*
    windowsversion.cpp seeded with:
    StartOrStopProgressMarquee() fn from rfidler-install program
 */

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


/* end of file windowsversion.cpp */