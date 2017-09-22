# RFIDler


## Firmware

The 'firmware' directory contains code for the dev platform(s).
Currently that is Pic32, but we will add a new section if and when required.

## Hardware

A fully built RFIDler board can be purchased here: [http://aperturelabs.com/tools.html](http://aperturelabs.com/tools.html)

### Pic32

The main microcontroller is a [Microchip PIC32MX795F512L](http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en545660)

## Software Build environment

The project was developed in Mplab-X IDE V3.20 under Linux, but can also be built under Windows & Mac:

* [Linux] (http://www.microchip.com/mplabx-ide-linux-installer)

* [Windows] (http://www.microchip.com/mplabx-ide-windows-installer)

* [Mac] (http://www.microchip.com/mplabx-ide-osx-installer)

The compiler used was the free version of Microchip's XC32 V1.40:

* [Linux] (http://www.microchip.com/mplabxc32linux)

* [Windows] (http://www.microchip.com/mplabxc32windows)

* [Mac] (http://www.microchip.com/mplabxc32osx)

USB stack and peripheral support is provided by [Microchip Application Library v2013-06-15] (http://www.microchip.com/pagehandler/en-us/devtools/mla/archives.html):

* [Linux](http://ww1.microchip.com/downloads/en/softwarelibrary/microchip-libraries-for-applications-v2013-06-15-linux-installer.run)
  - Install to /opt/microchip/microchip_solutions_v2013-06-15/
  - Note: if the installer fails to start, try adding the run-time option '--mode text'
* [Windows](http://ww1.microchip.com/downloads/en/softwarelibrary/microchip-libraries-for-applications-v2013-06-15-windows-installer.exe)
  - Install to installer default location
* [Mac](http://ww1.microchip.com/downloads/en/softwarelibrary/microchip-libraries-for-applications-v2013-06-15-osx-installer.dmg)
  - Install to installer default location

and [PIC32 Peripheral Library] (http://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC32%20Peripheral%20Library):

* [Linux](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC32%20Legacy%20Peripheral%20Libraries%20Linux.tar)
  - Install to /opt/microchip/xc32/v1.40
* [Windows](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC32%20Legacy%20Peripheral%20Libraries.zip)
  - Install to installer default location
* [Mac](http://ww1.microchip.com/downloads/en/DeviceDoc/PIC32%20Legacy%20Peripheral%20Libraries%20MACOS.zip)
  - Install to installer default location

### Bootloader

When the Bootloader is running the RFIDler appears on the USB as a HID, and waits for new RFIDler firmware to install in Flash memory.
There are several ways of entering the Bootloader, see "Loading new Firmware" section below.

USB HID Bootloader is provided by the [UBW32 project](http://www.schmalzhaus.com/UBW32/FW/HIDBoot.X/HIDBoot.X.zip)

For convenience, a copy of the bootloader hex and an MPLAB hex load project is provided in `firmware/Pic32/HIDBoot_MX795_Hex_Load.X`

The Bootloader client, mphidflash, runs on Linux/Mac/Windows and transmits & verifies the new firmware.

https://github.com/ApertureLabsLtd/mphidflash

#### Notes

mphidflash v1.3 has some known bugs where for some ROM binaries programming fails and a verification error is reported.
	
If you hit this problem check for a newer release of mphidflash. Pre-compiled executables for all platforms are available [here](https://github.com/ApertureLabsLtd/mphidflash)

### Software Build

Install packages as above.

Clone this repo to your local hard disk.

1. Start MPLAB X IDE
2. Choose `File/Open Project/`
3. Browse to RFIDler.X and click 'Open Project'

#### Windows

If you are running Windows, you will need to change the default Linux library to the local Windows version:

UPDATE NEEDED TO THIS SECTION!

(There are bugs in MPLAB X and GNU make such that paths to libraries containing spaces are not always processed correctly, 
and the default install path on Windows contains spaces so making the copy is the simplest solution.)

#### Mac OS X

If you are running Mac OS X, you will need to change the default Linux library to the local Mac version:

UPDATE NEEDED TO THIS SECTION!

### Connections

The device can be powered via the USB port, and, if connected to a PC, will provide a
management CLI/API via USB-Serial CDC at 115200 baud (8 bit, No Parity, 1 Stop Bit, No Handshaking/Flow Control).

The CLI/API is also accessible via 3.3v or 5v UART on pins RG7 (UART3 RX) and RG8 (UART3 TX), also at 115200 baud.

When you connect with USB for the first time, you may need to perform some configuration steps:

#### Linux

Create a rule file for UDEV to allow non-root access to the file, and also disable modem manager access. An appropriate file can be found in the MPLAB project
under the "Linux Support" tab. Copy this file to `/etc/udev/rules.d` and run `sudo udevadm control --reload-rules`

This file can also be found in this repo at: linux-support/71-rfidler-lf-cdc-blacklist.rules

####  Windows

Windows drivers can be found in the 'Windows Driver' tab of the MPLAB project


To connect, any serial terminal emulator should work, but we recommend:

* Linux: minicom (`sudo apt-get install minicom`)
* Windows: [PuTTY](http://www.chiark.greenend.org.uk/~sgtatham/putty/)
* Mac OS X: SerialTools (free from the App Store)

Example linux connection:

	minicom -D /dev/ttyACM1 -b 115200 

Once connected, hit `<ENTER>` to see the HELP screen and switch to CLI mode, or send commands to remain in API mode.

In API mode, all commands are as per CLI mode, and will be ACK'd by a single '.' or NACK'd by '!' if command fails
or '?' if it is not recognised. Other output is command dependant.

## Loading new Firmware

Enter bootloader mode 

* either from the menu (`BL`)
* _or_ by holding down button `BOOTLOADER` while simultaneously 
	* plugging in the USB cable 
	* _or_ pressing the 'RESET' button.

LED6 and LED5 will show stable orange light to confirm bootloader mode has been entered.

	#~/tools/mphidflash-1.6/binaries/mphidflash-1.6-linux-64 -r -w firmware/Pic32/RFIDler.X/dist/debug/production/RFIDler.X.production.hex 
	USB HID device found: 503808 bytes free
	Device family: PIC32

	Erasing...
	Writing hex file 'RFIDler.X.production.hex':......[...removed for brevity...]
	Verifying:.... [...removed for brevity...]
	Resetting device...

You can verify the flashing via `version`

	*RFIDler> version
	0071-beta
	

### Linux:

`dmesg` should show the following:

	generic-usb 0003:04D8:003C.0003: hiddev0,hidraw1: USB HID v1.11 Device [Microchip Technology Inc. USB HID Bootloader] on usb-0000:00:1d.0-1.1.2.1/input0

To flash the code, `cd` to the top of the repo and run:

		mphidflash -r -w firmware/Pic32/RFIDler.X/dist/default/production/RFIDler.X.production.hex

The device will be programmed and will then reboot. `dmesg` should show:

	usb 2-1.1.2.1: USB disconnect, device number 19
	usb 2-1.1.2.1: new full speed USB device number 20 using ehci_hcd
	cdc_acm 2-1.1.2.1:1.0: This device cannot do calls on its own. It is not a modem.
	cdc_acm 2-1.1.2.1:1.0: ttyACM3: USB ACM device

### Windows

???

### Mac OS X

## Install mphidflash from source
Option 1, v1.6:
```shell
curl https://github.com/ApertureLabsLtd/mphidflash/blob/master/dist/mphidflash-1.6-src.tar.gz > mphidflash1-6.tar.gz
mkdir mphidflash1-6
tar -zxvf mphidflash1-6.tar.gz -C mphidflash1-6
cd mphidflash1-6
mkdir binaries
sudo make install64
```

Option 2, latest:
```shell
git clone https://github.com/ApertureLabsLtd/mphidflash.git
cd mphidflash
sudo make install64
```

## Flash device
```shell
cd #RFIDler repo
mphidflash -r -w firmware/Pic32/RFIDler.X/dist/debug/production/RFIDler.X.production.hex
```
