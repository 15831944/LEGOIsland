# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=LegoOmni - Win32 Debug with SmartHeap
!MESSAGE No configuration specified.  Defaulting to LegoOmni - Win32 Debug with\
 SmartHeap.
!ENDIF 

!IF "$(CFG)" != "LegoOmni - Win32 Release" && "$(CFG)" !=\
 "LegoOmni - Win32 Debug" && "$(CFG)" != "LegoOmni - Win32 Debug with SmartHeap"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "LegoOmni.mak" CFG="LegoOmni - Win32 Debug with SmartHeap"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LegoOmni - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LegoOmni - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "LegoOmni - Win32 Debug with SmartHeap" (based on\
 "Win32 (x86) Dynamic-Link Library")
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
# PROP Target_Last_Scanned "LegoOmni - Win32 Debug"
RSC=rc.exe
MTL=mktyplib.exe
CPP=cl.exe

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : "..\..\bin\LegoOmni1.dll"

CLEAN : 
	-@erase "$(INTDIR)\LActor.obj"
	-@erase "$(INTDIR)\LegoActorPresenter.obj"
	-@erase "$(INTDIR)\LegoAnimPresenter.obj"
	-@erase "$(INTDIR)\LegoBitmap.obj"
	-@erase "$(INTDIR)\LegoBuild.obj"
	-@erase "$(INTDIR)\LegoCameraController.obj"
	-@erase "$(INTDIR)\LegoCarBuildPresenter.obj"
	-@erase "$(INTDIR)\LegoEntityPresenter.obj"
	-@erase "$(INTDIR)\LegoGameState.obj"
	-@erase "$(INTDIR)\LegoGui.obj"
	-@erase "$(INTDIR)\LegoGuiBGPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiButton.obj"
	-@erase "$(INTDIR)\LegoGuiButtonPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiControl.obj"
	-@erase "$(INTDIR)\LegoGuiCtrlPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiString.obj"
	-@erase "$(INTDIR)\LegoGuiStringPresenter.obj"
	-@erase "$(INTDIR)\LegoInputManager.obj"
	-@erase "$(INTDIR)\LegoModelPresenter.obj"
	-@erase "$(INTDIR)\LegoNavController.obj"
	-@erase "$(INTDIR)\LegoOmni.obj"
	-@erase "$(INTDIR)\LegoOmni.res"
	-@erase "$(INTDIR)\LegoPalettePresenter.obj"
	-@erase "$(INTDIR)\LegoPOVController.obj"
	-@erase "$(INTDIR)\LegoSpacePresenter.obj"
	-@erase "$(INTDIR)\LegoTestTimer.obj"
	-@erase "$(INTDIR)\LegoVideoManager.obj"
	-@erase "$(INTDIR)\LegoWorldPresenter.obj"
	-@erase "$(INTDIR)\LEntity.obj"
	-@erase "$(INTDIR)\LFactory.obj"
	-@erase "$(INTDIR)\LWorld.obj"
	-@erase "$(INTDIR)\PathCtrl.obj"
	-@erase "$(INTDIR)\Paths.obj"
	-@erase "$(INTDIR)\PathStruc.obj"
	-@erase "$(INTDIR)\PPresent.obj"
	-@erase "$(OUTDIR)\LegoOmni1.map"
	-@erase "..\..\bin\LegoOmni1.dll"
	-@erase "..\..\lib\LegoOmni1.exp"
	-@erase "..\..\lib\LegoOmni1.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /YX"StdLego.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /Fp"$(INTDIR)/LegoOmni.pch" /YX"StdLego.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "\lego\LegoOmni\include" /i "\omni\include" /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LegoOmni.res" /i "\lego\LegoOmni\include" /i\
 "\omni\include" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LegoOmni.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 tglrl40.lib d3drm.lib libcmt.lib winmm.lib omni2.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib oldnames.lib /nologo /subsystem:windows /dll /map /machine:I386 /nodefaultlib /out:"..\..\bin\LegoOmni1.dll" /implib:"..\..\lib\LegoOmni1.lib"
# SUBTRACT LINK32 /pdb:none /force
LINK32_FLAGS=tglrl40.lib d3drm.lib libcmt.lib winmm.lib omni2.lib dsound.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib\
 oldnames.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)/LegoOmni1.pdb" /map:"$(INTDIR)/LegoOmni1.map" /machine:I386\
 /nodefaultlib /def:".\LegoOmni.def" /out:"..\..\bin\LegoOmni1.dll"\
 /implib:"..\..\lib\LegoOmni1.lib" 
DEF_FILE= \
	".\LegoOmni.def"
