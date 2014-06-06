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



#ifndef HARDWARE_PROFILE_UBW32_H
#define HARDWARE_PROFILE_UBW32_H

#include "plib.h"
  
#define GetSystemClock()            (80000000ul)
#define GetPeripheralClock()        (GetSystemClock()) 
#define GetInstructionClock()       (GetSystemClock())

//#define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISAbits.TRISA2    // Input
#define self_power          1

//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISBbits.TRISB5    // Input
#define USB_BUS_SENSE       1

// LEDs
#define mLED_1              LATEbits.LATE3

#define mLED_2              LATEbits.LATE2
#define mLED_Comms          mLED_2

#define mLED_3              LATEbits.LATE1
#define mLED_Clock          mLED_3

#define mLED_4              LATEbits.LATE0
#define mLED_Emulate        mLED_4

#define mLED_5              LATGbits.LATG6
#define mLED_Read           mLED_5

#define mLED_6              LATAbits.LATA15
#define mLED_User           mLED_6

#define mLED_7              LATDbits.LATD11
#define mLED_Error          mLED_7

// active low
#define mLED_ON             0
#define mLED_OFF            1

#define mGetLED_1()         mLED_1
#define mGetLED_USB()       mLED_1
#define mGetLED_2()         mLED_2
#define mGetLED_Comms()     mLED_2
#define mGetLED_3()         mLED_3
#define mGetLED_Clock()     mLED_3
#define mGetLED_4()         mLED_4
#define mGetLED_Emulate()   mLED_4
#define mGetLED_5()         mLED_5
#define mGetLED_Read()      mLED_5
#define mGetLED_6()         mLED_6
#define mGetLED_User()      mLED_6
#define mGetLED_7()         mLED_7
#define mGetLED_Error()     mLED_7

#define mLED_1_On()         mLED_1 = mLED_ON
#define mLED_USB_On()       mLED_1_On()
#define mLED_2_On()         mLED_2 = mLED_ON
#define mLED_Comms_On()     mLED_2_On()
#define mLED_3_On()         mLED_3 = mLED_ON
#define mLED_Clock_On()     mLED_3_On()
#define mLED_4_On()         mLED_4 = mLED_ON
#define mLED_Emulate_On()   mLED_4_On()
#define mLED_5_On()         mLED_5 = mLED_ON
#define mLED_Read_On()      mLED_5_On()
#define mLED_6_On()         mLED_6 = mLED_ON
#define mLED_User_On()      mLED_6_On()
#define mLED_7_On()         mLED_7 = mLED_ON
#define mLED_Error_On()     mLED_7_On()

#define mLED_1_Off()        mLED_1 = mLED_OFF
#define mLED_USB_Off()      mLED_1_Off()
#define mLED_2_Off()        mLED_2 = mLED_OFF
#define mLED_Comms_Off()    mLED_2_Off()
#define mLED_3_Off()        mLED_3 = mLED_OFF
#define mLED_Clock_Off()    mLED_3_Off()
#define mLED_4_Off()        mLED_4 = mLED_OFF
#define mLED_Emulate_Off()  mLED_4_Off()
#define mLED_5_Off()        mLED_5 = mLED_OFF
#define mLED_Read_Off()     mLED_5_Off()
#define mLED_6_Off()        mLED_6 = mLED_OFF
#define mLED_User_Off()     mLED_6_Off()
#define mLED_7_Off()        mLED_7 = mLED_OFF
#define mLED_Error_Off()    mLED_7_Off()

#define mLED_1_Toggle()        mLED_1 = !mLED_1
#define mLED_USB_Toggle()      mLED_1_Toggle()
#define mLED_2_Toggle()        mLED_2 = !mLED_2
#define mLED_Comms_Toggle()    mLED_2_Toggle()
#define mLED_3_Toggle()        mLED_3 = !mLED_3
#define mLED_Clock_Toggle()    mLED_3_Toggle()
#define mLED_4_Toggle()        mLED_4 = !mLED_4
#define mLED_Emulate_Toggle()  mLED_4_Toggle()
#define mLED_5_Toggle()        mLED_5 = !mLED_5
#define mLED_Read_Toggle(   )  mLED_5_Toggle()
#define mLED_6_Toggle()        mLED_6 = !mLED_6
#define mLED_User_Toggle()     mLED_6_Toggle()
#define mLED_7_Toggle()        mLED_7 = !mLED_7
#define mLED_Error_Toggle()    mLED_7_Toggle()

#define mLED_All_On()       { mLED_1_On(); mLED_2_On(); mLED_3_On(); mLED_4_On(); mLED_5_On();  mLED_6_On(); mLED_7_On(); }
#define mLED_All_Off()      { mLED_1_Off(); mLED_2_Off(); mLED_3_Off(); mLED_4_Off(); mLED_5_Off(); mLED_6_Off(); mLED_7_Off(); }

