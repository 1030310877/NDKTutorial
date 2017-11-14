//
// Created by Joe Chan on 2017/10/31.
//
#include <jni.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include "clog.h"

pthread_t th;
bool interrupt = false;
JavaVM *gs_jvm = NULL;
jobject javaObject;

void *increase(void *arg) {
    int num = 0;
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);
    while (!interrupt) {
        sleep(1);
        num++;
        jclass jzlass = env->GetObjectClass(javaObject);
        jmethodID mid = env->GetMethodID(jzlass, "setText", "(I)V");
        if (mid != NULL) {
            env->CallVoidMethod(javaObject, mid, num);
        }
    }
    gs_jvm->DetachCurrentThread();
    //退出当前线程
    pthread_exit(NULL);
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial3Activity_startTimerThread(JNIEnv *env, jobject instance) {
    //JNIEnv只是在当前线程生效，因此需要获取Java虚拟机，在子线程中获取
    env->GetJavaVM(&gs_jvm);
    //同样只是当前线程生效，需要将其变成全局变量，在子线程使用
    javaObject = env->NewGlobalRef(instance);
    interrupt = false;
    //创建线程，如有参数需要传递，需将所有参数包装成struct后传入。
    int ret = pthread_create(&th, NULL, increase, NULL/*传递给函数的参数*/);
    if (ret == 0) { LOGI("create thread successfully");
    } else { LOGW("create thread failed"); }
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial3Activity_stopTimerThread(JNIEnv *env, jobject instance) {
    interrupt = true;
}