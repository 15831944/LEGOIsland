# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=MeshCost - Win32 Debug RL40
!MESSAGE No configuration specified.  Defaulting to MeshCost - Win32 Debug\
 RL40.
!ENDIF 

!IF "$(CFG)" != "MeshCost - Win32 Release" && "$(CFG)" !=\
 "MeshCost - Win32 Debug" && "$(CFG)" != "MeshCost - Win32 Debug RL40"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MeshCost.mak" CFG="MeshCost - Win32 Debug RL40"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MeshCost - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MeshCost - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "MeshCost - Win32 Debug RL40" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "MeshCost - Win32 Debug RL40"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "MeshCost - Win32 Release"

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

ALL : "$(OUTDIR)\MeshCost.exe"

CLEAN : 
	-@erase "$(INTDIR)\CostCalculation.obj"
	-@erase "$(INTDIR)\MeshCost.obj"
	-@erase "$(INTDIR)\MeshCost.pch"
	-@erase "$(INTDIR)\MeshCost.res"
	-@erase "$(INTDIR)\MeshCostDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(OUTDIR)\MeshCost.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MeshCost.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MeshCost.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MeshCost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 MxDirectX.lib ddraw.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc"
LINK32_FLAGS=MxDirectX.lib ddraw.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/MeshCost.pdb" /machine:I386 /nodefaultlib:"libc"\
 /out:"$(OUTDIR)/MeshCost.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CostCalculation.obj" \
	"$(INTDIR)\MeshCost.obj" \
	"$(INTDIR)\MeshCost.res" \
	"$(INTDIR)\MeshCostDlg.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MeshCost.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\MeshCostRL20.exe"

CLEAN : 
	-@erase "$(INTDIR)\CostCalculation.obj"
	-@erase "$(INTDIR)\MeshCost.obj"
	-@erase "$(INTDIR)\MeshCost.pch"
	-@erase "$(INTDIR)\MeshCost.res"
	-@erase "$(INTDIR)\MeshCostDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MeshCostRL20.exe"
	-@erase "$(OUTDIR)\MeshCostRL20.ilk"
	-@erase "$(OUTDIR)\MeshCostRL20.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MeshCost.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MeshCost.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MeshCost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 tglRL20d.lib rlddf.lib rlddfglu.lib rlff.lib 3DManagerd.lib ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd" /nodefaultlib:"libcmtd" /out:"Debug/MeshCostRL20.exe"
LINK32_FLAGS=tglRL20d.lib rlddf.lib rlddfglu.lib rlff.lib 3DManagerd.lib\
 ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib\
 roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)/MeshCostRL20.pdb" /debug /machine:I386\
 /nodefaultlib:"libc" /nodefaultlib:"libcd" /nodefaultlib:"libcmtd"\
 /out:"$(OUTDIR)/MeshCostRL20.exe" 
LINK32_OBJS= \
	"$(INTDIR)\CostCalculation.obj" \
	"$(INTDIR)\MeshCost.obj" \
	"$(INTDIR)\MeshCost.res" \
	"$(INTDIR)\MeshCostDlg.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MeshCostRL20.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "MeshCost"
# PROP BASE Intermediate_Dir "MeshCost"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\MeshCostRL40.exe"

CLEAN : 
	-@erase "$(INTDIR)\CostCalculation.obj"
	-@erase "$(INTDIR)\MeshCost.obj"
	-@erase "$(INTDIR)\MeshCost.pch"
	-@erase "$(INTDIR)\MeshCost.res"
	-@erase "$(INTDIR)\MeshCostDlg.obj"
	-@erase "$(INTDIR)\ProgressDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\MeshCostRL40.exe"
	-@erase "$(OUTDIR)\MeshCostRL40.ilk"
	-@erase "$(OUTDIR)\MeshCostRL40.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# SUBTRACT CPP /Fr
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MeshCost.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/MeshCost.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/MeshCost.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 tglrl20d.lib rlddf.lib rlddfglu.lib rlff.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd"
# ADD LINK32 tglRL40d.lib d3drm.lib 3DManagerd.lib ViewManagerd.lib realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd" /nodefaultlib:"libcmtd" /out:"Debug/MeshCostRL40.exe"
LINK32_FLAGS=tglRL40d.lib d3drm.lib 3DManagerd.lib ViewManagerd.lib\
 realtimed.lib pcubed.lib TglAfxd.lib MxDirectXd.lib ddraw.lib roid.lib\
 animd.lib geomd.lib miscd.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/MeshCostRL40.pdb" /debug /machine:I386 /nodefaultlib:"libc"\
 /nodefaultlib:"libcd" /nodefaultlib:"libcmtd" /out:"$(OUTDIR)/MeshCostRL40.exe"\
 
LINK32_OBJS= \
	"$(INTDIR)\CostCalculation.obj" \
	"$(INTDIR)\MeshCost.obj" \
	"$(INTDIR)\MeshCost.res" \
	"$(INTDIR)\MeshCostDlg.obj" \
	"$(INTDIR)\ProgressDlg.obj" \
	"$(INTDIR)\StdAfx.obj"