// usb status lights
#define mLED_Both_Off()         {mLED_USB_Off();mLED_Comms_Off();}
#define mLED_Both_On()          {mLED_USB_On();mLED_Comms_On();}
#define mLED_Only_USB_On()      {mLED_USB_On();mLED_Comms_Off();}
#define mLED_Only_Comms_On()    {mLED_USB_Off();mLED_Comms_On();}

/** SWITCH *********************************************************/
#define swBootloader        PORTEbits.RE7
#define swUser              PORTEbits.RE6

/** I/O pin definitions ********************************************/
#define INPUT_PIN                   1
#define OUTPUT_PIN                  0

#define TRUE                        1
#define FALSE                       0

#define EVEN                        0
#define ODD                         1

#define LOW                         FALSE
#define HIGH                        TRUE

// output coil control - select between reader/emulator circuits
#define COIL_MODE                  LATBbits.LATB4
#define COIL_MODE_READER()         COIL_MODE= LOW
#define COIL_MODE_EMULATOR()       COIL_MODE= HIGH

// coil for emulation
#define COIL_OUT                   LATGbits.LATG9
#define COIL_OUT_HIGH()            COIL_OUT=HIGH
#define COIL_OUT_LOW()             COIL_OUT=LOW

// door relay (active low)
#define DOOR_RELAY                  LATAbits.LATA14
#define DOOR_RELAY_OPEN()           DOOR_RELAY= HIGH
#define DOOR_RELAY_CLOSE()          DOOR_RELAY= LOW

// inductance/capicitance freq
#define IC_FREQUENCY               PORTAbits.RA2

#define SNIFFER_COIL               PORTDbits.RD12    // external reader clock detect
#define READER_ANALOGUE            PORTBbits.RB11   // reader coil analogue
#define DIV_LOW_ANALOGUE           PORTBbits.RB12   // voltage divider LOW analogue
#define DIV_HIGH_ANALOGUE          PORTBbits.RB13   // voltage divider HIGH analogue

// clock coil (normally controlled by OC Module, but defined here so we can force it high or low)
#define CLOCK_COIL                 PORTDbits.RD4
#define CLOCK_COIL_MOVED           PORTDbits.RD0 // temporary for greenwire

// digital output after analogue reader circuit
#define READER_DATA                PORTDbits.RD8

// trace / debug
#define DEBUG_PIN_1                 LATCbits.LATC1
#define DEBUG_PIN_1_TOGGLE()        DEBUG_PIN_1= !DEBUG_PIN_1
#define DEBUG_PIN_2                 LATCbits.LATC2
#define DEBUG_PIN_2_TOGGLE()        DEBUG_PIN_2= !DEBUG_PIN_2
#define DEBUG_PIN_3                 LATCbits.LATC3
#define DEBUG_PIN_3_TOGGLE()        DEBUG_PIN_3= !DEBUG_PIN_3
#define DEBUG_PIN_4                 LATEbits.LATE5
#define DEBUG_PIN_4_TOGGLE()        DEBUG_PIN_4= !DEBUG_PIN_4

// spi (sdi1) for sd card (not directly referenced)
//#define SD_CARD_RX                  LATCbits.LATC4
//#define SD_CARD_TX                  LATDbits.LATD0
//#define SD_CARD_CLK                 LATDbits.LATD10
//#define SD_CARD_SS                  LATDbits.LATD9
// spi for SD card
#define SD_CARD_DET                 LATFbits.LATF0
#define SD_CARD_WE                  LATFbits.LATF1      // write enable - unused for microsd but allocated anyway as library checks it
                                                        // (held LOW by default - cut solder bridge to GND to free pin if required)
#define SPI_SD                      SPI_CHANNEL1
#define SPI_SD_BUFF                 SPI1BUF
#define SPI_SD_STAT                 SPI1STATbits
// see section below for more defines!

// iso 7816 smartcard
// microchip SC module defines pins so we don't need to, but
// they are listed here to help avoid conflicts
#define ISO_7816_RX                 LATBbits.LATF2 // RX
#define ISO_7816_TX                 LATBbits.LATF8 // TX
#define ISO_7816_VCC                LATBbits.LATB9 // Power
#define ISO_7816_CLK                LATCbits.LATD1 // Clock
#define ISO_7816_RST                LATEbits.LATE8 // Reset

// user LED
#define USER_LED                    LATDbits.LATD7
#define USER_LED_ON()               LATDbits.LATD7=1
#define USER_LED_OFF()              LATDbits.LATD7=0

// LCR
#define LCR_CALIBRATE               LATBbits.LATB5

