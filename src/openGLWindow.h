#pragma once

// STL
#include <string>
#include <map>

// ImGui
#include <imgui-docking/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>

namespace XE
{
    /**
     * Provides easy and convenient way to handle OpenGL Window creation and basic scene management (init, render and release).
     */
    class OpenGLWindow
    {
    public:
        /**
         * Constructor of the class, initializes internal structures.
         */
        OpenGLWindow();

        /**
         * Creates a window with OpenGL context with given title and context version.
         *
         *  @param windowTitle     Title of the created window
         *  @param majorVersion    OpenGL context major version
         *  @param minorVersion    OpenGL context minor version
         *  @param showFullscreen  Tells, whether the window should be shown in fullscreen
         *
         *  @return True if window has been created successfully or false otherwise.
         */
        bool createOpenGLWindow(const std::string& windowTitle, int majorVersion, int minorVersion, int scr_width = 0, int scr_height = 0);

        /**
         * Creates a window with OpenGL context with given title and context version.
         *
         * @param windowTitle  Title of a created window
         *
         * @return Pointer to GLFW window or nullptr, if the window does not exist yet.
         */
        GLFWwindow* getWindow() const;

        /**
         * Runs the whole application. Contains the main application loop.
         */
        void runApp();

        /**
         * Initializes OpenGL Scene. This function is not implemented here, but it depends on
         * the tutorial, what are the contents of this function.
         */
        virtual void initializeScene() {}

        /**
         * Performs rendering of OpenGL Scene. This function is not implemented, but it depends on
         * the tutorial, what are the contents of this function.
         */
        virtual void renderScene() {}

        /**
         * Updates OpenGL scene - handles input in the application, updates variables etc. This function is not implemented,
         * but it depends on the tutorial, what are the contents of this function.
         */
        virtual void updateScene() {}

        /**
         * Releases OpenGL Scene, i.e. cleans up after itself and releases all used resources. This function
         * is not implemented, but it depends on the tutorial, what are the contents of this function.
         */
        virtual void releaseScene() {}

        /**
         * Checks, if specified key is currently pressed.
         *
         * @param keyCode  GLFW code of the key to check
         *
         * @return True if key is pressed or false otherwise.
         */
        bool keyPressed(int keyCode) const;

        /**
        * Checks, if specified mouse key is currently pressed.
        *
        * @param keyCode  GLFW code of the key to check
        *
        * @return True if key is pressed or false otherwise.
        */
        bool keyMousePressed(int keyCode) const;

        /**
         * Checks, if specified key was pressed. This function won't return true again, unless the key has been released and pressed again.
         *
         * @param keyCode  GLFW code of the key to check
         *
         * @return True, if key was pressed once, or false otherwise.
         */
        bool keyPressedOnce(int keyCode);

        /**
         * Closes application window and releases all resources. Also sets the error flag, if error has occured.
         *
         * @param errorHasOccured  Should be true, if an error has occured (default is false).
         */
        void closeWindow(bool errorHasOccured = false);

        /**
         * Gets the error flag.
         */
        bool hasErrorOccured() const;

        /**
         * Gets the projection matrix for the current window size.
         */
        glm::mat4 getProjectionMatrix() const;

        /**
         * Gets the orthographic projection matrix for the current window size.
         */
        glm::mat4 getOrthoProjectionMatrix() const;

        /**
         * Gets adjusted float value, that takes frames per second into account.
         * The name sof stands for "speed optimized float" and this is the name
         * I've been using in OpenGL programming since year 2005, so I will keep
         * the legacy :)
         *
         * @param value  Float value to be adjusted
         *
         * @return "Speed Optimized Floating Point Value (sof)".
         */
        float sof(float value) const;

        /**
         * Gets adjusted double value, that takes frames per second into account.
         *
         * @param value  Double value to be adjusted
         *
         * @return "Speed Optimized Floating Point Value (sof)".
         */
        double sof(double value) const;

        /**
         * Gets time delta - time passed since the last frame in seconds.
         */
        double getTimeDelta() const;

        /**
         * Gets current Frames Per Second (FPS).
         */
        int getFPS() const;

        /**
         * Turns vertical synchronization on or off.
         *
         * @param enable  True if you want to enable vertical synchronization or false otherwise
         */
        void setVerticalSynchronization(bool enable);

        /**
         * Checks, if vertical synchronization is on or off.
         *
         * @return True, if vertical synchronization is enabled, or false otherwise.
         */
        bool isVerticalSynchronizationEnabled() const;

        /**
         * Gets OpenGL default window.
         */
        static OpenGLWindow* getDefaultWindow();

    protected:
        /**
         * Callback function that gets called, when the size of the window changes. This function is also
         * left un-implemented and user should implement it.
         *
         * @param width   New window width (in pixels)
         * @param height  New window height (in pixels)
         */
        virtual void onWindowSizeChanged(int width, int height);

        /**
         * Callback function that gets called, when the size of the window changes. This function is also
         * left un-implemented and user should implement it.
         *
         * @param window  Pointer to GLFWwindow, size of which has changed
         * @param width   New window width (in pixels)
         * @param height  New window height (in pixels)
         */
        virtual void onMouseWheelScroll(double scrollOffsetX, double scrollOffsetY) {}

    private:
        GLFWwindow* Window = nullptr; // Pointer to GLFWwindow, nullptr by default
        bool KeyWasPressed[512]; // Array of bools, used by keyPressedOnce function
        bool HasErrorOccured = false; // Error flag, indicates, if any kind of error has occured

        int SCR_WIDTH; // Window's width
        int SCR_HEIGHT; // Window's height

        glm::mat4 ProjectionMatrix; // Precalculated projection matrix, when size changes, it's recalculated
        glm::mat4 OrthoMatrix; // Precalculated orthographic projection matrix, when size changes, it's recalculated
        void recalculateProjectionMatrix();

        double LastFrameTime = 0.0; // Time of last frame
        double LastFrameTimeFPS = 0.0; // Time of last FPS Update
        double TimeDelta = 0.0; // Time delta between last frame and current frame
        int FPS = 0; // Current FPS
        int NextFPS = 0; // Next FPS, that is being counted and will update the _FPS
        bool IsVerticalSynchronizationEnabled = false; // Stores information, if vertical synchronization is enabled

        bool HasMouseBeenScrolled = false;
        double ScrollOffsetX = 0.0;
        double ScrollOffsetY = 0.0;

        /**
         * Updates frame times and FPS counters.
         */
        void updateDeltaTimeAndFPS();

        /**
         * Static method that is set as callback to GLFW framework about window size changed.
         */
        static void onWindowSizeChangedStatic(GLFWwindow* window, int width, int height);

        static void onMouseWheelScrollStatic(GLFWwindow* window, double scrollOffsetX, double scrollOffsetY);

        static std::map<GLFWwindow*, OpenGLWindow*> Windows; // std::map used to map GLFWwindow pointers to OpenGLWindow (our class)
    };
} // namespace XE