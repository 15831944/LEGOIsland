# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=misc - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to misc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "misc - Win32 Release" && "$(CFG)" != "misc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak" CFG="misc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "misc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "misc - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "misc - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "misc - Win32 Release"

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

ALL : ".\misc.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoColor.obj"
	-@erase "$(INTDIR)\LegoImage.obj"
	-@erase "$(INTDIR)\LegoStorage.obj"
	-@erase "$(INTDIR)\LegoTexture.obj"
	-@erase "$(INTDIR)\LegoTree.obj"
	-@erase ".\misc.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/misc.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/misc.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"misc.lib"
LIB32_FLAGS=/nologo /out:"misc.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoColor.obj" \
	"$(INTDIR)\LegoImage.obj" \
	"$(INTDIR)\LegoStorage.obj" \
	"$(INTDIR)\LegoTexture.obj" \
	"$(INTDIR)\LegoTree.obj"

".\misc.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

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

ALL : ".\miscd.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoColor.obj"
	-@erase "$(INTDIR)\LegoImage.obj"
	-@erase "$(INTDIR)\LegoStorage.obj"
	-@erase "$(INTDIR)\LegoTexture.obj"
	-@erase "$(INTDIR)\LegoTree.obj"
	-@erase ".\miscd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/misc.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/misc.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"miscd.lib"
LIB32_FLAGS=/nologo /out:"miscd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoColor.obj" \
	"$(INTDIR)\LegoImage.obj" \
	"$(INTDIR)\LegoStorage.obj" \
	"$(INTDIR)\LegoTexture.obj" \
	"$(INTDIR)\LegoTree.obj"

".\miscd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "misc - Win32 Release"
# Name "misc - Win32 Debug"

!IF  "$(CFG)" == "misc - Win32 Release"

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\LegoTree.cpp
DEP_CPP_LEGOT=\
	".\LegoStorage.h"\
	".\LegoTree.h"\
	".\LegoTypes.h"\
	

"$(INTDIR)\LegoTree.obj" : $(SOURCE) $(DEP_CPP_LEGOT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoStorage.cpp
DEP_CPP_LEGOS=\
	".\LegoStorage.h"\
	".\LegoTypes.h"\
	

"$(INTDIR)\LegoStorage.obj" : $(SOURCE) $(DEP_CPP_LEGOS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoTexture.cpp
DEP_CPP_LEGOTE=\
	".\LegoImage.h"\
	".\LegoStorage.h"\
	".\LegoTexture.h"\
	".\LegoTypes.h"\
	

"$(INTDIR)\LegoTexture.obj" : $(SOURCE) $(DEP_CPP_LEGOTE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoImage.cpp
DEP_CPP_LEGOI=\
	".\LegoImage.h"\
	".\LegoStorage.h"\
	".\LegoTypes.h"\
	

"$(INTDIR)\LegoImage.obj" : $(SOURCE) $(DEP_CPP_LEGOI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoColor.cpp
DEP_CPP_LEGOC=\
	".\LegoColor.h"\
	".\LegoStorage.h"\
	".\LegoTypes.h"\
	

"$(INTDIR)\LegoColor.obj" : $(SOURCE) $(DEP_CPP_LEGOC) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
