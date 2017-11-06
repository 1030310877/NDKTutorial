//
// Created by Joe Chan on 2017/11/3.
//

#include <jni.h>
#include <stdio.h>
#include <string.h>
#include "clog.h"

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial4Activity_writeToFile(JNIEnv *env, jobject instance,
                                                                jstring file_, jstring content_) {
    const char *file = env->GetStringUTFChars(file_, 0);
    const char *content = env->GetStringUTFChars(content_, 0);

    FILE *fp = fopen(file, "w+");
    if (fp != NULL) {
        ssize_t ret = fwrite(content, strlen(content), 1, fp);
        if (ret == -1) { LOGE("write error"); }
        else { LOGD("write successfully"); }
        fclose(fp);
    }
    env->ReleaseStringUTFChars(file_, file);
    env->ReleaseStringUTFChars(content_, content);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_joe_com_ndktutorial_activity_Tutorial4Activity_readFromFile(JNIEnv *env, jobject instance,
                                                                 jstring file_) {
    const char *file = env->GetStringUTFChars(file_, 0);
    FILE *fp = fopen(file, "r");
    jstring result = NULL;
    if (fp == NULL) { LOGE("open file error");
    } else {
        fseek(fp, 0, SEEK_END);
        long file_len = ftell(fp);
        char *content = new char[file_len + 1];
        memset(content, 0, (unsigned int) file_len);
        rewind(fp); // 重置文件指针
        ssize_t ret = fread(content, file_len, 1, fp);
        if (ret == -1) { LOGE("read error");
        } else {
            content[file_len] = '\0';//手动追加'\0'的结束标识
            result = env->NewStringUTF(content);
        }
        fclose(fp);
    }
    env->ReleaseStringUTFChars(file_, file);
    return result;
}