//
// Created by Joe Chan on 2017/11/15.
//
#include <jni.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "clog.h"

JavaVM *gs_jvm = NULL;
jobject javaObject;

pthread_t th;
bool interrupt = false;
int socketFd, clientFd;

void *createSocketServer(void *arg);

void setReceiveContent(char buf[50]);

extern "C"
JNIEXPORT jint JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_startServer(JNIEnv *env, jobject instance) {
    //JNIEnv只是在当前线程生效，因此需要获取Java虚拟机，在子线程中获取
    env->GetJavaVM(&gs_jvm);
    //同样只是当前线程生效，需要将其变成全局变量，在子线程使用
    javaObject = env->NewGlobalRef(instance);

    int ret = pthread_create(&th, NULL, createSocketServer, NULL);
    if (ret == 0) { LOGI("create thread successfully");
        interrupt = false;
    } else { LOGW("create thread failed"); }
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_stopServer(JNIEnv *env, jobject instance) {
    interrupt = true;
    close(socketFd);
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_startClient(JNIEnv *env, jobject instance) {
    if (clientFd == NULL) {
        clientFd = socket(AF_INET, SOCK_STREAM, 0);
        if (-1 == socketFd) { LOGE("create socket client error"); }
        struct sockaddr_in addrSrv;
        addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");
        addrSrv.sin_family = AF_INET;
        addrSrv.sin_port = htons(9999);
        int ret = connect(clientFd, (const sockaddr *) &addrSrv, sizeof(sockaddr));
        if (ret == -1) { LOGW("client connect failed"); }
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_sendMsg(JNIEnv *env, jobject instance,
                                                            jstring content_) {
    const char *content = env->GetStringUTFChars(content_, 0);
    if (clientFd != NULL) {
        ssize_t len = send(clientFd, content, strlen(content), 0);LOGD("send msg length=%d", (int) len);
    }

    env->ReleaseStringUTFChars(content_, content);
}

void *createSocketServer(void *arg) {
    socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == socketFd) { LOGE("create socket server error");
        pthread_exit(NULL);
    }
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);
    server.sin_addr.s_addr = htonl (INADDR_ANY);

    //调用bind，绑定地址和端口
    if (bind(socketFd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) { LOGE(
                "Bind error.");
        pthread_exit(NULL);
    } else {
        //调用listen，开始监听
        if (listen(socketFd, 3) == -1) { LOGE("listen() error\n");
            pthread_exit(NULL);
        } else { LOGD("server start listen");
            int len = sizeof(sockaddr);
            //接受client连接
            int ret = accept(socketFd, (sockaddr *) &server, (socklen_t *) &len);
            if (ret != -1) { LOGD("accept a client"); }
            char recvBuf[10];
            while (!interrupt) {
                memset(recvBuf, NULL, sizeof(recvBuf));
                ssize_t lenRec = recv(ret, recvBuf, 10, 0);
                if (lenRec > 0) { LOGD("receive content length %d", (int) lenRec);
                    setReceiveContent(recvBuf);
                }
            }
            close(socketFd);
        }
    }
}

void setReceiveContent(char buf[50]) {
    if (buf[0] == '\0') {
        return;
    }
    JNIEnv *env;
    gs_jvm->AttachCurrentThread(&env, NULL);LOGD("receive msg:%s", buf);
    jstring str = env->NewStringUTF(buf);
    jclass jzlass = env->GetObjectClass(javaObject);
    jmethodID mid = env->GetMethodID(jzlass, "setReceiveContent", "(Ljava/lang/String;)V");
    if (mid != NULL) {
        env->CallVoidMethod(javaObject, mid, str);
    }
    env->DeleteLocalRef(jzlass);
    env->DeleteLocalRef(str);
}