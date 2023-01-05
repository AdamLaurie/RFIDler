#!/usr/bin/env python

"""
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
 ***************************************************************************

*/

// Author: Adam Laurie <adam@aperturelabs.com>

"""

import sys
import select
import os
import time
import xml.etree.ElementTree as ET
import collections
from matplotlib import pyplot
import numpy
import RFIDler


# global flags
Quiet = False

# global constants
ADC_To_Volts = 0.012890625  # 3.3 / 256
POT_To_Volts = 0.019607843  # 5 / 255


def output(message):
    if not Quiet:
        print(message)


def store_data(data,  filename_prefix = "dump"):
    root = ET.fromstring(''.join(data))
    # wrap it in an ElementTree instance, and save as XML
    tree = ET.ElementTree(root)
    timestr = time.strftime("%Y%m%d-%H%M%S")
    filename = "%s_%s.xml" % (filename_prefix, timestr)
    tree.write(filename)
    output("Wrote dump to %s" % filename)

def load_data(fname):
    try:
        with open(fname, "r") as f:
            lines = f.readlines()
    except (Exception, e):
        return [False, str(e)]

    return [True, lines]



def autocorr(data):
    """
    See 
    http://stackoverflow.com/questions/643699/how-can-i-use-numpy-correlate-to-do-autocorrelation
    """
    x1 = 400 
    x2 = 1000

    result1 = numpy.correlate( data,data[:x1], mode='full')
    result2 = numpy.correlate( data,data[:x2], mode='full')
    print(len(result1))

    print(len(result2))
    print(len(data))
    #return (result1, result2)
    return (result1[x1-1:], result2[x2-1:])

def plot_data(data):
    
    # create graphic objects
#    fig, ax1 = pyplot.subplots()
    fig, (ax1, ax_corr) = pyplot.subplots(2)

    # we need second subplot for voltage scale
    ax2 = ax1.twinx()

    # get xml sections
    xml = ET.fromstring(''.join(data))
    samples = xml.find('Samples')
    tag = xml.find('Tag')
    pots = xml.find('Pots')

    # raw coil data
    raw = samples.find('Coil_Data')
    data = raw.find('Data')
    out = data.text.replace(' ', '')
    out = map(ord, out.decode("hex"))
    out[:] = [x * ADC_To_Volts for x in out]
    x = range(len(out))
    ax2.plot(x, out, color='b', label="Raw Data")

    # reader HIGH/LOW
    raw = samples.find('Reader_Output')
    data = raw.find('Data')
    out = data.text.replace(' ', '')
    out = map(ord, out.decode("hex"))

    #Use a counter to help calc bit period
    count = 0
    prev = out[0]
    bitcounts = []

    # convert to value that will show on scale
    for i in range(len(out)):
        if out[i] != prev:
            prev = out[i]
            bitcounts.append(count)
            count = 1
        else:
            count = count +1

        if out[i]:
            out[i] = 258
        else:
            out[i] = 4

    print("Bit periods")
    print(bitcounts)
    
    print("Most common bit periods:")
    print("\n".join(["%d : %d" % kv for kv in collections.Counter(bitcounts).most_common(10)]))

 #   Not  yet finished
    ax_corr2 = ax_corr.twinx()
    #Show autocorrelation
    #Some test-data
    #x_data = [0]*200+[1,2,3,4,5,6,7,8,9,500]*10+[0]*200
    #x_data = x_data+x_data+x_data+x_data
    #Autocorrelation should be best at 500, there's a 500 repeater period (2000 samples)
    (autoc_1, autoc_2) = autocorr(out)
    ax_corr.plot(range(len(autoc_1)) , autoc_1 , range(len(autoc_1)) , "-", color='b',label = "Autocorrelation (full)")
    ax_corr2.plot(range(len(autoc_2)) , autoc_2 , range(len(autoc_2)) , "-", color='g',label = "Autocorrelation (500 samples)")


    ax1.plot(x, out, '-', color='g', label='Reader Logic')
    # show compressed version
    for i in range(len(out)):
        if out[i] == 258:
            out[i] = 320
        else:
            out[i] = 300
    ax1.plot(x, out, '-', color='g')

    # ax1.text(-10, out[0], 'Reader Logic', color= 'g', ha= 'right', va= 'center')

    # bit period
    raw = samples.find('Bit_Period')
    data = raw.find('Data')
    out = data.text.replace(' ', '')
    out = map(ord, out.decode("hex"))
    # show bit period as single vertical stripe
    prev = out[0]
    fill = 0
    fill1 = 0
    toggle = True
    for i in range(len(out)):
        if out[i] != prev:
            prev = out[i]
            if fill1:
                fill = fill1
                fill1 = i
            else:
                fill1 = i
            # fill every other stripe
            if toggle:
                ax1.axvspan(fill, fill1, facecolor='r', alpha=0.1)
            toggle = not toggle
    # find first stripe and add legend
    for i in range(len(out)):
        if (out[i]):
            break
    legend = tag.find('Data_Rate')
    data = legend.find('Data').text
    ax1.text(i + ((fill1 - fill) / 2), -10, 'Bit Period\n%s FCs' % data, color='r', alpha=0.5, rotation=270,
             ha='center', va='top')


    # pot settings
    color = 'r'
    for element in 'Pot_High', 'Pot_Low ':
        raw = pots.find(element.strip())
        data = raw.find('Data').text
        # convert pot setting to volts
        out = [float(data) * POT_To_Volts] * len(x)
        ax2.plot(x, out, '--', color=color,
                 label=element + ' %0.2fv (Pot: %s)' % (float(data) * POT_To_Volts, data))
        # ax2.text(len(x) + 16, out[0], '%s: %0.2fv\n(%s)' % (element, float(data) * POT_To_Volts, data), color= color)
        color = 'm'

    # done - label and show graph
    # ADC scale needs to match volts (5v / 3.3v)
    ax1.set_ylim(-5, 256 * 1.515151515)
    title = tag.find('Tag_Type')
    pyplot.xlim(0, len(x))
    pyplot.title('RFIDler - ' + title.find('Data').text)
    ax1.set_ylabel('Signal Strength (ADC)')
    ax1.set_xlabel('Sample Number')
    ax1.legend(loc=2)
    fig.canvas.set_window_title('RFIDler plot')
    # volts scale up to 5.0v as that is max pot setting
    # note that the ADC will clip at 3.3v, so although we can use a higher pot setting,
    # we can't see token samples above 3.3v
    ax2.set_ylim(0, 5.0)
    ax2.set_ylabel('Signal Strength (Volts)', rotation=270)
    ax2.legend(loc=1)
    pyplot.show()

