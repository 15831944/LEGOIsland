# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=MxDirectX - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to MxDirectX - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "MxDirectX - Win32 Release" && "$(CFG)" !=\
 "MxDirectX - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MxDirectX.mak" CFG="MxDirectX - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MxDirectX - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MxDirectX - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "MxDirectX - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "MxDirectX - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Release

ALL : "$(OUTDIR)\MxDirectX.lib"

CLEAN : 
	-@erase ".\MxDirectX.lib"
	-@erase ".\Release\MxDirect3D.obj"
	-@erase ".\Release\MxDirectX.pch"
	-@erase ".\Release\MxDirectDraw.obj"
	-@erase ".\Release\MxDirectX.obj"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"MxDirectX.h" /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MxDirectX.pch" /Yu"MxDirectX.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MxDirectX.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/MxDirectX.lib" 
LIB32_OBJS= \
	"$(INTDIR)/MxDirect3D.obj" \
	"$(INTDIR)/MxDirectDraw.obj" \
	"$(INTDIR)/MxDirectX.obj"

"$(OUTDIR)\MxDirectX.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MxDirectX - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Debug

ALL : "$(OUTDIR)\MxDirectXd.lib"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\MxDirectX.pch"
	-@erase ".\MxDirectXd.lib"
	-@erase ".\Debug\MxDirect3D.obj"
	-@erase ".\Debug\MxDirectDraw.obj"
	-@erase ".\Debug\MxDirectX.obj"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"MxDirectX.h" /c
CPP_PROJ=/nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MxDirectX.pch" /Yu"MxDirectX.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MxDirectX.bsc" 
BSC32_SBRS=
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"MxDirectXd.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/MxDirectXd.lib" 
LIB32_OBJS= \
	"$(INTDIR)/MxDirect3D.obj" \
	"$(INTDIR)/MxDirectDraw.obj" \
	"$(INTDIR)/MxDirectX.obj"

"$(OUTDIR)\MxDirectXd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "MxDirectX - Win32 Release"
# Name "MxDirectX - Win32 Debug"

!IF  "$(CFG)" == "MxDirectX - Win32 Release"

!ELSEIF  "$(CFG)" == "MxDirectX - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MxDirect3D.cpp
DEP_CPP_MXDIR=\
	".\MxDirectX.h"\
	".\MxDirectDraw.h"\
	".\MxDirect3D.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	

"$(INTDIR)\MxDirect3D.obj" : $(SOURCE) $(DEP_CPP_MXDIR) "$(INTDIR)"\
 "$(INTDIR)\MxDirectX.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxDirectDraw.cpp
DEP_CPP_MXDIRE=\
	".\MxDirectX.h"\
	".\MxDirectDraw.h"\
	".\MxDirect3D.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	

"$(INTDIR)\MxDirectDraw.obj" : $(SOURCE) $(DEP_CPP_MXDIRE) "$(INTDIR)"\
 "$(INTDIR)\MxDirectX.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxDirectX.cpp
DEP_CPP_MXDIREC=\
	".\MxDirectX.h"\
	".\MxDirectDraw.h"\
	".\MxDirect3D.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	

!IF  "$(CFG)" == "MxDirectX - Win32 Release"

# ADD CPP /Yc"MxDirectX.h"

BuildCmds= \
	$(CPP) /nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MxDirectX.pch" /Yc"MxDirectX.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\MxDirectX.obj" : $(SOURCE) $(DEP_CPP_MXDIREC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MxDirectX.pch" : $(SOURCE) $(DEP_CPP_MXDIREC) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MxDirectX - Win32 Debug"

# ADD CPP /Yc"MxDirectX.h"

BuildCmds= \
	$(CPP) /nologo /MLd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/MxDirectX.pch" /Yc"MxDirectX.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\MxDirectX.obj" : $(SOURCE) $(DEP_CPP_MXDIREC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MxDirectX.pch" : $(SOURCE) $(DEP_CPP_MXDIREC) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
