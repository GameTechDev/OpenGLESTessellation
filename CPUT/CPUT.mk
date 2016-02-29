##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=CPUT
ConfigurationName      :=Debug
WorkspacePath          := "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/SampleStartCPUT"
ProjectPath            := "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT"
IntermediateDirectory  :=obj/Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=d
Date                   :=10/02/2013
CodeLitePath           :="/home/d/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=lib/libCPUT_32D.a
Preprocessors          :=$(PreprocessorSwitch)DEBUG $(PreprocessorSwitch)_DEBUG $(PreprocessorSwitch)CPUT_OS_LINUX $(PreprocessorSwitch)CPUT_FOR_OGL 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="CPUT.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -s
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./CPUT $(IncludeSwitch)./gli $(IncludeSwitch)./glm 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -std=c++0x -fpermissive $(Preprocessors)
CFLAGS   :=  -g -std=c++0x -fpermissive $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTAssetSet$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTButton$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTCamera$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTCheckbox$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTConfigBlock$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTControl$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTDropdown$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTFont$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTFrustum$(ObjectSuffix) \
	$(IntermediateDirectory)/CPUT_CPUTGuiController$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTLight$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTMaterial$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTMesh$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTModel$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTNullNode$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(ObjectSuffix) \
	$(IntermediateDirectory)/CPUT_CPUTRenderNode$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTSlider$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTText$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTTexture$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTTimerLinux$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTWindowX$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUT_OGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(ObjectSuffix) \
	$(IntermediateDirectory)/CPUT_CPUTModelOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTMeshOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTBufferOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTShaderOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTTextureOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTFontOGL$(ObjectSuffix) $(IntermediateDirectory)/CPUT_CPUTScene$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/SampleStartCPUT/.build-debug"
	@echo rebuilt > "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/SampleStartCPUT/.build-debug/CPUT"

