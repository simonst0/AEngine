//
// Created by simon on 05/11/2019.
//

#ifndef MYAPPLICATION_UTIL_H
#define MYAPPLICATION_UTIL_H

#include "glm/glm.hpp"
#include <GLES2/gl2.h>
#include <jni.h>
#include "stb_image.h"
#include "glm/ext.hpp"
#include <android/log.h>
#include <random>

// Der Log-Tag, der im logcat erscheinen soll (man kann dann leicht danach filtern/suchen
#define TAG "NativeGame"
// Hiermit kann man Debug- und Fehler-Log-Messages einfach ins Logcat schreiben
#define log_debug(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##__VA_ARGS__)

#define RandomInt(min, max) min + ( std::rand() % ( max - min + 1 ) )
#define RandomFloat(min, max) min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)))

struct VertexData {
    VertexData(){ x = 0; y = 0;};
    VertexData(GLfloat x, GLfloat y){ this->x = x, this->y = y;}
    GLfloat x, y;
};

struct Color {
    Color(GLfloat r, GLfloat g, GLfloat b, GLfloat a){ this->r = r; this->b = b; this->g = g; this->a = a;}
    GLfloat r, g, b, a;
};

class FileReader
{
public:
   static bool read_asset_file(JNIEnv *env, const char *filename, std::function<void(const char *data, size_t len)> handler)
    {
        jclass loader = env->FindClass("local/fhs/mygame/Loader");
        jmethodID method = env->GetStaticMethodID(loader, "loadFile", "(Ljava/lang/String;)[B");

        jstring path = env->NewStringUTF(filename);
        jbyteArray arr = (jbyteArray)env->CallStaticObjectMethod(loader, method, path);
        int len = env->GetArrayLength(arr);
        jboolean isCopy;
        jbyte *buffer = env->GetByteArrayElements(arr, &isCopy);
        if (len != 0) {
            handler((const char *)buffer, len);
        }
        env->ReleaseByteArrayElements(arr, buffer, JNI_ABORT);

        // Huch! Java verwendet reference counting für JNI.
        env->DeleteLocalRef(path);
        env->DeleteLocalRef(arr);
        env->DeleteLocalRef(loader);

        return (len != 0);
    }

    static std::string read_text_file(JNIEnv *env, const char *filename)
    {
        std::string result;

        bool found = read_asset_file(env, filename, [&] (const char *data, size_t len) {
            result = std::string(data, len);
        });

        return result;
    }
};

#endif //MYAPPLICATION_UTIL_H
