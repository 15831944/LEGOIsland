# Microsoft Developer Studio Generated NMAKE File, Format Version 4.10
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

!IF "$(CFG)" == ""
CFG=Build All Lego Projects - Win32 3D Debug
!MESSAGE No configuration specified.  Defaulting to Build All Lego Projects -\
 Win32 3D Debug.
!ENDIF 

!IF "$(CFG)" != "Build All Lego Projects - Win32 Release" && "$(CFG)" !=\
 "Build All Lego Projects - Win32 Debug" && "$(CFG)" !=\
 "Build All Lego Projects - Win32 3D Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Build All Lego Projects.mak"\
 CFG="Build All Lego Projects - Win32 3D Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Build All Lego Projects - Win32 Release" (based on\
 "Win32 (x86) External Target")
!MESSAGE "Build All Lego Projects - Win32 Debug" (based on\
 "Win32 (x86) External Target")
!MESSAGE "Build All Lego Projects - Win32 3D Debug" (based on\
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
# PROP Target_Last_Scanned "Build All Lego Projects - Win32 Debug"

!IF  "$(CFG)" == "Build All Lego Projects - Win32 Release"

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
# PROP Cmd_Line "NMAKE /f Master.mak"
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "Build All Lego Projects.exe"
# PROP Bsc_Name "Build All Lego Projects.bsc"
OUTDIR=.\Release
INTDIR=.\Release

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "Build All Lego Projects - Win32 Debug"

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
# PROP Cmd_Line "NMAKE /f Master.mak"
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "Build All Lego Projects.exe"
# PROP Bsc_Name "Build All Lego Projects.bsc"
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ELSEIF  "$(CFG)" == "Build All Lego Projects - Win32 3D Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Build_Al"
# PROP BASE Intermediate_Dir "Build_Al"
# PROP BASE Target_Dir ""
# PROP BASE Cmd_Line "NMAKE /f Master.mak"
# PROP BASE Rebuild_Opt "BUILDALL="Yes""
# PROP BASE Target_File "Build All Lego Projects.exe"
# PROP BASE Bsc_Name "Build All Lego Projects.bsc"
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build_Al"
# PROP Intermediate_Dir "Build_Al"
# PROP Target_Dir ""
# PROP Cmd_Line "NMAKE /f Master.mak 3D_BUILD"
# PROP Rebuild_Opt "BUILDALL="Yes""
# PROP Target_File "Build All Lego Projects.exe"
# PROP Bsc_Name "Build All Lego Projects.bsc"
OUTDIR=.\Build_Al
INTDIR=.\Build_Al

ALL : 

CLEAN : 
	-@erase 

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

!ENDIF 

################################################################################
# Begin Target

# Name "Build All Lego Projects - Win32 Release"
# Name "Build All Lego Projects - Win32 Debug"
# Name "Build All Lego Projects - Win32 3D Debug"

!IF  "$(CFG)" == "Build All Lego Projects - Win32 Release"

".\Build All Lego Projects.exe" : 
   CD D:\Lego\Master
   NMAKE /f Master.mak

!ELSEIF  "$(CFG)" == "Build All Lego Projects - Win32 Debug"

".\Build All Lego Projects.exe" : 
   CD D:\Lego\Master
   NMAKE /f Master.mak

!ELSEIF  "$(CFG)" == "Build All Lego Projects - Win32 3D Debug"

".\Build All Lego Projects.exe" : 
   CD D:\Lego\Master
   NMAKE /f Master.mak 3D_BUILD

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\Master.mak

!IF  "$(CFG)" == "Build All Lego Projects - Win32 Release"

!ELSEIF  "$(CFG)" == "Build All Lego Projects - Win32 Debug"

!ELSEIF  "$(CFG)" == "Build All Lego Projects - Win32 3D Debug"

# PROP Intermediate_Dir "Debug"
INTDIR_SRC=.\Debug
"$(INTDIR_SRC)" :
    if not exist "$(INTDIR_SRC)/$(NULL)" mkdir "$(INTDIR_SRC)"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
