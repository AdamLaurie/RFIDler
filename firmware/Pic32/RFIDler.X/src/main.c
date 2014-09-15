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

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "USB/usb.h"
#include "USB/usb_device.h"
#include "USB/usb_function_cdc.h"

#include "uart3.h"

#include "rfidler.h"
#include "indala.h"
#include "ask.h"
#include "emulate.h"
#include "clock.h"
#include "rwd.h"
#include "detect.h"
#include "hitagcrypto.h"
#include "comms.h"
#include "tags.h"
#include "util.h"
#include "auto.h"
#include "uid.h"
#include "login.h"
#include "auth.h"
#include "q5.h"
#include "vtag.h"
#include "sc_config.h"
#include "wiegand.h"
#include "analogue.h"
#include "iso_7816.h"
#include "write.h"

// low level config
#pragma config CP       = ON           // Code Protect
#pragma config BWP      = ON           // Boot Flash Write Protect
#pragma config PWP      = OFF          // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2     // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF          // Background Debugger Disable (interferes with bootloader)

//globals
BYTE Comms_In_Buffer[COMMS_BUFFER_SIZE];
BYTE Comms_Out_Buffer[COMMS_BUFFER_SIZE];
VirtualTag RFIDlerVTag;          // semi-permanent TAG data
StoredConfig RFIDlerConfig;
BYTE EmulationMode= MOD_MODE_NONE;
BOOL SnifferMode= FALSE;
BOOL WiegandOutput= FALSE;
BYTE             *EMU_Reset_Data;               // Pointer to full array of bits, stored one bit per byte, '*' terminated
BYTE             *EMU_Data;                     // Pointer to current location in EMU_Reset_Data
BYTE             EMU_ThisBit;                   // The next data bit to transmit
BYTE             EMU_SubCarrier_T0;             // Number of Frame Clocks for sub-carrier '0'
BYTE             EMU_SubCarrier_T1;             // Number of Frame Clocks for sub-carrier '1'
unsigned int     EMU_Repeat;                    // Number of times to transmit full data set
BOOL             EMU_Background= FALSE;         // Emulate in the background until told to stop
unsigned int     EMU_DataBitRate;               // Number of Frame Clocks per bit
BYTE             TmpBits[TMP_LARGE_BUFF_LEN];   // Shared scratchpad
BYTE             ReaderPeriod= FALSE;           // reder period flag for analogue display - toggled by reader ISR
BOOL             FakeRead= FALSE;               // flag for analogue sampler to signal it wants access to buffers during read
BOOL             PWD_Mode= FALSE;               // is this tag password protected?
BYTE Password[9]= {0, 0, 0, 0, 0, 0, 0, 0, 0};  // 32 bits as HEX string set with LOGIN

// globals for RWD commands
BYTE             RWD_State= RWD_STATE_INACTIVE;
unsigned long    RWD_Fc= 0;                                     // field clock in uS
unsigned long    RWD_Gap_Period= 0;                             // length of command gaps in SYSTEM ticks
unsigned int     RWD_Zero_Period= 0;                            // length of '0' in OC5 ticks
unsigned int     RWD_One_Period= 0;                             // length of '1' in OC5 ticks
unsigned long    RWD_Sleep_Period= 0;                           // length of initial sleep to reset tag in uS
unsigned int     RWD_Wake_Period= 0;                            // length required for tag to restart OC5 ticks
unsigned int     RWD_Wait_Switch_TX_RX= 0;                      // length to wait when switching from TX to RX in OC5 ticks
unsigned int     RWD_Wait_Switch_RX_TX= 0;                      // length to wait when switching from RX to TX in OC5 ticks
unsigned int     RWD_Post_Wait= 0;                              // low level ISR wait period in OC5 ticks
unsigned int     RWD_OC5_config= 0;                             // Output Compare Module settings
unsigned int     RWD_OC5_r= 0;                                  // Output Compare Module primary compare value
unsigned int     RWD_OC5_rs= 0;                                 // Output Compare Module secondary compare value
BYTE             RWD_Command_Buff[TMP_SMALL_BUFF_LEN];          // Command buffer, array of bits as bytes, stored as 0x00/0x01, '*' terminated
BYTE             *RWD_Command_ThisBit= RWD_Command_Buff;        // Current command bit

BOOL stringPrinted;
volatile BOOL buttonPressed;
volatile BYTE buttonCount;

BYTE TmpBuff[NVM_PAGE_SIZE];  // we use this during page erase
BYTE DataBuff[ANALOGUE_BUFF_LEN]; // shared data buffer for external readers etc.
unsigned int DataBuffCount= 0;

BYTE Interface= INTERFACE_API;       // no menu/prompts by default
BYTE CommsChannel= COMMS_NONE;

const BYTE *OnOff[]= {
    "Off",
    "On"
};

const BYTE *HighLow[]= {
    "Low",
    "High"
};

/** P R I V A T E  P R O T O T Y P E S ***************************************/
static void InitializeSystem(void);
BYTE ProcessIO(void);
void USBCBSendResume(void);
void UserInit(void);
void parse_BL_packet(void);
BYTE ProcessSerialCommand(char *command);
unsigned int read_adc(void);
void slog(BYTE *message1, BYTE *message2);

// for bootloader
unsigned int * SoftwareKey = NULL;

int main(void)
{
    InitializeSystem();

    // execute autorun command
    if(*RFIDlerConfig.AutoRun)
    {
        mLED_User_On();
        ProcessSerialCommand(RFIDlerConfig.AutoRun);
        mLED_User_Off();
    }

    while(42)
    {
        if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE))
            USBDeviceAttach();

        // check for input
        ProcessIO();
    }//end while
}//end main


/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Nonechar
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{

    BYTE tmp;

    AD1PCFG = 0xFFFF;

    SYSTEMConfigPerformance(GetSystemClock());

    // timers
    // timer1 is used by SmartCard libs
    CloseTimer1();
    // timer2 is used by SmartCard and SD Card and rfidler clock routines for RFID carrier
    CloseTimer2();
    // timer4 is used by RFID reader ISR
    CloseTimer4();
    // FIXME: move timer 2 to timer 3 so clock can run concurrently with SD or smartcard
    // FIXME: convert timer45 to 16 bit so we can free up timer4
    //OpenTimer45(T45_ON | T45_SOURCE_INT | T45_PS_1_1, 0xFFFFFFFF);
    // timer5 is used for high level protocol timers that need uS. prescaler of 16 gives us up to 10,000 uS which is plenty
    // note that TIMER_PRESCALER must be set to match!
    OpenTimer5(T5_ON | T5_SOURCE_INT | T5_PS_1_16, 0xFFFFFFFF);
    // set to highest priority so our protocol timings are always accurate (use 6 or less everywhere else)
    // FIXME: this doesn't actually work - test by starting clock and doing 'timer-test'
    mT5SetIntPriority(7);

    USBDeviceInit();
    
    // make sure usb is up so we can log startup
#if defined(USB_INTERRUPT)
    if(USB_BUS_SENSE && (USBGetDeviceState() == DETACHED_STATE))
            USBDeviceAttach();
#endif
        
    // give USB time to attach etc.
    Delay_us(3000000);

    // load stored config
    loadconfig();

    UserInit();
}

void UserInit(void)
{
    unsigned int i, count;
    
    //Initialize all of the debouncing variables
    buttonCount = 0;
    buttonPressed = FALSE;
    stringPrinted = TRUE;

    // gpio
    Init_GPIO();

    // leds
    mLED_All_On();

    // uart
    UART3Init();

    // wiegand / clock & data
    wiegand_set_pullups(TRUE);

    // ISO 7816 SmartCard
    SC_Initialize();

    // coil in reader mode by default
    COIL_MODE_READER();

    // initalise ADC for rolling sample buffer
    //init_adc();

    // LCR
    LCR_CALIBRATE= LOW;

    //// RTC
    //// only enable this code if you've installed the 32.768KHz crystal at X2
    //// otherwise code will hang while waiting for clock to initialise
    //RtccOutputEnable(FALSE);
    //RtccInit();
    //while(RtccGetClkStat() != RTCC_CLK_ON)
    //    ;               
    //// set default time/date - Wednesday Jan 1st 2014, 00:00:01
    //RtccSetTimeDate(0x00000100, 0x14010103);

    mLED_All_Off();

    // auto-set initial tag type
    tag_set(RFIDlerConfig.TagType);
}


