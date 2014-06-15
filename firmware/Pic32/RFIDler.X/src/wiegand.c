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
#include "util.h"
#include "wiegand.h"
#include "comms.h"

// learn wiegand timings
BOOL learn_wiegand(BYTE trigger)
{
    // trigger external reader (set debug pin low)
    if(trigger)
    {
        switch(trigger)
        {
            case 1:
                DEBUG_PIN_1= DEBUG_PIN_ON;
                break;

            case 2:
                DEBUG_PIN_2= DEBUG_PIN_ON;
                break;


            case 3:
                DEBUG_PIN_3= DEBUG_PIN_ON;
                break;

            case 4:
                DEBUG_PIN_4= DEBUG_PIN_ON;
                break;

            default:
                return FALSE;
        }
    }

    RFIDlerConfig.Wiegand_IdleState= WIEGAND_IN_0;

    // wait for 1st pulse
    while(WIEGAND_IN_0 == RFIDlerConfig.Wiegand_IdleState && WIEGAND_IN_1 == RFIDlerConfig.Wiegand_IdleState)
        if(get_user_abort())
                return FALSE;

    //DEBUG_PIN_4= !DEBUG_PIN_4;
    // start measuring pulse
    GetTimer_us(RESET);

    // store bit
    if(WIEGAND_IN_0 != RFIDlerConfig.Wiegand_IdleState)
        DataBuff[DataBuffCount++]= '0';
    else
        DataBuff[DataBuffCount++]= '1';

    // wait for pulse to end
    while(WIEGAND_IN_0 != RFIDlerConfig.Wiegand_IdleState || WIEGAND_IN_1 != RFIDlerConfig.Wiegand_IdleState)
        if(get_user_abort())
                return FALSE;

    //DEBUG_PIN_4= !DEBUG_PIN_4;

    // read pulse length and start measuring gap
    RFIDlerConfig.Wiegand_Pulse= GetTimer_us(RESET);

    // wait for next pulse
    while(WIEGAND_IN_0 == RFIDlerConfig.Wiegand_IdleState && WIEGAND_IN_1 == RFIDlerConfig.Wiegand_IdleState)
        if(get_user_abort())
                return FALSE;

    //DEBUG_PIN_4= !DEBUG_PIN_4;

    // read gap length
    RFIDlerConfig.Wiegand_Gap= GetTimer_us(RESET);

    // store bit
    if(WIEGAND_IN_0 != RFIDlerConfig.Wiegand_IdleState)
        DataBuff[DataBuffCount++]= '0';
    else
        DataBuff[DataBuffCount++]= '1';

    // wait for pulse to end
    while(WIEGAND_IN_0 != RFIDlerConfig.Wiegand_IdleState || WIEGAND_IN_1 != RFIDlerConfig.Wiegand_IdleState)
        if(get_user_abort())
                return FALSE;

    // read the rest of the burst
    read_wiegand(NO_TRIGGER);

    if(Interface == INTERFACE_CLI)
    {
        UserMessageNum("     Wiegand pulse width: %d\r\n", RFIDlerConfig.Wiegand_Pulse);
        UserMessageNum(" uS                    gap: %d\r\n", RFIDlerConfig.Wiegand_Gap);
        UserMessageNum(" uS             bit period: %d uS\r\n", RFIDlerConfig.Wiegand_Pulse + RFIDlerConfig.Wiegand_Gap);
    }

    if(trigger)
    {
        switch(trigger)
        {
            case 1:
                DEBUG_PIN_1= DEBUG_PIN_OFF;
                break;

            case 2:
                DEBUG_PIN_2= DEBUG_PIN_OFF;
                break;


            case 3:
                DEBUG_PIN_3= DEBUG_PIN_OFF;
                break;

            case 4:
                DEBUG_PIN_4= DEBUG_PIN_OFF;
                break;

            default:
                return FALSE;
        }
    }
        
    return TRUE;
}

BOOL read_wiegand(BYTE trigger)
{
    unsigned int timeout;

    // trigger external reader (set debug pin low)
    if(trigger)
    {
        switch(trigger)
        {
            case 1:
                DEBUG_PIN_1_TOGGLE();
                break;

            case 2:
                DEBUG_PIN_2_TOGGLE();
                break;


            case 3:
                DEBUG_PIN_3_TOGGLE();
                break;

            case 4:
                DEBUG_PIN_4_TOGGLE();
                break;

            default:
                return FALSE;
        }
    }


    timeout= (RFIDlerConfig.Wiegand_Pulse + RFIDlerConfig.Wiegand_Gap) * 2L;

    // wait for the first pulse
    DataBuff[DataBuffCount++]= read_wiegand_bit(0);

    while(42)
    {
        DataBuff[DataBuffCount]= read_wiegand_bit(timeout);
        if (DataBuff[DataBuffCount] == '\0')
            break;
        DataBuffCount++;
    }

    if(trigger)
    {
        switch(trigger)
        {
            case 1:
                DEBUG_PIN_1_TOGGLE();
                break;

            case 2:
                DEBUG_PIN_2_TOGGLE();
                break;


            case 3:
                DEBUG_PIN_3_TOGGLE();
                break;

            case 4:
                DEBUG_PIN_4_TOGGLE();
                break;

            default:
                return FALSE;
        }
    }

    return TRUE;
}

