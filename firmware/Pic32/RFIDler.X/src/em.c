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
 * RFIDler is (C) 2013-2015 Aperture Labs Ltd.                             *
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
#include "ask.h"
#include "clock.h"
#include "config.h"
#include "em.h"
#include "util.h"

// em4205 return values
const BYTE EM4X05_Preamble[8]=  {0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00};   // "00001010"
const BYTE EM4X05_Error[8]= {0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x01};       // "00000001"
const BYTE *EM4X05_Delays[4]= {"No Delay", "BP/4 (RF/16)", "BP/8 (RF/8)", "No Delay"};
const BYTE *EM4X05_Capacitors[4]= {"Invalid", "210pF", "250pF", "330pF"};
// support routines for EM tags
//

BOOL em4x02_get_uid(BYTE *response)
{
     return ask_raw_get_uid(response);
}

BOOL em4x02_hex_to_uid(BYTE *response, BYTE *hex)
{
    BYTE tmp[40];

    if(em4x02_hex_to_bin(tmp, hex))
        return binarraytohex(response, tmp, 40);
    return FALSE;
}

// convert null-terminated hex UID (10 digits) to em4x02 encoded hex
BOOL hex_to_em4x02_hex(unsigned char *em, unsigned char *hex)
{
    if(hex_to_em4x02_bin(em, hex))
        return binarraytohex(em, em, 64);
    else
        return FALSE;
}

// convert null-terminated hex UID (10 digits) to 64 bit em4x02 encoded binary array
BOOL hex_to_em4x02_bin(unsigned char *em, unsigned char *hex)
{
    unsigned char tmp1[10], tmp2[40];

    if(strlen(hex) > 10)
        return FALSE;

    // pad to 10 hex digits
    memset(tmp1, '0', 10);
    memcpy(tmp1 + 10 - strlen(hex), hex, strlen(hex));
    hextobinarray(tmp2, tmp1);
    // encoding is the same as unique, but source data is in a different order
    bin_to_em4x02_bin(em, tmp2);
    return TRUE;
}

// convert 16 hex digit/64 bit EM4X02 ID to 40 bit raw UID
// safe to do in-place as we use a scratchpad
BOOL em4x02_hex_to_bin(unsigned char *bin, unsigned char *em)
{
    unsigned char i, j, colparity[4]= {0,0,0,0};

    if(!hextobinarray(TmpBits, em))
        return FALSE;
    
    // check header
    for(i= 0 ; i < 9 ; ++i)
        if(TmpBits[i] != 0x01)
            return FALSE;

    // skip 9 bit header and strip/check parity bits - every 5th bit
    for(i= 0 ; i < 10 ; ++i)
    {
        memcpy(bin + i * 4, (TmpBits + 9) + i * 5, 4);
        if(parity(bin + i * 4, EVEN, 4) != TmpBits[9 + i * 5 + 4])
            return FALSE;
    }

    // check column parity
    for(i= 0 ; i < 10 ; ++i)
        for(j= 0; j < 4 ; ++j)
            colparity[j] += bin[i * 4 + j];
    for(i= 0 ; i < 4 ; ++i)
        if(colparity[i] % 2 != TmpBits[9 + 50 + i])
            return FALSE;

    // check terminating stop bit
    if(TmpBits[63] != 0x00)
        return FALSE;

    return TRUE;
}

// convert 40 bit ID (array of 1 byte per bit 0/1 values) to em 64 bit ID
void bin_to_em4x02_bin(unsigned char *em, unsigned char *bin)
{
    unsigned char i, j, parity, colparity[4]= {0,0,0,0};

    // output header '111111111'
    memset(em, 0x01, 9);
    em += 9;

    //  output 10 blocks of 4 bits plus parity for each block
    for(i= 0 ; i < 10 ; ++i, ++em)
    {
        for(j= parity= 0 ; j < 4 ; ++j, ++bin, ++em)
        {
            *em= *bin;
            parity += *bin;
            // calculate column parity for later
            colparity[j] += *bin;
        }
        // output parity
        *em= parity % 2;
    }

    // output column parity
    for(i= 0 ; i < 4 ; ++i, ++em)
        *em= colparity[i] % 2;

    // output stop bit
    *em= 0x00;
}

// em4x05 - comms as per em4469

