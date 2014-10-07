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

// bad stuff happens if this gets optimised!
#pragma GCC optimize("O0")

#include "HardwareProfile.h"
#include "rfidler.h"
#include "rwd.h"
#include "comms.h"

unsigned long HW_Bits;
BYTE HW_Skip_Bits;                   // skip arbitrary number of leading bits (externally adjusted for manchester/biphase)
unsigned int PSK_Min_Pulse;
BOOL PSK_Read_Error= FALSE;
BOOL Manchester_Error= FALSE;
BOOL Manchester_Auto_Correct= FALSE;  // special case for tags that may start with (undetectable) 0 bit. will be reset by reader ISR if set.

// Interrupt Service Routines
//

// Reader clock ISR
// also process RWD commands while we toggle clock line
void __ISR(_OUTPUT_COMPARE_5_VECTOR, ipl6auto) reader_clock_tick (void)
{
    static unsigned int count= 0;

    // Clear interrupt flag
    mOC5ClearIntFlag();
    
    mLED_Clock_On();

    // process RWD commands (if any)
    switch (RWD_State)
    {
        case RWD_STATE_INACTIVE:
        case RWD_STATE_ACTIVE:
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            break;

        case RWD_STATE_GO_TO_SLEEP:
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // initial shutdown of coil to restart tag
            READER_CLOCK_ENABLE_OFF();
            // time small amounts with ticks, large with uS
            if(RWD_Sleep_Period > MAX_TIMER5_TICKS)
                Delay_us(CONVERT_TICKS_TO_US(RWD_Sleep_Period));
            else
            {
                WriteTimer5(0);
                while(GetTimer_ticks(NO_RESET) < RWD_Sleep_Period)
                    ;
            }
            count= 0;
            RWD_State= RWD_STATE_WAKING;
            // restart clock only if we have a wake period
            if(RWD_Wake_Period)
                READER_CLOCK_ENABLE_ON();
            break;

        case RWD_STATE_WAKING:
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // leave coil running for wakeup period
            if(count == RWD_Wake_Period)
            {
                count= 0;
                if(*RWD_Command_ThisBit != '*')
                    RWD_State= RWD_STATE_START_SEND;
                else
                    RWD_State= RWD_STATE_ACTIVE;
            }
            else
                count++;
            break;

        case RWD_STATE_START_SEND:
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // send initial gap
            // stop modulation of coil and wait
            READER_CLOCK_ENABLE_OFF();
            // time small amounts with ticks, large with uS
            if(RWD_Gap_Period > MAX_TIMER5_TICKS)
                Delay_us(CONVERT_TICKS_TO_US(RWD_Gap_Period));
            else
            {
                WriteTimer5(0);
                while(GetTimer_ticks(NO_RESET) < RWD_Gap_Period)
                    ;
            }
            count= 0;
            RWD_State= RWD_STATE_SENDING_BIT;
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // restart clock
            READER_CLOCK_ENABLE_ON();
            break;

        case RWD_STATE_SENDING_BIT:
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // clock running for bit period, then wait for gap period
            if((*RWD_Command_ThisBit && count == RWD_One_Period) || (!*RWD_Command_ThisBit && count == RWD_Zero_Period))
            {
                // stop modulation of coil and wait
                READER_CLOCK_ENABLE_OFF();
                if(RWD_Gap_Period > MAX_TIMER5_TICKS)
                    Delay_us(CONVERT_TICKS_TO_US(RWD_Gap_Period));
                else
                {
                    WriteTimer5(0);
                    while(GetTimer_ticks(NO_RESET) < RWD_Gap_Period)
                        ;
                }
                ++RWD_Command_ThisBit;
                count= 0;
                if(*RWD_Command_ThisBit == '*')
                    RWD_State= RWD_STATE_POST_WAIT;
                else
                    RWD_State= RWD_STATE_SENDING_BIT;
                // restart clock
               READER_CLOCK_ENABLE_ON();
            }
            else
                count++;
            break;

        case RWD_STATE_POST_WAIT:
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // coil running for forced post-command wait period
            if(count == RWD_Post_Wait)
            {
                count= 0;
                RWD_State= RWD_STATE_ACTIVE;
            }
            else
                count++;
            break;

        default:
            break;
    }
}

