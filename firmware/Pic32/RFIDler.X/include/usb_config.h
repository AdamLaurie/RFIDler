/********************************************************************
 FileName:     	usb_config.h
 Dependencies: 	Always: GenericTypeDefs.h, usb_device.h
               	Situational: usb_function_hid.h, usb_function_cdc.h, usb_function_msd.h, etc.
 Processor:		PIC18 or PIC24 USB Microcontrollers
 Hardware:		The code is natively intended to be used on the following
 				hardware platforms: PICDEM� FS USB Demo Board, 
 				PIC18F87J50 FS USB Plug-In Module, or
 				Explorer 16 + PIC24 USB PIM.  The firmware may be
 				modified for use on other USB platforms by editing the
 				HardwareProfile.h file.
 Complier:  	Microchip C18 (for PIC18) or C30 (for PIC24)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
 *******************************************************************/

/*********************************************************************
 * Descriptor specific type definitions are defined in: usbd.h
 ********************************************************************/

#ifndef USBCFG_H
#define USBCFG_H

/** DEFINITIONS ****************************************************/
#define USB_EP0_BUFF_SIZE		64	// Valid Options: 8, 16, 32, or 64 bytes.
								// Using larger options take more SRAM, but
								// does not provide much advantage in most types
								// of applications.  Exceptions to this, are applications
								// that use EP0 IN or OUT for sending large amounts of
								// application related data.
									
#define USB_MAX_NUM_INT     	1   // For tracking Alternate Setting

//Device descriptor - if these two definitions are not defined then
//  a ROM USB_DEVICE_DESCRIPTOR variable by the exact name of device_dsc
//  must exist.
#define USB_USER_DEVICE_DESCRIPTOR &device_dsc
#define USB_USER_DEVICE_DESCRIPTOR_INCLUDE extern ROM USB_DEVICE_DESCRIPTOR device_dsc

//Configuration descriptors - if these two definitions do not exist then
//  a ROM BYTE *ROM variable named exactly USB_CD_Ptr[] must exist.
#define USB_USER_CONFIG_DESCRIPTOR USB_CD_Ptr
#define USB_USER_CONFIG_DESCRIPTOR_INCLUDE extern ROM BYTE *ROM USB_CD_Ptr[]

//Make sure only one of the below "#define USB_PING_PONG_MODE"
//is uncommented.
//#define USB_PING_PONG_MODE USB_PING_PONG__NO_PING_PONG
#define USB_PING_PONG_MODE USB_PING_PONG__FULL_PING_PONG
//#define USB_PING_PONG_MODE USB_PING_PONG__EP0_OUT_ONLY
//#define USB_PING_PONG_MODE USB_PING_PONG__ALL_BUT_EP0		//NOTE: This mode is not supported in PIC18F4550 family rev A3 devices


//#define USB_POLLING
#define USB_INTERRUPT

/* Parameter definitions are defined in usb_device.h */
#define USB_PULLUP_OPTION USB_PULLUP_ENABLE
//#define USB_PULLUP_OPTION USB_PULLUP_DISABLED

#define USB_TRANSCEIVER_OPTION USB_INTERNAL_TRANSCEIVER
//External Transceiver support is not available on all product families.  Please
//  refer to the product family datasheet for more information if this feature
//  is available on the target processor.
//#define USB_TRANSCEIVER_OPTION USB_EXTERNAL_TRANSCEIVER

// we're doing CDC serial so we need to be at least Full speed
#define USB_SPEED_OPTION USB_FULL_SPEED
//#define USB_SPEED_OPTION USB_LOW_SPEED //(not valid option for PIC24F devices)


