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
     QUIET                               Supress confirmation of sent command (show results only)
     SLEEP <SECONDS>                     Pause for SECONDS
     HELP COMMANDS                       Print RFIDler Commands
     TEST                                Run hardware manufacting test suite

   Commands will be executed sequentially.
   Unrecognised commands will be passed directly to RFIDler.
   Commands with arguments to be passed directly should be quoted. e.g. "SET TAG FDXB"
```

## Install

   you can run from this directory or optionally install it

To install use the command: `pip install`

### See Also
RFIDler Wiki:  https://github.com/AdamLaurie/RFIDler/wiki/How
<br>Discussion forum : http://rfidler.org/
<br>github : https://github.com/AdamLaurie/RFIDler/
<br>Copying : [COPYING](/COPYING)
