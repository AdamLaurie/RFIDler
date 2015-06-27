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
#include "vtag.h"
#include "rfidler.h"
#include "util.h"
#include "tags.h"
#include "write.h"
#include "uid.h"
#include "comms.h"
#include "config.h"

void vtag_wipe(void)
{
    memset(&RFIDlerVTag, 0x00, sizeof(RFIDlerVTag));

}

/// show contents of vtag
void vtag_dump(void)
{
    BYTE tmp[MAXBLOCKSIZE + 1], interpret;
    unsigned int i, j, k;

    UserMessage("              Type: %s", (BYTE *) TagTypes[RFIDlerVTag.TagType]);

    UserMessage("\r\n         Emulating: %s", (BYTE *) TagTypes[RFIDlerVTag.EmulatedTagType]);

    UserMessage("\r\n           Raw UID: %s", RFIDlerVTag.UID);

    // show interpreted UID
    if(RFIDlerVTag.EmulatedTagType == TAG_TYPE_NONE)
        interpret= RFIDlerVTag.TagType;
    else
        interpret= RFIDlerVTag.EmulatedTagType;
    UserMessage("\r\n               UID: %s", interpret_uid(tmp, RFIDlerVTag.UID, interpret) ? tmp : (BYTE *) "invalid!");

    // show config block if present
    if(config_block_number(&i, RFIDlerVTag.TagType))
    {
        UserMessage("%s","\r\n\r\n");
        j= 0;
        pw_block_number(&j, RFIDlerVTag.TagType);
        k= 0;
        info_block_number(&k, RFIDlerVTag.TagType);
        config_block_show(&RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * i)], &RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * j)], &RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * k)], RFIDlerVTag.TagType);
    }

    if(RFIDlerVTag.DataBlocks == 0)
    {
        UserMessage("%s", "\r\n\r\n");
        return;
    }

    UserMessage("%s", "\r\n              Data:");
    tmp[HEXDIGITS(RFIDlerVTag.BlockSize)]= '\0';
    for(i= 0 ; i < RFIDlerVTag.DataBlocks ; ++i)
    {
        memcpy(tmp, &RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * i)], HEXDIGITS(RFIDlerVTag.BlockSize));
        if(tmp[0])
        {
            UserMessageNum("\r\n                 %d: ", i);
            UserMessage("%s", tmp);
        }
    }
    UserMessage("%s", "\r\n\r\n");
}

BOOL vtag_set_tag_type(BYTE *tagtype)
{
    BYTE tag;

    if(!(tag= tag_get_type(tagtype)))
            return FALSE;
    vtag_set_tag_from_type(tag);
    return TRUE;
}

void vtag_set_tag_from_type(BYTE tag)
{
    vtag_wipe();
    RFIDlerVTag.TagType= tag;
    RFIDlerVTag.BlockSize= tag_get_blocksize(tag);
    RFIDlerVTag.DataBlocks= tag_get_datablocks(tag);
}

// create a VTAG from UID
BOOL vtag_create_from_uid(BYTE *target_tagtype, BYTE source_tagtype, BYTE *uid)
{
    BYTE tag;
    unsigned int config_block_no, user_block_no;

    // set target tag type
    if (strlen(target_tagtype) == 0)
    {
        if(RFIDlerVTag.TagType == TAG_TYPE_NONE)
            tag= source_tagtype;
        else
            tag= RFIDlerVTag.TagType;
    }
    else
        if(!(tag= tag_get_type(target_tagtype)))
            return FALSE;

    // if tag & vtag are the same, just copy
    if(RFIDlerConfig.TagType == tag)
    {
        vtag_set_tag_from_type(tag);
        RFIDlerVTag.EmulatedTagType= TAG_TYPE_NONE;
    }
    else
    {
        // otherwise, set up emulation
        // check target is capable of emulating source
        if(config_block(TmpBits, source_tagtype, tag))
        {
            vtag_set_tag_from_type(tag);
            RFIDlerVTag.EmulatedTagType= source_tagtype;
        }
        else
            return FALSE;
    }

    // create raw UID
    if(!tag_uid_to_hex(RFIDlerVTag.UID, uid, source_tagtype))
            return FALSE;

    // get config & user data block numbers if required
    if(config_block_number(&config_block_no, tag))
    {
        // get & store config block
        if (!config_block(&RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * config_block_no)], source_tagtype, tag))
            return FALSE;

        // copy raw hex UID to data blocks
        if(config_user_block(&user_block_no, tag))
            tag_raw_uid_to_data(&RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * user_block_no)], RFIDlerVTag.UID, RFIDlerVTag.TagType);
    }

    return TRUE;
}