// em4x05 doesn't use PWM for reader->tag comms, so hard code it
BOOL em4x05_send_command(BYTE *command, char address, BOOL send_data, unsigned long data, BOOL get_response, BYTE *response, unsigned int write_delay)
{
    // 5 bit command + 6 bit address + parity + null = 13
    // return value 8 bit PREAMBLE + 45 bit OTA + null = 54
    // max command is 5 + 6 + 1 + 45 + 1 = 58
    BYTE tmp[58], tmp2[33], *p, rlen;

    // create command buffer
    strcpy(tmp, command);

    if(address != NO_ADDRESS)
    {
        // convert address to 4 bit binary array
        inttobinarray(tmp2, (unsigned int) address, 4);
        // convert to LSB
        string_reverse(tmp2, 4);
        // add reserved two bits
        tmp2[4]= 0x00;
        tmp2[5]= 0x00;
        // add parity
        tmp2[6]= parity(tmp2, EVEN, 6);
        // add to command string
        binarraytobinstring(tmp + strlen(command), tmp2, 7);
    }

    if(send_data)
    {
        // convert data to 32 bit array
        ulongtobinarray(tmp2, data, 32);
        // convert to LSB
        string_reverse(tmp2, 32);
        // add to command string
        rlen= strlen(tmp);
        bin_to_em4x05_ota(tmp + rlen, tmp2);
        // convert to human readable
        binarraytobinstring(tmp + rlen, tmp + rlen, 45);
    }

    // debug
//    UserMessage("\r\nsending: %s\r\n", tmp);

    // start clock if not already running
    if(!mGetLED_Clock() == mLED_ON)
    {
        InitHWReaderClock(OC_TOGGLE_PULSE, RFIDlerConfig.FrameClock / 2L, RFIDlerConfig.FrameClock, RWD_STATE_ACTIVE);

        // give reader time to wake up and settle
        Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wake_Period) / 100L);
    }

    // send to tag
    if(!em4x05_forward_link(tmp))
        return FALSE;

    // return should be 8 bit PREAMBLE + 45 bit OTA formatted data
    if(get_response)
        rlen= 53;
    else
        rlen= 8;
    
    if(write_delay)
        Delay_us((write_delay * RFIDlerConfig.FrameClock + RFIDlerConfig.RWD_Wait_Switch_RX_TX * RFIDlerConfig.FrameClock) / 100);

    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, rlen, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == rlen)
    {
        // check preamble
        if(memcmp(tmp, EM4X05_Preamble, 8) != 0x00)
            return FALSE;
        // extract OTA data
        if(get_response)
            return em4x05_ota_to_hex(response, tmp + 8);
        else
            return TRUE;
    }
    return FALSE;
}

BOOL em4x05_forward_link(BYTE *data)
{
    // wait for a rising edge from TAG so we start talking while tag is modulating
    GetTimer_us(RESET);
    while(READER_DATA)
        if (GetTimer_us(NO_RESET) > RFIDlerConfig.Timeout)
            return FALSE;
    while(!READER_DATA)
        if (GetTimer_us(NO_RESET) > RFIDlerConfig.Timeout)
            return FALSE;

    // send First Field Stop
    pause_HW_clock_FC(RFIDlerConfig.RWD_Gap_Period, HIGH);
    
    // run clock for 1/2 bit period
    TimerWait_FC(RFIDlerConfig.RWD_Zero_Period);

    // send data
    // to send a 1, leave coil running for a full bit period
    // to send a 0, switch off for 1st half of bit period (after 4 FCs), back on for 2nd half
    while(*data)
    {
        if(*data == '1')
        {
            TimerWait_FC(RFIDlerConfig.RWD_One_Period);
        }
        else
        {
            TimerWait_FC(4);
            pause_HW_clock_FC(RFIDlerConfig.RWD_Zero_Period - 4, HIGH);
            TimerWait_FC(RFIDlerConfig.RWD_Zero_Period);
        }
        ++data;
    }

    TimerWait_FC(RFIDlerConfig.RWD_Wait_Switch_TX_RX);
}

BOOL em4x05_get_uid(BYTE *response)
{
    // UID is stored in block 1
    return em4x05_read_word(response, 1);
}

// shut down TAG until next power up
BOOL em4x05_disable(void)
{
    return em4x05_send_command(EM4X05_DISABLE, NO_ADDRESS, TRUE, 0xFFFFFFFFL, FALSE, NULL, 0);
}

BOOL em4x05_write_word(BYTE word, BYTE *data, BOOL verify)
{
    BOOL ret;
    BYTE tmp[33];
    
    ret= em4x05_send_command(EM4X05_WRITE_WORD, word, TRUE, hextoulong(data), FALSE, NULL, EM4X05_WRITE_DELAY);
    
    // we should be checking command sent ok, but when testing never saw a correct preamble being returned by the tag.
    // AN604010 also suggests that you simply ignore this, and read the block back instead which we always do to verify anyway
    // so let's go with that!
    //if(!ret)
    //    return FALSE;
    
    if(!verify)
        return TRUE;
    
    if(!em4x05_read_word(tmp, word))
        return FALSE;
    if(memcmp(tmp, data, 8) != 0)
        return FALSE;
    
    return TRUE;
}