if len(sys.argv) < 3:
    print("""
 usage: {0} <PORT> <COMMAND> [ARGS] [COMMAND [ARGS] ...]

   Commands:

     DEBUG <OFF|ON>                      Show serial comms
     FLASH[P] <IMAGE.HEX>                Set bootloader mode and flash IMAGE.HEX [in Production mode]
     PLOT[N] <SAMPLES>                   Plot raw coil samples ([N]o local clock)
     STORE[N] <SAMPLES> <file_prefix>    Save raw coil samples to file ([N]o local clock)
     LOAD <file>                         Load and plot saved sample-file        
     PROMPT <MESSAGE>                    Print MESSAGE and wait for <ENTER>
     QUIET                               Supress confirmation of sent command (show results only)
     SLEEP <SECONDS>                     Pause for SECONDS
     TEST                                Run hardware manufacting test suite
    
   Commands will be executed sequentially.
   Unrecognised commands will be passed directly to RFIDler.
   Commands with arguments to be passed directly should be quoted. e.g. "SET TAG FDXB"
""".format(*sys.argv))
    exit(True)

port = sys.argv[1]
rfidler = RFIDler.RFIDler()
result, reason = rfidler.connect(port)
if not result:
    print('Warning - could not open serial port:', reason)

current = 2
# process each command
while current < len(sys.argv):
    command = sys.argv[current].upper()
    current += 1
    if command == 'DEBUG':
        if sys.argv[current].upper() == 'ON':
            rfidler.Debug = True
        else:
            if sys.argv[current].upper() == 'OFF':
                rfidler.Debug = False
            else:
                print('Unknown option:', sys.argv[current])
                exit(True)
        current += 1
        continue

    if command == 'FLASH' or command == 'FLASHP':
        if not os.path.exists('/dev/RFIDlerBL'):
            result, reason = rfidler.command('BL')
            if not result:
                print('could not set bootloader mode!')
                exit(True)
        rfidler.disconnect()
        time.sleep(1)
        if os.path.exists('/dev/RFIDlerBL'):
            print('bootloader mode - flashing...')
            os.system('mphidflash -r -w %s' % sys.argv[current])
        else:
            print('bootloader not detected!')
            exit(True)
        print('Waiting for reboot...')
        while 42:
            result, reason = rfidler.connect(port)
            if result:
                result, data = rfidler.command('PING')
                if result:
                    break
        if command == 'FLASHP':
            time.sleep(1)
            print('Load next board')
            # wait for disconnect
            while 42:
                try:
                    time.sleep(.5)
                    result, data = rfidler.command('PING')
                    if not result:
                        break
                except:
                    break
            print('Waiting for board...')
            # wait for new board in normal or bootloader mode
            while 42:
                result, reason = rfidler.connect(port)
                if result:
                    result, data = rfidler.command('PING')
                    if result:
                        break
                rfidler.disconnect()
                if os.path.exists('/dev/RFIDlerBL'):
                    break
            current -= 1
            continue
        current += 1
        continue

    if command == 'XKCD':
        pyplot.xkcd()
        continue

    if command in ['PLOT', 'PLOTN', 'STORE', 'STOREN', 'LOAD']:
        if command in ['PLOT', 'STORE']:
            result, data = rfidler.command('ANALOGUE %s' % sys.argv[current])
        elif command in ['PLOTN', 'STOREN']:
            result, data = rfidler.command('ANALOGUEN %s' % sys.argv[current])
        else:
            result, data = load_data(sys.argv[current])

        current += 1
        if result:
            if command in ['PLOT', 'PLOTN','LOAD']:
                plot_data(data)
            else:
                # Store
                store_data(data, sys.argv[current])
                current += 1
        else:
            output('Failed: ' + data)
        continue

    if command == 'PROMPT':
        raw_input(sys.argv[current])
        current += 1
        continue

    # perform hardware tests for manufacturing assurance
    # requires hardware to be placed on test jig
    if command == 'TEST':
        test = 1
        print('Testing H/W. Hit <ESC> to end.')
        while 42:
            print('waiting for board...')
            while 42:
                rfidler.disconnect()
                result, reason = rfidler.connect(port)
                if result:
                    break
                if os.path.exists('/dev/RFIDlerBL'):
                    print('bootloader mode - flashing...')
                    os.system(
                        'mphidflash -r -w /home/software/unpacked/RFIDler/firmware/Pic32/RFIDler.X/dist/debug/production/RFIDler.X.production.hex')

            os.system('clear')
            test_result = 'Pass'
            print('Starting test', test)
            for x in 'PING', \
                     'DEBUGOFF 0', \
                     'DEBUGON 4', \
                     'DEBUGON 2', 'SET TAG HITAG2', 'UID', 'DEBUGOFF 2', \
                     'DEBUGON 3', 'SET TAG INDALA64', 'UID', 'DEBUGOFF 3', \
                     'TEST-WIEGAND', 'TEST-SC', 'TEST-SD', \
                     'SET TAG HID26', 'ENCODE 12345678 HID26', 'EMULATOR BG', 'WIEGAND-OUT OFF', 'TEST-WIEGAND-READ 1':
                print('  Test %s - ' % x,
                sys.stdout.flush())
                for z in range(10):
                    result, data = rfidler.command(x)
                    if result:
                        break
                print(result, data)
                if not result:
                    test_result = 'Fail!'
            # now wait for board to change
            os.system('figlet ' + test_result)
            test += 1
            print('load next board')
            while 42:
                try:
                    result, data = rfidler.command('PING')
                    if not result:
                        break
                except:
                    break
        continue

    if command == 'SLEEP':
        output('Sleeping for %s seconds' % sys.argv[current])
        time.sleep(float(sys.argv[current]))
        current += 1
        continue

    if command == 'TERMINAL':
        while 42:
            while rfidler.Connection.inWaiting():
                sys.stdout.write(rfidler.Connection.readline(1))
                sys.stdout.flush()
            # send typed characters
            while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
                x = sys.stdin.read(1)
                rfidler.Connection.write(x)
                # read back echo
                x = rfidler.Connection.read(1)
                sys.stdout.write(x)
                sys.stdout.flush()

    # set quiet flag so we only see responses, not sent commands
    if command == 'QUIET':
        Quiet = True
        continue

    # catchall - pass command directly
    output("sending '%s'" % command)
    sys.stdout.flush()
    result, data = rfidler.command(command)
    if result:
        for line in data:
            print(line)
    else:
        output('Failed: ' + data)
    continue