// copy real tag to vtag or set up emulation
BOOL vtag_copy_from_tag(BYTE *tagtype, BYTE *pass)
{
    BYTE tmp[MAXUID + 1], tag, copy= FALSE, i;
    unsigned int config_block_no, user_block_no;

    // set target tag type
    if (strlen(tagtype) == 0)
    {
        if(RFIDlerVTag.TagType == TAG_TYPE_NONE)
            tag= RFIDlerConfig.TagType;
        else
            tag= RFIDlerVTag.TagType;
    }
    else
        if(!(tag= tag_get_type(tagtype)))
            return FALSE;
    
    // check we've got a tag to copy
    if(!get_tag_uid(tmp))
        return FALSE;

    // set vtag to desired type
    vtag_set_tag_from_type(tag);

    // if tag & vtag are the same, just copy
    if(RFIDlerConfig.TagType == tag)
    {
        RFIDlerVTag.EmulatedTagType= TAG_TYPE_NONE;
        // auth
        if(!tag_login(0, TmpBits, pass))
            tag_auth(0, TmpBits, pass);

        // copy UID
        strcpy(RFIDlerVTag.UID, tmp);
        
        // if no data to copy, we're done.
        if(RFIDlerVTag.DataBlocks == 0)
            return TRUE;

        // copy data blocks
        for(i= 0 ; i < RFIDlerVTag.DataBlocks ; ++i)
        {
            if (!read_tag(RFIDlerVTag.Data + HEXDIGITS(i * RFIDlerVTag.BlockSize), i, i))
                UserMessageNum("\r\n%d: (fail)\r\n", i);
            else
                copy= TRUE;
        }
        return copy;
    }

    // otherwise, set up emulation
    RFIDlerVTag.EmulatedTagType= RFIDlerConfig.TagType;
    strcpy(RFIDlerVTag.UID, tmp);

    // get config & user data block numbers
    if(!config_block_number(&config_block_no, tag) || !config_user_block(&user_block_no, tag))
        return FALSE;

    // get & store config block
    if (!config_block(&RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * config_block_no)], RFIDlerConfig.TagType, tag))
        return FALSE;

    // copy raw hex UID to data blocks
    tag_raw_uid_to_data(&RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * user_block_no)], RFIDlerVTag.UID, RFIDlerVTag.TagType);

    return TRUE;
}

// convert current vtag to new type
BOOL vtag_convert(BYTE *tagtype)
{
    BYTE tmp[MAXUID + 1], newtag;

    if(RFIDlerVTag.TagType == TAG_TYPE_NONE)
        return FALSE;

    // get current interpreted uid
    if(RFIDlerVTag.EmulatedTagType == TAG_TYPE_NONE)
        newtag= RFIDlerVTag.TagType;
    else
        newtag= RFIDlerVTag.EmulatedTagType;
    // check UID is valid
    if(!interpret_uid(tmp, RFIDlerVTag.UID, newtag))
        return FALSE;

    // create new VTAG from UID
    return vtag_create_from_uid(tagtype, newtag, tmp);
}

