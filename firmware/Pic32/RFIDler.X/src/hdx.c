/***************************************************************************
 * A copy of the GNU GPL is appended to this file.                         *
 *                                                                         *
 * This licence is based on the nmap licence, and we express our gratitude *
 * for the work that went into producing it. There is no other connection  *
 * between RFIDler and nmap either expressed or implied.                   *
 *                                                                         *
 ********************** IMPORTANT RFIDler LICENSE TERMS ********************
 *                                                                         *
 *                                                                         *
 * All references to RFIDler herein imply all it's derivatives, namely:    *
 *                                                                         *
 * o RFIDler-LF Standard                                                   *
 * o RFIDler-LF Lite                                                       *
 * o RFIDler-LF Nekkid                                                     *
 *                                                                         *
 *                                                                         *
 * RFIDler is (C) 2013-2014 Aperture Labs Ltd.                             *
 *                                                                         *
 * This program is free software; you may redistribute and/or modify it    *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; Version 2 ("GPL"), BUT ONLY WITH ALL OF THE   *
 * CLARIFICATIONS AND EXCEPTIONS DESCRIBED HEREIN.  This guarantees your   *
 * right to use, modify, and redistribute this software under certain      *
 * conditions.  If you wish to embed RFIDler technology into proprietary   *
 * software or hardware, we sell alternative licenses                      *
 * (contact sales@aperturelabs.com).                                       *
 *                                                                         *
 * Note that the GPL places important restrictions on "derivative works",  *
 * yet it does not provide a detailed definition of that term.  To avoid   *
 * misunderstandings, we interpret that term as broadly as copyright law   *
 * allows.  For example, we consider an application to constitute a        *
 * derivative work for the purpose of this license if it does any of the   *
 * following with any software or content covered by this license          *
 * ("Covered Software"):                                                   *
 *                                                                         *
 * o Integrates source code from Covered Software.                         *
 *                                                                         *
 * o Is designed specifically to execute Covered Software and parse the    *
 * results (as opposed to typical shell or execution-menu apps, which will *
 * execute anything you tell them to).                                     *
 *                                                                         *
 * o Includes Covered Software in a proprietary executable installer.  The *
 * installers produced by InstallShield are an example of this.  Including *
 * RFIDler with other software in compressed or archival form does not     *
 * trigger this provision, provided appropriate open source decompression  *
 * or de-archiving software is widely available for no charge.  For the    *
 * purposes of this license, an installer is considered to include Covered *
 * Software even if it actually retrieves a copy of Covered Software from  *
 * another source during runtime (such as by downloading it from the       *
 * Internet).                                                              *
 *                                                                         *
 * o Links (statically or dynamically) to a library which does any of the  *
 * above.                                                                  *
 *                                                                         *
 * o Executes a helper program, module, or script to do any of the above.  *
 *                                                                         *
 * This list is not exclusive, but is meant to clarify our interpretation  *
 * of derived works with some common examples.  Other people may interpret *
 * the plain GPL differently, so we consider this a special exception to   *
 * the GPL that we apply to Covered Software.  Works which meet any of     *
 * these conditions must conform to all of the terms of this license,      *
 * particularly including the GPL Section 3 requirements of providing      *
 * source code and allowing free redistribution of the work as a whole.    *
 *                                                                         *
 * As another special exception to the GPL terms, Aperture Labs Ltd. grants*
 * permission to link the code of this program with any version of the     *
 * OpenSSL library which is distributed under a license identical to that  *
 * listed in the included docs/licenses/OpenSSL.txt file, and distribute   *
 * linked combinations including the two.                                  *
 *                                                                         *
 * Any redistribution of Covered Software, including any derived works,    *
 * must obey and carry forward all of the terms of this license, including *
 * obeying all GPL rules and restrictions.  For example, source code of    *
 * the whole work must be provided and free redistribution must be         *
 * allowed.  All GPL references to "this License", are to be treated as    *
 * including the terms and conditions of this license text as well.        *
 *                                                                         *
 * Because this license imposes special exceptions to the GPL, Covered     *
 * Work may not be combined (even as part of a larger work) with plain GPL *
 * software.  The terms, conditions, and exceptions of this license must   *
 * be included as well.  This license is incompatible with some other open *
 * source licenses as well.  In some cases we can relicense portions of    *
 * RFIDler or grant special permissions to use it in other open source     *
 * software.  Please contact sales@aperturelabs.com with any such requests.*
 * Similarly, we don't incorporate incompatible open source software into  *
 * Covered Software without special permission from the copyright holders. *
 *                                                                         *
 * If you have any questions about the licensing restrictions on using     *
 * RFIDler in other works, are happy to help.  As mentioned above, we also *
 * offer alternative license to integrate RFIDler into proprietary         *
 * applications and appliances.  These contracts have been sold to dozens  *
 * of software vendors, and generally include a perpetual license as well  *
 * as providing for priority support and updates.  They also fund the      *
 * continued development of RFIDler.  Please email sales@aperturelabs.com  *
 * for further information.                                                *
 * If you have received a written license agreement or contract for        *
 * Covered Software stating terms other than these, you may choose to use  *
 * and redistribute Covered Software under those terms instead of these.   *
 *                                                                         *
 * Source is provided to this software because we believe users have a     *
 * right to know exactly what a program is going to do before they run it. *
 * This also allows you to audit the software for security holes (none     *
 * have been found so far).                                                *
 *                                                                         *
 * Source code also allows you to port RFIDler to new platforms, fix bugs, *
 * and add new features.  You are highly encouraged to send your changes   *
 * to the RFIDler mailing list for possible incorporation into the         *
 * main distribution.  By sending these changes to Aperture Labs Ltd. or   *
 * one of the Aperture Labs Ltd. development mailing lists, or checking    *
 * them into the RFIDler source code repository, it is understood (unless  *
 * you specify otherwise) that you are offering the RFIDler Project        *
 * (Aperture Labs Ltd.) the unlimited, non-exclusive right to reuse,       *
 * modify, and relicense the code.  RFIDler will always be available Open  *
 * Source, but this is important because the inability to relicense code   *
 * has caused devastating problems for other Free Software projects (such  *
 * as KDE and NASM).  We also occasionally relicense the code to third     *
 * parties as discussed above. If you wish to specify special license      *
 * conditions of your contributions, just say so when you send them.       *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the RFIDler   *
 * license file for more details (it's in a COPYING file included with     *
 * RFIDler, and also available from                                        *
 *   https://github.com/ApertureLabsLtd/RFIDler/COPYING                    *
 *                                                                         *
 ***************************************************************************/

