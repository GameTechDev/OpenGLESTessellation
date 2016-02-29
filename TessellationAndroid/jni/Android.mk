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

CPUT_PATH        := $(LOCAL_PATH)/../../CPUT/CPUT

LOCAL_MODULE     := cput_sample
LOCAL_SRC_FILES  := main.cpp
LOCAL_C_INCLUDES := $(CPUT_PATH)
LOCAL_LDLIBS     := -llog -landroid -lEGL
LOCAL_STATIC_LIBRARIES := android_native_app_glue CPUTAndroid
LOCAL_CFLAGS    := -std=c++11
LOCAL_CFLAGS    += -DCPUT_OS_ANDROID -DCPUT_FOR_OGLES

ifeq ($(APP_GL_VERSION), GLES2)
LOCAL_LDLIBS    += -lGLESv2
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES2
else
ifeq ($(APP_GL_COMPAT), 1)
LOCAL_LDLIBS    += -lGLESv2
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES3
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES3_COMPAT
else
LOCAL_LDLIBS    += -lGLESv3
LOCAL_CFLAGS    += -DCPUT_FOR_OGLES3
endif
endif
ifeq ($(CPUT_DEBUG), 1)
LOCAL_CFLAGS    += -DDEBUG
endif


include $(BUILD_SHARED_LIBRARY)

# Put this makefile include at the end so as not to destroy the LOCAL_PATH variable
include $(CPUT_PATH)/Android.mk

$(call import-module, android/native_app_glue)


