#!/usr/bin/env python3.12

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
# pylint: disable=invalid-name, missing-function-docstring

import sys
import select
import os
import time
from typing import Tuple
import xml.etree.ElementTree as ET
from collections import Counter
from itertools import groupby

try:
    from matplotlib import pyplot
except ImportError as e:
    print("Failed to import matplotlib.pyplot")
    pyplot = None

try:
    import numpy as np
except ImportError as e:
    print("Failed to import numpy")
    correlate = None

import RFIDler

# if we want Partial functionality with missing libraries
#
# try:
#     from matplotlib import pyplot
# except ImportError as e:
#     pyplot=None
#
# # later....
# if not pyplot
#    print PLot command not supported without 'matplotlib" lib

# global flags
Quiet = False
Verbose = False

# global constants
ADC_To_Volts = 0.012890625  # 3.3 / 256
POT_To_Volts = 0.019607843  # 5 / 255

cmd_help = {
    'DEBUG <OFF|ON>':                   'Show serial comms',
    'FLASH[P] <IMAGE.HEX>':             'Set bootloader mode and flash IMAGE.HEX [in Production mode]',
    'PLOT[N] <SAMPLES>':                'Plot raw coil samples ([N]o local clock)',
    'STORE[N] <SAMPLES> <file_prefix>': 'Save raw coil samples to file ([N]o local clock)',
    'LOAD <file>':                      'Load and plot saved sample-file',
    'FC <field_freq>':                  'Set Field Clock value Freq from KHz',
    'PROMPT <MESSAGE>':                 'Print MESSAGE and wait for <ENTER>',
    'QUIET':                            'Suppress confirmation of sent command (show results only)',
    'VERBOSE':                          'Be slightly more Verbose',
    'SLEEP <SECONDS>':                  'Pause for SECONDS',
    'RESET':                            'Wipe & Reset RFIDler to defaults',
    'HELP COMMANDS':                    'Print RFIDler Commands',
    'TEST':                             'Run hardware manufacturing test suite',
}


# should this take command name args for more detailed help???
def print_help() -> None:
    """ Print help test """
    print(f"    usage: {sys.argv[0]} [PORT] <COMMAND> [ARGS] [COMMAND [ARGS] ...]")
    print("    Commands:")

    max_len = max(len(x) for x in cmd_help) + 3

    for c, y in cmd_help.items():
        print(f"\t{c:{max_len}} {y}")

    print("""
   Commands will be executed sequentially.
   Unrecognized commands will be passed directly to RFIDler.
   Commands with arguments to be passed directly should be quoted. e.g. "SET TAG FDXB"
""")


def print_rfidler_help(rfer):

    print("RFIDler HELP:")

    h_result, h_rdata = rfer.command("HELP")
    if h_result:
        for h_line in h_rdata:
            print(h_line)
    else:
        output('Failed: ' + h_rdata)

    h_result, h_rdata = rfer.command('TAGS')
    if h_result:
        sys.stdout.write('\n')
        for h_line in h_rdata:
            sys.stdout.write(h_line.rstrip())
        # print()
        sys.stdout.write('\n\n')


def run_test() -> None:
    """
        perform hardware tests for manufacturing assurance
        requires hardware to be placed on test jig
    """
    # pylint: disable=line-too-long
    test = 1
    print('Testing H/W. Hit <ESC> to end.')
    while 42:
        print('waiting for board...')
        while 42:
            rfidler.disconnect()
            t_result, _ = rfidler.connect(rfidler.used_port)
            if t_result:
                break
            if os.path.exists('/dev/RFIDlerBL'):
                print('bootloader mode - flashing...')
                os.system(
                    'mphidflash -r -w /home/software/unpacked/RFIDler/firmware/Pic32/RFIDler.X/dist/debug/production/RFIDler.X.production.hex')

        os.system('clear')
        test_result = 'Pass'
        print('Starting test', test)
        for t in 'PING', \
                 'DEBUGOFF 0', \
                 'DEBUGON 4', \
                 'DEBUGON 2', 'SET TAG HITAG2', 'UID', 'DEBUGOFF 2', \
                 'DEBUGON 3', 'SET TAG INDALA64', 'UID', 'DEBUGOFF 3', \
                 'TEST-WIEGAND', 'TEST-SC', 'TEST-SD', \
                 'SET TAG HID26', 'ENCODE 12345678 HID26', 'EMULATOR BG', 'WIEGAND-OUT OFF', 'TEST-WIEGAND-READ 1':
            print(f'  Test {t} - ', end='')
            sys.stdout.flush()
            for _z in range(10):
                t_result, t_rdata = rfidler.command(t)
                if t_result:
                    break
            print(t_result, t_rdata)
            if not t_result:
                test_result = 'Fail!'

        # now wait for board to change
        os.system('figlet ' + test_result)
        test += 1
        print('load next board')
        while 42:
            try:
                t_result, t_rdata = rfidler.command('PING')
                if not t_result:
                    break
            except Exception as _e:   # pylint: disable=broad-exception-caught
                break


