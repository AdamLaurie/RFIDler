/********************************************************************
 FileName:     	usb_descriptors.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18 or PIC24 USB Microcontrollers
 Hardware:		The code is natively intended to be used on the following
 				hardware platforms: PICDEM™ FS USB Demo Board, 
 				PIC18F87J50 FS USB Plug-In Module, or
 				Explorer 16 + PIC24 USB PIM.  The firmware may be
 				modified for use on other USB platforms by editing the
 				HardwareProfile.h file.
 Complier:  	Microchip C18 (for PIC18) or C30 (for PIC24)
 Company:		Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

*********************************************************************
-usb_descriptors.c-
-------------------------------------------------------------------
Filling in the descriptor values in the usb_descriptors.c file:
-------------------------------------------------------------------

[Device Descriptors]
The device descriptor is defined as a USB_DEVICE_DESCRIPTOR type.  
This type is defined in usb_ch9.h  Each entry into this structure
needs to be the correct length for the data type of the entry.

[Configuration Descriptors]
The configuration descriptor was changed in v2.x from a structure
to a BYTE array.  Given that the configuration is now a byte array
each byte of multi-byte fields must be listed individually.  This
means that for fields like the total size of the configuration where
the field is a 16-bit value "64,0," is the correct entry for a
configuration that is only 64 bytes long and not "64," which is one
too few bytes.

The configuration attribute must always have the _DEFAULT
definition at the minimum. Additional options can be ORed
to the _DEFAULT attribute. Available options are _SELF and _RWU.
These definitions are defined in the usb_device.h file. The
_SELF tells the USB host that this device is self-powered. The
_RWU tells the USB host that this device supports Remote Wakeup.

[Endpoint Descriptors]
Like the configuration descriptor, the endpoint descriptors were 
changed in v2.x of the stack from a structure to a BYTE array.  As
endpoint descriptors also has a field that are multi-byte entities,
please be sure to specify both bytes of the field.  For example, for
the endpoint size an endpoint that is 64 bytes needs to have the size
defined as "64,0," instead of "64,"

Take the following example:
    // Endpoint Descriptor //
    0x07,                       //the size of this descriptor //
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP02_IN,                   //EndpointAddress
    _INT,                       //Attributes
    0x08,0x00,                  //size (note: 2 bytes)
    0x02,                       //Interval

The first two parameters are self-explanatory. They specify the
length of this endpoint descriptor (7) and the descriptor type.
The next parameter identifies the endpoint, the definitions are
defined in usb_device.h and has the following naming
convention:
_EP<##>_<dir>
where ## is the endpoint number and dir is the direction of
transfer. The dir has the value of either 'OUT' or 'IN'.
The next parameter identifies the type of the endpoint. Available
options are _BULK, _INT, _ISO, and _CTRL. The _CTRL is not
typically used because the default control transfer endpoint is
not defined in the USB descriptors. When _ISO option is used,
addition options can be ORed to _ISO. Example:
_ISO|_AD|_FE
This describes the endpoint as an isochronous pipe with adaptive
and feedback attributes. See usb_device.h and the USB
specification for details. The next parameter defines the size of
the endpoint. The last parameter in the polling interval.

-------------------------------------------------------------------
Adding a USB String
-------------------------------------------------------------------
A string descriptor array should have the following format:

rom struct{byte bLength;byte bDscType;word string[size];}sdxxx={
sizeof(sdxxx),DSC_STR,<text>};

The above structure provides a means for the C compiler to
calculate the length of string descriptor sdxxx, where xxx is the
index number. The first two bytes of the descriptor are descriptor
length and type. The rest <text> are string texts which must be
in the unicode format. The unicode format is achieved by declaring
each character as a word type. The whole text string is declared
as a word array with the number of characters equals to <size>.
<size> has to be manually counted and entered into the array
declaration. Let's study this through an example:
if the string is "USB" , then the string descriptor should be:
(Using index 02)
rom struct{byte bLength;byte bDscType;word string[3];}sd002={
sizeof(sd002),DSC_STR,'U','S','B'};

A USB project may have multiple strings and the firmware supports
the management of multiple strings through a look-up table.
The look-up table is defined as:
rom const unsigned char *rom USB_SD_Ptr[]={&sd000,&sd001,&sd002};

The above declaration has 3 strings, sd000, sd001, and sd002.
Strings can be removed or added. sd000 is a specialized string
descriptor. It defines the language code, usually this is
US English (0x0409). The index of the string must match the index
position of the USB_SD_Ptr array, &sd000 must be in position
USB_SD_Ptr[0], &sd001 must be in position USB_SD_Ptr[1] and so on.
The look-up table USB_SD_Ptr is used by the get string handler
function.

-------------------------------------------------------------------

The look-up table scheme also applies to the configuration
descriptor. A USB device may have multiple configuration
descriptors, i.e. CFG01, CFG02, etc. To add a configuration
descriptor, user must implement a structure similar to CFG01.
The next step is to add the configuration descriptor name, i.e.
cfg01, cfg02,.., to the look-up table USB_CD_Ptr. USB_CD_Ptr[0]
is a dummy place holder since configuration 0 is the un-configured
state according to the definition in the USB specification.

********************************************************************/
 
