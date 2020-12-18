#pragma once
#include "Texture.h"
#include "Util.h"
#include <string>
#include <GLES2/gl2.h>
#include <jni.h>
#include <unordered_map>
#include <vector>

class TextureLoader {
public:
    Texture* GetTextureFromFile(std::string path, std::string fileType = ".png");
    void LoadTextures(JNIEnv* env);
private:
    std::vector<std::string> Paths;
    std::vector<std::string> TextureNames;
    std::unordered_map<std::string, std::unique_ptr<Texture>> Textures;
};


