# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=writer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to writer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "writer - Win32 Release" && "$(CFG)" != "writer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "writer.mak" CFG="writer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "writer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "writer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "writer - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "writer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\writer.exe"

CLEAN : 
	-@erase "$(INTDIR)\LegoGuiFile.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\writer.obj"
	-@erase "$(INTDIR)\writer.pch"
	-@erase "$(INTDIR)\writer.res"
	-@erase "$(INTDIR)\writerDlg.obj"
	-@erase "$(OUTDIR)\writer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/writer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/writer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/writer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/writer.pdb" /machine:I386 /out:"$(OUTDIR)/writer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LegoGuiFile.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\writer.obj" \
	"$(INTDIR)\writer.res" \
	"$(INTDIR)\writerDlg.obj"

"$(OUTDIR)\writer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "writer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\writer.exe"

CLEAN : 
	-@erase "$(INTDIR)\LegoGuiFile.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\writer.obj"
	-@erase "$(INTDIR)\writer.pch"
	-@erase "$(INTDIR)\writer.res"
	-@erase "$(INTDIR)\writerDlg.obj"
	-@erase "$(OUTDIR)\writer.exe"
	-@erase "$(OUTDIR)\writer.ilk"
	-@erase "$(OUTDIR)\writer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/writer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/writer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/writer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/writer.pdb" /debug /machine:I386 /out:"$(OUTDIR)/writer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LegoGuiFile.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\writer.obj" \
	"$(INTDIR)\writer.res" \
	"$(INTDIR)\writerDlg.obj"

"$(OUTDIR)\writer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "writer - Win32 Release"
# Name "writer - Win32 Debug"

!IF  "$(CFG)" == "writer - Win32 Release"

!ELSEIF  "$(CFG)" == "writer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "writer - Win32 Release"

!ELSEIF  "$(CFG)" == "writer - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\writer.cpp
DEP_CPP_WRITE=\
	".\StdAfx.h"\
	".\writer.h"\
	".\writerDlg.h"\
	

"$(INTDIR)\writer.obj" : $(SOURCE) $(DEP_CPP_WRITE) "$(INTDIR)"\
 "$(INTDIR)\writer.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\writerDlg.cpp
DEP_CPP_WRITER=\
	".\LegoGuiFile.h"\
	".\StdAfx.h"\
	".\writer.h"\
	".\writerDlg.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	

"$(INTDIR)\writerDlg.obj" : $(SOURCE) $(DEP_CPP_WRITER) "$(INTDIR)"\
 "$(INTDIR)\writer.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "writer - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/writer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\writer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "writer - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/writer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\writer.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\writer.rc
DEP_RSC_WRITER_=\
	".\res\writer.ico"\
	".\res\writer.rc2"\
	

"$(INTDIR)\writer.res" : $(SOURCE) $(DEP_RSC_WRITER_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoGuiFile.cpp
DEP_CPP_LEGOG=\
	".\LegoGuiFile.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	

"$(INTDIR)\LegoGuiFile.obj" : $(SOURCE) $(DEP_CPP_LEGOG) "$(INTDIR)"\
 "$(INTDIR)\writer.pch"


# End Source File
# End Target
# End Project
################################################################################