obj/Debug:
	@test -d obj/Debug || $(MakeDirCommand) obj/Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(ObjectSuffix): CPUT/CPUTAssetLibrary.cpp $(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTAssetLibrary.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(DependSuffix): CPUT/CPUTAssetLibrary.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(DependSuffix) -MM "CPUT/CPUTAssetLibrary.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(PreprocessSuffix): CPUT/CPUTAssetLibrary.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(PreprocessSuffix) "CPUT/CPUTAssetLibrary.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetSet$(ObjectSuffix): CPUT/CPUTAssetSet.cpp $(IntermediateDirectory)/CPUT_CPUTAssetSet$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTAssetSet.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTAssetSet$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTAssetSet$(DependSuffix): CPUT/CPUTAssetSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTAssetSet$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTAssetSet$(DependSuffix) -MM "CPUT/CPUTAssetSet.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetSet$(PreprocessSuffix): CPUT/CPUTAssetSet.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTAssetSet$(PreprocessSuffix) "CPUT/CPUTAssetSet.cpp"

$(IntermediateDirectory)/CPUT_CPUTButton$(ObjectSuffix): CPUT/CPUTButton.cpp $(IntermediateDirectory)/CPUT_CPUTButton$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTButton.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTButton$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTButton$(DependSuffix): CPUT/CPUTButton.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTButton$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTButton$(DependSuffix) -MM "CPUT/CPUTButton.cpp"

$(IntermediateDirectory)/CPUT_CPUTButton$(PreprocessSuffix): CPUT/CPUTButton.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTButton$(PreprocessSuffix) "CPUT/CPUTButton.cpp"

$(IntermediateDirectory)/CPUT_CPUTCamera$(ObjectSuffix): CPUT/CPUTCamera.cpp $(IntermediateDirectory)/CPUT_CPUTCamera$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTCamera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTCamera$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTCamera$(DependSuffix): CPUT/CPUTCamera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTCamera$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTCamera$(DependSuffix) -MM "CPUT/CPUTCamera.cpp"

$(IntermediateDirectory)/CPUT_CPUTCamera$(PreprocessSuffix): CPUT/CPUTCamera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTCamera$(PreprocessSuffix) "CPUT/CPUTCamera.cpp"

$(IntermediateDirectory)/CPUT_CPUTCheckbox$(ObjectSuffix): CPUT/CPUTCheckbox.cpp $(IntermediateDirectory)/CPUT_CPUTCheckbox$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTCheckbox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTCheckbox$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTCheckbox$(DependSuffix): CPUT/CPUTCheckbox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTCheckbox$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTCheckbox$(DependSuffix) -MM "CPUT/CPUTCheckbox.cpp"

$(IntermediateDirectory)/CPUT_CPUTCheckbox$(PreprocessSuffix): CPUT/CPUTCheckbox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTCheckbox$(PreprocessSuffix) "CPUT/CPUTCheckbox.cpp"

$(IntermediateDirectory)/CPUT_CPUTConfigBlock$(ObjectSuffix): CPUT/CPUTConfigBlock.cpp $(IntermediateDirectory)/CPUT_CPUTConfigBlock$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTConfigBlock.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTConfigBlock$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTConfigBlock$(DependSuffix): CPUT/CPUTConfigBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTConfigBlock$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTConfigBlock$(DependSuffix) -MM "CPUT/CPUTConfigBlock.cpp"

$(IntermediateDirectory)/CPUT_CPUTConfigBlock$(PreprocessSuffix): CPUT/CPUTConfigBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTConfigBlock$(PreprocessSuffix) "CPUT/CPUTConfigBlock.cpp"

$(IntermediateDirectory)/CPUT_CPUTControl$(ObjectSuffix): CPUT/CPUTControl.cpp $(IntermediateDirectory)/CPUT_CPUTControl$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTControl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTControl$(DependSuffix): CPUT/CPUTControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTControl$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTControl$(DependSuffix) -MM "CPUT/CPUTControl.cpp"

$(IntermediateDirectory)/CPUT_CPUTControl$(PreprocessSuffix): CPUT/CPUTControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTControl$(PreprocessSuffix) "CPUT/CPUTControl.cpp"

$(IntermediateDirectory)/CPUT_CPUTDropdown$(ObjectSuffix): CPUT/CPUTDropdown.cpp $(IntermediateDirectory)/CPUT_CPUTDropdown$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTDropdown.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTDropdown$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTDropdown$(DependSuffix): CPUT/CPUTDropdown.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTDropdown$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTDropdown$(DependSuffix) -MM "CPUT/CPUTDropdown.cpp"

$(IntermediateDirectory)/CPUT_CPUTDropdown$(PreprocessSuffix): CPUT/CPUTDropdown.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTDropdown$(PreprocessSuffix) "CPUT/CPUTDropdown.cpp"

$(IntermediateDirectory)/CPUT_CPUTFont$(ObjectSuffix): CPUT/CPUTFont.cpp $(IntermediateDirectory)/CPUT_CPUTFont$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTFont.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTFont$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTFont$(DependSuffix): CPUT/CPUTFont.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTFont$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTFont$(DependSuffix) -MM "CPUT/CPUTFont.cpp"

$(IntermediateDirectory)/CPUT_CPUTFont$(PreprocessSuffix): CPUT/CPUTFont.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTFont$(PreprocessSuffix) "CPUT/CPUTFont.cpp"

$(IntermediateDirectory)/CPUT_CPUTFrustum$(ObjectSuffix): CPUT/CPUTFrustum.cpp $(IntermediateDirectory)/CPUT_CPUTFrustum$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTFrustum.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTFrustum$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTFrustum$(DependSuffix): CPUT/CPUTFrustum.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTFrustum$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTFrustum$(DependSuffix) -MM "CPUT/CPUTFrustum.cpp"

$(IntermediateDirectory)/CPUT_CPUTFrustum$(PreprocessSuffix): CPUT/CPUTFrustum.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTFrustum$(PreprocessSuffix) "CPUT/CPUTFrustum.cpp"

$(IntermediateDirectory)/CPUT_CPUTGuiController$(ObjectSuffix): CPUT/CPUTGuiController.cpp $(IntermediateDirectory)/CPUT_CPUTGuiController$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTGuiController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTGuiController$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTGuiController$(DependSuffix): CPUT/CPUTGuiController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTGuiController$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTGuiController$(DependSuffix) -MM "CPUT/CPUTGuiController.cpp"

$(IntermediateDirectory)/CPUT_CPUTGuiController$(PreprocessSuffix): CPUT/CPUTGuiController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTGuiController$(PreprocessSuffix) "CPUT/CPUTGuiController.cpp"

$(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(ObjectSuffix): CPUT/CPUTITTTaskMarker.cpp $(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTITTTaskMarker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(DependSuffix): CPUT/CPUTITTTaskMarker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(DependSuffix) -MM "CPUT/CPUTITTTaskMarker.cpp"

$(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(PreprocessSuffix): CPUT/CPUTITTTaskMarker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(PreprocessSuffix) "CPUT/CPUTITTTaskMarker.cpp"

$(IntermediateDirectory)/CPUT_CPUTLight$(ObjectSuffix): CPUT/CPUTLight.cpp $(IntermediateDirectory)/CPUT_CPUTLight$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTLight.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTLight$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTLight$(DependSuffix): CPUT/CPUTLight.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTLight$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTLight$(DependSuffix) -MM "CPUT/CPUTLight.cpp"

$(IntermediateDirectory)/CPUT_CPUTLight$(PreprocessSuffix): CPUT/CPUTLight.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTLight$(PreprocessSuffix) "CPUT/CPUTLight.cpp"

$(IntermediateDirectory)/CPUT_CPUTMaterial$(ObjectSuffix): CPUT/CPUTMaterial.cpp $(IntermediateDirectory)/CPUT_CPUTMaterial$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTMaterial.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTMaterial$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTMaterial$(DependSuffix): CPUT/CPUTMaterial.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTMaterial$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTMaterial$(DependSuffix) -MM "CPUT/CPUTMaterial.cpp"

$(IntermediateDirectory)/CPUT_CPUTMaterial$(PreprocessSuffix): CPUT/CPUTMaterial.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTMaterial$(PreprocessSuffix) "CPUT/CPUTMaterial.cpp"

$(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(ObjectSuffix): CPUT/CPUTMaterialOGL.cpp $(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTMaterialOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(DependSuffix): CPUT/CPUTMaterialOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(DependSuffix) -MM "CPUT/CPUTMaterialOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(PreprocessSuffix): CPUT/CPUTMaterialOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(PreprocessSuffix) "CPUT/CPUTMaterialOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTMesh$(ObjectSuffix): CPUT/CPUTMesh.cpp $(IntermediateDirectory)/CPUT_CPUTMesh$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTMesh.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTMesh$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTMesh$(DependSuffix): CPUT/CPUTMesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTMesh$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTMesh$(DependSuffix) -MM "CPUT/CPUTMesh.cpp"

$(IntermediateDirectory)/CPUT_CPUTMesh$(PreprocessSuffix): CPUT/CPUTMesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTMesh$(PreprocessSuffix) "CPUT/CPUTMesh.cpp"

$(IntermediateDirectory)/CPUT_CPUTModel$(ObjectSuffix): CPUT/CPUTModel.cpp $(IntermediateDirectory)/CPUT_CPUTModel$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTModel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTModel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTModel$(DependSuffix): CPUT/CPUTModel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTModel$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTModel$(DependSuffix) -MM "CPUT/CPUTModel.cpp"

$(IntermediateDirectory)/CPUT_CPUTModel$(PreprocessSuffix): CPUT/CPUTModel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTModel$(PreprocessSuffix) "CPUT/CPUTModel.cpp"

$(IntermediateDirectory)/CPUT_CPUTNullNode$(ObjectSuffix): CPUT/CPUTNullNode.cpp $(IntermediateDirectory)/CPUT_CPUTNullNode$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTNullNode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTNullNode$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTNullNode$(DependSuffix): CPUT/CPUTNullNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTNullNode$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTNullNode$(DependSuffix) -MM "CPUT/CPUTNullNode.cpp"

$(IntermediateDirectory)/CPUT_CPUTNullNode$(PreprocessSuffix): CPUT/CPUTNullNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTNullNode$(PreprocessSuffix) "CPUT/CPUTNullNode.cpp"

$(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(ObjectSuffix): CPUT/CPUTOSServicesLinux.cpp $(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTOSServicesLinux.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(DependSuffix): CPUT/CPUTOSServicesLinux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(DependSuffix) -MM "CPUT/CPUTOSServicesLinux.cpp"

$(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(PreprocessSuffix): CPUT/CPUTOSServicesLinux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(PreprocessSuffix) "CPUT/CPUTOSServicesLinux.cpp"

$(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(ObjectSuffix): CPUT/CPUTPerfTaskMarker.cpp $(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTPerfTaskMarker.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(DependSuffix): CPUT/CPUTPerfTaskMarker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(DependSuffix) -MM "CPUT/CPUTPerfTaskMarker.cpp"

$(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(PreprocessSuffix): CPUT/CPUTPerfTaskMarker.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(PreprocessSuffix) "CPUT/CPUTPerfTaskMarker.cpp"

$(IntermediateDirectory)/CPUT_CPUTRenderNode$(ObjectSuffix): CPUT/CPUTRenderNode.cpp $(IntermediateDirectory)/CPUT_CPUTRenderNode$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTRenderNode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTRenderNode$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTRenderNode$(DependSuffix): CPUT/CPUTRenderNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTRenderNode$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTRenderNode$(DependSuffix) -MM "CPUT/CPUTRenderNode.cpp"

$(IntermediateDirectory)/CPUT_CPUTRenderNode$(PreprocessSuffix): CPUT/CPUTRenderNode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTRenderNode$(PreprocessSuffix) "CPUT/CPUTRenderNode.cpp"

$(IntermediateDirectory)/CPUT_CPUTSlider$(ObjectSuffix): CPUT/CPUTSlider.cpp $(IntermediateDirectory)/CPUT_CPUTSlider$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTSlider.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTSlider$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTSlider$(DependSuffix): CPUT/CPUTSlider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTSlider$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTSlider$(DependSuffix) -MM "CPUT/CPUTSlider.cpp"

$(IntermediateDirectory)/CPUT_CPUTSlider$(PreprocessSuffix): CPUT/CPUTSlider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTSlider$(PreprocessSuffix) "CPUT/CPUTSlider.cpp"

$(IntermediateDirectory)/CPUT_CPUTText$(ObjectSuffix): CPUT/CPUTText.cpp $(IntermediateDirectory)/CPUT_CPUTText$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTText.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTText$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTText$(DependSuffix): CPUT/CPUTText.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTText$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTText$(DependSuffix) -MM "CPUT/CPUTText.cpp"

$(IntermediateDirectory)/CPUT_CPUTText$(PreprocessSuffix): CPUT/CPUTText.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTText$(PreprocessSuffix) "CPUT/CPUTText.cpp"

$(IntermediateDirectory)/CPUT_CPUTTexture$(ObjectSuffix): CPUT/CPUTTexture.cpp $(IntermediateDirectory)/CPUT_CPUTTexture$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTTexture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTTexture$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTTexture$(DependSuffix): CPUT/CPUTTexture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTTexture$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTTexture$(DependSuffix) -MM "CPUT/CPUTTexture.cpp"

$(IntermediateDirectory)/CPUT_CPUTTexture$(PreprocessSuffix): CPUT/CPUTTexture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTTexture$(PreprocessSuffix) "CPUT/CPUTTexture.cpp"

$(IntermediateDirectory)/CPUT_CPUTTimerLinux$(ObjectSuffix): CPUT/CPUTTimerLinux.cpp $(IntermediateDirectory)/CPUT_CPUTTimerLinux$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTTimerLinux.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTTimerLinux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTTimerLinux$(DependSuffix): CPUT/CPUTTimerLinux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTTimerLinux$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTTimerLinux$(DependSuffix) -MM "CPUT/CPUTTimerLinux.cpp"

$(IntermediateDirectory)/CPUT_CPUTTimerLinux$(PreprocessSuffix): CPUT/CPUTTimerLinux.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTTimerLinux$(PreprocessSuffix) "CPUT/CPUTTimerLinux.cpp"

$(IntermediateDirectory)/CPUT_CPUTWindowX$(ObjectSuffix): CPUT/CPUTWindowX.cpp $(IntermediateDirectory)/CPUT_CPUTWindowX$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTWindowX.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTWindowX$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTWindowX$(DependSuffix): CPUT/CPUTWindowX.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTWindowX$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTWindowX$(DependSuffix) -MM "CPUT/CPUTWindowX.cpp"

$(IntermediateDirectory)/CPUT_CPUTWindowX$(PreprocessSuffix): CPUT/CPUTWindowX.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTWindowX$(PreprocessSuffix) "CPUT/CPUTWindowX.cpp"

$(IntermediateDirectory)/CPUT_CPUT_OGL$(ObjectSuffix): CPUT/CPUT_OGL.cpp $(IntermediateDirectory)/CPUT_CPUT_OGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUT_OGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUT_OGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUT_OGL$(DependSuffix): CPUT/CPUT_OGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUT_OGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUT_OGL$(DependSuffix) -MM "CPUT/CPUT_OGL.cpp"

$(IntermediateDirectory)/CPUT_CPUT_OGL$(PreprocessSuffix): CPUT/CPUT_OGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUT_OGL$(PreprocessSuffix) "CPUT/CPUT_OGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(ObjectSuffix): CPUT/CPUTRenderStateBlock.cpp $(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTRenderStateBlock.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(DependSuffix): CPUT/CPUTRenderStateBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(DependSuffix) -MM "CPUT/CPUTRenderStateBlock.cpp"

$(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(PreprocessSuffix): CPUT/CPUTRenderStateBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(PreprocessSuffix) "CPUT/CPUTRenderStateBlock.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(ObjectSuffix): CPUT/CPUTAssetSetOGL.cpp $(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTAssetSetOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(DependSuffix): CPUT/CPUTAssetSetOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(DependSuffix) -MM "CPUT/CPUTAssetSetOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(PreprocessSuffix): CPUT/CPUTAssetSetOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(PreprocessSuffix) "CPUT/CPUTAssetSetOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(ObjectSuffix): CPUT/CPUTAssetLibraryOGL.cpp $(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTAssetLibraryOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(DependSuffix): CPUT/CPUTAssetLibraryOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(DependSuffix) -MM "CPUT/CPUTAssetLibraryOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(PreprocessSuffix): CPUT/CPUTAssetLibraryOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(PreprocessSuffix) "CPUT/CPUTAssetLibraryOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTModelOGL$(ObjectSuffix): CPUT/CPUTModelOGL.cpp $(IntermediateDirectory)/CPUT_CPUTModelOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTModelOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTModelOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTModelOGL$(DependSuffix): CPUT/CPUTModelOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTModelOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTModelOGL$(DependSuffix) -MM "CPUT/CPUTModelOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTModelOGL$(PreprocessSuffix): CPUT/CPUTModelOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTModelOGL$(PreprocessSuffix) "CPUT/CPUTModelOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTMeshOGL$(ObjectSuffix): CPUT/CPUTMeshOGL.cpp $(IntermediateDirectory)/CPUT_CPUTMeshOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTMeshOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTMeshOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTMeshOGL$(DependSuffix): CPUT/CPUTMeshOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTMeshOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTMeshOGL$(DependSuffix) -MM "CPUT/CPUTMeshOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTMeshOGL$(PreprocessSuffix): CPUT/CPUTMeshOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTMeshOGL$(PreprocessSuffix) "CPUT/CPUTMeshOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTBufferOGL$(ObjectSuffix): CPUT/CPUTBufferOGL.cpp $(IntermediateDirectory)/CPUT_CPUTBufferOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTBufferOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTBufferOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTBufferOGL$(DependSuffix): CPUT/CPUTBufferOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTBufferOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTBufferOGL$(DependSuffix) -MM "CPUT/CPUTBufferOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTBufferOGL$(PreprocessSuffix): CPUT/CPUTBufferOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTBufferOGL$(PreprocessSuffix) "CPUT/CPUTBufferOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTTextureOGL$(ObjectSuffix): CPUT/CPUTTextureOGL.cpp $(IntermediateDirectory)/CPUT_CPUTTextureOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTTextureOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTTextureOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTTextureOGL$(DependSuffix): CPUT/CPUTTextureOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTTextureOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTTextureOGL$(DependSuffix) -MM "CPUT/CPUTTextureOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTTextureOGL$(PreprocessSuffix): CPUT/CPUTTextureOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTTextureOGL$(PreprocessSuffix) "CPUT/CPUTTextureOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(ObjectSuffix): CPUT/CPUTRenderStateBlockOGL.cpp $(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTRenderStateBlockOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(DependSuffix): CPUT/CPUTRenderStateBlockOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(DependSuffix) -MM "CPUT/CPUTRenderStateBlockOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(PreprocessSuffix): CPUT/CPUTRenderStateBlockOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(PreprocessSuffix) "CPUT/CPUTRenderStateBlockOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTFontOGL$(ObjectSuffix): CPUT/CPUTFontOGL.cpp $(IntermediateDirectory)/CPUT_CPUTFontOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTFontOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTFontOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTFontOGL$(DependSuffix): CPUT/CPUTFontOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTFontOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTFontOGL$(DependSuffix) -MM "CPUT/CPUTFontOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTFontOGL$(PreprocessSuffix): CPUT/CPUTFontOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTFontOGL$(PreprocessSuffix) "CPUT/CPUTFontOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTShaderOGL$(ObjectSuffix): CPUT/CPUTShaderOGL.cpp $(IntermediateDirectory)/CPUT_CPUTShaderOGL$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTShaderOGL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTShaderOGL$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTShaderOGL$(DependSuffix): CPUT/CPUTShaderOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTShaderOGL$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTShaderOGL$(DependSuffix) -MM "CPUT/CPUTShaderOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTShaderOGL$(PreprocessSuffix): CPUT/CPUTShaderOGL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTShaderOGL$(PreprocessSuffix) "CPUT/CPUTShaderOGL.cpp"

$(IntermediateDirectory)/CPUT_CPUTScene$(ObjectSuffix): CPUT/CPUTScene.cpp $(IntermediateDirectory)/CPUT_CPUTScene$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/d/djbookou_ubuntu_456/djbookou_ubuntu_456/depot/projects/Framework/CPUT_Linux/CPUT/CPUT/CPUTScene.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CPUT_CPUTScene$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CPUT_CPUTScene$(DependSuffix): CPUT/CPUTScene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CPUT_CPUTScene$(ObjectSuffix) -MF$(IntermediateDirectory)/CPUT_CPUTScene$(DependSuffix) -MM "CPUT/CPUTScene.cpp"

$(IntermediateDirectory)/CPUT_CPUTScene$(PreprocessSuffix): CPUT/CPUTScene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CPUT_CPUTScene$(PreprocessSuffix) "CPUT/CPUTScene.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetLibrary$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetSet$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetSet$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetSet$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTButton$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTButton$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTButton$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTCamera$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTCamera$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTCamera$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTCheckbox$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTCheckbox$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTCheckbox$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTConfigBlock$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTConfigBlock$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTConfigBlock$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTControl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTControl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTControl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTDropdown$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTDropdown$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTDropdown$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFont$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFont$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFont$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFrustum$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFrustum$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFrustum$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTGuiController$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTGuiController$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTGuiController$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTITTTaskMarker$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTLight$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTLight$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTLight$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMaterial$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMaterial$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMaterial$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMaterialOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMesh$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMesh$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMesh$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTModel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTModel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTModel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTNullNode$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTNullNode$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTNullNode$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTOSServicesLinux$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTPerfTaskMarker$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderNode$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderNode$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderNode$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTSlider$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTSlider$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTSlider$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTText$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTText$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTText$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTexture$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTexture$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTexture$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTimerLinux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTimerLinux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTimerLinux$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTWindowX$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTWindowX$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTWindowX$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUT_OGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUT_OGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUT_OGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlock$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetSetOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTAssetLibraryOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTModelOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTModelOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTModelOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMeshOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMeshOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTMeshOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTBufferOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTBufferOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTBufferOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTextureOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTextureOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTTextureOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTRenderStateBlockOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFontOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFontOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTFontOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTShaderOGL$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTShaderOGL$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTShaderOGL$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTScene$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTScene$(DependSuffix)
	$(RM) $(IntermediateDirectory)/CPUT_CPUTScene$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../SampleStartCPUT/.build-debug/CPUT"


