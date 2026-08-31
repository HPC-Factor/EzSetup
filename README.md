# EzSetup
EzSetup originally by Scott Ludwig, with revisions by SPB Software House and C:Amie, HPC:Factor


EZSetup - A tool for creating Windows CE install applications

Description
-----------

EZSetup is a utility for creating setup applications for
Windows CE applications. The setup application created is
compressed and self-contained. A single .exe is created that
when run on a desktop PC, installs a Windows CE application on
a Windows CE device.

EZSetup was created to give the WinCE developer community a
free alternative to the commercial install application tools
such as InstallShield, CuteInstall, and NStall.

EZSetup is a free utility, covered by the Gnu Public License.
The gnu public license is at:

http://www.gnu.org/copyleft/gpl.html

Please contribute to EZSetup so the WinCE community can benefit!
Read the "Wish List" section for more info.

How it works
------------

EZSetup is given .ini and .cabs and two text files as input.
EZSetup has in its resources section two tools:

1> setup.exe
2> cexe.exe

EZSetup then takes these steps

- EZSetup writes setup.exe out to disk as a temp file
- EZSetup writes the .ini and .cabs (which the .ini references),
  and the readme.txt and eula.txt into setup.exe as resources.
- EZSetup writes cexe.exe out to disk as a temp file (cexe.exe
  is an .exe compressor program).
- EZSetup executes cexe.exe on setup.exe to compress the entire
  executable.
- EZSetup then renames setup.exe to the output filename
  specified on the command line.

The new compressed executable can be run directly on a
desktop PC to install the CE application on the CE device. When
the setup program is run, it does this:

- Decompresses it's payload (which is setup.exe compressed) into
  a temp file, then executes this temp file.
- Brings up a dialog with the readme.txt specified on the ezsetup
  command line
- When the user hits "next", a dialog comes up with the eula.txt
  specified on the ezsetup command line (end user license
  agreement).
- When "ok" is pressed, the .cabs and .ini are written to a
  subdirectory of the Windows CE Services directory (this is
  recommended by the CE SDK documentation).
- ceappmgr.exe is launched with a parameter pointing to the .ini
  file, and it takes over from here.
- The decompressed temp file is deleted.

Wish List
---------

1> .inf, .ini, and .cab file creation. EZSetup currently requires
   these files as input, so they need to be created by hand.
   Making .inf and .ini files by hand is somewhat tedious. It
   would be a great benefit to have this supported as some sort
   of wizard. 

2> The current setup app is very simple. It is configurable with
   a readme.txt and a eula.txt - pretty simple. It would be nice
   to move towards conforming to standard setup ui - the blue
   wash background, the dialog asking where on your harddisk to
   store the files, support for desktop PC uninstall, etc.

3> Both EZSetup and the tool it uses, CExe.exe, write resources
   into existing executables. In order to do this, it uses these
   Win32 apis:

   BeginUpdateResource()
   UpdateResource()
   EndUpdateResource()

   These apis don't work on Win95/Win98. They only work on
   NT (the executable that is output from ezsetup will of course
   run on any Windows platform). These are fairly simple apis
   to write; if someone where to write versions of these apis
   then ezsetup.exe and cexe.exe would run on Win95/98.

Source Code
-----------

Included in this distribution is the following source code:

EZSetup.exe
Setup.exe

These projects are VC++ 6.0 projects.

Change History
--------------

 2026/08/31 - v2.2
    C:Amie, HPC:Factor
	- Added -d command line argument to allow the selection of device type for labelling on the UI (Handheld PC, Windows CE, Pocket PC, SmartPhone, Palm Sized PC or Windows Mobile). This defaults to "Windows CE" if not set
	- Fixed alignment of form elements on the initial screen
	- Increased width of elements in the header of the initial screen to reduce chance of line wrapping
	- Re-wrote command line instructions screen
	- Added HPC:Factor as a release contributor
	- Added Czech translation
	- Removed Russian translation remnants from source

 2003/01/24 - v2.1
    Spb Software
  - Better keyboard support
  - Command line uninstall bug is fixed

2002/03/20 - v2.0
    Spb Software
  - Changes unknown

2001/07/20 - v1.1
	Scott Ludwig
	scottlu@eskimo.com
	http://www.eskimo.com/~scottlu

- Added language feature. EzSetup can now create German and French in
	  addition to English localized installers.
- Fixed bug where EzSetup would fail if executed on a path with spaces.

1999/06/23 - v1.0
	Scott Ludwig
	scottlu@eskimo.com
	http://www.eskimo.com/~scottlu

- Created and released v1.0 under gnu public license.
- Created and released v1.0 under gnu public license.
