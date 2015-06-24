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


// hitag1 commands
#define HITAG1_CC                   "00110"         // get UID when in Anti-Collision mode
#define HITAG1_SELECT               "00000"         // select tag for read/write
#define HITAG1_WRPPAGE              "1000"          // write page plaintext mode (page is 32 bits, number 0-63)
#define HITAG1_WRPBLK               "1001"          // write block plaintext mode (block is 4 pages)
#define HITAG1_WRCPAGE              "1010"          // write page crypto mode
#define HITAG1_WRCBLK               "1011"          // write block crypto mode
#define HITAG1_RDPPAGE              "1100"          // read page plaintext mode
#define HITAG1_RDPBLK               "1101"          // read block plaintext mode
#define HITAG1_RDCPAGE              "1110"          // read page crypto mode
#define HITAG1_RDCBLK               "1111"          // read block crypto mode
#define HITAG1_HALT                 "0111"          // halt selected tag

#define HITAG1_CRC_POLYNOM          0x1D
#define HITAG1_CRC_PRESET           0xFF

#define HITAG1_BLOCKSIZE            32              // read returns block sizes of 32, 64, 96 or 128 Bit, but we will only use 32
#define HITAG1_MAX_COMMAND_LEN      46              // longest command as binstring, plus NULL
#define HITAG1_DATABLOCKS           64              // total blocks
#define HITAG1_CONFIG_BLOCK_NUM     1               // config block
#define HITAG1_USER_DATA_BLOCK_NUM  4               // 1st user data block

#define HITAG1_WRITE_DELAY          726             // time to complete write in FCs

// hitag2 commands
#define HITAG2_START_AUTH           "11000"         // get UID and/or start the authentication process
#define HITAG2_READ_PAGE            "11"            // read page after auth
#define HITAG2_READ_PAGE_INVERTED   "01"            // as read page but all bits inverted
#define HITAG2_WRITE_PAGE           "10"            // write page after auth
#define HITAG2_HALT                 "00"            // silence currently authenticated tag

#define HITAG2_PWD_DEFAULT          "4D494B52"      // hitag default PWD ("MIKR")

#define HITAG2_KEY_LOW              "4D494B52"      // hitag default KEY_LOW
#define HITAG2_KEY_HIGH             "4F4E"          // hitag default KEY_HIGH ("ON")
#define HITAG2_KEY_DEFAULT          "4F4E4D494B52"  // hitag default key in correct order for AUTH command ("ONMIKR")

#define HITAG2_BLANK_BLOCK          "00000000"

#define HITAG2_PW_BLOCK_NUM         1               // password block number
#define HITAG2_KEY_BLOCK_NUM        2               // crypto key block number
#define HITAG2_CONFIG_BLOCK_NUM     3               // hitag2 config block
#define HITAG2_USER_DATA_BLOCK_NUM  4               // 1st user data block
#define HITAG2_BLOCKSIZE            32              // block size in bits
#define HITAG2_DATABLOCKS           8               // total number of blocks

#define HITAG2_WRITE_DELAY          614             // time to complete write in FCs

// config blocks
#define HITAG2_DEFAULT_CONFIG_BLOCK "06AA4854"      // hitag2 native, password mode
#define HITAG2_CRYPTO_CONFIG_BLOCK  "0EAA4854"      // hitag2 native, crypto mode
#define HITAG2_FDXB_CONFIG_BLOCK    "00AA4854"      // public-mode b
#define HITAG2_UNIQUE_CONFIG_BLOCK  "02AA4854"      // public-mode a
#define HITAG2_EM4X02_CONFIG_BLOCK  "02AA4854"      // public-mode a
#define HITAG2_MODEC_CONFIG_BLOCK   "04AA4854"      // public-mode c - PCF793X

// config block masks

#define HITAG2_MASK_PAGE_1_2_OTP_PROTECT    0b10000000
#define HITAG2_MASK_PAGE_3_OTP_PROTECT      0b01000000
#define HITAG2_MASK_PAGE_4_5_PROTECT        0b00100000
#define HITAG2_MASK_PAGE_6_7_PROTECT        0b00010000
#define HITAG2_MASK_SECURITY                0b00001000
#define HITAG2_MASK_MODE                    0b00000110
#define HITAG2_MASK_MODULATION              0b00000001

// config block bit shifts
#define HITAG2_SHIFT_PAGE_1_2_OTP_PROTECT   7
#define HITAG2_SHIFT_PAGE_3_OTP_PROTECT     6
#define HITAG2_SHIFT_PAGE_4_5_PROTECT       5
#define HITAG2_SHIFT_PAGE_6_7_PROTECT       4
#define HITAG2_SHIFT_SECURITY               3
#define HITAG2_SHIFT_MODE                   1
#define HITAG2_SHIFT_MODULATION             0

BOOL hitag1_get_uid(BYTE *response);
BOOL hitag1_hex_to_uid(BYTE *response, BYTE *hex);
BOOL hitag1_send_command(BYTE *response, BYTE *command, BOOL reset, BOOL sync, BYTE response_length, BOOL ack);
void hitag1_binarray_crc(BYTE *crc, BYTE *bin, BYTE length);
void hitag1_crc(BYTE *crc, BYTE data, BYTE bits);
BOOL hitag2_get_uid(BYTE *response);
BOOL hitag2_hex_to_uid(BYTE *response, BYTE *hex);
BOOL hitag1_select(BYTE *response, BYTE *uid);
BOOL hitag1_read_page(BYTE *response, BYTE block);
BOOL hitag2_pwd_auth(BYTE *response, BYTE *pwd);
BOOL hitag2_read_page(BYTE *response, BYTE block);
BOOL hitag2_write_page(BYTE block, BYTE *data);
void hitag2_test_rwd(unsigned int gapmin, unsigned int gapmax, unsigned int zeromin, unsigned int zeromax, unsigned int onemin, unsigned int onemax, BYTE *pass);
BOOL hitag2_hex_crypt(BYTE *target, BYTE *source);
void hitag2_binstring_crypt(BYTE *target, BYTE *source);
void hitag2_binarray_crypt(BYTE *target, BYTE *source, unsigned int length);
unsigned long hitag2_crypt(unsigned long source, BYTE length);
unsigned int hitag_ac_to_bin(BYTE *target, BYTE *source, unsigned int length);
BOOL hitag2_emulate_config_block(BYTE *config, BYTE target_tagtype);
BOOL hitag2_decode_pwm(unsigned long pulses[], unsigned long gaps[], unsigned int count);
BOOL hitag2_config_block_show(BYTE *config, BYTE *password, BYTE *key);

