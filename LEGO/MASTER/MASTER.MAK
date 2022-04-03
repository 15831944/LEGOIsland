!IF "$(CFG)" == "LegoMaster - Win32 Release"
TYPE=Release
CONFIGURATION=Win32 Release
SH_OPTION=
!ELSEIF "$(CFG)" == "LegoMaster - Win32 Debug"
TYPE=Debug
CONFIGURATION=Win32 Debug
SH_OPTION=
!ELSEIF "$(CFG)" == "LegoMaster - Win32 Debug with SmartHeap"
TYPE=Debug
CONFIGURATION=Win32 Debug with SmartHeap
SH_OPTION=SMARTHEAP_
!ELSEIF "$(CFG)" == "LegoMaster - Win32 3D Debug"
TYPE=Debug
CONFIGURATION=Win32 Debug
SH_OPTION=
!ELSE
!MESSAGE Invalid configuration: "$(CFG)"
!MESSAGE "LegoMaster - Win32 Debug" configuration will build as default.
TYPE=Debug
CONFIGURATION=Win32 Debug
SH_OPTION=
!ENDIF 

!IF "$(BUILDALL)" == "Yes"
TARGET_PROJECT=REBUILD_ALL
!ELSE
TARGET_PROJECT=BUILD
!ENDIF

#############################################################################
# Projects Directories Section

WeaveDir=\Omni\Src\Weave
OmniDir=\Omni\Src\Dll
PcubeDir=\Pcube
RealTimeDir=\RealTime
TglRL20Dir=\Tgl
TglRL40Dir=\Tgl
TglAfxDir=\TglAfx
ViewManagerDir=\ViewManager
MxDirectXDir=\MxDirectX
RoiDir=\Lego\Sources\Roi
AnimDir=\Lego\Sources\Anim
GeomDir=\Lego\Sources\Geom
MiscDir=\Lego\Sources\Misc
MeshCostDir=\Lego\Sources\MeshCost
LegoDir=\Lego\Sources\Product
LegoOmniDir=\Lego\LegoOmni\Src\Dll
MainDir=\Lego\Sources\Main
WriterDir=\Lego\LegoOmni\Src\Gui\GuiWriter
3DManagerDir=\Lego\Sources\3DManager
ROIInspectorDir=\Lego\Sources\ROIInspector
ConvertDir=\Lego\Tools\Convert


#############################################################################
# Main "Run" section

RUN: "$(SH_OPTION)$(TARGET_PROJECT)"


#############################################################################
REBUILD_ALL:\
	$(WeaveDir)\Weave.clean                 \
	$(WeaveDir)\Weave.build                 \
    $(OmniDir)\Omni.clean                   \
    $(OmniDir)\Omni.build                   \
    $(PcubeDir)\pcube.clean                 \
    $(PcubeDir)\pcube.build                 \
    $(RealTimeDir)\realtime.clean           \
    $(RealTimeDir)\realtime.build           \
    $(TglRL20Dir)\TGLRL20.clean             \
    $(TglRL20Dir)\TGLRL20.build             \
    $(TglRL40Dir)\tglRL40.clean             \
    $(TglRL40Dir)\tglRL40.build             \
    $(TglAfxDir)\TglAfx.clean               \
    $(TglAfxDir)\TglAfx.build               \
    $(ViewManagerDir)\ViewManager.clean     \
    $(ViewManagerDir)\ViewManager.build     \
    $(MxDirectXDir)\MxDirectX.clean         \
    $(MxDirectXDir)\MxDirectX.build         \
    $(RoiDir)\roi.clean                     \
    $(RoiDir)\roi.build                     \
    $(AnimDir)\anim.clean                   \
    $(AnimDir)\anim.build                   \
    $(GeomDir)\geom.clean                   \
    $(GeomDir)\geom.build                   \
    $(MiscDir)\misc.clean                   \
    $(MiscDir)\misc.build                   \
    $(3DManagerDir)\3DManager.clean         \
    $(3DManagerDir)\3DManager.build         \
    $(ROIInspectorDir)\ROIInspectorRL40.clean \
    $(ROIInspectorDir)\ROIInspectorRL40.build \
    $(ROIInspectorDir)\ROIInspectorRL20.clean \
    $(ROIInspectorDir)\ROIInspectorRL20.build \
    $(MeshCostDir)\MeshCost.clean           \
    $(MeshCostDir)\MeshCost.build           \
    $(MeshCostDir)\MeshCostRL40.clean       \
    $(MeshCostDir)\MeshCostRL40.build       \
    $(LegoDir)\LegoRL20.clean               \
    $(LegoDir)\LegoRL20.build               \
    $(LegoDir)\LegoRL40.clean               \
    $(LegoDir)\LegoRL40.build               \
    $(LegoOmniDir)\LegoOmni.clean           \
    $(LegoOmniDir)\LegoOmni.build           \
    $(MainDir)\Main.clean                   \
    $(MainDir)\Main.build                   \
    $(WriterDir)\writer.clean               \
    $(WriterDir)\writer.build               \
    $(ConvertDir)\Convert.clean             \
    $(ConvertDir)\Convert.build             \


