# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ROIInspector - Win32 Debug RL20
!MESSAGE No configuration specified.  Defaulting to ROIInspector - Win32 Debug\
 RL20.
!ENDIF 

!IF "$(CFG)" != "ROIInspector - Win32 Release" && "$(CFG)" !=\
 "ROIInspector - Win32 Debug RL40" && "$(CFG)" !=\
 "ROIInspector - Win32 Debug RL20"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ROIInspector.mak" CFG="ROIInspector - Win32 Debug RL20"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ROIInspector - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ROIInspector - Win32 Debug RL40" (based on "Win32 (x86) Application")
!MESSAGE "ROIInspector - Win32 Debug RL20" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "ROIInspector - Win32 Debug RL20"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "ROIInspector - Win32 Release"

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

ALL : "$(OUTDIR)\ROIInspector.exe"

CLEAN : 
	-@erase "$(INTDIR)\AnimateDlg.obj"
	-@erase "$(INTDIR)\AxisDlg.obj"
	-@erase "$(INTDIR)\CostsPage.obj"
	-@erase "$(INTDIR)\LODPropPage.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ROIDoc.obj"
	-@erase "$(INTDIR)\ROIInspector.obj"
	-@erase "$(INTDIR)\ROIInspector.pch"
	-@erase "$(INTDIR)\ROIInspector.res"
	-@erase "$(INTDIR)\ROIInspectorController.obj"
	-@erase "$(INTDIR)\ROIInspectorROI.obj"
	-@erase "$(INTDIR)\ROIInspectorView.obj"
	-@erase "$(INTDIR)\ROIPropPage.obj"
	-@erase "$(INTDIR)\ROIPropSheet.obj"
	-@erase "$(INTDIR)\ROITreeCtrl.obj"
	-@erase "$(INTDIR)\SelectLODsDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\ROIInspector.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ROIInspector.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ROIInspector.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ROIInspector.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/ROIInspector.pdb" /machine:I386\
 /out:"$(OUTDIR)/ROIInspector.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimateDlg.obj" \
	"$(INTDIR)\AxisDlg.obj" \
	"$(INTDIR)\CostsPage.obj" \
	"$(INTDIR)\LODPropPage.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ROIDoc.obj" \
	"$(INTDIR)\ROIInspector.obj" \
	"$(INTDIR)\ROIInspector.res" \
	"$(INTDIR)\ROIInspectorController.obj" \
	"$(INTDIR)\ROIInspectorROI.obj" \
	"$(INTDIR)\ROIInspectorView.obj" \
	"$(INTDIR)\ROIPropPage.obj" \
	"$(INTDIR)\ROIPropSheet.obj" \
	"$(INTDIR)\ROITreeCtrl.obj" \
	"$(INTDIR)\SelectLODsDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ROIInspector.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "InspectR"
# PROP BASE Intermediate_Dir "InspectR"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ROIInspectorRL40.exe" "$(OUTDIR)\ROIInspector.bsc"

CLEAN : 
	-@erase "$(INTDIR)\AnimateDlg.obj"
	-@erase "$(INTDIR)\AnimateDlg.sbr"
	-@erase "$(INTDIR)\AxisDlg.obj"
	-@erase "$(INTDIR)\AxisDlg.sbr"
	-@erase "$(INTDIR)\CostsPage.obj"
	-@erase "$(INTDIR)\CostsPage.sbr"
	-@erase "$(INTDIR)\LODPropPage.obj"
	-@erase "$(INTDIR)\LODPropPage.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ROIDoc.obj"
	-@erase "$(INTDIR)\ROIDoc.sbr"
	-@erase "$(INTDIR)\ROIInspector.obj"
	-@erase "$(INTDIR)\ROIInspector.pch"
	-@erase "$(INTDIR)\ROIInspector.res"
	-@erase "$(INTDIR)\ROIInspector.sbr"
	-@erase "$(INTDIR)\ROIInspectorController.obj"
	-@erase "$(INTDIR)\ROIInspectorController.sbr"
	-@erase "$(INTDIR)\ROIInspectorROI.obj"
	-@erase "$(INTDIR)\ROIInspectorROI.sbr"
	-@erase "$(INTDIR)\ROIInspectorView.obj"
	-@erase "$(INTDIR)\ROIInspectorView.sbr"
	-@erase "$(INTDIR)\ROIPropPage.obj"
	-@erase "$(INTDIR)\ROIPropPage.sbr"
	-@erase "$(INTDIR)\ROIPropSheet.obj"
	-@erase "$(INTDIR)\ROIPropSheet.sbr"
	-@erase "$(INTDIR)\ROITreeCtrl.obj"
	-@erase "$(INTDIR)\ROITreeCtrl.sbr"
	-@erase "$(INTDIR)\SelectLODsDlg.obj"
	-@erase "$(INTDIR)\SelectLODsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ROIInspector.bsc"
	-@erase "$(OUTDIR)\ROIInspectorRL40.exe"
	-@erase "$(OUTDIR)\ROIInspectorRL40.ilk"
	-@erase "$(OUTDIR)\ROIInspectorRL40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ROIInspector.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ROIInspector.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ROIInspector.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnimateDlg.sbr" \
	"$(INTDIR)\AxisDlg.sbr" \
	"$(INTDIR)\CostsPage.sbr" \
	"$(INTDIR)\LODPropPage.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ROIDoc.sbr" \
	"$(INTDIR)\ROIInspector.sbr" \
	"$(INTDIR)\ROIInspectorController.sbr" \
	"$(INTDIR)\ROIInspectorROI.sbr" \
	"$(INTDIR)\ROIInspectorView.sbr" \
	"$(INTDIR)\ROIPropPage.sbr" \
	"$(INTDIR)\ROIPropSheet.sbr" \
	"$(INTDIR)\ROITreeCtrl.sbr" \
	"$(INTDIR)\SelectLODsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ROIInspector.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 tglRL40d.lib d3drm.lib 3DManagerd.lib ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC" /out:"Debug/ROIInspectorRL40.exe"
