#ifndef _H_NLOG_H_
#define _H_NLOG_H_

#include <android/log.h>

#define NLOG_LEVEL_VERBOSE 1
#define NLOG_LEVEL_DEBUG 2
#define NLOG_LEVEL_INFO 3
#define NLOG_LEVEL_WARNING 4
#define NLOG_LEVEL_ERROR 5
#define NLOG_LEVEL_FATAL 6
#define NLOG_LEVEL_SILENT 7

#ifndef NLOG_TAG
#   define NLOG_TAG __FILE__
#endif

#ifndef NLOG_LEVEL
#   define NLOG_LEVEL NLOG_LEVEL_VERBOSE
#endif

#define NLOG_NOOP (void) 0


#define NLOG_PRINT(level, tag, fmt, ...) \
    __android_log_print(level, tag, "(%s:%u) %s: " fmt, \
    __FILE__, __LINE__, __PRETTY_FUNCTION__, ##__VA_ARGS__)

#if NLOG_LEVEL_VERBOSE >= NLOG_LEVEL
#   define NLOG_VERBOSE(tag, fmt, ...) NLOG_PRINT(ANDROID_LOG_VERBOSE, tag, fmt, ##__VA_ARGS__)
#else
#   define NLOG_VERBOSE(...) NLOG_NOOP
#endif

#if NLOG_LEVEL_DEBUG >= NLOG_LEVEL
#   define NLOG_DEBUG(tag, fmt, ...) NLOG_PRINT(ANDROID_LOG_DEBUG, tag, fmt, ##__VA_ARGS__)132
#else
#   define NLOG_DEBUG(...) NLOG_NOOP
#endif

#if NLOG_LEVEL_INFO >= NLOG_LEVEL
#   define NLOG_INFO(tag, fmt, ...) NLOG_PRINT(ANDROID_LOG_INFO, tag, fmt, ##__VA_ARGS__)
#else
#   define NLOG_INFO(...) NLOG_NOOP
#endif

#if NLOG_LEVEL_WARNING >= NLOG_LEVEL
#   define NLOG_WARNING(tag, fmt, ...) NLOG_PRINT(ANDROID_LOG_WARN, tag, fmt, ##__VA_ARGS__)
#else
#   define NLOG_WARNING(...) NLOG_NOOP
#endif

#if NLOG_LEVEL_ERROR >= NLOG_LEVEL
#   define NLOG_ERROR(tag, fmt, ...) NLOG_PRINT(ANDROID_LOG_ERROR, tag, fmt, ##__VA_ARGS__)
#else
#   define NLOG_ERROR(...) NLOG_NOOP
#endif


#if NLOG_LEVEL_FATAL >= NLOG_LEVEL
#   define NLOG_FATAL(tag, fmt, ...) NLOG_PRINT(ANDROID_LOG_FATAL, tag, fmt, ##__VA_ARGS__)
#else
#   define NLOG_FATAL(...) NLOG_NOOP
#endif

#if NLOG_LEVEL_FATAL >= NLOG_LEVEL
#   define NLOG_ASSERT(expression, fmt, ...) \
    if (!(expression)) \
    { \
        __android_log_assert(#expression, NLOG_TAG, fmt, ##__VA_ARGS__); \
    }
#else
#   define NLOG_ASSERT(...) NLOG_NOOP
#endif

#endif
