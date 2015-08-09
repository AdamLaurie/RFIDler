/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: taskbarfeatures.cpp

    Author: Anthony Naggs, 2015

    Copyright (c) 2015 Anthony Naggs.
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
 taskbarfeatures.cpp seeded with StartOrStopProgressMarquee() fn from rfidler-install program

 TODO add fn to manage Taskbar icon overlays
 */


// control Progress Marquee in Window & optionally under Taskbar icon
// NOTE static state means currently only one Window can have progress bar at a time

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
    case PROG_COMPLETE:
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


/* end of file taskbarfeatures.cpp */