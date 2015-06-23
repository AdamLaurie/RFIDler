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
 ***************************************************************************/

// Author: Adam Laurie <adam@aperturelabs.com>


#include <string.h>
#include <stdio.h>
#include "HardwareProfile.h"
#include "util.h"
#include "rfidler.h"
#include "USB/usb_function_cdc.h"
#include "comms.h"

// rtc
rtccTime	RTC_time;			// time structure
rtccDate	RTC_date;			// date structure

// are we +/- x%?
BYTE approx(unsigned long number, unsigned long target, unsigned char percentage)
{
    if(number > (target - (target / (100L / (unsigned long) percentage))) && number < (target + (target / (100L / (unsigned long) percentage))))
            return TRUE;
    return FALSE;
}

// convert BCD to unsigned int, length in hex digits
unsigned int bcdtouint(BYTE *bcd, BYTE length)
{
    BYTE i;
    unsigned int num= 0, mult= 1;

    for(i= 0 ; i < length ; ++i)
    {
        num += (bcd[length - i - 1] - '0') * mult;
        mult *= 10;
    }
    return num;
}

// convert BCD to ulong long, length in hex digits
unsigned long long bcdtoulonglong(BYTE *bcd, BYTE length)
{
    BYTE i;
    unsigned long long num= 0LL, mult= 1LL;

    for(i= 0 ; i < length ; ++i)
    {
        num += (bcd[length - i - 1] - '0') * mult;
        mult *= 10LL;
    }
    return num;
}

// convert binary array to unsigned int
unsigned int binarraytoint(BYTE *bin, BYTE length)
{
    unsigned int out= 0;

    while(length)
        out += *(bin++) << ((length--) - 1);

    return out;
}

// convert integer to binarray, limited to specified number of LSB
void inttobinarray(BYTE *target, unsigned int source, unsigned int bits)
{
    while(bits--)
    {
        *(target++)= (source >> bits) & 0x01;
    }
}

// convert ulong to binarray, limited to specified number of LSB
void ulongtobinarray(BYTE *target, unsigned long source, unsigned int bits)
{
    while(bits--)
    {
        *(target++)= (source >> bits) & 0x01;
    }
}

// convert ulong to binarray, limited to specified number of LSB
void ulonglongtobinarray(BYTE *target, unsigned long long source, unsigned int bits)
{
    while(bits--)
    {
        *(target++)= (source >> bits) & 0x01;
    }
}


BOOL ulongtohex(BYTE *target, unsigned long source)
{
    BYTE tmp[9];

    sprintf(tmp, "%08lX", source);
    memcpy(target, tmp, 8);
    return TRUE;
}

// convert integer to binstring, limited to specified number of LSB
void inttobinstring(BYTE *target, unsigned int source, unsigned int bits)
{
    inttobinarray(target, source, bits);
    binarraytobinstring(target, target, bits);
}

// convert ulong to binstring, limited to specified number of LSB
void ulongtobinstring(BYTE *target, unsigned long source, unsigned int bits)
{
    ulongtobinarray(target, source, bits);
    binarraytobinstring(target, target, bits);
}

// convert binary array to unsigned long long
unsigned long long binarraytoulonglong(BYTE *bin, BYTE length)
{
    unsigned long long out= 0LL;

    while(length)
        out += *(bin++) << ((length--) - 1);

    return out;
}

// convert binary array to unsigned long long
unsigned long binarraytoulong(BYTE *bin, BYTE length)
{
    unsigned long out= 0LL;

    while(length)
        out += *(bin++) << ((length--) - 1);

    return out;
}

// convert 2 character hex string to BYTE
BYTE hextobyte(BYTE *hex)
{
    int ret= 0;

    sscanf(hex, "%2X", &ret);
    return (BYTE) ret;
}

// print readable (ascii) characters from HEX string
void printhexreadable(BYTE *hex)
{
    BYTE    x[2]= {'\0', '\0'};
    
    while(*hex)
    {
        x[0]= hextobyte(hex);
        if(x[0] < 0x20 || x[0] > 0x7e)
            x[0]= '.';
        UserMessage("%s", x);
        hex += 2;
    }
}

// convert 8 digit hex to unsigned long
unsigned long hextoulong(BYTE *hex)
{
    unsigned long ret= 0L;

    if(sscanf(hex, "%8X", &ret) != 1)
            return 0L;
    return ret;
}

