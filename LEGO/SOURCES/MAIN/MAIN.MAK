# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Main - Win32 Debug with SmartHeap
!MESSAGE No configuration specified.  Defaulting to Main - Win32 Debug with\
 SmartHeap.
!ENDIF 

!IF "$(CFG)" != "Main - Win32 Release" && "$(CFG)" != "Main - Win32 Debug" &&\
 "$(CFG)" != "Main - Win32 Debug with SmartHeap"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Main.mak" CFG="Main - Win32 Debug with SmartHeap"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Main - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Main - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "Main - Win32 Debug with SmartHeap" (based on\
 "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Main - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Main - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_Re"
# PROP BASE Intermediate_Dir "Win32_Re"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win3Release"
# PROP Intermediate_Dir "Win3Release"
OUTDIR=.\Win3Release
INTDIR=.\Win3Release

ALL : "..\..\bin\Main.exe" "$(OUTDIR)\Main.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\MAIN.res"
	-@erase "$(INTDIR)\Main.sbr"
	-@erase "$(INTDIR)\NavDlg.obj"
	-@erase "$(INTDIR)\NavDlg.sbr"
	-@erase "$(INTDIR)\RealismDlg.obj"
	-@erase "$(INTDIR)\RealismDlg.sbr"
	-@erase "$(INTDIR)\RVWeightsDlg.obj"
	-@erase "$(INTDIR)\RVWeightsDlg.sbr"
	-@erase "$(INTDIR)\TimeAverage.obj"
	-@erase "$(INTDIR)\TimeAverage.sbr"
	-@erase "$(OUTDIR)\Main.bsc"
	-@erase "..\..\bin\Main.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Main.pch" /YX\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Win3Release/
CPP_SBRS=.\Win3Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MAIN.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Main.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Main.sbr" \
	"$(INTDIR)\NavDlg.sbr" \
	"$(INTDIR)\RealismDlg.sbr" \
	"$(INTDIR)\RVWeightsDlg.sbr" \
	"$(INTDIR)\TimeAverage.sbr"

"$(OUTDIR)\Main.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib msvcrt.lib mfc30.lib OLDNAMES.lib LegoOmni1.lib realtime.lib pcube.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib /out:"..\..\bin\Main.exe"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=winmm.lib msvcrt.lib mfc30.lib OLDNAMES.lib LegoOmni1.lib\
 realtime.lib pcube.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Main.pdb" /machine:I386 /nodefaultlib /out:"..\..\bin\Main.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\MAIN.res" \
	"$(INTDIR)\NavDlg.obj" \
	"$(INTDIR)\RealismDlg.obj" \
	"$(INTDIR)\RVWeightsDlg.obj" \
	"$(INTDIR)\TimeAverage.obj"

"..\..\bin\Main.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Main - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_De"
# PROP BASE Intermediate_Dir "Win32_De"
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : ".\Main.exe" "$(OUTDIR)\Main.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\MAIN.res"
	-@erase "$(INTDIR)\Main.sbr"
	-@erase "$(INTDIR)\NavDlg.obj"
	-@erase "$(INTDIR)\NavDlg.sbr"
	-@erase "$(INTDIR)\RealismDlg.obj"
	-@erase "$(INTDIR)\RealismDlg.sbr"
	-@erase "$(INTDIR)\RVWeightsDlg.obj"
	-@erase "$(INTDIR)\RVWeightsDlg.sbr"
	-@erase "$(INTDIR)\TimeAverage.obj"
	-@erase "$(INTDIR)\TimeAverage.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Main.bsc"
	-@erase "$(OUTDIR)\Main.pdb"
	-@erase ".\Main.exe"
	-@erase ".\Main.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "_MBCS" /FR /YX"StdMain.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "STRICT" /D "_MBCS" /FR"$(INTDIR)/" /Fp"$(INTDIR)/Main.pch" /YX"StdMain.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MAIN.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Main.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Main.sbr" \
	"$(INTDIR)\NavDlg.sbr" \
	"$(INTDIR)\RealismDlg.sbr" \
	"$(INTDIR)\RVWeightsDlg.sbr" \
	"$(INTDIR)\TimeAverage.sbr"

"$(OUTDIR)\Main.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 LegoOmni1d.lib realtimed.lib pcubed.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Main.exe"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=LegoOmni1d.lib realtimed.lib pcubed.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/Main.pdb" /debug /machine:I386 /out:"Main.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\MAIN.res" \
	"$(INTDIR)\NavDlg.obj" \
	"$(INTDIR)\RealismDlg.obj" \
	"$(INTDIR)\RVWeightsDlg.obj" \
	"$(INTDIR)\TimeAverage.obj"