// wiegand / clock & data
#define WIEGAND_IN_0                PORTDbits.RD5
#define WIEGAND_IN_0_PULLUP         CNPUEbits.CNPUE14
#define WIEGAND_IN_0_PULLDOWN       CNPDbits.CNPD14
#define WIEGAND_IN_1                PORTDbits.RD6
#define WIEGAND_IN_1_PULLUP         CNPUEbits.CNPUE15
#define WIEGAND_IN_1_PULLDOWN       CNPDbits.CNPD15
#define CAND_IN_DATA                WIEGAND_IN_0
#define CAND_IN_CLOCK               WIEGAND_IN_1

#define WIEGAND_OUT_0               LATDbits.LATD3
#define WIEGAND_OUT_1               LATDbits.LATD2
#define WIEGAND_OUT_0_TRIS          TRISDbits.TRISD3
#define WIEGAND_OUT_1_TRIS          TRISDbits.TRISD2
#define CAND_OUT_DATA               WIEGAND_OUT_0
#define CAND_OUT_CLOCK              WIEGAND_OUT_1

// connect/disconnect reader clock from coil - used to send RWD signals by creating gaps in carrier
#define READER_CLOCK_ENABLE         LATEbits.LATE9
#define READER_CLOCK_ENABLE_ON()    READER_CLOCK_ENABLE=0
#define READER_CLOCK_ENABLE_OFF()   READER_CLOCK_ENABLE=1

// these input pins must NEVER bet set to output or they will cause short circuits!
// they can be used to see data from reader before it goes into or gate
#define OR_IN_A                     PORTAbits.RA4
#define OR_IN_B                     PORTAbits.RA5


// CNCON and CNEN are set to allow wiegand input pin weak pullups to be switched on
#define Init_GPIO() { \
     CNCONbits.ON= TRUE; \
     CNENbits.CNEN14= TRUE; \
     CNENbits.CNEN15= TRUE; \
     TRISAbits.TRISA2= INPUT_PIN; \
     TRISAbits.TRISA4= INPUT_PIN; \
     TRISAbits.TRISA5= INPUT_PIN; \
     TRISAbits.TRISA14= OUTPUT_PIN; \
     TRISAbits.TRISA15= OUTPUT_PIN; \
     TRISBbits.TRISB4= OUTPUT_PIN; \
     TRISBbits.TRISB5= OUTPUT_PIN; \
     TRISBbits.TRISB9= OUTPUT_PIN; \
     TRISBbits.TRISB11= INPUT_PIN; \
     TRISBbits.TRISB12= INPUT_PIN; \
     TRISBbits.TRISB13= INPUT_PIN; \
     TRISCbits.TRISC1= OUTPUT_PIN; \
     TRISCbits.TRISC2= OUTPUT_PIN; \
     TRISCbits.TRISC3= OUTPUT_PIN; \
     TRISCbits.TRISC4= INPUT_PIN; \
     TRISDbits.TRISD0= INPUT_PIN; \
     TRISDbits.TRISD1= OUTPUT_PIN; \
     TRISDbits.TRISD2= OUTPUT_PIN; \
     TRISDbits.TRISD3= OUTPUT_PIN; \
     TRISDbits.TRISD4= OUTPUT_PIN; \
     TRISDbits.TRISD5= INPUT_PIN; \
     TRISDbits.TRISD6= INPUT_PIN; \
     TRISDbits.TRISD7= OUTPUT_PIN; \
     TRISDbits.TRISD8= INPUT_PIN; \
     TRISDbits.TRISD11= OUTPUT_PIN; \
     TRISDbits.TRISD12= INPUT_PIN; \
     TRISEbits.TRISE0= OUTPUT_PIN; \
     TRISEbits.TRISE1= OUTPUT_PIN; \
     TRISEbits.TRISE2= OUTPUT_PIN; \
     TRISEbits.TRISE3= OUTPUT_PIN; \
     TRISEbits.TRISE5= OUTPUT_PIN; \
     TRISEbits.TRISE6= INPUT_PIN; \
     TRISEbits.TRISE7= INPUT_PIN; \
     TRISEbits.TRISE8= OUTPUT_PIN; \
     TRISEbits.TRISE9= OUTPUT_PIN; \
     TRISFbits.TRISF0= INPUT_PIN; \
     TRISFbits.TRISF1= INPUT_PIN; \
     TRISFbits.TRISF2= INPUT_PIN; \
     TRISFbits.TRISF8= OUTPUT_PIN; \
     TRISGbits.TRISG6= OUTPUT_PIN; \
     TRISGbits.TRISG12= INPUT_PIN; \
     TRISGbits.TRISG13= INPUT_PIN; \
     TRISGbits.TRISG9= OUTPUT_PIN; \
     LATBbits.LATB9= LOW; \
     LATCbits.LATC1= LOW; \
     LATCbits.LATC2= LOW; \
     LATCbits.LATC3= LOW; \
     LATDbits.LATD2= WIEGAND_IN_1; \
     LATDbits.LATD3= WIEGAND_IN_0; \
     LATEbits.LATE5= LOW; \
     LATEbits.LATE9= HIGH; \
     }

