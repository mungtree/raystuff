#include "mugengine.hpp"

#include <utility>

void MugEngine::logError(std::string error) {
    if (onErrorCb == nullptr) return;
    onErrorCb(std::move(error));
}

int MugEngine::init() {
    if (isInit()) return 1;
    if (!glfwInit()) {
        logError("GLFW Failed to initialize");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    initState = true;
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow * MugEngine::createWindow(int width, int height, std::string title, GLFWmonitor *monitor,
    GLFWwindow *share) {
    if (this->window != nullptr) {
        logError("Window already created");
        return nullptr;
    }
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
    if (window == nullptr) {
        logError("Failed to create GLFW window");
        return nullptr;
    }
    this->window = window;
    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logError("Failed to initialize GLAD");
    }
    return window;
}
