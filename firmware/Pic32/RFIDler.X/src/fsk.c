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
#include "USB/usb.h"
#include "util.h"
#include "fsk.h"
#include "emulate.h"
#include "clock.h"

BOOL send_fsk_hex(unsigned char *data, unsigned long pulsewidth, unsigned int cpb, unsigned int c0, unsigned int c1, unsigned int repeat)
{
    unsigned int length;

    if(!(length= hextobinarray(TmpBits, data)))
        return 0;
    // manchester encoding with FSK is not done in the baseband, so pre-encode
    if(RFIDlerConfig.Manchester)
        length= manchester_encode(TmpBits, TmpBits, length);
    return send_fsk_bin(TmpBits, length, pulsewidth, cpb, c0, c1, repeat);
}

BOOL send_fsk_bin(unsigned char *data, unsigned int length, unsigned long pulsewidth, unsigned int cpb, unsigned int c0, unsigned int c1, unsigned int repeat)
{
    // terminate for transmission
    memcpy(TmpBits, data, length);
    TmpBits[length]= '*';
    // note we convert clocks (period) to ticks
    write_FSK_HW_clock(pulsewidth / 2L, TmpBits, cpb * 2, c0, c1, repeat);
    return TRUE;
}

// h/w clock FSK emulator - initialise data pointers for ISR and start timer 2
// args: clock pulsewidth (NOT period!), data as array of 0/1, T0 sub-carrier ticks, T1 sub-carrier ticks, repeat
void write_FSK_HW_clock(unsigned long pulse, BYTE *data, unsigned int tpb, unsigned int t0, unsigned int t1, unsigned int repeat)
{
    // convert to ticks
    pulse= CONVERT_TO_TICKS(pulse);

    // point globals at data for ISR
    EMU_ThisBit= *data;
    EMU_Data= data + 1;
    EMU_Reset_Data= data;
    EMU_Repeat= repeat;
    EMU_DataBitRate= tpb;
    EMU_SubCarrier_T0= t0;
    EMU_SubCarrier_T1= t1;

    // set mode (any FSK mode will do, as sub-carriers are set seperately)
    EmulationMode= MOD_MODE_FSK1;

    // make sure no clock is running
    stop_HW_clock();

    // make sure nobody's using our timer
    CloseTimer3();

    // emulator mode
    COIL_MODE_EMULATOR();

    // tri-state on, clock low
    READER_CLOCK_ENABLE_ON();
    CLOCK_COIL= LOW;

    // this is also a semaphore so the rest of the code knows we're running
    mLED_Emulate_On();

    // start timer - ISR will send data
    OpenTimer3( T3_ON | T3_PS_1_1 | T3_SOURCE_INT, pulse - 1L);
    mT3SetIntPriority(6);
    mT3ClearIntFlag();
    mT3IntEnable(TRUE);
}


// return raw HEX UID
BOOL fsk_raw_get_uid(BYTE *response)
{
    unsigned int i;
    BOOL blank= TRUE;
    BYTE tmp[MAXUID + 1];

    memset(tmp, '0', MAXUID);
    tmp[MAXUID]= '\0';
    
    if (read_fsk_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, RFIDlerConfig.DataRateSub0, RFIDlerConfig.DataRateSub1, tmp, RFIDlerConfig.DataBits, RFIDlerConfig.Invert, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, FALSE, HEX) != RFIDlerConfig.DataBits)
        return FALSE;
    
    for(i= 0 ; i < strlen(tmp) ; ++i)
        if(tmp[i] != '0')
            blank= FALSE;
    if (blank)
        return FALSE;

    strcpy(response, tmp);
    return TRUE;
}

// specify oneshot if data is not repeated (i.e. in response to a command rather than a cycling UID)
unsigned int read_fsk_data(unsigned int period_us, unsigned int ticks, unsigned int t0_ticks, unsigned int t1_ticks, BYTE *data, unsigned int bits, BOOL invert, unsigned char *sync, unsigned char syncbits, unsigned int timeout_us, BOOL oneshot, BYTE format)
{
    unsigned int i, j;
    BYTE found= 0, repeat;

    if(oneshot)
        repeat= 1;
    else
        repeat= 2;

    // if we're not doing a 1-shot read, we can grab double the data to allow for sync search
    if(!read_FSK_HW_clock(period_us, ticks, TmpBits, bits * repeat, timeout_us))
        return 0;

    if(FakeRead)
        return 0;

    // reset timer
    if(timeout_us)
        GetTimer_us(RESET);

    // wait for semaphore to tell us read has finished
    while(mLED_Read == mLED_ON)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return 0;

    // convert to standard binary
    if(!fskbinarraytobinarray(TmpBits, TmpBits, bits * repeat, (t0_ticks > t1_ticks) ^ invert))
        return 0;

    // find start of data
    if(syncbits)
    {
        for(i= j= found= 0 ; i < bits * repeat ; ++i)
        {
            if(TmpBits[i] == getbit(sync[j / 8], 7 - (j % 8)))
                ++j;
            else
            {
                i -= j;
                j= 0;
            }

            if(j == syncbits)
            {
                found= 1;
                break;
            }
        }
        if(!found)
            return 0;
    }

    // point at start of sync
    if(syncbits)
        i -= syncbits - 1;
    else
        i= 0;

    // copy to output buffer
    switch(format)
    {
        case HEX:
            return binarraytohex(data, TmpBits + i, bits);

        case BINARY:
        default:
            memcpy(data, TmpBits + i, bits);
            data[bits]= '\0';
            return bits;
    }
}

