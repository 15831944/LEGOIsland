# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

!IF "$(CFG)" == ""
CFG=realtime - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to realtime - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "realtime - Win32 Release" && "$(CFG)" !=\
 "realtime - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Realtime.mak" CFG="realtime - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "realtime - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "realtime - Win32 Debug" (based on "Win32 (x86) Static Library")
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
# PROP Target_Last_Scanned "realtime - Win32 Debug"
CPP=cl.exe

!IF  "$(CFG)" == "realtime - Win32 Release"

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

ALL : "$(OUTDIR)\Realtime.lib"

CLEAN : 
	-@erase "$(INTDIR)\OrientableROI.obj"
	-@erase "$(INTDIR)\realtime.obj"
	-@erase "$(INTDIR)\RelativeROI.obj"
	-@erase "$(INTDIR)\Viewmath.obj"
	-@erase "$(OUTDIR)\Realtime.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)/Realtime.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Realtime.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/Realtime.lib" 
LIB32_OBJS= \
	"$(INTDIR)\OrientableROI.obj" \
	"$(INTDIR)\realtime.obj" \
	"$(INTDIR)\RelativeROI.obj" \
	"$(INTDIR)\Viewmath.obj"

"$(OUTDIR)\Realtime.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "realtime - Win32 Debug"

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

ALL : "$(OUTDIR)\realtimed.lib" "$(OUTDIR)\Realtime.bsc"

CLEAN : 
	-@erase "$(INTDIR)\OrientableROI.obj"
	-@erase "$(INTDIR)\OrientableROI.sbr"
	-@erase "$(INTDIR)\realtime.obj"
	-@erase "$(INTDIR)\realtime.sbr"
	-@erase "$(INTDIR)\RelativeROI.obj"
	-@erase "$(INTDIR)\RelativeROI.sbr"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(INTDIR)\Viewmath.obj"
	-@erase "$(INTDIR)\Viewmath.sbr"
	-@erase "$(OUTDIR)\Realtime.bsc"
	-@erase "$(OUTDIR)\realtimed.lib"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Realtime.pch" /YX /Fo"$(INTDIR)/" /Fd"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Realtime.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\OrientableROI.sbr" \
	"$(INTDIR)\realtime.sbr" \
	"$(INTDIR)\RelativeROI.sbr" \
	"$(INTDIR)\Viewmath.sbr"

"$(OUTDIR)\Realtime.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"realtimed.lib"
LIB32_FLAGS=/nologo /out:"$(OUTDIR)/realtimed.lib" 
LIB32_OBJS= \
	"$(INTDIR)\OrientableROI.obj" \
	"$(INTDIR)\realtime.obj" \
	"$(INTDIR)\RelativeROI.obj" \
	"$(INTDIR)\Viewmath.obj"

"$(OUTDIR)\realtimed.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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

# Name "realtime - Win32 Release"
# Name "realtime - Win32 Debug"

!IF  "$(CFG)" == "realtime - Win32 Release"

!ELSEIF  "$(CFG)" == "realtime - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Viewmath.cpp
DEP_CPP_VIEWM=\
	".\Viewmath.h"\
	{$(INCLUDE)}"\Pcube.h"\
	{$(INCLUDE)}"\vec.h"\
	

!IF  "$(CFG)" == "realtime - Win32 Release"


"$(INTDIR)\Viewmath.obj" : $(SOURCE) $(DEP_CPP_VIEWM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "realtime - Win32 Debug"


"$(INTDIR)\Viewmath.obj" : $(SOURCE) $(DEP_CPP_VIEWM) "$(INTDIR)"

"$(INTDIR)\Viewmath.sbr" : $(SOURCE) $(DEP_CPP_VIEWM) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\realtime.cpp

!IF  "$(CFG)" == "realtime - Win32 Release"

DEP_CPP_REALT=\
	".\realtime.h"\
	".\Viewmath.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\vec.h"\
	

"$(INTDIR)\realtime.obj" : $(SOURCE) $(DEP_CPP_REALT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "realtime - Win32 Debug"

DEP_CPP_REALT=\
	".\realtime.h"\
	".\Viewmath.h"\
	{$(INCLUDE)}"\vec.h"\
	

"$(INTDIR)\realtime.obj" : $(SOURCE) $(DEP_CPP_REALT) "$(INTDIR)"

"$(INTDIR)\realtime.sbr" : $(SOURCE) $(DEP_CPP_REALT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RelativeROI.cpp
DEP_CPP_RELAT=\
	".\LODList.h"\
	".\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\vec.h"\
	

!IF  "$(CFG)" == "realtime - Win32 Release"


"$(INTDIR)\RelativeROI.obj" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "realtime - Win32 Debug"


"$(INTDIR)\RelativeROI.obj" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"

"$(INTDIR)\RelativeROI.sbr" : $(SOURCE) $(DEP_CPP_RELAT) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OrientableROI.cpp
DEP_CPP_ORIEN=\
	".\LODList.h"\
	".\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\vec.h"\
	

!IF  "$(CFG)" == "realtime - Win32 Release"


"$(INTDIR)\OrientableROI.obj" : $(SOURCE) $(DEP_CPP_ORIEN) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "realtime - Win32 Debug"


"$(INTDIR)\OrientableROI.obj" : $(SOURCE) $(DEP_CPP_ORIEN) "$(INTDIR)"

"$(INTDIR)\OrientableROI.sbr" : $(SOURCE) $(DEP_CPP_ORIEN) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