LINK32_OBJS= \
	"$(INTDIR)\LActor.obj" \
	"$(INTDIR)\LegoActorPresenter.obj" \
	"$(INTDIR)\LegoAnimPresenter.obj" \
	"$(INTDIR)\LegoBitmap.obj" \
	"$(INTDIR)\LegoBuild.obj" \
	"$(INTDIR)\LegoCameraController.obj" \
	"$(INTDIR)\LegoCarBuildPresenter.obj" \
	"$(INTDIR)\LegoEntityPresenter.obj" \
	"$(INTDIR)\LegoGameState.obj" \
	"$(INTDIR)\LegoGui.obj" \
	"$(INTDIR)\LegoGuiBGPresenter.obj" \
	"$(INTDIR)\LegoGuiButton.obj" \
	"$(INTDIR)\LegoGuiButtonPresenter.obj" \
	"$(INTDIR)\LegoGuiControl.obj" \
	"$(INTDIR)\LegoGuiCtrlPresenter.obj" \
	"$(INTDIR)\LegoGuiPresenter.obj" \
	"$(INTDIR)\LegoGuiString.obj" \
	"$(INTDIR)\LegoGuiStringPresenter.obj" \
	"$(INTDIR)\LegoInputManager.obj" \
	"$(INTDIR)\LegoModelPresenter.obj" \
	"$(INTDIR)\LegoNavController.obj" \
	"$(INTDIR)\LegoOmni.obj" \
	"$(INTDIR)\LegoOmni.res" \
	"$(INTDIR)\LegoPalettePresenter.obj" \
	"$(INTDIR)\LegoPOVController.obj" \
	"$(INTDIR)\LegoSpacePresenter.obj" \
	"$(INTDIR)\LegoTestTimer.obj" \
	"$(INTDIR)\LegoVideoManager.obj" \
	"$(INTDIR)\LegoWorldPresenter.obj" \
	"$(INTDIR)\LEntity.obj" \
	"$(INTDIR)\LFactory.obj" \
	"$(INTDIR)\LWorld.obj" \
	"$(INTDIR)\PathCtrl.obj" \
	"$(INTDIR)\Paths.obj" \
	"$(INTDIR)\PathStruc.obj" \
	"$(INTDIR)\PPresent.obj"

"..\..\bin\LegoOmni1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "..\..\bin\LegoOmni1d.dll" "$(OUTDIR)\LegoOmni.bsc"

CLEAN : 
	-@erase "$(INTDIR)\LActor.obj"
	-@erase "$(INTDIR)\LActor.sbr"
	-@erase "$(INTDIR)\LegoActorPresenter.obj"
	-@erase "$(INTDIR)\LegoActorPresenter.sbr"
	-@erase "$(INTDIR)\LegoAnimPresenter.obj"
	-@erase "$(INTDIR)\LegoAnimPresenter.sbr"
	-@erase "$(INTDIR)\LegoBitmap.obj"
	-@erase "$(INTDIR)\LegoBitmap.sbr"
	-@erase "$(INTDIR)\LegoBuild.obj"
	-@erase "$(INTDIR)\LegoBuild.sbr"
	-@erase "$(INTDIR)\LegoCameraController.obj"
	-@erase "$(INTDIR)\LegoCameraController.sbr"
	-@erase "$(INTDIR)\LegoCarBuildPresenter.obj"
	-@erase "$(INTDIR)\LegoCarBuildPresenter.sbr"
	-@erase "$(INTDIR)\LegoEntityPresenter.obj"
	-@erase "$(INTDIR)\LegoEntityPresenter.sbr"
	-@erase "$(INTDIR)\LegoGameState.obj"
	-@erase "$(INTDIR)\LegoGameState.sbr"
	-@erase "$(INTDIR)\LegoGui.obj"
	-@erase "$(INTDIR)\LegoGui.sbr"
	-@erase "$(INTDIR)\LegoGuiBGPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiBGPresenter.sbr"
	-@erase "$(INTDIR)\LegoGuiButton.obj"
	-@erase "$(INTDIR)\LegoGuiButton.sbr"
	-@erase "$(INTDIR)\LegoGuiButtonPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiButtonPresenter.sbr"
	-@erase "$(INTDIR)\LegoGuiControl.obj"
	-@erase "$(INTDIR)\LegoGuiControl.sbr"
	-@erase "$(INTDIR)\LegoGuiCtrlPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiCtrlPresenter.sbr"
	-@erase "$(INTDIR)\LegoGuiPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiPresenter.sbr"
	-@erase "$(INTDIR)\LegoGuiString.obj"
	-@erase "$(INTDIR)\LegoGuiString.sbr"
	-@erase "$(INTDIR)\LegoGuiStringPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiStringPresenter.sbr"
	-@erase "$(INTDIR)\LegoInputManager.obj"
	-@erase "$(INTDIR)\LegoInputManager.sbr"
	-@erase "$(INTDIR)\LegoModelPresenter.obj"
	-@erase "$(INTDIR)\LegoModelPresenter.sbr"
	-@erase "$(INTDIR)\LegoNavController.obj"
	-@erase "$(INTDIR)\LegoNavController.sbr"
	-@erase "$(INTDIR)\LegoOmni.obj"
	-@erase "$(INTDIR)\LegoOmni.res"
	-@erase "$(INTDIR)\LegoOmni.sbr"
	-@erase "$(INTDIR)\LegoPalettePresenter.obj"
	-@erase "$(INTDIR)\LegoPalettePresenter.sbr"
	-@erase "$(INTDIR)\LegoPOVController.obj"
	-@erase "$(INTDIR)\LegoPOVController.sbr"
	-@erase "$(INTDIR)\LegoSpacePresenter.obj"
	-@erase "$(INTDIR)\LegoSpacePresenter.sbr"
	-@erase "$(INTDIR)\LegoTestTimer.obj"
	-@erase "$(INTDIR)\LegoTestTimer.sbr"
	-@erase "$(INTDIR)\LegoVideoManager.obj"
	-@erase "$(INTDIR)\LegoVideoManager.sbr"
	-@erase "$(INTDIR)\LegoWorldPresenter.obj"
	-@erase "$(INTDIR)\LegoWorldPresenter.sbr"
	-@erase "$(INTDIR)\LEntity.obj"
	-@erase "$(INTDIR)\LEntity.sbr"
	-@erase "$(INTDIR)\LFactory.obj"
	-@erase "$(INTDIR)\LFactory.sbr"
	-@erase "$(INTDIR)\LWorld.obj"
	-@erase "$(INTDIR)\LWorld.sbr"
	-@erase "$(INTDIR)\PathCtrl.obj"
	-@erase "$(INTDIR)\PathCtrl.sbr"
	-@erase "$(INTDIR)\Paths.obj"
	-@erase "$(INTDIR)\Paths.sbr"
	-@erase "$(INTDIR)\PathStruc.obj"
	-@erase "$(INTDIR)\PathStruc.sbr"
	-@erase "$(INTDIR)\PPresent.obj"
	-@erase "$(INTDIR)\PPresent.sbr"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\LegoOmni.bsc"
	-@erase "$(OUTDIR)\LegoOmni1d.pdb"
	-@erase "..\..\bin\LegoOmni1d.dll"
	-@erase "..\..\bin\LegoOmni1d.ilk"
	-@erase "..\..\lib\LegoOmni1d.exp"
	-@erase "..\..\lib\LegoOmni1d.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MTd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /Fr /YX"StdLego.h" /c
