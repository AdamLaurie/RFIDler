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
#include "t55x7.h"
#include "rwd.h"
#include "psk.h"
#include "util.h"
#include "comms.h"
#include "config.h"

const BYTE *T55x7_Compat_Modulation[]= {"NRZ/Direct", "PSK1", "PSK2", "PSK3", "FSK1", "FSK2", "FSK1a", "FSK2a", "Manchester"};

const BYTE T55x7_Compat_Data_Rates[]= {8, 16, 32, 40, 50, 64, 100, 128};

// response length in bits
BOOL t55x7_send_command(BYTE *response, BYTE *command, BYTE length, BOOL reset, BOOL sync, BYTE response_length)
{
    // send command
    if(!rwd_send(command, length, reset, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, T55X7_START_GAP - RFIDlerConfig.RWD_Gap_Period, 0, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    if(!response_length)
        return TRUE;

    // wait for T55x7 damping to kick in: t55x7 may create a false pulse during RWD receipt, so wait for it to recognise
    // command and shut down before trying to read response.
    GetTimer_us(RESET);
    while(READER_DATA)
        if(GetTimer_us(NO_RESET) > RFIDlerConfig.Timeout)
            return FALSE;

    // skip 4 bit Sequence Terminator pattern and leading '0'
    HW_Skip_Bits= 10; // 10 primitive 'bits' manchester encoded

//    DEBUG_PIN_4= !DEBUG_PIN_4;
//    DEBUG_PIN_4= !DEBUG_PIN_4;
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, response, response_length, RFIDlerConfig.Sync, sync ? RFIDlerConfig.SyncBits : 0, RFIDlerConfig.Timeout, ONESHOT_READ, HEX) == response_length)
    {
        // delay for RX->TX time
        Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wait_Switch_RX_TX) / 100);
        return TRUE;
    }
    return FALSE;
}

// get raw UID
BOOL t55x7_get_uid(BYTE *response)
{
    BYTE tmp[33]; // 16 hex digits

    // t55x7 will be stuck if last command was a read or write, so always hard reset
    stop_HW_clock();

    // delay for sleep period
    Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Sleep_Period) / 100);

    // delay for startup time
    Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wake_Period) / 100);

    // t55x7 has fixed tracebility data - 2 x 32 bit blocks
    if(t55x7_send_command(tmp, T55X7_GET_TRACE_DATA, strlen(T55X7_GET_TRACE_DATA), NO_RESET, SYNC, 64))
    {
        strcpy(response, tmp);
        return TRUE;
    }
    return FALSE;
}

BOOL t55x7_read_block(BYTE *response, BYTE block)
{
    BYTE tmp[39], p, retry, reset= FALSE;

    if(block > T55X7_DATABLOCKS - 1)
        return FALSE;

    // create 6 or 38 bit command block: T55X7_DIRECT_ACCESS + [PWD] + single '0' + 3 bits address
    memset(tmp, '\0', sizeof(tmp));

    // command
    memcpy(tmp, T55X7_DIRECT_ACCESS, 2);
    p = 2;

    // password
    if(PWD_Mode)
    {
        hextobinstring(tmp + p, Password);
        p += 32;
    }

    // single '0'
    tmp[p]= '0';
    ++p;

    // address
    inttobinstring(tmp + p, (unsigned int) block, 3);
    p += 3;

    retry= RFIDlerConfig.Repeat;
    while(retry--)
    {
        //DEBUG_PIN_4= !DEBUG_PIN_4;
        //DEBUG_PIN_4= !DEBUG_PIN_4;
        if(t55x7_send_command(response, tmp, strlen(tmp), reset, NO_SYNC, 32))
            return TRUE;
        // try resetting tag
        reset= TRUE;
    }

    return FALSE;
}

