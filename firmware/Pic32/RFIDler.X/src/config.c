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
#include "config.h"
#include "em.h"
#include "read.h"
#include "hitag.h"
#include "q5.h"
#include "t55x7.h"

// get the config block number
BOOL config_block_number(unsigned int *block, BYTE tagtype)
{
    switch (tagtype)
    {
        case TAG_TYPE_EM4X05:
            *block= EM4X05_CONFIG_BLOCK_NUM;
            return TRUE;
            
        case TAG_TYPE_HITAG1:
            *block= HITAG1_CONFIG_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_HITAG2:
            *block= HITAG2_CONFIG_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_Q5:
            *block= Q5_CONFIG_BLOCK_NUM;

        case TAG_TYPE_T55X7:
            *block= T55X7_CONFIG_BLOCK_NUM;
            return TRUE;

        default:
            return FALSE;
    }
}

// get the first user-data block number
BOOL config_user_block(unsigned int *block, BYTE tagtype)
{
    switch (tagtype)
    {
        case TAG_TYPE_EM4X05:
            *block= EM4X05_USER_DATA_BLOCK_NUM;
            return TRUE;
            
        case TAG_TYPE_HITAG1:
            *block= HITAG1_USER_DATA_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_HITAG2:
            *block= HITAG2_USER_DATA_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_Q5:
            *block= Q5_USER_DATA_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_T55X7:
            *block= T55X7_USER_DATA_BLOCK_NUM;
            return TRUE;

        default:
            return FALSE;
    }
}

// get the password block number
BOOL pw_block_number(unsigned int *block, BYTE tagtype)
{
    switch (tagtype)
    {
        // explicitly return FALSE as password block (2) is always Write Only
        // so any attempt to read it will fail
        case TAG_TYPE_EM4X05:
            return FALSE;
            
        case TAG_TYPE_HITAG2:
            *block= HITAG2_PW_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_Q5:
            *block= Q5_PW_BLOCK_NUM;
            return TRUE;

        case TAG_TYPE_T55X7:
            *block= T55X7_PW_BLOCK_NUM;
            return TRUE;

        default:
            return FALSE;
    }
}

// get the additional info block number
BOOL info_block_number(unsigned int *block, BYTE tagtype)
{
    switch (tagtype)
    {
        // customer code, tag type, capacitor
        case TAG_TYPE_EM4X05:
            *block= EM4X05_INFO_BLOCK_NUM;
            return TRUE;
            
        // use this to show crypto key
        case TAG_TYPE_HITAG2:
            *block= HITAG2_KEY_BLOCK_NUM;
            return TRUE;

        default:
            return FALSE;
    }
}

// get current config block from tag
BOOL get_config_block(BYTE *out, BYTE tagtype)
{
    int block;

    if(config_block_number(&block, tagtype))
        return read_tag(out, block, block);
    return FALSE;
}

// get current password block from tag
BOOL get_pw_block(BYTE *out, BYTE tagtype)
{
    int block;

    if(pw_block_number(&block, tagtype))
        return read_tag(out, block, block);
    
    return FALSE;
}

// get additional info block from tag
BOOL get_info_block(BYTE *out, BYTE tagtype)
{
    int block;

    if(info_block_number(&block, tagtype))
        return read_tag(out, block, block);
    
    return FALSE;
}

// get a config block suitable for emulating
BOOL config_block(BYTE *config, BYTE target_tagtype, BYTE emulator_tagtype)
{
    switch (emulator_tagtype)
    {
        case TAG_TYPE_EM4X05:
            return em4205_emulate_config_block(config, target_tagtype);
            
        case TAG_TYPE_HITAG2:
            return hitag2_emulate_config_block(config, target_tagtype);

        case TAG_TYPE_Q5:
            return q5_emulate_config_block(config, target_tagtype);

        case TAG_TYPE_T55X7:
            return t55x7_emulate_config_block(config, target_tagtype);

        default:
            return FALSE;
    }
}

// display contents of tag config block if present
BOOL config_block_show(BYTE *config, BYTE *password, BYTE *info, BYTE tagtype)
{
    switch(tagtype)
    {
        case TAG_TYPE_EM4X05:
            return em4205_config_block_show(config, password, info);
            
        case TAG_TYPE_HITAG2:
            return hitag2_config_block_show(config, password, info);
            
        case TAG_TYPE_Q5:
            return q5_config_block_show(config, password);
            
        case TAG_TYPE_T55X7:
            return t55x7_config_block_show(config, password);
            
        default:
            return FALSE;
    }
}