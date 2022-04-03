# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=TglAfx - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to TglAfx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TglAfx - Win32 Release" && "$(CFG)" != "TglAfx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "TglAfx.mak" CFG="TglAfx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TglAfx - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TglAfx - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "TglAfx - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "TglAfx - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Release

ALL : "$(OUTDIR)\TglAfx.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoViewWnd.obj"
	-@erase "$(INTDIR)\MxDirect3DWnd.obj"
	-@erase "$(INTDIR)\MxDirectDrawWnd.obj"
	-@erase "$(INTDIR)\TglAfx.obj"
	-@erase "$(INTDIR)\TglAfx.pch"
	-@erase "$(INTDIR)\TglWnd.obj"
	-@erase "$(OUTDIR)\TglAfx.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TglAfx.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/TglAfx.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoViewWnd.obj" \
	"$(INTDIR)\MxDirect3DWnd.obj" \
	"$(INTDIR)\MxDirectDrawWnd.obj" \
	"$(INTDIR)\TglAfx.obj" \
	"$(INTDIR)\TglWnd.obj"

"$(OUTDIR)\TglAfx.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.
INTDIR=.\Debug

ALL : "$(OUTDIR)\TglAfxd.lib"

CLEAN : 
	-@erase "$(INTDIR)\LegoViewWnd.obj"
	-@erase "$(INTDIR)\MxDirect3DWnd.obj"
	-@erase "$(INTDIR)\MxDirectDrawWnd.obj"
	-@erase "$(INTDIR)\TglAfx.obj"
	-@erase "$(INTDIR)\TglAfx.pch"
	-@erase "$(INTDIR)\TglWnd.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\TglAfxd.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/TglAfx.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"TglAfxd.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/TglAfxd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\LegoViewWnd.obj" \
	"$(INTDIR)\MxDirect3DWnd.obj" \
	"$(INTDIR)\MxDirectDrawWnd.obj" \
	"$(INTDIR)\TglAfx.obj" \
	"$(INTDIR)\TglWnd.obj"

"$(OUTDIR)\TglAfxd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "TglAfx - Win32 Release"
# Name "TglAfx - Win32 Debug"

!IF  "$(CFG)" == "TglAfx - Win32 Release"

!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\TglWnd.cpp
DEP_CPP_TGLWN=\
	".\MxDirect3DWnd.h"\
	".\MxDirectDrawWnd.h"\
	".\TglAfx.h"\
	".\TglWnd.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\MxDirect3D.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "TglAfx - Win32 Release"

# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\TglWnd.obj" : $(SOURCE) $(DEP_CPP_TGLWN) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\TglWnd.obj" : $(SOURCE) $(DEP_CPP_TGLWN) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxDirectDrawWnd.cpp

!IF  "$(CFG)" == "TglAfx - Win32 Release"

DEP_CPP_MXDIR=\
	".\MxDirectDrawWnd.h"\
	".\TglAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	
# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\MxDirectDrawWnd.obj" : $(SOURCE) $(DEP_CPP_MXDIR) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

DEP_CPP_MXDIR=\
	".\MxDirectDrawWnd.h"\
	".\TglAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	
# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\MxDirectDrawWnd.obj" : $(SOURCE) $(DEP_CPP_MXDIR) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxDirect3DWnd.cpp
DEP_CPP_MXDIRE=\
	".\MxDirect3DWnd.h"\
	".\MxDirectDrawWnd.h"\
	".\TglAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\MxDirect3D.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "TglAfx - Win32 Release"

# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\MxDirect3DWnd.obj" : $(SOURCE) $(DEP_CPP_MXDIRE) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\MxDirect3DWnd.obj" : $(SOURCE) $(DEP_CPP_MXDIRE) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TglAfx.cpp
DEP_CPP_TGLAF=\
	".\TglAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "TglAfx - Win32 Release"

# ADD CPP /Yc"TglAfx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yc"TglAfx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\TglAfx.obj" : $(SOURCE) $(DEP_CPP_TGLAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TglAfx.pch" : $(SOURCE) $(DEP_CPP_TGLAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

# ADD CPP /Yc"TglAfx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yc"TglAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\TglAfx.obj" : $(SOURCE) $(DEP_CPP_TGLAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\TglAfx.pch" : $(SOURCE) $(DEP_CPP_TGLAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoViewWnd.cpp
DEP_CPP_LEGOV=\
	".\LegoViewWnd.h"\
	".\MxDirect3DWnd.h"\
	".\MxDirectDrawWnd.h"\
	".\TglAfx.h"\
	{$(INCLUDE)}"\Controller.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoView1.h"\
	{$(INCLUDE)}"\MxDirect3D.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "TglAfx - Win32 Release"

# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\LegoViewWnd.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "TglAfx - Win32 Debug"

# ADD CPP /Yu"TglAfx.h"

"$(INTDIR)\LegoViewWnd.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\TglAfx.pch"
   $(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/TglAfx.pch" /Yu"TglAfx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
