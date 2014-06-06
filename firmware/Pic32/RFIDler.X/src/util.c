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

GNU General Public License

----------------------------------------------------------------------------

Table of Contents

   * GNU GENERAL PUBLIC LICENSE
        o Preamble
        o TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
        o How to Apply These Terms to Your New Programs

----------------------------------------------------------------------------

GNU GENERAL PUBLIC LICENSE

Version 2, June 1991

Copyright (C) 1989, 1991 Free Software Foundation, Inc.
59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.

Preamble

The licenses for most software are designed to take away your freedom to
share and change it. By contrast, the GNU General Public License is intended
to guarantee your freedom to share and change free software--to make sure
the software is free for all its users. This General Public License applies
to most of the Free Software Foundation's software and to any other program
whose authors commit to using it. (Some other Free Software Foundation
software is covered by the GNU Library General Public License instead.) You
can apply it to your programs, too.

When we speak of free software, we are referring to freedom, not price. Our
General Public Licenses are designed to make sure that you have the freedom
to distribute copies of free software (and charge for this service if you
wish), that you receive source code or can get it if you want it, that you
can change the software or use pieces of it in new free programs; and that
you know you can do these things.

To protect your rights, we need to make restrictions that forbid anyone to
deny you these rights or to ask you to surrender the rights. These
restrictions translate to certain responsibilities for you if you distribute
copies of the software, or if you modify it.

For example, if you distribute copies of such a program, whether gratis or
for a fee, you must give the recipients all the rights that you have. You
must make sure that they, too, receive or can get the source code. And you
must show them these terms so they know their rights.

We protect your rights with two steps: (1) copyright the software, and (2)
offer you this license which gives you legal permission to copy, distribute
and/or modify the software.

Also, for each author's protection and ours, we want to make certain that
everyone understands that there is no warranty for this free software. If
the software is modified by someone else and passed on, we want its
recipients to know that what they have is not the original, so that any
problems introduced by others will not reflect on the original authors'
reputations.

Finally, any free program is threatened constantly by software patents. We
wish to avoid the danger that redistributors of a free program will
individually obtain patent licenses, in effect making the program
proprietary. To prevent this, we have made it clear that any patent must be
licensed for everyone's free use or not licensed at all.

The precise terms and conditions for copying, distribution and modification
follow.

TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

0. This License applies to any program or other work which contains a notice
placed by the copyright holder saying it may be distributed under the terms
of this General Public License. The "Program", below, refers to any such
program or work, and a "work based on the Program" means either the Program
or any derivative work under copyright law: that is to say, a work
containing the Program or a portion of it, either verbatim or with
modifications and/or translated into another language. (Hereinafter,
translation is included without limitation in the term "modification".) Each
licensee is addressed as "you".

Activities other than copying, distribution and modification are not covered
by this License; they are outside its scope. The act of running the Program
is not restricted, and the output from the Program is covered only if its
contents constitute a work based on the Program (independent of having been
made by running the Program). Whether that is true depends on what the
Program does.

1. You may copy and distribute verbatim copies of the Program's source code
as you receive it, in any medium, provided that you conspicuously and
appropriately publish on each copy an appropriate copyright notice and
disclaimer of warranty; keep intact all the notices that refer to this
License and to the absence of any warranty; and give any other recipients of
the Program a copy of this License along with the Program.

You may charge a fee for the physical act of transferring a copy, and you
may at your option offer warranty protection in exchange for a fee.

2. You may modify your copy or copies of the Program or any portion of it,
thus forming a work based on the Program, and copy and distribute such
modifications or work under the terms of Section 1 above, provided that you
also meet all of these conditions:

   * a) You must cause the modified files to carry prominent notices stating
     that you changed the files and the date of any change.

   * b) You must cause any work that you distribute or publish, that in
     whole or in part contains or is derived from the Program or any part
     thereof, to be licensed as a whole at no charge to all third parties
     under the terms of this License.

   * c) If the modified program normally reads commands interactively when
     run, you must cause it, when started running for such interactive use
     in the most ordinary way, to print or display an announcement including
     an appropriate copyright notice and a notice that there is no warranty
     (or else, saying that you provide a warranty) and that users may
     redistribute the program under these conditions, and telling the user
     how to view a copy of this License. (Exception: if the Program itself
     is interactive but does not normally print such an announcement, your
     work based on the Program is not required to print an announcement.)