// uart3 (CLI/API) speed
#define BAUDRATE3       115200UL
#define BRG_DIV3        4
#define BRGH3           1

// spi for potentiometer
#define SPI_POT                     SPI_CHANNEL4
#define SPI_POT_BUFF                SPI4BUF
#define SPI_POT_STAT                SPI4STATbits

// spi for sd card - defines required for Microchip SD-SPI libs
// define interface type
#define USE_SD_INTERFACE_WITH_SPI

#define MDD_USE_SPI_1
#define SPI_START_CFG_1     (PRI_PRESCAL_64_1 | SEC_PRESCAL_8_1 | MASTER_ENABLE_ON | SPI_CKE_ON | SPI_SMP_ON)
#define SPI_START_CFG_2     (SPI_ENABLE)
// Define the SPI frequency
#define SPI_FREQUENCY			(20000000)
// Description: SD-SPI Card Detect Input bit
#define SD_CD               PORTFbits.RF0
// Description: SD-SPI Card Detect TRIS bit
#define SD_CD_TRIS          TRISFbits.TRISF0
// Description: SD-SPI Write Protect Check Input bit
#define SD_WE               PORTFbits.RF1
// Description: SD-SPI Write Protect Check TRIS bit
#define SD_WE_TRIS          TRISFbits.TRISF1
// Description: The main SPI control register
#define SPICON1             SPI1CON
// Description: The SPI status register
#define SPISTAT             SPI1STAT
// Description: The SPI Buffer
#define SPIBUF              SPI1BUF
// Description: The receive buffer full bit in the SPI status register
#define SPISTAT_RBF         SPI1STATbits.SPIRBF
// Description: The bitwise define for the SPI control register (i.e. _____bits)
#define SPICON1bits         SPI1CONbits
// Description: The bitwise define for the SPI status register (i.e. _____bits)
#define SPISTATbits         SPI1STATbits
// Description: The enable bit for the SPI module
#define SPIENABLE           SPICON1bits.ON
// Description: The definition for the SPI baud rate generator register (PIC32)
#define SPIBRG              SPI1BRG
// Description: The TRIS bit for the SCK pin
#define SPICLOCK            TRISDbits.TRISD10
// Description: The TRIS bit for the SDI pin
#define SPIIN               TRISCbits.TRISC4
// Description: The TRIS bit for the SDO pin
#define SPIOUT              TRISDbits.TRISD0
#define SD_CS               LATDbits.LATD9
// Description: SD-SPI Chip Select TRIS bit
#define SD_CS_TRIS          TRISDbits.TRISD9
//SPI library functions
#define putcSPI             putcSPI1
#define getcSPI             getcSPI1
#define OpenSPI(config1, config2)   OpenSPI1(config1, config2)

// Define setup parameters for OpenADC10 function
// Turn module on | Ouput in integer format | Trigger mode auto | Enable autosample
#define ADC_CONFIG1     (ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON)
// ADC ref external | Disable offset test | Disable scan mode | Perform 2 samples | Use dual buffers | Use alternate mode
#define ADC_CONFIG2     (ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON)

// Use ADC internal clock | Set sample time
#define ADC_CONFIG3     (ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_0)

// slow sample rate for tuning coils
#define ADC_CONFIG2_SLOW     (ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_16 | ADC_ALT_BUF_ON | ADC_ALT_INPUT_ON)
#define ADC_CONFIG3_SLOW     (ADC_CONV_CLK_INTERNAL_RC | ADC_SAMPLE_TIME_31)

// use AN11
#define ADC_CONFIGPORT  ENABLE_AN11_ANA
// Do not assign channels to scan
#define ADC_CONFIGSCAN  SKIP_SCAN_ALL

#define ADC_TO_VOLTS        0.003208F


// flash memory - int myvar = *(int*)(myflashmemoryaddress);

// memory is 0x9D005000 to 0x9D07FFFF

#define NVM_MEMORY_END 0x9D07FFFF
#define NVM_PAGE_SIZE	4096
#define NVM_PAGES       2       // config & VTAG
#define RFIDLER_NVM_ADDRESS (NVM_MEMORY_END - (NVM_PAGE_SIZE * NVM_PAGES))

// UART timeout in us
#define SERIAL_TIMEOUT                  100

#endif
