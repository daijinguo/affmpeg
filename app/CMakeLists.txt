#
# a cmake web address
# https://www.cnblogs.com/xianghang123/p/3556425.html
#

cmake_minimum_required(VERSION 3.6)

include_directories( src/main/cpp/ffmpeg/include )

# custom define
#  THIRD_LIB_DIR not work, do not known why
#  set(THIRD_LIB_DIR, ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/ )
#set(CURRENT_DIR ${CMAKE_SOURCE_DIR})
#message( "Third share library ${THIRD_LIB_DIR}" )

add_library( native-lib
             SHARED
             src/main/cpp/ffmpeg_config.cpp
             src/main/cpp/arminfo.cpp
             src/main/cpp/NativePlayer.cpp )

# add ffmpeg lib
## add_library( avcodec SHARED IMPORTED)
## set_target_properties( avcodec PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libavcodec.so )

## add_library( avdevice SHARED IMPORTED)
## set_target_properties( avdevice PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libavdevice.so )

## add_library( avfilter SHARED IMPORTED)
## set_target_properties( avfilter PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libavfilter.so )

## add_library( avformat SHARED IMPORTED)
## set_target_properties( avformat PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libavformat.so )

## add_library( avutil SHARED IMPORTED)
## set_target_properties( avutil PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libavutil.so )

## add_library( swresample SHARED IMPORTED)
## set_target_properties( swresample PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libswresample.so )

## add_library( swscale SHARED IMPORTED)
## set_target_properties( swscale PROPERTIES IMPORTED_LOCATION
##                        ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libswscale.so )


message( ">>>> android abi: ${ANDROID_ABI}" )
message( ">>>> libffmpeg.so : ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libffmpeg.so" )

add_library( ffmpeg SHARED IMPORTED)
set_target_properties( ffmpeg PROPERTIES IMPORTED_LOCATION
                       ${CMAKE_SOURCE_DIR}/jniLibs/${ANDROID_ABI}/libffmpeg.so )


find_library( log-lib  log  z  android)

target_link_libraries( native-lib
                       ${log-lib}
                       z
                       android
                       ffmpeg )

## target_link_libraries( native-lib
##                        ${log-lib}
##                        z
##                        android
##                        avcodec
##                        avdevice
##                        avfilter
##                        avformat
##                        avutil
##                        swscale
##                        swresample )



