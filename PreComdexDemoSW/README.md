# Updated README from 5/20/2020

The Navigator was software that ran on top of the DOS file system that managed the Simon
user interface. This folder contains an early version to show how the navigator works to vendors.
It is NOT the final version of code that went into Simon. There's a few missing files, so please consider
it in as-is condition.

The software in this folder works only on the original IBM PC which has a CGA (640x200) compatible graphics card.
Perhaps someone can get a virtual environment working on Windows, but at this moment I have only
managed to get it working on a "vintage" IBM PS/2 model P70 that I have around. 

The 1992 Comdex demo and the 1994 Simon product both used a system-on-chip from Vadem called VG230 which was 8086 compatible
and an architecture that was very close to IBM's PC XT. This made it very fast to develop on since applications
could be developed on the PC and run on Simon with very little effort.

Cellular radios can take 2 years or more to design from scratch. To help speed development, existing radios were embedded.
The 1992 Comdex demo worked with a custom Motorola MicroTac cellular radio which had a unique 3-wire bus to control it. Of note
is the code in PH_RTNS.CPP which managed that communication to make calls and get status. The final Simon product
used a cellular radio from Mitsubishi and not Motorola.

Note that the software runs in portrait mode, so you need to tilt your head (or monitor) 90 degrees to view it on a PC which
normally runs in landscape mode. Also, on a PC a mouse was used to emulate the touch screen.
Also FYI, all files ending in '@' are font files in various styles and sizes that are rotated to work in portrait mode.

# Original README from 10/12/1992

This diskette contains programs needed to display the various phone related
screens for the personal communicator and a program that will display fonts
that are currently available for our use.  Mail screens are not included,
but their appearance is similar as is navigation to those screens.  To run
the program displaying screens:  (ALL PROGRAMS RUN UNDER DOS ONLY.)

* put the diskette in your 3.5 inch floppy drive
* change directory to that drive
* type "mouse" (the word minus quotes) to start the mouse driver this step is not needed if a Microsoft compatible mouse driver is already resident)
* type "nav" (minus quotes)

When the first screen appears, select any box.  This may be confusing at
first due to the fact that there is no cursor displayed.  That will not be a
problem on the product because the user knows where his finger is touching.
When the left mouse button is depressed, move the mouse around until a box
highlights.  Then move to the desired box and release the left mouse button.
The box will be selected when the left mouse button is released.

Resulting actions are as described in the spec which you already have.
Selecting some boxes will cause new screens to appear.  Selecting "back"
will take you to the preceeding screen.  Selecting "phone" will take you
directly to the "phone" screen.  The "tools" screen is not yet implemented.
Nor is the "help" screen.  But, the appearance of those screens and the
navigation to them will be the same as the 10 screens that you do have.

If you choose, performance in navigating between screens is greatly improved
by running from hard disk (or ramdisk) instead of from the diskette.  To do
this, copy all the files on the diskette to a subdirectory and follow the
steps listed above.  IF YOU DON'T COPY TO A SUBDIRECTORY, BE CAREFUL NOT TO
OVERWRITE ANY "MOUSE.COM" MOUSE DRIVER THAT YOU ALREADY HAVE ON YOUR SYSTEM.

Note that:
1. Screens will occupy the entire crt view and distort the size of items on the screen.
2. This level of code can now be "control breaked" out of.  Since the structure of the function spawns other programs, it is necessary to hold down "control C" until the program stops.

Also included in subdirectory "fonts" is a copy of all currently available
fonts, a program "showfont.exe" that will display the fonts, and a file
describing how to use "showfont.exe" called "showfont.doc".