// optional verify as writing config block may casue next read to fail
BOOL t55x7_write_block(BYTE block, BYTE *data, BOOL lock, BOOL verify)
{
    BYTE tmp[71], p;

    if(block > T55X7_DATABLOCKS - 1)
        return FALSE;

    // create 38 or 70 bit command block: T55X7_STD_WRITE_P0 + [PWD] + Lock Bit + 32 bits Data + 3 bits address
    memset(tmp, '\0', sizeof(tmp));

    // command
    memcpy(tmp, T55X7_STD_WRITE_P0, 2);
    p= 2;

    // password
    if(PWD_Mode)
    {
        hextobinstring(tmp + p, Password);
        p += 32;
    }

    // lockbit
    inttobinstring(tmp + p, (unsigned int) lock, 1);
    ++p;

    // data
    hextobinstring(tmp + p, data);
    p += T55X7_BLOCKSIZE;

    // address
    inttobinstring(tmp + p, (unsigned int) block, 3);
    p += 3;

    // send
    if(!t55x7_send_command(NULL, tmp, strlen(tmp), NO_RESET, NO_SYNC, 0))
         return FALSE;

    // no ack, so read back and verify
    // delay for long enough to allow write plus TX->RX period
    Delay_us((T55X7_WRITE_DELAY * RFIDlerConfig.FrameClock + RFIDlerConfig.RWD_Wait_Switch_TX_RX * RFIDlerConfig.FrameClock) / 100L);

    if(!verify)
        return TRUE;

    if(!t55x7_read_block(tmp, block))
        return FALSE;
    if(memcmp(tmp, data, HEXDIGITS(T55X7_BLOCKSIZE)) != 0)
        return FALSE;

    return TRUE;
}

// try to find values that correctly transmit all commands to t55x7
// so that a GET_UID command will return a true value
BOOL t55x7_rwd_test(BYTE *pattern)
{
    BYTE gap, one, zero, i, tmp[T55X7_BLOCKSIZE * 2 + 1];
    BOOL found= FALSE;

    // min/max from datasheets
    for(one= 48 ; one <= 63 ; ++one)
        for(zero= 16; zero <= 31 ; ++zero)
            for(gap=  8 ; gap <= 30 ; ++gap)
            {
                if(get_user_abort())
                    return found;
                RFIDlerConfig.RWD_Gap_Period= gap;
                RFIDlerConfig.RWD_One_Period= one;
                RFIDlerConfig.RWD_Zero_Period= zero;
                if(get_tag_uid(tmp))
                {
                    UserMessageNum(" gap: %d", gap);
                    UserMessageNum(" one: %d", one);
                    UserMessageNum(" zero: %d", zero);
                    UserMessage(" UID: %s\r\n", tmp);
                    found= TRUE;
                }
            }
    UserMessage("%s", "\r\n");
    return found;
}