// Emulate TAG ISR
// this ISR does the actual send of a '*' terminated bitstream
// mLED_Antenna is set during emulation, and can be used as a semaphore to detect emulation in progress
// note that the best resolution we can achieve on a pic32 seems to be 2us
//
// setup routine is responsible for:
//
//   setting clock period and arming interrupt
//   setting global variables:
//
//     EMU_ThisBit              - the next bit to output (as 0x00 or 0x01)
//     *EMU_Data                - pointer to array of 0x00/0x01 values, '*' terminated
//                                inital value should be &EMU_ThisBit + 1
//     *EMU_Reset_Data          - pointer to the complete data array
//     EMU_Repeat               - number of times to repeat full data pattern (0 means send once)
//     EMU_Invert               - Invert 0x00/0x01 values TRUE/FALSE
//     EMU_DataBitRate          - Frame Clocks Per Bit
//     EMU_SubCarrier_T0         - 1st sub-carrier Frame Clocks
//     EMU_SubCarrier_T1        - 2nd sub-carrier Frame Clocks
//     EMU_Manchester           - Manchester Encoding TRUE/FALSE
//     EMU_BiPhase              - BiPhase Encoding TRUE/FALSE
void __ISR(_TIMER_3_VECTOR, ipl7auto) emulation_send_bit (void)
{
    static unsigned int count= 0;

    // ack interrupt
    mT3ClearIntFlag();

#ifdef RFIDLER_DEBUG
    // show bit value
    //DEBUG_PIN_1= EMU_ThisBit;

    // show tick
    //DEBUG_PIN_2= !DEBUG_PIN_2;
#endif

    // are we finished?
    if(EMU_ThisBit == '*')
    {
        if(!EMU_Background && !(EMU_Repeat--))
        {
            CloseTimer3();
            mLED_Emulate_Off();
            count= 0;
            COIL_OUT= 0;
            return;
        }
        // repeat
        EMU_Data= EMU_Reset_Data;
        EMU_ThisBit= *(EMU_Data++);
        count= 0;
    }

    // count reflects the FC we are about to process, starting from 1
    // so we can calulate bit periods and sub-carriers.
    // count should be reset after each full bit.
    ++count;

    // output and set up bit for next tick
    switch(EmulationMode)
    {
        // ASK / OOK - we get called once per bit just toggle the line according to bit value
        //
        // MANCHESTER/BI_PHASE - we get called twice per bit, half-bit toggles
        //
        case MOD_MODE_ASK_OOK:
            // output half-bit? manchester always toggles, biphase only toggles if it's a 1
            if(count == EMU_SubCarrier_T0 && (RFIDlerConfig.Manchester || (RFIDlerConfig.BiPhase && (EMU_ThisBit ^ RFIDlerConfig.Invert))))
                COIL_OUT= !COIL_OUT;
            // output current bit
            else
            {
                // biphase always toggles on a full bit period
                if(RFIDlerConfig.BiPhase)
                {
                    if (count % EMU_DataBitRate)
                    COIL_OUT= !COIL_OUT;
                }
                else
                    COIL_OUT= (EMU_ThisBit ^ RFIDlerConfig.Invert);
            }
            // is this a bit period?
            if (count == EMU_DataBitRate)
            {
                // set the next bit value
                EMU_ThisBit= *(EMU_Data++);
                count= 0;
            }
            break;

        // FSK - we get called N times per bit
        // create sub-carriers T0 & T1 for bit values 0 and 1
        // e.g. if bit period N is 40 ticks (RF/40) and T0 is RF/8 and T1 is RF/5
        // then T0 is 8 ticks and T1 is 5 ticks.
        // note that we must independantly check for end of bit period for each sub-carrier
        // to cater for cases where there is no common clock multiple (e.g. HID: RF/8 & RF/10)
        case MOD_MODE_FSK1:
        case MOD_MODE_FSK2:
            // output sub-carriers
            // if current bit is a '1'
            if(EMU_ThisBit ^ RFIDlerConfig.Invert)
            {
                if(!(count % EMU_SubCarrier_T1))
                    COIL_OUT= !COIL_OUT;
                // rounded bit period?
                if (!(count % ((EMU_DataBitRate / EMU_SubCarrier_T1) * EMU_SubCarrier_T1)))
                {
                    // set the next bit value
                    EMU_ThisBit= *(EMU_Data++);
                    count= 0;
                }
            }
            // if current bit is a '0'
            else
            {
                if(!(count % EMU_SubCarrier_T0))
                    COIL_OUT= !COIL_OUT;
                // rounded bit period?
                if (!(count % ((EMU_DataBitRate / EMU_SubCarrier_T0) * EMU_SubCarrier_T0)))
                {
                    // set the next bit value
                    EMU_ThisBit= *(EMU_Data++);
                    count= 0;
                }
            }
            break;

        // TODO: PSK2, PSK3
        // PSK1 - we get called N times per bit
        // create sub-carrier
        // half-bit phase shift if bit changes
        case MOD_MODE_PSK1:
            // output sub-carrier?
            if(!(count % EMU_SubCarrier_T0))
                COIL_OUT= !COIL_OUT;
            // output current bit
            else
                COIL_OUT= (EMU_ThisBit ^ RFIDlerConfig.Invert);
            // is this is a bit period?
            if (count == EMU_DataBitRate)
            {
                // set the next bit value
                EMU_ThisBit= *(EMU_Data++);
                count= 0;
            }
            break;

        default:
            break;
    }
//#ifdef RFIDLER_DEBUG
//    // show modulator
//    DEBUG_PIN_3= COIL_OUT;
//#endif
}