/*********************************************************************
 * Descriptor specific type definitions are defined in:
 * usb_device.h
 *
 * Configuration options are defined in:
 * usb_config.h
 ********************************************************************/
#ifndef __USB_DESCRIPTORS_C
#define __USB_DESCRIPTORS_C
 
/** INCLUDES *******************************************************/
#include "./USB/usb.h"
#include "./USB/usb_function_cdc.h"
#include "HardwareProfile.h"
#include "rfidler.h"

/** CONSTANTS ******************************************************/
#if defined(__18CXX)
#pragma romdata
#endif

/* Device Descriptor */
ROM USB_DEVICE_DESCRIPTOR device_dsc=
{
    0x12,                   // Size of this descriptor in bytes
    USB_DESCRIPTOR_DEVICE,  // DEVICE descriptor type
    0x0200,                 // USB Spec Release Number in BCD format
    CDC_DEVICE,             // Class Code
    0x00,                   // Subclass code
    0x00,                   // Protocol code
    USB_EP0_BUFF_SIZE,      // Max packet size for EP0, see usb_config.h
    0x1D50,                 // Vendor ID - OpenMoko
    0x6098,                 // Product ID: RFIDler LF
    RFIDLER_HW_VERSION,     // Device release number in BCD format
    0x01,                   // Manufacturer string index
    0x02,                   // Product string index
    RFIDLER_SERIAL_NUMBER_STRING_DESC_INDEX,  // Device serial number string index
    0x01                    // Number of possible configurations
};

/* Configuration 1 Descriptor */
ROM BYTE configDescriptor1[]={
    /* Configuration Descriptor */
    0x09,//sizeof(USB_CFG_DSC),    // Size of this descriptor in bytes
    USB_DESCRIPTOR_CONFIGURATION,                // CONFIGURATION descriptor type
    67,0,                   // Total length of data for this cfg
    2,                      // Number of interfaces in this cfg
    1,                      // Index value of this configuration
    0,                      // Configuration string index
    _DEFAULT | _SELF,               // Attributes, see usb_device.h
    50,                     // Max power consumption (2X mA)
							
    /* Interface Descriptor */
    9,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    0,                      // Interface Number
    0,                      // Alternate Setting Number
    1,                      // Number of endpoints in this intf
    COMM_INTF,              // Class code
    ABSTRACT_CONTROL_MODEL,        // Subclass code
    0x00,                 // Protocol code - vendor specific
    0,                      // Interface string index

    /* CDC Class-Specific Descriptors */
    sizeof(USB_CDC_HEADER_FN_DSC),
    CS_INTERFACE,
    DSC_FN_HEADER,
    0x10,0x01,

    sizeof(USB_CDC_ACM_FN_DSC),
    CS_INTERFACE,
    DSC_FN_ACM,
    USB_CDC_ACM_FN_DSC_VAL,

    sizeof(USB_CDC_UNION_FN_DSC),
    CS_INTERFACE,
    DSC_FN_UNION,
    CDC_COMM_INTF_ID,
    CDC_DATA_INTF_ID,

    sizeof(USB_CDC_CALL_MGT_FN_DSC),
    CS_INTERFACE,
    DSC_FN_CALL_MGT,
    0x00,
    CDC_DATA_INTF_ID,

    /* Endpoint Descriptor */
    //sizeof(USB_EP_DSC),DSC_EP,_EP02_IN,_INT,CDC_INT_EP_SIZE,0x02,
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP02_IN,            //EndpointAddress
    _INTERRUPT,                       //Attributes
    0x08,0x00,                  //size
    0x02,                       //Interval

    /* Interface Descriptor */
    9,//sizeof(USB_INTF_DSC),   // Size of this descriptor in bytes
    USB_DESCRIPTOR_INTERFACE,               // INTERFACE descriptor type
    1,                      // Interface Number
    0,                      // Alternate Setting Number
    2,                      // Number of endpoints in this intf
    DATA_INTF,              // Class code
    0,                      // Subclass code
    NO_PROTOCOL,            // Protocol code
    0,                      // Interface string index
    
    /* Endpoint Descriptor */
    //sizeof(USB_EP_DSC),DSC_EP,_EP03_OUT,_BULK,CDC_BULK_OUT_EP_SIZE,0x00,
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP03_OUT,            //EndpointAddress
    _BULK,                       //Attributes
    0x40,0x00,                  //size
    0x00,                       //Interval

    /* Endpoint Descriptor */
    //sizeof(USB_EP_DSC),DSC_EP,_EP03_IN,_BULK,CDC_BULK_IN_EP_SIZE,0x00
    0x07,/*sizeof(USB_EP_DSC)*/
    USB_DESCRIPTOR_ENDPOINT,    //Endpoint Descriptor
    _EP03_IN,            //EndpointAddress
    _BULK,                       //Attributes
    0x40,0x00,                  //size
    0x00,                       //Interval
};