BOOL t55x7_config_block_show(BYTE *config, BYTE *password)
{
    uint32_t    value= hextoulong(config);
    BOOL        xmode;

    UserMessage("  Config Block (0): %.8s\r\n\r\n", config);
    UserMessageNum("        Master Key: %d  = ", GET_CONFIG(value, T55X7_MASK_MASTER_KEY, T55X7_SHIFT_MASTER_KEY));
    if(GET_CONFIG(value, T55X7_MASK_MASTER_KEY, T55X7_SHIFT_MASTER_KEY) == T55X7_COMPAT_MODE)
        UserMessage("%s\r\n", "Compatibility Mode");
    else
        if(GET_CONFIG(value, T55X7_MASK_MASTER_KEY, T55X7_SHIFT_MASTER_KEY) == T55X7_XMODE_MODE)
            UserMessage("%s\r\n", "Extended Mode");
        else
            UserMessage("%s\r\n", "Undefined Mode");
    xmode= GET_CONFIG(value, T55X7_MASK_XMODE, T55X7_SHIFT_XMODE);
    UserMessage("            X-Mode: %s\r\n", xmode ? "True" : "False");

    // display additional/alternate fields if in xmode
    if(xmode)
    {
        UserMessageNum("         Data Rate: %02d = ", GET_CONFIG(value, T55X7_XMODE_MASK_DATA_BIT_RATE, T55X7_SHIFT_DATA_BIT_RATE));
        UserMessageNum("%d * FC\r\n", GET_CONFIG(value, T55X7_XMODE_MASK_DATA_BIT_RATE, T55X7_SHIFT_DATA_BIT_RATE) * 2 + 2);
        UserMessageNum("        Modulation: %02d = ", GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION));
        if(GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION) > 8)
        {
            if(GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION)== T55X7_MOD_BIPHASE_50)
                UserMessage("%s\r\n", "BiPhase ('50)");
            else
                if (GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION)== T55X7_MOD_BIPHASE_57)
                    UserMessage("%s\r\n", "BiPhase ('57)");
                else
                    UserMessage("%s\r\n", "Invalid");
        }
        else
            UserMessage("%s\r\n", (BYTE *) T55x7_Compat_Modulation[GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION)]);
       UserMessage("              SST: %s\r\n", GET_CONFIG(value, T55X7_XMODE_MASK_SST, T55X7_SHIFT_ST_SST) ? "True" : "False");
    }
    else
    {
        UserMessageNum("         Data Rate: %02d = ", GET_CONFIG(value, T55X7_COMPAT_MASK_DATA_BIT_RATE, T55X7_SHIFT_DATA_BIT_RATE));
        UserMessageNum("%d * FC\r\n", T55x7_Compat_Data_Rates[GET_CONFIG(value, T55X7_COMPAT_MASK_DATA_BIT_RATE, T55X7_SHIFT_DATA_BIT_RATE)]);
        UserMessageNum("        Modulation: %02d = ", GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION));
        if(GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION) > 8)
        {
            if(GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION)== 16)
                UserMessage("%s\r\n", "BiPhase ('50)");
            else
                UserMessage("%s\r\n", "Reserved/Invalid");
        }
        else
            UserMessage("%s\r\n", (BYTE *) T55x7_Compat_Modulation[GET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION)]);
        UserMessage("                ST: %s\r\n", GET_CONFIG(value, T55X7_COMPAT_MASK_ST, T55X7_SHIFT_ST_SST) ? "True" : "False");
    }
    // display common fields
    UserMessageNum("       PSK Carrier: %d = ", GET_CONFIG(value, T55X7_MASK_PSK_CARRIER_FREQ, T55X7_SHIFT_PSK_CARRIER_FREQ));
    if(GET_CONFIG(value, T55X7_MASK_PSK_CARRIER_FREQ, T55X7_SHIFT_PSK_CARRIER_FREQ) > 2)
        UserMessage("%s\r\n", "Reserved");
    else
        UserMessageNum("%d * FC\r\n", GET_CONFIG(value, T55X7_MASK_PSK_CARRIER_FREQ, T55X7_SHIFT_PSK_CARRIER_FREQ) * 2 + 2);
    UserMessageNum("          Maxblock: %d\r\n", GET_CONFIG(value, T55X7_MASK_MAX_BLOCK, T55X7_SHIFT_MAX_BLOCK));
    UserMessage("               AOR: %s\r\n", GET_CONFIG(value, T55X7_MASK_AOR, T55X7_SHIFT_AOR) ? "True" : "False");
    UserMessage("               OTP: %s\r\n", GET_CONFIG(value, T55X7_MASK_OTP, T55X7_SHIFT_OTP) ? "True" : "False");
    UserMessage("               PWD: %s\r\n", GET_CONFIG(value, T55X7_MASK_PWD, T55X7_SHIFT_PWD) ? "True" : "False");
    UserMessage("        Fast Write: %s\r\n", GET_CONFIG(value, T55X7_MASK_FAST_WRITE, T55X7_SHIFT_FAST_WRITE) ? "True" : "False");
    UserMessage("      Inverse Data: %s\r\n", GET_CONFIG(value, T55X7_MASK_INVERSE_DATA, T55X7_SHIFT_INVERSE_DATA) ? "True" : "False");
    UserMessage("         POR Delay: %s\r\n", GET_CONFIG(value, T55X7_MASK_POR_DELAY, T55X7_SHIFT_POR_DELAY) ? "True" : "False");

    UserMessage("\r\n     PWD Block (7): %.8s    ", password);
    printhexreadable(password, 4);
    UserMessage("%s", "\r\n");
    return TRUE;
}

