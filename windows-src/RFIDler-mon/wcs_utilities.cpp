/* 

    Project: RFIDler Monitor v0.1
             Graphical monitor that lists which USB ports an RFIDler is 
             currently connected to, and watches for changes.
             Tool for Aperture Labs RFIDler LF.

    File: wcs_utilities.cpp

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


// duplicate a substring, max of length wide chars
// protects when copying registry strings that are not NIL terminated
wchar_t* wcs_dupsubstr(const wchar_t* string, size_t length)
{
    size_t alloclen; // = (string[length] == L'\0') ? length : (length + 1);
    wchar_t* buff = NULL;
    
    if (string != NULL) {
        for (alloclen = 0; (alloclen < length) && (string[alloclen] != L'\0'); alloclen++)
            ;

        if (alloclen > 0) {
            buff = (wchar_t*)calloc(alloclen + 1, sizeof(wchar_t));

            if (buff) {
                wcsncpy_s(buff, alloclen + 1, string, alloclen);
            }
        }
    }
    return buff;
}


// case insensitive substring search
const wchar_t* wcs_istr(const wchar_t* pString, const wchar_t* pSubStr)
{
    if (pString && pSubStr && *pString && *pSubStr) {
        size_t lenSubStr = wcslen(pSubStr);
        wchar_t ch = *pSubStr;

        do {
            while (*pString == ch) {
                if (!_wcsnicmp(pString, pSubStr, lenSubStr)) {
                    return pString;
                }
                pString++;
            }
            while (*pString && (*pString != ch)) {
                pString++;
            }
        } while(*pString);
    }
    return NULL;
}


// exact string prefix?
BOOL wcs_checkprefix(const wchar_t* String, const wchar_t* SubStr)
{
    size_t len = wcslen(SubStr);

    if (0 == wcsncmp(String, SubStr, len)) {
        return TRUE;
    }
    return FALSE;
}


// if string has expected prefix then return offset to the rest of the string, otherwise NULL
BOOL wcs_consumeprefix(const wchar_t* String, const wchar_t* SubStr, unsigned* Offset)
{
    size_t len = wcslen(SubStr);

    if (0 == wcsncmp(String, SubStr, len)) {
        *Offset = len;
        return TRUE;
    }
    *Offset = 0;
    return FALSE;
}


/* end of file wcs_utilities.cpp */