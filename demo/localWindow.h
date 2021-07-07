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
#include "geometry/static_meshes_3D/house.h"
#include "geometry/static_meshes_3D/snowCoveredPlainGround.h"

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
        std::unique_ptr<static_meshes_3D::House> House;
        std::unique_ptr<static_meshes_3D::SnowCoveredPlainGround> Snowground;
        std::unique_ptr<HUD010> HUD;

        // Camera
        FlyingCamera Camera = FlyingCamera(glm::vec3(0.0f, 8.0f, 20.0f), glm::vec3(0.0f, 8.0f, 19.0f), glm::vec3(0.0f, 1.0f, 0.0f), 50);

        // Transform scene
        struct HouseTransformation
        {
            glm::vec3 position;
            float angle;
        };

        std::vector<HouseTransformation> houseTransformations
        {
            {glm::vec3(-140, 0, 94), glm::radians(90.0f)},
            {glm::vec3(-140, 0, 64), glm::radians(90.0f)},
            {glm::vec3(-140, 0, 34), glm::radians(90.0f)},
            {glm::vec3(-140, 0, 4), glm::radians(90.0f)},
            {glm::vec3(-97, 0, 18), glm::radians(-90.0f)},
            {glm::vec3(-97, 0, 48), glm::radians(-90.0f)},
            {glm::vec3(-97, 0, 78), glm::radians(-90.0f)},
            {glm::vec3(-63, 0, -14), glm::radians(180.0f)},
            {glm::vec3(-33, 0, -14), glm::radians(180.0f)},
            {glm::vec3(-3, 0, -14), glm::radians(180.0f)},
            {glm::vec3(27, 0, -14), glm::radians(180.0f)},
            {glm::vec3(-75, 0, -64), glm::radians(0.0f)},
            {glm::vec3(-45, 0, -64), glm::radians(0.0f)},
            {glm::vec3(-15, 0, -64), glm::radians(0.0f)},
            {glm::vec3(15, 0, -64), glm::radians(0.0f)},
            {glm::vec3(45, 0, -64), glm::radians(0.0f)},
            {glm::vec3(-121, 0, -54), glm::radians(45.0f)}
        };
    };
} // namespace XE
