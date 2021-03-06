#pragma once

// STL
#include <vector>
#include <string>

// GLM
#include <glm/glm.hpp>

// GLAD
#include <glad/glad.h>

namespace XE
{
    // Forward class declaration of ShaderProgram (because of cross-inclusion)
    class ShaderProgram;

    /**
     * Wraps OpenGL shader uniform variable.
     */
    class Uniform
    {
    public:
        Uniform();
        Uniform(const std::string& name, ShaderProgram* shaderProgram);

        // Family of functions setting vec2 uniforms
        Uniform& operator=(const glm::vec2& vector2D);
        void set(const glm::vec2& vector2D);
        void set(const glm::vec2* vectors2D, int count = 1);

        // Family of functions setting vec3 uniforms
        Uniform& operator=(const glm::vec3& vector3D);
        void set(const glm::vec3& vector3D);
        void set(const glm::vec3* vectors3D, int count = 1);

        // Family of functions setting vec4 uniforms
        Uniform& operator=(const glm::vec4& vector4D);
        void set(const glm::vec4& vector4D);
        void set(const glm::vec4* vectors4D, int count = 1);

        // Family of functions setting float uniforms
        Uniform& operator=(const float floatValue);
        Uniform& operator=(const std::vector<float>& floatValues);
        void set(const float floatValue);
        void set(const float* floatValues, int count = 1);

        // Family of functions setting integer uniforms
        Uniform& operator=(const int integerValue);
        void set(const int integerValue);
        void set(const int* integerValues, int count = 1);

        // Family of functions setting boolean uniforms
        Uniform& operator=(const bool boolValue);
        void set(const bool boolValue);
        void set(const bool* boolValue, int count = 1);

        // Family of functions setting 3x3 matrices uniforms
        Uniform& operator=(const glm::mat3& matrix);
        void set(const glm::mat3& matrix);
        void set(const glm::mat3* matrices, int count = 1);

        // Family of functions setting 4x4 matrices uniforms
        Uniform& operator=(const glm::mat4& matrix);
        void set(const glm::mat4& matrix);
        void set(const glm::mat4* matrices, int count = 1);

    private:
        ShaderProgram* MasterShaderProgram; // Pointer to shader program this uniform belongs to

        std::string Name; // Name of uniform
        int Location; // OpenGL assigned uniform location (cached in this variable)
    };
} // namespace XE