// Author: Adam Laurie <adam@aperturelabs.com>

// ISO-11784/5 HDX as per http://www.webcitation.org/5fsCRL5Zz

#include "HardwareProfile.h"
#include "detect.h"
#include "hdx.h"
#include "fsk.h"
#include "rfidler.h"
#include "util.h"

// HDX reads data in Half Duplex mode
// first we energise the TAG for long enough that it charges up
// then we use sniffer to read response
// each bit is 16 ticks, a 1 is 124.2 KHz and a 0 is 134.2 KHz
// activation frequency is 134.2 KHz (745 FCs))
BOOL hdx_get_uid(BYTE *response)
{
    BYTE i;
    BYTE tmp[HDX_DATABITS];
    
    // this is a work in progress, so until reading produces any data, return empty
    return FALSE;

    // energise tag & wait for wakeup period
    InitHWReaderClock(OC_TOGGLE_PULSE, 745 / 2L, 745, RWD_STATE_ACTIVE);
    Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wake_Period) / 100);

    // switch off clock and switch to sniffer mode
    detect_init();

    // read to temporary array for speed
    for(i= 0 ; i < HDX_DATABITS ; ++i)
        tmp[i]= read_external_clock_burst(16) / 1000L;

    // convert to binary based on freq +- 3
    for(i= 0 ; i < HDX_DATABITS ; ++i)
    {
        if (tmp[i] >= 122 && tmp[i] <= 128)
            tmp[i]= 0x01;
        else
            if (tmp[i] >= 129 && tmp[i] <= 135)
                 tmp[i]= 0x00;
            else
                return FALSE;
    }
    binarraytohex(response, tmp, HDX_DATABITS);
    return TRUE;
}

// convert human readable UID to 128 bit fdx-b HEX string
BOOL uid_to_hdx_hex(BYTE *hex, BYTE *uid)
{
    BYTE tmp[128];
    if(!uid_to_fdxb_bin(tmp, uid))
        return FALSE;

   binarraytohex(hex, tmp, 128);
   return TRUE;
}

