# Microsoft Developer Studio Project File - Name="calc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=calc - Win32 DebugRel
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "calc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "calc.mak" CFG="calc - Win32 DebugRel"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "calc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "calc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "calc - Win32 DebugRel" (based on "Win32 (x86) Console Application")
!MESSAGE "calc - Win32 ReleaseSimpleFx" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "calc - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"P:\ass parser\HaAssScripter\ha_ass_script.exe"

!ELSEIF  "$(CFG)" == "calc - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "calc - Win32 DebugRel"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "calc___Win32_DebugRel"
# PROP BASE Intermediate_Dir "calc___Win32_DebugRel"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "calc___Win32_DebugRel"
# PROP Intermediate_Dir "calc___Win32_DebugRel"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /ML /W3 /O2 /Ob2 /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"AssCalcPublic.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "calc - Win32 ReleaseSimpleFx"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "calc___Win32_ReleaseSimpleFx"
# PROP BASE Intermediate_Dir "calc___Win32_ReleaseSimpleFx"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "calc___Win32_ReleaseSimpleFx"
# PROP Intermediate_Dir "calc___Win32_ReleaseSimpleFx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "HA_SIMPLEFX" /FR /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"P:\ass parser\HaAssScripter\ha_ass_script.exe"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"P:\ass parser\simplefx\ha_ass_script_simplefx.exe"

!ENDIF 

# Begin Target

# Name "calc - Win32 Release"
# Name "calc - Win32 Debug"
# Name "calc - Win32 DebugRel"
# Name "calc - Win32 ReleaseSimpleFx"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "out"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\def_out\lex.calc_.c
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\def_out\lexCalc.l

!IF  "$(CFG)" == "calc - Win32 Release"

!ELSEIF  "$(CFG)" == "calc - Win32 Debug"

# Begin Custom Build
InputPath=..\def_out\lexCalc.l

"..\def_out\lex.calc_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd "..\def_out" 
	..\flex -Pcalc_ lexCalc.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 DebugRel"

# Begin Custom Build
InputPath=..\def_out\lexCalc.l

"..\def_out\lex.calc_c.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd "..\def_out" 
	..\flex -Pcalc_ lexCalc.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 ReleaseSimpleFx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\def_out\lexcalc.y

!IF  "$(CFG)" == "calc - Win32 Release"

!ELSEIF  "$(CFG)" == "calc - Win32 Debug"

# Begin Custom Build
InputPath=..\def_out\lexcalc.y

BuildCmds= \
	cd "..\def_out" \
	..\bison.exe --defines -pcalc_ lexcalc.y \
	

"..\def_out\lexcalc_tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\def_out\lexcalc_tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 DebugRel"

# Begin Custom Build
InputPath=..\def_out\lexcalc.y

BuildCmds= \
	cd "..\def_out" \
	..\bison.exe --defines -pcalc_ lexcalc.y \
	

"..\def_out\lexcalc_tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\def_out\lexcalc_tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 ReleaseSimpleFx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\def_out\lexcalc_tab.c
# ADD CPP /YX"stdafx.h"
# End Source File
# End Group
# Begin Group "in"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\def_out\lex.src_.c
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\def_out\srcread.l

!IF  "$(CFG)" == "calc - Win32 Release"

!ELSEIF  "$(CFG)" == "calc - Win32 Debug"

# Begin Custom Build
InputPath=..\def_out\srcread.l

"..\def_out\lex.src_.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd "..\def_out" 
	..\flex -Psrc_ srcread.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 DebugRel"

# Begin Custom Build
InputPath=..\def_out\srcread.l

"..\def_out\lex.src_.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd "..\def_out" 
	..\flex -Psrc_ srcread.l 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 ReleaseSimpleFx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\def_out\srcread.y

!IF  "$(CFG)" == "calc - Win32 Release"

!ELSEIF  "$(CFG)" == "calc - Win32 Debug"

# Begin Custom Build
InputPath=..\def_out\srcread.y

BuildCmds= \
	cd "..\def_out" \
	..\bison.exe --defines -psrc_ srcread.y \
	

"..\def_out\srcread_tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\def_out\srcread_tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 DebugRel"

# Begin Custom Build
InputPath=..\def_out\srcread.y

BuildCmds= \
	cd "..\def_out" \
	..\bison.exe --defines -psrc_ srcread.y \
	

"..\def_out\srcread_tab.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

"..\def_out\srcread_tab.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "calc - Win32 ReleaseSimpleFx"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\def_out\srcread_tab.c
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\def_out\srcread_tab.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\asciIn.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\calc.cpp
# ADD CPP /YX"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
