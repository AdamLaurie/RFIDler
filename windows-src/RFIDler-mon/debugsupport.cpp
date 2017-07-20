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


// everything in this file, mostly formatted debug prints, is for debug builds only

#if defined(_DEBUG)

/*
    TODO Function to check DLGTEMPLATEEX for compatibility with Property Sheet rules.

    Ref: https://blogs.msdn.microsoft.com/oldnewthing/20070108-02/?p=28493

    Must have Styles:
    DS_3DLOOK DS_CONTROL WS_CHILD WS_TABSTOP
    
    Optional Styles:
    DS_SHELLFONT DS_LOCALEDIT WS_CLIPCHILDREN

    Must not have other styles, e.g.:
    WS_OVERLAPPED
    WS_POPUP
    WS_MINIMIZE
    WS_VISIBLE
    WS_DISABLED
    WS_CLIPSIBLINGS
    WS_MAXIMIZE
    WS_CAPTION     (WS_BORDER | WS_DLGFRAME)
    WS_BORDER
    WS_DLGFRAME
    WS_VSCROLL
    WS_HSCROLL
    WS_SYSMENU
    WS_THICKFRAME
    WS_GROUP
    WS_MINIMIZEBOX
    WS_MAXIMIZEBOX
    DS_ABSALIGN
    DS_SYSMODAL
    DS_MODALFRAME  (Can be combined with WS_CAPTION )
    DS_NOIDLEMSG  (WM_ENTERIDLE message will not be sent)
    DS_SETFOREGROUND  (not in win3.1)
    DS_NOFAILCREATE
    DS_CENTER
    DS_CENTERMOUSE
    DS_CONTEXTHELP

*/


void DlgProcDebugReport(wchar_t *WindowName, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    switch(iMsg) {
    case WM_NOTIFY:
        {
            NMHDR *pNm = (NMHDR *) lParam;

            if (NM_CUSTOMDRAW != pNm->code) {
                PrintDebugStatus(L"%s WM_NOTIFY code 0x%x\n",
                    WindowName, pNm->code);
            }
        }
        break;

    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_CHAR:
        PrintDebugStatus(L"%s %s: wParam 0x%x, lParam %p\n",
            WindowName,
            (iMsg == WM_KEYDOWN) ? L"WM_KEYDOWN" : (iMsg == WM_KEYUP) ? L"WM_KEYUP" : L"WM_CHAR", wParam, lParam);
        break;
    }
}


