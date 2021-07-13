// GLM
#include <glm/gtc/matrix_transform.hpp>

// Project
#include "OpenGLWindow.h"

using namespace XE;

std::map<GLFWwindow*, OpenGLWindow*> OpenGLWindow::Windows;

OpenGLWindow::OpenGLWindow()
{
    for (auto& kwp : KeyWasPressed)
    {
        kwp = false;
    }
}

bool OpenGLWindow::createOpenGLWindow(const std::string& windowTitle, int majorVersion, int minorVersion, int scr_width, int scr_height)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const auto primaryMonitor = glfwGetPrimaryMonitor();
    const auto videoMode = glfwGetVideoMode(primaryMonitor);

    // Gets window size
    bool showFullscreen = false;
    if (scr_width != 0 && scr_height != 0)
    {
        SCR_WIDTH = scr_width;
        SCR_HEIGHT = scr_height;
    }
    else
    {
        SCR_WIDTH = videoMode->width;
        SCR_HEIGHT = videoMode->height;
        showFullscreen = true;
    }

    Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, windowTitle.c_str(), showFullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (Window == nullptr)
    {
        return false;
    }

    glfwMakeContextCurrent(Window);
    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    glfwSetWindowSizeCallback(Window, onWindowSizeChangedStatic);

    if (!showFullscreen)
    {
       // glfwMaximizeWindow(Window);
        // After calling glfwMaximizeWindow, the onWindowSizeChanged somehow does not get called
        // Therefore I call it manually
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        onWindowSizeChanged(width, height);
    }

    glfwSetScrollCallback(Window, onMouseWheelScrollStatic);
    Windows[Window] = this;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init("#version 440");

    return true;
}

bool OpenGLWindow::keyPressed(int keyCode) const
{
    return glfwGetKey(Window, keyCode) == GLFW_PRESS;
}

bool OpenGLWindow::keyPressedOnce(int keyCode)
{
    bool result = false;
    if (keyPressed(keyCode))
    {
        if (!KeyWasPressed[keyCode])
        {
            result = true;
        }

        KeyWasPressed[keyCode] = true;
    }
    else
    {
        KeyWasPressed[keyCode] = false;
    }

    return result;
}

void OpenGLWindow::runApp()
{
    setVerticalSynchronization(true);
    recalculateProjectionMatrix();
    initializeScene();

    //Draw cursor or not
    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Update time at the beginning, so that calculations are correct
    LastFrameTime = LastFrameTimeFPS = glfwGetTime();

    while (glfwWindowShouldClose(Window) == 0)
    {
        updateDeltaTimeAndFPS();
        renderScene();

        glfwSwapBuffers(Window);
        glfwPollEvents();
        updateScene();
    }

    releaseScene();

    glfwDestroyWindow(Window);
    Windows.erase(Windows.find(Window));

    if (Windows.empty())
    {
        glfwTerminate();
    }
}

GLFWwindow* OpenGLWindow::getWindow() const
{
    return Window;
}

void OpenGLWindow::closeWindow(bool hasErrorOccured)
{
    glfwSetWindowShouldClose(Window, true);
    HasErrorOccured = hasErrorOccured;
}

bool OpenGLWindow::hasErrorOccured() const
{
    return HasErrorOccured;
}

glm::mat4 OpenGLWindow::getProjectionMatrix() const
{
    return ProjectionMatrix;
}

glm::mat4 OpenGLWindow::getOrthoProjectionMatrix() const
{
    return OrthoMatrix;
}

float OpenGLWindow::sof(float value) const
{
    return value * static_cast<float>(TimeDelta);
}

double OpenGLWindow::sof(double value) const
{
    return value * TimeDelta;
}

double OpenGLWindow::getTimeDelta() const
{
    return TimeDelta;
}

int OpenGLWindow::getFPS() const
{
    return FPS;
}

void OpenGLWindow::setVerticalSynchronization(bool enable)
{
    glfwSwapInterval(enable ? 1 : 0);
    IsVerticalSynchronizationEnabled = enable;
}

bool OpenGLWindow::isVerticalSynchronizationEnabled() const
{
    return IsVerticalSynchronizationEnabled;
}

OpenGLWindow* OpenGLWindow::getDefaultWindow()
{
    return Windows.size() == 0 ? nullptr : (*Windows.begin()).second;
}

void OpenGLWindow::onWindowSizeChanged(int width, int height)
{
    recalculateProjectionMatrix();
    glViewport(0, 0, width, height);
}

void OpenGLWindow::recalculateProjectionMatrix()
{
    int width, height;
    glfwGetWindowSize(getWindow(), &width, &height);
    ProjectionMatrix = glm::perspective(45.0f, static_cast<float>(width) / static_cast<float>(height), 0.5f, 1500.0f);
    OrthoMatrix = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
}

void OpenGLWindow::updateDeltaTimeAndFPS()
{
    const auto currentTime = glfwGetTime();
    TimeDelta = currentTime - LastFrameTime;
    LastFrameTime = currentTime;
    NextFPS++;

    if (currentTime - LastFrameTimeFPS > 1.0)
    {
        LastFrameTimeFPS = currentTime;
        FPS = NextFPS;
        NextFPS = 0;
    }
}

void OpenGLWindow::onWindowSizeChangedStatic(GLFWwindow* window, int width, int height)
{
    if (Windows.count(window) != 0)
    {
        Windows[window]->onWindowSizeChanged(width, height);
    }
}

void OpenGLWindow::onMouseWheelScrollStatic(GLFWwindow* window, double scrollOffsetX, double scrollOffsetY)
{
    if (Windows.count(window) != 0)
    {
        Windows[window]->onMouseWheelScroll(scrollOffsetX, scrollOffsetY);
    }
}