//When implemented, the Microsoft OS Descriptor allows the WinUSB driver package
//installation to be automatic on Windows 8, and is therefore recommended.

    #define MICROSOFT_OS_DESCRIPTOR_INDEX   (unsigned char)0xEE //Magic string index number for the Microsoft OS descriptor
    #define GET_MS_DESCRIPTOR               (unsigned char)0x2A //(arbitarily assigned, but should not clobber/overlap normal bRequests)
                                                                // Vendor Code, arbitrary non-zero value chosen once by vendor, DO NOT CHANGE as cached by Windows
    #define EXTENDED_COMPAT_ID              (WORD)0x0004
    #define EXTENDED_PROPERTIES             (WORD)0x0005
    typedef struct __attribute__ ((packed)) _MS_OS_DESCRIPTOR{BYTE bLength;BYTE bDscType;WORD string[7];BYTE vendorCode;BYTE bPad;}MS_OS_DESCRIPTOR;
    typedef struct __attribute__ ((packed)) _MS_COMPAT_ID_FEATURE_DESC{DWORD dwLength;WORD bcdVersion;WORD wIndex;BYTE bCount;BYTE Reserved[7];BYTE bFirstInterfaceNumber;BYTE Reserved1;BYTE compatID[8];BYTE subCompatID[8];BYTE Reserved2[6];}MS_COMPAT_ID_FEATURE_DESC;
    // Note below structure edited for RFIDler to have 3 features, Note character array sizes must match the Unicode string lenghts!
    typedef struct __attribute__ ((packed)) _MS_EXT_PROPERTY_FEATURE_DESC{DWORD dwLength;WORD bcdVersion;WORD wIndex;WORD wCount;
        DWORD dwSize1;DWORD dwPropertyDataType1;WORD wPropertyNameLength1;WORD bPropertyName1[20];DWORD dwPropertyDataLength1;WORD bPropertyData1[39];
        DWORD dwSize2;DWORD dwPropertyDataType2;WORD wPropertyNameLength2;WORD bPropertyName2[6];DWORD dwPropertyDataLength2;WORD bPropertyData2[11];
        DWORD dwSize3;DWORD dwPropertyDataType3;WORD wPropertyNameLength3;WORD bPropertyName3[6];DWORD dwPropertyDataLength3;WORD bPropertyData3[38];
        }MS_EXT_PROPERTY_FEATURE_DESC;
    extern ROM MS_OS_DESCRIPTOR MSOSDescriptor;
    extern ROM MS_COMPAT_ID_FEATURE_DESC CompatIDFeatureDescriptor;
    extern ROM MS_EXT_PROPERTY_FEATURE_DESC ExtPropertyFeatureDescriptor;


#define USB_SUPPORT_DEVICE

#define USB_NUM_STRING_DESCRIPTORS 4

//#define USB_INTERRUPT_LEGACY_CALLBACKS
#define USB_ENABLE_ALL_HANDLERS
//#define USB_ENABLE_SUSPEND_HANDLER
//#define USB_ENABLE_WAKEUP_FROM_SUSPEND_HANDLER
//#define USB_ENABLE_SOF_HANDLER
//#define USB_ENABLE_ERROR_HANDLER
//#define USB_ENABLE_OTHER_REQUEST_HANDLER
//#define USB_ENABLE_SET_DESCRIPTOR_HANDLER
//#define USB_ENABLE_INIT_EP_HANDLER
//#define USB_ENABLE_EP0_DATA_HANDLER
//#define USB_ENABLE_TRANSFER_COMPLETE_HANDLER

/** DEVICE CLASS USAGE *********************************************/
#define USB_USE_CDC

/** ENDPOINTS ALLOCATION *******************************************/
#define USB_MAX_EP_NUMBER	    3

/* CDC */
#define CDC_COMM_INTF_ID        0x0
#define CDC_COMM_EP              2
#define CDC_COMM_IN_EP_SIZE      8

#define CDC_DATA_INTF_ID        0x01
#define CDC_DATA_EP             3
#define CDC_DATA_OUT_EP_SIZE    64
#define CDC_DATA_IN_EP_SIZE     64

//#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D2 //Send_Break command
#define USB_CDC_SUPPORT_ABSTRACT_CONTROL_MANAGEMENT_CAPABILITIES_D1 //Set_Line_Coding, Set_Control_Line_State, Get_Line_Coding, and Serial_State commands
/** DEFINITIONS ****************************************************/

#define RFIDLER_SERIAL_NUMBER_STRING_DESC_INDEX   3


#endif //USBCFG_H
