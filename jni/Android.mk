LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_CFLAGS += -D__STDC_CONSTANT_MACROS
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/3rdparty/lame/include 

LOCAL_SRC_FILES = \
./mp3_encoder/jni/AudioEncoder.cpp 

LOCAL_STATIC_LIBRARIES := libmp3_encoder

LOCAL_LDFLAGS += $(LOCAL_PATH)/3rdparty/lame/lib/libmp3lame.a

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog 
LOCAL_LDLIBS += -lz 
LOCAL_LDLIBS += -landroid 
LOCAL_LDLIBS += -L$(LOCAL_PATH)/3rdparty/lame/lib -lmp3lame

LOCAL_MODULE := libaudioencoder
include $(BUILD_SHARED_LIBRARY)
include $(call all-makefiles-under,$(LOCAL_PATH))