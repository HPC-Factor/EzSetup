# Microsoft Developer Studio Project File - Name="setup" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=setup - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "setup.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "setup.mak" CFG="setup - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "setup - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 German Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 French Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 Spanish Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 Italian Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 Czech Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 Swedish Release" (based on "Win32 (x86) Application")
!MESSAGE "setup - Win32 Portuguese Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/Products/EzSetup/sources/Setup", MSXCAAAA"
# PROP Scc_LocalPath "Desktop"
# PROP WCE_FormatVersion ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"Release/setup_english.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"main" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_German_Release"
# PROP BASE Intermediate_Dir "setup___Win32_German_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_German_Release"
# PROP Intermediate_Dir "setup___Win32_German_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_German_Release/setup_german.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_French_Release"
# PROP BASE Intermediate_Dir "setup___Win32_French_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_French_Release"
# PROP Intermediate_Dir "setup___Win32_French_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_French_Release/setup_french.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_Spanish_Release"
# PROP BASE Intermediate_Dir "setup___Win32_Spanish_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_Spanish_Release"
# PROP Intermediate_Dir "setup___Win32_Spanish_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_Spanish_Release/setup_spanish.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_Spanish_Release/setup_spanish.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_Italian_Release"
# PROP BASE Intermediate_Dir "setup___Win32_Italian_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_Italian_Release"
# PROP Intermediate_Dir "setup___Win32_Italian_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"Release/setup_english.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_Italian_Release/setup_italian.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_Czech_Release"
# PROP BASE Intermediate_Dir "setup___Win32_Czech_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_Czech_Release"
# PROP Intermediate_Dir "setup___Win32_Czech_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"Release/setup_english.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_Czech_Release/setup_czech.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_Swedish_Release"
# PROP BASE Intermediate_Dir "setup___Win32_Swedish_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_Swedish_Release"
# PROP Intermediate_Dir "setup___Win32_Swedish_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"Release/setup_english.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_Swedish_Release/setup_swedish.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "setup___Win32_Portuguese_Release"
# PROP BASE Intermediate_Dir "setup___Win32_Portuguese_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "setup___Win32_Portuguese_Release"
# PROP Intermediate_Dir "setup___Win32_Portuguese_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"Release/setup_english.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libc.lib /nologo /entry:"main" /subsystem:windows /machine:I386 /nodefaultlib /out:"setup___Win32_Portuguese_Release/setup_portuguese.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "setup - Win32 Release"
# Name "setup - Win32 Debug"
# Name "setup - Win32 German Release"
# Name "setup - Win32 French Release"
# Name "setup - Win32 Spanish Release"
# Name "setup - Win32 Italian Release"
# Name "setup - Win32 Czech Release"
# Name "setup - Win32 Swedish Release"
# Name "setup - Win32 Portuguese Release"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\install_splash.bmp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\res_czech.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_english.rc

!IF  "$(CFG)" == "setup - Win32 Release"

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_french.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_german.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_italian.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_portuguese.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_spanish.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\res_swedish.rc

!IF  "$(CFG)" == "setup - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 German Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 French Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Spanish Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Italian Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Czech Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Swedish Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "setup - Win32 Portuguese Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Wizard.cpp
# End Source File
# Begin Source File

SOURCE=.\Wizard.h
# End Source File
# End Target
# End Project
