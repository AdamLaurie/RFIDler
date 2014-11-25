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
#include "nvm.h"
#include "comms.h"

// save config and return TRUE if verify OK
BOOL saveconfig(void)
{
    NVMProgram((void *) RFIDLER_NVM_ADDRESS, (const void *) &RFIDlerConfig, sizeof(RFIDlerConfig), (void*) TmpBuff);
    NVMProgram((void *)RFIDLER_NVM_ADDRESS + sizeof(RFIDlerConfig), (const void *)&RFIDlerVTag, sizeof(RFIDlerVTag), (void*) TmpBuff);
    return !checkconfigchanged();
}

// return TRUE if config is changed
BOOL checkconfigchanged(void)
{
    if(memcmp(&RFIDlerConfig, (void *) RFIDLER_NVM_ADDRESS, sizeof(RFIDlerConfig)) != 0)
        return TRUE;
    if(memcmp(&RFIDlerVTag, (void *) RFIDLER_NVM_ADDRESS + sizeof(RFIDlerConfig), sizeof(RFIDlerVTag)) != 0)
        return TRUE;
    return FALSE;
}

// load config from NVM - return TRUE if loaded, FALSE if freshly initialised
BOOL loadconfig(void)
{
    // load config
    memcpy(&RFIDlerConfig, (void *) RFIDLER_NVM_ADDRESS, sizeof(RFIDlerConfig));
    // check sentinal
    if (memcmp(RFIDlerConfig.Name, "RFIDler", 7) != 0)
    {
        memset(&RFIDlerConfig, 0x00, sizeof(RFIDlerConfig));
        memcpy(RFIDlerConfig.Name, "RFIDler", 7);
        saveconfig();
        return FALSE;
    }
    // load VTAG
    memcpy(&RFIDlerVTag, (void *) RFIDLER_NVM_ADDRESS + sizeof(RFIDlerConfig), sizeof(RFIDlerVTag));
    return TRUE;
}

void wipeconfig(void)
{
    unsigned long i;

    for(i= RFIDLER_NVM_ADDRESS ; i < RFIDLER_NVM_ADDRESS + (unsigned long) sizeof(RFIDlerConfig); i += NVM_PAGE_SIZE)
            NVMErasePage((void *) i);
}

void showconfig(void)
{
    UserMessage("%s", "\r\n\r\nCurrent config:\r\n");
    UserMessage("\r\n  TAG Type:              %s", (BYTE *) TagTypes[RFIDlerConfig.TagType]);
    UserMessageNum("\r\n  Frame Clock uS/100:    %d", RFIDlerConfig.FrameClock);
    UserMessage("\r\n  Modulation:            %s", (BYTE *) ModulationSchemes[RFIDlerConfig.Modulation]);
    UserMessage("\r\n  Manchester:            %s", (BYTE *) OnOff[RFIDlerConfig.Manchester]);
    UserMessage("\r\n  BiPhase:               %s", (BYTE *) OnOff[RFIDlerConfig.BiPhase]);
    UserMessage("\r\n  Invert:                %s", (BYTE *) OnOff[RFIDlerConfig.Invert]);
    UserMessageNum("\r\n  Data Rate RF/n:        %d", RFIDlerConfig.DataRate);
    UserMessageNum("\r\n  Data Rate Sub 0:       %d", RFIDlerConfig.DataRateSub0);
    UserMessageNum("\r\n  Data Rate Sub 1:       %d", RFIDlerConfig.DataRateSub1);
    UserMessageNum("\r\n  Data Bits:             %d", RFIDlerConfig.DataBits);
    UserMessageNum("\r\n  Data Blocks:           %d", RFIDlerConfig.DataBlocks);
    UserMessageNum("\r\n  Blocksize:             %d", RFIDlerConfig.BlockSize);
    UserMessageNum("\r\n  Sync Bits:             %d", RFIDlerConfig.SyncBits);
    UserMessageNum("\r\n  Sync 0:                0x%02x", RFIDlerConfig.Sync[0]);
    UserMessageNum("\r\n  Sync 1:                0x%02x", RFIDlerConfig.Sync[1]);
    UserMessageNum("\r\n  Sync 2:                0x%02x", RFIDlerConfig.Sync[2]);
    UserMessageNum("\r\n  Sync 3:                0x%02x", RFIDlerConfig.Sync[3]);
    UserMessageNum("\r\n  Pot Low:               %d", RFIDlerConfig.PotLow);
    UserMessageNum("\r\n  Pot High:              %d", RFIDlerConfig.PotHigh);
    UserMessageNum("\r\n  PSK Quality uS:        %d", RFIDlerConfig.PSK_Quality);
    UserMessageNum("\r\n  Repeat:                %d", RFIDlerConfig.Repeat);
    UserMessageNum("\r\n  Timeout uS:            %d", RFIDlerConfig.Timeout);
    UserMessageNum("\r\n  RWD n-bit Barrier:     %d", RFIDlerConfig.RWD_Barrier_Bits);
    UserMessageNum("\r\n  RWD Barrier Period FC: %d", RFIDlerConfig.RWD_Barrier_Period);
    UserMessageNum("\r\n  RWD Barrier Gap FC:    %d", RFIDlerConfig.RWD_Barrier_Gap_Period);
    UserMessageNum("\r\n  RWD Zero Gap FC:       %d", RFIDlerConfig.RWD_Zero_Gap_Period);
    UserMessageNum("\r\n  RWD One Gap FC:        %d", RFIDlerConfig.RWD_One_Gap_Period);
    UserMessageNum("\r\n  RWD Sleep FC:          %d", RFIDlerConfig.RWD_Sleep_Period);
    UserMessageNum("\r\n  RWD Wake FC:           %d", RFIDlerConfig.RWD_Wake_Period);
    UserMessageNum("\r\n  RWD Zero FC:           %d", RFIDlerConfig.RWD_Zero_Period);
    UserMessageNum("\r\n  RWD One FC:            %d", RFIDlerConfig.RWD_One_Period);
    UserMessageNum("\r\n  RWD Wait RX->TX FC:    %d", RFIDlerConfig.RWD_Wait_Switch_RX_TX);
    UserMessageNum("\r\n  RWD Wait TX->RX FC:    %d", RFIDlerConfig.RWD_Wait_Switch_TX_RX);
    UserMessageNum("\r\n  Wiegand Pulse uS:      %d", RFIDlerConfig.Wiegand_Pulse);
    UserMessageNum("\r\n  Wiegand Gap uS:        %d", RFIDlerConfig.Wiegand_Gap);
    UserMessage("\r\n  Wiegand IdleState:     %s\r\n", (BYTE *) HighLow[RFIDlerConfig.Wiegand_IdleState]);
}
