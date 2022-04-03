# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=GuiDemo - Win32 Release
!MESSAGE No configuration specified.  Defaulting to GuiDemo - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "GuiDemo - Win32 Release" && "$(CFG)" !=\
 "GuiDemo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "GuiDemo.mak" CFG="GuiDemo - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GuiDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "GuiDemo - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "GuiDemo - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "GuiDemo - Win32 Release"

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

ALL : "$(OUTDIR)\GuiDemor.exe" ".\Win3Release\GuiDemo.bsc"

CLEAN : 
	-@erase ".\Win3Release\GuiDemo.bsc"
	-@erase ".\Win3Release\GuiDemo.sbr"
	-@erase ".\Win3Release\idler.sbr"
	-@erase "..\..\bin\GuiDemor.exe"
	-@erase ".\Win3Release\GuiDemo.obj"
	-@erase ".\Win3Release\idler.obj"
	-@erase ".\Win3Release\GuiDemo.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include" /I "preempt" /I "\Omni\Include" /I "\Omni\include\preempt" /I "\Omni\include\dibsect" /I "\Omni\include\dsound" /I "\Omni\include\winmm" /I "\Omni\include\gdi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /YX"LegoOmni.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\include" /I "preempt" /I\
 "\Omni\Include" /I "\Omni\include\preempt" /I "\Omni\include\dibsect" /I\
 "\Omni\include\dsound" /I "\Omni\include\winmm" /I "\Omni\include\gdi" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)/"\
 /Fp"$(INTDIR)/GuiDemo.pch" /YX"LegoOmni.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Win3Release/
CPP_SBRS=.\Win3Release/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GuiDemo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GuiDemo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/GuiDemo.sbr" \
	"$(INTDIR)/idler.sbr"

".\Win3Release\GuiDemo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\lib\LegoOmni1r.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\bin\GuiDemor.exe"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=..\..\lib\LegoOmni1r.lib /nologo /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)/GuiDemor.pdb" /machine:I386\
 /out:"..\..\bin\GuiDemor.exe" 
LINK32_OBJS= \
	"$(INTDIR)/GuiDemo.obj" \
	"$(INTDIR)/idler.obj" \
	"$(INTDIR)/GuiDemo.res"

"$(OUTDIR)\GuiDemor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "GuiDemo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_De"
# PROP BASE Intermediate_Dir "Win32_De"
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : "$(OUTDIR)\GuiDemod.exe" ".\WinDebug\GuiDemo.bsc"

CLEAN : 
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\GuiDemo.bsc"
	-@erase ".\WinDebug\GuiDemo.sbr"
	-@erase ".\WinDebug\idler.sbr"
	-@erase "..\..\bin\GuiDemod.exe"
	-@erase ".\WinDebug\idler.obj"
	-@erase ".\WinDebug\GuiDemo.obj"
	-@erase ".\WinDebug\GuiDemo.res"
	-@erase "..\..\bin\GuiDemod.ilk"
	-@erase ".\WinDebug\GuiDemod.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /I "preempt" /I "\Omni\Include" /I "\Omni\include\preempt" /I "\Omni\include\dibsect" /I "\Omni\include\dsound" /I "\Omni\include\winmm" /I "\Omni\include\gdi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "_AFXDLL" /D "_MBCS" /FR /YX"LegoOmni.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\include" /I "preempt" /I\
 "\Omni\Include" /I "\Omni\include\preempt" /I "\Omni\include\dibsect" /I\
 "\Omni\include\dsound" /I "\Omni\include\winmm" /I "\Omni\include\gdi" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "STRICT" /D "_AFXDLL" /D "_MBCS"\
 /FR"$(INTDIR)/" /Fp"$(INTDIR)/GuiDemo.pch" /YX"LegoOmni.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/GuiDemo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/GuiDemo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/GuiDemo.sbr" \
	"$(INTDIR)/idler.sbr"

