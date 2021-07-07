// Project
#include "matrixManager.h"

using namespace XE;

MatrixManager& MatrixManager::getInstance()
{
    static MatrixManager mm;
    return mm;
}

const glm::mat4& MatrixManager::getProjectionMatrix() const
{
    return ProjectionMatrix;
}

const glm::mat4& MatrixManager::getOrthoProjectionMatrix() const
{
    return OrthoProjectionMatrix;
}

const glm::mat4& MatrixManager::getViewMatrix() const
{
    return ViewMatrix;
}

void MatrixManager::setProjectionMatrix(const glm::mat4& projectionMatrix)
{
    ProjectionMatrix = projectionMatrix;
}

void MatrixManager::setOrthoProjectionMatrix(const glm::mat4& orthoProjectionMatrix)
{
    OrthoProjectionMatrix = orthoProjectionMatrix;
}

void MatrixManager::setViewMatrix(const glm::mat4& viewMatrix)
{
    ViewMatrix = viewMatrix;
}