def flash_board(cmd: str, cmd_arg: str) -> None:
    """
    reload firmware
    uses "mphidflash" command
    """
    # pylint: disable=too-many-branches
    if cmd in ['FLASH', 'FLASHP']:

        if not os.path.exists(cmd_arg):
            print(f'could file/open code file: {cmd_arg}')
            sys.exit(True)

        if not os.path.exists('/dev/RFIDlerBL'):
            f_result, _reason = rfidler.command('BL')
            if not result:
                print('could not set bootloader mode!')
                sys.exit(True)

        rfidler.disconnect()
        time.sleep(1)
        if os.path.exists('/dev/RFIDlerBL'):
            print('bootloader mode - flashing...')
            os.system(f'mphidflash -r -w {cmd_arg}')
        else:
            print('bootloader not detected!')
            sys.exit(True)

        print('Waiting for reboot...')
        while 42:
            f_result, _reason = rfidler.connect(rfidler.used_port)
            if f_result:
                f_result, _rdata = rfidler.command('PING')
                if f_result:
                    break

        if cmd == 'FLASHP':
            time.sleep(1)
            print('Load next board')
            # wait for disconnect
            while 42:
                try:
                    time.sleep(.5)
                    f_result, _rdata = rfidler.command('PING')
                    if not f_result:
                        break
                except Exception as _e:   # pylint: disable=broad-exception-caught
                    break
            print('Waiting for board...')
            # wait for new board in normal or bootloader mode
            while 42:
                f_result, _reason = rfidler.connect(rfidler.used_port)
                if f_result:
                    f_result, _rdata = rfidler.command('PING')
                    if f_result:
                        break
                rfidler.disconnect()
                if os.path.exists('/dev/RFIDlerBL'):
                    break


def output(message: str) -> None:
    """ optionally print message """
    if not Quiet:
        print(message)


def store_data(dat, filename_prefix="dump") -> None:
    """ Write data to file """
    root = ET.fromstring(''.join(dat))
    # wrap it in an ElementTree instance, and save as XML
    tree = ET.ElementTree(root)
    ET.indent(tree, space="  ", level=0)
    timestr = time.strftime("%Y%m%d-%H%M%S")
    filename = f"{filename_prefix}_{timestr}.xml"
    tree.write(filename)
    output(f"Wrote dump to {filename}")


def load_data(fname: str) -> Tuple[bool, list]:
    """ Read data to file """
    try:    # ET.ElementTree write in "utf-8" format by default
        with open(fname, "r", encoding="utf-8") as f:
            lines = f.readlines()
    except Exception as _e:  # pylint: disable=broad-exception-caught
        return [False, str(_e)]

    return [True, lines]


def autocorr(data) -> Tuple[list, list]:
    """
    See
    http://stackoverflow.com/questions/643699/how-can-i-use-numpy-correlate-to-do-autocorrelation
    """
    x1 = 400
    x2 = 1000

    result1 = np.correlate(data, data[:x1], mode='full')
    result2 = np.correlate(data, data[:x2], mode='full')

    if Verbose:
        print(len(result1))
        print(len(result2))
        print(len(data))

    # return (result1, result2)
    return (result1[x1 - 1:], result2[x2 - 1:])


# Pylink hates this funtion
#
# unsubscriptable-object false positive: https://github.com/pylint-dev/pylint/issues/4577
def plot_data(data) -> None:
    """
        process and plot data with pyplot
    """
    # pylint: disable=too-many-statements, too-many-branches, too-many-locals, line-too-long

    if pyplot is None or np is None:
        print("plot functionally not available: missing library")
        return

    # create graphic objects
    # fig, ax1 = pyplot.subplots()
    fig, (ax1, ax_corr) = pyplot.subplots(2)

    fig.canvas.manager.set_window_title('RFIDler plot')

    # we need second subplot for voltage scale
    ax2 = ax1.twinx()

    # get xml sections
    xml = ET.fromstring(''.join(data))
    samples = xml.find('Samples')
    # tag = xml.find('Tag')
    # pots = xml.find('Pots')

    title = xml.find('Tag/Tag_Type/Data').text
    pyplot.title(f'RFIDler - {title}')

    # raw coil data
    # raw = samples.find('Coil_Data')
    # data = raw.find('Data')
    # out = data.text.replace(' ', '')

    # out = samples.find('Coil_Data/Data').text.replace(' ', '')
    # out = list(bytes.fromhex(out))
    # out[:] = [x * ADC_To_Volts for x in out]
    # r = range(len(out))

    # way faster
    out = samples.find('Coil_Data/Data').text.replace(' ', '')
    out = np.frombuffer(bytes.fromhex(out), np.dtype('B')) * ADC_To_Volts
    r = range(out.size)

    ax2.plot(r, out, color='b', label="Raw Data")

    # reader HIGH/LOW
    # raw = samples.find('Reader_Output')
    # data = raw.find('Data')
    # out = data.text.replace(' ', '')
    out = samples.find('Reader_Output/Data').text.replace(' ', '')

    # out = map(ord, out.decode("hex"))
    out = list(bytes.fromhex(out))

    # Use a counter to help calc bit period
