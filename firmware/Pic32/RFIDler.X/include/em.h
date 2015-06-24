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

// em4x02
#define EM4X02_DATABITS         64

// em4205/4305 (em4469 compatible command set)
#define EM4205_DATABITS         512
#define EM4205_BLOCKSIZE        32
#define EM4205_DATABLOCKS       16
#define EM4X05_CONFIG_BLOCK_NUM 4
#define EM4X05_INFO_BLOCK_NUM   0

// em4205 commands (leading 0 + 3 bits + even parity)
#define EM4205_LOGIN            "00011"
#define EM4205_WRITE_WORD       "00101"
#define EM4205_READ_WORD        "01001"
#define EM4205_PROTECT          "01100"
#define EM4205_DISABLE          "01010"

// config block masks

#define EM4205_MASK_RESERVED                0b1111100000000000000000000000000
#define EM4205_MASK_PIGEON                  0b0000010000000000000000000000000
#define EM4205_MASK_UNUSED_4                0b0000001000000000000000000000000
#define EM4205_MASK_RTF                     0b0000000100000000000000000000000
#define EM4205_MASK_DISABLE                 0b0000000010000000000000000000000
#define EM4205_MASK_UNUSED_3                0b0000000001100000000000000000000
#define EM4205_MASK_WRITE_LOGIN             0b0000000000010000000000000000000
#define EM4205_MASK_UNUSED_2                0b0000000000001000000000000000000
#define EM4205_MASK_READ_LOGIN              0b0000000000000100000000000000000
#define EM4205_MASK_LWR                     0b0000000000000011110000000000000
#define EM4205_MASK_DELAYED_ON              0b0000000000000000001100000000000
#define EM4205_MASK_UNUSED_1                0b0000000000000000000011000000000
#define EM4205_MASK_ENCODER                 0b0000000000000000000000111100000
#define EM4205_MASK_DATA_RATE               0b0000000000000000000000000011111

// config block bit shifts

#define EM4205_SHIFT_RESERVED               27
#define EM4205_SHIFT_PIGEON                 26
#define EM4205_SHIFT_UNUSED_5               25
#define EM4205_SHIFT_RTF                    24
#define EM4205_SHIFT_DISABLE                23
#define EM4205_SHIFT_UNUSED_4               21
#define EM4205_SHIFT_WRITE_LOGIN            20
#define EM4205_SHIFT_UNUSED_3               19
#define EM4205_SHIFT_READ_LOGIN             18
#define EM4205_SHIFT_LWR                    14
#define EM4205_SHIFT_DELAYED_ON             12
#define EM4205_SHIFT_UNUSED_2               10
#define EM4205_SHIFT_ENCODER                6
#define EM4205_SHIFT_DATA_RATE              0

// info block masks

#define EM4205_MASK_CUSTOMER                0b0000000000001111111111000000000
#define EM4205_MASK_CAPACITOR               0b0000000000000000000000001100000
#define EM4205_MASK_CHIP                    0b0000000000000000000000000011110

// info block shifts
#define EM4205_SHIFT_CUSTOMER               9
#define EM4205_SHIFT_CAPACITOR              5
#define EM4205_SHIFT_CHIP                   1

// config values
#define CHIP_TYPE_EM4205                    8
#define CHIP_TYPE_EM4305                    9



BOOL em4x02_get_uid(BYTE *response);
BOOL em4x02_hex_to_uid(BYTE *response, BYTE *hex);
BOOL hex_to_em4x02_bin(unsigned char *em, unsigned char *hex);
BOOL em4x02_hex_to_bin(unsigned char *bin, unsigned char *em);
void bin_to_em4x02_bin(unsigned char *em, unsigned char *bin);

BOOL em4205_send_command(BYTE *command, char address, BOOL send_data, unsigned long data, BOOL get_response, BYTE *response);
BOOL em4205_forward_link(BYTE *data);
BOOL em4205_get_uid(BYTE *response);
BOOL em4205_disable(void);
BOOL em4205_read_word(BYTE *response, BYTE word);
void bin_to_em4205_ota(unsigned char *ota, unsigned char *bin);
BOOL em4205_ota_to_hex(unsigned char *hex, unsigned char *ota);
BOOL em4205_config_block_show(BYTE *config, BYTE *password, BYTE *info);