# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := CPUTAndroid
LOCAL_CFLAGS    := -std=c++11
LOCAL_CFLAGS    += -DCPUT_OS_ANDROID -DCPUT_FOR_OGLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue CPUTAndroid

ifeq ($(APP_GL_VERSION), GLES2)
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES2
else
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES3 -DKTX_OPENGL_ES3=1 -DSUPPORT_SOFTWARE_ETC_UNPACK=0
ifeq ($(APP_GL_COMPAT), 1)
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES3_COMPAT
endif
endif
ifeq ($(CPUT_DEBUG), 1)
LOCAL_CFLAGS    += -DDEBUG
endif

LOCAL_C_INCLUDES := $(LOCAL_PATH)/. 

LOCAL_SRC_FILES := 	CPUTAnimation.cpp\
	CPUTAssetLibrary.cpp \
	CPUTAssetLibraryOGL.cpp \
	CPUTAssetSet.cpp \
	CPUTBufferOGL.cpp \
	CPUTButton.cpp \
	CPUTCamera.cpp \
	CPUTCheckbox.cpp \
	CPUTConfigBlock.cpp \
	CPUTControl.cpp \
	CPUTDropdown.cpp \
	CPUTFont.cpp \
	CPUTFontOGL.cpp \
	CPUTFrustum.cpp \
	CPUTGuiController.cpp \
	CPUTGuiControllerOGL.cpp \
	CPUTITTTaskMarker.cpp \
	CPUTLight.cpp \
	CPUTMaterial.cpp \
	CPUTMaterialEffect.cpp \
	CPUTMaterialEffectOGL.cpp \
 	CPUTMesh.cpp \
	CPUTMeshOGL.cpp \
	CPUTModel.cpp \
	CPUTModelOGL.cpp \
	CPUTNullNode.cpp \
	CPUT_OGL.cpp \
	CPUT_OGL_GLES.cpp \
	CPUTOSServicesLinux.cpp \
	CPUTParser.cpp \
	CPUTPerfTaskMarker.cpp \
	CPUTRenderNode.cpp \
	CPUTRenderStateBlock.cpp \
	CPUTRenderStateBlockOGL.cpp \
	CPUTRenderTargetOGL.cpp \
	CPUTScene.cpp \
	CPUTShader.cpp \
	CPUTShaderOGL.cpp \
	CPUTSlider.cpp \
	CPUTText.cpp \
	CPUTSprite.cpp \
	CPUTSpriteOGL.cpp \
	CPUTTexture.cpp \
	CPUTTextureOGL.cpp \
	CPUTTimerLinux.cpp \
	CPUTWindowAndroid.cpp \
	../middleware/stb/stb_image.c \
	../middleware/libktx/checkheader.c \
	../middleware/libktx/hashtable.c \
	../middleware/libktx/loader.c \
	../middleware/libktx/swap.c \
	../middleware/libktx/writer.c \
	../middleware/ndk_helper/JNIHelper.cpp \
	../middleware/ndk_helper/gestureDetector.cpp \
	../middleware/ndk_helper/vecmath.cpp
include $(BUILD_STATIC_LIBRARY)

