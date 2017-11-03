//
// Created by Joe Chan on 2017/11/1.
//

#include <jni.h>
#include "clog.h"

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial2Activity_callMethod(JNIEnv *env, jobject instance) {
    jclass activity = env->GetObjectClass(instance);
    jmethodID mid = env->GetMethodID(activity, "changeText", "()V");
    if (mid != NULL) {
        env->CallVoidMethod(instance, mid, NULL);
    } else { LOGE("can't find method"); }
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial2Activity_callStaticMethod(JNIEnv *env,
                                                                     jobject instance) {
    jclass activity = env->FindClass("joe/com/ndktutorial/activity/Tutorial2Activity");
    jmethodID mid = env->GetStaticMethodID(activity, "changeStaticText", "()V");
    if (mid != NULL) {
        env->CallStaticVoidMethod(activity, mid, NULL);
    } else { LOGE("can't find method"); }
}