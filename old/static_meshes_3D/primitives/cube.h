#pragma once

// GLM
#include <glm/glm.hpp>

// XE
#include <renderable.h>

namespace XE
{
    const int CUBE_FRONT_FACE = 1; // Bitmask to render cube front face
    const int CUBE_BACK_FACE = 1 << 1; // Bitmask to render cube back face
    const int CUBE_LEFT_FACE = 1 << 2; // Bitmask to render cube left face
    const int CUBE_RIGHT_FACE = 1 << 3; // Bitmask to render cube right face
    const int CUBE_TOP_FACE = 1 << 4; // Bitmask to render cube top face
    const int CUBE_BOTTOM_FACE = 1 << 5; // Bitmask to render cube bottom face

    // Cube mesh of unit size
    class Cube : public Renderable
    {
    public:
        Cube(bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

        void render() const override;
        void renderPoints() const override;
        void renderFaces(int facesBitmask) const;

        static glm::vec3 vertices[36]; // Array of mesh vertices
        static glm::vec2 textureCoordinates[6]; // Array of mesh texture coordinates
        static glm::vec3 normals[6]; // Array of mesh normals

    private:
        void initializeData() override;
    };
} // namespace XE