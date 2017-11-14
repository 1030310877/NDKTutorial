//
// Created by Joe Chan on 2017/11/15.
//
#include <jni.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "clog.h"

pthread_t th;
bool interrupt = false;
int socketFd;

void *createSocketServer(void *arg);

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_startServer(JNIEnv *env, jobject instance) {

    int ret = pthread_create(&th, NULL, createSocketServer, NULL);
    if (ret == 0) { LOGI("create thread successfully");
    } else { LOGW("create thread failed"); }
}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_startClient(JNIEnv *env, jobject instance) {

    // TODO

}

extern "C"
JNIEXPORT void JNICALL
Java_joe_com_ndktutorial_activity_Tutorial5Activity_sendMsg(JNIEnv *env, jobject instance,
                                                            jstring content_) {
    const char *content = env->GetStringUTFChars(content_, 0);

    // TODO

    env->ReleaseStringUTFChars(content_, content);
}

void *createSocketServer(void *arg) {
    socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == socketFd) { LOGE("create socket server error"); }
    else { pthread_exit(NULL); }
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(9999);
    server.sin_addr.s_addr = htonl (INADDR_ANY);

    if (bind(socketFd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1) {
        //调用bind，绑定地址和端口
        LOGE("Bind error.");
        pthread_exit(NULL);
    } else {
        if (listen(socketFd, 3) == -1) {
            //调用listen，开始监听
            LOGE("listen() error\n");
            pthread_exit(NULL);
        }
    }
}