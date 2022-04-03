# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Lego - Win32 Debug RL20
!MESSAGE No configuration specified.  Defaulting to Lego - Win32 Debug RL20.
!ENDIF 

!IF "$(CFG)" != "Lego - Win32 Release" && "$(CFG)" != "Lego - Win32 Debug RL40"\
 && "$(CFG)" != "Lego - Win32 Debug RL20"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Lego.mak" CFG="Lego - Win32 Debug RL20"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Lego - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Lego - Win32 Debug RL40" (based on "Win32 (x86) Application")
!MESSAGE "Lego - Win32 Debug RL20" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Lego - Win32 Debug RL20"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Lego - Win32 Release"

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

ALL : "$(OUTDIR)\Lego.exe"

CLEAN : 
	-@erase "$(INTDIR)\Cshades.obj"
	-@erase "$(INTDIR)\Lego.obj"
	-@erase "$(INTDIR)\Lego.pch"
	-@erase "$(INTDIR)\Lego.res"
	-@erase "$(INTDIR)\LegoDoc.obj"
	-@erase "$(INTDIR)\LegoView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MxLegoCitizenView.obj"
	-@erase "$(INTDIR)\MxLegoEditorView.obj"
	-@erase "$(INTDIR)\MxLegoView.obj"
	-@erase "$(INTDIR)\RealismDlg.obj"
	-@erase "$(INTDIR)\RVWeightsDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Town.obj"
	-@erase "$(OUTDIR)\Lego.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Lego.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Lego.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Lego.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Lego.pdb" /machine:I386 /out:"$(OUTDIR)/Lego.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cshades.obj" \
	"$(INTDIR)\Lego.obj" \
	"$(INTDIR)\Lego.res" \
	"$(INTDIR)\LegoDoc.obj" \
	"$(INTDIR)\LegoView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MxLegoCitizenView.obj" \
	"$(INTDIR)\MxLegoEditorView.obj" \
	"$(INTDIR)\MxLegoView.obj" \
	"$(INTDIR)\RealismDlg.obj" \
	"$(INTDIR)\RVWeightsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Town.obj"

"$(OUTDIR)\Lego.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Lego___W"
# PROP BASE Intermediate_Dir "Lego___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\LegoRL40.exe" "$(OUTDIR)\Lego.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Cshades.obj"
	-@erase "$(INTDIR)\Cshades.sbr"
	-@erase "$(INTDIR)\Lego.obj"
	-@erase "$(INTDIR)\Lego.pch"
	-@erase "$(INTDIR)\Lego.res"
	-@erase "$(INTDIR)\Lego.sbr"
	-@erase "$(INTDIR)\LegoDoc.obj"
	-@erase "$(INTDIR)\LegoDoc.sbr"
	-@erase "$(INTDIR)\LegoView.obj"
	-@erase "$(INTDIR)\LegoView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MxLegoCitizenView.obj"
	-@erase "$(INTDIR)\MxLegoCitizenView.sbr"
	-@erase "$(INTDIR)\MxLegoEditorView.obj"
	-@erase "$(INTDIR)\MxLegoEditorView.sbr"
	-@erase "$(INTDIR)\MxLegoView.obj"
	-@erase "$(INTDIR)\MxLegoView.sbr"
	-@erase "$(INTDIR)\RealismDlg.obj"
	-@erase "$(INTDIR)\RealismDlg.sbr"
	-@erase "$(INTDIR)\RVWeightsDlg.obj"
	-@erase "$(INTDIR)\RVWeightsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Town.obj"
	-@erase "$(INTDIR)\Town.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Lego.bsc"
	-@erase "$(OUTDIR)\LegoRL40.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\3d\vec" /I "..\..\3d\realtime" /I "..\TGL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Lego.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Lego.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Lego.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Cshades.sbr" \
	"$(INTDIR)\Lego.sbr" \
	"$(INTDIR)\LegoDoc.sbr" \
	"$(INTDIR)\LegoView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MxLegoCitizenView.sbr" \
	"$(INTDIR)\MxLegoEditorView.sbr" \
	"$(INTDIR)\MxLegoView.sbr" \
	"$(INTDIR)\RealismDlg.sbr" \
	"$(INTDIR)\RVWeightsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Town.sbr"