".\WinDebug\GuiDemo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ..\..\lib\LegoOmni1d.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\GuiDemod.exe"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
LINK32_FLAGS=..\..\lib\LegoOmni1d.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/GuiDemod.pdb" /debug /machine:I386\
 /out:"..\..\bin\GuiDemod.exe" 
LINK32_OBJS= \
	"$(INTDIR)/idler.obj" \
	"$(INTDIR)/GuiDemo.obj" \
	"$(INTDIR)/GuiDemo.res"

"$(OUTDIR)\GuiDemod.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "GuiDemo - Win32 Release"
# Name "GuiDemo - Win32 Debug"

!IF  "$(CFG)" == "GuiDemo - Win32 Release"

!ELSEIF  "$(CFG)" == "GuiDemo - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Preempt\idler.cpp
DEP_CPP_IDLER=\
	".\preempt\idler.h"\
	

!IF  "$(CFG)" == "GuiDemo - Win32 Release"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\idler.obj" : $(SOURCE) $(DEP_CPP_IDLER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\idler.sbr" : $(SOURCE) $(DEP_CPP_IDLER) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "GuiDemo - Win32 Debug"


BuildCmds= \
	$(CPP) $(CPP_PROJ) $(SOURCE) \
	

"$(INTDIR)\idler.obj" : $(SOURCE) $(DEP_CPP_IDLER) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\idler.sbr" : $(SOURCE) $(DEP_CPP_IDLER) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\GuiDemo.rc
DEP_RSC_GUIDE=\
	".\ICON1.ICO"\
	

"$(INTDIR)\GuiDemo.res" : $(SOURCE) $(DEP_RSC_GUIDE) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\GuiDemo.cpp

!IF  "$(CFG)" == "GuiDemo - Win32 Release"

