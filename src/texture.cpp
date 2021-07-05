// STL
#include <iostream>
#include <mutex>

// STB
#define STB_IMAGE_IMPLEMENTATION
#include <textureLoader/stb_image.h>

// Project
#include "texture.h"

Texture::~Texture()
{
    deleteTexture();
}

bool Texture::createFromData(const unsigned char* data, int width, int height, int bytesPerPixel, bool generateMipmaps)
{
    if (IsLoaded) {
        return false;
    }

    Width = width;
    Height = height;
    BytesPerPixel = bytesPerPixel;

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    GLenum internalFormat = 0;
    GLenum format = 0;
    if (BytesPerPixel == 4) {
        internalFormat = format = GL_RGBA;
    }
    else if (BytesPerPixel == 3) {
        internalFormat = format = GL_RGB;
    }
    else if (BytesPerPixel == 1) {
        internalFormat = format = GL_DEPTH_COMPONENT;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, Width, Height, 0, format, GL_UNSIGNED_BYTE, data);

    if (generateMipmaps) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    IsLoaded = true;
    return true;
}

bool Texture::loadTexture2D(const std::string& filePath, bool generateMipmaps)
{

    stbi_set_flip_vertically_on_load(1); // This sometimes screws the texture
    const auto imageData = stbi_load(filePath.c_str(), &Width, &Height, &BytesPerPixel, 0);
    if (imageData == nullptr)
    {
        std::cout << "Failed to load image " << filePath << "!" << std::endl;
        return false;
    }

    auto result = createFromData(imageData, Width, Height, BytesPerPixel, generateMipmaps);
    stbi_image_free(imageData);
    FilePath = filePath;
    return result;
}

void Texture::bind(const int textureUnit) const
{
    if (!isLoadedCheck()) {
        return;
    }

    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, TextureID);
}

void Texture::deleteTexture()
{
    if (!isLoadedCheck()) {
        return;
    }

    glDeleteTextures(1, &TextureID);
    IsLoaded = false;
}

std::string Texture::getFilePath() const
{
    return FilePath;
}

int Texture::getWidth() const
{
    return Width;
}

int Texture::getHeight() const
{
    return Height;
}

int Texture::getBytesPerPixel() const
{
    return BytesPerPixel;
}

int Texture::getNumTextureImageUnits()
{
    static std::once_flag queryOnceFlag;
    static int maxTextureUnits;
    std::call_once(queryOnceFlag, []() {glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits); });
    
    return maxTextureUnits;
}

bool Texture::isLoadedCheck() const
{
    if (!IsLoaded)
    {
        std::cout << "Attempting to access non loaded texture!" << std::endl;
        return false;
    }

    return true;
}
