# this for ndk-build build
# but this replace by cmake

APP_ABI      := armeabi-v7a
APP_PLATFORM := android-27
#APP_STL      := stlport_static
APP_STL      := c++_static
APP_CPPFLAGS += -std=c++14
