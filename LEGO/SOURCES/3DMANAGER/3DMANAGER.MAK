# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=3DManager - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to 3DManager - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "3DManager - Win32 Release" && "$(CFG)" !=\
 "3DManager - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "3DManager.mak" CFG="3DManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "3DManager - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "3DManager - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "3DManager - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "3DManager - Win32 Release"

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

ALL : "$(OUTDIR)\3DManager.lib"

CLEAN : 
	-@erase "$(INTDIR)\3DManager.pch"
	-@erase "$(INTDIR)\Controller.obj"
	-@erase "$(INTDIR)\Lego3DManager.obj"
	-@erase "$(INTDIR)\Lego3DView.obj"
	-@erase "$(INTDIR)\LegoView1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TglSurface.obj"
	-@erase "$(OUTDIR)\3DManager.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/3DManager.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/3DManager.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/3DManager.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Controller.obj" \
	"$(INTDIR)\Lego3DManager.obj" \
	"$(INTDIR)\Lego3DView.obj" \
	"$(INTDIR)\LegoView1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TglSurface.obj"

"$(OUTDIR)\3DManager.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "3DManager - Win32 Debug"

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

ALL : "$(OUTDIR)\3DManagerd.lib"

CLEAN : 
	-@erase "$(INTDIR)\3DManager.pch"
	-@erase "$(INTDIR)\Controller.obj"
	-@erase "$(INTDIR)\Lego3DManager.obj"
	-@erase "$(INTDIR)\Lego3DView.obj"
	-@erase "$(INTDIR)\LegoView1.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TglSurface.obj"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\3DManagerd.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/3DManager.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/3DManager.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"3DManagerd.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/3DManagerd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Controller.obj" \
	"$(INTDIR)\Lego3DManager.obj" \
	"$(INTDIR)\Lego3DView.obj" \
	"$(INTDIR)\LegoView1.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TglSurface.obj"

"$(OUTDIR)\3DManagerd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "3DManager - Win32 Release"
# Name "3DManager - Win32 Debug"

!IF  "$(CFG)" == "3DManager - Win32 Release"

!ELSEIF  "$(CFG)" == "3DManager - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TglSurface.cpp
DEP_CPP_TGLSU=\
	".\StdAfx.h"\
	".\TglSurface.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

"$(INTDIR)\TglSurface.obj" : $(SOURCE) $(DEP_CPP_TGLSU) "$(INTDIR)"\
 "$(INTDIR)\3DManager.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lego3DManager.cpp
DEP_CPP_LEGO3=\
	".\Lego3DManager.h"\
	".\Lego3DView.h"\
	".\LegoView1.h"\
	".\StdAfx.h"\
	".\TglSurface.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	

"$(INTDIR)\Lego3DManager.obj" : $(SOURCE) $(DEP_CPP_LEGO3) "$(INTDIR)"\
 "$(INTDIR)\3DManager.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lego3DView.cpp
DEP_CPP_LEGO3D=\
	".\Lego3DView.h"\
	".\LegoView1.h"\
	".\StdAfx.h"\
	".\TglSurface.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\Lego3DView.obj" : $(SOURCE) $(DEP_CPP_LEGO3D) "$(INTDIR)"\
 "$(INTDIR)\3DManager.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoView1.cpp
DEP_CPP_LEGOV=\
	".\LegoView1.h"\
	".\StdAfx.h"\
	".\TglSurface.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

"$(INTDIR)\LegoView1.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\3DManager.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "3DManager - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/3DManager.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\3DManager.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "3DManager - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/3DManager.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\3DManager.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Controller.cpp
DEP_CPP_CONTR=\
	".\Controller.h"\
	".\Lego3DView.h"\
	".\LegoView1.h"\
	".\StdAfx.h"\
	".\TglSurface.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\Controller.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"\
 "$(INTDIR)\3DManager.pch"


# End Source File
# End Target
# End Project
################################################################################