These requirements apply to the modified work as a whole. If identifiable
sections of that work are not derived from the Program, and can be
reasonably considered independent and separate works in themselves, then
this License, and its terms, do not apply to those sections when you
distribute them as separate works. But when you distribute the same sections
as part of a whole which is a work based on the Program, the distribution of
the whole must be on the terms of this License, whose permissions for other
licensees extend to the entire whole, and thus to each and every part
regardless of who wrote it.

Thus, it is not the intent of this section to claim rights or contest your
rights to work written entirely by you; rather, the intent is to exercise
the right to control the distribution of derivative or collective works
based on the Program.

In addition, mere aggregation of another work not based on the Program with
the Program (or with a work based on the Program) on a volume of a storage
or distribution medium does not bring the other work under the scope of this
License.

3. You may copy and distribute the Program (or a work based on it, under
Section 2) in object code or executable form under the terms of Sections 1
and 2 above provided that you also do one of the following:

   * a) Accompany it with the complete corresponding machine-readable source
     code, which must be distributed under the terms of Sections 1 and 2
     above on a medium customarily used for software interchange; or,

   * b) Accompany it with a written offer, valid for at least three years,
     to give any third party, for a charge no more than your cost of
     physically performing source distribution, a complete machine-readable
     copy of the corresponding source code, to be distributed under the
     terms of Sections 1 and 2 above on a medium customarily used for
     software interchange; or,

   * c) Accompany it with the information you received as to the offer to
     distribute corresponding source code. (This alternative is allowed only
     for noncommercial distribution and only if you received the program in
     object code or executable form with such an offer, in accord with
     Subsection b above.)

The source code for a work means the preferred form of the work for making
modifications to it. For an executable work, complete source code means all
the source code for all modules it contains, plus any associated interface
definition files, plus the scripts used to control compilation and
installation of the executable. However, as a special exception, the source
code distributed need not include anything that is normally distributed (in
either source or binary form) with the major components (compiler, kernel,
and so on) of the operating system on which the executable runs, unless that
component itself accompanies the executable.

If distribution of executable or object code is made by offering access to
copy from a designated place, then offering equivalent access to copy the
source code from the same place counts as distribution of the source code,
even though third parties are not compelled to copy the source along with
the object code.

4. You may not copy, modify, sublicense, or distribute the Program except as
expressly provided under this License. Any attempt otherwise to copy,
modify, sublicense or distribute the Program is void, and will automatically
terminate your rights under this License. However, parties who have received
copies, or rights, from you under this License will not have their licenses
terminated so long as such parties remain in full compliance.

5. You are not required to accept this License, since you have not signed
it. However, nothing else grants you permission to modify or distribute the
Program or its derivative works. These actions are prohibited by law if you
do not accept this License. Therefore, by modifying or distributing the
Program (or any work based on the Program), you indicate your acceptance of
this License to do so, and all its terms and conditions for copying,
distributing or modifying the Program or works based on it.

6. Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the original
licensor to copy, distribute or modify the Program subject to these terms
and conditions. You may not impose any further restrictions on the
recipients' exercise of the rights granted herein. You are not responsible
for enforcing compliance by third parties to this License.

7. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License. If you cannot distribute so
as to satisfy simultaneously your obligations under this License and any
other pertinent obligations, then as a consequence you may not distribute
the Program at all. For example, if a patent license would not permit
royalty-free redistribution of the Program by all those who receive copies
directly or indirectly through you, then the only way you could satisfy both
it and this License would be to refrain entirely from distribution of the
Program.

If any portion of this section is held invalid or unenforceable under any
particular circumstance, the balance of the section is intended to apply and
the section as a whole is intended to apply in other circumstances.

It is not the purpose of this section to induce you to infringe any patents
or other property right claims or to contest validity of any such claims;
this section has the sole purpose of protecting the integrity of the free
software distribution system, which is implemented by public license
practices. Many people have made generous contributions to the wide range of
software distributed through that system in reliance on consistent
application of that system; it is up to the author/donor to decide if he or
she is willing to distribute software through any other system and a
licensee cannot impose that choice.

