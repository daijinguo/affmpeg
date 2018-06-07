#include <jni.h>

#include "nlog.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfilter.h"
}

#include <sstream>

#ifndef TAG
#   define TAG "config"
#endif

#ifdef __FILE__
#   undef  __FILE__
#   define __FILE__ "ffmpeg_config.cpp"
#endif


extern "C" JNIEXPORT jstring JNICALL
Java_dai_android_ffmpeg_V_FConfigActivity_getAvcodecCconfiguration(
    JNIEnv *env,
    jobject thiz)
{
#ifdef __PRETTY_FUNCTION__
#undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ "getAvcodecCconfiguration"
#else
#   define __PRETTY_FUNCTION__ "getAvcodecCconfiguration"
#endif


    char szInfo[1024] = {0x00};
    //const char *pConfig = avcodec_configuration();
    snprintf(szInfo, sizeof(szInfo), "%s\n", avcodec_configuration());
    NLOG_INFO(TAG, "config string: %s", szInfo);

    return env->NewStringUTF(szInfo);
}


struct URLProtocol;

extern "C" JNIEXPORT jstring JNICALL
Java_dai_android_ffmpeg_V_FConfigActivity_urlProtocolInfo(
    JNIEnv *env,
    jobject thiz)
{
#ifdef __PRETTY_FUNCTION__
#undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ "getAvcodecCconfiguration"
#else
#   define __PRETTY_FUNCTION__ "getAvcodecCconfiguration"
#endif

    std::stringstream ss;
    ss << std::endl;

    av_register_all();

    struct URLProtocol *pup = NULL;
    //Input
    struct URLProtocol **p_temp = &pup;
    avio_enum_protocols((void **) p_temp, 0);
    while ((*p_temp) != NULL) {
        char szBuffer[32] = { 0x00 };
        sprintf(szBuffer, "[In ][%12s]\n",  avio_enum_protocols((void **) p_temp, 0));
        ss << szBuffer;
    }
    pup = NULL;
    //Output
    avio_enum_protocols((void **) p_temp, 1);
    while ((*p_temp) != NULL) {
        char szBuffer[32] = { 0x00 };
        sprintf(szBuffer, "[Out][%10s]\n", avio_enum_protocols((void **) p_temp, 1));
        ss << szBuffer;
    }

    const char *pstr = ss.str().c_str();
    NLOG_INFO(TAG, "info2: %s\n", pstr);
    return env->NewStringUTF(pstr);
}


extern "C" JNIEXPORT jstring JNICALL
Java_dai_android_ffmpeg_V_FConfigActivity_avFormatInfo(
    JNIEnv *env,
    jobject thiz)
{
#ifdef __PRETTY_FUNCTION__
#undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ "avFormatInfo"
#else
#   define __PRETTY_FUNCTION__ "avFormatInfo"
#endif

    std::stringstream ss;
    ss << std::endl;

    av_register_all();

    //Input
    AVInputFormat *if_temp = av_iformat_next(NULL);
    while (if_temp != nullptr) {
        char szBuffer[64] = { 0x00 };
        sprintf(szBuffer, "[In ]:[%12s]:",  if_temp->name);
        ss << szBuffer;
        if (nullptr != if_temp->mime_type) {
            ss << if_temp->mime_type;
        }
        ss << std::endl;

        if_temp = if_temp->next;
    }

    //Output
    AVOutputFormat *of_temp = av_oformat_next(NULL);
    while (of_temp != nullptr) {
        char szBuffer[64] = { 0x00 };
        sprintf(szBuffer, "[Out ]:[%12s]",  of_temp->name);
        ss << szBuffer;
        if (nullptr != of_temp->mime_type) {
            ss << of_temp->mime_type;
        }
        ss << std::endl;

        of_temp = of_temp->next;
    }

    const char* pstr = ss.str().c_str();

    NLOG_INFO(TAG, "info1: %s\n", pstr);
    return env->NewStringUTF(pstr);
}

extern "C" JNIEXPORT jstring JNICALL
Java_dai_android_ffmpeg_V_FConfigActivity_avCodecInfo(
    JNIEnv *env,
    jobject thiz)
{
#ifdef __PRETTY_FUNCTION__
#undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ "avCodecInfo"
#else
#   define __PRETTY_FUNCTION__ "avCodecInfo"
#endif

    std::stringstream ss;
    ss << std::endl;

    av_register_all();
    AVCodec *c_temp = av_codec_next(NULL);
    while (c_temp != NULL) {
        if (c_temp->decode != NULL) {
            ss << "[Dec]->";
        }
        else {
            ss << "[Enc]->";
        }

        switch (c_temp->type) {
        case AVMEDIA_TYPE_VIDEO:
            ss << "[Video]:";
            break;
        case AVMEDIA_TYPE_AUDIO:
            ss << "[Audio]:";
            break;
        default:
            ss << "[Other]:";
            break;
        }

        char szBuffer[16] = { 0x00 };
        sprintf(szBuffer, "[%12s]\n", c_temp->name);
        ss << szBuffer;

        c_temp = c_temp->next;
    }

    const char* pStr = ss.str().c_str();

    NLOG_INFO(TAG, "info6: %s\n", pStr);

    return env->NewStringUTF(pStr);
}


extern "C" JNIEXPORT jstring JNICALL
Java_dai_android_ffmpeg_V_FConfigActivity_avFilterInfo(
    JNIEnv *env,
    jobject thiz)
{
#ifdef __PRETTY_FUNCTION__
#undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ "avFilterInfo"
#else
#   define __PRETTY_FUNCTION__ "avFilterInfo"
#endif

    std::stringstream ss;
    ss << std::endl;

    avfilter_register_all();
    AVFilter *f_temp = (AVFilter *) avfilter_next(NULL);
    while (f_temp != NULL) {
        char szBuffer[16] = { 0x00 };
        sprintf(szBuffer, "[%10s]:", f_temp->name);
        ss << szBuffer;
        ss << f_temp->description;
        ss << std::endl;

        f_temp = f_temp->next;
    }

    NLOG_INFO(TAG, "info7: %s\n", ss.str().c_str());

    return env->NewStringUTF(ss.str().c_str());
}