# RFIDler CLI python wrapper

---

[rfidler.py](rfidler.py) RFIDler Software Defined RFID device python wrapper

## Usage
```
./rfidler.py [PORT] <COMMAND> [ARGS] [COMMAND [ARGS] ...]

   Commands:

     DEBUG <OFF|ON>                      Show serial comms
     FLASH[P] <IMAGE.HEX>                Set bootloader mode and flash IMAGE.HEX [in Production mode]
     PLOT[N] <SAMPLES>                   Plot raw coil samples ([N]o local clock)
     STORE[N] <SAMPLES> <file_prefix>    Save raw coil samples to file ([N]o local clock)
     LOAD <file>                         Load and plot saved sample-file
     PROMPT <MESSAGE>                    Print MESSAGE and wait for <ENTER>
     QUIET                               Suppress confirmation of sent command (show results only)
     SLEEP <SECONDS>                     Pause for SECONDS
     HELP COMMANDS                       Print RFIDler Commands
     TEST                                Run hardware manufacturing test suite

   Commands will be executed sequentially.
   Unrecognized commands will be passed directly to RFIDler.
   Commands with arguments to be passed directly should be quoted. e.g. "SET TAG FDXB"
```

## Example
For more detailed information see [RFIDler/wiki](https://github.com/AdamLaurie/RFIDler/wiki/How)

 Set the tag type to ASKRAW, set the High Potentiometer to max, and plot 500 samples :
&nbsp;&nbsp;`./rfidler.py 'set tag askraw' 'potset h 255' plot 500`

Set tag type to FSK, set the High Potentiometer to max, set frequency to 134.2KHz and plot 500 samples :  
&nbsp;&nbsp;`./rfidler.py 'set tag fskraw' 'potset h 255' 'set fc 745' plot 500`

Note:
The calculation for frequency is simply 1 over the frequency, eg:  
&nbsp;&nbsp;$`1 / 134200 = 0.00000745`$




Which translates as 'set the tag to ASKRAW, set the High Potentiometer to max, and plot 500 samples.

## Install

   you can run from this directory or optionally install it

To install use the command: `pip install`

### See Also
RFIDler Wiki:  https://github.com/AdamLaurie/RFIDler/wiki/How
<br>Discussion forum : http://rfidler.org/
<br>github : https://github.com/AdamLaurie/RFIDler/
<br>Copying : [COPYING](/COPYING)