// DATA reading ISR
void __ISR(_TIMER_4_VECTOR, ipl7auto) HW_read_bit(void)
{
    static unsigned long count= 0L;
    unsigned int time;
    static char out, previous= -1;
    BYTE i, *p;
    BOOL fskread= FALSE;

    // show trigger moment (you must also set end of routine debugger statement)
    DEBUG_PIN_1= HIGH;

    // reset interrupt
    mT4ClearIntFlag();

    // toggle bit period flag for analogue sampler
    ReaderPeriod= !ReaderPeriod;

    if(FakeRead)
        return;


    // don't do anything unless we've got data to read - we may have been left running due to higher level error.
    if(!HW_Bits)
    {
        stop_HW_reader_ISR();
        return;
    }

    // some tags lead a read with a fixed bit pattern that do not form part of the data, so skip if required (e.g. T5567)
    if(HW_Skip_Bits)
    {
        --HW_Skip_Bits;
        return;
    }
    DEBUG_PIN_1= LOW;

    // debugging - monitor with a logic analyser
    // show read period
    DEBUG_PIN_2= HIGH;

    // show data value
    //DEBUG_PIN_3= READER_DATA;

    switch(RFIDlerConfig.Modulation)
    {
        case MOD_MODE_ASK_OOK:

            // get current bit value
            out= READER_DATA;

            // check for manchester encoding sync/errors
            if(RFIDlerConfig.Manchester && count)
            {
                // the 2nd half bit may not be equal to the 1st
                // this error is allowed to occur exactly once, in which case we
                // are out of sync so we slip timing by half a bit
                if(count % 2 && out == previous)
                {
                    //DEBUG_PIN_4= !DEBUG_PIN_4;
                    // error LED on
                    mLED_Error_On();
                    if(Manchester_Error)
                    {
                        //DEBUG_PIN_4= !DEBUG_PIN_4;
                        // 2 strikes and we fail!
                        count= 0L;
                        previous= -1;
                        Manchester_Auto_Correct= FALSE;
                        stop_HW_reader_ISR();
                        return;
                    }
                    else
                    {
                        //DEBUG_PIN_4= !DEBUG_PIN_4;
                        // 1st error - reset data and start again, now offset by a half bit.
                        Manchester_Error= TRUE;
                        //DEBUG_PIN_2= LOW;

                        // special case - if tag can start with a '0' (i.e. there is no initial '1' as a sync
                        // bit, it will look like a 1/2 bit error, but we may only detect the error later on,
                        // so we must correct all the previous mis-reads, offset the count by 1/2 a bit and
                        // complete this read
                        if(Manchester_Auto_Correct && count != 1)
                        {
                            for(i= 0, p= EMU_Data ; i <= count / 2L ; ++i, --p)
                                *p= !*(p);
                            --count;
                        }
                        else
                        {
                            EMU_Data -= (count / 2L);
                            count= 1L;
                            // successful read resets timeout
                            WriteTimer5(0);
                            return;
                        }
                    }
                }
            }
            
            // now set data bit

            // biphase is 1 if mid-bit change or 0 if no mid-bit change
            if(RFIDlerConfig.BiPhase && count % 2L)
            {
                if(previous == out)
                    *(EMU_Data++)= 0x00 ^ RFIDlerConfig.Invert;
                else
                    *(EMU_Data++)= 0x01 ^ RFIDlerConfig.Invert;
               //DEBUG_PIN_1= *(EMU_Data - 1);
               // successful read resets timeout
               WriteTimer5(0);
            }

            // read data direct for normal ASK
            if(!RFIDlerConfig.Manchester && !RFIDlerConfig.BiPhase)
            {
                //DEBUG_PIN_1= out;
                *(EMU_Data++)= out ^ RFIDlerConfig.Invert;
                // successful read resets timeout
                WriteTimer5(0);
            }

            // read only 2nd half of bit if manchester
            if (RFIDlerConfig.Manchester && count % 2L)
            {
                //DEBUG_PIN_1= out;
                // always invert as we are now reading 2nd half bit, so opposite value
                *(EMU_Data++)= !(out ^ RFIDlerConfig.Invert);
                // successful read resets timeout
                WriteTimer5(0);
            }

            previous= out;

            break;

        case MOD_MODE_FSK1:
        case MOD_MODE_FSK2:
            // to read FSK we will measure a pulse width. we must stop before end of bit period so we don't
            // get caught by the next interrupt. accordingly our time period is shortened by 20%, but
            // that should be OK as we only need to see a single pulse.
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            //time= CONVERT_TO_TICKS(RFIDlerConfig.FrameClock * (RFIDlerConfig.DataRate - (RFIDlerConfig.DataRate / 5)));
            time= RFIDlerConfig.FrameClock * (RFIDlerConfig.DataRate - (RFIDlerConfig.DataRate / 5));
            GetTimer_us(RESET);
            // measure 2nd pulse
            while(GetTimer_us(NO_RESET) < time && !fskread)
            {
              fskread= TRUE;
              //DEBUG_PIN_4= !DEBUG_PIN_4;
                // skip to first pulse
              while(READER_DATA)
                    if(GetTimer_us(NO_RESET) > time)
                    {
                        fskread= FALSE;
                        break;
                    }
                while(!READER_DATA)
                    if(GetTimer_us(NO_RESET) > time)
                    {
                        fskread= FALSE;
                        break;
                    }
                // skip first pulse
                while(READER_DATA)
                    if(GetTimer_us(NO_RESET) > time)
                    {
                        fskread= FALSE;
                        break;
                    }
                while(!READER_DATA)
                    if(GetTimer_us(NO_RESET) > time)
                    {
                        fskread= FALSE;
                        break;
                    }
                // measure second pulse
                GetTimer_us(RESET);
                //DEBUG_PIN_4= !DEBUG_PIN_4;
                while(READER_DATA)
                    if(GetTimer_us(NO_RESET) > time)
                    {
                        fskread= FALSE;
                        break;
                    }
            }
            //DEBUG_PIN_4= !DEBUG_PIN_4;
            // successful read resets timeout
            if(fskread)
                *(EMU_Data++)= GetTimer_us(RESET); // get pulsewidth in uS
            break;

        // TODO: PSK2, PSK3
        case MOD_MODE_PSK1:
            // READER_DATA goes high when a phase change occurs
            // we toggle bit value on phase change

            // data line should go high at start of bit period, but to allow for some lag
            // we will wait for up to a full frame clock just to be sure
            time= CONVERT_TO_TICKS(RFIDlerConfig.FrameClock);
            WriteTimer5(0);
            while(ReadTimer5() < time)
                if(READER_DATA)
                    break;

            // show toggle output
            //DEBUG_PIN_1 ^= READER_DATA;

            // get data
            out ^= (READER_DATA ^ RFIDlerConfig.Invert);

            // test read quality - pulsewidth wil be short if tag not correctly coupled
            if(PSK_Min_Pulse && READER_DATA)
            {
                // fast reset timer
                WriteTimer5(0);
                //DEBUG_PIN_1 ^= 1;
                while(READER_DATA)
                    ;
                time= GetTimer_us(NO_RESET);
                if(time < PSK_Min_Pulse)
                    PSK_Read_Error= 1;
                //DEBUG_PIN_1 ^= 1;
            }

            *(EMU_Data++)= out;
            // successful read resets timeout
            WriteTimer5(0);
            break;
            
        default:
            break;
    }

    ++count;

    // debugging - reset output line
    DEBUG_PIN_2= LOW;

    // finished?
    if(count == HW_Bits)
    {
        HW_Bits= count= 0L;
        previous= -1;
        // if only 1 manchester error caught, that's OK
        Manchester_Error= FALSE;
        // caller must reset this to use again
        Manchester_Auto_Correct= FALSE;
        mLED_Error_Off();
        // stop reading, but leave clock running to preserve tag state - higher level will shut down when done
        stop_HW_reader_ISR();
    }
}

// end optimisation
#pragma GCC reset_options