"$(OUTDIR)\MeshCostRL40.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "MeshCost - Win32 Release"
# Name "MeshCost - Win32 Debug"
# Name "MeshCost - Win32 Debug RL40"

!IF  "$(CFG)" == "MeshCost - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "MeshCost - Win32 Release"

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshCost.cpp
DEP_CPP_MESHC=\
	".\CostCalculation.h"\
	".\MeshCost.h"\
	".\MeshCostDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\LODList.h"\
	{$(INCLUDE)}"\realtime.h"\
	{$(INCLUDE)}"\std.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\tglVector.h"\
	

!IF  "$(CFG)" == "MeshCost - Win32 Release"


"$(INTDIR)\MeshCost.obj" : $(SOURCE) $(DEP_CPP_MESHC) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"


"$(INTDIR)\MeshCost.obj" : $(SOURCE) $(DEP_CPP_MESHC) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"


"$(INTDIR)\MeshCost.obj" : $(SOURCE) $(DEP_CPP_MESHC) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshCostDlg.cpp
DEP_CPP_MESHCO=\
	".\CostCalculation.h"\
	".\MeshCost.h"\
	".\MeshCostDlg.h"\
	".\ProgressDlg.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
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
	{$(INCLUDE)}"\Version.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

!IF  "$(CFG)" == "MeshCost - Win32 Release"


"$(INTDIR)\MeshCostDlg.obj" : $(SOURCE) $(DEP_CPP_MESHCO) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"


"$(INTDIR)\MeshCostDlg.obj" : $(SOURCE) $(DEP_CPP_MESHCO) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"


"$(INTDIR)\MeshCostDlg.obj" : $(SOURCE) $(DEP_CPP_MESHCO) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


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
	

!IF  "$(CFG)" == "MeshCost - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MeshCost.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MeshCost.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MeshCost.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MeshCost.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/MeshCost.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\MeshCost.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MeshCost.rc

!IF  "$(CFG)" == "MeshCost - Win32 Release"

DEP_RSC_MESHCOS=\
	".\res\MeshCost.ico"\
	".\res\MeshCost.rc2"\
	

"$(INTDIR)\MeshCost.res" : $(SOURCE) $(DEP_RSC_MESHCOS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"

DEP_RSC_MESHCOS=\
	".\res\MeshCost.ico"\
	".\res\MeshCost.rc2"\
	{$(INCLUDE)}"\Palette.bmp"\
	

"$(INTDIR)\MeshCost.res" : $(SOURCE) $(DEP_RSC_MESHCOS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"

DEP_RSC_MESHCOS=\
	".\res\MeshCost.ico"\
	".\res\MeshCost.rc2"\
	{$(INCLUDE)}"\Palette.bmp"\
	

"$(INTDIR)\MeshCost.res" : $(SOURCE) $(DEP_RSC_MESHCOS) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressDlg.cpp
DEP_CPP_PROGR=\
	".\MeshCost.h"\
	".\ProgressDlg.h"\
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
	

!IF  "$(CFG)" == "MeshCost - Win32 Release"


"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"


"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"


"$(INTDIR)\ProgressDlg.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CostCalculation.cpp

!IF  "$(CFG)" == "MeshCost - Win32 Release"

DEP_CPP_COSTC=\
	".\CostCalculation.h"\
	".\MeshCost.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
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
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\CostCalculation.obj" : $(SOURCE) $(DEP_CPP_COSTC) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug"

DEP_CPP_COSTC=\
	".\CostCalculation.h"\
	".\MeshCost.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoView1.h"\
	{$(INCLUDE)}"\LegoViewWnd.h"\
	{$(INCLUDE)}"\MxDirect3DWnd.h"\
	{$(INCLUDE)}"\MxDirectDrawWnd.h"\
	{$(INCLUDE)}"\tgl.h"\
	{$(INCLUDE)}"\TglSurface.h"\
	

"$(INTDIR)\CostCalculation.obj" : $(SOURCE) $(DEP_CPP_COSTC) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ELSEIF  "$(CFG)" == "MeshCost - Win32 Debug RL40"

DEP_CPP_COSTC=\
	".\CostCalculation.h"\
	".\MeshCost.h"\
	".\StdAfx.h"\
	{$(INCLUDE)}"\d3d.h"\
	{$(INCLUDE)}"\d3dcaps.h"\
	{$(INCLUDE)}"\d3dtypes.h"\
	{$(INCLUDE)}"\ddraw.h"\
	{$(INCLUDE)}"\Lego3DView.h"\
	{$(INCLUDE)}"\LegoMatrix.h"\
	{$(INCLUDE)}"\LegoROI.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
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
	{$(INCLUDE)}"\vec.h"\
	{$(INCLUDE)}"\ViewLODList.h"\
	{$(INCLUDE)}"\ViewManager.h"\
	

"$(INTDIR)\CostCalculation.obj" : $(SOURCE) $(DEP_CPP_COSTC) "$(INTDIR)"\
 "$(INTDIR)\MeshCost.pch"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