// convert byte-reversed 8 digit hex to unsigned long
unsigned long hexreversetoulong(BYTE *hex)
{
    unsigned long ret= 0L;
    unsigned int x;
    BYTE i;

    if(strlen(hex) != 8)
        return 0L;

    for(i= 0 ; i < 4 ; ++i)
    {
        if(sscanf(hex, "%2X", &x) != 1)
                return 0L;
        ret += ((unsigned long) x) << i * 8;
        hex += 2;
    }
    return ret;
}

// convert hex to unsigned long long
unsigned long long hextoulonglong(BYTE *hex)
{
    BYTE tmp[64];
    
    if(hextobinarray(tmp, hex) != 64)
        return 0L;
    return binarraytoulonglong(tmp, 64);
}

// convert byte-reversed 12 digit hex to unsigned long
unsigned long long hexreversetoulonglong(BYTE *hex)
{
    unsigned long long ret= 0LL;
    BYTE tmp[9];
    
    // this may seem an odd way to do it, but weird compiler issues were 
    // breaking direct conversion!
    
    tmp[8]= '\0';
    memset(tmp + 4, '0', 4);
    memcpy(tmp, hex + 8, 4);
    ret= hexreversetoulong(tmp);
    ret <<= 32;
    memcpy(tmp, hex, 8);
    ret += hexreversetoulong(tmp);
    return ret;
}

// fixme - this is effectively replaced by the above!
// library sscanf llx is broken, so we have to do it ourselves...
char hextolonglong(unsigned long long *out, unsigned char *hex)
{
    char i, c= 0;
    static unsigned int x;
    unsigned char tmp[3]= {0,0,0};

    *out= 0LL;
    if(strlen(hex) % 2)
        return 0;
    // deal with section of 224 bit IDs
    if(strlen(hex) > 16)
        i= 14;
    else
        i= strlen(hex) - 2;
    for( ; i >= 0 ; i -= 2)
    {
        tmp[0]= hex[i];
        tmp[1]= hex[i+1];
        if (!sscanf(tmp,"%X",&x))
            return 0LL;
        *out += (unsigned long long) x << c;
        c += 8;
    }
    return 1;
}

// convert hex to sequence of 0/1 bit values
// returns number of bits converted
unsigned int hextobinarray(unsigned char *target, unsigned char *source)
{
    unsigned int length, i, count= 0;
    unsigned char x;

    length= strlen(source);
    // process 4 bits (1 hex digit) at a time
    while(length--)
    {
        x= *(source++);
        // capitalize
        if (x >= 'a' && x <= 'f')
            x -= 32;
        // convert to numeric value
        if (x >= '0' && x <= '9')
            x -= '0';
        else if (x >= 'A' && x <= 'F')
            x -= 'A' - 10;
        else
            return 0;
        // output
        for(i= 0 ; i < 4 ; ++i, ++count)
            *(target++)= (x >> (3 - i)) & 1;
    }
    
    return count;
}

// convert hex to human readable binary string
unsigned int hextobinstring(unsigned char *target, unsigned char *source)
{
    unsigned int length;

    if(!(length= hextobinarray(target, source)))
        return 0;
    binarraytobinstring(target, target, length);
    return length;
}

// convert binary array of 0x00/0x01 values to hex (safe to do in place as target will always be shorter than source)
// return number of bits converted
unsigned int binarraytohex(unsigned char *target, unsigned char *source, unsigned int length)
{
    unsigned char i, x;
    unsigned int j= length;

    if(j % 4)
        return 0;

    while(j)
    {
        for(i= x= 0 ; i < 4 ; ++i)
            x += (source[i] << (3 - i));
        sprintf(target,"%X", x);
        ++target;
        source += 4;
        j -= 4;
    }

    return length;
}

// print binary array as hex
void hexprintbinarray(BYTE *bin, unsigned int length)
{
    while(length--)
        UserMessageNum("%02lx", *(bin++));
}

// convert binary string of '0'/'1' values to hex (safe to do in place as target will always be shorter than source)
// return number of bits converted
unsigned int binstringtohex(unsigned char *target, unsigned char *source)
{
    unsigned char i, x;
    unsigned int j, length;

    length= j= strlen(source);
    if(j % 4)
        return 0;

    while(j)
    {
        for(i= x= 0 ; i < 4 ; ++i)
            x += ((source[i] - '0') << (3 - i));
        sprintf(target,"%X", x);
        ++target;
        source += 4;
        j -= 4;
    }

    return length;
}

// convert human readable bin string to unsigned char
void binstringtobyte(BYTE *target, unsigned char *source, BYTE length)
{
    BYTE shift= 0;
    
    *target= 0;
    while(length)
    {
        *target += (source[length - 1] - '0') << shift;
        length--;
        shift++;
    }
}

