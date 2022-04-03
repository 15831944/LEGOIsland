# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=roi - Win32 Debug with SmartHeap
!MESSAGE No configuration specified.  Defaulting to roi - Win32 Debug with\
 SmartHeap.
!ENDIF 

!IF "$(CFG)" != "roi - Win32 Release" && "$(CFG)" != "roi - Win32 Debug" &&\
 "$(CFG)" != "roi - Win32 Debug with SmartHeap"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "roi.mak" CFG="roi - Win32 Debug with SmartHeap"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "roi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "roi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "roi - Win32 Debug with SmartHeap" (based on\
 "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "roi - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "roi - Win32 Release"

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

ALL : ".\roi.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoROI.obj"
	-@erase ".\roi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/roi.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/roi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"roi.lib"
LIB32_FLAGS=/nologo /out:"roi.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoROI.obj"

".\roi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "roi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "roi___Wi"
# PROP BASE Intermediate_Dir "roi___Wi"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\roid.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoROI.obj"
	-@erase ".\roid.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/roi.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/roi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"roid.lib"
LIB32_FLAGS=/nologo /out:"roid.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoROI.obj"

".\roid.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "roi - Win32 Debug with SmartHeap"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "roi___W0"
# PROP BASE Intermediate_Dir "roi___W0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug with SmartHeap"
# PROP Intermediate_Dir "Debug with SmartHeap"
# PROP Target_Dir ""
OUTDIR=.\Debug with SmartHeap
INTDIR=.\Debug with SmartHeap

ALL : ".\roidSH.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoROI.obj"
	-@erase ".\roidSH.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "USE_SMART_HEAP" /D MEM_DEBUG=1 /D DEFINE_NEW_MACRO=1 /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "USE_SMART_HEAP" /D MEM_DEBUG=1 /D DEFINE_NEW_MACRO=1 /Fp"$(INTDIR)/roi.pch"\
 /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=".\Debug with SmartHeap/"
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/roi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"roid.lib"
# ADD LIB32 /nologo /out:"roidSH.lib"
LIB32_FLAGS=/nologo /out:"roidSH.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoROI.obj"

".\roidSH.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "roi - Win32 Release"
# Name "roi - Win32 Debug"
# Name "roi - Win32 Debug with SmartHeap"

!IF  "$(CFG)" == "roi - Win32 Release"

!ELSEIF  "$(CFG)" == "roi - Win32 Debug"

!ELSEIF  "$(CFG)" == "roi - Win32 Debug with SmartHeap"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\LegoROI.cpp
DEP_CPP_LEGOR=\
	".\LegoROI.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoColor.h"\
	{$(INCLUDE)}"\LegoFace.h"\
	{$(INCLUDE)}"\LegoImage.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoMesh.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTextureVertex.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "roi - Win32 Release"


"$(INTDIR)\LegoROI.obj" : $(SOURCE) $(DEP_CPP_LEGOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "roi - Win32 Debug"


"$(INTDIR)\LegoROI.obj" : $(SOURCE) $(DEP_CPP_LEGOR) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "roi - Win32 Debug with SmartHeap"


"$(INTDIR)\LegoROI.obj" : $(SOURCE) $(DEP_CPP_LEGOR) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
