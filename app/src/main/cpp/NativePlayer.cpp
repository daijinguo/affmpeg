
#include <jni.h>
#include "nlog.h"

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
}


#include <android/native_window.h>
#include <android/native_window_jni.h>


#ifndef TAG
#   define TAG "nativePlayer"
#endif

#ifdef __FILE__
#   undef  __FILE__
#   define __FILE__ "NativePlayer.cpp"
#endif

#ifndef  TAG
#   define TAG "nplayer"
#endif


extern "C" JNIEXPORT jint JNICALL
Java_dai_android_ffmpeg_player_NativePlayer_playVideo(
    JNIEnv *env,
    jclass clazz,
    jstring url,
    jobject surface)
{

#ifdef __PRETTY_FUNCTION__
#undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ "playVideo"
#else
#   define __PRETTY_FUNCTION__ "playVideo"
#endif

    const char *strUrl = env->GetStringUTFChars(url, JNI_FALSE);
    NLOG_INFO(TAG, "url: %s\n", strUrl);

    av_register_all();

    AVFormatContext *pFormatCtx = avformat_alloc_context();
    if (0 != avformat_open_input(&pFormatCtx, strUrl, NULL, NULL)) {
        NLOG_ERROR(TAG, "Can not open url: %s\n", strUrl);
        return -1;
    }

    if (0 > avformat_find_stream_info(pFormatCtx, NULL)) {
        NLOG_ERROR(TAG, "Can not open url: %s\n", strUrl);
        return -1;
    }

    int videoStream = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; ++i) {
        if (videoStream < 0 && pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
        }
    }

    if (-1 == videoStream) {
        NLOG_ERROR(TAG, "Can not find video stream\n");
        return -1;
    }

    AVCodecContext *pCodecContext = pFormatCtx->streams[videoStream]->codec;
    AVCodec *pCodec = avcodec_find_decoder(pCodecContext->codec_id);
    if (NULL == pCodec) {
        NLOG_ERROR(TAG, "Can not find\n");
        return -1;
    }

    if (0 > avcodec_open2(pCodecContext, pCodec, NULL)) {
        NLOG_ERROR(TAG, "Can not open codec2\n");
        return -1;
    }

    ANativeWindow *pNativeWin = ANativeWindow_fromSurface(env, surface);
    int videoWidth = pCodecContext->width;
    int videoHeight = pCodecContext->height;

    ANativeWindow_setBuffersGeometry(pNativeWin, videoWidth, videoHeight, WINDOW_FORMAT_RGBA_8888);
    ANativeWindow_Buffer winBuffer;
    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameRGBA = av_frame_alloc();
    if (NULL == pFrame || NULL == pFrameRGBA) {
        NLOG_ERROR(TAG, "Can not alloc AVFrame\n");
        return -1;
    }

    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, videoWidth, videoHeight, 1);
    uint8_t *buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));

    av_image_fill_arrays(pFrameRGBA->data,
                         pFrameRGBA->linesize,
                         buffer,
                         AV_PIX_FMT_RGBA,
                         videoWidth,
                         videoHeight,
                         1);

    // not finish @ https://www.imooc.com/article/19699

    struct SwsContext *swsContext = sws_getContext(
        videoWidth,
        videoHeight,
        pCodecContext->pix_fmt,
        videoWidth,
        videoHeight,
        AV_PIX_FMT_RGBA,
        SWS_BILINEAR,
        NULL,
        NULL,
        NULL);

    int frameFinished;
    AVPacket packet;
    while (av_read_frame(pFormatCtx, &packet) >= 0) {
        if (packet.stream_index == videoStream) {
            avcodec_decode_video2(pCodecContext, pFrame, &frameFinished, &packet);
            if (frameFinished) {
                ANativeWindow_lock(pNativeWin, &winBuffer, 0);

                sws_scale(swsContext,
                          (uint8_t const *const *) pFrame->data,
                          pFrame->linesize,
                          0,
                          pCodecContext->height,
                          pFrameRGBA->data,
                          pFrameRGBA->linesize);

                uint8_t *dst = (uint8_t *) winBuffer.bits;
                int dstStride = winBuffer.stride * 4;
                uint8_t *src = (uint8_t *) (pFrameRGBA->data[0]);
                int srcStride = pFrameRGBA->linesize[0];

                int h;
                for (h = 0; h < videoHeight; h++) {
                    memcpy(dst + h * dstStride, src + h * srcStride, srcStride);
                }

                ANativeWindow_unlockAndPost(pNativeWin);
            }
        }

        av_packet_unref(&packet);
    }

    av_free(buffer);
    av_free(pFrameRGBA);
    av_free(pFrame);

    avcodec_close(pCodecContext);
    avformat_close_input(&pFormatCtx);

    return 0;
}