BOOL vtag_write_to_tag(BYTE *pass)
{
    unsigned int block, config_block_no;
    BYTE tmp[MAXBLOCKSIZE + 1];
    BOOL auth= FALSE;
    StoredConfig tmptag;

    // preserve tag type
    memcpy(&tmptag, &RFIDlerConfig, sizeof(RFIDlerConfig));

    // set real tag to vtag type if not already the same
    if(RFIDlerConfig.TagType != RFIDlerVTag.TagType)
        if(!tag_set(RFIDlerVTag.TagType))
        {
            memcpy(&RFIDlerConfig, &tmptag, sizeof(RFIDlerConfig));
            return FALSE;
        }

    // reset target tag, but don't care if we get UID as it may not be in a valid mode
    get_tag_uid(tmp);

    // re-auth
    if(!tag_login(block, tmp, pass))
        tag_auth(block, tmp, pass);

    // initialise target in default mode
    // get config block number
    if(!config_block_number(&config_block_no, RFIDlerConfig.TagType))
        return FALSE;

    // get default config block data
    tmp[HEXDIGITS(RFIDlerVTag.BlockSize)]= '\0';
    if (!config_block(tmp, RFIDlerConfig.TagType, RFIDlerConfig.TagType))
    {
        memcpy(&RFIDlerConfig, &tmptag, sizeof(RFIDlerConfig));
        return FALSE;
    }

    // write default config
    if(!write_tag(config_block_no, tmp, VERIFY))
    {
        memcpy(&RFIDlerConfig, &tmptag, sizeof(RFIDlerConfig));
        return FALSE;
     }
    
    // reset tag again
    get_tag_uid(tmp);

    // write all VTAG blocks with valid data in them
    // but avoid writing config block until last as tag may stop responding
    tmp[HEXDIGITS(RFIDlerVTag.BlockSize)]= '\0';
    for(block= 0 ; block < RFIDlerVTag.DataBlocks ; ++block)
        if(block != config_block_no && RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * block)])
        {
            // try to login/auth in case target tag requires it
            // don't care if we fail
            if(!(auth= tag_login(block, tmp, pass)))
                auth= tag_auth(block, tmp, pass);
            
            memcpy(tmp, &RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * block)], HEXDIGITS(RFIDlerVTag.BlockSize));
            UserMessageNum("\r\n%d: ", block);
            UserMessage("%s", tmp);
            // failure allowed as we may be trying to write locked blocks
            if(!write_tag(block, tmp, VERIFY))
            {
                UserMessage("%s", " Failed!");
                if(!auth)
                    UserMessage("%s", " (Auth/Login)");
            }
        }

    // write config block (no verify as some tags stop talking after config change)

    if(!tag_login(block, tmp, pass))
        tag_auth(block, tmp, pass);

    tmp[HEXDIGITS(RFIDlerVTag.BlockSize)]= '\0';
    memcpy(tmp, &RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * config_block_no)], HEXDIGITS(RFIDlerVTag.BlockSize));
    UserMessageNum("\r\n\r\n%d: ", config_block_no);
    UserMessage("%s", tmp);
    if(!write_tag(config_block_no, tmp, NO_VERIFY))
    {
        memcpy(&RFIDlerConfig, &tmptag, sizeof(RFIDlerConfig));
        return FALSE;
    }

    memcpy(&RFIDlerConfig, &tmptag, sizeof(RFIDlerConfig));
    return TRUE;
}

BOOL vtag_write_blocks(unsigned int startblock, BYTE *data)
{
    unsigned int user_block_no;

    // check data doesn't overrun emulation tag capacity
    if(strlen(data) * 4 > (RFIDlerVTag.DataBlocks - startblock) * RFIDlerVTag.BlockSize || startblock >= RFIDlerVTag.DataBlocks)
        return FALSE;
    // check data doesn't overrun emulated tag size
    if(RFIDlerVTag.EmulatedTagType != TAG_TYPE_NONE && config_user_block(&user_block_no, RFIDlerVTag.TagType))
        if((((strlen(data) * 4) / RFIDlerVTag.BlockSize) + startblock) - 1 > tag_get_databits(RFIDlerVTag.EmulatedTagType) / RFIDlerVTag.BlockSize)
            return FALSE;
    memcpy(&RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * startblock)], data, strlen(data));
    // copy raw hex back to UID if emulating
    if(RFIDlerVTag.EmulatedTagType != TAG_TYPE_NONE && config_user_block(&user_block_no, RFIDlerVTag.TagType))
        memcpy(RFIDlerVTag.UID, &RFIDlerVTag.Data[HEXDIGITS(RFIDlerVTag.BlockSize * user_block_no)], HEXDIGITS(RFIDlerVTag.BlockSize * (RFIDlerVTag.DataBlocks - user_block_no)));
    return TRUE;
}