void ListViewNotificationDebugReport(wchar_t *WindowName, NM_LISTVIEW *pNm)
{
    UINT notifycode = pNm->hdr.code;

    switch(notifycode) {
    case LVN_GETDISPINFOW:
        {   // no action seems to be needed
            NMLVDISPINFO* pdi = (NMLVDISPINFO*) pNm;

            PrintDebugStatus(L"%s WM_NOTIFY ListView hdr.code = LVN_GETDISPINFOW, iItem %u, mask = 0x%x\n",
                WindowName,
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
            NMLVKEYDOWN* pnkd = (NMLVKEYDOWN*) pNm;

            PrintDebugStatus(L"%s ListView LVN_KEYDOWN hwndFrom 0x%0x, wVKey %u 0x%0x, flags 0x%0x\n",
                WindowName,
                pNm->hdr.hwndFrom, pnkd->wVKey, pnkd->flags);
        }
        break;

    default: // report unhandled notifications
        if ((notifycode >= LVN_LAST) && (notifycode <= LVN_FIRST)) {
            PrintDebugStatus(L"%s WM_NOTIFY ListView hdr.code = %u = (LVN_FIRST-%u)\n",
                WindowName,
                notifycode, LVN_FIRST - notifycode);
        }
        break;
    }
}


void HeaderNotificationDebugReport(wchar_t *WindowName, LPNMHEADER pNmHdr)
{
    if ((pNmHdr->hdr.code >= HDN_LAST) && (pNmHdr->hdr.code <= HDN_FIRST)) {
        // NB particularly interested in Notifications from List View's Header Control
        LPWSTR psNotifyName = L"?";

        switch (pNmHdr->hdr.code) {
        case HDN_ITEMCHANGINGA: psNotifyName = L"HDN_ITEMCHANGINGA"; break;
        case HDN_ITEMCHANGINGW: psNotifyName = L"HDN_ITEMCHANGINGW"; break;
        case HDN_ITEMCHANGEDA: psNotifyName = L"HDN_ITEMCHANGEDA"; break;
        case HDN_ITEMCHANGEDW: psNotifyName = L"HDN_ITEMCHANGEDW"; break;
        case HDN_ITEMCLICKA: psNotifyName = L"HDN_ITEMCLICKA"; break;
        case HDN_ITEMCLICKW: psNotifyName = L"HDN_ITEMCLICKW"; break;
        case HDN_ITEMDBLCLICKA: psNotifyName = L"HDN_ITEMDBLCLICKA"; break;
        case HDN_ITEMDBLCLICKW: psNotifyName = L"HDN_ITEMDBLCLICKW"; break;
        case HDN_DIVIDERDBLCLICKA: psNotifyName = L"HDN_DIVIDERDBLCLICKA"; break;
        case HDN_DIVIDERDBLCLICKW: psNotifyName = L"HDN_DIVIDERDBLCLICKW"; break;
        case HDN_BEGINTRACKA: psNotifyName = L"HDN_BEGINTRACKA"; break;
        case HDN_BEGINTRACKW: psNotifyName = L"HDN_BEGINTRACKW"; break;
        case HDN_ENDTRACKA: psNotifyName = L"HDN_ENDTRACKA"; break;
        case HDN_ENDTRACKW: psNotifyName = L"HDN_ENDTRACKW"; break;
        case HDN_TRACKA: psNotifyName = L"HDN_TRACKA"; break;
        case HDN_TRACKW: psNotifyName = L"HDN_TRACKW"; break;
        case HDN_GETDISPINFOA: psNotifyName = L"HDN_GETDISPINFOA"; break;
        case HDN_GETDISPINFOW: psNotifyName = L"HDN_GETDISPINFOW"; break;
        case HDN_BEGINDRAG: psNotifyName = L"HDN_BEGINDRAG"; break;
        case HDN_ENDDRAG: psNotifyName = L"HDN_ENDDRAG"; break;
        case HDN_FILTERCHANGE: psNotifyName = L"HDN_FILTERCHANGE"; break;
        case HDN_FILTERBTNCLICK: psNotifyName = L"HDN_FILTERBTNCLICK"; break;
        case HDN_BEGINFILTEREDIT: psNotifyName = L"HDN_BEGINFILTEREDIT"; break;
        case HDN_ENDFILTEREDIT: psNotifyName = L"HDN_ENDFILTEREDIT"; break;
        case HDN_ITEMSTATEICONCLICK: psNotifyName = L"HDN_ITEMSTATEICONCLICK"; break;
        case HDN_ITEMKEYDOWN: psNotifyName = L"HDN_ITEMKEYDOWN"; break;
        case HDN_DROPDOWN: psNotifyName = L"HDN_DROPDOWN"; break;
        case HDN_OVERFLOWCLICK: psNotifyName = L"HDN_OVERFLOWCLICK"; break;
        }

        PrintDebugStatus(L"%s NMHEADER %s hwndFrom 0x%08x (%u), idFrom 0x%08x (%u), code 0x%x (%u)\n",
            WindowName,
            psNotifyName,
            pNmHdr->hdr.hwndFrom, pNmHdr->hdr.hwndFrom, pNmHdr->hdr.idFrom, pNmHdr->hdr.idFrom, pNmHdr->hdr.code, pNmHdr->hdr.code);
        PrintDebugStatus(L"  NMHEADER iItem %i, iButton %i, pitem %p\n",
            pNmHdr->iItem, pNmHdr->iButton, pNmHdr->pitem);
        if (pNmHdr->pitem) {
            PrintDebugStatus(L"  NMHEADER pitem: mask 0x%008x", pNmHdr->pitem->mask);
            if (HDI_WIDTH & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", cxy %u", pNmHdr->pitem->cxy);
            }
            if (HDI_TEXT & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", pszText(%i) %*s", pNmHdr->pitem->cchTextMax, pNmHdr->pitem->cchTextMax, pNmHdr->pitem->pszText);
            }
            if (HDI_FORMAT & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", fmt 0x%08x", pNmHdr->pitem->fmt);
            }
            if (HDI_LPARAM & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", lParam %p", pNmHdr->pitem->lParam);
            }
            if (HDI_BITMAP & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", hbm 0x%x", pNmHdr->pitem->hbm);
            }
            if (HDI_IMAGE & pNmHdr->pitem->mask) {
                // index of bitmap in ImageList
                PrintDebugStatus(L", iImage %i", pNmHdr->pitem->iImage);
            }
            if (HDI_DI_SETITEM & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", HDI_DI_SETITEM");
            }
            if (HDI_ORDER & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", iOrder %i", pNmHdr->pitem->iOrder);
            }
            if (HDI_FILTER & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", filter type %u, pvFilter %p", pNmHdr->pitem->type, pNmHdr->pitem->pvFilter);
            }
            if (HDI_STATE & pNmHdr->pitem->mask) {
                PrintDebugStatus(L", state %u", pNmHdr->pitem->state);
            }
            PrintDebugStatus(L"\n");
        }
    }
}


void TabControlNotificationDebugReport(wchar_t *WindowName, NMHDR *pNm)
{
    LPWSTR psNotifyName = L"?";

    switch (pNm->code) {
    case TTN_GETDISPINFO: psNotifyName = L"TTN_GETDISPINFO"; break;
    case NM_CLICK: psNotifyName = L"NM_CLICK"; break;
    case NM_RCLICK: psNotifyName = L"NM_RCLICK"; break;
    case NM_DBLCLK: psNotifyName = L"NM_DBLCLK"; break;
    case NM_RELEASEDCAPTURE: psNotifyName = L"NM_RELEASEDCAPTURE"; break;
    case TCN_FOCUSCHANGE: psNotifyName = L"TCN_FOCUSCHANGE"; break;
    case TCN_GETOBJECT: psNotifyName = L"TCN_GETOBJECT"; break;
    case TCN_KEYDOWN: psNotifyName = L"TCN_KEYDOWN"; break;
    case TCN_SELCHANGE: psNotifyName = L"TCN_SELCHANGE"; break;
    case TCN_SELCHANGING: psNotifyName = L"TCN_SELCHANGING"; break;
    }

    PrintDebugStatus(L"%s NMHEADER %s hwndFrom 0x%08x (%u), idFrom 0x%08x (%u), code 0x%x (%u)\n",
        WindowName,
        psNotifyName,
        pNm->hwndFrom, pNm->hwndFrom, pNm->idFrom, pNm->idFrom, pNm->code, pNm->code);
}


#endif // _DEBUG

/* end of file debugsupport.cpp */