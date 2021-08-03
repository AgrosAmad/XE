// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/gtc/matrix_transform.hpp>

// Project
#include "flyingCamera.h"

// Window management
#include "openGLWindow.h"

using namespace XE;

FlyingCamera::FlyingCamera(OpenGLWindow* localWindow, const glm::vec3& position, const glm::vec3& viewPoint, const glm::vec3& upVector, float moveSpeed, float mouseSensitivity)
    : Position(position)
    , ViewPoint(viewPoint)
    , UpVector(upVector)
    , MoveSpeed(moveSpeed)
    , MouseSensitivity(mouseSensitivity)
    , Window(localWindow)
{
    // Standard WSAD controls, as you are used to from games :)
    setControls(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_MOUSE_BUTTON_RIGHT);
}

void FlyingCamera::setMoveSpeed(float moveSpeed)
{
    MoveSpeed = moveSpeed;
}

void FlyingCamera::setMouseSensitivity(float mouseSensitivity)
{
    MouseSensitivity = mouseSensitivity;
}

void FlyingCamera::setControls(int forwardKeyCode, int backwardKeyCode, int strafeLeftKeyCode, int strafeRightKeyCode, int cameraRotationKeyCode)
{
    ForwardKeyCode = forwardKeyCode;
    BackwardKeyCode = backwardKeyCode;
    StrafeLeftKeyCode = strafeLeftKeyCode;
    StrafeRightKeyCode = strafeRightKeyCode;
    CameraRotationKeyCode = cameraRotationKeyCode;
}

void FlyingCamera::setWindowCenterPosition(const glm::i32vec2& windowCenterPosition)
{
    WindowCenterPosition = windowCenterPosition;
}

glm::mat4 FlyingCamera::getViewMatrix() const
{
    return glm::lookAt(Position, ViewPoint, UpVector);
}

glm::vec3 FlyingCamera::getEye() const
{
    return Position;
}

glm::vec3 FlyingCamera::getViewPoint() const
{
    return ViewPoint;
}

glm::vec3 FlyingCamera::getUpVector() const
{
    return UpVector;
}

void FlyingCamera::update()
{
    // Moves camera around
    if (Window->keyPressed(ForwardKeyCode)) 
    {
        moveBy(Window->sof(MoveSpeed));
    }

    if (Window->keyPressed(BackwardKeyCode)) 
    {
        moveBy(-Window->sof(MoveSpeed));
    }

    if (Window->keyPressed(StrafeLeftKeyCode)) 
    {
        strafeBy(-Window->sof(MoveSpeed));
    }

    if (Window->keyPressed(StrafeRightKeyCode)) 
    {
        strafeBy(Window->sof(MoveSpeed));
    }

    // Rotates camera with mouse movement
    double curPosX, curPosY;
    glfwGetCursorPos(Window->getWindow(), &curPosX, &curPosY);
    const auto curMousePosition = glm::i32vec2(curPosX, curPosY);
    const auto delta = MouseLastPos - curMousePosition;

    // Hides mouse when rotating camera
    if (Window->keyMousePressed(CameraRotationKeyCode))
    {
        glfwSetInputMode(Window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetCursorPos(Window->getWindow(), MouseLastPos.x, MouseLastPos.y);
    }
    else
    {
        glfwSetInputMode(Window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        MouseLastPos = curMousePosition;
    }

    if (delta.x != 0 && Window->keyMousePressed(CameraRotationKeyCode))
    {
        rotateLeftRight(static_cast<float>(delta.x) * MouseSensitivity);
    }

    if (delta.y != 0 && Window->keyMousePressed(CameraRotationKeyCode))
    {
        rotateUpDown(static_cast<float>(delta.y) * MouseSensitivity);
    }

    //glfwSetCursorPos(Window->getWindow(), WindowCenterPosition.x, WindowCenterPosition.y);

}

void FlyingCamera::moveBy(float distance)
{
    glm::vec3 vOffset = getNormalizedViewVector();
    vOffset *= distance;
    Position += vOffset;
    ViewPoint += vOffset;
}

void FlyingCamera::strafeBy(float distance)
{
    glm::vec3 strafeVector = glm::normalize(glm::cross(getNormalizedViewVector(), UpVector));
    strafeVector = glm::normalize(strafeVector);
    strafeVector *= distance;

    Position += strafeVector;
    ViewPoint += strafeVector;
}

void FlyingCamera::rotateLeftRight(float angleInDegrees)
{
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(getNormalizedViewVector(), 0.0f);
    ViewPoint = Position + glm::vec3(rotatedViewVector);
}

void FlyingCamera::rotateUpDown(float angleInDegrees)
{
    const glm::vec3 viewVector = getNormalizedViewVector();
    const glm::vec3 viewVectorNoY = glm::normalize(glm::vec3(viewVector.x, 0.0f, viewVector.z));

    float currentAngleDegrees = glm::degrees(acos(glm::dot(viewVectorNoY, viewVector)));
    if (viewVector.y < 0.0f) {
        currentAngleDegrees = -currentAngleDegrees;
    }

    float newAngleDegrees = currentAngleDegrees + angleInDegrees;
    if (newAngleDegrees > -85.0f && newAngleDegrees < 85.0f)
    {
        glm::vec3 rotationAxis = glm::cross(getNormalizedViewVector(), UpVector);
        rotationAxis = glm::normalize(rotationAxis);

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleInDegrees), rotationAxis);
        glm::vec4 rotatedViewVector = rotationMatrix * glm::vec4(getNormalizedViewVector(), 0.0f);

        ViewPoint = Position + glm::vec3(rotatedViewVector);
    }
}

glm::vec3 FlyingCamera::getNormalizedViewVector() const
{
    return glm::normalize(ViewPoint - Position);
}