LINK32_FLAGS=tglRL40d.lib d3drm.lib 3DManagerd.lib ViewManagerd.lib\
 realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib\
 animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/ROIInspectorRL40.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC"\
 /out:"$(OUTDIR)/ROIInspectorRL40.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimateDlg.obj" \
	"$(INTDIR)\AxisDlg.obj" \
	"$(INTDIR)\CostsPage.obj" \
	"$(INTDIR)\LODPropPage.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ROIDoc.obj" \
	"$(INTDIR)\ROIInspector.obj" \
	"$(INTDIR)\ROIInspector.res" \
	"$(INTDIR)\ROIInspectorController.obj" \
	"$(INTDIR)\ROIInspectorROI.obj" \
	"$(INTDIR)\ROIInspectorView.obj" \
	"$(INTDIR)\ROIPropPage.obj" \
	"$(INTDIR)\ROIPropSheet.obj" \
	"$(INTDIR)\ROITreeCtrl.obj" \
	"$(INTDIR)\SelectLODsDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ROIInspectorRL40.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ROIInspe"
# PROP BASE Intermediate_Dir "ROIInspe"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ROIInspectorRL20.exe" "$(OUTDIR)\ROIInspector.bsc"

CLEAN : 
	-@erase "$(INTDIR)\AnimateDlg.obj"
	-@erase "$(INTDIR)\AnimateDlg.sbr"
	-@erase "$(INTDIR)\AxisDlg.obj"
	-@erase "$(INTDIR)\AxisDlg.sbr"
	-@erase "$(INTDIR)\CostsPage.obj"
	-@erase "$(INTDIR)\CostsPage.sbr"
	-@erase "$(INTDIR)\LODPropPage.obj"
	-@erase "$(INTDIR)\LODPropPage.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ROIDoc.obj"
	-@erase "$(INTDIR)\ROIDoc.sbr"
	-@erase "$(INTDIR)\ROIInspector.obj"
	-@erase "$(INTDIR)\ROIInspector.pch"
	-@erase "$(INTDIR)\ROIInspector.res"
	-@erase "$(INTDIR)\ROIInspector.sbr"
	-@erase "$(INTDIR)\ROIInspectorController.obj"
	-@erase "$(INTDIR)\ROIInspectorController.sbr"
	-@erase "$(INTDIR)\ROIInspectorROI.obj"
	-@erase "$(INTDIR)\ROIInspectorROI.sbr"
	-@erase "$(INTDIR)\ROIInspectorView.obj"
	-@erase "$(INTDIR)\ROIInspectorView.sbr"
	-@erase "$(INTDIR)\ROIPropPage.obj"
	-@erase "$(INTDIR)\ROIPropPage.sbr"
	-@erase "$(INTDIR)\ROIPropSheet.obj"
	-@erase "$(INTDIR)\ROIPropSheet.sbr"
	-@erase "$(INTDIR)\ROITreeCtrl.obj"
	-@erase "$(INTDIR)\ROITreeCtrl.sbr"
	-@erase "$(INTDIR)\SelectLODsDlg.obj"
	-@erase "$(INTDIR)\SelectLODsDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\ROIInspector.bsc"
	-@erase "$(OUTDIR)\ROIInspectorRL20.exe"
	-@erase "$(OUTDIR)\ROIInspectorRL20.ilk"
	-@erase "$(OUTDIR)\ROIInspectorRL20.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ROIInspector.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ROIInspector.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ROIInspector.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AnimateDlg.sbr" \
	"$(INTDIR)\AxisDlg.sbr" \
	"$(INTDIR)\CostsPage.sbr" \
	"$(INTDIR)\LODPropPage.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ROIDoc.sbr" \
	"$(INTDIR)\ROIInspector.sbr" \
	"$(INTDIR)\ROIInspectorController.sbr" \
	"$(INTDIR)\ROIInspectorROI.sbr" \
	"$(INTDIR)\ROIInspectorView.sbr" \
	"$(INTDIR)\ROIPropPage.sbr" \
	"$(INTDIR)\ROIPropSheet.sbr" \
	"$(INTDIR)\ROITreeCtrl.sbr" \
	"$(INTDIR)\SelectLODsDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\ROIInspector.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 tglRL20d.lib rlddf.lib rlddfglu.lib rlff.lib 3DManagerd.lib ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC" /out:"Debug/ROIInspectorRL20.exe"