CPP_PROJ=/nologo /MTd /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D\
 "STRICT" /Fr"$(INTDIR)/" /Fp"$(INTDIR)/LegoOmni.pch" /YX"StdLego.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "\lego\LegoOmni\include" /i "\omni\include" /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LegoOmni.res" /i "\lego\LegoOmni\include" /i\
 "\omni\include" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LegoOmni.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LActor.sbr" \
	"$(INTDIR)\LegoActorPresenter.sbr" \
	"$(INTDIR)\LegoAnimPresenter.sbr" \
	"$(INTDIR)\LegoBitmap.sbr" \
	"$(INTDIR)\LegoBuild.sbr" \
	"$(INTDIR)\LegoCameraController.sbr" \
	"$(INTDIR)\LegoCarBuildPresenter.sbr" \
	"$(INTDIR)\LegoEntityPresenter.sbr" \
	"$(INTDIR)\LegoGameState.sbr" \
	"$(INTDIR)\LegoGui.sbr" \
	"$(INTDIR)\LegoGuiBGPresenter.sbr" \
	"$(INTDIR)\LegoGuiButton.sbr" \
	"$(INTDIR)\LegoGuiButtonPresenter.sbr" \
	"$(INTDIR)\LegoGuiControl.sbr" \
	"$(INTDIR)\LegoGuiCtrlPresenter.sbr" \
	"$(INTDIR)\LegoGuiPresenter.sbr" \
	"$(INTDIR)\LegoGuiString.sbr" \
	"$(INTDIR)\LegoGuiStringPresenter.sbr" \
	"$(INTDIR)\LegoInputManager.sbr" \
	"$(INTDIR)\LegoModelPresenter.sbr" \
	"$(INTDIR)\LegoNavController.sbr" \
	"$(INTDIR)\LegoOmni.sbr" \
	"$(INTDIR)\LegoPalettePresenter.sbr" \
	"$(INTDIR)\LegoPOVController.sbr" \
	"$(INTDIR)\LegoSpacePresenter.sbr" \
	"$(INTDIR)\LegoTestTimer.sbr" \
	"$(INTDIR)\LegoVideoManager.sbr" \
	"$(INTDIR)\LegoWorldPresenter.sbr" \
	"$(INTDIR)\LEntity.sbr" \
	"$(INTDIR)\LFactory.sbr" \
	"$(INTDIR)\LWorld.sbr" \
	"$(INTDIR)\PathCtrl.sbr" \
	"$(INTDIR)\Paths.sbr" \
	"$(INTDIR)\PathStruc.sbr" \
	"$(INTDIR)\PPresent.sbr"

"$(OUTDIR)\LegoOmni.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 libcmt.lib winmm.lib omni2d.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib miscd.lib roid.lib animd.lib geomd.lib tglrl40d.lib d3drm.lib 3dmanagerd.lib realtimed.lib viewmanagerd.lib pcubed.lib oldnames.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib /out:"..\..\bin\LegoOmni1d.dll" /implib:"..\..\lib\LegoOmni1d.lib"
# SUBTRACT LINK32 /pdb:none /map /force
LINK32_FLAGS=libcmt.lib winmm.lib omni2d.lib dsound.lib kernel32.lib user32.lib\
 gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib\
 oleaut32.lib uuid.lib odbc32.lib odbccp32.lib miscd.lib roid.lib animd.lib\
 geomd.lib tglrl40d.lib d3drm.lib 3dmanagerd.lib realtimed.lib viewmanagerd.lib\
 pcubed.lib oldnames.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)/LegoOmni1d.pdb" /debug /machine:I386 /nodefaultlib\
 /def:".\LegoOmni.def" /out:"..\..\bin\LegoOmni1d.dll"\
 /implib:"..\..\lib\LegoOmni1d.lib" 
