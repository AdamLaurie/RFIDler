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


#include "HardwareProfile.h"
#include "rfidler.h"
#include "tags.h"
#include "clock.h"
#include "hitag.h"
#include "q5.h"
#include "uid.h"
#include "fdxb.h"
#include "comms.h"
#include "hid.h"
#include "awid.h"
#include "em.h"
#include "indala.h"
#include "unique.h"

// tagtype #defines in rfidler.h
const BYTE *TagTypes[]= {
    "NONE",
    "ASKRAW",
    "FSK1RAW",
    "FSK2RAW",
    "PSK1RAW",
    "PSK2RAW",
    "PSK3RAW",
    "HITAG1",
    "HITAG2",
    "EM4X02",
    "Q5",
    "HID26",
    "INDALA64",
    "INDALA224",
    "UNIQUE",
    "FDXB",
    "T55X7",
    "AWID26",
    NULL
};

void tag_list(void)
{
    unsigned char i;

    UserMessage("%s", "\r\nKnown TAG types:\r\n");
    for(i= 1 ; TagTypes[i] != NULL ; ++i)
    {
        UserMessage("\r\n  %s", (BYTE *) TagTypes[i]);
    }
    UserMessage("%s", "\r\n");
}

BYTE tag_get_type(BYTE *tag)
{
    BYTE i;

    for(i= 0 ; TagTypes[i] != NULL ; ++i)
        if(strcmp(tag, TagTypes[i]) == 0)
            return i;
    return 0;
}

unsigned int tag_get_blocksize(BYTE tag)
{
    switch(tag)
    {        
        case TAG_TYPE_HITAG1:
            return hitag1_blocksize();

        case TAG_TYPE_HITAG2:
            return hitag2_blocksize();

        case TAG_TYPE_Q5:
        case TAG_TYPE_T55X7:
            return q5_blocksize();

        default:
            return 0;
    }
}

unsigned int tag_get_datablocks(BYTE tag)
{
    switch(tag)
    {
       case TAG_TYPE_HITAG1:
            return hitag1_datablocks();

        case TAG_TYPE_HITAG2:
            return hitag2_datablocks();

        case TAG_TYPE_Q5:
        case TAG_TYPE_T55X7:
            return q5_datablocks();

        default:
            return 0;
    }
}

unsigned int tag_get_databits(BYTE tag)
{
    switch(tag)
    {
        case TAG_TYPE_EM4X02:
            return EM4X02_DATABITS;
            
        case TAG_TYPE_HID_26:
            return HID26_DATABITS;

        case TAG_TYPE_AWID_26:
            return AWID26_DATABITS;

        case TAG_TYPE_FDXB:
            return FDXB_DATABITS;

        case TAG_TYPE_HITAG1:
            return hitag1_datablocks() * hitag1_blocksize();

        case TAG_TYPE_HITAG2:
            return hitag2_datablocks() * hitag2_blocksize();

        case TAG_TYPE_INDALA_64:
            return INDALA_64_DATABITS;

        case TAG_TYPE_INDALA_224:
            return INDALA_224_DATABITS;

        case TAG_TYPE_Q5:
        case TAG_TYPE_T55X7:
            return q5_datablocks() * q5_blocksize();

        case TAG_TYPE_UNIQUE:
            return UNIQUE_DATABITS;

        default:
            return 0;
    }
}

BYTE auto_detect_tag_type(void)
{
    BYTE i, tag, tmp[MAXUID + 1];

    tag= RFIDlerConfig.TagType;

    UserMessage("%s", "\r\n");
    for(i= 1 ; TagTypes[i] != NULL ; ++i)
    {
        UserMessage("\r\n  %s: ", (BYTE *) TagTypes[i]);
        tag_set(i);
        if(get_interpreted_tag_uid(tmp, RFIDlerConfig.TagType))
            UserMessage("%s", tmp);
    }
    tag_set(tag);
    UserMessage("%s", "\r\n");
}

