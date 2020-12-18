#pragma  once

#include <string>
#include <GLES2/gl2.h>
#include <jni.h>

class Texture {
public:
    GLuint TextureHandle;
    void Load(JNIEnv *env, std::string path, GLuint textureHandle);
};