".\Main.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Main___W"
# PROP BASE Intermediate_Dir "Main___W"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug with SmartHeap"
# PROP Intermediate_Dir "Debug with SmartHeap"
# PROP Target_Dir ""
OUTDIR=.\Debug with SmartHeap
INTDIR=.\Debug with SmartHeap

ALL : ".\MainSH.exe" "$(OUTDIR)\MainSH.bsc"

CLEAN : 
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\MAIN.res"
	-@erase "$(INTDIR)\Main.sbr"
	-@erase "$(INTDIR)\NavDlg.obj"
	-@erase "$(INTDIR)\NavDlg.sbr"
	-@erase "$(INTDIR)\RealismDlg.obj"
	-@erase "$(INTDIR)\RealismDlg.sbr"
	-@erase "$(INTDIR)\RVWeightsDlg.obj"
	-@erase "$(INTDIR)\RVWeightsDlg.sbr"
	-@erase "$(INTDIR)\TimeAverage.obj"
	-@erase "$(INTDIR)\TimeAverage.sbr"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MainSH.bsc"
	-@erase "$(OUTDIR)\MainSH.pdb"
	-@erase ".\MainSH.exe"
	-@erase ".\MainSH.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "_AFXDLL" /D "_MBCS" /FR /YX"StdLego.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "_AFXDLL" /D "_MBCS" /D "USE_SMART_HEAP" /D MEM_DEBUG=1 /D DEFINE_NEW_MACRO=1 /FR /YX"StdLego.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "STRICT" /D "_AFXDLL" /D "_MBCS" /D "USE_SMART_HEAP" /D MEM_DEBUG=1 /D\
 DEFINE_NEW_MACRO=1 /FR"$(INTDIR)/" /Fp"$(INTDIR)/Main.pch" /YX"StdLego.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=".\Debug with SmartHeap/"
CPP_SBRS=".\Debug with SmartHeap/"
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MAIN.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"Debug with SmartHeap/MainSH.bsc"
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MainSH.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Main.sbr" \
	"$(INTDIR)\NavDlg.sbr" \
	"$(INTDIR)\RealismDlg.sbr" \
	"$(INTDIR)\RVWeightsDlg.sbr" \
	"$(INTDIR)\TimeAverage.sbr"

"$(OUTDIR)\MainSH.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 LegoOmni1d.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Main.exe"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 LegoOmni1dSH.lib realtimed.lib pcubed.lib /nologo /subsystem:windows /debug /machine:I386 /out:"MainSH.exe"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=LegoOmni1dSH.lib realtimed.lib pcubed.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/MainSH.pdb" /debug\
 /machine:I386 /out:"MainSH.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\MAIN.res" \
	"$(INTDIR)\NavDlg.obj" \
	"$(INTDIR)\RealismDlg.obj" \
	"$(INTDIR)\RVWeightsDlg.obj" \
	"$(INTDIR)\TimeAverage.obj"

".\MainSH.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Main - Win32 Release"
# Name "Main - Win32 Debug"
# Name "Main - Win32 Debug with SmartHeap"

!IF  "$(CFG)" == "Main - Win32 Release"

!ELSEIF  "$(CFG)" == "Main - Win32 Debug"

!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\MAIN.RC
DEP_RSC_MAIN_=\
	".\ICON1.ICO"\
	

!IF  "$(CFG)" == "Main - Win32 Release"


