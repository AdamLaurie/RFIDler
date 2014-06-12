RFIDler
=======

Firmware
========

The 'firmware' directory contains code for the dev platform(s).

Currently that is Pic32, but we will add a new section if and when required.

Hardware
========

	Pic32
	=====

	The main microcontroller is a Microchip PIC32MX795F512L

	  http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en545660

Software Build environment
==========================

	The project was developed in Mplab-X IDE V1.41 under Linux, but can also be built under Windows & Mac:

	  http://www.microchip.com/pagehandler/en-us/family/mplabx/

	The compiler used was the free version of Microchip's XC32 V1.21:

	  http://www.microchip.com/pagehandler/en-us/devtools/mplabxc/home.html

	USB stack and peripheral support is provided by Microchip Application Library v2013-06-15:

      Linux:
      
        http://ww1.microchip.com/downloads/en/softwarelibrary/microchip-libraries-for-applications-v2013-06-15-linux-installer.run

        *** Install to '/microchip_solutions_v2013-06-15'

      Windows:

        http://ww1.microchip.com/downloads/en/softwarelibrary/microchip-libraries-for-applications-v2013-06-15-windows-installer.exe

        *** Install to installer default location

      Mac:

        http://ww1.microchip.com/downloads/en/softwarelibrary/microchip-libraries-for-applications-v2013-06-15-osx-installer.dmg

        *** Install to default location, which will normally be your home directory.

Bootloader
==========

      USB HID Bootloader is provided by the UBW32 project:

        http://www.schmalzhaus.com/UBW32/FW/HIDBoot.X/HIDBoot.X.zip

      Bootloader client is mphidflash:

        http://code.google.com/p/mphidflash/

      For convenience, a copy of the bootloader hex and an MPLAB hex load project is provided in firmware/Pic32/HIDBoot_MX795_Hex_Load.X

Software Build
==============

    Install packages as above.

    Clone this repo to your local hard disk.

    Start MPLAB X IDE and choose:

        File/Open Project/

            Browse to RFIDler.X and click 'Open Project'

    If you are running Windows, you will need to change the default Linux library to the local Windows version:

        In the 'Projects' window, expand RFIDler/Libraries

            Highlight the only entry (/opt/microchip/xc32/v1.21/pic32mx/lib/libmchp_peripheral_32MX795F512L.a) and right-click

               Select 'Remove'

            Copy the libmchp_peripheral_32MX795F512L.a file:

                from your local XC32 installation (normally 'Program Files (x86)/Microchip/xc32') and drill down to v1.21/pic32mx/lib/

                to your RFIDler.X project directory.

            Select 'Libraries' and right-click

               Select 'Add Library/Object file'

                   Browse to your RFIDler.X project and select libmchp_peripheral_32MX795F512L.a

    (There are bugs in MPLAB X and GNU make such that paths to libraries containing spaces are not always processed correctly,

    and the default install path on Windows contains spaces so making the copy is the simplest solution.)


    If you are running Mac OS X, you will need to change the default Linux library to the local Mac version:

       In the 'Projects' window, expand RFIDler/Libraries

          Highlight the only entry (/opt/microchip/xc32/v1.21/pic32mx/lib/libmchp_peripheral_32MX795F512L.a) and ctrl-click

            Select 'Remove'

          Select 'Libraries' and ctrl-click

            Select 'Add Library/Object file'

               Browse to your xc32 installation directory (default is /Applications/microchip/xc32) and drill down to v1.21/pic32mx/lib/

                  select libmchp_peripheral_32MX795F512L.a

       In the projects window, highlight 'RFIDler' and ctl-click

         Select 'Properties'

           For both 'Conf: [default]' and 'Conf: [debug]', perform the following steps:

             Select 'xc32-gcc'

                In the 'Option categories' pulldown menu, select 'Preprocessing and messages'

                   Double-click on the 'Include directories' window

                      Edit the two 'microchip_solutions_v2013-06-15' entries, such that they point at your local installation
                      (prepending '../../../../..' should suffice if you installed to the default location, and your project
                      is also in the default location for projects)

                      Edit the '/opt/microchip/xc32' entry, and substitute '/Applications/' for '/opt/'

        Select 'Run/Clean and Build Main Project'

Connections
===========

	The device can be powered via the USB port, and, if connected to a PC, will provide a
	management CLI/API via USB-Serial CDC at 115200 baud (8 bit, No Parity, 1 Stop Bit, No Handshaking/Flow Control).

        The CLI/API is also accessible via 3.3v or 5v UART on pins RF4 (UART2 RX) and RF5 (UART2 TX)

        When you connect with USB for the first time, you may need to perform some configuration steps:

          Linux:

             Create a rule file for UDEV to allow non-root access to the file, and also disable modem manager access. An appropriate file can be found in the MPLAB project
             under the "Linux Support" tab. Copy this file to /etc/udev/rules.d and run 'sudo udevadm control --reload-rules'

          Windows:

             Windows drivers can be found in the 'Windows Driver' tab of the MPLAB project

        To connect, any serial terminal emulator should work, but we recommend:

          Linux: minicom ('sudo apt-get install minicom')

          Windows: PuTTY (http://www.chiark.greenend.org.uk/~sgtatham/putty/)

          Mac OS X: SerialTools (free from the App Store)

        Once connected, hit <ENTER> to see the HELP screen and switch to CLI mode, or send commands to remain in API mode.
        In API mode, all commands are as per CLI mode, and will be ACK'd by a single '.' or NACK'd by '!' if command fails
        or '?' if it is not recognised. Other output is command dependant.

Loading new Firmware
====================

	Enter bootloader mode either from the menu ('BL'), or by holding down button 'PROG' while simultaneously plugging in the USB cable or pressing the 'RESET' button.

	LED1 will blink to confirm bootloader mode has been entered.

        Linux:

             'dmesg' should show the following:

	         generic-usb 0003:04D8:003C.0003: hiddev0,hidraw1: USB HID v1.11 Device [Microchip Technology Inc. USB HID Bootloader] on usb-0000:00:1d.0-1.1.2.1/input0

	     To flash the code, 'cd' to the top of the repo and run:

	         mphidflash -r -w firmware/Pic32/RFIDler.X/dist/default/production/RFIDler.X.production.hex

 	     The device will be programmed and will then reboot. 'dmesg' should show:

	         usb 2-1.1.2.1: USB disconnect, device number 19
	         usb 2-1.1.2.1: new full speed USB device number 20 using ehci_hcd
	         cdc_acm 2-1.1.2.1:1.0: This device cannot do calls on its own. It is not a modem.
	         cdc_acm 2-1.1.2.1:1.0: ttyACM3: USB ACM device

        Windows:

            ???

        Mac OS X:

            ???