// get a specified bit
unsigned char getbit(unsigned char byte, unsigned char bit)
{
    return (byte >> bit) & 0x01;
}

// convert array of BYTES to readable hex
void bytestohex(unsigned char *target, unsigned char *source, unsigned int length)
{
    while(length--)
        sprintf(target++,"%X",source++);
}

// convert human readable binary to binary array
unsigned int binstringtobinarray(BYTE *target, BYTE *source)
{
    unsigned int length, i;

    length= strlen(source);
    for(i= 0 ; i < length ; ++i)
    {
        if(*source != '0' && *source != '1')
            return 0;
        *(target++)= *(source++) - '0';
    }
    return length;
}

// convert binary array to human readable binary
void binarraytobinstring(BYTE *target, BYTE *source, unsigned int length)
{
    unsigned int i;

    for(i= 0 ; i < length ; ++i)
        *(target++)= *(source++) + '0';
    *target= '\0';
}

// invert binary string
void invertbinstring(BYTE *target, BYTE *source)
{
    unsigned int length;

    length= strlen(source);
    while(length--)
        *(target++)= (!(*(source++) - '0') + '0');
}

// print a hex value as binary
void printhexasbin(unsigned char *hex)
{
    unsigned int length;

    length= hextobinarray(TmpBits,hex);
    printbinarray(TmpBits, length);
}

// print a binstring value as hex
void printbinstringashex(unsigned char *bin)
{
    if(binstringtohex(TmpBits, bin))
        UserMessage("%s\r\n", TmpBits);
}

void printbinarray(unsigned char *bin, unsigned int length)
{
    while(length--)
    {
        // normally we are printing 0/1, but if we're looking at anything else we want a space between values
        if(*bin > 1)
            UserMessageNum("%d ",*bin);
        else
            UserMessageNum("%d",*bin);

        bin++;
    }
    UserMessage("%s", "\r\n");
}


// convert sequence of 0/1 bit values to manchester encoded
// we use a temp buffer so it's safe to encode in-place
unsigned int manchester_encode(unsigned char *target, unsigned char *source, unsigned int length)
{
    unsigned char tmp[TMP_LARGE_BUFF_LEN];
    unsigned int i= 0;

    while(length--)
    {
        if(*(source++))
        {
            tmp[i++]= 0x01;
            tmp[i++]= 0x00;
        }
        else
        {
           tmp[i++]= 0x00;
           tmp[i++]= 0x01;
        }
    }
    memcpy(target, tmp, i);
    return i;
}

// convert manchester encoded 01/10 to 1/0
// target is smaller than source, so safe to do in place
// length is source buffer length
// return size of target buffer
unsigned int manchester_decode(unsigned char *target, unsigned char *source, unsigned int length)
{
    unsigned int i= 0;

    while(i < length)
    {
        // check for bit error
        if(*source == *(source+1))
            return i / 2;
        *(target++)= *(source);
        source += 2;
        i += 2;
    }
    return i / 2;
}

char * strip_newline(char *buff)
{
    int i= 0;

    while(buff[i] != '\0')
    {
        if (buff[i] == '\r' || buff[i] == '\n')
        {
            buff[i]= '\0';
            return buff;
        }
        ++i;
    }
    return buff;
}

// command ACK when in API mode
// '.' for command complete
// '+' for data to follow
BOOL command_ack(BOOL data)
{
    if(Interface == INTERFACE_API)
    {
        if(data)
            UserMessage("%s", "+");
        else
            UserMessage("%s", ".");
    }
    else
    {
        if(data)
            UserMessage("%s", "\r\n");
        else
            UserMessage("%s", "\r\nOK\r\n\r\n");
    }
    return TRUE;
}

// command NACK when in API mode
// note we still return TRUE to flag CLI that command was recognised
BOOL command_nack(BYTE *reason)
{
    if(Interface == INTERFACE_API)
        UserMessage("!%s\r\n", reason);
    else
        UserMessage("\r\n%s\r\n\r\n", reason);
    return TRUE;
}

// command UNKNOWN when in API mode
BOOL command_unknown(void)
{
    if(Interface == INTERFACE_API)
        UserMessage("%s", "?");
    return FALSE;
}


// convert to upper and strip trailing spaces
void ToUpper(char *string)
{
    int i;

    for (i = 0; i < strlen(string); ++i)
        if (string[i] >= 'a' && string[i] <= 'z')
            string[i] -= 'a' - 'A';

    while(string[strlen(string) - 1] == ' ')
        string[strlen(string) - 1]= '\0';
}

