# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Convert - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Convert - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Convert - Win32 Release" && "$(CFG)" !=\
 "Convert - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Convert.mak" CFG="Convert - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Convert - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Convert - Win32 Debug" (based on "Win32 (x86) Application")
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
# PROP Target_Last_Scanned "Convert - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "Convert - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\Convert.exe"

CLEAN : 
	-@erase "$(INTDIR)\Convert.obj"
	-@erase "$(INTDIR)\Convert.res"
	-@erase "$(INTDIR)\Gif.obj"
	-@erase "$(INTDIR)\Gui.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\Script.obj"
	-@erase "$(INTDIR)\StudioFile.obj"
	-@erase "$(OUTDIR)\Convert.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Convert.pch" /YX /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Convert.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Convert.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 3dftkvc1.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc"
LINK32_FLAGS=3dftkvc1.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Convert.pdb" /machine:I386 /nodefaultlib:"libc"\
 /out:"$(OUTDIR)/Convert.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Convert.obj" \
	"$(INTDIR)\Convert.res" \
	"$(INTDIR)\Gif.obj" \
	"$(INTDIR)\Gui.obj" \
	"$(INTDIR)\model.obj" \
	"$(INTDIR)\Script.obj" \
	"$(INTDIR)\StudioFile.obj"

"$(OUTDIR)\Convert.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\Convert.exe"

CLEAN : 
	-@erase "$(INTDIR)\Convert.obj"
	-@erase "$(INTDIR)\Convert.res"
	-@erase "$(INTDIR)\Gif.obj"
	-@erase "$(INTDIR)\Gui.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\Script.obj"
	-@erase "$(INTDIR)\StudioFile.obj"
	-@erase "$(INTDIR)\vc40.idb"
	-@erase "$(INTDIR)\vc40.pdb"
	-@erase "$(OUTDIR)\Convert.exe"
	-@erase "$(OUTDIR)\Convert.ilk"
	-@erase "$(OUTDIR)\Convert.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /YX /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Convert.pch" /YX /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\.
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/Convert.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Convert.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 3dftkvc1.lib animd.lib geomd.lib miscd.lib squat.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd"
# SUBTRACT LINK32 /pdb:none
LINK32_FLAGS=3dftkvc1.lib animd.lib geomd.lib miscd.lib squat.lib /nologo\
 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)/Convert.pdb" /debug\
 /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd"\
 /out:"$(OUTDIR)/Convert.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Convert.obj" \
	"$(INTDIR)\Convert.res" \
	"$(INTDIR)\Gif.obj" \
	"$(INTDIR)\Gui.obj" \
	"$(INTDIR)\model.obj" \
	"$(INTDIR)\Script.obj" \
	"$(INTDIR)\StudioFile.obj"

"$(OUTDIR)\Convert.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Convert - Win32 Release"
# Name "Convert - Win32 Debug"

!IF  "$(CFG)" == "Convert - Win32 Release"

!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Convert.cpp

!IF  "$(CFG)" == "Convert - Win32 Release"

DEP_CPP_CONVE=\
	".\Convert.h"\
	".\Gif.h"\
	".\Model.h"\
	".\Script.h"\
	".\StudioFile.h"\
	{$(INCLUDE)}"\3dsftk.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoBox.h"\
	{$(INCLUDE)}"\LegoColor.h"\
	{$(INCLUDE)}"\LegoFace.h"\
	{$(INCLUDE)}"\LegoImage.h"\
	{$(INCLUDE)}"\LegoMesh.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTextureVertex.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\Squat.h"\
	{$(INCLUDE)}"\Version.h"\
	

"$(INTDIR)\Convert.obj" : $(SOURCE) $(DEP_CPP_CONVE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

DEP_CPP_CONVE=\
	".\Convert.h"\
	".\Gif.h"\
	".\Model.h"\
	".\Script.h"\
	".\StudioFile.h"\
	{$(INCLUDE)}"\3dsftk.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoBox.h"\
	{$(INCLUDE)}"\LegoColor.h"\
	{$(INCLUDE)}"\LegoFace.h"\
	{$(INCLUDE)}"\LegoImage.h"\
	{$(INCLUDE)}"\LegoMesh.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTextureVertex.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\Squat.h"\
	{$(INCLUDE)}"\Version.h"\
	

"$(INTDIR)\Convert.obj" : $(SOURCE) $(DEP_CPP_CONVE) "$(INTDIR)"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Convert.rc
DEP_RSC_CONVER=\
	".\cdromdrive.ico"\
	".\closedfolder.ico"\
	".\computer.ico"\
	".\fixeddrive.ico"\
	".\openfolder.ico"\
	".\remotedrive.ico"\
	".\removabledrive.ico"\
	

"$(INTDIR)\Convert.res" : $(SOURCE) $(DEP_RSC_CONVER) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\model.cpp
DEP_CPP_MODEL=\
	".\Convert.h"\
	".\Model.h"\
	{$(INCLUDE)}"\3dsftk.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoBox.h"\
	{$(INCLUDE)}"\LegoColor.h"\
	{$(INCLUDE)}"\LegoFace.h"\
	{$(INCLUDE)}"\LegoMesh.h"\
	{$(INCLUDE)}"\LegoSphere.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTextureVertex.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoUtil.h"\
	{$(INCLUDE)}"\LegoVector.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\Vec.h"\
	

"$(INTDIR)\model.obj" : $(SOURCE) $(DEP_CPP_MODEL) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gif.cpp
DEP_CPP_GIF_C=\
	".\Gif.h"\
	

"$(INTDIR)\Gif.obj" : $(SOURCE) $(DEP_CPP_GIF_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Gui.cpp
DEP_CPP_GUI_C=\
	".\Convert.h"\
	".\gui.h"\
	".\Model.h"\
	".\Script.h"\
	".\StudioFile.h"\
	{$(INCLUDE)}"\3dsftk.h"\
	{$(INCLUDE)}"\LegoAnim.h"\
	{$(INCLUDE)}"\LegoBox.h"\
	{$(INCLUDE)}"\LegoColor.h"\
	{$(INCLUDE)}"\LegoFace.h"\
	{$(INCLUDE)}"\LegoMesh.h"\
	{$(INCLUDE)}"\LegoStorage.h"\
	{$(INCLUDE)}"\LegoTexture.h"\
	{$(INCLUDE)}"\LegoTextureVertex.h"\
	{$(INCLUDE)}"\LegoTree.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	{$(INCLUDE)}"\LegoVertex.h"\
	{$(INCLUDE)}"\Version.h"\
	

"$(INTDIR)\Gui.obj" : $(SOURCE) $(DEP_CPP_GUI_C) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StudioFile.cpp
DEP_CPP_STUDI=\
	".\StudioFile.h"\
	{$(INCLUDE)}"\3dsftk.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\StudioFile.obj" : $(SOURCE) $(DEP_CPP_STUDI) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Script.cpp

!IF  "$(CFG)" == "Convert - Win32 Release"

DEP_CPP_SCRIP=\
	".\Convert.h"\
	".\Script.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\Script.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Convert - Win32 Debug"

DEP_CPP_SCRIP=\
	".\Convert.h"\
	".\Script.h"\
	{$(INCLUDE)}"\3dsftk.h"\
	{$(INCLUDE)}"\LegoColor.h"\
	{$(INCLUDE)}"\LegoTypes.h"\
	

"$(INTDIR)\Script.obj" : $(SOURCE) $(DEP_CPP_SCRIP) "$(INTDIR)"


!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
