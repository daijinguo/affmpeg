
##

LOCAL_PATH := $(call my-dir)

$(warning $(LOCAL_PATH))

## ffmpeg library

#FFMPEG_SO_DIR =
FFMPEG_SO_DIR := ../../../jniLibs/$(APP_ABI)/

##include $(CLEAR_VARS)
##LOCAL_MODULE    := avcodec
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libavcodec.so
##$(warning $(LOCAL_SRC_FILES))
##include $(PREBUILT_SHARED_LIBRARY)

##include $(CLEAR_VARS)
##LOCAL_MODULE    := avdevice
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libavdevice.so
##include $(PREBUILT_SHARED_LIBRARY)

##include $(CLEAR_VARS)
##LOCAL_MODULE    := avfilter
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libavfilter.so
##include $(PREBUILT_SHARED_LIBRARY)

##include $(CLEAR_VARS)
##LOCAL_MODULE    := avformat
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libavformat.so
##include $(PREBUILT_SHARED_LIBRARY)

##include $(CLEAR_VARS)
##LOCAL_MODULE    := avutil
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libavutil.so
##include $(PREBUILT_SHARED_LIBRARY)

##include $(CLEAR_VARS)
##LOCAL_MODULE    := swresample
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libswresample.so
##include $(PREBUILT_SHARED_LIBRARY)

##include $(CLEAR_VARS)
##LOCAL_MODULE    := swscale
##LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libswscale.so
##include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := ffmpeg
LOCAL_SRC_FILES := ${FFMPEG_SO_DIR}libffmpeg.so
include $(PREBUILT_SHARED_LIBRARY)


## program
include $(CLEAR_VARS)

LOCAL_CPP_FEATURES := rtti
LOCAL_CPP_FEATURES := exceptions

LOCAL_MODULE     := native-lib
LOCAL_SRC_FILES  := arminfo.cpp \
                    ffmpeg_config.cpp \
                    NativePlayer.cpp
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ffmpeg/include
LOCAL_LDLIBS     := -llog -lz -landroid
##LOCAL_SHARED_LIBRARIES :=  avcodec avdevice avfilter avformat avutil swresample swscale
LOCAL_SHARED_LIBRARIES :=  ffmpeg
include $(BUILD_SHARED_LIBRARY)
