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

// We want the crypto functions to be as fast as possible, so optimize!
// The best compiler optimization in Microchip's free XC32 edition is -O1
#pragma GCC optimize("O1")

#include "HardwareProfile.h"
#include "ask.h"
#include "comms.h"
#include "config.h"
#include "hitagcrypto.h"
#include "hitag.h"
#include "rfidler.h"
#include "rwd.h"
#include "sniff.h"
#include "util.h"

// sync/ack checking
const BYTE Hitag2Sync[5]= {0x01, 0x01, 0x01, 0x01, 0x01};
const BYTE Hitag1ACK[3]= {0x01, 0x00, 0x01};

const BYTE *Hitag2_Modes[]= {"Public Mode B", "Public Mode A", "Public Mode C", "Hitag2"};

// crypto globals
Hitag_State Hitag_Crypto_State;
BOOL CryptoActive= FALSE;

// crypto hints:
//
// when running hitag2 in crypto mode, bear in mind that both the reader and the tag must maintain the same crypto
// stream. this means that every crypto operation on either side must be mirrored on the other side in order to
// keep the streams synchronised. essentially, this means that every encrypted packet received from the tag must
// be decrypted, even if you don't plan to use the data, and everything must be done in real-time order - i.e. you
// cannot pre-encrypt to save time if that changes the order that bits are encrypted in.
//
// after authentication, everything is encrypted on the reader side, including commands. the tag only encrypts the data,
// not the 5 sync bits.

BOOL hitag1_get_uid(BYTE *response)
{
    BYTE tmp[132]; // 33 bits x 4

    rwd_send(HITAG1_SET_CC, strlen(HITAG1_SET_CC), RESET, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, RFIDlerConfig.RWD_Sleep_Period, RFIDlerConfig.RWD_Wake_Period, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX);
     // get tag id in anti-collision mode (proprietary data format, so switch off manchester and read at double the data rate, for 4 x the data bits)
    RFIDlerConfig.Manchester= FALSE;
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate / 2, tmp, RFIDlerConfig.DataBits * 4, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == RFIDlerConfig.DataBits * 4)
    {
        if (hitag_ac_to_bin(tmp, tmp, 132))
        {
            // check sync bit
            if(tmp[0] != 0x01)
               return FALSE;
            binarraytohex(response, tmp + 1, 32);
            RFIDlerConfig.Manchester= TRUE;
            // delay for RX->TX period
            Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wait_Switch_RX_TX) / 100);
            return TRUE;
        }
    }
    RFIDlerConfig.Manchester= TRUE;
    
    return FALSE;
}

// return interpreted UID
BOOL hitag1_hex_to_uid(BYTE *response, BYTE *hex)
{
    strcpy(response, hex);
    return TRUE;
}

// select HITAG1 for read/write operations - return config page
BOOL hitag1_select(BYTE *response, BYTE *uid)
{
    BYTE command[38], tmp1[33]; // command: 5 bit command + 32 bit uid + NULL

    strcpy(command, HITAG1_SELECT);
    if(!hextobinstring(command + 5, uid))
        return FALSE;

    // send command and get back 1 sync bit + 32 bit configpage
    if(!hitag1_send_command(tmp1, command, NO_RESET, NO_SYNC, 33, NO_ACK))
        return FALSE;

    // check sync bit
    if(tmp1[0] == 0x01)
    {
        binarraytohex(response, tmp1 + 1, 32);
        return TRUE;
    }
    return FALSE;
}

