#include "Texture.h"
#include "stb_image.h"
#include "Util.h"
#include <android/log.h>

void Texture::Load(JNIEnv *env, std::string path, GLuint textureHandle)
{
    TextureHandle = textureHandle;
    bool found = FileReader::read_asset_file(env, path.c_str(), [=] (const char *data, size_t len) {
        int width, height, channels;

        stbi_uc *pixels = stbi_load_from_memory((stbi_uc const *)data, len, &width, &height, &channels, 4);

        log_debug("pixels=%p, width=%d, height=%d, channels=%d", pixels, width, height, channels);

        glBindTexture(GL_TEXTURE_2D, TextureHandle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        // Bilinear or nearest neighbor?
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Clamp oder repeat; NPOT textures? http://stackoverflow.com/questions/4760174/
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_image_free(pixels);
    });
    if(!found)
        log_debug("texture not found handle %d path %s", TextureHandle, path.c_str());
    else
        log_debug("found texture handle %d", TextureHandle);
}