// nothing to do!
BOOL fsk_raw_hex_to_uid(BYTE *response, BYTE *hex)
{
    strcpy(response, hex);
    return TRUE;
}


// low level read routines

// h/w clock reader - initialise data pointers for ISR and start timers
// timer2 creates clock output for external reader
// timer4 reads data bit values
// period_us == clock for reader
// ticks == clock periods per bit
// bits == number of bits to read
// min_pulse_us == minimum external reader pulswidth for a 'good' read, 0 for read 'anything'

BOOL read_FSK_HW_clock(unsigned int period, unsigned int ticks, BYTE *data, unsigned int bits, unsigned int timeout_us)
{
    unsigned int gaplength;

    // point globals at data for ISR
    EMU_Data= data;
    HW_Bits= bits;

    memset(EMU_Data, '\0', bits);

    // stop USB interfering
    USBMaskInterrupts();

    // start clock if not already running
    if(!mGetLED_Clock() == mLED_ON)
    {
        InitHWReaderClock(OC_TOGGLE_PULSE, period / 2L, period, RWD_STATE_ACTIVE);

        // give reader time to wake up and settle
        Delay_us((RFIDlerConfig.FrameClock * RFIDlerConfig.RWD_Wake_Period) / 100);
    }

    // reset timer for timeout
    GetTimer_us(RESET);

    // align ourselves to reader's bit period by finding the end of a pulse train.
    // we can do this by measuring the gaps. when they become significantly different
    // sized (more than 25%), we have just switched frequency.

    // find the start of a pulse
    while(READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return FALSE;
    while(!READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return FALSE;
    while(READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return FALSE;

    // reset timer so we can meausure gap period
    GetTimer_us(RESET);
    while(!READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return FALSE;
    gaplength= GetTimer_us(RESET);
    
    // now look for a gap that doesn't match
    while(42)
    {
        while(READER_DATA)
            if(timeout_us)
                if (GetTimer_us(NO_RESET) > timeout_us)
                    return FALSE;
        GetTimer_us(TRUE);
        while(!READER_DATA)
            if(timeout_us)
                if (GetTimer_us(NO_RESET) > timeout_us)
                    return FALSE;
        if(!approx(GetTimer_us(NO_RESET), gaplength, FSK_TOLERANCE))
            break;
    }

    // reset timer for external timeouts
    GetTimer_us(RESET);

    // start ISR to read FSK data
    InitHWReaderISR(CONVERT_TO_TICKS(period) * ticks - 1L, TRUE);

    return TRUE;
}

// convert special case fsk bin array to standard bin array
// this is an array of sizes. there should be only two values (approximate), one for '0' and one for '1'
// the lower of the two values is '0' - calling routine should decide if this is correct, and set 'invert' to switch
// if required
BOOL fskbinarraytobinarray(unsigned char *target, unsigned char *source, unsigned int length, BOOL invert)
{
    unsigned int i;
    unsigned char val0= 0, val1= 0;
    BYTE percentage= FSK_TOLERANCE;

    val0= source[0];

    // check we only have two values
    for(i= 1 ; i < length ; ++i)
    {
        if(!val1 && !approx(source[i], val0, percentage))
            val1= source[i];
        if(!approx(source[i], val0, percentage) && !approx(source[i], val1, percentage))
            return FALSE;
    }

    // lower value (smaller pulses, so higher frequency) is '0', so swap if not set that way
    if((val1 < val0) ^ invert)
        val0= val1;

    for(i= 0 ; i < length ; ++i)
        if(approx(source[i], val0, percentage))
            target[i]= 0x00;
        else
            target[i]= 0x01;

    return TRUE;
}
