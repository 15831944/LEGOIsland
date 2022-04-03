# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=ViewManager - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ViewManager - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ViewManager - Win32 Release" && "$(CFG)" !=\
 "ViewManager - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ViewManager.mak" CFG="ViewManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ViewManager - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ViewManager - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "ViewManager - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "ViewManager - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\ViewManager.lib"

CLEAN : 
	-@erase ".\Release\ViewManager.lib"
	-@erase ".\Release\ViewManager.obj"
	-@erase ".\Release\ViewLODList.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/ViewManager.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ViewManager.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/ViewManager.lib" 
LIB32_OBJS= \
	"$(INTDIR)/ViewManager.obj" \
	"$(INTDIR)/ViewLODList.obj"

"$(OUTDIR)\ViewManager.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ViewManager - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ViewManagerd.lib"

CLEAN : 
	-@erase ".\ViewManagerd.lib"
	-@erase ".\Debug\ViewManager.obj"
	-@erase ".\Debug\ViewLODList.obj"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/ViewManager.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ViewManager.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"ViewManagerd.lib"
LIB32_FLAGS=/nologo /out:"ViewManagerd.lib" 
LIB32_OBJS= \
	"$(INTDIR)/ViewManager.obj" \
	"$(INTDIR)/ViewLODList.obj"

"$(OUTDIR)\ViewManagerd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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

# Name "ViewManager - Win32 Release"
# Name "ViewManager - Win32 Debug"

!IF  "$(CFG)" == "ViewManager - Win32 Release"

!ELSEIF  "$(CFG)" == "ViewManager - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ViewManager.cpp

!IF  "$(CFG)" == "ViewManager - Win32 Release"

DEP_CPP_VIEWM=\
	".\viewmanager.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\realtime.h"\
	".\ViewLODList.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\LODList.h"\
	

"$(INTDIR)\ViewManager.obj" : $(SOURCE) $(DEP_CPP_VIEWM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "ViewManager - Win32 Debug"

DEP_CPP_VIEWM=\
	".\viewmanager.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\realtime.h"\
	".\ViewLODList.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	

"$(INTDIR)\ViewManager.obj" : $(SOURCE) $(DEP_CPP_VIEWM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ViewLODList.cpp
DEP_CPP_VIEWL=\
	".\viewmanager.h"\
	".\ViewLODList.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\LODList.h"\
	

"$(INTDIR)\ViewLODList.obj" : $(SOURCE) $(DEP_CPP_VIEWL) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