/********************************************************************
 * Function:        void ProcessIO(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
BYTE ProcessIO(void)
{   
    BYTE numBytesRead= 0, i;
    static BYTE commandbytes = 0;
    static BYTE command_buffer[COMMS_BUFFER_SIZE];
    static BYTE history[MAX_HISTORY][COMMS_BUFFER_SIZE], history_pos= 0, history_peak= 0, going_up= FALSE;

    //Blink the LEDs according to the comms device status
    BlinkCommsStatus();

    if(CommsChannel == COMMS_USB)
    {
        // User Application USB tasks
        if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1))
            return;

        if (mUSBUSARTIsTxTrfReady())
            numBytesRead= getsUSBUSART(Comms_In_Buffer, 64);
    }

    // check for serial input
    if (UART3IsPressed())
    {
        CommsChannel= COMMS_UART;
        numBytesRead= GetUART3Message(Comms_In_Buffer, SERIAL_TIMEOUT);
    }

    if (numBytesRead != 0)
    {
        for (i = 0; i < numBytesRead; i++)
        {
            switch (Comms_In_Buffer[i])
            {

                // backspace
                case 0x08:
                    numBytesRead= 0;
                    if(commandbytes == 0)
                    {
                        // beep
                        UserMessage("%s", "\a");
                        break;
                    }
                    // erase character
                    UserMessage("%s", "\b \b");
                    command_buffer[commandbytes--]= '\0';
                    break;

                // enter
                case 0x0A:
                case 0x0D:
                    command_buffer[commandbytes] = '\0';
                    going_up= FALSE;
                    // don't put empty commands in history
                    if(!strlen(command_buffer))
                        return ProcessSerialCommand(command_buffer);
                    // shuffle history down if we already reached and used the last entry
                    if(history_pos == MAX_HISTORY - 1 && strlen(&history[MAX_HISTORY - 1][0]))
                        for(i= 1 ; i < MAX_HISTORY ; ++i)
                            strcpy(&history[i - 1][0], &history[i][0]);
                    strcpy(&history[history_pos][0], command_buffer);
                    if(history_pos > history_peak)
                       history_peak= history_pos;
                    if(history_pos < MAX_HISTORY - 1)
                        history_pos++;
                    commandbytes = 0;
                    numBytesRead = 0;
                    return ProcessSerialCommand(command_buffer);
                    break;

                // TODO: fix history - memory corruption?
                // arrow key?
                case 0x1B:
                    // get the next two bytes, overwriting current byte - should be '[' + command
                    // fixme: make this work with serial input as well
                    if(CommsChannel == COMMS_USB)
                    {
                        while(!USBUSARTIsTxTrfReady())
                            CDCTxService();
                        while(!getsUSBUSART(Comms_In_Buffer, 2))
                            ;

                        if(Comms_In_Buffer[0] != '[')
                            break;
                    }

                    // always clear previous
                    while(commandbytes)
                    {
                        commandbytes--;
                        UserMessage("%s", "\b \b");
                    }
                    command_buffer[0]= '\0';
                    numBytesRead= 0;

                    // UP
                    if(Comms_In_Buffer[1] == 'A')
                    {
                        if(history_pos == 0)
                            UserMessage("%s", "\a");
                        else
                        {
                            // first time we hit up we should show current line, not decrement
                            if(going_up)
                                --history_pos;
                            else
                               going_up= TRUE;
                        }
                        strcpy(command_buffer, &history[history_pos][0]);
                    }

                    // DOWN
                    if(Comms_In_Buffer[1] == 'B')
                    {
                        going_up= FALSE;
                        if(history_pos > history_peak || history_pos == MAX_HISTORY - 1)
                            UserMessage("%s", "\a");
                        else
                            strcpy(command_buffer, &history[++history_pos][0]);
                    }

                    commandbytes= strlen(command_buffer);
                    UserMessage("%s", command_buffer);

                    break;
                     
                default:
                    if(commandbytes == TMP_SMALL_BUFF_LEN || Comms_In_Buffer[i] < ' ' ||  Comms_In_Buffer[i] > '~')
                    {
                        // beep
                        UserMessage("%s", "\a");
                        numBytesRead= 0;
                        break;
                    }
                    Comms_Out_Buffer[i] = command_buffer[commandbytes++] = Comms_In_Buffer[i];
                    break;
            }
        }

        if(Interface == INTERFACE_CLI)
        {
            Comms_Out_Buffer[numBytesRead]= '\0';
            UserMessage("%s", Comms_Out_Buffer);
        }
    }

    CDCTxService();
}		//end ProcessIO

/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckCDCRequest();
}//end



/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    //Enable the CDC data endpoints
    CDCInitEP();
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function will only be able to wake up the host if
 *                  all of the below are true:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *                  If the host has not armed the device to perform remote wakeup,
 *                  then this function will return without actually performing a
 *                  remote wakeup sequence.  This is the required behavior, 
 *                  as a USB device that has not been armed to perform remote 
 *                  wakeup must not drive remote wakeup signalling onto the bus;
 *                  doing so will cause USB compliance testing failure.
 *                  
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            This function does nothing and returns quickly, if the USB
 *                  bus and host are not in a suspended condition, or are 
 *                  otherwise not in a remote wakeup ready state.  Therefore, it
 *                  is safe to optionally call this function regularly, ex: 
 *                  anytime application stimulus occurs, as the function will
 *                  have no effect, until the bus really is in a state ready
 *                  to accept remote wakeup. 
 *
 *                  When this function executes, it may perform clock switching,
 *                  depending upon the application specific code in 
 *                  USBCBWakeFromSuspend().  This is needed, since the USB
 *                  bus will no longer be suspended by the time this function
 *                  returns.  Therefore, the USB module will need to be ready
 *                  to receive traffic from the host.
 *
 *                  The modifiable section in this routine may be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of ~3-15 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at least 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    //First verify that the host has armed us to perform remote wakeup.
    //It does this by sending a SET_FEATURE request to enable remote wakeup,
    //usually just before the host goes to standby mode (note: it will only
    //send this SET_FEATURE request if the configuration descriptor declares
    //the device as remote wakeup capable, AND, if the feature is enabled
    //on the host (ex: on Windows based hosts, in the device manager 
    //properties page for the USB device, power management tab, the 
    //"Allow this device to bring the computer out of standby." checkbox 
    //should be checked).
    if(USBGetRemoteWakeupStatus() == TRUE) 
    {
        //Verify that the USB bus is in fact suspended, before we send
        //remote wakeup signalling.
        if(USBIsBusSuspended() == TRUE)
        {
            USBMaskInterrupts();
            
            //Clock switch to settings consistent with normal USB operation.
            USBSuspendControl = 0; 
            USBBusIsSuspended = FALSE;  //So we don't execute this code again, 
                                        //until a new suspend condition is detected.

            //Section 7.1.7.7 of the USB 2.0 specifications indicates a USB
            //device must continuously see 5ms+ of idle on the bus, before it sends
            //remote wakeup signalling.  One way to be certain that this parameter
            //gets met, is to add a 2ms+ blocking delay here (2ms plus at 
            //least 3ms from bus idle to USBIsBusSuspended() == TRUE, yeilds
            //5ms+ total delay since start of idle).
            delay_count = 3600U;        
            do
            {
                delay_count--;
            }while(delay_count);
            
            //Now drive the resume K-state signalling onto the USB bus.
            USBResumeControl = 1;       // Start RESUME signaling
            delay_count = 1800U;        // Set RESUME line for 1-13 ms
            do
            {
                delay_count--;
            }while(delay_count);
            USBResumeControl = 0;       //Finished driving resume signalling

            USBUnmaskInterrupts();
        }
    }
}

/*******************************************************************
 * Function:        BOOL USER_USB_CALLBACK_EVENT_HANDLER(
 *                        int event, void *pdata, WORD size)
 *
 * PreCondition:    None
 *
 * Input:           int event - the type of event
 *                  void *pdata - pointer to the event data
 *                  WORD size - size of the event data
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called from the USB stack to
 *                  notify a user application that a USB event
 *                  occured.  This callback is in interrupt context
 *                  when the USB_INTERRUPT option is selected.
 *
 * Note:            None
 *******************************************************************/
BOOL USER_USB_CALLBACK_EVENT_HANDLER(int event, void *pdata, WORD size)
{
    switch( event )
    {
        case EVENT_TRANSFER:
            CommsChannel= COMMS_USB;
            break;
        case EVENT_CONFIGURED: 
            USBCBInitEP();
            break;
        case EVENT_EP0_REQUEST:
            USBCBCheckOtherReq();
            break;
        default:
            break;
    }
    return TRUE; 
}

unsigned int read_adc(void)
{
    unsigned int offset;

    // clear interrupt so we read
    mAD1ClearIntFlag();

    // wait for ADC to finish reading
    while ( !mAD1GetIntFlag() )
        ;
    offset = 8 * ((~ReadActiveBufferADC10() & 0x01));
    return ReadADC10(offset);
}