"$(INTDIR)\MAIN.res" : $(SOURCE) $(DEP_RSC_MAIN_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Main - Win32 Debug"


"$(INTDIR)\MAIN.res" : $(SOURCE) $(DEP_RSC_MAIN_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"


"$(INTDIR)\MAIN.res" : $(SOURCE) $(DEP_RSC_MAIN_) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Main.cpp

!IF  "$(CFG)" == "Main - Win32 Release"

DEP_CPP_MAIN_C=\
	"..\3DManager\LegoView1.h"\
	".\Main.h"\
	".\NavDlg.h"\
	".\RealismDlg.h"\
	".\RVWeightsDlg.h"\
	".\StdMain.h"\
	".\TimeAverage.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoGameState.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	

"$(INTDIR)\Main.obj" : $(SOURCE) $(DEP_CPP_MAIN_C) "$(INTDIR)"

"$(INTDIR)\Main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug"

DEP_CPP_MAIN_C=\
	"..\..\..\Omni\Include\MxAtom.h"\
	"..\3DManager\LegoView1.h"\
	".\Main.h"\
	".\NavDlg.h"\
	".\RealismDlg.h"\
	".\RVWeightsDlg.h"\
	".\StdMain.h"\
	".\TimeAverage.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoGameState.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\Main.obj" : $(SOURCE) $(DEP_CPP_MAIN_C) "$(INTDIR)"

"$(INTDIR)\Main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_C) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"

DEP_CPP_MAIN_C=\
	"..\..\..\Omni\Include\MxAtom.h"\
	"..\3DManager\LegoView1.h"\
	".\Main.h"\
	".\NavDlg.h"\
	".\RealismDlg.h"\
	".\RVWeightsDlg.h"\
	".\StdMain.h"\
	".\TimeAverage.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\Lego3DManager.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoGameState.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LegoVideoManager.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\Main.obj" : $(SOURCE) $(DEP_CPP_MAIN_C) "$(INTDIR)"

"$(INTDIR)\Main.sbr" : $(SOURCE) $(DEP_CPP_MAIN_C) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RVWeightsDlg.cpp
DEP_CPP_RVWEI=\
	"..\..\..\Omni\Include\MxAtom.h"\
	".\RVWeightsDlg.h"\
	".\StdMain.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "Main - Win32 Release"


"$(INTDIR)\RVWeightsDlg.obj" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"

"$(INTDIR)\RVWeightsDlg.sbr" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug"


"$(INTDIR)\RVWeightsDlg.obj" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"

"$(INTDIR)\RVWeightsDlg.sbr" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"


"$(INTDIR)\RVWeightsDlg.obj" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"

"$(INTDIR)\RVWeightsDlg.sbr" : $(SOURCE) $(DEP_CPP_RVWEI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RealismDlg.cpp
DEP_CPP_REALI=\
	"..\..\..\Omni\Include\MxAtom.h"\
	".\RealismDlg.h"\
	".\StdMain.h"\
	".\TimeAverage.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStopWatch.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "Main - Win32 Release"


"$(INTDIR)\RealismDlg.obj" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"

"$(INTDIR)\RealismDlg.sbr" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug"


"$(INTDIR)\RealismDlg.obj" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"

"$(INTDIR)\RealismDlg.sbr" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"


"$(INTDIR)\RealismDlg.obj" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"

"$(INTDIR)\RealismDlg.sbr" : $(SOURCE) $(DEP_CPP_REALI) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\TimeAverage.cpp
DEP_CPP_TIMEA=\
	"..\..\..\Omni\Include\MxAtom.h"\
	".\StdMain.h"\
	".\TimeAverage.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\LegoGuiBase.h"\
	{$(INCLUDE)}"\LegoGuiControl.h"\
	{$(INCLUDE)}"\LegoInputManager.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNotify.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "Main - Win32 Release"


"$(INTDIR)\TimeAverage.obj" : $(SOURCE) $(DEP_CPP_TIMEA) "$(INTDIR)"

"$(INTDIR)\TimeAverage.sbr" : $(SOURCE) $(DEP_CPP_TIMEA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug"


"$(INTDIR)\TimeAverage.obj" : $(SOURCE) $(DEP_CPP_TIMEA) "$(INTDIR)"

"$(INTDIR)\TimeAverage.sbr" : $(SOURCE) $(DEP_CPP_TIMEA) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"


"$(INTDIR)\TimeAverage.obj" : $(SOURCE) $(DEP_CPP_TIMEA) "$(INTDIR)"

"$(INTDIR)\TimeAverage.sbr" : $(SOURCE) $(DEP_CPP_TIMEA) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\NavDlg.cpp

!IF  "$(CFG)" == "Main - Win32 Release"

DEP_CPP_NAVDL=\
	"..\..\..\Omni\Include\MxAtom.h"\
	".\NavDlg.h"\
	".\StdMain.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
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
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\NavDlg.obj" : $(SOURCE) $(DEP_CPP_NAVDL) "$(INTDIR)"

"$(INTDIR)\NavDlg.sbr" : $(SOURCE) $(DEP_CPP_NAVDL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug"

DEP_CPP_NAVDL=\
	"..\..\..\Omni\Include\MxAtom.h"\
	".\NavDlg.h"\
	".\StdMain.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\NavDlg.obj" : $(SOURCE) $(DEP_CPP_NAVDL) "$(INTDIR)"

"$(INTDIR)\NavDlg.sbr" : $(SOURCE) $(DEP_CPP_NAVDL) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Main - Win32 Debug with SmartHeap"

DEP_CPP_NAVDL=\
	"..\..\..\Omni\Include\MxAtom.h"\
	".\NavDlg.h"\
	".\StdMain.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\dsound.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoNavController.h"\
	{$(INCLUDE)}"\LegoOmni.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LEntity.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\LWorld.h"\
	{$(INCLUDE)}"\MxActionRequest.h"\
	{$(INCLUDE)}"\MxAnx.h"\
	{$(INCLUDE)}"\MxAudioManager.h"\
	{$(INCLUDE)}"\MxAudioPresenter.h"\
	{$(INCLUDE)}"\MxAutoLock.h"\
	{$(INCLUDE)}"\MxBitmap.h"\
	{$(INCLUDE)}"\MxBitmapMacros.h"\
	{$(INCLUDE)}"\MxCollection.h"\
	{$(INCLUDE)}"\MxCore.h"\
	{$(INCLUDE)}"\MxCriticalSection.h"\
	{$(INCLUDE)}"\MxDebug.h"\
	{$(INCLUDE)}"\MxDequeue.h"\
	{$(INCLUDE)}"\MxDisplaySurface.h"\
	{$(INCLUDE)}"\MxDSAction.h"\
	{$(INCLUDE)}"\MxDSBuffer.h"\
	{$(INCLUDE)}"\MxDSChunk.h"\
	{$(INCLUDE)}"\MxDSChunkSource.h"\
	{$(INCLUDE)}"\MxDSFile.h"\
	{$(INCLUDE)}"\MxDSMarker.h"\
	{$(INCLUDE)}"\MxDSMedia.h"\
	{$(INCLUDE)}"\MxDSObject.h"\
	{$(INCLUDE)}"\MxDSSource.h"\
	{$(INCLUDE)}"\MxDSSubscriber.h"\
	{$(INCLUDE)}"\MxDSTypes.h"\
	{$(INCLUDE)}"\MxEntity.h"\
	{$(INCLUDE)}"\MxEvent.h"\
	{$(INCLUDE)}"\MxEventManager.h"\
	{$(INCLUDE)}"\MxEventPresenter.h"\
	{$(INCLUDE)}"\MxFlc.h"\
	{$(INCLUDE)}"\MxGeometry.h"\
	{$(INCLUDE)}"\MxGeometry3D.h"\
	{$(INCLUDE)}"\MxHashTable.h"\
	{$(INCLUDE)}"\MxIO.h"\
	{$(INCLUDE)}"\MxList.h"\
	{$(INCLUDE)}"\MxMain.h"\
	{$(INCLUDE)}"\MxMatrix.h"\
	{$(INCLUDE)}"\MxMIDI.h"\
	{$(INCLUDE)}"\MxMusicManager.h"\
	{$(INCLUDE)}"\MxNotificationManager.h"\
	{$(INCLUDE)}"\MxObjectFactory.h"\
	{$(INCLUDE)}"\MxOmni.h"\
	{$(INCLUDE)}"\MxPalette.h"\
	{$(INCLUDE)}"\MxPresentationManager.h"\
	{$(INCLUDE)}"\MxPresenter.h"\
	{$(INCLUDE)}"\MxPriority.h"\
	{$(INCLUDE)}"\MxQueue.h"\
	{$(INCLUDE)}"\MxRegion.h"\
	{$(INCLUDE)}"\MxSemaphore.h"\
	{$(INCLUDE)}"\MxSmk.h"\
	{$(INCLUDE)}"\MxSoundManager.h"\
	{$(INCLUDE)}"\MxStack.h"\
	{$(INCLUDE)}"\MxStd.h"\
	{$(INCLUDE)}"\MxSTLWrap.h"\
	{$(INCLUDE)}"\MxStreamChunk.h"\
	{$(INCLUDE)}"\MxStreamController.h"\
	{$(INCLUDE)}"\MxStreamer.h"\
	{$(INCLUDE)}"\MxStreamProvider.h"\
	{$(INCLUDE)}"\MxString.h"\
	{$(INCLUDE)}"\MxSymbol.h"\
	{$(INCLUDE)}"\MxThread.h"\
	{$(INCLUDE)}"\MxTickleManager.h"\
	{$(INCLUDE)}"\MxTimer.h"\
	{$(INCLUDE)}"\MxTypes.h"\
	{$(INCLUDE)}"\MxUtilities.h"\
	{$(INCLUDE)}"\MxVariableTable.h"\
	{$(INCLUDE)}"\MxVector.h"\
	{$(INCLUDE)}"\MxVersion.h"\
	{$(INCLUDE)}"\MxVideoManager.h"\
	{$(INCLUDE)}"\MxVideoPresenter.h"\
	{$(INCLUDE)}"\MxWeaver.h"\
	{$(INCLUDE)}"\Rad.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\Smack.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\NavDlg.obj" : $(SOURCE) $(DEP_CPP_NAVDL) "$(INTDIR)"

"$(INTDIR)\NavDlg.sbr" : $(SOURCE) $(DEP_CPP_NAVDL) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
