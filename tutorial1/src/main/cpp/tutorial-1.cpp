#include <jni.h>
#include <stdint.h>
#include "clog.h"

extern "C" JNIEXPORT jstring JNICALL
Java_joe_com_ndktutorial_activity_Tutorial1Activity_newStringFromJNI(JNIEnv *env, jobject instance) {
    return env->NewStringUTF("Hello World");
}

extern "C" JNIEXPORT jint JNICALL
Java_joe_com_ndktutorial_activity_Tutorial1Activity_newIntFromJNI(JNIEnv *env, jobject instance) {
    jint result = 1024;
    return result;
}

extern "C" JNIEXPORT jboolean JNICALL
Java_joe_com_ndktutorial_activity_Tutorial1Activity_newBooleanFromJNI(JNIEnv *env, jobject instance) {
    jboolean result = JNI_TRUE;//JNI_FALSE
    return result;
}

extern "C" JNIEXPORT jintArray JNICALL
Java_joe_com_ndktutorial_activity_Tutorial1Activity_newIntArrayFromJNI(JNIEnv *env, jobject instance) {
    jintArray intArray = env->NewIntArray(5);
    //拿到数组的指针后才能进行操作
    jint *arrayP = env->GetIntArrayElements(intArray, NULL);

    jint len = env->GetArrayLength(intArray);

    LOGD("int array len=%d", len);

    arrayP[0] = 1;
    arrayP[1] = 2;
    arrayP[2] = 3;
    arrayP[3] = 4;
    arrayP[4] = 5;
    return intArray;
}

extern "C" JNIEXPORT jobject JNICALL
Java_joe_com_ndktutorial_activity_Tutorial1Activity_newTestObjectFromJNI(JNIEnv *env, jobject instance) {
    jclass jclazz;
    char classPath[] = "joe/com/ndktutorial/activity/Tutorial1Activity$TestObject";
    //使用包名+类名找到class
    jclazz = env->FindClass(classPath);
    if (jclazz == NULL) { LOGE("can't find the class %s", classPath);
        return NULL;
    }
    //找到默认的构造函数
    jmethodID construct = env->GetMethodID(jclazz, "<init>",
                                           "(Ljoe/com/ndktutorial/activity/Tutorial1Activity;)V");//因为是内部类，所以签名需要写好外部类
    if (construct == NULL) { LOGE("can't find the default construct function");
        return NULL;
    }
    //new出一个Object
    jobject result = env->NewObject(jclazz, construct, NULL);

    //删除局部引用
    env->DeleteLocalRef(jclazz);
    return result;
}