DEF_FILE= \
	".\LegoOmni.def"
LINK32_OBJS= \
	"$(INTDIR)\LActor.obj" \
	"$(INTDIR)\LegoActorPresenter.obj" \
	"$(INTDIR)\LegoAnimPresenter.obj" \
	"$(INTDIR)\LegoBitmap.obj" \
	"$(INTDIR)\LegoBuild.obj" \
	"$(INTDIR)\LegoCameraController.obj" \
	"$(INTDIR)\LegoCarBuildPresenter.obj" \
	"$(INTDIR)\LegoEntityPresenter.obj" \
	"$(INTDIR)\LegoGameState.obj" \
	"$(INTDIR)\LegoGui.obj" \
	"$(INTDIR)\LegoGuiBGPresenter.obj" \
	"$(INTDIR)\LegoGuiButton.obj" \
	"$(INTDIR)\LegoGuiButtonPresenter.obj" \
	"$(INTDIR)\LegoGuiControl.obj" \
	"$(INTDIR)\LegoGuiCtrlPresenter.obj" \
	"$(INTDIR)\LegoGuiPresenter.obj" \
	"$(INTDIR)\LegoGuiString.obj" \
	"$(INTDIR)\LegoGuiStringPresenter.obj" \
	"$(INTDIR)\LegoInputManager.obj" \
	"$(INTDIR)\LegoModelPresenter.obj" \
	"$(INTDIR)\LegoNavController.obj" \
	"$(INTDIR)\LegoOmni.obj" \
	"$(INTDIR)\LegoOmni.res" \
	"$(INTDIR)\LegoPalettePresenter.obj" \
	"$(INTDIR)\LegoPOVController.obj" \
	"$(INTDIR)\LegoSpacePresenter.obj" \
	"$(INTDIR)\LegoTestTimer.obj" \
	"$(INTDIR)\LegoVideoManager.obj" \
	"$(INTDIR)\LegoWorldPresenter.obj" \
	"$(INTDIR)\LEntity.obj" \
	"$(INTDIR)\LFactory.obj" \
	"$(INTDIR)\LWorld.obj" \
	"$(INTDIR)\PathCtrl.obj" \
	"$(INTDIR)\Paths.obj" \
	"$(INTDIR)\PathStruc.obj" \
	"$(INTDIR)\PPresent.obj"

"..\..\bin\LegoOmni1d.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LegoOmni"
# PROP BASE Intermediate_Dir "LegoOmni"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug with SmartHeap"
# PROP Intermediate_Dir "Debug with SmartHeap"
# PROP Target_Dir ""
OUTDIR=.\Debug with SmartHeap
INTDIR=.\Debug with SmartHeap

ALL : "..\..\bin\LegoOmni1dSH.dll"

CLEAN : 
	-@erase "$(INTDIR)\LActor.obj"
	-@erase "$(INTDIR)\LegoActorPresenter.obj"
	-@erase "$(INTDIR)\LegoAnimPresenter.obj"
	-@erase "$(INTDIR)\LegoBitmap.obj"
	-@erase "$(INTDIR)\LegoBuild.obj"
	-@erase "$(INTDIR)\LegoCameraController.obj"
	-@erase "$(INTDIR)\LegoCarBuildPresenter.obj"
	-@erase "$(INTDIR)\LegoEntityPresenter.obj"
	-@erase "$(INTDIR)\LegoGameState.obj"
	-@erase "$(INTDIR)\LegoGui.obj"
	-@erase "$(INTDIR)\LegoGuiBGPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiButton.obj"
	-@erase "$(INTDIR)\LegoGuiButtonPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiControl.obj"
	-@erase "$(INTDIR)\LegoGuiCtrlPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiPresenter.obj"
	-@erase "$(INTDIR)\LegoGuiString.obj"
	-@erase "$(INTDIR)\LegoGuiStringPresenter.obj"
	-@erase "$(INTDIR)\LegoInputManager.obj"
	-@erase "$(INTDIR)\LegoModelPresenter.obj"
	-@erase "$(INTDIR)\LegoNavController.obj"
	-@erase "$(INTDIR)\LegoOmni.obj"
	-@erase "$(INTDIR)\LegoOmni.res"
	-@erase "$(INTDIR)\LegoPalettePresenter.obj"
	-@erase "$(INTDIR)\LegoPOVController.obj"
	-@erase "$(INTDIR)\LegoSpacePresenter.obj"
	-@erase "$(INTDIR)\LegoTestTimer.obj"
	-@erase "$(INTDIR)\LegoVideoManager.obj"
	-@erase "$(INTDIR)\LegoWorldPresenter.obj"
	-@erase "$(INTDIR)\LEntity.obj"
	-@erase "$(INTDIR)\LFactory.obj"
	-@erase "$(INTDIR)\LWorld.obj"
	-@erase "$(INTDIR)\PathCtrl.obj"
	-@erase "$(INTDIR)\Paths.obj"
	-@erase "$(INTDIR)\PathStruc.obj"
	-@erase "$(INTDIR)\PPresent.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\LegoOmni1dSH.pdb"
	-@erase "..\..\bin\LegoOmni1dSH.dll"
	-@erase "..\..\bin\LegoOmni1dSH.ilk"
	-@erase "..\..\lib\LegoOmni1dSH.exp"
	-@erase "..\..\lib\LegoOmni1dSH.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /YX"StdLego.h" /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "STRICT" /D "USE_SMART_HEAP" /D MEM_DEBUG=1 /D DEFINE_NEW_MACRO=1 /YX"StdLego.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS"\
 /D "STRICT" /D "USE_SMART_HEAP" /D MEM_DEBUG=1 /D DEFINE_NEW_MACRO=1\
 /Fp"$(INTDIR)/LegoOmni.pch" /YX"StdLego.h" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=".\Debug with SmartHeap/"
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /i "\lego\LegoOmni\include" /i "\omni\include" /d "_DEBUG"
# ADD RSC /l 0x409 /i "\lego\LegoOmni\include" /i "\omni\include" /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/LegoOmni.res" /i "\lego\LegoOmni\include" /i\
 "\omni\include" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/LegoOmni.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 libcmt.lib winmm.lib omni2d.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib miscd.lib roid.lib animd.lib geomd.lib tglrl20d.lib rlddf.lib rlddfglu.lib rlff.lib 3dmanagerd.lib realtimed.lib viewmanagerd.lib pcubed.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib /out:"..\..\bin\LegoOmni1d.dll" /implib:"..\..\lib\LegoOmni1d.lib"
