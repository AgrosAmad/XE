#pragma once

// STL
#include <string>

// GLAD
#include <glad/glad.h>

namespace XE
{
    /**
     *  Wraps OpenGL texture into convenient class.
     */
    class Texture
    {
    public:
        ~Texture();

        /**
         * Creates texture from given raw data.
         *
         * @param data             Pointer to raw data of the texture
         * @param width            Width of the texture
         * @param height           Height of the texture
         * @param bytesPerPixel    Bytes per pixel of the texture
         * @param generateMipmaps  True, if mipmaps should be generated automatically
         *
         * @return True, if texture has been loaded correctly or false otherwise.
         */
        bool createFromData(const unsigned char* data, int width, int height, int bytesPerPixel, bool generateMipmaps = false);

        /**
         * Loads image file as 2D OpenGL texture.
         *
         * @param filePath         Path to an image file
         * @param generateMipmaps  True, if mipmaps should be generated automatically
         *
         * @return True, if the texture has been loaded correctly or false otherwise.
         */
        bool loadTexture2D(const std::string& filePath, bool generateMipmaps = true);

        /**
         * Binds texture to specified texture unit.
         *
         * @param textureUnit  Texture unit index (default is 0)
         */
        void bind(int textureUnit = 0);

        /**
         * Deletes loaded texture from OpenGL. Does nothing if the texture has not been loaded correctly.
         */
        void deleteTexture();

        /**
         * Gets file path of the texture if the texture has been loaded from file.
         *
         * @return File path of the texture or empty string otherwise.
         */
        std::string getFilePath() const;

        /**
         * Gets width of the texture (in pixels).
         */
        int getWidth() const;

        /**
         * Gets height of the texture (in pixels).
         */
        int getHeight() const;

        /**
         * Gets number of bytes each pixel is represented with.
         */
        int getBytesPerPixel() const;

        /**
         * Gets number of available OpenGL texture image units of current hardware.
         */
        static int getNumTextureImageUnits();

        // Gets texture ID in OpenGL-assigned units
        int getTextureUnit() const;

    private:
        GLuint TextureID = 0; // OpenGL-assigned texture ID
        int TextureUnit = 0; // OpenGL-assigned texture unit ID
        int Width = 0; // Width of texture in pixels
        int Height = 0; // Height of texture in pixels
        int BytesPerPixel = 0; // Amount of bytes every pixel is represented with
        bool IsLoaded = false; // Flag holding, if texture has been loaded correctly
        std::string FilePath; // Path of file from which the texture has been loaded (might be empty, if texture was simply created from data)

        /**
         * Checks, if the texture has been loaded correctly and if not, logs it into console.
         *
         * @return True, if texture has been loaded correctly or false otherwise.
         */
        bool isLoadedCheck() const;
    };
} // namespace XE