BOOL em4x05_read_word(BYTE *response, BYTE word)
{
    // hard reset
    stop_HW_clock();

    // delay for sleep period
    Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Sleep_Period) / 100);

    return em4x05_send_command(EM4X05_READ_WORD, word, FALSE, 0L, TRUE, response, 0);
}

// convert 32 bit binary data to 45 bit EM4205 OTA format
// The 32 bit data field has an even parity bit inserted every 8 data bits, data is terminated with 8 column parity bits and a 0.
void bin_to_em4x05_ota(unsigned char *ota, unsigned char *bin)
{
    unsigned char i, j, parity, colparity[8]= {0,0,0,0,0,0,0,0};

    //  output 4 blocks of 8 bits plus parity for each block
    for(i= 0 ; i < 4 ; ++i, ++ota)
    {
        for(j= parity= 0 ; j < 8 ; ++j, ++bin, ++ota)
        {
            *ota= *bin;
            parity += *bin;
            // calculate column parity for later
            colparity[j] += *bin;
        }
        // output parity
        *ota= parity % 2;
    }

    // output column parity
    for(i= 0 ; i < 8 ; ++i, ++ota)
        *ota= colparity[i] % 2;

    //output stop bit
    *ota= 0x00;
}

// convert EM4205 OTA format to 32 bit hex 
BOOL em4x05_ota_to_hex(unsigned char *hex, unsigned char *ota)
{
    unsigned char i, j, colparity[8]= {0,0,0,0,0,0,0,0}, tmp[32];

    // strip/check parity bits - 4 blocks, every 9th bit
    for(i= 0 ; i < 4 ; ++i)
    {
        memcpy(tmp + i * 8, ota + i * 9, 8);
        if(parity(tmp + i * 8, EVEN, 8) != ota[i * 9 + 8])
            return FALSE;
    }

    // check column parity
    for(i= 0 ; i < 4 ; ++i)
        for(j= 0; j < 8 ; ++j)
            colparity[j] += tmp[i * 8 + j];
    for(i= 0 ; i < 8 ; ++i)
        if(colparity[i] % 2 != ota[36 + i])
            return FALSE;

    // check terminating stop bit
    if(ota[44] != 0x00)
        return FALSE;
    
    // data is sent from tag LSB, so reverse
    string_reverse(tmp, 32);
    binarraytohex(hex, tmp, 32);

    return TRUE;
}

BOOL em4x05_config_block_show(BYTE *config, BYTE *password, BYTE *info)
{
    uint32_t    value= hextoulong(info);
    
    UserMessage("         Info Block (0): %.8s\r\n\r\n", info);
    
    UserMessageNum("          Customer Code: 0x%03x\r\n", GET_CONFIG(value, EM4X05_MASK_CUSTOMER, EM4X05_SHIFT_CUSTOMER));
    UserMessageNum("              Capacitor: %d = ", GET_CONFIG(value, EM4X05_MASK_CAPACITOR, EM4X05_SHIFT_CAPACITOR));
    UserMessage("%s\r\n", EM4X05_Capacitors[GET_CONFIG(value, EM4X05_MASK_CAPACITOR, EM4X05_SHIFT_CAPACITOR)]);
    UserMessageNum("              Chip Type: %d = ", GET_CONFIG(value, EM4X05_MASK_CHIP, EM4X05_SHIFT_CHIP));
    if(GET_CONFIG(value, EM4X05_MASK_CHIP, EM4X05_SHIFT_CHIP) == CHIP_TYPE_EM4205)
        UserMessage("EM4205\r\n");
    else
        if(GET_CONFIG(value, EM4X05_MASK_CHIP, EM4X05_SHIFT_CHIP) == CHIP_TYPE_EM4305)
            UserMessage("EM4305\r\n");
        else
            UserMessage("Invalid\r\n");
        
    UserMessage("\r\n          PWD Block (2): %s\r\n\r\n", "Write Only");

    value= hextoulong(config);
    UserMessage("       Config Block (4): %.8s\r\n\r\n", config);
    
    UserMessage("            Pigeon Mode: %s\r\n", GET_CONFIG(value, EM4X05_MASK_PIGEON, EM4X05_SHIFT_PIGEON) ? "True" : "False");
    UserMessage("                    RTF: %s\r\n", GET_CONFIG(value, EM4X05_MASK_RTF, EM4X05_SHIFT_RTF) ? "True" : "False");
    UserMessage("                Disable: %s\r\n", GET_CONFIG(value, EM4X05_MASK_DISABLE, EM4X05_SHIFT_DISABLE) ? "True" : "False");
    UserMessage("            Write Login: %s\r\n", GET_CONFIG(value, EM4X05_MASK_WRITE_LOGIN, EM4X05_SHIFT_WRITE_LOGIN) ? "True" : "False");
    UserMessage("             Read Login: %s\r\n", GET_CONFIG(value, EM4X05_MASK_READ_LOGIN, EM4X05_SHIFT_READ_LOGIN) ? "True" : "False");
    UserMessageNum("                    LWR: %d\r\n", GET_CONFIG(value, EM4X05_MASK_LWR, EM4X05_SHIFT_LWR));
    UserMessage("             Delayed On: %d = ", GET_CONFIG(value, EM4X05_MASK_DELAYED_ON, EM4X05_SHIFT_DELAYED_ON));
    UserMessage("%s\r\n", EM4X05_Delays[GET_CONFIG(value, EM4X05_MASK_DELAYED_ON, EM4X05_SHIFT_DELAYED_ON)]);
    UserMessage("                Encoder: %d = ", GET_CONFIG(value, EM4X05_MASK_ENCODER, EM4X05_SHIFT_ENCODER));
    if(GET_CONFIG(value, EM4X05_MASK_ENCODER, EM4X05_SHIFT_ENCODER) == 0x01)
        UserMessage("%s\r\n", "Manchester");
    else
        if(GET_CONFIG(value, EM4X05_MASK_ENCODER, EM4X05_SHIFT_ENCODER) == 0x02)
            UserMessage("%s\r\n", "BiPhase");
        else
            UserMessage("%s\r\n", "Invalid");
    UserMessageNum("              Data Rate: %d = ", GET_CONFIG(value, EM4X05_MASK_DATA_RATE, EM4X05_SHIFT_DATA_RATE));
    UserMessageNum("RF/%d\r\n", GET_CONFIG(value, EM4X05_MASK_DATA_RATE, EM4X05_SHIFT_DATA_RATE) * 2 + 2);
    return TRUE;
}