# SUBTRACT BASE LINK32 /pdb:none /map /force
# ADD LINK32 omni2dSH.lib libcmt.lib winmm.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib miscd.lib roid.lib animd.lib geomd.lib tglrl40d.lib d3drm.lib 3dmanagerd.lib realtimed.lib viewmanagerd.lib pcubed.lib oldnames.lib /nologo /subsystem:windows /dll /debug /machine:I386 /nodefaultlib /out:"..\..\bin\LegoOmni1dSH.dll" /implib:"..\..\lib\LegoOmni1dSH.lib"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=omni2dSH.lib libcmt.lib winmm.lib dsound.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib miscd.lib roid.lib\
 animd.lib geomd.lib tglrl40d.lib d3drm.lib 3dmanagerd.lib realtimed.lib\
 viewmanagerd.lib pcubed.lib oldnames.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)/LegoOmni1dSH.pdb" /debug /machine:I386\
 /nodefaultlib /def:".\LegoOmni.def" /out:"..\..\bin\LegoOmni1dSH.dll"\
 /implib:"..\..\lib\LegoOmni1dSH.lib" 
DEF_FILE= \
	".\LegoOmni.def"
LINK32_OBJS= \
	"$(INTDIR)\LActor.obj" \
	"$(INTDIR)\LegoActorPresenter.obj" \
	"$(INTDIR)\LegoAnimPresenter.obj" \
	"$(INTDIR)\LegoBitmap.obj" \
	"$(INTDIR)\LegoBuild.obj" \
	"$(INTDIR)\LegoCameraController.obj" \
	"$(INTDIR)\LegoCarBuildPresenter.obj" \
	"$(INTDIR)\LegoEntityPresenter.obj" \
	"$(INTDIR)\LegoGameState.obj" \
	"$(INTDIR)\LegoGui.obj" \
	"$(INTDIR)\LegoGuiBGPresenter.obj" \
	"$(INTDIR)\LegoGuiButton.obj" \
	"$(INTDIR)\LegoGuiButtonPresenter.obj" \
	"$(INTDIR)\LegoGuiControl.obj" \
	"$(INTDIR)\LegoGuiCtrlPresenter.obj" \
	"$(INTDIR)\LegoGuiPresenter.obj" \
	"$(INTDIR)\LegoGuiString.obj" \
	"$(INTDIR)\LegoGuiStringPresenter.obj" \
	"$(INTDIR)\LegoInputManager.obj" \
	"$(INTDIR)\LegoModelPresenter.obj" \
	"$(INTDIR)\LegoNavController.obj" \
	"$(INTDIR)\LegoOmni.obj" \
	"$(INTDIR)\LegoOmni.res" \
	"$(INTDIR)\LegoPalettePresenter.obj" \
	"$(INTDIR)\LegoPOVController.obj" \
	"$(INTDIR)\LegoSpacePresenter.obj" \
	"$(INTDIR)\LegoTestTimer.obj" \
	"$(INTDIR)\LegoVideoManager.obj" \
	"$(INTDIR)\LegoWorldPresenter.obj" \
	"$(INTDIR)\LEntity.obj" \
	"$(INTDIR)\LFactory.obj" \
	"$(INTDIR)\LWorld.obj" \
	"$(INTDIR)\PathCtrl.obj" \
	"$(INTDIR)\Paths.obj" \
	"$(INTDIR)\PathStruc.obj" \
	"$(INTDIR)\PPresent.obj"

"..\..\bin\LegoOmni1dSH.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "LegoOmni - Win32 Release"
# Name "LegoOmni - Win32 Debug"
# Name "LegoOmni - Win32 Debug with SmartHeap"

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\LegoOmni.def

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LegoOmni.rc