#    count = 0
#    prev = out[0]
#    bitcounts = []

    # convert to value that will show on scale
#    for i in range(len(out)):
#        if out[i] != prev:
#            prev = out[i]
#            bitcounts.append(count)
#            count = 1
#        else:
#            count = count +1
#
#        if out[i]:
#            out[i] = 258
#        else:
#            out[i] = 4

    if Verbose:
        # Use a counter to help calc bit period

        # way faster way to count
        # https://stackoverflow.com/questions/55141181/count-number-of-consecutive-elements-in-a-list#answer-55141306
        bitcounts = [len(list(g)) for k, g in groupby(out)]

        print("Bit periods")
        print(bitcounts)

        print("Most common bit periods:")
        print("\n".join(["%d : %d" % kv for kv in Counter(bitcounts).most_common(10)]))  # pylint: disable=consider-using-f-string

    ax1.plot(r, [258 if x else 4 for x in out], '-', color='g',
             label='Reader Logic')
    # show compressed version
    ax1.plot(r, [320 if x else 300 for x in out], '-', color='g')

    #   Not  yet finished
    ax_corr2 = ax_corr.twinx()
    # Show autocorrelation
    # Some test-data
    # x_data = [0]*200+[1,2,3,4,5,6,7,8,9,500]*10+[0]*200
    # x_data = x_data+x_data+x_data+x_data
    # Autocorrelation should be best at 500, there's a 500 repeater period (2000 samples)
    (autoc_1, autoc_2) = autocorr(out)
    ax_corr.title.set_text("Autocorrelation")
    c1 = ax_corr.plot(range(len(autoc_1)), autoc_1, "-", color='m',
                      label="Autocorrelation (full)", alpha=0.5)
    c2 = ax_corr2.plot(range(len(autoc_2)), autoc_2, "-", color='g',
                       label="Autocorrelation (500 samples)", alpha=0.5)
    # consolidate legend labels
    lns = c1 + c2
    labs = [ln.get_label() for ln in lns]
    leg_corr = ax_corr.legend(lns, labs, loc=0, fontsize='x-small',
                              draggable=True)  # bbox_to_anchor=(1.04, 1))
    # leg_corr2 = ax_corr2.legend(loc=0, fontsize='x-small', draggable=True)  # bbox_to_anchor=(1.04, 1))

    # bit period
    # raw = samples.find('Bit_Period')
    # data = raw.find('Data')
    # out = data.text.replace(' ', '')
    out = samples.find('Bit_Period/Data').text.replace(' ', '')
    out = list(bytes.fromhex(out))

    # show bit period as single vertical stripe
    prev = out[0]
    fill = 0
    fill1 = 0
    toggle = True

    for i, out_dat in enumerate(out):
        if out_dat != prev:
            prev = out_dat
            if fill1:
                fill = fill1
                fill1 = i
            else:
                fill1 = i
            # fill every other stripe
            if toggle:
                ax1.axvspan(fill, fill1, facecolor='r', alpha=0.1)
            toggle = not toggle

