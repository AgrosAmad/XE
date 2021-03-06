#pragma once

// STL
#include <functional>

// GLM
#include <glm/glm.hpp>

/**
 * Implements a camera, that can fly around the world freely.
 * It cannot rotate more than 90 degrees up / down (so it's not sutiable for space flight simulators).
 */
namespace XE
{

    class OpenGLWindow; // For cross-declaration;

    class FlyingCamera
    {
    public:
        FlyingCamera(OpenGLWindow* localWindow, const glm::vec3& position, const glm::vec3& viewPoint, const glm::vec3& upVector, float moveSpeed = 10.0f, float mouseSensitivity = 0.15f);

        /**
         * Sets movement speed of camera (how fast camera moves forward / backward and strafes left / right).
         *
         * @param moveSpeed  Movement speed (distance travelled per second)
         */
        void setMoveSpeed(float moveSpeed);

        /**
         * Sets mouse sensitivity, or the speed, with which you rotate view with mouse.
         *
         * @param mouseSensitivity  Sensitivity in degrees per pixel - how many degrees does camera turn for each pixel moved
         */
        void setMouseSensitivity(float mouseSensitivity);

        /**
         * Sets keys to control camera with.
         *
         * @param forwardKeyCode      Key code to move forward
         * @param backwardKeyCode     Key code to move backward
         * @param strafeLeftKeyCode   Key code to strafe left
         * @param strafeRightKeyCode  Key code to strafe right
         */
        void setControls(int forwardKeyCode, int backwardKeyCode, int strafeLeftKeyCode, int strafeRightKeyCode, int cameraRotationKeyCode);

        /**
         * Sets center of window position, in pixels.
         * This is required for camera rotation, that resets cursor position constantly.
         *
         * @param windowCenterPosition  Center of the window
         */
        void setWindowCenterPosition(const glm::i32vec2& windowCenterPosition);

        /**
         * Gets the current view matrix calculated from position and viewpoint of camera.
         */
        glm::mat4 getViewMatrix() const;

        /**
         * Gets the current eye position (camera's position).
         */
        glm::vec3 getEye() const;

        /**
         * Gets the point camera looks to.
         */
        glm::vec3 getViewPoint() const;

        /**
         * Gets the up vector of the camera.
         */
        glm::vec3 getUpVector() const;

        /**
         * Gets normalized view vector of the camera.
         */
        glm::vec3 getNormalizedViewVector() const;

        /**
         * Updates camera - reacts on key presses and updates camera's internal state (position, view vector...).
         */
        void update();

    private:
        /**
         * Moves camera by specified distance (positive value = move forward, negative value = move backward).
         *
         * @param distance  Distance to move by
         */
        void moveBy(float distance);

        /**
         * Strafes camera by specified distance (positive value = strafe right, negative value = strafe left).
         *
         * @param distance Distance to strafe by
         */
        void strafeBy(float distance);

        /**
         * Rotates camera view by specified angle to the left or right side.
         *
         * @param angleInDegrees Angle to rotate by (in degrees)
         */
        void rotateLeftRight(float angleInDegrees);

        /**
         * Rotates camera view by specified angle up or down.
         *
         * @param angleInDegrees Angle to rotate by (in degrees)
         */
        void rotateUpDown(float angleInDegrees);

        OpenGLWindow* Window; // Window in which this camera is active

        glm::vec3 Position; // Camera's position (eye position)
        glm::vec3 ViewPoint; // Viewpoint - where does camera look to
        glm::vec3 UpVector; // Up vector of the camera

        glm::i32vec2 WindowCenterPosition; // Center of the window (to restore cursor position every frame to)
        glm::i32vec2 MouseLastPos; // Last mouse position (to compute movement)
        float MouseSensitivity; // Mouse sensitivity in degrees per pixel

        float MoveSpeed; // Speed of camera (both for going forward / backward and for strafing left / right)
        int ForwardKeyCode; // Key code to move forward
        int BackwardKeyCode; // Key code to move backward
        int StrafeLeftKeyCode; // Key code to rotate left
        int StrafeRightKeyCode; // Key code to rotate right
        int CameraRotationKeyCode; // Key code to activate camera rotation with mouse
    };
} // namespace XE