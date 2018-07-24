//
// Created by Joe Chan on 2018/7/24.
//
#include <jni.h>
#include "clog.h"
#include <android/bitmap.h>

extern "C"
JNIEXPORT jobject JNICALL
Java_joe_com_ndktutorial_activity_Tutorial6Activity_grayBitmap(JNIEnv *env, jclass type, jobject bmp) {
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bmp, &info) < 0) { LOGW("Parameter is not Bitmap");
        return NULL;
    }
    uint32_t *pixels;
    if (AndroidBitmap_lockPixels(env, bmp, (void **) (&pixels)) < 0) { LOGW("Bitmap Pixel decode Error");
        return NULL;
    }
    int pixelCount = info.width * info.height;

    uint32_t MODEL;
    uint32_t av;
    for (int i = 0; i < pixelCount; ++i) {
        av = 0;
        uint32_t color = pixels[i];
        if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888/**8888**/) {
            MODEL = 0xFF;
            av += (color & MODEL);
            av += (color >> 8) & MODEL;
            av += (color >> 16) & MODEL;
            av /= 3;
            color = 0xFF00 + av;
            color = (color << 8) + av;
            color = (color << 8) + av;
            pixels[i] = color;
        } else if (info.format == ANDROID_BITMAP_FORMAT_RGB_565/**565**/) {
            av += (color >>= 5) & 0b11111;
            av += (color >>= 6) & 0b111111;
            av += (color >> 5) & 0b11111;
            av /= 3;
            color = av;
            color = (color << 5) + av;
            color = (color << 6) + av;
            pixels[i] = color << 5;
        } else if (info.format == ANDROID_BITMAP_FORMAT_RGBA_4444/**4444**/) {
            MODEL = 0xF;
            av += (color & MODEL);
            av += (color >> 4) & MODEL;
            av += (color >> 8) & MODEL;
            av /= 3;
            color = 0xF0 + av;
            color = (color << 4) + av;
            color = (color << 4) + av;
            pixels[i] = color;
        }
    }

    if (AndroidBitmap_unlockPixels(env, bmp) < 0) { LOGW("unLock Pixel Failed");
    }

    return NULL;
}