!IF  "$(CFG)" == "LegoOmni - Win32 Release"


"$(INTDIR)\LegoOmni.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"


"$(INTDIR)\LegoOmni.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"


"$(INTDIR)\LegoOmni.res" : $(SOURCE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Common\LFactory.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LFACT=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoCarBuildPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiPresenter.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPalettePresenter.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LFactory.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	

"$(INTDIR)\LFactory.obj" : $(SOURCE) $(DEP_CPP_LFACT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LFACT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoCarBuildPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPalettePresenter.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LFactory.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LFactory.obj" : $(SOURCE) $(DEP_CPP_LFACT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LFactory.sbr" : $(SOURCE) $(DEP_CPP_LFACT) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LFACT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoCarBuildPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPalettePresenter.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LFactory.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LFactory.obj" : $(SOURCE) $(DEP_CPP_LFACT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LWorld.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LWORL=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LWorld.obj" : $(SOURCE) $(DEP_CPP_LWORL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LWORL=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LWorld.obj" : $(SOURCE) $(DEP_CPP_LWORL) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LWorld.sbr" : $(SOURCE) $(DEP_CPP_LWORL) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LWORL=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LWorld.obj" : $(SOURCE) $(DEP_CPP_LWORL) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LEntity.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LENTI=\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LEntity.obj" : $(SOURCE) $(DEP_CPP_LENTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LENTI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LEntity.obj" : $(SOURCE) $(DEP_CPP_LENTI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LEntity.sbr" : $(SOURCE) $(DEP_CPP_LENTI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LENTI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LEntity.obj" : $(SOURCE) $(DEP_CPP_LENTI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LActor.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LACTO=\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LActor.obj" : $(SOURCE) $(DEP_CPP_LACTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LACTO=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LActor.obj" : $(SOURCE) $(DEP_CPP_LACTO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LActor.sbr" : $(SOURCE) $(DEP_CPP_LACTO) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LACTO=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LActor.obj" : $(SOURCE) $(DEP_CPP_LACTO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Main\LegoOmni.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOO=\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoContainer.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LFactory.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\Memtrace.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoOmni.obj" : $(SOURCE) $(DEP_CPP_LEGOO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOO=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoContainer.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LFactory.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\Memtrace.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoOmni.obj" : $(SOURCE) $(DEP_CPP_LEGOO) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoOmni.sbr" : $(SOURCE) $(DEP_CPP_LEGOO) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOO=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoContainer.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LFactory.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\Memtrace.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoOmni.obj" : $(SOURCE) $(DEP_CPP_LEGOO) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Paths\PathCtrl.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_PATHC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\PathCtrl.obj" : $(SOURCE) $(DEP_CPP_PATHC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_PATHC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\PathCtrl.obj" : $(SOURCE) $(DEP_CPP_PATHC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PathCtrl.sbr" : $(SOURCE) $(DEP_CPP_PATHC) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_PATHC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\PathCtrl.obj" : $(SOURCE) $(DEP_CPP_PATHC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Paths\Paths.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_PATHS=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\Paths.obj" : $(SOURCE) $(DEP_CPP_PATHS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_PATHS=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\Paths.obj" : $(SOURCE) $(DEP_CPP_PATHS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Paths.sbr" : $(SOURCE) $(DEP_CPP_PATHS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_PATHS=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\Paths.obj" : $(SOURCE) $(DEP_CPP_PATHS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Paths\PathStruc.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_PATHST=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\PathStruc.obj" : $(SOURCE) $(DEP_CPP_PATHST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_PATHST=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\PathStruc.obj" : $(SOURCE) $(DEP_CPP_PATHST) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PathStruc.sbr" : $(SOURCE) $(DEP_CPP_PATHST) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_PATHST=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\PathStruc.obj" : $(SOURCE) $(DEP_CPP_PATHST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Paths\PPresent.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_PPRES=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\PPresent.obj" : $(SOURCE) $(DEP_CPP_PPRES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_PPRES=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\PPresent.obj" : $(SOURCE) $(DEP_CPP_PPRES) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\PPresent.sbr" : $(SOURCE) $(DEP_CPP_PPRES) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_PPRES=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\Ppresent.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\PPresent.obj" : $(SOURCE) $(DEP_CPP_PPRES) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LegoActorPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOA=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoActorPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoActorPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoActorPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoActorPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOG=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOG=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxDSBuffer.h"\
	"..\..\..\..\Omni\Include\MxDSMedia.h"\
	"..\..\..\..\Omni\Include\MxDSSource.h"\
	"..\..\..\..\Omni\Include\MxSemaphore.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\..\Omni\Include\MxStreamChunk.h"\
	"..\..\..\..\Omni\Include\MxStreamController.h"\
	"..\..\..\..\Omni\Include\MxStreamProvider.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOG) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOG) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOG=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxDSBuffer.h"\
	"..\..\..\..\Omni\Include\MxDSMedia.h"\
	"..\..\..\..\Omni\Include\MxDSSource.h"\
	"..\..\..\..\Omni\Include\MxSemaphore.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\..\Omni\Include\MxStreamChunk.h"\
	"..\..\..\..\Omni\Include\MxStreamController.h"\
	"..\..\..\..\Omni\Include\MxStreamProvider.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOG) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiButton.cpp
DEP_CPP_LEGOGU=\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiButtonPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	

!IF  "$(CFG)" == "LegoOmni - Win32 Release"


"$(INTDIR)\LegoGuiButton.obj" : $(SOURCE) $(DEP_CPP_LEGOGU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiButton.obj" : $(SOURCE) $(DEP_CPP_LEGOGU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiButton.sbr" : $(SOURCE) $(DEP_CPP_LEGOGU) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"


"$(INTDIR)\LegoGuiButton.obj" : $(SOURCE) $(DEP_CPP_LEGOGU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiButtonPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiButtonPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiButtonPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUI)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiButtonPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiButtonPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUI)\
 "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiButtonPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUI)\
 "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiButtonPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiButtonPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUI)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiControl.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUIC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxDSBuffer.h"\
	"..\..\..\..\Omni\Include\MxDSMedia.h"\
	"..\..\..\..\Omni\Include\MxDSSource.h"\
	"..\..\..\..\Omni\Include\MxSemaphore.h"\
	"..\..\..\..\Omni\Include\MxStreamChunk.h"\
	"..\..\..\..\Omni\Include\MxStreamController.h"\
	"..\..\..\..\Omni\Include\MxStreamProvider.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiControl.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUIC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxDSBuffer.h"\
	"..\..\..\..\Omni\Include\MxDSMedia.h"\
	"..\..\..\..\Omni\Include\MxDSSource.h"\
	"..\..\..\..\Omni\Include\MxSemaphore.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\..\Omni\Include\MxStreamChunk.h"\
	"..\..\..\..\Omni\Include\MxStreamController.h"\
	"..\..\..\..\Omni\Include\MxStreamProvider.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiControl.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiControl.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUIC) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUIC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxDSBuffer.h"\
	"..\..\..\..\Omni\Include\MxDSMedia.h"\
	"..\..\..\..\Omni\Include\MxDSSource.h"\
	"..\..\..\..\Omni\Include\MxSemaphore.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\..\Omni\Include\MxStreamChunk.h"\
	"..\..\..\..\Omni\Include\MxStreamController.h"\
	"..\..\..\..\Omni\Include\MxStreamProvider.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiControl.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiCtrlPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUICT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiCtrlPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUICT)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUICT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiCtrlPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUICT)\
 "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiCtrlPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUICT)\
 "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUICT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiCtrlPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUICT)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGui.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUI_=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

"$(INTDIR)\LegoGui.obj" : $(SOURCE) $(DEP_CPP_LEGOGUI_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUI_=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGui.obj" : $(SOURCE) $(DEP_CPP_LEGOGUI_) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGui.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUI_) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUI_=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiButton.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGui.obj" : $(SOURCE) $(DEP_CPP_LEGOGUI_) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Video\LegoBitmap.cpp
DEP_CPP_LEGOB=\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\std.h"\
	

!IF  "$(CFG)" == "LegoOmni - Win32 Release"


"$(INTDIR)\LegoBitmap.obj" : $(SOURCE) $(DEP_CPP_LEGOB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoBitmap.obj" : $(SOURCE) $(DEP_CPP_LEGOB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoBitmap.sbr" : $(SOURCE) $(DEP_CPP_LEGOB) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"


"$(INTDIR)\LegoBitmap.obj" : $(SOURCE) $(DEP_CPP_LEGOB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Video\LegoVideoManager.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOV=\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTestTimer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoVideoManager.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOV=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTestTimer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoVideoManager.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoVideoManager.sbr" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOV=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTestTimer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoVideoManager.obj" : $(SOURCE) $(DEP_CPP_LEGOV) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Input\LegoInputManager.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOI=\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

"$(INTDIR)\LegoInputManager.obj" : $(SOURCE) $(DEP_CPP_LEGOI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoInputManager.obj" : $(SOURCE) $(DEP_CPP_LEGOI) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoInputManager.sbr" : $(SOURCE) $(DEP_CPP_LEGOI) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOI=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoInputManager.obj" : $(SOURCE) $(DEP_CPP_LEGOI) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Video\LegoModelPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOM=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoContainer.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\Memtrace.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\Version.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoModelPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOM=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoContainer.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\Memtrace.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\Version.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoModelPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOM) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoModelPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOM) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOM=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoActorPresenter.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoContainer.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoModelPresenter.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\Memtrace.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\Version.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoModelPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOM) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiStringPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUIS=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoGuiStringPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiStringPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIS)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUIS=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoGuiStringPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiStringPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIS)\
 "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiStringPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUIS)\
 "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUIS=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoGuiStringPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiStringPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIS)\
 "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiString.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUIST=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoGuiStringPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiString.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUIST=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoGuiStringPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiString.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIST) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiString.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUIST) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUIST=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoGuiCtrlPresenter.h"\
	{$(INCLUDE)}"\LegoGuiString.h"\
	{$(INCLUDE)}"\LegoGuiStringPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiString.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIST) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Gui\LegoGuiBGPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGUIB=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiBGPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGUIB=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGuiBGPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIB) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGuiBGPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOGUIB) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGUIB=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBitmap.h"\
	{$(INCLUDE)}"\LegoGui.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiBGPresenter.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGuiBGPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOGUIB) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LegoPOVController.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOP=\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoPOVController.obj" : $(SOURCE) $(DEP_CPP_LEGOP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOP=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoPOVController.obj" : $(SOURCE) $(DEP_CPP_LEGOP) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoPOVController.sbr" : $(SOURCE) $(DEP_CPP_LEGOP) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOP=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoPOVController.obj" : $(SOURCE) $(DEP_CPP_LEGOP) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LegoCameraController.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOC=\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoCameraController.obj" : $(SOURCE) $(DEP_CPP_LEGOC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoCameraController.obj" : $(SOURCE) $(DEP_CPP_LEGOC) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoCameraController.sbr" : $(SOURCE) $(DEP_CPP_LEGOC) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOC=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoCameraController.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPOVController.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoCameraController.obj" : $(SOURCE) $(DEP_CPP_LEGOC) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Video\LegoAnimPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOAN=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoAnimPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOAN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOAN=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoAnimPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOAN) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoAnimPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOAN) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOAN=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoAnimPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoAnimPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOAN) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Video\LegoPalettePresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOPA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPalettePresenter.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoPalettePresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOPA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPalettePresenter.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoPalettePresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOPA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoPalettePresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOPA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOPA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoPalettePresenter.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoPalettePresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOPA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LegoWorldPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOW=\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoWorldPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOW) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOW=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoWorldPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOW) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoWorldPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOW) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOW=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoWorldPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOW) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Entity\LegoEntityPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOE=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

