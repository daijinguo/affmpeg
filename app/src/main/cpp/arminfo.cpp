#include <jni.h>

#include "nlog.h"

#ifndef TAG
#   define TAG "arminfo"
#endif

#ifdef __FILE__
#   undef  __FILE__
#   define __FILE__ "arminfo.cpp"
#endif

extern "C" JNIEXPORT jstring JNICALL
Java_dai_android_ffmpeg_V_FConfigActivity_getAbiInfo(
    JNIEnv *env,
    jobject thiz)
{
#if defined(__arm__)
#   if defined(__ARM_ARCH_7A__)
#       if defined(__ARM_NEON__)
#           define ABI "armeabi-v7a/NEON"
#       else
#           define ABI "armeabi-v7a"
#       endif
#   else
#       define ABI "armeabi"
#   endif
#elif defined(__i386__)
#       define ABI "x86"
#   elif defined(__mips__)
#       define ABI "mips"
#   else
#       define ABI "unknown"
#endif

    NLOG_INFO(TAG, "ABI information: %s\n", ABI);

    return env->NewStringUTF(ABI);
}