BUILD:	\
	$(WeaveDir)\Weave.build                 \
    $(OmniDir)\Omni.build                   \
    $(PcubeDir)\pcube.build                 \
    $(RealTimeDir)\realtime.build           \
    $(TglRL20Dir)\TGLRL20.build             \
    $(TglRL40Dir)\tglRL40.build             \
    $(TglAfxDir)\TglAfx.build               \
    $(ViewManagerDir)\ViewManager.build     \
    $(MxDirectXDir)\MxDirectX.build         \
    $(RoiDir)\roi.build                     \
    $(AnimDir)\anim.build                   \
    $(GeomDir)\geom.build                   \
    $(MiscDir)\misc.build                   \
    $(3DManagerDir)\3DManager.build         \
    $(ROIInspectorDir)\ROIInspectorRL40.build \
    $(ROIInspectorDir)\ROIInspectorRL20.build \
    $(MeshCostDir)\MeshCost.build           \
    $(MeshCostDir)\MeshCostRL40.build       \
    $(LegoDir)\LegoRL20.build               \
    $(LegoDir)\LegoRL40.build               \
    $(LegoOmniDir)\LegoOmni.build           \
    $(MainDir)\Main.build                   \
    $(WriterDir)\writer.build               \
    $(ConvertDir)\Convert.build             \


CLEAN:	\
	$(WeaveDir)\Weave.clean                 \
    $(OmniDir)\Omni.clean                   \
    $(PcubeDir)\pcube.clean                 \
    $(RealTimeDir)\realtime.clean           \
    $(TglRL20Dir)\TGLRL20.clean             \
    $(TglRL40Dir)\tglRL40.clean             \
    $(TglAfxDir)\TglAfx.clean               \
    $(ViewManagerDir)\ViewManager.clean     \
    $(MxDirectXDir)\MxDirectX.clean         \
    $(RoiDir)\roi.clean                     \
    $(AnimDir)\anim.clean                   \
    $(GeomDir)\geom.clean                   \
    $(MiscDir)\misc.clean                   \
    $(3DManagerDir)\3DManager.clean         \
    $(ROIInspectorDir)\ROIInspectorRL40.clean \
    $(ROIInspectorDir)\ROIInspectorRL20.clean \
    $(MeshCostDir)\MeshCost.clean           \
    $(MeshCostDir)\MeshCostRL40.clean       \
    $(LegoDir)\LegoRL20.clean               \
    $(LegoDir)\LegoRL40.clean               \
    $(LegoOmniDir)\LegoOmni.clean           \
    $(MainDir)\Main.clean                   \
    $(WriterDir)\writer.clean               \
    

3D_BUILD:	\
    $(PcubeDir)\pcube.build                 \
    $(RealTimeDir)\realtime.build           \
    $(TglRL20Dir)\TGLRL20.build             \
    $(TglRL40Dir)\tglRL40.build             \
    $(TglAfxDir)\TglAfx.build               \
    $(ViewManagerDir)\ViewManager.build     \
    $(MxDirectXDir)\MxDirectX.build         \
    $(RoiDir)\roi.build                     \
    $(AnimDir)\anim.build                   \
    $(GeomDir)\geom.build                   \
    $(MiscDir)\misc.build                   \
    $(3DManagerDir)\3DManager.build         \
    $(ROIInspectorDir)\ROIInspectorRL40.build \
    $(ROIInspectorDir)\ROIInspectorRL20.build \
    $(MeshCostDir)\MeshCost.build           \
    $(MeshCostDir)\MeshCostRL40.build       \
    $(LegoDir)\LegoRL20.build               \
    $(LegoDir)\LegoRL40.build               \


#############################################################################

SMARTHEAP_REBUILD_ALL:\
#	$(WeaveDir)\Weave.clean                             \
#	$(WeaveDir)\Weave.build                             \
    $(OmniDir)\Omni.clean                               \
    $(OmniDir)\Omni.build                               \
    $(RoiDir)\roi.clean                                 \
    $(RoiDir)\roi.build                                 \
    $(LegoOmniDir)\LegoOmni.clean                       \
    $(LegoOmniDir)\LegoOmni.build                       \
    $(MainDir)\Main.clean                               \
    $(MainDir)\Main.build                               \

SMARTHEAP_BUILD:\
#	$(WeaveDir)\Weave.build                             \
    $(OmniDir)\Omni.build                               \
    $(RoiDir)\roi.build                                 \
    $(LegoOmniDir)\LegoOmni.build                       \
    $(MainDir)\Main.build                               \


#############################################################################

.SUFFIXES : .$(TYPE)