BYTE ProcessSerialCommand(char *command)
{
    BYTE commandok= FALSE;
    BYTE tmpc;
    double tmpfloat;
    unsigned int i, p, tmpint, tmpint1, tmpint2, tmpint3,  tmpint4, tmpint5, tmpint6, tmpint7;
    static unsigned long tmplong;
    static char local_tmp[256], local_tmp1[256];
    BYTE *ccprompt= "";
    static BYTE *prompt= "RFIDler"; // main prompt
    BYTE *prompt_2= "> ";

    ToUpper(command);
    
    // switch to menu mode if empty command
    if(strlen(command) == 0)
        Interface= INTERFACE_CLI;

    // experimental - figure out rates etc for analogue grabbing
    if (strncmp(command, "ANALOGUE ", 9) == 0)
    {
        if(sscanf(command + 9, "%d", &tmpint) == 1)
        {
            if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
                commandok= command_nack("Set TAG type first!");
            else
            {
                commandok= command_ack(DATA);
                analogue_sample(tmpint);
                analogue_xml_out(tmpint);
                eod();
            }
        }
        else
            commandok= command_nack("Invalid number of samples!");
    }
    
    if (strncmp(command, "APDU ", 5) == 0)
    {
        commandok= command_ack(DATA);
        iso_7816_send_hex_apdu(command + 5);
        iso_7816_output();
        eod();
    }

    if (strcmp(command, "API") == 0)
    {
        commandok= command_ack(NO_DATA);
        Interface= INTERFACE_API;
    }

    if (strncmp(command, "ASK ", 4) == 0)
    {
        if(sscanf(command + 4,"%s %ld %u %u", local_tmp, &tmplong, &tmpint, &tmpint1) == 4)
        {
            if(!send_ask_hex(local_tmp, tmplong, tmpint, tmpint1))
                commandok= command_nack("Send failed!");
            else
                commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strcmp(command, "ATR") == 0)
    {
        if(SC_PowerOnATR())
        {
            commandok= command_ack(DATA);
            hexprintbinarray(scCardATR, scATRLength);
            UserMessage("%s", "\r\n");
            eod();
        }
        else
            commandok= command_nack("Failed!");
    }

    if (strncmp(command, "AUTH", 4) == 0)
    {
        // allow null key / block
        local_tmp[0]= '\0';
        tmpint= 0;
        if(sscanf(command + 4, " %s %u", local_tmp, &tmpint) > 2)
                commandok= command_nack("Invalid parameters!");
        else
        {
            if(tag_auth(tmpint, DataBuff, local_tmp))
            {
                commandok= command_ack(DATA);
                UserMessage("%s\r\n", DataBuff);
                eod();
            }
            else
                commandok= command_nack("Auth failed!");
        }
    }

    if (strcmp(command, "AUTOPOT") == 0)
    {
        commandok= command_ack(DATA);
        autopot();
        eod();
    }

    if (strcmp(command, "AUTORATE") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "Trying (for best results use non-zero SYNC bits):\r\n");
        tmpint= autorate();
        if (tmpint)
                UserMessageNum("Data rate is RF/%d\r\n", tmpint);
        eod();
    }

    if (strcmp(command, "AUTORUN") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s\r\n", RFIDlerConfig.AutoRun);
        eod();
    }

    if (strcmp(command, "AUTORUN OFF") == 0)
    {
        memset(RFIDlerConfig.AutoRun, 0x00, sizeof(RFIDlerConfig.AutoRun));
        commandok= command_ack(NO_DATA);
    }
    else if(strncmp(command, "AUTORUN ", 8) == 0 && strlen(command + 8) < sizeof(RFIDlerConfig.AutoRun) - 1)
    {
        strcpy(RFIDlerConfig.AutoRun, command + 8);
        commandok= command_ack(NO_DATA);
    }


    if (strcmp(command, "AUTOTAG") == 0)
    {
        commandok= command_ack(DATA);
        auto_detect_tag_type();
        eod();
    }

    if (strncmp(command, "BINTOHEX ", 9) == 0)
    {
        commandok= command_ack(DATA);
        printbinstringashex(command + 9);
        eod();
    }

    if (strcmp(command, "BL") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "Switching to BOOTLOADER mode...\r\n\r\n");
        eod();
        Delay_us(100000);
        parse_BL_packet();
    }

    if (strcmp(command, "CLI") == 0)
    {
        Interface= INTERFACE_CLI;
        commandok= command_ack(NO_DATA);
    }

    if (strncmp(command, "CLOCKH ", 7) == 0)
    {
        if(sscanf(&command[7], "%lf", &tmpfloat) == 1 && tmpfloat > 0)
        {
            // convert to uS/100
            tmplong= (unsigned long) ((1L/tmpfloat) * 100000000L);
            InitHWReaderClock(OC_TOGGLE_PULSE, tmplong / 2L, tmplong, RWD_STATE_ACTIVE);
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Failed!");
    }

    if (strncmp(command, "CLOCKP ", 7) == 0)
    {
        if(sscanf(&command[7], "%u %u", &tmpint, &tmpint1) == 2 && tmpint > 0 && tmpint1 > tmpint)
        {
            InitHWReaderClock(OC_PWM_FAULT_PIN_DISABLE, (unsigned long) tmpint * 2L, (unsigned long) tmpint1 * 2L, RWD_STATE_ACTIVE);
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Failed!");
    }

    if (strncmp(command, "CLOCKT ", 7) == 0)
    {
        if(sscanf(&command[7], "%ld", &tmplong) == 1 && tmplong > 0)
        {
            InitHWReaderClock(OC_TOGGLE_PULSE, tmplong / 2L, tmplong, RWD_STATE_ACTIVE);
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Failed!");
    }

    if (strncmp(command, "CLONE", 5) == 0)
    {
        // allow null key/pwd
        local_tmp[0]= '\0';
        if(sscanf(command + 5, "%s", local_tmp) <= 1)
        {
            if (!vtag_write_to_tag(local_tmp))
                commandok= command_nack("Failed!");
            else
                commandok= command_ack(NO_DATA);
        }
        else
           commandok= command_nack("Invalid parameters!");
    }

    if (strcmp(command, "COIL HIGH") == 0)
    {
        commandok= command_ack(NO_DATA);
        COIL_OUT_HIGH();
    }

    if (strcmp(command, "COIL LOW") == 0)
    {
        commandok= command_ack(NO_DATA);
        COIL_OUT_LOW();
    }

    if (strcmp(command, "CONFIG") == 0)
    {
        commandok= command_ack(DATA);
        showconfig();
        eod();
    }

    if (strncmp(command, "CONVERT ", 8) == 0)
    {
        if(RFIDlerVTag.TagType)
        {
            if(sscanf(command + 7, "%s", local_tmp) == 1)
            {
                if(vtag_convert(local_tmp))
                    commandok= command_ack(NO_DATA);
                else
                    commandok= command_nack("Failed!");
            }
        }
        else
           commandok= command_nack("VTag type not set!");
    }

    if (strncmp(command, "COPY", 4) == 0)
    {
        // allow empty tag type / pwd/key
        local_tmp[0]= '\0';
        local_tmp1[0]= '\0';
        tmpint= 0;
        if(sscanf(command + 4, "%s %s", local_tmp, local_tmp1) <= 2)
        {
            if(vtag_copy_from_tag(local_tmp, local_tmp1))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Failed!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if(strcmp(command, "DEBUG") == 0)
    {
        commandok= command_ack(DATA);
        debug_show();
        eod();
    }

    if (strncmp(command, "DEBUG ", 6) == 0)
    {
        if(sscanf(command + 6, "%i", &tmpint) == 1)
        {
            if (debug_toggle((BYTE) tmpint))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Invalid DEBUG pin!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strncmp(command, "DEBUGON ", 8) == 0)
    {
        if(sscanf(command + 8, "%i", &tmpint) == 1)
        {
            if (debug_on((BYTE) tmpint))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Invalid DEBUG pin!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strncmp(command, "DEBUGOFF ", 9) == 0)
    {
        if(sscanf(command + 9, "%i", &tmpint) == 1)
        {
            if (debug_off((BYTE) tmpint))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Ivalid LED!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strcmp(command, "DETECT") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "Waiting for external clock (hit any key to abort)...\r\n");
        detect_external_clock();
        eod();
    }

    if (strcmp(command, "DOOR CLOSE") == 0)
    {
        commandok= command_ack(NO_DATA);
        DOOR_RELAY_CLOSE();
    }

    if (strcmp(command, "DOOR OPEN") == 0)
    {
        commandok= command_ack(NO_DATA);
        DOOR_RELAY_OPEN();
    }

    if (strncmp(command, "DUMP ", 5) == 0)
    {
        if((tmpint2= sscanf(command + 5,"%u %u", &tmpint, &tmpint1)) && tmpint2 == 1 || tmpint2 == 2)
        {
            // only start block specified, so default to read 1 block
            if(tmpint2 == 1)
               tmpint1=  tmpint;

            if(tmpint > RFIDlerConfig.DataBlocks - 1 || tmpint1 > RFIDlerConfig.DataBlocks - 1)
                commandok= command_nack("Invalid block number(s)!");
            else
                // read and view data
                if(!read_tag(DataBuff, tmpint, tmpint1))
                    commandok= command_nack("Read failed!");
                else
                {
                    commandok= command_ack(DATA);
                    local_tmp[HEXDIGITS(RFIDlerConfig.BlockSize)]= '\0';
                    for(i= tmpint, p= 0 ; i <= tmpint1 ; ++i, ++p)
                    {
                        UserMessageNum("%d: ", i);
                        memcpy(local_tmp, DataBuff + p * HEXDIGITS(RFIDlerConfig.BlockSize), HEXDIGITS(RFIDlerConfig.BlockSize));
                        UserMessage("%s\r\n", local_tmp);
                    }
                    eod();
                }
        }
        else
            commandok= command_nack("Invalid block number(s)!\r\n");
    }

    if (strncmp(command, "EMU ", 4) == 0)
    {
        if(RFIDlerConfig.TagType)
        {
            if(emulate_tag(command + 4))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Failed!");
        }
        else
           commandok= command_nack("Tag type not set!");
    }

    if(strcmp(command, "EMULATOR") == 0 || strcmp(command, "EMULATOR BG") == 0)
    {
       if(!RFIDlerVTag.TagType)
           commandok= command_nack("Create valid VTAG first!");
       else
       {
           // store current tag type
           tmpc= RFIDlerConfig.TagType;
           // emulation or native mode
           if(RFIDlerVTag.EmulatedTagType != TAG_TYPE_NONE)
               tag_set(RFIDlerVTag.EmulatedTagType);
           else
               tag_set(RFIDlerVTag.TagType);
           if(!interpret_uid(DataBuff, RFIDlerVTag.UID, RFIDlerConfig.TagType))
               commandok= command_nack("Invalid UID!");
           else
           {
               commandok= command_ack(NO_DATA);
               if(strcmp(command, "EMULATOR BG") == 0)
               {
                   EMU_Background= TRUE;
                   emulate_tag(DataBuff);
               }
               else
               {
                   while(!get_user_abort() && emulate_tag(DataBuff))
                   {
                       // some readers will not respond until TAG stops talking
                       Delay_us(250000);
                       mLED_Comms_Toggle();
                   }
                   // restore tag settings
                   tag_set(tmpc);
               }
           }
       }
    }

    if (strncmp(command, "ENCODE ", 7) == 0)
    {
        if(RFIDlerConfig.TagType)
        {
            // allow empty tag type but not uid
            local_tmp[0]= '\0';
            local_tmp1[0]= '\0';
            if(sscanf(command + 7, "%s %s", local_tmp, local_tmp1) <= 2 && strlen(local_tmp) != 0)
            {
                // output hex only
                if(strlen(local_tmp1) == 0)
                {
                    if(tag_uid_to_hex(TmpBuff, local_tmp, RFIDlerConfig.TagType))
                    {
                        commandok= command_ack(DATA);
                        UserMessage("%s\r\n", TmpBuff);
                        eod();
                    }
                    else
                        commandok= command_nack("Encode failed!");
                }
                // encode to VTAG
                else
                {
                    if(vtag_create_from_uid(local_tmp1, RFIDlerConfig.TagType, local_tmp))
                        commandok= command_ack(NO_DATA);
                    else
                        commandok= command_nack("VTAG encode failed!");
                }
            }
        }
        else
           commandok= command_nack("Tag type not set!");
    }

    if (strcmp(command, "EXAMPLES") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "RAW Emulation examples:\r\n");
        UserMessage("%s", "\r\n  EM4X02 ID '0000DC4420'\r\n\r\n");
        UserMessage("%s", "    SET MAN ON\r\n");
        UserMessage("%s", "    ASK FF800006F0949406 800 64 20\r\n");
        UserMessage("%s", "\r\n  Unique ID '0DEADBEEF0'\r\n\r\n");
        UserMessage("%s", "    SET MAN ON\r\n");
        UserMessage("%s", "    ASK FFDC0A7EEEF783C0 800 64 20\r\n");
        UserMessage("%s", "\r\n  HID Prox26 Site Code 123 ID 45678\r\n\r\n");
        UserMessage("%s", "    SET MAN OFF\r\n");
        UserMessage("%s", "    FSK 1D5559555569AA6A6965A6A6 800 50 8 10 20\r\n");
        UserMessage("%s", "\r\n  Indala (encrypted):\r\n\r\n");
        UserMessage("%s", "    SET MAN OFF\r\n");
        UserMessage("%s", "    PSK1 000000025AA9A2B074F113A4645E20B7A792B831DD3C58D27A727B2B 800 32 2 20\r\n");
        UserMessage("%s", "\r\n\r\n TAG Emulation examples\r\n");
        UserMessage("%s", "\r\n  EM4X02 ID 'ABCDE12345'\r\n\r\n");
        UserMessage("%s", "    SET TAG EM4X02\r\n");
        UserMessage("%s", "    EMU ABCDE12345\r\n");
        UserMessage("%s", "\r\n  Unique ID '00CAFEF00D'\r\n\r\n");
        UserMessage("%s", "    SET TAG UNIQUE\r\n");
        UserMessage("%s", "    EMU 00CAFEF00D\r\n");
        UserMessage("%s", "\r\n  HID Prox26 Site Code 254 ID 00666\r\n\r\n");
        UserMessage("%s", "    SET TAG HID26\r\n");
        UserMessage("%s", "    EMU 25400666\r\n");
        UserMessage("%s", "\r\n\r\n RWD command examples\r\n");
        UserMessage("%s", " ====================\r\n");
        UserMessage("%s", "\r\n  Hitag2 START_AUTH\r\n\r\n");
        UserMessage("%s", "    PWM 800 4000 4000 18 26 5\r\n");
        UserMessage("%s", "    RWD 11000\r\n");
        eod();
    }

    if (strncmp(command, "FSK ", 4) == 0)
    {
        if(sscanf(command + 4,"%s %ld %u %u %u %u", local_tmp, &tmplong, &tmpint, &tmpint1, &tmpint2, &tmpint3) == 6)
        {
            UserMessage("Sending %s ", local_tmp);
            if(send_fsk_hex(local_tmp, tmplong, tmpint, tmpint1, tmpint2, tmpint3))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Send failed!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strcmp(command, "FREQUENCY") == 0)
    {
        commandok= command_ack(DATA);
        UserMessageNum("%d\r\n", analogue_frequency());
        eod();
    }

    if (strncmp(command, "HEXTOBIN ", 9) == 0)
    {
        commandok= command_ack(DATA);
        printhexasbin(command + 9);
        eod();
    }

    if (strncmp(command, "LED ", 4) == 0)
    {
        if(sscanf(command + 4, "%i", &tmpint) == 1)
        {
            if (led_toggle((BYTE) tmpint))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Invalid LED!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strncmp(command, "LEDON ", 6) == 0)
    {
        if(sscanf(command + 6, "%i", &tmpint) == 1)
        {
            if (led_on((BYTE) tmpint))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Invalid LED!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strncmp(command, "LEDOFF ", 7) == 0)
    {
        if(sscanf(command + 7, "%i", &tmpint) == 1)
        {
            if (led_off((BYTE) tmpint))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Ivalid LED!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }


    if (strcmp(command, "LOAD") == 0)
    {
        commandok= command_ack(NO_DATA);
        loadconfig();
    }

    if (strncmp(command, "LOGIN", 5) == 0)
    {
        // allow empty password / block
        local_tmp[0]= '\0';
        tmpint= 0;
        if(sscanf(command + 5, " %s %u", local_tmp, &tmpint) > 2)
            commandok= command_nack("Invalid parameters!");
        else
        {
            if(tag_login(tmpint, DataBuff, local_tmp))
            {
                commandok= command_ack(DATA);
                UserMessage("%s\r\n", DataBuff);
                eod();
            }
            else
                commandok= command_nack("Login failed!");
        }
    }

    if (strcmp(command, "PING") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s\r\n", "RFIDler");
        eod();
    }

    if (strcmp(command, "POTS") == 0)
    {
        commandok= command_ack(DATA);
        show_mcp414_wipers();
        eod();
    }

    if (strncmp(command, "POTDEC ", 7) == 0)
    {
        if(sscanf(command + 7,"%c %d", &tmpc, &tmpint1) == 2 && tmpc == 'H' || tmpc == 'L')
        {
            while(tmpint1--)
                if((tmpc= decrement_mcp414(tmpc == 'H' ? 0 : 1, local_tmp)))
                    break;
            if(tmpc)
                commandok= command_nack("POT decrement failed!");
            else
                commandok= command_ack(NO_DATA);
        }
        else
           commandok= command_nack("Invalid parameters");
    }

    if (strncmp(command, "POTINC ", 7) == 0)
    {
        if(sscanf(command + 7,"%c %d", &tmpc, &tmpint1) == 2 && tmpc == 'H' || tmpc == 'L')
        {
            while(tmpint1--)
                if((tmpc= increment_mcp414(tmpc == 'H' ? 0 : 1, FALSE, local_tmp)))
                    break;
            if(tmpc)
                commandok= command_nack("POT increment failed!");
            else
                commandok= command_ack(NO_DATA);
        }
        else
           commandok= command_nack("invalid parameters");
    }

    if (strncmp(command, "POTSET ", 7) == 0)
    {
        if(sscanf(command + 7,"%c %d", &tmpc, &tmpint1) == 2 && tmpc == 'H' || tmpc == 'L')
        {
            if(!set_mcp414_wiper(tmpc == 'H' ? WIPER_HIGH : WIPER_LOW, VOLATILE, tmpint1, local_tmp))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("POT set failed!");
        }
        else
           commandok= command_nack("Invalid parameter!");
    }

    if (strncmp(command, "POTSETNV ", 9) == 0)
    {
        if(sscanf(command + 9,"%c %d", &tmpc, &tmpint1) == 2 && tmpc == 'H' || tmpc == 'L')
        {
            if(!set_mcp414_wiper(tmpc == 'H' ? WIPER_HIGH : WIPER_LOW, NON_VOLATILE, tmpint1, local_tmp))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("POT set failed!");
        }
        else
           commandok= command_nack("Invalid parameter!");
    }

    if (strncmp(command, "POTSETV ", 8) == 0)
    {
        if(sscanf(command + 8,"%c %lf", &tmpc, &tmpfloat) == 2 && tmpc == 'H' || tmpc == 'L')
        {
            tmpint1= (int) (tmpfloat / VOLTS_TO_POT);
            if(!set_mcp414_wiper(tmpc == 'H' ? WIPER_HIGH : WIPER_LOW, VOLATILE, tmpint1, local_tmp))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("POT set failed!");
        }
        else
           commandok= command_nack("Invalid parameter!");
    }

    if (strncmp(command, "PSK1 ", 5) == 0)
    {
        if(sscanf(command + 5,"%s %ld %u %u %u", local_tmp, &tmplong, &tmpint, &tmpint1, &tmpint2) == 5)
        {
            if(send_psk1_hex(local_tmp, tmplong, tmpint, tmpint1, tmpint2))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Send failed!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strncmp(command, "PWM ", 4) == 0)
    {
        if(sscanf(command + 4,"%u %u %u %u %u %u %u %u", &tmpint, &tmpint1, &tmpint2, &tmpint3, &tmpint4, &tmpint5, &tmpint6, &tmpint7) == 8)
        {
            rwd_set_pwm(tmpint, tmpint1, tmpint2, tmpint3, tmpint4, tmpint5, tmpint6, tmpint7);
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strncmp(command, "READ ", 5) == 0)
    {
        if((tmpint2= sscanf(command + 5,"%u %u", &tmpint, &tmpint1)) && tmpint2 == 1 || tmpint2 == 2)
        {
            // only start block specified, so default to read 1 block
            if(tmpint2 == 1)
               tmpint1=  tmpint;

            if(RFIDlerConfig.TagType != RFIDlerVTag.TagType)
                commandok= command_nack("VTag not compatible!");
            else
            {
            if(tmpint > RFIDlerConfig.DataBlocks - 1 || tmpint1 > RFIDlerConfig.DataBlocks - 1)
                commandok= command_nack("Invalid block number(s)!");
            else
                // read and view data
                if(!read_tag(&RFIDlerVTag.Data[tmpint * HEXDIGITS(RFIDlerVTag.BlockSize)], tmpint, tmpint1))
                    commandok= command_nack("Read failed!");
                else
                {
                    commandok= command_ack(DATA);
                    local_tmp[HEXDIGITS(RFIDlerConfig.BlockSize)]= '\0';
                    for(i= tmpint ; i <= tmpint1 ; ++i)
                    {
                        UserMessageNum("%d: ", i);
                        memcpy(local_tmp, RFIDlerVTag.Data + i * HEXDIGITS(RFIDlerConfig.BlockSize), HEXDIGITS(RFIDlerConfig.BlockSize));
                        UserMessage("%s\r\n", local_tmp);
                    }
                    UserMessage("%s", "\r\n");
                }
            }
        }
        else
            commandok= command_nack("Invalid block number(s)!\r\n");
    }

    if(strcmp(command, "READER") == 0)
    {
        if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
            commandok= command_nack("TAG type not set!");
        else
        {
            commandok= command_ack(DATA);
            while(!get_user_abort())
            {
                if(get_interpreted_tag_uid(DataBuff, RFIDlerConfig.TagType))
                    UserMessage("%s\r\n", DataBuff);
                mLED_Comms_Toggle();
            }
            eod();
            stop_HW_clock();
        }
    }

    if (strcmp(command, "REBOOT") == 0)
    {
        commandok= command_ack(NO_DATA);
        Delay_us(1000000);
        SoftReset();
    }

    if (strcmp(command, "RTC") == 0)
    {
        commandok= command_ack(DATA);
        RTC_time.l= RtccGetTime();
        RTC_date.l= RtccGetDate();
        // note time/data is in BCD
        sprintf(TmpBuff, "%02x/%02x/%02x %02x:%02x:%02x", RTC_date.year, RTC_date.mon, RTC_date.mday, RTC_time.hour, RTC_time.min, RTC_time.sec);
        UserMessage("%s\r\n", TmpBuff);
    }

    if (strncmp(command, "RWD ", 4) == 0)
    {
        if(sscanf(command + 4,"%s", local_tmp) == 1)
        {
            if(rwd_send(local_tmp, strlen(local_tmp), RESET, BLOCK, RWD_STATE_START_SEND, RFIDlerConfig.FrameClock, RFIDlerConfig.RWD_Sleep_Period, RFIDlerConfig.RWD_Wake_Period, RFIDlerConfig.RWD_Zero_Period, RFIDlerConfig.RWD_One_Period, RFIDlerConfig.RWD_Gap_Period, 0))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Failed! PWM parameters not set or invalid data!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }

    if (strcmp(command, "SAVE") == 0)
    {
        if(saveconfig())
            commandok= command_ack(NO_DATA);
        else
            commandok= command_nack("Verify failed!");
    }

    if (strncmp(command, "SELECT", 6) == 0)
    {
        // allow empty UID
        local_tmp[0]= '\0';
        if(sscanf(command + 6, "%s", local_tmp, &tmpint) <= 1)
        {
            if(select_tag(DataBuff, local_tmp))
            {
                commandok= command_ack(DATA);
                UserMessage("%s\r\n", DataBuff);
                eod();
            }
            else
                commandok= command_nack("Select failed!");
        }
        else
            commandok= command_nack("Invalid parameters!");
    }
    
    if (strcmp(command, "SET BIPHASE OFF") == 0)
    {
        RFIDlerConfig.BiPhase= FALSE;
        commandok= command_ack(NO_DATA);
    }

    if (strcmp(command, "SET BIPHASE ON") == 0)
    {
        RFIDlerConfig.BiPhase= TRUE;
        RFIDlerConfig.Manchester= FALSE;
        commandok= command_ack(NO_DATA);
    }

    if (strncmp(command, "SET BITS ", 9) == 0)
    {
        if(sscanf(command + 9,"%u", &tmpint) == 1)
        {
            RFIDlerConfig.DataBits= tmpint;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid data bits!");
    }

    if (strncmp(command, "SET FC ", 7) == 0)
    {
        if(sscanf(command + 7,"%ld", &tmplong) == 1)
        {
            RFIDlerConfig.FrameClock= tmplong;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid FC period!");
    }

    if (strcmp(command, "SET INVERT OFF") == 0)
    {
        RFIDlerConfig.Invert= FALSE;
        commandok= command_ack(NO_DATA);
    }

    if (strcmp(command, "SET INVERT ON") == 0)
    {
        RFIDlerConfig.Invert= TRUE;
        commandok= command_ack(NO_DATA);
    }

    if (strcmp(command, "SET MANCHESTER OFF") == 0)
    {
        RFIDlerConfig.Manchester= FALSE;
        commandok= command_ack(NO_DATA);
    }
    
    if (strcmp(command, "SET MANCHESTER ON") == 0)
    {
        RFIDlerConfig.Manchester= TRUE;
        RFIDlerConfig.BiPhase= FALSE;
        commandok= command_ack(NO_DATA);
    }

    if (strncmp(command, "SET MOD ", 8) == 0)
    {
        if(strcmp(command + 8,"ASK") == 0)
        {
            RFIDlerConfig.Modulation= MOD_MODE_ASK_OOK;
            commandok= command_ack(NO_DATA);
        }
        else if(strcmp(command + 8,"FSK") == 0)
        {
            RFIDlerConfig.Modulation= MOD_MODE_FSK1;
            commandok= command_ack(NO_DATA);
        }
        else if(strcmp(command + 8,"PSK1") == 0)
        {
            RFIDlerConfig.Modulation= MOD_MODE_PSK1;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Unknown modulation scheme!");
    }

    if (strncmp(command, "SET PSK ", 8) == 0)
    {
        if(sscanf(command + 8,"%ld", &tmplong) == 1)
        {
            RFIDlerConfig.PSK_Quality= tmplong;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid data bits!");
    }

    
    if (strncmp(command, "SET RATE ", 9) == 0)
    {
        if(sscanf(command + 9,"%u", &tmpint) == 1)
        {
            RFIDlerConfig.DataRate= tmpint;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid data rate!");
    }

    if (strncmp(command, "SET REPEAT ", 11) == 0)
    {
        if(sscanf(command + 11,"%u", &tmpint) == 1)
        {
            RFIDlerConfig.Repeat= tmpint;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid repetitions!");
    }

    if (strncmp(command, "SET SUB0 ", 9) == 0)
    {
        if(sscanf(command + 9,"%u", &tmpint) == 1)
        {
            RFIDlerConfig.DataRateSub0= tmpint;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid data rate!");
    }

    if (strncmp(command, "SET SUB1 ", 9) == 0)
    {
        if(sscanf(command + 9,"%u", &tmpint) == 1)
        {
            RFIDlerConfig.DataRateSub1= tmpint;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid data rate!");
    }

    if (strncmp(command, "SET SYNCBITS ", 13) == 0)
    {
        if(sscanf(command + 13,"%u", &tmpint) == 1)
        {
            RFIDlerConfig.SyncBits= (unsigned char) tmpint;
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Invalid number of bits!");
    }
    else
        if (strncmp(command, "SET SYNC", 8) == 0)
        {
            if(sscanf(command + 8,"%u %X", &tmpint, &tmpint1) == 2 && tmpint >= 0 && tmpint <= 3)
            {
                RFIDlerConfig.Sync[tmpint]= (unsigned char) tmpint1;
                commandok= command_ack(NO_DATA);
            }
            else
                commandok= command_nack("Invalid sync byte!");
        }

    if (strncmp(command, "SET TAG ", 8) == 0)
    {
        if((tmpc= tag_get_type(command + 8)))
        {
            tag_set(tmpc);
            commandok= command_ack(NO_DATA);
        }
        else
            commandok= command_nack("Unknown TAG type!");
    }

    if (strncmp(command, "SET VTAG ", 9) == 0)
    {
        if(vtag_set_tag_type(command + 9))
            commandok= command_ack(NO_DATA);
        else
            commandok= command_nack("Unknown TAG type!");
    }

    if(strcmp(command, "SNIFFER") == 0)
    {
       commandok= command_ack(DATA);
       UserMessage("%s", "Hit any key to stop sniffer\r\n");
       SnifferMode= TRUE;
       while(!get_user_abort())
            if(get_interpreted_tag_uid(DataBuff, RFIDlerConfig.TagType))
                UserMessage("%s\r\n", DataBuff);
       eod();
       stop_HW_clock();
       SnifferMode= FALSE;
    }

    if (strcmp(command, "STOP") == 0)
    {
        commandok= command_ack(NO_DATA);
        stop_HW_clock();
    }

    if (strcmp(command, "TAGS") == 0)
    {
        commandok= command_ack(DATA);
        tag_list();
        eod();
    }

    if(strcmp(command, "TCONFIG") == 0)
    {
        if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
            commandok= command_nack("Tag type not set!");
        else
        {
            if(!config_block_number(&tmpint, RFIDlerConfig.TagType))
                commandok= command_nack("Not supported for this tag type!");
            else
            {
                if (get_config_block(local_tmp, RFIDlerConfig.TagType))
                    {
                        commandok= command_ack(DATA);
                        config_block_show(local_tmp, RFIDlerConfig.TagType);
                        eod();
                    }
                else
                    commandok= command_nack("Read failed!");
            }
        }
    }
    
    if (strcmp(command, "TEST-HITAG") == 0)
    {
        // exercise hitag crypto, init from serialnumber, key & IV & gen authenticator
        unsigned long test;

        commandok= command_ack(DATA);

        UserMessage("%s", "\r\nbenchmark & verify Hitag 2 crypto implementation");

        test = hitag2_verifytest();
        UserMessage("\r\nCrypto self test of correctness = %s", test ? "Pass" : "FAIL");

        test = hitag2_benchtest(1);
        UserMessageNum("\r\nHitag 2 crypto, init + gen 32 bits - us: %ld", test);

        test = hitag2_benchtest_gen32();
        UserMessageNum("\r\nHitag 2 crypto, gen new 32 bits only - us: %ld", test);

        test = hitag2_benchtest(1000);
        UserMessageNum("\r\nHitag 2 crypto, init + gen 32 bits, x1000 - us: %ld\r\n", test);

        eod();
    }

    if (strncmp(command, "TEST-RWD", 8) == 0)
    {
        commandok= command_ack(DATA);
        // allow null key/pwd
        local_tmp[0]= '\0';
        sscanf(command + 8, "%s", local_tmp);
        rwd_test(local_tmp);
        eod();
    }

    if (strcmp(command, "TEST-SC") == 0)
    {
        if(SC_PowerOnATR())
        {
            commandok= command_ack(DATA);
            UserMessage("%s", "ATR: ");
            hexprintbinarray(scCardATR, scATRLength);
            UserMessage("%s", "\r\n");
            eod();
        }
        else
            commandok= command_nack("Failed!");
    }

    if (strcmp(command, "TEST-SD") == 0)
    {
        // for automated test we don't want prompts or output - just pass/fail
        if(sdcard_test((Interface == INTERFACE_API)))
            commandok= command_ack(NO_DATA);
        else
            commandok= command_nack("Failed!");
    }

    if (strcmp(command, "TEST-TIMER") == 0)
    {
        commandok= command_ack(DATA);
        clock_test();
        eod();

    }

    if (strcmp(command, "TEST-WIEGAND") == 0)
    {
        wiegand_set_pullups(FALSE);
        if(wiegand_test())
            commandok= command_ack(NO_DATA);
        else
            commandok= command_nack("Failed!");
    }

    if (strncmp(command, "TEST-WIEGAND-READ ", 18) == 0)
    {
        tmpint= 0;
        if(sscanf(command + 18,"%d", &tmpint) <= 1 && tmpint >= 0 && tmpint <= 4)
        {
            commandok= command_ack(DATA);
            if(! RFIDlerConfig.Wiegand_Pulse || ! RFIDlerConfig.Wiegand_Gap)
                learn_wiegand((BYTE) tmpint);
            else
                read_wiegand((BYTE) tmpint);
            UserMessage("Read: %s\r\n", DataBuff);
            DataBuff[0]= '\0';
            DataBuffCount= 0;
            eod();
        }
        else
            commandok= command_nack("Invalid debug pin!");
    }

    if (strncmp(command, "TRESET", 6) == 0)
    {
        if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
            commandok= command_nack("Tag type not set!");
        else
        {
            if(!config_block_number(&tmpint, RFIDlerConfig.TagType))
                commandok= command_nack("Not supported for this tag type!");
            else
            {
                // allow empty password / block
                local_tmp[0]= '\0';
                sscanf(command + 6, " %s", local_tmp);
                if (tag_write_default_config(RFIDlerConfig.TagType, local_tmp))
                    commandok= command_ack(NO_DATA);
                else
                    commandok= command_nack("Write failed!");
            }
        }
    }

    if (strcmp(command, "TRISTATE OFF") == 0)
    {
        commandok= command_ack(NO_DATA);
        READER_CLOCK_ENABLE_OFF();
    }

    if (strcmp(command, "TRISTATE ON") == 0)
    {
        commandok= command_ack(NO_DATA);
        READER_CLOCK_ENABLE_ON();
    }

    if (strncmp(command, "TWIPE", 5) == 0)
    {
        if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
            commandok= command_nack("Tag type not set!");
        else
        {
            // allow empty password / block
            local_tmp[0]= '\0';
            sscanf(command + 5, " %s", local_tmp);
            if (tag_write_default_blocks(RFIDlerConfig.TagType, local_tmp))
                commandok= command_ack(NO_DATA);
            else
                commandok= command_nack("Write failed!");
         }
    }

    if (strcmp(command, "UID") == 0)
    {
        if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
            commandok= command_nack("Set TAG type first!");
        else
        {
            if(get_interpreted_tag_uid(DataBuff, RFIDlerConfig.TagType))
            {
                commandok= command_ack(DATA);
                UserMessage("%s\r\n", DataBuff);
                eod();
            }
            else
                commandok= command_nack("read error!");
        }
    }

    // version number is generated by pre-processor macro counting number of commits to git repo
    // VERSION=`git rev-list HEAD --count`
    // hardware revision is defined in
    if (strcmp(command, "VERSION") == 0)
    {
        commandok= command_ack(DATA);
        UserMessageNum("%04d-beta\r\n", VERSION);
        eod();
    }

    if (strcmp(command, "VTAG") == 0)
    {
        commandok= command_ack(DATA);
        vtag_dump();
        eod();
    }

    if (strncmp(command, "VWRITE ", 7) == 0)
    {
        if(sscanf(command + 7,"%u %s", &tmpint, local_tmp) == 2)
        {
            if(vtag_write_blocks(tmpint, local_tmp))
            {
                commandok= command_ack(DATA);
                UserMessage("%s\r\n", local_tmp);
                eod();
            }
            else
                commandok= command_nack("VTAG write failed!");
        }
        else
            commandok= command_nack("Invalid block number or no data!");
    }

    // pinouts
    if (strcmp(command, "WIRING") == 0 || strcmp(command, "WIRES") == 0 || strcmp(command, "PINS") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "  === WIRING: PIC32 PIC32MX795F512L ===\r\n");
        UserMessage("%s", "  PIN NUMBER / NAME         FUNCTION                USE\r\n");
        UserMessage("%s", "  =====================================================\r\n");
        UserMessage("%s", "  13           _MCLR        RESET_BUTTON            Reset / VPP\r\n");
        UserMessage("%s", "  59           RA2          IC Frequency IN         Measure Inductance/Capacitance\r\n");
        UserMessage("%s", "  60           RA4          OR-IN-A                 Output from Schmitt trigger A\r\n");
        UserMessage("%s", "  61           RA5          OR-IN-B                 Output from Schmitt trigger B\r\n");
        UserMessage("%s", "  67           RA15         LED6                    User LED White\r\n");
        UserMessage("%s", "  66           RA14         RELAY                   Door Relay\r\n");
        UserMessage("%s", "  26           RB6/PGC      PGC                     Program Clock\r\n");
        UserMessage("%s", "  27           RB7/PGD2     PGD2                    Program Data 2\r\n");
        UserMessage("%s", "  33           RB9          S/C VCC                 ISO-7816 Smartcard VCC\r\n");
        UserMessage("%s", "  35           RB11/AN11    Analogue IN             Reader analogue data\r\n");
        UserMessage("%s", "  41           RB12/AN12    Analogue LOW IN         Voltage divider LOW analogue data\r\n");
        UserMessage("%s", "  42           RB13/AN13    Analogue HIGH IN        Voltage divider HIGH analogue data\r\n");
        UserMessage("%s", "  06           RC1          DEBUG1                  Logic Analyser Debug Pin 1\r\n");
        UserMessage("%s", "  07           RC2          DEBUG2                  Logic Analyser Debug Pin 2\r\n");
        UserMessage("%s", "  08           RC3          DEBUG3                  Logic Analyser Debug Pin 3\r\n");
        UserMessage("%s", "  09           RC4/SDI1     SD_CARD_RX              SPI RX for SD Card\r\n");
        UserMessage("%s", "  72           RD0/SDO1     SD_CARD_TX              SPI TX for SD Card\r\n");
        UserMessage("%s", "  76           RD1          S/C CLK                 ISO-7816 Smartcard Clock\r\n");
        UserMessage("%s", "  77           RD2          WIEGAND_1_OUT           Wiegand 1 / Clock & Data - Clock OUT\r\n");
        UserMessage("%s", "  78           RD3          WIEGAND_0_OUT           Wiegand 0 / Clock & Data - Data OUT\r\n");
        UserMessage("%s", "  81           RD4          READER-CLOCK            Reader COIL CLOCK\r\n");
        UserMessage("%s", "  82           RD5          WIEGAND_0_IN            Wiegand 0 / Clock & Data - Data IN\r\n");
        UserMessage("%s", "  83           RD6          WIEGAND_1_IN            Wiegand 1 / Clock & Data  - Clock IN\r\n");
        UserMessage("%s", "  68           RD8          READER-DATA             Reader COIL DATA\r\n");
        UserMessage("%s", "  69           RD9/_SS1     SD_CARD_SS              SPI Select SD Card\r\n");
        UserMessage("%s", "  70           RD10/SCK1    SD_CARD_CLK             SPI Clock for SD Card\r\n");
        UserMessage("%s", "  71           RD11         LED7                    Error LED Red\r\n");
        UserMessage("%s", "  79           RD12         CLOCK-SNIFF             Clock Sniff\r\n");
        UserMessage("%s", "  48           RD15         _POT_SHUTDOWN           Potentiometer power control\r\n");
        UserMessage("%s", "  93           RE0          LED4                    Emulate LED Red\r\n");
        UserMessage("%s", "  94           RE1          LED3                    Clock LED Yellow\r\n");
        UserMessage("%s", "  98           RE2          LED2                    Comms LED White\r\n");
        UserMessage("%s", "  99           RE3          LED1                    USB LED Green\r\n");
        UserMessage("%s", "  03           RE5          DEBUG4                  Logic Analyser Debug Pin 4\r\n");
        UserMessage("%s", "  04           RE6          USER_BUTTON             User defined button\r\n");
        UserMessage("%s", "  05           RE7          BOOTLOADER_BUTTON       Bootloader select button\r\n");
        UserMessage("%s", "  18           RE8          S/C RST                 ISO-7816 Smartcard Reset\r\n");
        UserMessage("%s", "  19           RE9          READER-CLOCK-ENABLE     Tri-State clock select\r\n");
        UserMessage("%s", "  87           RF0          SD_CARD_DET             SD Card Detect\r\n");
        UserMessage("%s", "  88           RF1          SD_CARD_WP              SD Card Write Protect (unused)\r\n");
        UserMessage("%s", "  52           RF2          S/C RX                  ISO-7816 Smartcard RX\r\n");
        UserMessage("%s", "  51           RF3/USBID    USBID                   USBID\r\n");
        UserMessage("%s", "  49           RF4/SDI4     SPI4 IN                 Potentiometer Data IN\r\n");
        UserMessage("%s", "  50           RF5/SDO4     SPI4 OUT                Potentiometer Data OUT\r\n");
        UserMessage("%s", "  53           RF8          S/C TX                  ISO-7816 Smartcard TX\r\n");
        UserMessage("%s", "  40           RF12/_SS4    _SPI4 SLAVE SELECT      Potentiometer Select\r\n"); // potentiometer: MCP414X
        UserMessage("%s", "  39           RF13/SCK4    SPI4 CLOCK              Potentiometer Clock\r\n");
        UserMessage("%s", "  57           RG2/D+       D+                      USB D+\r\n");
        UserMessage("%s", "  56           RG3/D-       D-                      USB D-\r\n");
        UserMessage("%s", "  10           RG6          LED5                    Read LED Green\r\n");
        UserMessage("%s", "  11           RG7/U3RX     CLI UART3 RX            UART CLI/API\r\n");
        UserMessage("%s", "  12           RG8/U3TX     CLI UART3 TX            UART CLI/API\r\n");
        UserMessage("%s", "  14           RG9          Emulation COIL          Emulation COIL\r\n");
        UserMessage("%s", "  54           VBUS         VBus                    USB VBus\r\n");
        eod();
    }
    
    if (strcmp(command, "WIEGAND-LEARN") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "Waiting for external Wiegand reader (hit any key to abort)...\r\n");
        learn_wiegand(NO_TRIGGER);
        eod();
    }

    if (strcmp(command, "WIEGAND-OUT OFF") == 0)
    {
        commandok= command_ack(NO_DATA);
        wiegand_out_disable();
    }

    if (strcmp(command, "WIEGAND-OUT ON") == 0)
    {
        commandok= command_ack(NO_DATA);
        wiegand_out_enable();
    }

    if (strcmp(command, "WIEGAND-READ") == 0)
    {
        commandok= command_ack(DATA);
        UserMessage("%s", "Waiting for external Wiegand reader (hit any key to abort)...\r\n");
        DataBuff[0]= '\0';
        if(! RFIDlerConfig.Wiegand_Pulse || ! RFIDlerConfig.Wiegand_Gap)
            learn_wiegand(NO_TRIGGER);
        else
            read_wiegand(NO_TRIGGER);
        UserMessage("Read: %s\r\n", DataBuff);
        DataBuff[0]= '\0';
        DataBuffCount= 0;
        eod();
    }

    if (strncmp(command, "WIEGAND-WRITE ", 14) == 0)
    {
        if(! RFIDlerConfig.Wiegand_Pulse || ! RFIDlerConfig.Wiegand_Gap)
            commandok= command_nack("Wiegand parameters not set!");
        else
        {
            wiegand_out_enable();
            if(sscanf(command + 14,"%s", local_tmp) == 1)
            {
                commandok= command_ack(NO_DATA);
                write_wiegand(local_tmp);
            }
            else
                commandok= command_nack("Invalid parameters!");
        }
    }

    if (strcmp(command, "WIPE") == 0)
    {
        commandok= command_ack(NO_DATA);
        wipeconfig();
    }

    if (strncmp(command, "WRITE ", 6) == 0)
    {
        if(sscanf(command + 6,"%u %s", &tmpint, local_tmp) == 2)
        {
            if(write_tag(tmpint, local_tmp, VERIFY))
            {
                commandok= command_ack(DATA);
                UserMessage("%s\r\n", local_tmp);
                eod();
            }
            else
                commandok= command_nack("Write failed!");
        }
        else
            commandok= command_nack("Invalid block number or no data!");
    }

    // show help if asked or command not recognised
    if (!commandok)
    {
        if(strcmp(command, "HELP") == 0 || Interface == INTERFACE_CLI)
        {
            command_ack(DATA);
            UserMessage("%s", "    ANALOGUE <# OF SAMPLES>                                      Sample raw coil & output in XML (HEX)\r\n");
            UserMessage("%s", "    APDU <CLA+INS+P1+P2[+LC+DATA][+LE]>                          Transmit (HEX) ISO-7816-4 APDU to SmartCard. Return is [DATA]+<SW1>+<SW2>\r\n");
            UserMessage("%s", "    API                                                          Switch to API mode\r\n");
            UserMessage("%s", "    ASK <HEX UID> <FC> <RATE> <REPEAT>                           Emulate ASK, Field Clock in uS/100, Data Rate in RF/n\r\n");
            UserMessage("%s", "    ATR                                                          Get Answer To Reset from SmartCard\r\n");
            UserMessage("%s", "    AUTH [HEX KEY] [BLOCK]                                       Authenticate in CRYPTO mode\r\n");
            UserMessage("%s", "    AUTOPOT                                                      Auto-Detect ideal POT setting(s)\r\n");
            UserMessage("%s", "    AUTORATE                                                     Auto-Detect data rate\r\n");
            UserMessage("%s", "    AUTORUN [OFF | COMMAND [ARGS]]                               Set/Show startup command\r\n");
            UserMessage("%s", "    AUTOTAG                                                      Auto-Detect TAG type\r\n");
            UserMessage("%s", "    BINTOHEX <BIN>                                               Show BINARY as HEX string\r\n");
            UserMessage("%s", "    BL                                                           Reboot in BOOTLOADER mode\r\n");
            UserMessage("%s", "    CLI                                                          Switch to CLI mode\r\n");
            UserMessage("%s", "    COIL <HIGH|LOW>                                              Set emulator coil output HIGH/LOW\r\n");
            UserMessage("%s", "    CONFIG                                                       Show current NVM config\r\n");
            UserMessage("%s", "    CONVERT <TAGTYPE>                                            Convert VTAG to TAGTYPE\r\n");
            UserMessage("%s", "    CLOCKH <HZ>                                                  Enable H/W TOGGLE CLOCK (timings in Hz, max 250,000)\r\n");
            UserMessage("%s", "    CLOCKP <PW> <PERIOD>                                         Enable H/W PWM CLOCK (timings in uS/100, max 53,687,091)\r\n");
            UserMessage("%s", "    CLOCKT <PERIOD>                                              Enable H/W TOGGLE CLOCK (timings in uS/100, max 53,687,091)\r\n");
            UserMessage("%s", "    CLONE [HEX KEY|PWD]                                          Copy Virtual TAG to TAG (may require auth/login)\r\n");
            UserMessage("%s", "    COPY [TAGTYPE] [HEX KEY|PWD]                                 Copy TAG (and optionally convert) to Virtual TAG (may require auth/login)\r\n");
            UserMessage("%s", "    DEBUG [1-4]                                                  Toggle DEBUG line state (no argument to SHOW current states)\r\n");
            UserMessage("%s", "    DEBUGOFF <0-4>                                               DEBUG off (LOW) (0 for ALL)\r\n");
            UserMessage("%s", "    DEBUGON <0-4>                                                DEBUG on (HIGH) (0 for ALL)\r\n");
            UserMessage("%s", "    DETECT                                                       Detect external clock with READER coil\r\n");
            UserMessage("%s", "    DOOR <CLOSE|OPEN>                                            Close or Open DOOR RELAY\r\n");
            UserMessage("%s", "    DUMP <START BLOCK> [END BLOCK]                               Read and view data block(s) (may require auth/login)\r\n");
            UserMessage("%s", "    EMU <UID>                                                    One-shot emulate UID with current TAG config\r\n");
            UserMessage("%s", "    EMULATOR [BG]                                                Continuously emulate VTAG [optionally in the BackGround]\r\n");
            UserMessage("%s", "    ENCODE <UID> [TAGTYPE]                                       Show raw HEX UID or create VTAG for encoded UID\r\n");
            UserMessage("%s", "    EXAMPLES                                                     Show some emulation examples\r\n");
            UserMessage("%s", "    FSK <HEX UID> <FC> <RATE> <SUB0> <SUB1> <REPEAT>             Emulate FSK, Field Clock in uS/100, Data Rate in RF/n,\r\n");
            UserMessage("%s", "                                                                   Sub Carriers 0/1 in RF/n\r\n");
            UserMessage("%s", "    FREQUENCY                                                    Show resonant frequency of coil\r\n");
            UserMessage("%s", "    HELP                                                         Show this help\r\n");
            UserMessage("%s", "    HEXTOBIN <HEX>                                               Show HEX as BINARY string\r\n");
            UserMessage("%s", "    LOAD                                                         Load config from NVM\r\n");
            UserMessage("%s", "    LED <1-6>                                                    Toggle LED\r\n");
            UserMessage("%s", "    LEDOFF <0-6>                                                 LED off (0 for ALL)\r\n");
            UserMessage("%s", "    LEDON <0-6>                                                  LED on (0 for ALL)\r\n");
            UserMessage("%s", "    LOGIN [PWD] [BLOCK]                                          Authenticate in PASSWORD mode\r\n");
            UserMessage("%s", "    PING                                                         Keepalive - prints 'RFIDler'\r\n");
            UserMessage("%s", "    POTS                                                         Show POT wiper settings\r\n");
            UserMessage("%s", "    POTINC <H|L> <1-255>                                         Increment POT\r\n");
            UserMessage("%s", "    POTDEC <H|L> <1-255>                                         Decrement POT\r\n");
            UserMessage("%s", "    POTSET[V][NV] <H|L> <0-255>                                  Set [Volts][Non Volatile] POT wiper\r\n");
            UserMessage("%s", "    PSK1 <HEX UID> <FC> <RATE> <SUB> <REPEAT>                    Emulate PSK1, Field Clock in uS/100, Data Rate in RF/n,\r\n");
            UserMessage("%s", "                                                                 Sub Carrier in RF/n\r\n");
            UserMessage("%s", "    PWM <FC> <SLEEP> <WAKE> <PW0> <PW1> <GAP> <TXRX> <RXTX>      Set PWM parameters for RWD commands, Field Clock in uS/100, timings in FCs\r\n");
            UserMessage("%s", "    READ <START BLOCK> [END BLOCK]                               Read and store data block(s) (may require auth/login)\r\n");
            UserMessage("%s", "    READER                                                       Go into READER mode (continuously acquire UID)\r\n");
            UserMessage("%s", "    REBOOT                                                       Perform soft reset\r\n");
            UserMessage("%s", "    RTC                                                          Show Real Time Clock\r\n");
            UserMessage("%s", "    RWD <BINARY>                                                 Send binary command/data\r\n");
            UserMessage("%s", "    SAVE                                                         Save current config to NVM\r\n");
            UserMessage("%s", "    SELECT [UID]                                                 Send SELECT command\r\n");
            UserMessage("%s", "    SET BIPHASE <ON|OFF>                                         Set BiPhase encoding\r\n");
            UserMessage("%s", "    SET BITS <BITS>                                              Set number of data bits\r\n");
            UserMessage("%s", "    SET FC <PERIOD>                                              Set Field Clock in uS/100\r\n");
            UserMessage("%s", "    SET INVERT <ON|OFF>                                          Set data inversion\r\n");
            UserMessage("%s", "    SET MANCHESTER <ON|OFF>                                      Set Manchester encoding\r\n");
            UserMessage("%s", "    SET MOD <ASK|FSK|PSK1>                                       Set modulation scheme\r\n");
            UserMessage("%s", "    SET PSK <QUALITY>                                            Set minimum PSK pulse width in uS\r\n");
            UserMessage("%s", "    SET RATE <RATE>                                              Set Data Rate in RF/n (FC/bit)\r\n");
            UserMessage("%s", "    SET REPEAT <REPEAT>                                          Set emulation transmission repetitions\r\n");
            UserMessage("%s", "    SET SUB0 <RATE>                                              Set Sub Carrier 0 data rate in RF/n (FC/bit)\r\n");
            UserMessage("%s", "    SET SUB1 <RATE>                                              Set Sub Carrier 1 data rate in RF/n (FC/bit)\r\n");
            UserMessage("%s", "    SET SYNCBITS <BITS>                                          Set number of SYNC bits\r\n");
            UserMessage("%s", "    SET SYNC[0-3] <HEX>                                          Set SYNC byte 0-3\r\n");
            UserMessage("%s", "    SET TAG <TYPE>                                               Set parameters appropriate for TAG TYPE\r\n");
            UserMessage("%s", "    SET VTAG <TYPE>                                              Set Virtual TAG TYPE\r\n");
            UserMessage("%s", "    SNIFFER                                                      Go into SNIFFER mode (continuously sniff UID)\r\n");
            UserMessage("%s", "    STOP                                                         Stop any running clocks\r\n");
            UserMessage("%s", "    TAGS                                                         Show known TAG TYPES\r\n");
            UserMessage("%s", "    TCONFIG                                                      Show TAG's config block\r\n");
            UserMessage("%s", "    TEST-HITAG                                                   Hitag2 crypto - test correctness & timing\r\n");
            UserMessage("%s", "    TEST-RWD [HEX KEY|PATTERN|PWD]                               Find ideal paramaters for RWD commands\r\n");
            UserMessage("%s", "    TEST-SC                                                      Test ISO-7816 Smartcard (get ATR)\r\n");
            UserMessage("%s", "    TEST-SD                                                      Test SD card (directory listing)\r\n");
            UserMessage("%s", "    TEST-TIMER                                                   Timer tests\r\n");
            UserMessage("%s", "    TEST-WIEGAND                                                 Wiegand loopback test\r\n");
            UserMessage("%s", "    TEST-WIEGAND-READ <DEBUG PIN>                                Wiegand reader test (triggers with DEBUG_PIN_X)\r\n");
            UserMessage("%s", "    TRESET [PWD]                                                 Reset TAG's config block to default\r\n");
            UserMessage("%s", "    TRISTATE <ON|OFF>                                            Switch reader circuit tri-state ON/OFF\r\n");
            UserMessage("%s", "    TWIPE [PWD]                                                  Reset TAG contents to default (*** all data will be lost!)\r\n");
            UserMessage("%s", "    UID                                                          Read TAG UID\r\n");
            UserMessage("%s", "    VERSION                                                      Show firmware version\r\n");
            UserMessage("%s", "    VTAG                                                         Show contents of Virtual TAG\r\n");
            UserMessage("%s", "    VWRITE <BLOCK> <HEX DATA>                                    Write VTAG data block(s)\r\n");
            UserMessage("%s", "    WIEGAND-LEARN                                                Learn Wiegand input timings\r\n");
            UserMessage("%s", "    WIEGAND-OUT <OFF|ON>                                         Set Wiegand output OFF or ON\r\n");
            UserMessage("%s", "    WIEGAND-READ                                                 Read Wiegand input\r\n");
            UserMessage("%s", "    WIEGAND-WRITE <BINARY>                                       Send Wiegand output\r\n");
            UserMessage("%s", "    WIPE                                                         Wipe NVM\r\n");
            UserMessage("%s", "    WRITE <BLOCK> <HEX DATA>                                     Write data block (may require login/auth)\r\n");
            UserMessage("%s", "    WIRING                                                       Show wiring diagram (alias: WIRES PINS)\r\n");
            UserMessage("%s", "    Note: '*' prepended to main prompt indicates unsaved config changes\r\n");
            eod();
        }
        else
            command_unknown();
    }

    // end of command processing
   
    // check for config changes
    if(checkconfigchanged())
        ccprompt= "*";
    else
        ccprompt= "";
    if(RFIDlerConfig.TagType == TAG_TYPE_NONE)
        prompt= "RFIDler";
    else
        prompt= (unsigned char *) TagTypes[RFIDlerConfig.TagType];

    if(Interface == INTERFACE_CLI)
    {
        UserMessage("%s", ccprompt);
        UserMessage("%s", prompt);
        UserMessage("%s", prompt_2);
    }

    return 0;
}

// borrowed from UBW32 source
// Restarts UBW32 with a software reset, which should launch bootloader
// without user having to press PRG button
void parse_BL_packet(void)
{
    unsigned int dma_status;
    unsigned int int_status;

	// Kill USB so that we always re-enumerate when we hit the bootloader
	USBModuleDisable();

	// Set the software key
	SoftwareKey = (unsigned int *)0xA0000000;
	*SoftwareKey = 0x12345678;

	// TEMP : For reset testing
	/* The following code illustrates a software Reset */
	/* perform a system unlock sequence */
    mSYSTEMUnlock(int_status, dma_status);

	/* set SWRST bit to arm reset */
    RSWRSTSET = 1;

    /* read RSWRST register to trigger reset */
    volatile int* p = &RSWRST;
    *p;

    /* prevent any unwanted code execution until reset occurs*/
    while(1);
}

/** EOF main.c *************************************************/