// read page - 32 bits
// pages 2 - 15 are probably not readable!
BOOL hitag1_read_page(BYTE *response, BYTE block)
{
    BYTE tmp[HITAG1_BLOCKSIZE + 6]; // 32 bits plus 6 sync bits

    if(block > HITAG1_DATABLOCKS - 1)
        return FALSE;

    // get tag's UID for select command
    if(!hitag1_get_uid(tmp))
        return FALSE;

    // select for read/write
    hitag1_select(tmp, tmp);

    // create 12 bit command block: HITAG1_RDPPAGE + 8 bits address
    strcpy(tmp, HITAG1_RDPPAGE);
    inttobinstring(tmp + 4, (unsigned int) block, 8);
    tmp[12]= '\0';

    // ??? docs say 6 sync bits!
    if(!hitag1_send_command(tmp, tmp, NO_RESET, NO_SYNC, HITAG1_BLOCKSIZE + 1, NO_ACK))
        return FALSE;

    // check sync
    if(tmp[0] != 0x01)
        return FALSE;
    
    binarraytohex(response, tmp + 1, HITAG1_BLOCKSIZE);

    return TRUE;
}


BOOL hitag1_write_page(BYTE block, BYTE *data)
{
    BYTE crc, command[21], tmp[33], tmp1[4];

    if(block > HITAG1_DATABLOCKS - 1)
        return FALSE;

    // get tag's UID for select command
    if(!hitag1_get_uid(tmp))
        return FALSE;

    // select for read/write
    hitag1_select(tmp, tmp);

    // convert data to binstring for send
    if(hextobinstring(tmp, data) != 32)
        return FALSE;

    // create and send 12 bit command block: HITAG1_WRPPAGE (4 bits) + 8 bit address
    memcpy(command, HITAG1_WRPPAGE, 4);
    inttobinstring(command + 4, (unsigned int) block, 8);
    command[12]= '\0';
    if(!hitag1_send_command(tmp1, command, NO_RESET, NO_SYNC, 0, ACK))
        return FALSE;

    // delay to switch back to write mode
    Delay_us((RFIDlerConfig.RWD_Wait_Switch_RX_TX * RFIDlerConfig.FrameClock) / 100);

    // now send data
    if(!hitag1_send_command(tmp1, tmp, NO_RESET, NO_SYNC, 0, ACK))
        return FALSE;

    // read back and verify
    // delay for long enough to allow write plus RX->TX period
    Delay_us((HITAG1_WRITE_DELAY * RFIDlerConfig.FrameClock + RFIDlerConfig.RWD_Wait_Switch_RX_TX * RFIDlerConfig.FrameClock) / 100);
    if(!hitag1_read_page(tmp, block))
        return FALSE;

    if(memcmp(tmp, data, 8) != 0)
        return FALSE;

    return TRUE;
}

// calcuate CRC & send command - response in binarray
BOOL hitag1_send_command(BYTE *response, BYTE *command, BOOL reset, BOOL sync, BYTE response_length, BOOL ack)
{
    BYTE crc= HITAG1_CRC_PRESET, tmp[HITAG1_MAX_COMMAND_LEN], length; // supplied command is 4 bits + 8 bit address. we add 8 bit CRC
    
    // calculate crc
    length= binstringtobinarray(tmp, command);
    hitag1_binarray_crc(&crc, tmp, length);

    // add 8 bit crc to command
    inttobinarray(tmp + length, (unsigned int) crc, 8);
    length += 8;

    // send command - first gap is GAP, not SLEEP
    if(!rwd_send(tmp, length, reset, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wake_Period, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    // get/check 3 bit ACK if required
    if(ack)
    {
        // sync manchester
        HW_Skip_Bits= 1;
        if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, 3, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == 3)
        {
            if (memcmp(tmp, Hitag1ACK , 3) != 0)
                return FALSE;
        }
        else
            return FALSE;
    }

    if(!response_length)
        return TRUE;

    // read response as binary data
    
    // sync manchester
    HW_Skip_Bits= 1;
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, response, response_length, RFIDlerConfig.Sync, sync ? RFIDlerConfig.SyncBits : 0, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == response_length)
    {
        // delay for RX->TX time
        Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wait_Switch_RX_TX) / 100);
        return TRUE;
    }

    return FALSE;
}

