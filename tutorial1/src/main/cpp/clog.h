//
// Created by Joe Chan on 2017/10/26.
//

#include "android/log.h"

#define LOGD(fmt, ...);  __android_log_print(ANDROID_LOG_DEBUG,"JNI",fmt,##__VA_ARGS__)
#define LOGI(fmt, ...);  __android_log_print(ANDROID_LOG_INFO,"JNI",fmt,##__VA_ARGS__)
#define LOGW(fmt, ...);  __android_log_print(ANDROID_LOG_WARN,"JNI",fmt,##__VA_ARGS__)
#define LOGE(fmt, ...);  __android_log_print(ANDROID_LOG_ERROR,"JNI",fmt,##__VA_ARGS__)

#ifndef NDKTUTORIAL_CLOG_H
#define NDKTUTORIAL_CLOG_H

#endif //NDKTUTORIAL_CLOG_H