BOOL tag_set(BYTE tag)
{
    // reset everything, then set what needs to be changed
    RFIDlerConfig.FrameClock= 0;
    RFIDlerConfig.BiPhase= FALSE;
    RFIDlerConfig.Manchester= FALSE;
    RFIDlerConfig.Invert= FALSE;
    RFIDlerConfig.Modulation= MOD_MODE_NONE;
    RFIDlerConfig.PotLow= 0;
    RFIDlerConfig.PotHigh= 0;
    RFIDlerConfig.DataRate= 0;
    RFIDlerConfig.DataBits= 0;
    RFIDlerConfig.TagType= tag;
    RFIDlerConfig.Repeat= 0;
    RFIDlerConfig.Timeout= 0L;
    RFIDlerConfig.Sync[0]= 0x00;
    RFIDlerConfig.Sync[1]= 0x00;
    RFIDlerConfig.Sync[2]= 0x00;
    RFIDlerConfig.Sync[3]= 0x00;
    RFIDlerConfig.SyncBits= 0;
    RFIDlerConfig.RWD_Gap_Period= 0;
    RFIDlerConfig.RWD_Sleep_Period= 0;
    RFIDlerConfig.RWD_Wake_Period= 0;
    RFIDlerConfig.RWD_Zero_Period= 0;
    RFIDlerConfig.RWD_One_Period= 0;
    RFIDlerConfig.RWD_Wait_Switch_RX_TX= 0;
    RFIDlerConfig.RWD_Wait_Switch_TX_RX= 0;

    switch(tag)
    {
        case TAG_TYPE_NONE:
            break;

        case TAG_TYPE_ASK_RAW:
            RFIDlerConfig.FrameClock= 800; // 125 KHz
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 100;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataBits= 256;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

      case TAG_TYPE_AWID_26:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_FSK;
            RFIDlerConfig.PotHigh=  100;
            RFIDlerConfig.DataRate= 50;
            RFIDlerConfig.DataRateSub0= 8;
            RFIDlerConfig.DataRateSub1= 10;
            RFIDlerConfig.DataBits= 96;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.Sync[0]= 0x01;
            RFIDlerConfig.Sync[1]= 0x1D;
            RFIDlerConfig.Sync[2]= 0x80;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 18;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

       case TAG_TYPE_FDXB:
            RFIDlerConfig.FrameClock= 745; // 134.2 KHz
            RFIDlerConfig.BiPhase= TRUE;
            RFIDlerConfig.Invert= TRUE;
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 130;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataBits= 128;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.Sync[0]= 0x00;
            RFIDlerConfig.Sync[1]= 0x20;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 11;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

       case TAG_TYPE_FSK1_RAW:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_FSK;
            RFIDlerConfig.PotHigh= POTHIGH_DEFAULT;
            RFIDlerConfig.DataRate= 50;
            RFIDlerConfig.DataRateSub0= 8;
            RFIDlerConfig.DataRateSub1= 5;
            RFIDlerConfig.DataBits= 256;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

       case TAG_TYPE_FSK2_RAW:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_FSK;
            RFIDlerConfig.PotHigh= 90;
            RFIDlerConfig.DataRate= 50;
            RFIDlerConfig.DataRateSub0= 8;
            RFIDlerConfig.DataRateSub1= 10;
            RFIDlerConfig.DataBits= 256;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;
                  
        case TAG_TYPE_HID_26:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_FSK;
            RFIDlerConfig.PotHigh=  120;
            RFIDlerConfig.DataRate= 50;
            RFIDlerConfig.DataRateSub0= 8;
            RFIDlerConfig.DataRateSub1= 10;
            RFIDlerConfig.DataBits= 96;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.Sync[0]= 0x1D;
            RFIDlerConfig.Sync[1]= 0x55;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 16;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

        case TAG_TYPE_HITAG1:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Manchester= TRUE;
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 170;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataBits= 33; //
            RFIDlerConfig.DataBlocks= HITAG1_DATABLOCKS;
            RFIDlerConfig.BlockSize= HITAG1_BLOCKSIZE;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.RWD_Gap_Period= 5; // 4 - 10
            RFIDlerConfig.RWD_Sleep_Period= 2000;
            RFIDlerConfig.RWD_Wake_Period= 500; // documentations says ~3ms, so round up a bit
            RFIDlerConfig.RWD_Zero_Period= 18; // 18 - 22
            RFIDlerConfig.RWD_One_Period= 32; // 26 - 32
            RFIDlerConfig.RWD_Wait_Switch_TX_RX= 180; // docs say 204, so stop a little earlier so we catch leading edge
            RFIDlerConfig.RWD_Wait_Switch_RX_TX= 120; // docs say 96, so give it a bit longer t0 be safe!
            RFIDlerConfig.SyncBits= 1;
            RFIDlerConfig.Sync[0]= 0x00;
            RFIDlerConfig.Sync[0]= 0x00;
            RFIDlerConfig.Sync[0]= 0x00;
            RFIDlerConfig.Sync[0]= 0x00;
            break;

        case TAG_TYPE_HITAG2:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Manchester= TRUE;
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 160;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataBits= 37; // 5 bits leadin + 32 bits ID
            RFIDlerConfig.DataBlocks= HITAG2_DATABLOCKS;
            RFIDlerConfig.BlockSize= HITAG2_BLOCKSIZE;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.RWD_Gap_Period= 4; // 4 - 10
            RFIDlerConfig.RWD_Sleep_Period= 2000;
            RFIDlerConfig.RWD_Wake_Period= 525; // (was 450) must be > 312.5 but less than 544 to allow reset of user modes
            RFIDlerConfig.RWD_Zero_Period= 18; // 18 - 22
            RFIDlerConfig.RWD_One_Period= 26; // 26 - 32
            RFIDlerConfig.RWD_Wait_Switch_TX_RX= 199;
            RFIDlerConfig.RWD_Wait_Switch_RX_TX= 90;
            RFIDlerConfig.Sync[0]= 0xF8;
            RFIDlerConfig.Sync[1]= 0x00;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 5;
            break;

        case TAG_TYPE_Q5:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Manchester= TRUE;
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 130;
            RFIDlerConfig.DataRate= 64;
            RFIDlerConfig.DataBits= 64;
            RFIDlerConfig.DataBlocks= Q5_DATABLOCKS;
            RFIDlerConfig.BlockSize= Q5_BLOCKSIZE;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.Sync[0]= 0xFF;
            RFIDlerConfig.Sync[1]= 0xFF;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 9;
            RFIDlerConfig.RWD_Sleep_Period= 2000;
            RFIDlerConfig.RWD_Wake_Period= 1000; // must be more than 3ms, but play it safe
            RFIDlerConfig.RWD_Gap_Period= 20; // 14 nominal, 8 - 50 normal, 8 - 25 fast write mode
            RFIDlerConfig.RWD_Zero_Period= 24; // 24 nominal, 16 - 31 normal, 8 - 15 fast write mode
            RFIDlerConfig.RWD_One_Period= 54; // 54 nominal, 48 - 63 normal, 24 - 31 fast write mode
            RFIDlerConfig.RWD_Wait_Switch_TX_RX= 64; // q5 will exit downlink mode after 64 but may not yet be damped!
            RFIDlerConfig.RWD_Wait_Switch_RX_TX= 192; // the longer the better!
            break;

        case TAG_TYPE_EM4X02:
        case TAG_TYPE_UNIQUE:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Manchester= TRUE;
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 100;
            RFIDlerConfig.DataRate= 64;
            RFIDlerConfig.DataBits= 64;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.Sync[0]= 0xFF;
            RFIDlerConfig.Sync[1]= 0xFF;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 9;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

        case TAG_TYPE_INDALA_64:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_PSK1;
            RFIDlerConfig.PotLow= POTLOW_DEFAULT;
            RFIDlerConfig.PotHigh= 170;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataRateSub0= 2;
            RFIDlerConfig.DataBits= 64;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.PSK_Quality= 4L;
            RFIDlerConfig.Sync[0]= 0x00;
            RFIDlerConfig.Sync[1]= 0x00;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 24;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

        case TAG_TYPE_INDALA_224:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_PSK1;
            RFIDlerConfig.PotLow= POTLOW_DEFAULT;
            RFIDlerConfig.PotHigh= 170;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataRateSub0= 2;
            RFIDlerConfig.DataBits= 224;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.PSK_Quality= 4L;
            RFIDlerConfig.Sync[0]= 0x00;
            RFIDlerConfig.Sync[1]= 0x00;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 24;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;

        case TAG_TYPE_PSK1_RAW:
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Modulation= MOD_MODE_PSK1;
            RFIDlerConfig.PotLow= POTLOW_DEFAULT;
            RFIDlerConfig.PotHigh= POTHIGH_DEFAULT;
            RFIDlerConfig.DataRate= 32;
            RFIDlerConfig.DataRateSub0= 2;
            RFIDlerConfig.DataBits= 256;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.PSK_Quality= 4L;
            RFIDlerConfig.RWD_Wake_Period= 1000;
            break;


        case TAG_TYPE_T55X7:
            // same as Q5 but slightly different timings, sync and no modulation-defeat
            RFIDlerConfig.FrameClock= 800;
            RFIDlerConfig.Manchester= TRUE;
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            RFIDlerConfig.PotHigh= 100;
            RFIDlerConfig.DataRate= 64;
            RFIDlerConfig.DataBits= 64;
            RFIDlerConfig.DataBlocks= Q5_DATABLOCKS;
            RFIDlerConfig.BlockSize= Q5_BLOCKSIZE;
            RFIDlerConfig.TagType= tag;
            RFIDlerConfig.Repeat= 20;
            RFIDlerConfig.Timeout= 13000; // timeout in uS (note with prescaler of 16 max is 13107)
            RFIDlerConfig.Sync[0]= 0xE0;
            RFIDlerConfig.Sync[1]= 0x15;
            RFIDlerConfig.Sync[2]= 0x00;
            RFIDlerConfig.Sync[3]= 0x00;
            RFIDlerConfig.SyncBits= 16;
            RFIDlerConfig.RWD_Sleep_Period= 2000;
            RFIDlerConfig.RWD_Wake_Period= 1000; // must be more than 3ms, but play it safe
            RFIDlerConfig.RWD_Gap_Period= 20; // 14 nominal, 8 - 50 normal, 8 - 25 fast write mode
            RFIDlerConfig.RWD_Zero_Period= 24; // 24 nominal, 16 - 31 normal, 8 - 15 fast write mode
            RFIDlerConfig.RWD_One_Period= 54; // 54 nominal, 48 - 63 normal, 24 - 31 fast write mode
            RFIDlerConfig.RWD_Wait_Switch_TX_RX= 70; // t55x7 will exit downlink mode after 64 but we mustn't read until t55x7 switches damping on
            RFIDlerConfig.RWD_Wait_Switch_RX_TX= 70;
            break;

        default:
            return FALSE;
    }

    // stop clocks
    stop_HW_clock();

    // configure potentiometers
    set_mcp414_wiper(WIPER_HIGH, VOLATILE, RFIDlerConfig.PotHigh, TmpBuff);
    set_mcp414_wiper(WIPER_LOW, VOLATILE, RFIDlerConfig.PotLow, TmpBuff);

    // delay to allow things to settle
    Delay_us(500000);
    
    return TRUE;
}