#    # find first stripe and add legend
#    for i in range(len(out)):
#        if out[i]:
#            break

    for i, out_dat in enumerate(out):
        if out_dat:
            break
    data = xml.find('Tag/Data_Rate/Data').text
    # Do we want this Rotated (Can't read it)
    ax1.text(i + ((fill1 - fill) / 2), -10, f'Bit Period\n{data} FCs',
             color='r', alpha=0.5,  # rotation=270,
             ha='center', va='top')

    # pot settings
    color = 'r'
    for element in 'Pot_High', 'Pot_Low':
        # raw = pots.find( element.strip())
        # data = raw.find('Data').text
        data = xml.find(f'Pots/{element}/Data').text
        # convert pot setting to volts
        fdata = float(data)
        out = [fdata * POT_To_Volts] * len(r)
        ax2.plot(r, out, '--', color=color,
                 label=f"{element} {(fdata * POT_To_Volts):0.2f}v (Pot: {data})")
        # label=element + ' %0.2fv (Pot: %s)' % (float(data) * POT_To_Volts, data))
        # ax2.text(len(x) + 16, out[0], '%s: %0.2fv\n(%s)' % (element, float(data) * POT_To_Volts, data), color= color)
        color = 'm'

    # done - label and show graph
    # ADC scale needs to match volts (5v / 3.3v)
    ax1.set_ylim(-5, 256 * 1.515151515)

    pyplot.xlim(0, len(r))

    ax1.set_ylabel('Signal Strength (ADC)', labelpad=8.0)
    ax1.set_xlabel('Sample Number')

    leg_ax1 = ax1.legend(bbox_to_anchor=(0, 1), loc='lower left', fontsize='x-small', draggable=True)
    # volts scale up to 5.0v as that is max pot setting
    # note that the ADC will clip at 3.3v, so although we can use a higher pot setting,
    # we can't see token samples above 3.3v
    ax2.set_ylim(0, 5.0)

    # use "labelpad" so it moves off tic marks on right
    ax2.set_ylabel('Signal Strength (Volts)', rotation=270, labelpad=8.0)
    leg_ax2 = ax2.legend(bbox_to_anchor=(1, 1), loc='lower right', fontsize='x-small', draggable=True)

    # tight_layout does subplots_adjust automatically
    # pyplot.subplots_adjust(hspace=0.5)

    # https://matplotlib.org/stable/users/explain/axes/tight_layout_guide.html
    # https://matplotlib.org/stable/api/_as_gen/matplotlib.figure.Figure.tight_layout.html
    pyplot.tight_layout()

    pyplot.show()


