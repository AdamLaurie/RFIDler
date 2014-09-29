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




#define T55X7_SOFT_RESET           "00"        // reset (test mode)
#define T55X7_DIRECT_ACCESS        "10"        // direct read in pwd or non-pwd mode
#define T55X7_STD_WRITE_P0         "10"        // write page 0
#define T55X7_STD_WRITE_P1         "11"        // write page 1
#define T55X7_GET_TRACE_DATA       "11"        // get 64 bits tracebility data
#define T55X7_AOR                  "10"        // Answer On Request (wakeup)
#define T55X7_READ_CONFIG_BLOCK    "100000"    // direct read, no PWD, address 000

#define T55X7_START_GAP            48          // start gap in FC - range 10 - 50, must be greater than command gap
#define T55X7_POR_DELAY            8190        // FCs additional startup delay if POR set
#define T55X7_WRITE_DELAY          1000        // time needed to complete write operation in FC - 64 + 648 in the docs, so round up a bit

#define T55X7_BLOCKSIZE            32          // blocksize in bits
#define T55X7_DATABLOCKS           8           // total number of blocks
#define T55X7_CONFIG_BLOCK_NUM     0           // config block number
#define T55X7_USER_DATA_BLOCK_NUM  1           // 1st user data block
#define T55X7_PW_BLOCK_NUM         7           // password block number
#define T55X7_BLANK_BLOCK          "FFFFFFFF"

#define T55X7_DEFAULT_PWD          "FFFFFFFF"  // default password

// config blocks
#define T55X7_DEFAULT_CONFIG_BLOCK      "00148000"      // compat mode, data rate 64, manchester, 7 data blocks
#define T55X7_EM_UNIQUE_CONFIG_BLOCK    "00148040"      // emulate em4x02/unique - data rate 64, manchester, 2 data blocks
//#define Q5_FDXB_CONFIG_BLOCK         "E600F0E8"      // emulate fdx-b
#define T55X7_HID_26_CONFIG_BLOCK       "00107060"      // hid 26 bit - FSK2a, data rate 50, 3 data blocks
#define T55X7_INDALA_64_CONFIG_BLOCK    "00081040"      // emulate indala 64 bit - PSK1, psk carrier FC * 2, data rate 32, maxblock 2
#define T55X7_INDALA_224_CONFIG_BLOCK   "000810E0"      // emulate indala 224 bit - PSK1, psk carrier FC * 2, data rate 32, maxblock 7

// note that T55X7 sends data in LSB order, so everything in the datasheet is effectively reversed
// what is shown as "bit 32" is actually bit 0

// config block common masks
#define T55X7_MASK_MASTER_KEY                    0b11110000000000000000000000000000
#define T55X7_MASK_XMODE                         0b00000000000000100000000000000000
#define T55X7_MASK_PSK_CARRIER_FREQ              0b00000000000000000000110000000000
#define T55X7_MASK_AOR                           0b00000000000000000000001000000000
#define T55X7_MASK_OTP                           0b00000000000000000000000100000000
#define T55X7_MASK_MAX_BLOCK                     0b00000000000000000000000011100000
#define T55X7_MASK_PWD                           0b00000000000000000000000000010000
#define T55X7_MASK_FAST_WRITE                    0b00000000000000000000000000000100
#define T55X7_MASK_INVERSE_DATA                  0b00000000000000000000000000000010
#define T55X7_MASK_POR_DELAY                     0b00000000000000000000000000000001

#define T55X7_COMPAT_MODE                        0b0110
// config block masks - compatibility mode (master key == 0110)
#define T55X7_COMPAT_MASK_DATA_BIT_RATE          0b00000000000111000000000000000000
#define T55X7_COMPAT_MASK_MODULATION             0b00000000000000011111000000000000
#define T55X7_COMPAT_MASK_ST                     0b00000000000000000000000000001000

#define T55X7_XMODE_MODE                         0b1001
// config block masks - xtended mode (master key == 1001)
#define T55X7_XMODE_MASK_DATA_BIT_RATE           0b00000000111111000000000000000000
#define T55X7_XMODE_MASK_MODULATION              0b00000000000000011111000000000000
#define T55X7_XMODE_MASK_SST                     0b00000000000000000000000000001000

// config block bit shifts - (same for both modes, but not all apply)
#define T55X7_SHIFT_MASTER_KEY                  28
#define T55X7_SHIFT_DATA_BIT_RATE               18
#define T55X7_SHIFT_XMODE                       17
#define T55X7_SHIFT_MODULATION                  12
#define T55X7_SHIFT_PSK_CARRIER_FREQ            10
#define T55X7_SHIFT_AOR                         9
#define T55X7_SHIFT_OTP                         8
#define T55X7_SHIFT_MAX_BLOCK                   5
#define T55X7_SHIFT_PWD                         4
#define T55X7_SHIFT_ST_SST                      3
#define T55X7_SHIFT_FAST_WRITE                  2
#define T55X7_SHIFT_INVERSE_DATA                1
#define T55X7_SHIFT_POR_DELAY                   0

// T55X7 modulation settings
#define T55X7_MOD_BIPHASE_57               24
#define T55X7_MOD_BIPHASE_50               17
#define T55X7_MOD_MANCHESTER               8
#define T55X7_MOD_FSK2_A                   7
#define T55X7_MOD_FSK1_A                   6
#define T55X7_MOD_FSK2                     5
#define T55X7_MOD_FSK1                     4
#define T55X7_MOD_PSK3                     3
#define T55X7_MOD_PSK2                     2
#define T55X7_MOD_PSK1                     1
#define T55X7_MOD_DIRECT                   0


//

BOOL t55x7_send_command(BYTE *response, BYTE *command, BYTE length, BOOL reset, BOOL sync, BYTE response_length);
//BOOL q5_get_uid(BYTE *response);
//BOOL q5_hex_to_uid(BYTE *response, BYTE *hex);
BOOL t55x7_read_block(BYTE *response, BYTE block);
//BOOL q5_write_block(BYTE block, BYTE *data, BOOL lock, BOOL verify);
//BOOL q5_get_config(BYTE *response);
//BOOL q5_login(BYTE *response, BYTE *pass);
BOOL t55x7_rwd_test(BYTE *pattern);
//BOOL q5_config_block_show(BYTE *config);
BOOL t55x7_emulate_config_block(BYTE *config, BYTE target_tagtype);