DEP_CPP_GUIDEM=\
	"\Omni\Include\MxOmni.h"\
	".\..\..\include\StdLego.h"\
	".\..\..\include\LegoOmni.h"\
	".\..\..\include\LWorld.h"\
	".\GuiDemo.h"\
	".\preempt\idler.h"\
	".\..\..\include\LegoGui.h"\
	".\..\..\include\LegoNotify.h"\
	"..\..\..\..\Omni\Include\MxAnx.h"\
	"..\..\..\..\Omni\Include\MxAudioPresenter.h"\
	"..\..\..\..\Omni\Include\MxAutoLock.h"\
	"..\..\..\..\Omni\Include\MxBitmap.h"\
	"\Omni\Include\MxBitmapMacros.h"\
	".\..\..\..\..\Omni\Include\MxCollection.h"\
	"\Omni\Include\MxCore.h"\
	".\..\..\..\..\Omni\Include\MxCriticalSection.h"\
	"..\..\..\..\Omni\Include\MxDequeue.h"\
	"..\..\..\..\Omni\Include\MxDisplaySurface.h"\
	".\..\..\..\..\Omni\Include\MxDSAction.h"\
	".\..\..\..\..\Omni\Include\MxDSBuffer.h"\
	".\..\..\..\..\Omni\Include\MxDSChunk.h"\
	"..\..\..\..\Omni\Include\MxDSFile.h"\
	".\..\..\..\..\Omni\Include\MxDSMarker.h"\
	".\..\..\..\..\Omni\Include\MxDSMedia.h"\
	".\..\..\..\..\Omni\Include\MxDSObject.h"\
	".\..\..\..\..\Omni\Include\MxDSRequest.h"\
	".\..\..\..\..\Omni\Include\MxDSSource.h"\
	".\..\..\..\..\Omni\Include\MxDSSubscriber.h"\
	".\..\..\..\..\Omni\Include\MxDSTypes.h"\
	"\Omni\Include\MxEntity.h"\
	"..\..\..\..\Omni\Include\MxEvent.h"\
	"..\..\..\..\Omni\Include\MxEventManager.h"\
	"..\..\..\..\Omni\Include\MxEventPresenter.h"\
	"..\..\..\..\Omni\Include\MxFlc.h"\
	"\Omni\Include\MxGeometry.h"\
	"..\..\..\..\Omni\Include\MxHashTable.h"\
	".\..\..\..\..\Omni\Include\mxio.h"\
	"\Omni\Include\MxList.h"\
	"\Omni\Include\MxMain.h"\
	"..\..\..\..\Omni\Include\MxMatrix.h"\
	"..\..\..\..\Omni\Include\MxMIDI.h"\
	"..\..\..\..\Omni\Include\MxMusicManager.h"\
	"\Omni\Include\MxNotificationManager.h"\
	"..\..\..\..\Omni\Include\MxObjectFactory.h"\
	"..\..\..\..\Omni\Include\MxPalette.h"\
	"\Omni\Include\MxPresenter.h"\
	"..\..\..\..\Omni\Include\MxPriority.h"\
	".\..\..\..\..\Omni\Include\MxQueue.h"\
	"..\..\..\..\Omni\Include\MxRegion.h"\
	".\..\..\..\..\Omni\Include\MxSemaphore.h"\
	"..\..\..\..\Omni\Include\MxSmk.h"\
	"..\..\..\..\Omni\Include\MxSoundManager.h"\
	"..\..\..\..\Omni\Include\MxStack.h"\
	"\Omni\Include\MxSTLWrap.h"\
	".\..\..\..\..\Omni\Include\MxStreamProvider.h"\
	".\..\..\..\..\Omni\Include\MxString.h"\
	"\Omni\Include\MxStreamController.h"\
	"..\..\..\..\Omni\Include\MxStreamer.h"\
	".\..\..\..\..\Omni\Include\MxThread.h"\
	"\Omni\Include\MxTimer.h"\
	".\..\..\..\..\Omni\Include\MxTypes.h"\
	".\..\..\..\..\Omni\Include\MxUtilities.h"\
	"..\..\..\..\Omni\Include\MxVariableTable.h"\
	"..\..\..\..\Omni\Include\MxVector.h"\
	"..\..\..\..\Omni\Include\MxVideoManager.h"\
	"..\..\..\..\Omni\Include\MxVideoPresenter.h"\
	"..\..\..\..\Omni\Include\rad.h"\
	"..\..\..\..\Omni\Include\smack.h"\
	"..\..\..\..\Omni\Include\wail.h"\
	"..\..\..\..\Omni\Include\MxTickleManager.h"\
	{$(INCLUDE)}"\ddraw.h"\
	"\Omni\Include\MxGeometry3D.h"\
	".\..\..\..\..\Omni\Include\MxStreamChunk.h"\
	".\..\..\..\..\Omni\Include\MxDSChunkSource.h"\
	".\..\..\..\..\Omni\Include\MxSymbol.h"\
	".\..\..\..\..\Omni\Include\MxWeaver.h"\
	"..\..\..\..\Omni\Include\MxPresentationManager.h"\
	".\..\..\..\..\Omni\Include\MxVersion.h"\
	"..\..\..\..\Omni\Include\MxAudioManager.h"\
	"\Omni\include\dsound\dsound.h"\
	{$(INCLUDE)}"\std.h"\
	".\..\..\..\..\Omni\Include\MxActionRequest.h"\
	"\Omni\Include\MxStd.h"\
	"..\..\..\..\Omni\Include\MxDebug.h"\
	".\..\..\Include\LActor.h"\
	"..\..\Include\PathCtrl.h"\
	"..\..\Include\LEntity.h"\
	"..\..\Include\Paths.h"\
	"..\..\Include\PathStruc.h"\
	"\Omni\Include\MxRawData.h"\
	"..\..\Include\LegoActorPresenter.h"\
	".\..\..\include\LegoInputManager.h"\
	".\..\..\include\LegoGuiBase.h"\
	".\..\..\include\LegoGuiControl.h"\
	

"$(INTDIR)\GuiDemo.obj" : $(SOURCE) $(DEP_CPP_GUIDEM) "$(INTDIR)"

"$(INTDIR)\GuiDemo.sbr" : $(SOURCE) $(DEP_CPP_GUIDEM) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "GuiDemo - Win32 Debug"

