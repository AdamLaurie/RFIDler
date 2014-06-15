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

// note this needs fixing to co-exist with RFID coil timers

#include "HardwareProfile.h"

#define SYS_FREQ    GetSystemClock()
//#define SYS_FREQ 64000000UL

// Note : FCY denotes the instruction cycle clock frequency (SYS_FREQ/2)"
//#define FCY GetInstructionClock()
#define FCY (SYS_FREQ)

#include "p32xxxx.h"

// Enable Port Pin of Micro as Vcc for Smart Card
#define  ENABLE_SC_POWER_THROUGH_PORT_PIN

// Set Clock Freq to drive Smart Card - we want 4MHz
#define Scdrv_ClockSet()            (TMR2 = 0, T2CON = T2_SOURCE_INT | T2_32BIT_MODE_OFF | T2_PS_1_1, PR2 = 19, OC2R = 10, OC2RS= 10, TRISDbits.TRISD1 = 0, OC2CON = OC_PWM_FAULT_PIN_DISABLE | OC_TIMER2_SRC | OC_TIMER_MODE16)

//Enable UART
#define SCdrv_EnableUART()	    	(U1MODEbits.UARTEN = 1)

// Enable Clock to drive Smart Card
#define SCdrv_EnableClock()	    	(OC2CONbits.ON = 1,T2CONbits.ON = 1)

// Disable Clock used to drive Smart Card
#define SCdrv_DisableClock()	    (OC2CONbits.ON = 0,T2CONbits.ON = 0,TMR2 = 0)

// Set Clock Freq to drive Smart Card
#define SCdrv_EnableDelayTimerIntr()   (IPC1bits.T1IP = 3,IPC1bits.T1IS = 1,IFS0bits.T1IF = 0,T1CON = 0x0030,PR1 = 0xFFFF,IEC0bits.T1IE = 1,INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR),INTEnableInterrupts())

// One count of timer 1 corresponds to how much micro seconds...
#define TIMER1_SINGLE_COUNT_MICRO_SECONDS	(BYTE)(256/(FCY/1000000UL))

// Enable Clock to drive Smart Card
#define SCdrv_SetDelayTimerCnt(count)	    (TMR1 = count)

// Enable Clock to drive Smart Card
#define SCdrv_EnableDelayTimer()	    	(T1CONbits.TON = 1)

// Disable Clock used to drive Smart Card
#define SCdrv_DisableDelayTimer()	    	(T1CONbits.TON = 0)

//Reference Clock Circuit - Input Clock
#define REF_CLOCK_CIRCUIT_INPUT_CLK    		FCY

//Reference Clock Circuit - Input Clock
#define REF_CLOCK_POWER2_VALUE      		(BYTE)0

//Reference Clock Circuit - Input Clock
#define REF_CLOCK_DIVISOR_VALUE      		(BYTE)PR2

// Frequency of clock given to smart card
#define REF_CLOCK_TO_SMART_CARD				(unsigned long)(FCY/(PR2 + 1))

//Turn on 1/off 0 card power
#define SCdrv_SetSwitchCardPower(x) 			(LATBbits.LATB9=(x))

//set reset state to the value x
#define SCdrv_SetSwitchCardReset(x) 			(LATEbits.LATE8=(x))

//set tx pin to the value x
#define SCdrv_SetTxPinData(x) 					(LATFbits.LATF8=(x))

//Get Smart Card Present status
//#define SCdrv_CardPresent()	      				(PORTBbits.RB0 || !PORTBbits.RB1)
// we don't have a microswitch, so always present
#define SCdrv_CardPresent()                             (TRUE)

//Get Rx Pin Data
#define SCdrv_GetRxPinData()               		(PORTFbits.RF2)

//Set Tx Pin direction
#define SCdrv_TxPin_Direction(flag)    			(TRISFbits.TRISF8 = flag)

//Set Power Pin direction connected to the smart card
#define SCdrv_PowerPin_Direction(flag) 			(TRISBbits.TRISB9 = flag)

//Set Reset Pin direction connected to the smart card
#define SCdrv_ResetPin_Direction(flag) 			(TRISEbits.TRISE8 = flag)

//Set Card Present Pin direction connected to the smart card
//#define SCdrv_CardPresent_Direction(flag) 		(TRISBbits.TRISB0 = flag)
#define SCdrv_CardPresent_Direction(flag)

//Set Sim Present Pin direction connected to the smart card
//#define SCdrv_SimPresent_Direction(flag) 		(TRISBbits.TRISB1 = flag)
#define SCdrv_SimPresent_Direction(flag)

// Enable Pull up at Tx Pin
#define SCdrv_EnableTxPinPullUp()

// Enable Pull up at Rx Pin
#define SCdrv_EnableRxPinPullUp()

// Enable Pull up for SMART_CARD_DETECTION
//#define SCdrv_EnableCardPresentPinPullUp()		(CNPUEbits.CNPUE2 = 1)
#define SCdrv_EnableCardPresentPinPullUp()

// Enable Pull up for SIM_CARD_DETECTION
//#define SCdrv_EnableSimPresentPinPullUp()		(CNPUEbits.CNPUE3 = 1)
#define SCdrv_EnableSimPresentPinPullUp()

// Disable Pull up at Tx Pin
#define SCdrv_DisableTxPinPullUp()

// Disable Pull up at Rx Pin
#define SCdrv_DisableRxPinPullUp()

// MAP UART Rx Pin
#define MapUART1RxPin()

// MAP UART Tx Pin
#define MapUART1TxPin()

