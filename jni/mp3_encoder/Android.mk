LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_ARM_MODE := arm 
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../3rdparty/lame/include 
LOCAL_CFLAGS := -DHAVE_CONFIG_H -DFPM_ARM -ffast-math -O3 

LOCAL_SRC_FILES += \
./libmp3_encoder/mp3_encoder.cpp 
    
LOCAL_MODULE := libmp3_encoder
include $(BUILD_STATIC_LIBRARY)