// update hitag1 crc for arbitrary binarray length
void hitag1_binarray_crc(BYTE *crc, BYTE *bin, BYTE length)
{
    BYTE i;

    for(i= 0 ; i < length ; i += 8)
        if(length - i < 8)
            hitag1_crc(crc, (BYTE) binarraytoint(bin + i, length - i) << 8 - (length - i), length - i);
        else
           hitag1_crc(crc, (BYTE) binarraytoint(bin + i, 8), 8);
}

// update hitag1 crc from a single byte, limit to specified number of bits
void hitag1_crc(BYTE *crc, BYTE data, BYTE bits)
{
    *crc ^= data;

    while(bits--)
    {
        if( *crc & 0x80 )
        {
            *crc <<= 1;
            *crc ^= HITAG1_CRC_POLYNOM;
        }
        else
            *crc <<= 1;
    }
}

// decode externally sniffed PWM
BOOL hitag1_decode_pwm(unsigned int pulses[], unsigned int gaps[], unsigned int count)
{
    unsigned int    i, j;
    BOOL            decoded= FALSE;
    BYTE            out[46], tmp[9], x; // max command from hitag1 is 5 bit command plus 32 bits + 8 bit crc == 45
    
    j= 0;
    while(j < count)
    {
        i= generic_decode_pwm(out, &pulses[j], 10, 256, &gaps[j], 10, 80, count - j);
        if(i)
        {
            // there are only 5 message sizes, so decode accordingly
            switch(strlen(out))
            {
                // halt
                case 4:
                    if(memcmp(out, HITAG1_HALT, 4) == 0)
                        UserMessage("\r\n%s, HALT", out);
                    else
                        UserMessage("\r\n%s, ?INVALID?", out); 
                    break;
                     
                // get UID
                case 5:
                    if(memcmp(out, HITAG1_SET_CC, 5) == 0)
                        UserMessage("\r\n%s, SET_CC", out);
                        else
                            UserMessage("\r\n%s, ?INVALID?", out); 
                    break;
                    
               // read/write
                case 20:
                    if(memcmp(out, HITAG1_RDPPAGE, 4) == 0)
                        UserMessage("\r\n%s, READ_PLAINTEXT_PAGE:", out);
                        else
                            if(memcmp(out, HITAG1_WRPPAGE, 4) == 0)
                                UserMessage("\r\n%s, WRITE_PLAINTEXT_PAGE:", out);
                            else
                            {
                            UserMessage("\r\n%s, ?INVALID?", out);
                            break;
                            }
                    out[20]= '\0';
                    binstringtohex(tmp, out + 4);
                    // page
                    UserMessage("%.2s:", tmp);
                    // crc
                    UserMessage("%s", tmp + 2);
                    break;
                    
                // data
                case 40:
                    UserMessage("\r\n%s, DATA:", out);
                    out[40]= '\0';
                    binstringtohex(tmp, out);
                    // DATA
                    UserMessage("%.8s:", tmp);
                    // CRC
                    UserMessage("%s", tmp + 8);
                    break;
                    
                // select
                case 45:
                    if(memcmp(out, HITAG1_SELECT, 5) == 0)
                    {
                        UserMessage("\r\n%s, SELECT:", out);
                        out[45]= '\0';
                        binstringtohex(tmp, out + 5);
                        // UID
                        UserMessage("%.8s:", tmp);
                        // CRC
                        UserMessage("%s", tmp + 8);
                    }
                    else
                        UserMessage("\r\n%s, ?INVALID?", out);
                    break;
 
                default:
                    UserMessage("\r\n%s,?INVALID?", out);
            }
            decoded= TRUE;
            j += i;
        }
        else
            break;
    }
    
    UserMessage("%s", "\r\n");
    
    return decoded;
}

// hitag2 