// convert human readable UID to 128 bit fdx-b binary array
BOOL uid_to_hdx_bin(BYTE *bin, BYTE *uid)
{
    BYTE tmp1[64], crc[8], i;
    unsigned int country, crctag;
    unsigned long long id;

    memset(tmp1, 0x00, 64);

    // set animal flag
    if(uid[0] == 'A')
        tmp1[0]= 0x01;
    else
        if(uid[0] != '0')
            return FALSE;

    // set data flag
    if(uid[1] == 'D')
        tmp1[15]= 0x01;
    else
        if(uid[1] != '0')
            return FALSE;

    // set country code - 4 hex digits -> 10 bits
    country= bcdtouint(uid + 2, 4);
    inttobinarray(tmp1 + 16, country, 10);

    // set national ID - 12 hex digits -> 38 bits
    id= bcdtoulonglong(uid + 6, 12);
    ulonglongtobinarray(tmp1 + 26, id, 38);

    // reverse binary
    string_reverse(tmp1, 64);

    // add header for over-the-air: 10 x 0x00 + 0x01
    memset(bin, 0x00, 10);

    // every 9th bit is 0x01, but we can just fill the rest with 0x01 and overwrite
    memset(bin + 10, 0x01, 118);

    //data is 8 blocks of 8 bits, plus obfuscation bit
    for(i= 0 ; i < 8 ; ++i)
        memcpy(bin + 11 + i * 9, tmp1 + i * 8, 8);

    // calculate & append crc for 64 bits of data
    for(i= 0 ; i < 8 ; ++i)
        crc[i]= (BYTE) binarraytoint(tmp1 + i * 8, 8);
    crctag= crc_ccitt(crc, 8);
    inttobinarray(bin + 83, crctag >> 8, 8);
    inttobinarray(bin + 92, crctag, 8);

    // add trailer
    for(i= 0 ; i < 3 ; ++i)
        memset(bin + 101 + i * 9, 0x00, 8);

    return TRUE;
}

// convert fdxb 128 bit binary array to human readable UID
// format is ADCCCCIIIIIIIIIIII where A is 'A' or '0' for animal / non-animal,
// D is 'D' or '0' for Data block available / No data available, 
// CCCC is ISO-3166 country code or ICAR.ORG manufacturer code
// IIIIIIIIIIII is national ID
BOOL hdx_hex_to_uid(BYTE *uid, BYTE *hex)
{
    BYTE tmp[128];
    unsigned int country;
    unsigned long long id;


    // strip headers etc.
    if(!fdxb_hex_to_bin(tmp, hex))
        return FALSE;

    // reverse binary
    string_reverse(tmp, 64);

    // output animal flag
    if(tmp[0])
        uid[0]= 'A';
    else
        uid[0]= '0';

    // output data flag
    if(tmp[15])
        uid[1]= 'D';
    else
        uid[1]= '0';

    // output country/icar code
    country= binarraytoint(&tmp[16], 10);
    sprintf(&uid[2], "%04u", country);

    // output national ID
    id= binarraytoulonglong(&tmp[26], 38);
    sprintf(&uid[6], "%012llu", id);

    return TRUE;
}

// convert 32 hex digit/128 bit FDXB ID to 64 bit raw UID
// safe to do in-place as we use a scratchpad
BOOL hdx_hex_to_bin(BYTE *response, BYTE *fdxb)
{
    BYTE i, crc_check[8], trailer[9]= {0,0,0,0,0,0,0,0,1}, tmp[128];
    unsigned int crctag;

    hextobinarray(tmp, fdxb);

    // check header - should be 10 x 0x00 + 0x01
    for(i= 0 ; i < 10 ; ++i)
        if(tmp[i] != 0x00)
            return FALSE;
    if(tmp[10] != 0x01)
        return FALSE;

    // check CRC
    // calculate crc for 64 bits of data (8 blocks of 8 plus obfuscation bit)
    for(i= 0 ; i < 8 ; ++i)
        crc_check[i]= (BYTE) binarraytoint(tmp + 11 + i * 9, 8);
    // stored crc (2 x 8 + 1) is at offset 83 (11 + 64 + 8)
    crctag= binarraytoint(tmp + 83, 8) << 8;
    crctag += binarraytoint(tmp + 92, 8);
    if (crctag != crc_ccitt(crc_check, 8))
        return FALSE;

    // check trailer - '000000001' x 3 at offset 101
    for(i= 0 ; i < 3 ; ++i)
        if(memcmp(tmp + 101 + i * 9, trailer, 9) != 0)
            return FALSE;

    // data is 8 blocks of 8 bits, plus obfuscation bit so check and strip every 9th bit
    for(i= 0 ; i < 8 ; ++i)
    {
        if(tmp[11 + ((i + 1) * 9) - 1] != 0x01)
            return FALSE;
        memcpy(response + i * 8, tmp + 11 + (i * 9), 8);
    }

    return TRUE;
}
