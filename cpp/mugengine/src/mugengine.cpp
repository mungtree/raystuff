#include "mugengine.hpp"

MugEngine::MugEngine() = default;

int MugEngine::init() {
    if (isInit()) return 1;
    MugLogger::init();
    if (!glfwInit()) {
        MugLogger::critical("GLFW failed to initialize");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    initState = true;

    MugLogger::info("MugEngine Initialized!");
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow * MugEngine::createWindow(int width, int height, const std::string& title, GLFWmonitor *monitor,
    GLFWwindow *share) {
    if (this->window != nullptr) {
        MugLogger::error("Window already created");
        return nullptr;
    }
    GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), monitor, share);
    if (window == nullptr) {
        MugLogger::critical("Failed to create GLFW window");
        return nullptr;
    }
    this->window = window;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        MugLogger::critical("Failed to initialize GLAD");
    }
    return window;
}