# part arg is now optional
if __name__ == '__main__':

    port = None
    no_connect = False
    av = sys.argv[1:]
    ac = len(av)

    if ac == 0 or av[0] == "HELP":
        print_help()
        sys.exit(True)

    rfidler = RFIDler.RFIDler()

    if av and av[0] == "-n":
        av.pop(0)
        no_connect = True
        sys.exit(True)

    # if there is more then 1 arg AND 1st arg is a path
    # assume it is a path to port
    if av and av[0][0] == '/':
        port = av.pop(0)

    if no_connect is False:
        # if port is None, connect() will scan for the correct port
        result, reason = rfidler.connect(port)
        del no_connect
        if not result:
            print(f'Warning - could not open serial port: {port or reason}')
            print(f'Reason: {reason}')
            # sys.exit(1)

    # plot_data = None
    # should we have a -png option to have pylot save a PNG ?
    # process each command
    while av:
        command = av.pop(0)
        command_up = command.upper()
        command_option = None

        if rfidler.Debug or Verbose:
            print(f"COMMAND is '{command}'")

        if command_up == 'VERBOSE':
            Verbose = True
            continue

        if command_up.startswith('NOVERB'):
            Verbose = False
            continue

        if command_up == 'DEBUG':
            if av:
                command_option = av.pop(0).upper()
                if command_option == 'ON':
                    rfidler.Debug = Verbose = True
                elif command_option == 'OFF':
                    rfidler.Debug = Verbose = False
                else:
                    print(f'Unknown option: {command_option}')
                    sys.exit(True)
            else:
                print(f"{command} missing argument: ON / OFF")
                sys.exit(1)
            continue

        # HELP gets you the python help, "HELP COMMANDS" or "HELP RFIDLER"
        # will get the RFIDler board help info
        if command_up in ['HELP', 'USAGE', "?"]:
            if av:
                command_option = av.pop(0).upper()
                if command_option in ['COMMANDS', 'RFIDLER']:
                    print_rfidler_help(rfidler)
                else:
                    print_help()
            else:
                print_help()
            sys.exit(0)

        if command_up in ['VERSION']:
            print(f"RFIDler.py : {RFIDler.__VERSION__}")
            if rfidler.connection:
                result, rdata = rfidler.command(command)
                print(f"RFIDler Firmware: {rdata[0]}")
            continue

        if command_up in ['FLASH', 'FLASHP']:
            if ac:
                command_option = av.pop(0)
                flash_board(command_up, command_option)
            else:
                print(f"{command} missing argument")
                sys.exit(1)
            continue

        if command_up == 'XKCD':
            if pyplot is None:
                print(f"command {command} functionally not available without 'matplotlib' lib")
            else:
                pyplot.xkcd()
            continue

        if command_up in ['CONNECT', 'RECONNECT']:
            if Verbose:
                print("(re)connect")
            rfidler.disconnect()  # Always returns True
            result, rdata = rfidler.connect(rfidler.used_port)
            print(f"Conn result: {result} {rdata}")
            continue

        if command_up in ['RESET']:
            if Verbose:
                print("WIPE/REBOOTING")
            result, rdata = rfidler.command("WIPE")
            if result is False:
                output('Reboot Failed: ' + rdata)
            result, rdata = rfidler.command("REBOOT")
            if result is False:
                output('Reboot Failed: ' + rdata)
                sys.exit(1)
            if av:  # Only need to reconnect this if no more args
                rfidler.disconnect()
                time.sleep(2)
                result, rdata = rfidler.connect(rfidler.used_port)
                if result is False:
                    output('(re)connect Failed: ' + rdata)
                    sys.exit(1)
            continue

        if command_up == 'FC':
            if not av:  # We should add a ranges / value test
                print(f"command:{command} missing Freq option (in KHz)")
                sys.exit(1)

            command_option = av.pop(0).upper()

            if command_option.endswith('KHZ'):
                command_option = command_option[:-3]

            try:
                command_option = float(command_option)
            except ValueError:
                print(f"command:{command} invalid value {command_option}")
                print("\texpecting value in Khz")
                sys.exit(1)

            command_option = int(100000 // command_option)

            if Verbose:
                print(f"setting FC to {command_option}")

            result, rdata = rfidler.command(f'SET FC {command_option}')
            if result is False:
                output('Failed: ' + rdata)
                sys.exit(1)
            continue

        # This Command logic is a mess
        if command_up in ['PLOT', 'PLOTN', 'STORE', 'STOREN', 'LOAD']:

            if av:
                command_option = av.pop(0)
            else:
                print(f"command:{command} option(s) missing")
                sys.exit(1)

            if command_up in ['PLOT', 'STORE']:
                # if command_option.isdigit() ??
                result, rdata = rfidler.command(f'ANALOGUE {command_option}')
            elif command_up in ['PLOTN', 'STOREN']:
                # if command_option.isdigit() ??
                result, rdata = rfidler.command(f'ANALOGUEN {command_option}')
            elif command_up in ['LOAD']:
                result, rdata = load_data(command_option)
            else:
                print("Command Parse Error: This should never happen")
                sys.exit(1)

            if result:
                if command_up in ['PLOT', 'PLOTN', 'LOAD']:
                    try:
                        plot_data(rdata)
                    except KeyboardInterrupt as _e:
                        print("KeyboardInterrupt: exiting.....")
                        continue

                elif command_up in ['STORE', 'STOREN']:
                    # Store
                    if av:
                        command_option = av.pop(0)
                    else:
                        print(f"command:{command} file_prefix option missing")
                        sys.exit(1)
                    store_data(rdata, command_option)
                else:
                    print("Command Parse Error: This should never happen")
                    sys.exit(1)

            else:
                output(f'{command}: Failed: ' + rdata)
                sys.exit(1)

            continue

        if command_up == 'PROMPT':
            if av:
                command_option = av.pop(0)
            else:
                command_option = '-->'
            input(command_option)
            continue

        # perform hardware tests for manufacturing assurance
        # requires hardware to be placed on test jig
        if command_up == 'TEST':
            try:
                run_test()
            except KeyboardInterrupt as _e:
                print("KeyboardInterrupt: exiting.....")
                continue

        if command_up == 'SLEEP':
            if av:
                command_option = float(av.pop(0))
            else:
                print("command: SLEEP option missing")
                sys.exit(1)

            output(f'Sleeping for {command_option} seconds')
            time.sleep(command_option)
            continue

        if command_up == 'TERMINAL':
            while 42:
                while rfidler.connection.inWaiting():
                    sys.stdout.write(rfidler.connection.readline(1))
                    sys.stdout.flush()
                # send typed characters
                while sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
                    x = sys.stdin.read(1)
                    rfidler.connection.write(x)
                    # read back echo
                    x = rfidler.connection.read(1)
                    sys.stdout.write(x)
                    sys.stdout.flush()

        # set quiet flag so we only see responses, not sent commands
        if command_up == 'QUIET':
            Quiet = True
            Verbose = False
            continue

        # catchall - pass command directly
        output(f"sending {command}")
        sys.stdout.flush()
        result, rdata = rfidler.command(command)
        if result:
            for line in rdata:
                print(line)
        else:
            output('Failed: ' + rdata)

        continue

    sys.exit(0)