// encode UID to raw hex according to TAG selection
BOOL tag_uid_to_hex(BYTE *hex, BYTE *uid, BYTE tagtype)
{
    switch(tagtype)
    {
       case TAG_TYPE_AWID_26:
            if(!bcd_to_awid26_hex(hex, uid))
                return FALSE;
            return TRUE;
            
        case TAG_TYPE_Q5:
        case TAG_TYPE_EM4X02:
            if(!hex_to_em4x02_hex(hex, uid))
                return FALSE;
            return TRUE;

        case TAG_TYPE_FDXB:
            if(!uid_to_fdxb_hex(hex, uid))
                return FALSE;
            return TRUE;

        case TAG_TYPE_HID_26:
            if(!bcd_to_hid26_hex(hex, uid))
                return FALSE;
            return TRUE;

        case TAG_TYPE_INDALA_64:
            if(!indala64_hex_to_uid(hex, uid))
                return FALSE;
            return TRUE;


        case TAG_TYPE_INDALA_224:
            if(!indala224_hex_to_uid(hex, uid))
                return FALSE;
            return TRUE;

        case TAG_TYPE_UNIQUE:
            if(!hex_to_unique_hex(hex, uid))
                return FALSE;
            return TRUE;

        default:
            return FALSE;
    }
    return TRUE;
}
