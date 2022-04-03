# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=LegoMaster - Win32 Debug with SmartHeap
!MESSAGE No configuration specified.  Defaulting to LegoMaster - Win32 Debug\
 with SmartHeap.
!ENDIF 

!IF "$(CFG)" != "LegoMaster - Win32 Release" && "$(CFG)" !=\
 "LegoMaster - Win32 Debug" && "$(CFG)" != "LegoMaster - Win32 3D Debug" &&\
 "$(CFG)" != "LegoMaster - Win32 Debug with SmartHeap"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "LegoMaster.mak"\
 CFG="LegoMaster - Win32 Debug with SmartHeap"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LegoMaster - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "LegoMaster - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE "LegoMaster - Win32 3D Debug" (based on "Win32 (x86) External Target")
!MESSAGE "LegoMaster - Win32 Debug with SmartHeap" (based on\
 "Win32 (x86) External Target")
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
# PROP Target_Last_Scanned "LegoMaster - Win32 Debug"

!IF  "$(CFG)" == "LegoMaster - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Master.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Master.exe"
# PROP BASE Bsc_Name "Master.bsc"
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Master.mak CFG="LegoMaster - Win32 Release""
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "LegoMaster.exe"
# PROP Bsc_Name "LegoMaster.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Master.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Master.exe"
# PROP BASE Bsc_Name "Master.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Master.mak CFG="LegoMaster - Win32 Debug""
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "LegoMaster.exe"
# PROP Bsc_Name "LegoMaster.bsc"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 3D Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build_Al"
# PROP BASE Intermediate_Dir "Build_Al"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Master.mak"
# PROP BASE Rebuild_Opt "BUILDALL="Yes""
# PROP BASE Target_File "LegoMaster.exe"
# PROP BASE Bsc_Name "LegoMaster.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build_Al"
# PROP Intermediate_Dir "Build_Al"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Master.mak 3D_BUILD CFG="LegoMaster - Win32 3D Debug""
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "LegoMaster.exe"
# PROP Bsc_Name "LegoMaster.bsc"
OUTDIR=.\Build_Al
INTDIR=.\Build_Al

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 Debug with SmartHeap"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build_A0"
# PROP BASE Intermediate_Dir "Build_A0"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Master.mak"
# PROP BASE Rebuild_Opt "BUILDALL="Yes""
# PROP BASE Target_File "LegoMaster.exe"
# PROP BASE Bsc_Name "LegoMaster.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build_A0"
# PROP Intermediate_Dir "Build_A0"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Master.mak CFG="LegoMaster - Win32 Debug with SmartHeap""
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "LegoMaster.exe"
# PROP Bsc_Name "LegoMaster.bsc"
OUTDIR=.\Build_A0
INTDIR=.\Build_A0

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ENDIF 

################################################################################
# Begin Target

# Name "LegoMaster - Win32 Release"
# Name "LegoMaster - Win32 Debug"
# Name "LegoMaster - Win32 3D Debug"
# Name "LegoMaster - Win32 Debug with SmartHeap"

!IF  "$(CFG)" == "LegoMaster - Win32 Release"

".\LegoMaster.exe" : 
   CD C:\Lego\Master
   NMAKE /f Master.mak CFG="LegoMaster - Win32 Release"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 Debug"

".\LegoMaster.exe" : 
   CD C:\Lego\Master
   NMAKE /f Master.mak CFG="LegoMaster - Win32 Debug"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 3D Debug"

".\LegoMaster.exe" : 
   CD C:\Lego\Master
   NMAKE /f Master.mak 3D_BUILD CFG="LegoMaster - Win32 3D Debug"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 Debug with SmartHeap"

".\LegoMaster.exe" : 
   CD C:\Lego\Master
   NMAKE /f Master.mak CFG="LegoMaster - Win32 Debug with SmartHeap"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Master.mak

!IF  "$(CFG)" == "LegoMaster - Win32 Release"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 Debug"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 3D Debug"

# PROP Intermediate_Dir "Debug"
INTDIR_SRC=.\Debug
"$(INTDIR_SRC)" :
    if not exist "$(INTDIR_SRC)/$(NULL)" mkdir "$(INTDIR_SRC)"

!ELSEIF  "$(CFG)" == "LegoMaster - Win32 Debug with SmartHeap"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