// create a config block based on current tag settings
BOOL em4x05_create_config_block(BYTE *config)
{
    uint32_t    value= hextoulong(config);

    // data rate
    if(RFIDlerConfig.DataRate >= 8 && RFIDlerConfig.DataRate <= 64)
        value= SET_CONFIG(value, EM4X05_MASK_DATA_RATE, EM4X05_SHIFT_DATA_RATE, (RFIDlerConfig.DataRate - 2) / 2);
    else
        return FALSE;
    
    // modulation
    if(RFIDlerConfig.Manchester && RFIDlerConfig.Modulation == MOD_MODE_ASK_OOK)
        value= SET_CONFIG(value, EM4X05_MASK_ENCODER, EM4X05_SHIFT_ENCODER, EM4X05_MOD_MANCHESTER);
    else
    {
        if(RFIDlerConfig.BiPhase && RFIDlerConfig.Modulation == MOD_MODE_ASK_OOK)
            value= SET_CONFIG(value, EM4X05_MASK_ENCODER, EM4X05_SHIFT_ENCODER, EM4X05_MOD_BIPHASE);
        else
            return FALSE;
    }

    // data blocks
    if((RFIDlerConfig.DataBits / EM4X05_BLOCKSIZE + EM4X05_USER_DATA_BLOCK_NUM) > EM4X05_DATABLOCKS)
        return FALSE;
    value= SET_CONFIG(value, EM4X05_MASK_LWR, EM4X05_SHIFT_LWR, ((RFIDlerConfig.DataBits / EM4X05_BLOCKSIZE + EM4X05_USER_DATA_BLOCK_NUM - 1) & (EM4X05_MASK_LWR >> EM4X05_SHIFT_LWR)));

    ulongtohex(config, value);

    return TRUE;
}

// set a config block suitable for emulating
BOOL em4x05_emulate_config_block(BYTE *config, BYTE target_tagtype)
{
    switch (target_tagtype)
    {
       case TAG_TYPE_ASK_RAW:
           memcpy(config, EM4X05_DEFAULT_CONFIG_BLOCK, HEXDIGITS(EM4X05_BLOCKSIZE));
           return em4x05_create_config_block(config);
           
        case TAG_TYPE_EM4X02:
        case TAG_TYPE_Q5:
        case TAG_TYPE_UNIQUE:
            memcpy(config, EM4X05_UNIQUE_CONFIG_BLOCK, HEXDIGITS(EM4X05_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_EM4X05:
            memcpy(config, EM4X05_DEFAULT_CONFIG_BLOCK, HEXDIGITS(EM4X05_BLOCKSIZE));
            return TRUE;
            
        case TAG_TYPE_FDXB:
            memcpy(config, EM4X05_FDXB_CONFIG_BLOCK, HEXDIGITS(EM4X05_BLOCKSIZE));
            return TRUE;

        default:
            return FALSE;
    }
}
