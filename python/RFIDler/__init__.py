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

# pylint: disable=invalid-name

from typing import Union, Tuple
# serial needs to be pyserial
# https://stackoverflow.com/questions/64383756/has-python-package-serial-been-renamed-to-pyserial
import serial
import serial.tools.list_ports

__VERSION__ = '1.1'


class RFIDler():
    """Class for communicating with RFIDler hardware"""

    # globals
    connection = None
    Debug = False
    used_port = None

    def send_command(self, tosend: str) -> Tuple[bool, str]:
        """
        low level send a command
        internal use only - external code should call 'command()'
        args: command line to send
        return: True/False, data
        possible data values:
            '.' - OK, command complete, no data to follow
            '+' - OK, command complete, data/result to follow
            '!' - command failed, reason to follow
            '?' - command not recognised
        """
        # pylint: disable=too-many-return-statements

        if self.connection is None:
            return False, "Device not connected"

        try:
            cmd_str = f"{tosend}\r\n".encode('ascii')
            if self.Debug:
                print(f'\r\n>>> {cmd_str}', end='')

            self.connection.write(cmd_str)
        except serial.serialutil.SerialException as _e:
            print(f"SerialException: {_e}")
            return False, f"Send SerialException {_e}"
        # except Exception as _e:
        except (OSError, ValueError) as _e:
            print(f"Exception: Send: '{_e}'")
            return False, "Serial communications failure (send)!"

        if self.Debug:
            print("")
        try:
            result = self.connection.read(1).decode('ascii')
            if self.Debug:
                print('\r\n<<<', end='')
            if result not in '.+!?':
                if self.Debug:
                    print(result, '(fail!)')
                return False, result
            if self.Debug:
                print(result)
            return True, result
        except serial.serialutil.SerialException as _e:
            print(f"SerialException: {_e}")
            return False, f"Read SerialException {_e}"
        except (OSError, ValueError) as _e:
            print(f"Exception: Read: {_e}")
            return False, "Serial communications failure (receive)!"

    def command(self, tosend: str) -> Tuple[bool, str]:
        """
        send command
        args: command line to send
        return: True/False, [data line(s) or reason for failure]
        note that CR/LF is stripped from each data item
            but all other whitespace is left intact (including blank lines)
        """
        # pylint: disable=too-many-return-statements
        if self.connection is None:
            return False, "Device not connected"

        result, data = self.send_command(tosend)
        if not result:
            return False, data
        # check type of result
        # if '?', command wasn't recognised
        if data == '?':
            return False, "Command not recognised!"
        # if '!', command failed
        if data == '!':
            data = self.connection.readline().decode('ascii').rstrip('\r\n')
            return False, data
        # if '.', we're done
        if data == '.':
            return True, ''
        # if '+', we need to get results. '*' terminates.
        if data == '+':
            data = []
            while 42:
                item = self.connection.readline()
                item = item.decode('ascii').rstrip('\r\n')

                if self.Debug:
                    print('<<<', item)
                if item == '*':
                    return True, data
                data.append(item)

        # possible return / fall through that should never happen
        return False, ''

    def connect(self, port: str = None, baud: int = 115200, timeout: int = 1) -> Tuple[bool, str]:
        """
        open a serial connection to RFIDler and switch to API mode
        args: port =None, baud= 115200, timeout= 1
        if port is None, code will scan for the correct port
        return: True/False, reason for failure
        """
        if port is None:
            port = self._find_port()
            if port is None:
                return False, "Unable to find correct port"

            print(f"Using: {port}")

        try:
            self.connection = serial.Serial(port, baud, timeout=timeout)
            self.connection.flushInput()
            self.connection.flushOutput()
        except serial.serialutil.SerialException as _e:
            print(f"SerialException: {_e}")
            return False, f"Can't open serial port: {_e}"
        except (OSError, ValueError) as _e:
            return False, f"Exception Error: {_e}"

        # Save for later if needed elsewhere
        self.used_port = port

        # make sure we're in API mode
        # send it twice as RFIDler's serial buffer may already have some crap in it
        self.command("API")
        while self.connection.readline():
            continue
        if not self.command("API"):
            return False, "Can't switch to API mode"
        return True, ""

    # RFIDler ports info:
    #   description: RFIDler-LF
    #   manufacturer: Aperture Labs Ltd.
    #   hwid: USB VID:PID=1D50:6098 SER=17130C2E00E1 LOCATION=1-1
    #   pid: 24728
    #   vid: 7504
    #   serial_number 17130C2E00E1
    #   product RFIDler-LF
    def _find_port(self) -> Union[str, None]:
        """find serial device"""

        if self.Debug:
            print("find serial device")
        ports = serial.tools.list_ports.comports()
        for p in ports:
            if self.Debug:
                print(f"{p.name}: {p.description} [{p.hwid}]")

            if (p.description and p.description.startswith("RFIDler")) or \
               (p.product and p.product.startswith("RFIDler")):
                return p.device

        return None

    def disconnect(self) -> bool:
        """
        close serial connection to RFIDler
        """
        try:
            if self.connection:
                self.connection.close()
                self.connection = None
        except Exception as _e:   # pylint: disable=broad-exception-caught
            pass
        return True