# ADD LINK32 tglRL20d.lib rlddf.lib rlddfglu.lib rlff.lib 3DManagerd.lib ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC" /out:"Debug/ROIInspectorRL20.exe"
LINK32_FLAGS=tglRL20d.lib rlddf.lib rlddfglu.lib rlff.lib 3DManagerd.lib\
 ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib\
 roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/ROIInspectorRL20.pdb" /debug /machine:I386\
 /nodefaultlib:"LIBCMTD" /nodefaultlib:"LIBCD" /nodefaultlib:"LIBC"\
 /out:"$(OUTDIR)/ROIInspectorRL20.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AnimateDlg.obj" \
	"$(INTDIR)\AxisDlg.obj" \
	"$(INTDIR)\CostsPage.obj" \
	"$(INTDIR)\LODPropPage.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ROIDoc.obj" \
	"$(INTDIR)\ROIInspector.obj" \
	"$(INTDIR)\ROIInspector.res" \
	"$(INTDIR)\ROIInspectorController.obj" \
	"$(INTDIR)\ROIInspectorROI.obj" \
	"$(INTDIR)\ROIInspectorView.obj" \
	"$(INTDIR)\ROIPropPage.obj" \
	"$(INTDIR)\ROIPropSheet.obj" \
	"$(INTDIR)\ROITreeCtrl.obj" \
	"$(INTDIR)\SelectLODsDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\ROIInspectorRL20.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "ROIInspector - Win32 Release"
# Name "ROIInspector - Win32 Debug RL40"
# Name "ROIInspector - Win32 Debug RL20"

!IF  "$(CFG)" == "ROIInspector - Win32 Release"

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ROIInspector - Win32 Release"

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIInspector.cpp
DEP_CPP_ROIIN=\
	".\MainFrm.h"\
	".\ROIDoc.h"\
	".\ROIInspector.h"\
	".\ROIInspectorController.h"\
	".\ROIInspectorView.h"\
	".\ROITreeCtrl.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Controller.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoView1.h"\
	{$(INCLUDE)}"\LegoViewWnd.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIInspector.obj" : $(SOURCE) $(DEP_CPP_ROIIN) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIInspector.obj" : $(SOURCE) $(DEP_CPP_ROIIN) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspector.sbr" : $(SOURCE) $(DEP_CPP_ROIIN) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIInspector.obj" : $(SOURCE) $(DEP_CPP_ROIIN) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspector.sbr" : $(SOURCE) $(DEP_CPP_ROIIN) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/ROIInspector.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ROIInspector.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ROIInspector.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ROIInspector.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/ROIInspector.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\StdAfx.sbr" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ROIInspector.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\ROIInspector.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIDoc.cpp
