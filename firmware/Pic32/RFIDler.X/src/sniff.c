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
#include "clock.h"
#include "comms.h"
#include "hitag.h"
#include "q5.h"
#include "sniff.h"
#include "tamagotchi.h"
#include "util.h"

// watch external clock for PWM messages
// specify minimum gap to look for in us
void sniff_pwm(unsigned int min)
{
    BOOL            toggle;
    BOOL            abort= FALSE;
    unsigned long   i, count, pulsecount= 0L, gaps[DETECT_BUFFER_SIZE], pulses[DETECT_BUFFER_SIZE];
    
    // make sure local clock isn't running & switch to input
    stop_HW_clock();

    COIL_MODE_READER();
    READER_CLOCK_ENABLE_OFF(LOW);
    
    toggle= SNIFFER_COIL;
    
    // wait for 100 ticks to make sure we're settled
    toggle= SNIFFER_COIL;
    while(count < 100)
    {
        while(SNIFFER_COIL == toggle)
            // check for user abort
            if(get_user_abort())
                return;
        ++count;
        toggle= !toggle;
    }
    
    // watch for gaps / pulses
    i= 0;
    GetTimer_us(RESET);
    while(!abort)
    {
        while(SNIFFER_COIL == toggle)
            // check for user abort
            if((abort= get_user_abort()))
                break;
        toggle= !toggle;
        count= GetTimer_us(RESET);
        // check if it was a gap
        if(count > min)
        {
            pulses[i]= pulsecount;
            gaps[i++]= count;
            pulsecount= 0L;
        }
        else
            pulsecount += count;
        if(i == DETECT_BUFFER_SIZE)
        {
            decode_pwm(pulses, gaps, i);
            i= 0;
        }
    }
    
    decode_pwm(pulses, gaps, i);
}

void decode_pwm(unsigned long pulses[], unsigned long gaps[], unsigned int count)
{
    unsigned int i;
    
    switch(RFIDlerConfig.TagType)
    {
        case TAG_TYPE_HITAG1:
            hitag1_decode_pwm(pulses, gaps, count);
            break;
            
        case TAG_TYPE_HITAG2:
            hitag2_decode_pwm(pulses, gaps, count);
            break;

        case TAG_TYPE_Q5:
        case TAG_TYPE_T55X7:
            q5_decode_pwm(pulses, gaps, count);
            break;

        case TAG_TYPE_TAMAGOTCHI:
            tamagotchi_decode_pwm(pulses, gaps, count);
            break;
            
        default:
            for(i= 0 ; i < count ; ++i)
            {
                UserMessageNum("\r\nPulse: %d ", pulses[i]);
                UserMessageNum("Gap: %d", gaps[i]);
            }
            break;
    }
    UserMessage("\r\n","");
}

// convert pwm array to human readable binary
// terminates at end of first sequence and returns number of samples processed 
BYTE generic_decode_pwm(BYTE *result, unsigned long pulses[], unsigned int minpulse, unsigned int maxpulse, unsigned long gaps[], unsigned int mingap, unsigned int maxgap, unsigned int count)
{
    unsigned int    one, zero, i;
    BOOL            sequence= FALSE;
    
    // first try to detect size of one and zero blocks
    // short block is a zero, long is a one
    for(i= 0, zero= 65535, one= 0 ; i < count ; ++i)
    {
        if(gaps[i] >= mingap && gaps[i] <= maxgap && pulses[i] > minpulse && pulses[i] <= maxpulse)
        {
            if(pulses[i] > one)
                one= pulses[i];
            if(pulses[i] < zero)
                zero= pulses[i];
        }
    }
    
    if(zero == 65535 || one == 0)
        return 0;
    
    // decode and return the first sequence
    for(i= 0 ; i < count ; ++i)
    {
        if(gaps[i] >= mingap && gaps[i] <= maxgap)
        {
            if(pulses[i] <= maxpulse)
            {
                if(approx(pulses[i], zero, 20))
                    *(result++)= '0';
                else
                    *(result++)= '1';
                sequence= TRUE;
            }
            else
                if(sequence)
                {
                   *result= '\0';
                   return i + 1;
                }
        }
    }
    
    if(!sequence)
        return 0;
    
    *result= '\0';
    return i;
}