unsigned char read_wiegand_bit(unsigned int timeout)
{
    unsigned int time;
    unsigned char tmp;

    // reset timer
    GetTimer_us(RESET);

    // wait for pulse or timeout if required
    while(WIEGAND_IN_0 == RFIDlerConfig.Wiegand_IdleState && WIEGAND_IN_1 == RFIDlerConfig.Wiegand_IdleState)
    {
        time= GetTimer_us(NO_RESET);
        if(timeout && time > timeout)
            return '\0';
        if(get_user_abort())
            return '\0';
    }

    if (WIEGAND_IN_0 != RFIDlerConfig.Wiegand_IdleState)
        tmp = '0';
    else
        tmp= '1';

    // wait for pulse to end
    while(WIEGAND_IN_0 != RFIDlerConfig.Wiegand_IdleState || WIEGAND_IN_1 != RFIDlerConfig.Wiegand_IdleState)
        ;

    return tmp;
}

BOOL write_wiegand(BYTE *data)
{
    while(*data)
    {
        if(!write_wiegand_bit(*data))
            return TRUE;
        ++data;
    }

    return FALSE;
}

// TODO: write_wiegand_uid
// send wiegad data appropriate to the tag
// uid is human readable HEX
BOOL write_wiegand_uid(BYTE *uid)
{
    if(WiegandOutput)
        return TRUE;
    return TRUE;
}

BOOL write_wiegand_bit(BYTE thisbit)
{
    if(! RFIDlerConfig.Wiegand_Pulse || ! RFIDlerConfig.Wiegand_Gap)
        return FALSE;

    // reset timer
    GetTimer_us(RESET);
    
    // send bit
    if(thisbit == '0')
        WIEGAND_OUT_0= !RFIDlerConfig.Wiegand_IdleState;
    else
        WIEGAND_OUT_1= !RFIDlerConfig.Wiegand_IdleState;
    
    while(GetTimer_us(NO_RESET) < RFIDlerConfig.Wiegand_Pulse)
        ;
    
    WIEGAND_OUT_0= RFIDlerConfig.Wiegand_IdleState;
    WIEGAND_OUT_1= RFIDlerConfig.Wiegand_IdleState;

    // send gap
    GetTimer_us(RESET);
    while(GetTimer_us(NO_RESET) < RFIDlerConfig.Wiegand_Gap)
        ;

    return TRUE;
}

// simple test for wiegand pin loopback
BOOL wiegand_test(void)
{
    wiegand_out_enable();
    WIEGAND_OUT_0= LOW;
    WIEGAND_OUT_1= HIGH;
    if(WIEGAND_IN_0 != LOW || WIEGAND_IN_1 != HIGH)
        return FALSE;

    WIEGAND_OUT_0= HIGH;
    WIEGAND_OUT_1= LOW;
    if(WIEGAND_IN_0 != HIGH || WIEGAND_IN_1 != LOW)
        return FALSE;

    return TRUE;
}


// add HID parity to binary array: EVEN prefix for 1st half of ID, ODD suffix for 2nd half
void wiegand_add_parity(unsigned char *target, unsigned char *source, unsigned char length)
{
    *(target++)= parity(source, EVEN, length / 2);
    memcpy(target, source, length);
    target += length;
    *(target)= parity(source + length / 2, ODD, length / 2);
}

// disable wiegand output pins by setting them to inputs (needed for hardware test rig)
void wiegand_out_disable(void)
{
    WIEGAND_OUT_0_TRIS= INPUT_PIN;
    WIEGAND_OUT_1_TRIS= INPUT_PIN;
    WiegandOutput= FALSE;
}

// enable wiegand output pins and set to default state
void wiegand_out_enable(void)
{
    WIEGAND_OUT_0_TRIS= OUTPUT_PIN;
    WIEGAND_OUT_1_TRIS= OUTPUT_PIN;
    WIEGAND_OUT_0= WIEGAND_IN_0;
    WIEGAND_OUT_1= WIEGAND_IN_1;
    WiegandOutput= TRUE;
}

// enable or disable weak pullups on wiegand read pins.
// note these may not be strong enough for some readers,
// so external pullups may need to be used.
void wiegand_set_pullups(BOOL state)
{
//    WIEGAND_IN_0_PULLDOWN= !state;
//    WIEGAND_IN_1_PULLDOWN= !state;
    WIEGAND_IN_0_PULLUP= state;
    WIEGAND_IN_1_PULLUP= state;

}

// this device does not seem to support pull-downs(!)
//// enable or disable weak pulldowns on wiegand read pins
//void wiegand_set_pulldowns(BOOL state)
//{
//    WIEGAND_IN_0_PULLUP= !state;
//    WIEGAND_IN_1_PULLUP= !state;
//    WIEGAND_IN_0_PULLDOWN= state;
//    WIEGAND_IN_1_PULLDOWN= state;
//}

