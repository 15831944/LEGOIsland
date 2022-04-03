# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Viewer - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Viewer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Viewer - Win32 Release" && "$(CFG)" != "Viewer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Viewer.mak" CFG="Viewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Viewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Viewer - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Viewer - Win32 Debug"
MTL=mktyplib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Viewer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Viewer.exe"

CLEAN : 
	-@erase ".\Release\Viewer.exe"
	-@erase ".\Release\Viewer.obj"
	-@erase ".\viewer.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Viewer.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /fo"viewer.res" /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"viewer.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Viewer.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 rlddf.lib rlddfglu.lib rlff.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib"
LINK32_FLAGS=rlddf.lib rlddfglu.lib rlff.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/Viewer.pdb" /machine:I386\
 /nodefaultlib:"libc.lib" /out:"$(OUTDIR)/Viewer.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Viewer.obj" \
	".\viewer.res"

"$(OUTDIR)\Viewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Viewer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Viewer__"
# PROP BASE Intermediate_Dir "Viewer__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Viewer.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\Viewer.exe"
	-@erase ".\Debug\Viewer.obj"
	-@erase ".\viewer.res"
	-@erase ".\Debug\Viewer.ilk"
	-@erase ".\Debug\Viewer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Viewer.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /fo"viewer.res" /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"viewer.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Viewer.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 rlddf.lib rlddfglu.lib rlff.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libc.libd"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=rlddf.lib rlddfglu.lib rlff.lib geomd.lib miscd.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Viewer.pdb" /debug\
 /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libc.libd"\
 /out:"$(OUTDIR)/Viewer.exe" 
LINK32_OBJS= \
	"$(INTDIR)/Viewer.obj" \
	".\viewer.res"

"$(OUTDIR)\Viewer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Viewer - Win32 Release"
# Name "Viewer - Win32 Debug"

!IF  "$(CFG)" == "Viewer - Win32 Release"

!ELSEIF  "$(CFG)" == "Viewer - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\viewer.rc

"$(INTDIR)\viewer.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Viewer.cpp
DEP_CPP_VIEWE=\
	{$(INCLUDE)}"\Rl.h"\
	{$(INCLUDE)}"\Rlwin.h"\
	".\Viewer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoMesh.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoBox.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\Vec.h"\
	{$(INCLUDE)}"\ddraw.h"\
	"..\..\Sources\Geom\LegoVertex.h"\
	"..\..\Sources\Geom\LegoFace.h"\
	

"$(INTDIR)\Viewer.obj" : $(SOURCE) $(DEP_CPP_VIEWE) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
