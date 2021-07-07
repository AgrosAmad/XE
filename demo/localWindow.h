#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// XII Library
#include "openGLWindow.h"
#include "shader.h"
#include "shaderProgram.h"
#include "flyingCamera.h"
#include "texture.h"
#include "sampler.h"
#include "vertexBufferObject.h"

#include "managers/shaderManager.h"
#include "managers/shaderProgramManager.h"
#include "managers/textureManager.h"
#include "managers/samplerManager.h"
#include "managers/matrixManager.h"

#include "HUD010.h"
#include "staticGeometry.h"

// Meshes
#include "geometry/static_meshes_3D/plainGround.h"
#include "geometry/static_meshes_3D/primitives/pyramid.h"
#include "geometry/static_meshes_3D/primitives/torus.h"

namespace XE
{
    class LocalWindow : public OpenGLWindow
    {
        void initializeScene() override;
        void renderScene() override;
        void updateScene() override;
        void releaseScene() override;

    private:

        // Rendering
        std::unique_ptr<static_meshes_3D::Pyramid> Pyramid;
        std::unique_ptr<static_meshes_3D::Torus> Torus;
        std::unique_ptr<static_meshes_3D::PlainGround> PlainGround;

        // Camera
        FlyingCamera Camera = FlyingCamera(glm::vec3(0.0f, 8.0f, 20.0f), glm::vec3(0.0f, 8.0f, 19.0f), glm::vec3(0.0f, 1.0f, 0.0f), 50);

        // Transform scene
        float rotationAngleRad = 0.0f;
        std::vector<glm::vec3> objectPositions
        {
            glm::vec3(-30.0f, 0.0f, -50.0f),
            glm::vec3(-30.0f, 0.0f, -25.0f),
            glm::vec3(-30.0f, 0.0f, 0.0f),
            glm::vec3(-30.0f, 0.0f, 25.0f),
            glm::vec3(-30.0f, 0.0f, 50.0f),
            glm::vec3(30.0f, 0.0f, -50.0f),
            glm::vec3(30.0f, 0.0f, -25.0f),
            glm::vec3(30.0f, 0.0f, 0.0f),
            glm::vec3(30.0f, 0.0f, 25.0f),
            glm::vec3(30.0f, 0.0f, 50.0f)
        };
    };
} // namespace XE