//Language code string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[1];}sd000={
sizeof(sd000),USB_DESCRIPTOR_STRING,{0x0409}};

//Manufacturer string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[18];}sd001={
sizeof(sd001),USB_DESCRIPTOR_STRING,
{'A','p','e','r','t','u','r','e',' ','L','a','b','s',' ','L','t','d','.'
}};

//Product string descriptor
ROM struct{BYTE bLength;BYTE bDscType;WORD string[10];}sd002={
sizeof(sd002),USB_DESCRIPTOR_STRING,
{'R','F','I','D','l','e','r','-','L','F'}
};


// Buffer to put USB serial number (Unicode); reordered version of factory programmed Ethernet MAC
// Note this string descriptor is 'static' as it is modified on boot
static struct{BYTE bLength;BYTE bDscType;WORD string[12];}sd003={
sizeof(sd003),USB_DESCRIPTOR_STRING,
{'0','1','2','3','4','5','6','7','8','9','A','B'}
};

//Array of configuration descriptors
ROM BYTE *ROM USB_CD_Ptr[]=
{
    (ROM BYTE *ROM)&configDescriptor1
};
//Array of string descriptors
ROM BYTE *ROM USB_SD_Ptr[USB_NUM_STRING_DESCRIPTORS]=
{
    (ROM BYTE *ROM)&sd000,
    (ROM BYTE *ROM)&sd001,
    (ROM BYTE *ROM)&sd002,
    (ROM BYTE *ROM)&sd003
};

    /*
        MS_OS_DESCRIPTOR, MS_COMPAT_ID_FEATURE_DESC and MS_EXT_PROPERTY_FEATURE_DESC
        are defined in Microchip's USB Library for Applications dated 2013-12-20
        Adapted for RFIDler-LF in July 2017.
        Note: if string text is changed ensure usb_config.h string lengths are updated too!
    */

    //Microsoft "OS Descriptor" - This descriptor is based on a Microsoft specific
    //specification (not part of the standard USB 2.0 specs or class specs).
    //Implementing this special descriptor allows WinUSB driver package installation
    //to be automatic on Windows 8.  For additional details, see:
    //http://msdn.microsoft.com/en-us/library/windows/hardware/hh450799(v=vs.85).aspx
    const MS_OS_DESCRIPTOR MSOSDescriptor =
    {
        sizeof(MSOSDescriptor),         //bLength - lenght of this descriptor in bytes
        USB_DESCRIPTOR_STRING,          //bDescriptorType - "string"
        {'M','S','F','T','1','0','0'},  //qwSignature - special values that specifies the OS descriptor spec version that this firmware implements
        GET_MS_DESCRIPTOR,              //bMS_VendorCode - defines the "GET_MS_DESCRIPTOR" bRequest literal value
        0x00                            //bPad - always 0x00
    };


    //Extended Compat ID OS Feature Descriptor
    const MS_COMPAT_ID_FEATURE_DESC CompatIDFeatureDescriptor =
    {
        //----------Header Section--------------
        sizeof(CompatIDFeatureDescriptor),  //dwLength
        0x0100,                             //bcdVersion = 1.00
        EXTENDED_COMPAT_ID,                 //wIndex
        0x01,                               //bCount - 0x01 "Function Section(s)" implemented in this descriptor
        {0,0,0,0,0,0,0},                    //Reserved[7]
        //----------Function Section 1----------
        0x00,                               //bFirstInterfaceNumber: the WinUSB interface in this firmware is interface #0
        0x01,                               //Reserved - fill this reserved byte with 0x01 according to documentation
        {'W','I','N','U','S','B',0x00,0x00},//compatID - "WINUSB" (with two null terminators to fill all 8 bytes)
        {0,0,0,0,0,0,0,0},                  //subCompatID - eight bytes of 0
        {0,0,0,0,0,0}                       //Reserved
    };


    //Extended Properties OS Feature Descriptor
    const MS_EXT_PROPERTY_FEATURE_DESC ExtPropertyFeatureDescriptor =
    {
        //----------Header Section--------------
        sizeof(ExtPropertyFeatureDescriptor),   //dwLength
        0x0100,                                 //bcdVersion = 1.00
        EXTENDED_PROPERTIES,                    //wIndex
        3,                                      //wCount - number of "Property Sections" implemented in this descriptor
        //----------Property Section 1----------
        132,                                    //dwSize - 132 bytes in this Property Section
        0x00000001,                             //dwPropertyDataType (Unicode string)
        40,                                     //wPropertyNameLength - 40 bytes in the bPropertyName field
        {'D','e','v','i','c','e','I','n','t','e','r','f','a','c','e','G','U','I','D', 0x0000},  //bPropertyName - "DeviceInterfaceGUID"
        78,                                     //dwPropertyDataLength - 78 bytes in the bPropertyData field (GUID value in UNICODE formatted string, with braces and dashes)
        //The below value is the Device Interface GUID (a 128-bit long "globally unique identifier")
        //Please modify the GUID value in your application before moving to production.
        //When you change the GUID, you must also change the PC application software
        //that connects to this device, as the software looks for the device based on
        //VID, PID, and GUID.  All three values in the PC application must match
        //the values in this firmware.
        //The GUID value can be a randomly generated 128-bit hexadecimal number,
        //formatted like the below value.  The actual value is not important,
        //so long as it is almost certain to be globally unique, and matches the
        //PC software that communicates with this firmware.
        //*HACK* instead of generating unique GUID we use standard GUID for COM & LPT ports
        //= '{4d36e978-e325-11ce-bfc1-08002be10318}' to get installed as a COM port
        {'{','4','d','3','6','e','9','7','8','-','e','3','2','5','-','1','1','c','e','-','b','f','c','1','-','0','8','0','0','2','b','e','1','0','3','1','8','}',0x0000},  //bPropertyData - this is the actual GUID value.  Make sure this matches the PC application code trying to connect to the device.
        //----------Property Section 2----------
        14 + 12 + 22,                           //dwSize - 14 bytes + 2 nul terminated Unicode strings in this Property Section
        0x00000001,                             //dwPropertyDataType (Unicode string)
        12,                                     //wPropertyNameLength - 12 bytes in the bPropertyName field
        {'L','a','b','e','l', 0x0000},          //bPropertyName - "Label"
        22,                                     //dwPropertyDataLength - 22 bytes in the bPropertyData field
                                                //bPropertyData - device label = "RFIDler-LF"
        {'R','F','I','D','l','e','r','-','L','F',0x0000},
        //----------Property Section 3----------
        14 + 12 + 76,                           //dwSize - 14 bytes + 2 nul terminated Unicode strings in this Property Section
        0x00000002,                             //dwPropertyDataType (Unicode string with environment variables)
        12,                                     //wPropertyNameLength - 12 bytes in the bPropertyName field
        {'I','c','o','n','s', 0x0000},          //bPropertyName - "Icons"
        76,                                     //dwPropertyDataLength - 22 bytes in the bPropertyData field
                                                //bPropertyData - "%SystemRoot%\\system32\\Shell32.dll,-13"
        {'%','S','y','s','t','e','m','R','o','o','t','%','\\','s','y','s','t','e','m','3','2','\\','S','h','e','l','l','3','2','.','d','l','l',',','-','1','3',0x0000}
    };

#pragma code

// Read device's unique Ethernet MAC Address, use for USB serial number
void MakeUSBSerialNumberFromEMAC(void)
{
    WORD sernum;
    WORD index = 0;

    while (index < 12)
    {
        WORD d = 0;
        // choose part of the Ethernet MAC address to read
        if (index == 0)
            sernum = EMAC1SA0;
        else if (index == 4)
            sernum = EMAC1SA1;
        else
            sernum = EMAC1SA2;

        // convert 16 bits to Unicode hexadecimal format
        while ((d < 4) && (index < 12))
        {
            WORD unichar = sernum & 0x000f;
            if (unichar < 10)
                unichar += '0';
            else
                unichar += ('A' - 10);
            sd003.string[index++] = unichar;
            sernum >>= 4; // shift right
            d++;
        }
    }
 }
#endif
/** EOF usb_descriptors.c ****************************************************/
