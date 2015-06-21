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
#include "q5.h"
#include "ask.h"
#include "rwd.h"
#include "util.h"
#include "comms.h"
#include "config.h"

const BYTE *Q5_Modulation[]= {"Manchester", "PSK1", "PSK2", "PSK3", "FSK1", "FSK2", "Biphase", "NRZ/Direct"};
const BYTE PSK_Rates[]= {2, 4, 8, 8};

// q5 needs special timings etc., so have a master send command routine to keep things simple
// response length in bits
BOOL q5_send_command(BYTE *response, BYTE *command, BYTE length, BOOL reset, BOOL sync, BYTE response_length)
{
    // send command
    if(!rwd_send(command, length, reset, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, Q5_START_GAP - RFIDlerConfig.RWD_Gap_Period, 0, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    if(!response_length)
        return TRUE;

    // wait for Q5 damping to kick in: q5 may create a false pulse during RWD receipt, so wait for it to recognise
    // command and shut down before trying to read response.
    GetTimer_us(RESET);
    while(READER_DATA)
        if(GetTimer_us(NO_RESET) > RFIDlerConfig.Timeout)
            return FALSE;

    // skip leading '0'
    HW_Skip_Bits= 1;  // 2 primitive 'bits' manchester encoded, but we lose 1/2 a bit due to ASK startup delay, so skip 1 less

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
BOOL q5_get_uid(BYTE *response)
{
    BYTE tmp[17]; // 16 hex digits

    // q5 will be stuck if last command was a read or write, so always hard reset
    stop_HW_clock();

    // delay for sleep period
    Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Sleep_Period) / 100);

    // delay for startup time
    //Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wake_Period) / 100);

    // q5 has fixed em4x02 style data in page 1
    if(q5_send_command(tmp, Q5_GET_TRACE_DATA, strlen(Q5_GET_TRACE_DATA), NO_RESET, SYNC, 64))
    {
        strcpy(response, tmp);
        return TRUE;
    }
    return FALSE;
}

// convert raw 64 bit HEX UID to 10 digit human readable hex
BOOL q5_hex_to_uid(BYTE *response, BYTE *hex)
{
    // q5 is the same as em4x02
    return em4x02_hex_to_uid(response, hex);
}

BOOL q5_read_block(BYTE *response, BYTE block)
{
    BYTE tmp[39], retry, reset= FALSE;

    if(block > Q5_DATABLOCKS - 1)
        return FALSE;

    // create 6 or 38 bit command block: Q5_DIRECT_ACCESS + PWD_Mode + [PWD] + 3 bits address
    memset(tmp, '\0', 39);
    memcpy(tmp, Q5_DIRECT_ACCESS, 2);
    if(PWD_Mode)
    {
        tmp[2]= '1';
        hextobinstring(tmp + 3, Password);
        inttobinstring(tmp + 34, (unsigned int) block, 3);
    }
    else
    {
        tmp[2]= '0';
        inttobinstring(tmp + 3, (unsigned int) block, 3);
    }

    retry= RFIDlerConfig.Repeat;
    while(retry--)
    {
        //DEBUG_PIN_4= !DEBUG_PIN_4;
        //DEBUG_PIN_4= !DEBUG_PIN_4;
        if(q5_send_command(response, tmp, strlen(tmp), reset, NO_SYNC, 32))
            return TRUE;
        // try resetting tag
        reset= TRUE;
    }

    return FALSE;
}

// optional verify as writing config block may casue next read to fail
BOOL q5_write_block(BYTE block, BYTE *data, BOOL lock, BOOL verify)
{
    BYTE tmp[71], p;

    if(block > Q5_DATABLOCKS - 1)
        return FALSE;

    // create 38 or 70 bit command block: Q5_STD_WRITE_P0 + [PWD] + Lock Bit + 32 bits Data + 3 bits address
    memset(tmp, '\0', sizeof(tmp));

    // command
    memcpy(tmp, Q5_STD_WRITE_P0, 2);
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
    p += Q5_BLOCKSIZE;

    // address
    inttobinstring(tmp + p, (unsigned int) block, 3);
    p += 3;

    // send
    if(!q5_send_command(NULL, tmp, strlen(tmp), NO_RESET, NO_SYNC, 0))
         return FALSE;
    
    // no ack, so read back and verify
    // delay for long enough to allow write plus TX->RX period
    Delay_us((Q5_WRITE_DELAY * RFIDlerConfig.FrameClock + RFIDlerConfig.RWD_Wait_Switch_TX_RX * RFIDlerConfig.FrameClock) / 100L);
    
    if(!verify)
        return TRUE;

    if(!q5_read_block(tmp, block))
        return FALSE;
    if(memcmp(tmp, data, HEXDIGITS(Q5_BLOCKSIZE)) != 0)
        return FALSE;

    return TRUE;
}

// set password and mode, and return UID
BOOL q5_login(BYTE *response, BYTE *pass)
{
    BYTE tmp[35];

    // check we need password - if we can get UID without, then we don't
    if(q5_get_uid(tmp))
        return FALSE;

    if(strlen(pass) == 0)
        pass= Q5_DEFAULT_PWD;

    memcpy(tmp, Q5_AOR, 2);
    hextobinstring(tmp + 2, pass);
    tmp[34]= '\0';

    // send password
    if (!q5_send_command(response, tmp, strlen(tmp), RESET, NO_SYNC, 0))
        return FALSE;

    // see if we can now get UID
    if(!q5_get_uid(tmp))
        return FALSE;

    PWD_Mode= TRUE;
    strcpy(Password, pass);
    strcpy(response, pass);
    return TRUE;
}

// try to find values that correctly transmit all commands to q5
// to test this properly, q5 should have invalid data in it's data blocks
// so that only a GET_TRACE_DATA command will return a true value
BOOL q5_rwd_test(BYTE *pattern)
{
    BYTE gap, one, zero, tmp[Q5_BLOCKSIZE + 1];
    BOOL found= FALSE, blank;

    // min/max from datasheets
    for(one= 48 ; one <= 63 ; ++one)
        for(zero= 16; zero <= 31 ; ++zero)
            for(gap=  10 ; gap <= 50 ; ++gap)
            {
                RFIDlerConfig.Manchester= TRUE;
                blank= TRUE;
                if(get_user_abort())
                    return found;
                RFIDlerConfig.RWD_Gap_Period= gap;
                RFIDlerConfig.RWD_One_Period= one;
                RFIDlerConfig.RWD_Zero_Period= zero;
                // reset tag
                get_tag_uid(tmp);
                // try to switch off modulation
                rwd_send(Q5_MODULATION_DEFEAT, strlen(Q5_MODULATION_DEFEAT), NO_RESET, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, RFIDlerConfig.RWD_Gap_Period, 0, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX);
                // read a block with no sync & no manchester - will be all '0' if not modulating
                RFIDlerConfig.Manchester= FALSE;
                if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, RFIDlerConfig.DataBits, RFIDlerConfig.Sync, 0, RFIDlerConfig.Timeout, NO_ONESHOT_READ, HEX) == RFIDlerConfig.DataBits)
                {
                    if(strcmp(tmp, "0000000000000000") != 0)
                            blank= FALSE;
                    RFIDlerConfig.Manchester= TRUE;
                    if(blank && get_tag_uid(tmp) && q5_read_block(tmp, 0))
                    {
                        UserMessageNum("\r\nFound tag with gap %d", gap);
                        UserMessageNum(" one %d", one);
                        UserMessageNum(" zero %d", zero);
                        found= TRUE;
                    }
                }
            }
    UserMessage("%s", "\r\n");
    return found;
}