$(WeaveDir)\Weave.$(TYPE):                  # Weaver
$(OmniDir)\Omni.$(TYPE):                    # Omni
$(PcubeDir)\pcube.$(TYPE):                  # Pcube
$(RealTimeDir)\realtime.$(TYPE):            # RealTime
$(TglRL20Dir)\TGLRL20.$(TYPE):              # TglRL20
$(TglRL40Dir)\tglRL40.$(TYPE):              # TglRL40
$(TglAfxDir)\TglAfx.$(TYPE):                # TglAfx
$(ViewManagerDir)\ViewManager.$(TYPE):      # ViewManager
$(MxDirectXDir)\MxDirectX.$(TYPE):          # MxDirectX
$(RoiDir)\roi.$(TYPE):                      # Roi
$(AnimDir)\anim.$(TYPE):                    # anim
$(GeomDir)\geom.$(TYPE):                    # geom
$(MiscDir)\misc.$(TYPE):                    # misc
$(MeshCostDir)\MeshCost.$(TYPE):            # MeshCost
$(LegoOmniDir)\LegoOmni.$(TYPE):            # LegoOmni
$(MainDir)\Main.$(TYPE):                    # Main
$(WriterDir)\writer.$(TYPE):                # writer
$(3DManagerDir)\3DManager.$(TYPE):          # 3DManager
$(ConvertDir)\Convert.$(TYPE):              # Convert

.$(TYPE).build:
	@echo *** Building $(@B) - $(CONFIGURATION)...
	@cd $(@D)
	@-nmake ALL /F "$(@B).mak" CFG="$(@B) - $(CONFIGURATION)" /nologo 
	@cd $(MAKEDIR)
	@echo *** Building $(@B) - $(CONFIGURATION) done

.$(TYPE).clean:
	@echo *** Cleaning $(@B) - $(CONFIGURATION)...
	@cd $(@D)
	@-nmake CLEAN /F "$(@B).mak" CFG="$(@B) - $(CONFIGURATION)" /nologo 
	@cd $(MAKEDIR)
	@echo *** Cleaning $(@B) - $(CONFIGURATION) done

### MeshCostRL40 ------------------------------------------------------------
$(MeshCostDir)\MeshCostRL40.build:
	@echo *** Building $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake ALL /F "MeshCost.mak" CFG="MeshCost - $(CONFIGURATION) RL40" /nologo 
	@cd $(MAKEDIR)
	@echo *** Building $(@B) $(CONFIGURATION) done

$(MeshCostDir)\MeshCostRL40.clean:
	@echo *** Cleaning $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake CLEAN /F "MeshCost.mak" CFG="MeshCost - $(CONFIGURATION) RL40" /nologo 
	@cd $(MAKEDIR)
	@echo *** Cleaning $(@B) $(CONFIGURATION) done

### LegoRL20 ----------------------------------------------------------------
$(LegoDir)\LegoRL20.build:
	@echo *** Building $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake ALL /F "Lego.mak" CFG="Lego - $(CONFIGURATION) RL20" /nologo 
	@cd $(MAKEDIR)
	@echo *** Building $(@B) $(CONFIGURATION) done

$(LegoDir)\LegoRL20.clean:
	@echo *** Cleaning $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake CLEAN /F "Lego.mak" CFG="Lego - $(CONFIGURATION) RL20" /nologo 
	@cd $(MAKEDIR)
	@echo *** Cleaning $(@B) $(CONFIGURATION) done

### LegoRL40 ----------------------------------------------------------------
$(LegoDir)\LegoRL40.build:
	@echo *** Building $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake ALL /F "Lego.mak" CFG="Lego - $(CONFIGURATION) RL40" /nologo 
	@cd $(MAKEDIR)
	@echo *** Building $(@B) $(CONFIGURATION) done

$(LegoDir)\LegoRL40.clean:
	@echo *** Cleaning $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake CLEAN /F "Lego.mak" CFG="Lego - $(CONFIGURATION) RL40" /nologo 
	@cd $(MAKEDIR)
	@echo *** Cleaning $(@B) $(CONFIGURATION) done

### ROIInspectorRL20 ----------------------------------------------------------------
$(ROIInspectorDir)\ROIInspectorRL20.build:
	@echo *** Building $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake ALL /F "ROIInspector.mak" CFG="ROIInspector - $(CONFIGURATION) RL20" /nologo 
	@cd $(MAKEDIR)
	@echo *** Building $(@B) $(CONFIGURATION) done

$(ROIInspectorDir)\ROIInspectorRL20.clean:
	@echo *** Cleaning $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake CLEAN /F "ROIInspector.mak" CFG="ROIInspector - $(CONFIGURATION) RL20" /nologo 
	@cd $(MAKEDIR)
	@echo *** Cleaning $(@B) $(CONFIGURATION) done

### ROIInspectorRL40 ----------------------------------------------------------------
$(ROIInspectorDir)\ROIInspectorRL40.build:
	@echo *** Building $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake ALL /F "ROIInspector.mak" CFG="ROIInspector - $(CONFIGURATION) RL40" /nologo 
	@cd $(MAKEDIR)
	@echo *** Building $(@B) $(CONFIGURATION) done

$(ROIInspectorDir)\ROIInspectorRL40.clean:
	@echo *** Cleaning $(@B) $(CONFIGURATION)...
	@cd $(@D)
	@-nmake CLEAN /F "ROIInspector.mak" CFG="ROIInspector - $(CONFIGURATION) RL40" /nologo 
	@cd $(MAKEDIR)
	@echo *** Cleaning $(@B) $(CONFIGURATION) done