BOOL hitag2_get_uid(BYTE *response)
{
    BYTE tmp[37];

    // START_AUTH kills active crypto session
    CryptoActive= FALSE;

    if(!rwd_send(HITAG2_START_AUTH, strlen(HITAG2_START_AUTH), RESET, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, RFIDlerConfig.RWD_Sleep_Period, RFIDlerConfig.RWD_Wake_Period, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;
    
    // skip 1/2 bit to synchronise manchester
    HW_Skip_Bits= 1;
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, RFIDlerConfig.DataBits, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == RFIDlerConfig.DataBits)
    {
        // check sync bits
        if (memcmp(tmp, Hitag2Sync, 5) != 0)
            return FALSE;
        binarraytohex(response, tmp + 5, 32);
        return TRUE;
    }
    return FALSE;
}

// return interpreted UID
BOOL hitag2_hex_to_uid(BYTE *response, BYTE *hex)
{
    strcpy(response, hex);
    return TRUE;
}

// auth in password mode
BOOL hitag2_pwd_auth(BYTE *response, BYTE *pwd)
{
    BYTE tmp[37];

    // restart the tag
    if(!hitag2_get_uid(tmp))
        return FALSE;

    if(strlen(pwd) == 0)
        pwd= HITAG2_PWD_DEFAULT;

    // use default transport key if none specified
    if(!hextobinstring(tmp, pwd))
        return FALSE;

    // wait for RX->TX period, then send 32 bit PWD
    if(!rwd_send(tmp, strlen(tmp), NO_RESET, BLOCK, RWD_STATE_WAKING, RFIDlerConfig.FrameClock, 0, RFIDlerConfig.RWD_Wait_Switch_RX_TX, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;
    
    // skip 1/2 bit to synchronise manchester
    HW_Skip_Bits= 1;
    // get 37 bit response: sync + config byte + 24 bit TAG pwd
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, 37, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == 37)
    {
        // check sync bits
        if (memcmp(tmp, Hitag2Sync, 5) != 0)
            return FALSE;
        binarraytohex(response, tmp + 5, 32);
        return TRUE;
    }
    return FALSE;
}

// note that PRN is not created with security in mind - just using a simple seed
BOOL hitag2_crypto_auth(BYTE *response, BYTE *hexkey)
{
    BYTE tmp[65], tmphex[9];
    unsigned long long key;
    unsigned long uid;
    unsigned long initvec;

    // use default transport key if none specified
    if(strlen(hexkey) == 0)
        hexkey= HITAG2_KEY_DEFAULT;

    // get UID for initialisation
    if(!hitag2_get_uid(tmp))
        return FALSE;
    
    // convert to numerics for crypto routines
    uid= hexreversetoulong(tmp);
    key= hexreversetoulonglong(hexkey);

    // generate 32 bit PRN for challenge
    srand(Led_Count);
    initvec= rand();
    initvec <<= 16;
    initvec += rand();

    // prepare to send IV in the clear to tag
    ulongtobinstring(tmp, initvec, 32);

    // convert IV to MSB for crypto routines
    binstringtohex(tmphex, tmp);
    initvec= hexreversetoulong(tmphex);

    // initialise  crypto
    hitag2_init(&Hitag_Crypto_State, rev64(key), rev32(uid), rev32(initvec));

    // send inverse of 1st 32bits of keystream to tag for authentication
    ulongtobinstring(tmp + 32, hitag2_crypt(0xFFFFFFFF, 32), 32);

    // restart the tag & auth process
    if(!hitag2_get_uid(TmpBuff))
        return FALSE;

    // wait for RX->TX period, then send PRN+secret
    if(!rwd_send(tmp, strlen(tmp), NO_RESET, BLOCK, RWD_STATE_WAKING, RFIDlerConfig.FrameClock, 0, RFIDlerConfig.RWD_Wait_Switch_RX_TX, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    // skip 1/2 bit to synchronise manchester
    HW_Skip_Bits= 1;
    // get 37 bit response: sync + config byte + 24 bit TAG pwd
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, 37, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == 37)
    {
        // check sync bits
        if (memcmp(tmp, Hitag2Sync, 5) != 0)
            return FALSE;
        CryptoActive= TRUE;

        // decrypt
        binarraytohex(response, tmp + 5, 32);
        return hitag2_hex_crypt(response, response);
    }
    return FALSE;
}

BOOL hitag2_read_page(BYTE *response, BYTE block)
{
    BYTE tmp[37];

    if(block > HITAG2_DATABLOCKS - 1)
        return FALSE;

    // create 10 bit command block: HITAG2_READ_PAGE + 3 bits address + invert(HITAG2_READ_PAGE + 3 bits address)
    memcpy(tmp, HITAG2_READ_PAGE, 2);
    inttobinstring(tmp + 2, (unsigned int) block, 3);
    invertbinstring(tmp + 5, tmp);
    tmp[10]= '\0';

    // encrypt command if in crypto mode
    if(CryptoActive)
        hitag2_binstring_crypt(tmp, tmp);

    // send with RX->TX delay and no reset
    if(!rwd_send(tmp, strlen(tmp), NO_RESET, BLOCK, RWD_STATE_WAKING, RFIDlerConfig.FrameClock, 0, RFIDlerConfig.RWD_Wait_Switch_RX_TX, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    // skip 1/2 bit to synchronise manchester
    HW_Skip_Bits= 1;
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, 37, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == 37)
    {
        // check sync bits
        if (memcmp(tmp, Hitag2Sync, 5) != 0)
            return FALSE;
        binarraytohex(response, tmp + 5, 32);

        // decrypt
        if(CryptoActive)
            return hitag2_hex_crypt(response, response);

        return TRUE;
    }
    return FALSE;
}

BOOL hitag2_write_page(BYTE block, BYTE *data)
{
    BYTE command[11], tmp[37], tmp1[37], tmp2[37], tmphex[9];

    if(block > HITAG2_DATABLOCKS - 1)
        return FALSE;

    // create 10 bit command block: HITAG2_WRIE_PAGE + 3 bits address + invert(HITAG2_WRITE_PAGE + 3 bits address)
    memcpy(command, HITAG2_WRITE_PAGE, 2);
    inttobinstring(command + 2, (unsigned int) block, 3);
    invertbinstring(command + 5, command);
    command[10]= '\0';

    // encrypt command if in crypto mode
    if(CryptoActive)
        hitag2_binstring_crypt(tmp, command);
    else
        memcpy(tmp, command, 11);

    // convert data to binstring for send
    if(hextobinstring(tmp1, data) != 32)
        return FALSE;

    // send command with RX->TX delay and no reset
    if(!rwd_send(tmp, strlen(tmp), NO_RESET, BLOCK, RWD_STATE_WAKING, RFIDlerConfig.FrameClock, 0, RFIDlerConfig.RWD_Wait_Switch_RX_TX, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    // skip 1/2 bit to synchronise manchester
    HW_Skip_Bits= 1;
    // get ACK - 10 bytes + sync
    if(read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp2, 15, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY) == 15)
    {
        // check sync bits
        if (memcmp(tmp2, Hitag2Sync, 5) != 0)
            return FALSE;

        // decrypt
        if(CryptoActive)
            hitag2_binarray_crypt(tmp2 + 5, tmp2 + 5, 10);

        // check ACK - should be our original command echo'd back
        binarraytobinstring(tmp2 + 5, tmp2 + 5, 10);
        if(memcmp(command, tmp2 + 5, 10) != 0)
            return FALSE;
    }

    // encrypt data if in crypto mode
    if(CryptoActive)
        hitag2_binstring_crypt(tmp1, tmp1);

    // send data with RX->TX delay and no reset
    if(!rwd_send(tmp1, strlen(tmp1), NO_RESET, BLOCK, RWD_STATE_WAKING, RFIDlerConfig.FrameClock, 0, RFIDlerConfig.RWD_Wait_Switch_RX_TX, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
        return FALSE;

    // no ack, so read back and verify
    // delay for long enough to allow write plus RX->TX period
    Delay_us((HITAG2_WRITE_DELAY * RFIDlerConfig.FrameClock + RFIDlerConfig.RWD_Wait_Switch_RX_TX * RFIDlerConfig.FrameClock) / 100);
    if(!hitag2_read_page(tmp, block))
        return FALSE;
    if(memcmp(tmp, data, 8) != 0)
        return FALSE;

    return TRUE;
}

// attempt to find ideal parameters for GAP, ZERO and ONE periods.
// ranges specified in FC
void hitag2_test_rwd(unsigned int gapmin, unsigned int gapmax, unsigned int zeromin, unsigned int zeromax, unsigned int onemin, unsigned int onemax, BYTE *pass)
{
    BYTE i, imax, countu, counta, countr;
    unsigned int gap, zero, one, fc;

    imax= 5;

    for(fc= 800 ; fc <= 809 ; ++fc)
    {
        for(gap= gapmin ; gap <= gapmax ; ++gap)
            for(zero= zeromin ; zero <= zeromax ; ++zero)
                for(one= onemin ; one <= onemax ; ++one)
                {
                    RFIDlerConfig.FrameClock= (unsigned long) fc;
                    RFIDlerConfig.RWD_Gap_Period= gap;
                    RFIDlerConfig.RWD_Zero_Period= zero;
                    RFIDlerConfig.RWD_One_Period= one;
                    UserMessageNum("\rGap %d", gap);
                    UserMessageNum(" Zero %d", zero);
                    UserMessageNum(" One %d", one);
                    UserMessageNum(" FC %d", fc);
                    for(i= countu= counta= countr= 0 ; i < imax ; ++i)
                    {
                        if(get_user_abort())
                            return;
                        if(hitag2_get_uid(DataBuff))
                        {
                            ++countu;
                            if(hitag2_pwd_auth(DataBuff, pass) || hitag2_crypto_auth(DataBuff, pass))
                            {
                                ++counta;
                                if(hitag2_read_page(DataBuff, 0))
                                    ++countr;
                            }
                        }
                    }
                    if(countu == imax && counta == imax && countr == imax)
                    {
                        UserMessageNum(" - got %d", countu);
                        UserMessageNum(" uids, %d", counta);
                        UserMessageNum(" auths %d", countr);
                        UserMessageNum(" reads, out of %d attempts.\r\n", imax);
                    }
                }
        UserMessage("%s", "\r\n");
    }
}

// decrypt hex - safe to do in place
BOOL hitag2_hex_crypt(BYTE *target, BYTE *source)
{
    BYTE cryptogram, tmp[3];
    unsigned int length;

    length= strlen(source);

    while(length)
    {
        if(sscanf(source, "%2X", &cryptogram) != 1)
            return FALSE;
        sprintf(tmp, "%02X", hitag2_crypt(cryptogram, 8));
        memcpy(target, tmp, 2);
        source += 2;
        target += 2;
        length -= 2;
    }
    return TRUE;
}

// encrypt a binstring - safe to do in place
void hitag2_binstring_crypt(BYTE *target, BYTE *source)
{
    BYTE cryptogram;
    unsigned int length;

    length= strlen(source);
    while(length)
    {
        cryptogram= *(source++) - '0';
        *(target++)= (BYTE) hitag2_crypt(cryptogram, 1) + '0';
        --length;
    }
    *target= '\0';
}

// encrypt a binarray - safe to do in place
void hitag2_binarray_crypt(BYTE *target, BYTE *source, unsigned int length)
{
    while(length)
    {
        *(target++)= (BYTE) hitag2_crypt(*(source++), 1);
        --length;
    }
}

// crypt with current keystream, length in bits
unsigned long hitag2_crypt(unsigned long source, BYTE length)
{
    return source ^ hitag2_nstep(&Hitag_Crypto_State, length);
}

// convert hitag 'anticollision mode' data to standard binary
// safe to do in-place as target is shorter
unsigned int hitag_ac_to_bin(BYTE *target, BYTE *source, unsigned int length)
{
    unsigned int i;
    BYTE zero[]= {1,1,0,0};
    BYTE one[]= {1,0,1,0};

    for(i= 0 ; i < length ; i += 4, source, ++target)
    {
        if(memcmp(source + i, one, 4) == 0)
            *target= 0x01;
        else
            if(memcmp(source + i, zero, 4) == 0)
                *target= 0x00;
            else
                return 0;
    }
    return HEXDIGITS(length);
}

// set a config block suitable for emulating
BOOL hitag2_emulate_config_block(BYTE *config, BYTE target_tagtype)
{
    switch (target_tagtype)
    {
        case TAG_TYPE_FDXB:
            memcpy(config, HITAG2_FDXB_CONFIG_BLOCK, HEXDIGITS(HITAG2_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_EM4X02:
        case TAG_TYPE_Q5:
        case TAG_TYPE_UNIQUE:
            memcpy(config, HITAG2_UNIQUE_CONFIG_BLOCK, HEXDIGITS(HITAG2_BLOCKSIZE));
            return TRUE;

        case TAG_TYPE_HITAG2:
            memcpy(config, HITAG2_DEFAULT_CONFIG_BLOCK, HEXDIGITS(HITAG2_BLOCKSIZE));
            return TRUE;

        default:
            return FALSE;
    }
}

// decode externally sniffed PWM
BOOL hitag2_decode_pwm(unsigned int pulses[], unsigned int gaps[], unsigned int count)
{
    unsigned int    i, j;
    BOOL            decoded= FALSE, encrypted= FALSE, auth= FALSE;
    BYTE            out[65], tmp[33], x; // max response from hitag2 is 64 bits
    
    j= 0;
    while(j < count)
    {
        i= generic_decode_pwm(out, &pulses[j], 10, 256, &gaps[j], 10, 80, count - j);
        if(i)
        {
            // there are only 4 message sizes, so decode accordingly
            switch(strlen(out))
            {
                // start_auth
                case 5:
                    auth= FALSE;
                    if(memcmp(out, HITAG2_START_AUTH, 5) == 0)
                    {
                        UserMessage("\r\n%s, START_AUTH", out);
                        auth= TRUE;
                    }
                    else
                        UserMessage("\r\n%s, ?INVALID?", out); 
                    encrypted= FALSE; 
                    break;
                    
                // read/write/halt
                case 10:
                    auth= FALSE;
                    if(encrypted)
                    {
                        UserMessage("\r\n%s, CMD_ENCRYPTED", out);
                        break;
                    }
                    if(memcmp(out, HITAG2_HALT, 2) == 0)
                    {
                        UserMessage("\r\n%s, HALT", out);
                        break;
                    }
                    if(memcmp(out, HITAG2_READ_PAGE, 2) == 0)
                        UserMessage("\r\n%s, READ_PAGE:", out);
                    if(memcmp(out, HITAG2_READ_PAGE_INVERTED, 2) == 0)
                        UserMessage("\r\n%s, READ_PAGE_INVERTED:", out);
                    if(memcmp(out, HITAG2_WRITE_PAGE, 2) == 0)
                        UserMessage("\r\n%s, WRITE_PAGE:", out);
                    binstringtobyte(&x, &out[2], 3);
                    UserMessageNum("%d", x);
                    break;
                
                // password or data
                case 32:
                    if(auth)
                        UserMessage("\r\n%s, PWD:", out);
                    else
                        UserMessage("\r\n%s, DATA:", out);
                    binstringtohex(out, out);
                    UserMessage("%s", out);
                    auth= FALSE;
                    break;
                 
                // crypto handshake
                case 64:
                    UserMessage("\r\n%s, PRN:", out);
                    memcpy(tmp, out, 32);
                    tmp[32]= '\0';
                    binstringtohex(out, tmp);
                    UserMessage("%s: SECRET:", out);
                    binstringtohex(out, out + 32);
                    UserMessage("%s", out);
                    encrypted= TRUE;
                    auth= FALSE;
                    break;
                    
                default:
                    UserMessage("\r\n%s,?INVALID?", out);
            }
            decoded= TRUE;
            j += i;
        }
        else
            break;
    }
    
    UserMessage("%s", "\r\n");
    
    return decoded;
}

BOOL hitag2_config_block_show(BYTE *config, BYTE *password, BYTE *key)
{
    BYTE    value= hextobyte(config); // first byte only used as config

    UserMessage("     PWD Block (1): %.8s    ", password);
    printhexreadable(password, 4);
    
    UserMessage("\r\n\r\n     Key Block (2): %.8s    ", key);
    printhexreadable(key, 4);
    
    UserMessage("\r\n\r\n  Config Block (3): %.8s\r\n\r\n", config);
    UserMessageNum("        Page 1 & 2: %d = ", GET_CONFIG(value, HITAG2_MASK_PAGE_1_2_OTP_PROTECT, HITAG2_SHIFT_PAGE_1_2_OTP_PROTECT));
    if(GET_CONFIG(value, HITAG2_MASK_SECURITY, HITAG2_SHIFT_SECURITY))
        UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_PAGE_1_2_OTP_PROTECT, HITAG2_SHIFT_PAGE_1_2_OTP_PROTECT) ? "No Read / No Write" : "Read / Write");
    else
        UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_PAGE_1_2_OTP_PROTECT, HITAG2_SHIFT_PAGE_1_2_OTP_PROTECT) ? "Page 1: No Read / No Write, Page 2: Read Only" : "Read / Write");
    UserMessageNum("            Page 3: %d = ", GET_CONFIG(value, HITAG2_MASK_PAGE_3_OTP_PROTECT, HITAG2_SHIFT_PAGE_3_OTP_PROTECT));
    UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_PAGE_3_OTP_PROTECT, HITAG2_SHIFT_PAGE_3_OTP_PROTECT) ? "Read Only" : "Read / Write");
    UserMessageNum("        Page 4 & 5: %d = ", GET_CONFIG(value, HITAG2_MASK_PAGE_4_5_PROTECT, HITAG2_SHIFT_PAGE_4_5_PROTECT));
    UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_PAGE_4_5_PROTECT, HITAG2_SHIFT_PAGE_4_5_PROTECT) ? "Read Only" : "Read / Write");
    UserMessageNum("        Page 6 & 7: %d = ", GET_CONFIG(value, HITAG2_MASK_PAGE_6_7_PROTECT, HITAG2_SHIFT_PAGE_6_7_PROTECT));
    UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_PAGE_6_7_PROTECT, HITAG2_SHIFT_PAGE_6_7_PROTECT) ? "Read Only" : "Read / Write");
    UserMessageNum("          Security: %d = ", GET_CONFIG(value, HITAG2_MASK_SECURITY, HITAG2_SHIFT_SECURITY));
    UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_SECURITY, HITAG2_SHIFT_SECURITY) ? "Crypto" : "Password");
    UserMessageNum("              Mode: %d = ", GET_CONFIG(value, HITAG2_MASK_MODE, HITAG2_SHIFT_MODE));
    UserMessage("%s\r\n", (BYTE *) Hitag2_Modes[GET_CONFIG(value, HITAG2_MASK_MODE, HITAG2_SHIFT_MODE)]);
    UserMessageNum("        Modulation: %d = ", GET_CONFIG(value, HITAG2_MASK_MODULATION, HITAG2_SHIFT_MODULATION));
    UserMessage("%s\r\n", GET_CONFIG(value, HITAG2_MASK_MODULATION, HITAG2_SHIFT_MODULATION) ? "BiPhase" : "Manchester");

    UserMessage("\r\n     PWD Block (3): %.6s      ", config + 2);
    printhexreadable(config + 2, 3);
    UserMessage("%s", "\r\n");
    return TRUE;
}

// end optimisation
#pragma GCC reset_options