DEP_CPP_GUIDEM=\
	"\Omni\Include\MxOmni.h"\
	".\..\..\include\StdLego.h"\
	".\..\..\include\LegoOmni.h"\
	".\..\..\include\LWorld.h"\
	".\GuiDemo.h"\
	".\preempt\idler.h"\
	".\..\..\include\LegoGui.h"\
	".\..\..\include\LegoNotify.h"\
	"\Omni\Include\MxStd.h"\
	".\..\..\..\..\Omni\Include\MxTypes.h"\
	".\..\..\..\..\Omni\Include\MxDSTypes.h"\
	".\..\..\..\..\Omni\Include\MxUtilities.h"\
	"\Omni\Include\MxCore.h"\
	".\..\..\..\..\Omni\Include\MxString.h"\
	".\..\..\..\..\Omni\Include\MxCollection.h"\
	"\Omni\Include\MxList.h"\
	".\..\..\..\..\Omni\Include\MxQueue.h"\
	"..\..\..\..\Omni\Include\MxDebug.h"\
	"..\..\..\..\Omni\Include\MxAutoLock.h"\
	".\..\..\..\..\Omni\Include\mxio.h"\
	".\..\..\..\..\Omni\Include\MxCriticalSection.h"\
	"\Omni\Include\MxSTLWrap.h"\
	{$(INCLUDE)}"\std.h"\
	"\Omni\Include\MxMain.h"\
	".\..\..\..\..\Omni\Include\MxVersion.h"\
	".\..\..\Include\LActor.h"\
	"..\..\Include\PathCtrl.h"\
	"..\..\Include\LEntity.h"\
	"\Omni\Include\MxEntity.h"\
	"\Omni\Include\MxPresenter.h"\
	"\Omni\Include\MxGeometry.h"\
	"..\..\Include\Paths.h"\
	"\Omni\Include\MxGeometry3D.h"\
	"..\..\Include\PathStruc.h"\
	"\Omni\Include\MxRawData.h"\
	"..\..\Include\LegoActorPresenter.h"\
	"\Omni\Include\MxStreamController.h"\
	".\..\..\include\LegoInputManager.h"\
	".\..\..\..\..\Omni\Include\MxDSObject.h"\
	".\..\..\..\..\Omni\Include\MxDSBuffer.h"\
	".\..\..\..\..\Omni\Include\MxDSSubscriber.h"\
	".\..\..\..\..\Omni\Include\MxStreamProvider.h"\
	".\..\..\..\..\Omni\Include\MxDSRequest.h"\
	".\..\..\..\..\Omni\Include\MxDSMedia.h"\
	".\..\..\..\..\Omni\Include\MxActionRequest.h"\
	".\..\..\..\..\Omni\Include\MxDSChunk.h"\
	".\..\..\..\..\Omni\Include\MxDSChunkSource.h"\
	".\..\..\..\..\Omni\Include\MxSymbol.h"\
	".\..\..\..\..\Omni\Include\MxWeaver.h"\
	".\..\..\..\..\Omni\Include\MxStreamChunk.h"\
	".\..\..\..\..\Omni\Include\MxDSAction.h"\
	".\..\..\..\..\Omni\Include\MxDSMarker.h"\
	".\..\..\..\..\Omni\Include\MxDSSource.h"\
	".\..\..\..\..\Omni\Include\MxThread.h"\
	".\..\..\..\..\Omni\Include\MxSemaphore.h"\
	"\Omni\Include\MxBitmapMacros.h"\
	"\Omni\Include\MxTimer.h"\
	".\..\..\include\LegoGuiBase.h"\
	".\..\..\include\LegoGuiControl.h"\
	"\Omni\Include\MxNotificationManager.h"\
	

"$(INTDIR)\GuiDemo.obj" : $(SOURCE) $(DEP_CPP_GUIDEM) "$(INTDIR)"

"$(INTDIR)\GuiDemo.sbr" : $(SOURCE) $(DEP_CPP_GUIDEM) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