"$(INTDIR)\LegoEntityPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOE=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoEntityPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOE) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoEntityPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOE) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOE=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoEntityPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOE) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Paths\LegoSpacePresenter.cpp
DEP_CPP_LEGOS=\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LActor.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSpacePresenter.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRawData.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\PathCtrl.h"\
	{$(INCLUDE)}"\Paths.h"\
	{$(INCLUDE)}"\PathStruc.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "LegoOmni - Win32 Release"


"$(INTDIR)\LegoSpacePresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoSpacePresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOS) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoSpacePresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOS) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"


"$(INTDIR)\LegoSpacePresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOS) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Common\LegoTestTimer.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTestTimer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoTestTimer.obj" : $(SOURCE) $(DEP_CPP_LEGOT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTestTimer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoTestTimer.obj" : $(SOURCE) $(DEP_CPP_LEGOT) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoTestTimer.sbr" : $(SOURCE) $(DEP_CPP_LEGOT) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOT=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTestTimer.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoTestTimer.obj" : $(SOURCE) $(DEP_CPP_LEGOT) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Common\LegoGameState.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOGA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGameState.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGameState.obj" : $(SOURCE) $(DEP_CPP_LEGOGA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOGA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGameState.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoGameState.obj" : $(SOURCE) $(DEP_CPP_LEGOGA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoGameState.sbr" : $(SOURCE) $(DEP_CPP_LEGOGA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOGA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoGameState.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoGameState.obj" : $(SOURCE) $(DEP_CPP_LEGOGA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\legoOmni\Src\Entity\LegoNavController.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGON=\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoNavController.obj" : $(SOURCE) $(DEP_CPP_LEGON) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGON=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoNavController.obj" : $(SOURCE) $(DEP_CPP_LEGON) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoNavController.sbr" : $(SOURCE) $(DEP_CPP_LEGON) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGON=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\3DManager\LegoView1.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoNavController.obj" : $(SOURCE) $(DEP_CPP_LEGON) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Build\LegoBuild.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOBU=\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBuild.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoBuild.obj" : $(SOURCE) $(DEP_CPP_LEGOBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOBU=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBuild.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoBuild.obj" : $(SOURCE) $(DEP_CPP_LEGOBU) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoBuild.sbr" : $(SOURCE) $(DEP_CPP_LEGOBU) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOBU=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBuild.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoBuild.obj" : $(SOURCE) $(DEP_CPP_LEGOBU) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\Lego\LegoOmni\Src\Build\LegoCarBuildPresenter.cpp

!IF  "$(CFG)" == "LegoOmni - Win32 Release"

DEP_CPP_LEGOCA=\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBuild.h"\
	{$(INCLUDE)}"\LegoCarBuildPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoCarBuildPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOCA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug"

DEP_CPP_LEGOCA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBuild.h"\
	{$(INCLUDE)}"\LegoCarBuildPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\LegoCarBuildPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOCA) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\LegoCarBuildPresenter.sbr" : $(SOURCE) $(DEP_CPP_LEGOCA) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "LegoOmni - Win32 Debug with SmartHeap"

DEP_CPP_LEGOCA=\
	"..\..\..\..\Omni\Include\MxActionRequest.h"\
	"..\..\..\..\Omni\Include\MxSI.h"\
	"..\..\..\Sources\Geom\LegoVector.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoBuild.h"\
	{$(INCLUDE)}"\LegoCarBuildPresenter.h"\
	{$(INCLUDE)}"\LegoEntityPresenter.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoWorldPresenter.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxAtom.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\StdLego.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\LegoCarBuildPresenter.obj" : $(SOURCE) $(DEP_CPP_LEGOCA) "$(INTDIR)"
   $(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