"$(OUTDIR)\Lego.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ..\..\3d\realtime\debug\realtime.lib ..\..\3d\pcube\debug\pcube.lib ..\TGL\debug\tglrl20.lib rlddf.lib rlddfglu.lib rlff.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 tglrl40d.lib d3drm.lib realtimed.lib viewmanagerd.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC" /out:"Debug/LegoRL40.exe"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=tglrl40d.lib d3drm.lib realtimed.lib viewmanagerd.lib pcubed.lib\
 TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib\
 /nologo /subsystem:windows /profile /debug /machine:I386\
 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC"\
 /out:"$(OUTDIR)/LegoRL40.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cshades.obj" \
	"$(INTDIR)\Lego.obj" \
	"$(INTDIR)\Lego.res" \
	"$(INTDIR)\LegoDoc.obj" \
	"$(INTDIR)\LegoView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MxLegoCitizenView.obj" \
	"$(INTDIR)\MxLegoEditorView.obj" \
	"$(INTDIR)\MxLegoView.obj" \
	"$(INTDIR)\RealismDlg.obj" \
	"$(INTDIR)\RVWeightsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Town.obj"

"$(OUTDIR)\LegoRL40.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Lego___W"
# PROP BASE Intermediate_Dir "Lego___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\LegoRL20.exe" "$(OUTDIR)\Lego.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Cshades.obj"
	-@erase "$(INTDIR)\Cshades.sbr"
	-@erase "$(INTDIR)\Lego.obj"
	-@erase "$(INTDIR)\Lego.pch"
	-@erase "$(INTDIR)\Lego.res"
	-@erase "$(INTDIR)\Lego.sbr"
	-@erase "$(INTDIR)\LegoDoc.obj"
	-@erase "$(INTDIR)\LegoDoc.sbr"
	-@erase "$(INTDIR)\LegoView.obj"
	-@erase "$(INTDIR)\LegoView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MxLegoCitizenView.obj"
	-@erase "$(INTDIR)\MxLegoCitizenView.sbr"
	-@erase "$(INTDIR)\MxLegoEditorView.obj"
	-@erase "$(INTDIR)\MxLegoEditorView.sbr"
	-@erase "$(INTDIR)\MxLegoView.obj"
	-@erase "$(INTDIR)\MxLegoView.sbr"
	-@erase "$(INTDIR)\RealismDlg.obj"
	-@erase "$(INTDIR)\RealismDlg.sbr"
	-@erase "$(INTDIR)\RVWeightsDlg.obj"
	-@erase "$(INTDIR)\RVWeightsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Town.obj"
	-@erase "$(INTDIR)\Town.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Lego.bsc"
	-@erase "$(OUTDIR)\LegoRL20.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Lego.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Lego.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Lego.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Cshades.sbr" \
	"$(INTDIR)\Lego.sbr" \
	"$(INTDIR)\LegoDoc.sbr" \
	"$(INTDIR)\LegoView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MxLegoCitizenView.sbr" \
	"$(INTDIR)\MxLegoEditorView.sbr" \
	"$(INTDIR)\MxLegoView.sbr" \
	"$(INTDIR)\RealismDlg.sbr" \
	"$(INTDIR)\RVWeightsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Town.sbr"

"$(OUTDIR)\Lego.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 ..\..\3d\realtime\debug\realtime.lib ..\..\3d\pcube\debug\pcube.lib ..\TGL\debug\tglrl20.lib rlddf.lib rlddfglu.lib rlff.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 tglrl20d.lib rlddf.lib rlddfglu.lib rlff.lib realtimed.lib viewmanagerd.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC" /out:"Debug/LegoRL20.exe"
# SUBTRACT LINK32 /nodefaultlib
LINK32_FLAGS=tglrl20d.lib rlddf.lib rlddfglu.lib rlff.lib realtimed.lib\
 viewmanagerd.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib\
 animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /profile /debug\
 /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD"\
 /nodefaultlib:"LIBC" /out:"$(OUTDIR)/LegoRL20.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Cshades.obj" \
	"$(INTDIR)\Lego.obj" \
	"$(INTDIR)\Lego.res" \
	"$(INTDIR)\LegoDoc.obj" \
	"$(INTDIR)\LegoView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MxLegoCitizenView.obj" \
	"$(INTDIR)\MxLegoEditorView.obj" \
	"$(INTDIR)\MxLegoView.obj" \
	"$(INTDIR)\RealismDlg.obj" \
	"$(INTDIR)\RVWeightsDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Town.obj"