BOOL q5_config_block_show(BYTE *config)
{
    uint32_t    value= hextoulong(config);

    UserMessage("  Config Block: %.8s\r\n", config);
    UserMessage("   Page Select: %s\r\n", GET_CONFIG(value, Q5_MASK_PAGE_SELECT, Q5_SHIFT_PAGE_SELECT) ? "True" : "False");
    UserMessage("    Fast Write: %s\r\n", GET_CONFIG(value, Q5_MASK_FAST_WRITE, Q5_SHIFT_FAST_WRITE) ? "True" : "False");
    UserMessageNum("     Data Rate: %02d = ", GET_CONFIG(value, Q5_MASK_DATA_BIT_RATE, Q5_SHIFT_DATA_BIT_RATE));
    UserMessageNum("%d * FC\r\n", GET_CONFIG(value, Q5_MASK_DATA_BIT_RATE, Q5_SHIFT_DATA_BIT_RATE) * 2 + 2);
    UserMessage("       Use AOR: %s\r\n", GET_CONFIG(value, Q5_MASK_USE_AOR, Q5_SHIFT_USE_AOR) ? "True" : "False");
    UserMessage("       Use PWD: %s\r\n", GET_CONFIG(value, Q5_MASK_USE_PWD, Q5_SHIFT_USE_PWD) ? "True" : "False");
    UserMessageNum("   PSK Carrier: %d  = ", GET_CONFIG(value, Q5_MASK_PSK_CARRIER_FREQ, Q5_SHIFT_PSK_CARRIER_FREQ));
    UserMessageNum("%d * FC\r\n", PSK_Rates[GET_CONFIG(value, Q5_MASK_PSK_CARRIER_FREQ, Q5_SHIFT_PSK_CARRIER_FREQ)]);
    UserMessage("  Inverse Data: %s\r\n", GET_CONFIG(value, Q5_MASK_INVERSE_DATA, Q5_SHIFT_INVERSE_DATA) ? "True" : "False");
    UserMessageNum("    Modulation: %d  = ", GET_CONFIG(value, Q5_MASK_MODULATION, Q5_SHIFT_MODULATION));
    UserMessage("%s\r\n", (BYTE *) Q5_Modulation[GET_CONFIG(value, Q5_MASK_MODULATION, Q5_SHIFT_MODULATION)]);
    UserMessageNum("     Max Block: %d\r\n", GET_CONFIG(value, Q5_MASK_MAX_BLOCK, Q5_SHIFT_MAX_BLOCK));
    UserMessage("            ST: %s", GET_CONFIG(value, Q5_MASK_ST, Q5_SHIFT_ST) ? "True" : "False");
    return TRUE;
}

