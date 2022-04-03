# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=geom - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to geom - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "geom - Win32 Release" && "$(CFG)" != "geom - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "geom.mak" CFG="geom - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "geom - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "geom - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "geom - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "geom - Win32 Release"

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

ALL : ".\geom.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoBox.obj"
	-@erase "$(INTDIR)\LegoFace.obj"
	-@erase "$(INTDIR)\LegoMatrix.obj"
	-@erase "$(INTDIR)\LegoMesh.obj"
	-@erase "$(INTDIR)\LegoSphere.obj"
	-@erase "$(INTDIR)\LegoTextureVertex.obj"
	-@erase "$(INTDIR)\LegoVertex.obj"
	-@erase ".\geom.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/geom.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/geom.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"geom.lib"
LIB32_FLAGS=/nologo /out:"geom.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoBox.obj" \
	"$(INTDIR)\LegoFace.obj" \
	"$(INTDIR)\LegoMatrix.obj" \
	"$(INTDIR)\LegoMesh.obj" \
	"$(INTDIR)\LegoSphere.obj" \
	"$(INTDIR)\LegoTextureVertex.obj" \
	"$(INTDIR)\LegoVertex.obj"

".\geom.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "geom - Win32 Debug"

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

ALL : ".\geomd.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoBox.obj"
	-@erase "$(INTDIR)\LegoFace.obj"
	-@erase "$(INTDIR)\LegoMatrix.obj"
	-@erase "$(INTDIR)\LegoMesh.obj"
	-@erase "$(INTDIR)\LegoSphere.obj"
	-@erase "$(INTDIR)\LegoTextureVertex.obj"
	-@erase "$(INTDIR)\LegoVertex.obj"
	-@erase ".\geomd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /MLd /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/geom.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/geom.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"geomd.lib"
LIB32_FLAGS=/nologo /out:"geomd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoBox.obj" \
	"$(INTDIR)\LegoFace.obj" \
	"$(INTDIR)\LegoMatrix.obj" \
	"$(INTDIR)\LegoMesh.obj" \
	"$(INTDIR)\LegoSphere.obj" \
	"$(INTDIR)\LegoTextureVertex.obj" \
	"$(INTDIR)\LegoVertex.obj"

".\geomd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "geom - Win32 Release"
# Name "geom - Win32 Debug"

!IF  "$(CFG)" == "geom - Win32 Release"

!ELSEIF  "$(CFG)" == "geom - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\LegoBox.cpp

!IF  "$(CFG)" == "geom - Win32 Release"

DEP_CPP_LEGOB=\
	".\LegoBox.h"\
	".\LegoVertex.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	

"$(INTDIR)\LegoBox.obj" : $(SOURCE) $(DEP_CPP_LEGOB) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "geom - Win32 Debug"

DEP_CPP_LEGOB=\
	".\LegoBox.h"\
	".\LegoVertex.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	

"$(INTDIR)\LegoBox.obj" : $(SOURCE) $(DEP_CPP_LEGOB) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoFace.cpp
DEP_CPP_LEGOF=\
	".\LegoFace.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\LegoFace.obj" : $(SOURCE) $(DEP_CPP_LEGOF) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoMatrix.cpp

!IF  "$(CFG)" == "geom - Win32 Release"

DEP_CPP_LEGOM=\
	".\LegoMatrix.h"\
	".\LegoVector.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\Vec.h"\
	

"$(INTDIR)\LegoMatrix.obj" : $(SOURCE) $(DEP_CPP_LEGOM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "geom - Win32 Debug"

DEP_CPP_LEGOM=\
	".\LegoMatrix.h"\
	{$(INCLUDE)}"\Vec.h"\
	

"$(INTDIR)\LegoMatrix.obj" : $(SOURCE) $(DEP_CPP_LEGOM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoMesh.cpp
DEP_CPP_LEGOME=\
	".\LegoFace.h"\
	".\LegoMesh.h"\
	".\LegoTextureVertex.h"\
	".\LegoVertex.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\LegoMesh.obj" : $(SOURCE) $(DEP_CPP_LEGOME) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoSphere.cpp
DEP_CPP_LEGOS=\
	".\LegoSphere.h"\
	".\LegoVertex.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\LegoSphere.obj" : $(SOURCE) $(DEP_CPP_LEGOS) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoVertex.cpp
DEP_CPP_LEGOV=\
	".\LegoVertex.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\LegoVertex.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoTextureVertex.cpp
DEP_CPP_LEGOT=\
	".\LegoTextureVertex.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\LegoTextureVertex.obj" : $(SOURCE) $(DEP_CPP_LEGOT) "$(INTDIR)"


# End Source File
# End Target
# End Project
################################################################################