This section is intended to make thoroughly clear what is believed to be a
consequence of the rest of this License.

8. If the distribution and/or use of the Program is restricted in certain
countries either by patents or by copyrighted interfaces, the original
copyright holder who places the Program under this License may add an
explicit geographical distribution limitation excluding those countries, so
that distribution is permitted only in or among countries not thus excluded.
In such case, this License incorporates the limitation as if written in the
body of this License.

9. The Free Software Foundation may publish revised and/or new versions of
the General Public License from time to time. Such new versions will be
similar in spirit to the present version, but may differ in detail to
address new problems or concerns.

Each version is given a distinguishing version number. If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation. If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

10. If you wish to incorporate parts of the Program into other free programs
whose distribution conditions are different, write to the author to ask for
permission. For software which is copyrighted by the Free Software
Foundation, write to the Free Software Foundation; we sometimes make
exceptions for this. Our decision will be guided by the two goals of
preserving the free status of all derivatives of our free software and of
promoting the sharing and reuse of software generally.

NO WARRANTY

11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY FOR
THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO
THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM
PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR
CORRECTION.

12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED TO
LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR
THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

END OF TERMS AND CONDITIONS

How to Apply These Terms to Your New Programs

If you develop a new program, and you want it to be of the greatest possible
use to the public, the best way to achieve this is to make it free software
which everyone can redistribute and change under these terms.

To do so, attach the following notices to the program. It is safest to
attach them to the start of each source file to most effectively convey the
exclusion of warranty; and each file should have at least the "copyright"
line and a pointer to where the full notice is found.

one line to give the program's name and an idea of what it does.
Copyright (C) 19yy  name of author

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this when
it starts in an interactive mode:

Gnomovision version 69, Copyright (C) 19yy name of author
Gnomovision comes with ABSOLUTELY NO WARRANTY; for details
type `show w'.  This is free software, and you are welcome
to redistribute it under certain conditions; type `show c'
for details.

The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License. Of course, the commands you use may be
called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.

You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary. Here is a sample; alter the names:

Yoyodyne, Inc., hereby disclaims all copyright
interest in the program `Gnomovision'
(which makes passes at compilers) written
by James Hacker.

signature of Ty Coon, 1 April 1989
Ty Coon, President of Vice

This General Public License does not permit incorporating your program into
proprietary programs. If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library. If this is what you want to do, use the GNU Library General Public
License instead of this License.

*/

// Author: Adam Laurie <adam@aperturelabs.com>


#include <string.h>
#include <stdio.h>
#include "HardwareProfile.h"
#include "util.h"
#include "rfidler.h"
#include "USB/usb_function_cdc.h"
#include "comms.h"


//const unsigned int TimeScaler= (GetSystemClock() / US_TO_TICKS);
const unsigned int TimeScaler= (GetSystemClock() / TIMER5_PRESCALER) / 1000000; // compensate for pre-scaler
const unsigned long TimeScaler2= (GetSystemClock() / 10000000L);

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
    if(sprintf(target, "%08X", source) != 1)
        return FALSE;
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

// low level pulse timer
unsigned int GetTimer_us(BYTE reset)
{
    unsigned int time;
    
    time= ReadTimer5();

    if(reset)
       WriteTimer5(0L);
    return time / TimeScaler;
}

// low level pulse timer - return prescaled ticks converted back to a long
unsigned long GetTimer_ticks(BYTE reset)
{
    unsigned long time;

    time= ReadTimer5();

    if(reset)
       WriteTimer5(0);
    return time * TIMER5_PRESCALER;
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


// raw timer wait - for things that don't want any delays...
// 1us == x timer ticks where x is what MHz chip is running at (e.g. 80 for 80MHz)
// note that we reset on the way out to ensure external code action is included in
// the timing.
void TimerWait(unsigned long ticks)
{
    while (ReadTimer5() < ticks)
        ;
    WriteTimer5(0);
}

void Delay_us(unsigned long us)
{
    unsigned long ticks= us * TimeScaler2;

    while (ticks--)
        ;
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


