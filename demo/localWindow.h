#pragma once

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

//#include "staticGeometry.h"

// Meshes
//#include <renderable.h>
#include <geometry/primitives/cube.h>
#include <geometry/primitives/quad.h>
#include <geometry/primitives/triangle.h>

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
        std::unique_ptr<Cube> Cubo;
        //std::unique_ptr<Quad> porfa;
        //std::unique_ptr<Triangle> trifa;

        //std::unique_ptr<static_meshes_3D::Pyramid> Pyramid;
        //std::unique_ptr<static_meshes_3D::Torus> Torus;
        //std::unique_ptr<static_meshes_3D::PlainGround> PlainGround;

        // Camera
        FlyingCamera Camera = FlyingCamera(this, glm::vec3(0.0f, 8.0f, 20.0f), glm::vec3(0.0f, 8.0f, 19.0f), glm::vec3(0.0f, 1.0f, 0.0f), 50);

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
