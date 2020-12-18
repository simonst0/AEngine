#include "TextureLoader.h"

Texture *TextureLoader::GetTextureFromFile(std::string path, std::string fileType)
{
    if(Textures.count(path) == 0)
    {
        Paths.push_back(path+fileType);
        Textures[path] = std::make_unique<Texture>();
        TextureNames.push_back(path);
    }
    else
        log_debug("Attempting to reload Texture with path %s", path.c_str());
    return Textures[path].get();
}

void TextureLoader::LoadTextures(JNIEnv *env)
{
    int pathSize = Paths.size();
    GLuint TextureHandles[pathSize];
    glGenTextures(pathSize, TextureHandles);
    for (int i = 0; i < pathSize; ++i)
        Textures[TextureNames[i]]->Load(env, Paths[i], TextureHandles[i]);
}