// reverse a string in place
void string_reverse(unsigned char *string, unsigned int length)
{
    unsigned int i;
    unsigned char x, *p;

    i= length / 2;
    p= string;
    while(length > i)
    {
        x= string[length - 1];
        string[length - 1]= *p;
        *p= x;
        ++p;
        --length;
    }
}

// bytes swap a string in place
BOOL string_byteswap(unsigned char *string, unsigned int length)
{
    unsigned char x;

    if(length % 2)
        return FALSE;

    while(length)
    {
        x= *string;
        *string= *(string + 1);
        *(string + 1)= x;
        length -= 2;
        string += 2;
    }
    return TRUE;
}

// return parity bit required to match type
BYTE parity(unsigned char *bits, BYTE type, unsigned int length)
{
    unsigned int x;

    for(x= 0 ; length > 0 ; --length)
        x += bits[length - 1];
    x %= 2;

    return x ^ type;
}

// wait for a pulse on the reader coil and return it's length
// note this will return a partial pulse if it's already started
// return pulse length in ticks
unsigned long get_reader_pulse(unsigned int timeout_us)
{
    // wait for start of pulse
    GetTimer_us(RESET);
    while(!READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return 0;

    // measure pulse length
    GetTimer_us(RESET);
    while(READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return 0;

    return GetTimer_ticks(NO_RESET);
}

// wait for a gap on the reader coil and return it's length
// note this will return a partial gap if it's already started
// return pulse length in ticks
unsigned long get_reader_gap(unsigned int timeout_us)
{
    // wait for start of gap
    GetTimer_us(RESET);
    while(READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return 0;

    // measure gap length
    GetTimer_us(RESET);
    while(!READER_DATA)
        if(timeout_us)
            if (GetTimer_us(NO_RESET) > timeout_us)
                return 0;

    return GetTimer_ticks(NO_RESET);
}

// ccitt standard crc
unsigned int crc_ccitt(BYTE *data, unsigned int length)
{
    return crc16(0, data, length, CRC16_MASK_CCITT);
}

// 16 bit generic crc
unsigned int crc16(unsigned int crc, BYTE *data, unsigned int length, unsigned int mask)
{
    unsigned int i, j, c;

    for(i= 0 ; i <  length ; ++i)
    {
        c= (unsigned int) data[i];
        c <<= 8;
        for(j= 0 ; j < 8 ; ++j)
        {
           if ((crc ^ c) & 0x8000)
               crc= (crc << 1) ^ mask;
           else
               crc <<= 1;
           c <<= 1;
        }
        crc &= 0xffff;
    }
    return crc;
}

void space_indent(BYTE count)
{
    while(count)
    {
        UserMessage("%s", " ");
        --count;
    }
}

// some simple XML helper routines
void xml_version(void)
{
    UserMessage("%s", "<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
}

void xml_header(BYTE *item, BYTE *indent)
{
    UserMessage("%s", "\r\n");
    space_indent(*indent);
    UserMessage("<%s>", item);
    (*indent) += 2;
}

void xml_footer(BYTE *item, BYTE *indent, BOOL newline)
{
    if(newline)
        UserMessage("%s", "\r\n");
    if(*indent > 1)
        (*indent) -= 2;
    else
        *indent= 0;
    if(newline)
        space_indent(*indent);
    UserMessage("</%s>", item);
}

void xml_indented_text(BYTE *data, BYTE indent)
{
    UserMessage("%s", "\r\n");
    space_indent(indent);
    UserMessage("%s", data);
}

void xml_item_text(BYTE *item, BYTE *data, BYTE *indent)
{
    xml_header(item, indent);
    UserMessage("%s", data);
    xml_footer(item, indent, NO_NEWLINE);
}

void xml_item_decimal(BYTE *item, BYTE num, BYTE *indent)
{
    BYTE tmp[4];

    xml_header(item, indent);
    sprintf(tmp, "%d", num);
    UserMessage("%s", tmp);
    xml_footer(item, indent, NO_NEWLINE);
}

void xml_indented_array(BYTE *data, BYTE mask, unsigned int length, BYTE indent)
{
    unsigned int i;

    for(i= 0 ; i < length ; ++i)
    {
        if(!(i % 32))
        {
            UserMessage("%s", "\r\n");
            space_indent(indent);
        }
        UserMessageNum("%02lx", data[i] & mask);
    }
}

void xml_item_array(BYTE *item, BYTE *data, BYTE mask, unsigned int length, BYTE *indent)
{
    xml_header(item, indent);
    xml_indented_array(data, mask, length, *indent);
    xml_footer(item, indent, NEWLINE);
}