//// create a config block based on current tag settings
BOOL t55x7_create_config_block(BYTE *config)
{
    uint32_t    value= hextoulong(config);
    BYTE        i, tmp, xmode= FALSE;

    // first decide if we need to be in extended mode or not

    // invert is only supported in x-mode
    if(RFIDlerConfig.Invert)
        xmode= TRUE;

    // is data rate supported by compat mode?
    for(i= 0, tmp= FALSE ; i < sizeof(T55x7_Compat_Data_Rates) ; ++i)
        if(RFIDlerConfig.DataRate == T55x7_Compat_Data_Rates[i])
        {
            tmp= TRUE;
            break;
        }
    if(!tmp)
        xmode= TRUE;

    // data rate
    if(xmode)
    {
       value= SET_CONFIG(value, T55X7_MASK_MASTER_KEY, T55X7_SHIFT_MASTER_KEY, T55X7_XMODE_MODE);
       value= SET_CONFIG(value, T55X7_MASK_XMODE, T55X7_SHIFT_XMODE, TRUE);
       value= SET_CONFIG(value, T55X7_XMODE_MASK_DATA_BIT_RATE, T55X7_SHIFT_DATA_BIT_RATE, (RFIDlerConfig.DataRate - 2) / 2);
    }
    else
       value= SET_CONFIG(value, T55X7_COMPAT_MASK_DATA_BIT_RATE, T55X7_SHIFT_DATA_BIT_RATE, i);

    // psk sub-carrier
    if(RFIDlerConfig.DataRateSub0)
        value= SET_CONFIG(value, T55X7_MASK_PSK_CARRIER_FREQ, T55X7_SHIFT_PSK_CARRIER_FREQ, RFIDlerConfig.DataRateSub0 / 4);

    // modulation
    if(RFIDlerConfig.Manchester && RFIDlerConfig.Modulation == MOD_MODE_ASK_OOK)
        tmp= T55X7_MOD_MANCHESTER;
    else
    {
        // todo - add general support for biphase 57 (but this is just biphase 50 with inversion)
        if(RFIDlerConfig.BiPhase && RFIDlerConfig.Modulation == MOD_MODE_ASK_OOK)
            tmp= T55X7_MOD_BIPHASE_50;
        else
            switch(RFIDlerConfig.Modulation)
            {
                case MOD_MODE_ASK_OOK:
                    tmp= T55X7_MOD_DIRECT;
                    break;
                case MOD_MODE_FSK1:
                    tmp= T55X7_MOD_FSK1;
                    break;
                case MOD_MODE_FSK2:
                    tmp= T55X7_MOD_FSK2;
                    break;
                case MOD_MODE_PSK1:
                    tmp= T55X7_MOD_PSK1;
                    break;
                case MOD_MODE_PSK2:
                    tmp= T55X7_MOD_PSK2;
                    break;
                case MOD_MODE_PSK3:
                    tmp= T55X7_MOD_PSK3;
                    break;
                default:
                    return FALSE;
            }
    }
    value= SET_CONFIG(value, T55X7_MASK_MODULATION, T55X7_SHIFT_MODULATION, tmp);

    // data blocks
    value= SET_CONFIG(value, T55X7_MASK_MAX_BLOCK, T55X7_SHIFT_MAX_BLOCK, RFIDlerConfig.DataBits / T55X7_BLOCKSIZE);

    ulongtohex(config, value);

    return TRUE;
}

// set a config block suitable for emulating
BOOL t55x7_emulate_config_block(BYTE *config, BYTE target_tagtype)
{
    switch (target_tagtype)
    {
       case TAG_TYPE_ASK_RAW:
       case TAG_TYPE_FSK1_RAW:
       case TAG_TYPE_FSK2_RAW:
       case TAG_TYPE_PSK1_RAW:
       case TAG_TYPE_PSK2_RAW:
       case TAG_TYPE_PSK3_RAW:
           memcpy(config, T55X7_RAW_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
           t55x7_create_config_block(config);
           return TRUE;

       case TAG_TYPE_AWID_26:
       case TAG_TYPE_HID_26:
            memcpy(config, T55X7_HID_26_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_FDXB:
            memcpy(config, T55X7_FDXB_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_INDALA_64:
            memcpy(config, T55X7_INDALA_64_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_INDALA_224:
            memcpy(config, T55X7_INDALA_224_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_EM4X02:
        case TAG_TYPE_UNIQUE:
        case TAG_TYPE_PAXTON:
            memcpy(config, T55X7_EM_UNIQUE_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_T55X7:
            memcpy(config, T55X7_DEFAULT_CONFIG_BLOCK, HEXDIGITS(T55X7_BLOCKSIZE));
            return TRUE;

        default:
            return FALSE;
    }
}