// create a config block based on current tag settings
BOOL q5_create_config_block(BYTE *config)
{
    uint32_t    value= hextoulong(config);
    BYTE        tmp;

    // data rate
    value= SET_CONFIG(value, Q5_MASK_DATA_BIT_RATE, Q5_SHIFT_DATA_BIT_RATE, (RFIDlerConfig.DataRate - 2) / 2);

    // psk sub-carrier
    if((tmp= RFIDlerConfig.DataRateSub0))
    {
        if(tmp == 2)
            tmp= 0;
        else
            if (tmp == 4)
                tmp= 1;
            else
                tmp= 2;
        value= SET_CONFIG(value, Q5_MASK_PSK_CARRIER_FREQ, Q5_SHIFT_PSK_CARRIER_FREQ, tmp);
    }

    // modulation
    if(RFIDlerConfig.Manchester && RFIDlerConfig.Modulation == MOD_MODE_ASK_OOK)
        tmp= Q5_MOD_MANCHESTER;
    else
    {
        if(RFIDlerConfig.BiPhase && RFIDlerConfig.Modulation == MOD_MODE_ASK_OOK)
            tmp= Q5_MOD_BIPHASE;
        else
            switch(RFIDlerConfig.Modulation)
            {
                case MOD_MODE_ASK_OOK:
                    tmp= Q5_MOD_DIRECT;
                    break;
                case MOD_MODE_FSK1:
                    tmp= Q5_MOD_FSK1;
                    break;
                case MOD_MODE_FSK2:
                    tmp= Q5_MOD_FSK2;
                    break;
                case MOD_MODE_PSK1:
                    tmp= Q5_MOD_PSK1;
                    break;
                case MOD_MODE_PSK2:
                    tmp= Q5_MOD_PSK2;
                    break;
                case MOD_MODE_PSK3:
                    tmp= Q5_MOD_PSK3;
                    break;
                default:
                    return FALSE;
            }
    }
    value= SET_CONFIG(value, Q5_MASK_MODULATION, Q5_SHIFT_MODULATION, tmp);

    // data blocks
    value= SET_CONFIG(value, Q5_MASK_MAX_BLOCK, Q5_SHIFT_MAX_BLOCK, RFIDlerConfig.DataBits / Q5_BLOCKSIZE);

    ulongtohex(config, value);

    return TRUE;
}

// set a config block suitable for emulating
BOOL q5_emulate_config_block(BYTE *config, BYTE target_tagtype)
{
    switch (target_tagtype)
    {
       case TAG_TYPE_ASK_RAW:
       case TAG_TYPE_FSK1_RAW:
       case TAG_TYPE_FSK2_RAW:
       case TAG_TYPE_PSK1_RAW:
       case TAG_TYPE_PSK2_RAW:
       case TAG_TYPE_PSK3_RAW:
           memcpy(config, Q5_DEFAULT_CONFIG_BLOCK, HEXDIGITS(Q5_BLOCKSIZE));
           q5_create_config_block(config);
           return TRUE;

       case TAG_TYPE_AWID_26:
       case TAG_TYPE_HID_26:
            memcpy(config, Q5_HID_26_CONFIG_BLOCK, HEXDIGITS(Q5_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_FDXB:
            memcpy(config, Q5_FDXB_CONFIG_BLOCK, HEXDIGITS(Q5_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_INDALA_64:
            memcpy(config, Q5_INDALA_64_CONFIG_BLOCK, HEXDIGITS(Q5_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_INDALA_224:
            memcpy(config, Q5_INDALA_224_CONFIG_BLOCK, HEXDIGITS(Q5_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_EM4X02:
        case TAG_TYPE_Q5:
        case TAG_TYPE_UNIQUE:
            memcpy(config, Q5_DEFAULT_CONFIG_BLOCK, HEXDIGITS(Q5_BLOCKSIZE));
            return TRUE;

        default:
            return FALSE;
    }
}

// decode externally sniffed PWM
BOOL q5_decode_pwm(unsigned long pulses[], unsigned long gaps[], unsigned int count)
{
    unsigned int    i, j;
    BOOL            decoded= FALSE;
    BYTE            out[65]; // max response from hitag2 is 64 bits
    
    j= 0;
    while(j < count)
    {
        i= generic_decode_pwm(out, &pulses[j], 10, 512, &gaps[j], 20, 500, count - j);
        if(i)
        {
            decoded= TRUE;
            UserMessage("\r\n%s", out);
            j += i;
        }
        else
            break;
    }
    
    UserMessage("%s", "\r\n");
    
    return decoded;
}