DEP_CPP_ROIDO=\
	".\ROIDoc.h"\
	".\ROIInspector.h"\
	".\StdAfx.h"\
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
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\Version.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIDoc.obj" : $(SOURCE) $(DEP_CPP_ROIDO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIDoc.obj" : $(SOURCE) $(DEP_CPP_ROIDO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIDoc.sbr" : $(SOURCE) $(DEP_CPP_ROIDO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIDoc.obj" : $(SOURCE) $(DEP_CPP_ROIDO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIDoc.sbr" : $(SOURCE) $(DEP_CPP_ROIDO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIInspectorView.cpp
DEP_CPP_ROIINS=\
	".\AnimateDlg.h"\
	".\AxisDlg.h"\
	".\CostsPage.h"\
	".\LODPropPage.h"\
	".\ROIDoc.h"\
	".\ROIInspector.h"\
	".\ROIInspectorController.h"\
	".\ROIInspectorROI.h"\
	".\ROIInspectorView.h"\
	".\ROIPropPage.h"\
	".\ROIPropSheet.h"\
	".\ROITreeCtrl.h"\
	".\SelectLODsDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Controller.h"\
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
	{$(INCLUDE)}"\LegoView1.h"\
	{$(INCLUDE)}"\LegoViewWnd.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDraw.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIInspectorView.obj" : $(SOURCE) $(DEP_CPP_ROIINS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIInspectorView.obj" : $(SOURCE) $(DEP_CPP_ROIINS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspectorView.sbr" : $(SOURCE) $(DEP_CPP_ROIINS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIInspectorView.obj" : $(SOURCE) $(DEP_CPP_ROIINS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspectorView.sbr" : $(SOURCE) $(DEP_CPP_ROIINS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIInspector.rc

!IF  "$(CFG)" == "ROIInspector - Win32 Release"

DEP_RSC_ROIINSP=\
	".\Res\lod.ico"\
	".\Res\lodlist.ico"\
	".\Res\parts.ico"\
	".\Res\roi.ico"\
	".\Res\ROIDoc.ico"\
	".\Res\ROIInspector.ico"\
	".\Res\ROIInspector.rc2"\
	".\Res\Toolbar.bmp"\
	

"$(INTDIR)\ROIInspector.res" : $(SOURCE) $(DEP_RSC_ROIINSP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"

DEP_RSC_ROIINSP=\
	".\Res\lod.ico"\
	".\Res\lodlist.ico"\
	".\Res\parts.ico"\
	".\Res\roi.ico"\
	".\Res\ROIDoc.ico"\
	".\Res\ROIInspector.ico"\
	".\Res\ROIInspector.rc2"\
	".\Res\Toolbar.bmp"\
	{$(INCLUDE)}"\Palette.bmp"\
	

"$(INTDIR)\ROIInspector.res" : $(SOURCE) $(DEP_RSC_ROIINSP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"

DEP_RSC_ROIINSP=\
	".\Res\lod.ico"\
	".\Res\lodlist.ico"\
	".\Res\parts.ico"\
	".\Res\roi.ico"\
	".\Res\ROIDoc.ico"\
	".\Res\ROIInspector.ico"\
	".\Res\ROIInspector.rc2"\
	".\Res\Toolbar.bmp"\
	{$(INCLUDE)}"\Palette.bmp"\
	

"$(INTDIR)\ROIInspector.res" : $(SOURCE) $(DEP_RSC_ROIINSP) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROITreeCtrl.cpp
DEP_CPP_ROITR=\
	".\ROIInspector.h"\
	".\ROITreeCtrl.h"\
	".\StdAfx.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROITreeCtrl.obj" : $(SOURCE) $(DEP_CPP_ROITR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROITreeCtrl.obj" : $(SOURCE) $(DEP_CPP_ROITR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROITreeCtrl.sbr" : $(SOURCE) $(DEP_CPP_ROITR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROITreeCtrl.obj" : $(SOURCE) $(DEP_CPP_ROITR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROITreeCtrl.sbr" : $(SOURCE) $(DEP_CPP_ROITR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIInspectorController.cpp
DEP_CPP_ROIINSPE=\
	".\ROIInspectorController.h"\
	".\ROIInspectorROI.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Controller.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIInspectorController.obj" : $(SOURCE) $(DEP_CPP_ROIINSPE)\
 "$(INTDIR)" "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIInspectorController.obj" : $(SOURCE) $(DEP_CPP_ROIINSPE)\
 "$(INTDIR)" "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspectorController.sbr" : $(SOURCE) $(DEP_CPP_ROIINSPE)\
 "$(INTDIR)" "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIInspectorController.obj" : $(SOURCE) $(DEP_CPP_ROIINSPE)\
 "$(INTDIR)" "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspectorController.sbr" : $(SOURCE) $(DEP_CPP_ROIINSPE)\
 "$(INTDIR)" "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIInspectorROI.cpp
DEP_CPP_ROIINSPEC=\
	".\ROIInspectorROI.h"\
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
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIInspectorROI.obj" : $(SOURCE) $(DEP_CPP_ROIINSPEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIInspectorROI.obj" : $(SOURCE) $(DEP_CPP_ROIINSPEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspectorROI.sbr" : $(SOURCE) $(DEP_CPP_ROIINSPEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIInspectorROI.obj" : $(SOURCE) $(DEP_CPP_ROIINSPEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIInspectorROI.sbr" : $(SOURCE) $(DEP_CPP_ROIINSPEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SelectLODsDlg.cpp
DEP_CPP_SELEC=\
	".\ROIInspector.h"\
	".\SelectLODsDlg.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\SelectLODsDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\SelectLODsDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\SelectLODsDlg.sbr" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\SelectLODsDlg.obj" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\SelectLODsDlg.sbr" : $(SOURCE) $(DEP_CPP_SELEC) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIPropPage.cpp
DEP_CPP_ROIPR=\
	".\ROIInspector.h"\
	".\ROIPropPage.h"\
	".\StdAfx.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIPropPage.obj" : $(SOURCE) $(DEP_CPP_ROIPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIPropPage.obj" : $(SOURCE) $(DEP_CPP_ROIPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIPropPage.sbr" : $(SOURCE) $(DEP_CPP_ROIPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIPropPage.obj" : $(SOURCE) $(DEP_CPP_ROIPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIPropPage.sbr" : $(SOURCE) $(DEP_CPP_ROIPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ROIPropSheet.cpp
DEP_CPP_ROIPRO=\
	".\CostsPage.h"\
	".\LODPropPage.h"\
	".\ROIInspector.h"\
	".\ROIPropPage.h"\
	".\ROIPropSheet.h"\
	".\StdAfx.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\ROIPropSheet.obj" : $(SOURCE) $(DEP_CPP_ROIPRO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\ROIPropSheet.obj" : $(SOURCE) $(DEP_CPP_ROIPRO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIPropSheet.sbr" : $(SOURCE) $(DEP_CPP_ROIPRO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\ROIPropSheet.obj" : $(SOURCE) $(DEP_CPP_ROIPRO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\ROIPropSheet.sbr" : $(SOURCE) $(DEP_CPP_ROIPRO) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LODPropPage.cpp
DEP_CPP_LODPR=\
	".\LODPropPage.h"\
	".\ROIInspector.h"\
	".\StdAfx.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\LODPropPage.obj" : $(SOURCE) $(DEP_CPP_LODPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\LODPropPage.obj" : $(SOURCE) $(DEP_CPP_LODPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\LODPropPage.sbr" : $(SOURCE) $(DEP_CPP_LODPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\LODPropPage.obj" : $(SOURCE) $(DEP_CPP_LODPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\LODPropPage.sbr" : $(SOURCE) $(DEP_CPP_LODPR) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AxisDlg.cpp
DEP_CPP_AXISD=\
	".\AxisDlg.h"\
	".\ROIInspector.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\AxisDlg.obj" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\AxisDlg.obj" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\AxisDlg.sbr" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\AxisDlg.obj" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\AxisDlg.sbr" : $(SOURCE) $(DEP_CPP_AXISD) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CostsPage.cpp
DEP_CPP_COSTS=\
	".\CostsPage.h"\
	".\ROIInspector.h"\
	".\StdAfx.h"\
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
	

!IF  "$(CFG)" == "ROIInspector - Win32 Release"


"$(INTDIR)\CostsPage.obj" : $(SOURCE) $(DEP_CPP_COSTS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"


"$(INTDIR)\CostsPage.obj" : $(SOURCE) $(DEP_CPP_COSTS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\CostsPage.sbr" : $(SOURCE) $(DEP_CPP_COSTS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"


"$(INTDIR)\CostsPage.obj" : $(SOURCE) $(DEP_CPP_COSTS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\CostsPage.sbr" : $(SOURCE) $(DEP_CPP_COSTS) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AnimateDlg.cpp

!IF  "$(CFG)" == "ROIInspector - Win32 Release"

DEP_CPP_ANIMA=\
	".\AnimateDlg.h"\
	".\ROIInspector.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

"$(INTDIR)\AnimateDlg.obj" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL40"

DEP_CPP_ANIMA=\
	".\AnimateDlg.h"\
	".\ROIInspector.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTree.h"\
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
	

"$(INTDIR)\AnimateDlg.obj" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\AnimateDlg.sbr" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ELSEIF  "$(CFG)" == "ROIInspector - Win32 Debug RL20"

DEP_CPP_ANIMA=\
	".\AnimateDlg.h"\
	".\ROIInspector.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTree.h"\
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
	

"$(INTDIR)\AnimateDlg.obj" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"

"$(INTDIR)\AnimateDlg.sbr" : $(SOURCE) $(DEP_CPP_ANIMA) "$(INTDIR)"\
 "$(INTDIR)\ROIInspector.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
