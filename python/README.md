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

<details><summary>RFIDler Commands:</summary>

```
    ANALOGUE[N] <# OF SAMPLES>                                   Sample raw coil ([N]o local clock) & output in XML (HEX)
    APDU <CLA+INS+P1+P2[+LC+DATA][+LE]>                          Transmit (HEX) ISO-7816-4 APDU to SmartCard. Return is [DATA]+<SW1>+<SW2>
    API                                                          Switch to API mode
    ASK <HEX UID> <FC> <RATE> <REPEAT>                           Emulate ASK, Field Clock in uS/100, Data Rate in RF/n
    ATR                                                          Get Answer To Reset from SmartCard
    AUTH [HEX KEY] [BLOCK]                                       Authenticate in CRYPTO mode
    AUTOPOT                                                      Auto-Detect ideal POT setting(s)
    AUTORATE                                                     Auto-Detect data rate
    AUTORUN [OFF | COMMAND [ARGS]]                               Set/Show startup command
    AUTOTAG                                                      Auto-Detect TAG type
    BINTOHEX <BIN>                                               Show BINARY as HEX string
    BL                                                           Reboot in BOOTLOADER mode
    CLI                                                          Switch to CLI mode
    COIL <HIGH|LOW>                                              Set emulator coil output HIGH/LOW
    CONFIG                                                       Show current NVM config
    CONVERT <TAGTYPE>                                            Convert VTAG to TAGTYPE
    CLOCKH <HZ>                                                  Enable H/W TOGGLE CLOCK (timings in Hz, max 250,000)
    CLOCKP <PW> <PERIOD>                                         Enable H/W PWM CLOCK (timings in uS/100, max 53,687,091)
    CLOCKT <PERIOD>                                              Enable H/W TOGGLE CLOCK (timings in uS/100, max 53,687,091)
    CLONE [HEX KEY|PWD]                                          Copy Virtual TAG to TAG (may require auth/login)
    COPY [TAGTYPE] [HEX KEY|PWD]                                 Copy TAG (and optionally convert) to Virtual TAG (may require auth/login)
    DEBUG [1-4]                                                  Toggle DEBUG line state (no argument to SHOW current states)
    DEBUGOFF <0-4>                                               DEBUG off (LOW) (0 for ALL)
    DEBUGON <0-4>                                                DEBUG on (HIGH) (0 for ALL)
    DETECT                                                       Detect external clock with READER coil
    DOOR <CLOSE|OPEN>                                            Close or Open DOOR RELAY
    DUMP <START BLOCK> [END BLOCK]                               Read and view data block(s) (may require auth/login)
    EMU <UID>                                                    One-shot emulate UID with current TAG config
    EMULATOR [BG]                                                Continuously emulate VTAG [optionally in the BackGround]
    ENCODE <UID> [TAGTYPE]                                       Show raw HEX UID or create VTAG for encoded UID
    EXAMPLES                                                     Show some emulation examples
    FSK <HEX UID> <FC> <RATE> <SUB0> <SUB1> <REPEAT>             Emulate FSK, Field Clock in uS/100, Data Rate in RF/n,
                                                                      Sub Carriers 0/1 in RF/n
    FREQUENCY                                                    Show resonant frequency of coil
    HELP                                                         Show this help
    HEXTOBIN <HEX>                                               Show HEX as BINARY string
    HITAG2-CRACK <NR/PRN> <AR/SECRET>                            Crack HiTag2 card crypto (SNIFF-PWM first)
    HITAG2-KEYSTREAM <NR/PRN> <AR/SECRET>                        Retrieve HiTag2 card crypto keystream (SNIFF-PWM first)
    HITAG2-READER [KEY] [S]                                      Reader mode for crypto authenticated HiTag2 operations - S stores to NVRAM
    HITAG2-CLEARSTOREDTAGS                                       Clears the HiTag2 tags from NVRAM
    HITAG2-COUNTSTOREDTAGS                                       Displays the number of HiTag2 tags stored in NVRAM
    HITAG2-LISTSTOREDTAGS [START] [END]                          Displays the stored tags from START to END
    LOAD                                                         Load config from NVM
    LED <1-6>                                                    Toggle LED
    LEDOFF <0-6>                                                 LED off (0 for ALL)
    LEDON <0-6>                                                  LED on (0 for ALL)
    LOGIN [PWD] [BLOCK]                                          Authenticate in PASSWORD mode
    PING                                                         Keepalive - prints 'RFIDler'
    PINS                                                         Show wiring diagram (alias: WIRES WIRING)
    POTS                                                         Show POT wiper settings
    POTINC <H|L> <1-255>                                         Increment POT
    POTDEC <H|L> <1-255>                                         Decrement POT
    POTSET[V][NV] <H|L> <0-255>                                  Set [Volts][Non Volatile] POT wiper
    PSK1 <HEX UID> <FC> <RATE> <SUB> <REPEAT>                    Emulate PSK1, Field Clock in uS/100, Data Rate in RF/n,
                                                                      Sub Carrier in RF/n
    PWM <FC> <SLEEP> <WAKE> <PW0> <PW1> <GAP> <TXRX> <RXTX>      Set PWM parameters for RWD commands, Field Clock in uS/100, timings in FCs
    READ <START BLOCK> [END BLOCK]                               Read and store data block(s) (may require auth/login)
    READER                                                       Go into READER mode (continuously acquire UID)
    REBOOT                                                       Perform soft reset
    RTC                                                          Show Real Time Clock
    RWD <BINARY>                                                 Send binary command/data
    SAVE                                                         Save current config to NVM
    SELECT [UID]                                                 Send SELECT command
    SET BIPHASE <ON|OFF>                                         Set BiPhase encoding
    SET BITS <BITS>                                              Set number of data bits
    SET FC <PERIOD>                                              Set Field Clock in uS/100
    SET INVERT <ON|OFF>                                          Set data inversion
    SET MANCHESTER <ON|OFF>                                      Set Manchester encoding
    SET MOD <ASK|FSK|PSK1>                                       Set modulation scheme
    SET PSK <QUALITY>                                            Set minimum PSK pulse width in uS
    SET RATE <RATE>                                              Set Data Rate in RF/n (FC/bit)
    SET REPEAT <REPEAT>                                          Set emulation transmission repetitions
    SET SUB0 <RATE>                                              Set Sub Carrier 0 data rate in RF/n (FC/bit)
    SET SUB1 <RATE>                                              Set Sub Carrier 1 data rate in RF/n (FC/bit)
    SET SYNCBITS <BITS>                                          Set number of SYNC bits
    SET SYNC<0-3> <HEX>                                          Set SYNC byte 0-3
    SET TAG <TYPE>                                               Set parameters appropriate for TAG TYPE
    SET VTAG <TYPE>                                              Set Virtual TAG TYPE
    SNIFFER                                                      Go into SNIFFER mode (continuously sniff UID)
    SNIFF-PWM [MIN GAP] [MIN PULSE] [MESG GAP]                   Sniff PWM on external clock with READER coil. Values in uS (default 12/0/0).
    SNIFF-PWM <C|S|L>                                            Sniff PWM (HiTag2 mode) to NVRAM - CLEAR, STORE, LIST
    STOP                                                         Stop any running clocks
    TAGS                                                         Show known TAG TYPES
    TCONFIG                                                      Show TAG's config block
    TEST-HITAG                                                   Hitag2 crypto - test correctness & timing
    TEST-RWD [HEX KEY|PATTERN|PWD]                               Find ideal paramaters for RWD commands
    TEST-SC                                                      Test ISO-7816 Smartcard (get ATR)
    TEST-SD                                                      Test SD card (directory listing)
    TEST-TIMER                                                   Timer tests
    TEST-WIEGAND                                                 Wiegand loopback test
    TEST-WIEGAND-READ <DEBUG PIN>                                Wiegand reader test (triggers with DEBUG_PIN_X)
    TRESET [PWD]                                                 Reset TAG's config block to default
    TRISTATE <ON|OFF>                                            Switch reader circuit tri-state ON/OFF
    TWIPE [PWD]                                                  Reset TAG contents to default (*** all data will be lost!)
    UID                                                          Read TAG UID
    VERSION                                                      Show firmware version
    VTAG                                                         Show contents of Virtual TAG
    VWRITE <BLOCK> <HEX DATA>                                    Write VTAG data block(s)
    WIEGAND-LEARN                                                Learn Wiegand input timings
    WIEGAND-OUT <OFF|ON>                                         Set Wiegand output OFF or ON
    WIEGAND-READ                                                 Read Wiegand input
    WIEGAND-WRITE <BINARY>                                       Send Wiegand output
    WIPE                                                         Wipe NVM
    WRITE <BLOCK> <HEX DATA>                                     Write data block (may require login/auth)
    WIRES                                                        Show wiring diagram (alias: WIRING PINS)
    WIRING                                                       Show wiring diagram (alias: WIRES PINS)
```    
</details>

### Usage Examples
<ul>

For more detailed information see [RFIDler/wiki](https://github.com/AdamLaurie/RFIDler/wiki/How)  


 Set the tag type to ASKRAW, set the High Potentiometer to max, and plot 500 samples :  
&nbsp;&nbsp;`./rfidler.py 'set tag askraw' 'potset h 255' plot 500`

Set tag type to FSK, set the High Potentiometer to max, set frequency to 134.2KHz and plot 500 samples :  
&nbsp;&nbsp;`./rfidler.py 'set tag fskraw' 'potset h 255' 'set fc 745' plot 500`

Note:
The calculation for frequency is simply 1 over the frequency, eg:  
&nbsp;&nbsp;$`1 / 134200 = 0.00000745`$

</ul>

## Install
<ul>

You can run from this directory or optionally install it

To install use the command: `pip3 install .`
</ul>

## See Also
- RFIDler Wiki:  https://github.com/AdamLaurie/RFIDler/wiki/How
- Discussion Forum : http://rfidler.org/
- Github : https://github.com/AdamLaurie/RFIDler/
- Copying : [COPYING](/COPYING)
