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

// psk functions
// PSK1 - Phase change signals bit value change


#include "HardwareProfile.h"
#include "rfidler.h"
#include "psk.h"
#include "emulate.h"
#include "USB/usb.h"
#include "clock.h"

// high level routines



// read a PSK1 bitstream and find start of data
//
// parameters:
//
//   period_us    - clock period in uS
//   ticks        - clock periods per bit
//   data         - buffer for final data [no. of bits])
//   bits         - no. of bits to read (always specify in bits, not bytes)
//   leadin       - no. of leading '0' bits
//   bytes        - if set, return data as bytes, otherwise bits
//   timeout_us   - timeout in uS, 0 for blocking
//   min_pulse_us - mininum pulse width from external reader for 'good' read. 0 for read anything.
//
// return:
//
//   data will be filled with one byte per bit (value 0x00 or 0x01)
//   return will be 0 if leadin not found, or no. of BITS read
// specify oneshot if data is not repeated (i.e. in response to a command rather than a cycling UID)
unsigned int read_psk1_data(unsigned int period_us, unsigned int ticks, BYTE *data, unsigned int bits, unsigned char *sync, unsigned char syncbits, unsigned int timeout_us, unsigned int min_pulse_us, BOOL oneshot, BYTE format)
{
    unsigned int i= 0, j;
    BYTE found= 0, inverted= 0, repeat;

   if(oneshot)
        repeat= 1;
    else
        repeat= 2;

    // if we're not doing a 1-shot read, we can grab double the data to allow for sync search
    read_PSK1_HW_clock(period_us, ticks, TmpBits, bits * repeat, timeout_us, min_pulse_us);

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

    if(PSK_Read_Error)
        return 0;

    // find start of data
    while(syncbits)
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

        // point at start of sync
        i -= syncbits - 1;

        if(found)
            break;
        if(inverted)
            return 0;
        // with PSK we have no way of knowing if 1st bit was a 0 or 1, so invert data and try again
        inverted= 1;
        for(i= 0 ; i < bits * repeat ; ++i)
            TmpBits[i] ^= 1;
    }

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

BOOL send_psk1_hex(unsigned char *data, unsigned int pulsewidth, unsigned int tpb, unsigned int c0, unsigned int repeat)
{
    unsigned int length;
    BYTE tmp[256];

    if(!(length= hextobinarray(tmp, data)))
        return FALSE;

    return send_psk1_bin(tmp, length, pulsewidth, tpb, c0, repeat);
}

BOOL send_psk1_bin(unsigned char *data, unsigned int length, unsigned int pulsewidth, unsigned int tpb, unsigned int c0, unsigned int repeat)
{
    BYTE tmp[512];

    // manchester encoding with PSK is not done in the baseband, so pre-encode
    if(RFIDlerConfig.Manchester)
        length= manchester_encode(tmp, data, length);
    else
        memcpy(tmp, data, length);

    tmp[length]= '*';
    write_PSK1_HW_clock(pulsewidth, tmp, tpb, c0, repeat);
    return TRUE;
}

// low level write routines

// h/w clock PSK emulator - initialise data pointers for ISR and start timer 2
// args: clock period, data as array of 0/1, fc per bit, sub-carrier ticks, repeat
void write_PSK1_HW_clock(unsigned int period, BYTE *data, unsigned int fcpb, unsigned int c0, unsigned int repeat)
{
    // convert to ticks
    period= CONVERT_TO_TICKS(period);
    // for psk we want a full clock cycle, not a tick
    period *= 2;

    // point globals at data for ISR
    EMU_ThisBit= *data;
    EMU_Data= data + 1;
    EMU_Reset_Data= data;
    EMU_DataBitRate= fcpb;
    EMU_SubCarrier_T0= c0;
    EMU_Repeat= repeat;

    // set mode
    EmulationMode= MOD_MODE_PSK1;

    // make sure no clock is running
    stop_HW_clock();

    // make sure nobody's using our timers
    CloseTimer3();

    // tri-state on, clock low
    READER_CLOCK_ENABLE_ON();
    CLOCK_COIL= LOW;

    // emulator mode
    COIL_MODE_EMULATOR();

    // this is also a semaphore so the rest of the code knows we're running
    mLED_Emulate_On();

    // start timer - ISR will send data
    OpenTimer3( T3_ON | T3_PS_1_1 | T3_SOURCE_INT, period / 2L - 1L);
    mT3SetIntPriority(6);
    mT3ClearIntFlag();
    mT3IntEnable(TRUE);
}

// low level read routines

// h/w clock reader - initialise data pointers for ISR and start timers
// timer2 creates clock output for external reader
// timer4 reads data bit values
// period_us == clock for reader
// ticks == clock periods per bit
// bits == number of bits to read
// min_pulse_us == minimum external reader pulswidth for a 'good' read, 0 for read 'anything'

void read_PSK1_HW_clock(unsigned int period, unsigned int ticks, BYTE *data, unsigned int bits, unsigned int timeout_us, unsigned int min_pulse_us)
{
    // point globals at data for ISR
    EMU_Data= data;
    HW_Bits= bits;
    PSK_Min_Pulse= min_pulse_us;
    PSK_Read_Error= FALSE;

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

    // align ourselves to reader's bit period by finding start of a pulse
    while(READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return;
    while(!READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return;
        
    // reset timer for external timeouts
    GetTimer_us(RESET);

    // start ISR to read PSK data
    InitHWReaderISR(CONVERT_TO_TICKS(period) * ticks - 1L, TRUE);
}

BOOL psk1_raw_get_uid(BYTE *response)
{
    unsigned int i;
    BYTE tmp[MAXUID + 1];
    BOOL blank= TRUE;

    memset(tmp, '0', MAXUID);
    tmp[MAXUID]= '\0';

    if(!read_psk1_data(RFIDlerConfig.FrameClock, RFIDlerConfig.DataRate, tmp, RFIDlerConfig.DataBits, RFIDlerConfig.Sync, RFIDlerConfig.SyncBits, RFIDlerConfig.Timeout, RFIDlerConfig.PSK_Quality, FALSE, HEX) == RFIDlerConfig.DataBits)
        return FALSE;

    for(i= 0 ; i < strlen(tmp) ; ++i)
        if(tmp[i] != '0')
            blank= FALSE;

    if(blank)
        return FALSE;

    strcpy(response, tmp);
    return TRUE;
}

// resturn interpreted UID
BOOL psk1_raw_hex_to_uid(BYTE *response, BYTE *hex)
{
    if(!strlen(hex))
        return FALSE;

    strcpy(response, hex);
    return TRUE;
}
