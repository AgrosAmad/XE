#pragma once

// STL
#include <vector>
#include <string>

// GLAD
#include <glad/glad.h>

#define DEFINE_SHADER_CONSTANT(constantName, constantValue) \
static const std::string constantName()                     \
{                                                           \
    static std::string value = constantValue;               \
    return value;                                           \
}

#define DEFINE_SHADER_CONSTANT_INDEX(constantName, constantValue)          \
DEFINE_SHADER_CONSTANT(constantName, constantValue)                        \
static const std::string constantName(const int index)                     \
{                                                                          \
    return std::string(constantValue) + "[" + std::to_string(index) + "]"; \
}

namespace XE
{
    /**
     * Storage for commonly used shaders throughout the tutorials.
     */
    class ShaderKeys
    {
    public:
        DEFINE_SHADER_CONSTANT(ambientLight, "ambientLight");
        DEFINE_SHADER_CONSTANT(diffuseLight, "diffuseLight");
        DEFINE_SHADER_CONSTANT(specularHighlight, "specularHighlight");
        DEFINE_SHADER_CONSTANT(pointLight, "pointLight");
        DEFINE_SHADER_CONSTANT(fog, "fog");
    };

    /**
     * Storage for commonly used constants in shader programs.
     */
    class ShaderConstants
    {
    public:
        // Matrices
        DEFINE_SHADER_CONSTANT(modelMatrix, "mvp.ModelMatrix");
        DEFINE_SHADER_CONSTANT(projectionMatrix, "mvp.ProjectionMatrix");
        DEFINE_SHADER_CONSTANT(viewMatrix, "mvp.ViewMatrix");
        DEFINE_SHADER_CONSTANT(normalMatrix, "mvp.NormalMatrix");

        // Color and textures
        DEFINE_SHADER_CONSTANT(color, "color");
        DEFINE_SHADER_CONSTANT(sampler, "textura");

        // Lighting
        DEFINE_SHADER_CONSTANT(ambientLight, "ambientLight");
        DEFINE_SHADER_CONSTANT(diffuseLight, "diffuseLight");
        DEFINE_SHADER_CONSTANT(pointLightA, "pointLightA");
        DEFINE_SHADER_CONSTANT(pointLightB, "pointLightB");
        DEFINE_SHADER_CONSTANT(normalLength, "normalLength");
        DEFINE_SHADER_CONSTANT(material, "material");
        DEFINE_SHADER_CONSTANT(eyePosition, "eyePosition");
        DEFINE_SHADER_CONSTANT(numPointLights, "numPointLights");

        // Fog constants
        DEFINE_SHADER_CONSTANT(fogParams, "fogParams");
    };

    /**
     * Wraps OpenGL shader loading and compilation into a very convenient class.
     */
    class Shader
    {
    public:
        ~Shader();

        /**
         * Loads and compiles shader from a specified file.
         *
         * @param fileName    path to a file
         * @param shaderType  type of shader (vertex, fragment, geometry...)
         *
         * @return True, if the shader has been successfully loaded and compiled, false otherwise.
         */
        bool loadShaderFromFile(const std::string& fileName, GLenum shaderType);

        /**
         * Checks, if shader is loaded successfully.
         *
         * @return True, if the shader has been successfully loaded and compiled, false otherwise.
         */
        bool isLoaded() const;

        /**
         * Deletes shader object from OpenGL.
         */
        void deleteShader();

        /**
         * Gets OpenGL assigned shader ID.
         */
        GLuint getShaderID() const;

        /**
         * Gets shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...).
         */
        GLenum getShaderType() const;

    private:
        /**
         * Gets all lines from specified shader file.
         *
         * @param fileName               Filename to read the line from.
         * @param result                 std::vector to store the source code lines into
         * @param isReadingIncludedFile  Flag saying, whether we are reading file that's been included, that is only #include_part.
         *
         * @return True, if the loading has been successful, or false otherwise.
         */
        bool getLinesFromFile(const std::string& fileName, std::vector<std::string>& result, bool isReadingIncludedFile = false) const;

        GLuint ShaderID; // OpenGL-assigned shader ID
        GLenum ShaderType; // Type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER...)
        bool IsLoaded = false; // Flag teling, whether shader has been loaded and compiled sucessfully
    };
} // namespace XE