"$(OUTDIR)\LegoRL20.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Lego - Win32 Release"
# Name "Lego - Win32 Debug RL40"
# Name "Lego - Win32 Debug RL20"

!IF  "$(CFG)" == "Lego - Win32 Release"

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Lego - Win32 Release"

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lego.cpp
DEP_CPP_LEGO_=\
	".\Lego.h"\
	".\Legodoc.h"\
	".\LegoView.h"\
	".\Mainfrm.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
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
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\Lego.obj" : $(SOURCE) $(DEP_CPP_LEGO_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\Lego.obj" : $(SOURCE) $(DEP_CPP_LEGO_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\Lego.sbr" : $(SOURCE) $(DEP_CPP_LEGO_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\Lego.obj" : $(SOURCE) $(DEP_CPP_LEGO_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\Lego.sbr" : $(SOURCE) $(DEP_CPP_LEGO_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\Stdafx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Lego.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lego.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Lego.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lego.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Lego.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Lego.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Lego - Win32 Release"

DEP_CPP_MAINF=\
	".\Lego.h"\
	".\LegoView.h"\
	".\Mainfrm.h"\
	".\MxLegoCitizenView.h"\
	".\MxLegoView.h"\
	".\RealismDlg.h"\
	".\RVWeightsDlg.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

DEP_CPP_MAINF=\
	".\Lego.h"\
	".\LegoView.h"\
	".\Mainfrm.h"\
	".\MxLegoCitizenView.h"\
	".\MxLegoView.h"\
	".\RealismDlg.h"\
	".\RVWeightsDlg.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

DEP_CPP_MAINF=\
	".\Lego.h"\
	".\LegoView.h"\
	".\Mainfrm.h"\
	".\MxLegoCitizenView.h"\
	".\MxLegoView.h"\
	".\RealismDlg.h"\
	".\RVWeightsDlg.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoDoc.cpp
DEP_CPP_LEGOD=\
	".\Lego.h"\
	".\Legodoc.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
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
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\LegoDoc.obj" : $(SOURCE) $(DEP_CPP_LEGOD) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\LegoDoc.obj" : $(SOURCE) $(DEP_CPP_LEGOD) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\LegoDoc.sbr" : $(SOURCE) $(DEP_CPP_LEGOD) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\LegoDoc.obj" : $(SOURCE) $(DEP_CPP_LEGOD) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\LegoDoc.sbr" : $(SOURCE) $(DEP_CPP_LEGOD) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoView.cpp
DEP_CPP_LEGOV=\
	".\Lego.h"\
	".\Legodoc.h"\
	".\LegoView.h"\
	".\MxLegoCitizenView.h"\
	".\MxLegoEditorView.h"\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\version.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\LegoView.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\LegoView.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\LegoView.sbr" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\LegoView.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\LegoView.sbr" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lego.rc
DEP_RSC_LEGO_R=\
	".\Res\Lego.ico"\
	".\Res\Lego.rc2"\
	".\Res\Legodoc.ico"\
	".\Res\Toolbar.bmp"\
	{$(INCLUDE)}"\Palette.bmp"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\Lego.res" : $(SOURCE) $(DEP_RSC_LEGO_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\Lego.res" : $(SOURCE) $(DEP_RSC_LEGO_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\Lego.res" : $(SOURCE) $(DEP_RSC_LEGO_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Cshades.cpp
DEP_CPP_CSHAD=\
	".\Cshades.h"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\Cshades.obj" : $(SOURCE) $(DEP_CPP_CSHAD) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"
   $(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Lego.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE)


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Cshades.obj" : $(SOURCE) $(DEP_CPP_CSHAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Cshades.sbr" : $(SOURCE) $(DEP_CPP_CSHAD) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\Cshades.obj" : $(SOURCE) $(DEP_CPP_CSHAD) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Cshades.sbr" : $(SOURCE) $(DEP_CPP_CSHAD) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Town.cpp

!IF  "$(CFG)" == "Lego - Win32 Release"

DEP_CPP_TOWN_=\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
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
	

"$(INTDIR)\Town.obj" : $(SOURCE) $(DEP_CPP_TOWN_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

DEP_CPP_TOWN_=\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
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
	

"$(INTDIR)\Town.obj" : $(SOURCE) $(DEP_CPP_TOWN_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\Town.sbr" : $(SOURCE) $(DEP_CPP_TOWN_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

DEP_CPP_TOWN_=\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
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
	

"$(INTDIR)\Town.obj" : $(SOURCE) $(DEP_CPP_TOWN_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\Town.sbr" : $(SOURCE) $(DEP_CPP_TOWN_) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RVWeightsDlg.cpp
DEP_CPP_RVWEI=\
	".\Lego.h"\
	".\RVWeightsDlg.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\RVWeightsDlg.obj" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\RVWeightsDlg.obj" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\RVWeightsDlg.sbr" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\RVWeightsDlg.obj" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\RVWeightsDlg.sbr" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RealismDlg.cpp
DEP_CPP_REALI=\
	".\Lego.h"\
	".\RealismDlg.h"\
	".\Stdafx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\RealismDlg.obj" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\RealismDlg.obj" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\RealismDlg.sbr" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\RealismDlg.obj" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\RealismDlg.sbr" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxLegoView.cpp

!IF  "$(CFG)" == "Lego - Win32 Release"

DEP_CPP_MXLEG=\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3D.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\MxLegoView.obj" : $(SOURCE) $(DEP_CPP_MXLEG) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

DEP_CPP_MXLEG=\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3D.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\MxLegoView.obj" : $(SOURCE) $(DEP_CPP_MXLEG) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MxLegoView.sbr" : $(SOURCE) $(DEP_CPP_MXLEG) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

DEP_CPP_MXLEG=\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3D.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\MxLegoView.obj" : $(SOURCE) $(DEP_CPP_MXLEG) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MxLegoView.sbr" : $(SOURCE) $(DEP_CPP_MXLEG) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxLegoEditorView.cpp

!IF  "$(CFG)" == "Lego - Win32 Release"

DEP_CPP_MXLEGO=\
	".\Lego.h"\
	".\MxLegoEditorView.h"\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\MxLegoEditorView.obj" : $(SOURCE) $(DEP_CPP_MXLEGO) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"

DEP_CPP_MXLEGO=\
	".\Lego.h"\
	".\MxLegoEditorView.h"\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\MxLegoEditorView.obj" : $(SOURCE) $(DEP_CPP_MXLEGO) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MxLegoEditorView.sbr" : $(SOURCE) $(DEP_CPP_MXLEGO) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"

DEP_CPP_MXLEGO=\
	".\Lego.h"\
	".\MxLegoEditorView.h"\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\MxLegoEditorView.obj" : $(SOURCE) $(DEP_CPP_MXLEGO) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MxLegoEditorView.sbr" : $(SOURCE) $(DEP_CPP_MXLEGO) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MxLegoCitizenView.cpp
DEP_CPP_MXLEGOC=\
	".\Lego.h"\
	".\MxLegoCitizenView.h"\
	".\MxLegoView.h"\
	".\Stdafx.h"\
	".\Town.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\TglWnd.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "Lego - Win32 Release"


"$(INTDIR)\MxLegoCitizenView.obj" : $(SOURCE) $(DEP_CPP_MXLEGOC) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL40"


"$(INTDIR)\MxLegoCitizenView.obj" : $(SOURCE) $(DEP_CPP_MXLEGOC) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MxLegoCitizenView.sbr" : $(SOURCE) $(DEP_CPP_MXLEGOC) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ELSEIF  "$(CFG)" == "Lego - Win32 Debug RL20"


"$(INTDIR)\MxLegoCitizenView.obj" : $(SOURCE) $(DEP_CPP_MXLEGOC) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"

"$(INTDIR)\MxLegoCitizenView.sbr" : $(SOURCE) $(DEP_CPP_MXLEGOC) "$(INTDIR)"\
 "$(INTDIR)\Lego.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
################################################################################
# Section Lego : {900AA0F7-64A9-11CF-B788-444553540000}
# 	1:17:ID_INDICATOR_TIME:103
# 	1:17:ID_INDICATOR_DATE:102
# 	2:2:BH:
# 	2:17:ID_INDICATOR_TIME:ID_INDICATOR_TIME
# 	2:17:ID_INDICATOR_DATE:ID_INDICATOR_DATE
# End Section
################################################################################
