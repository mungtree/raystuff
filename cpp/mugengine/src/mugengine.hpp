#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/MugLogger.hpp"

class MugEngine {
private:
    MugLogger logger;
    bool initState = false;
    GLFWwindow *window = nullptr;
public:
    MugEngine();
    int init();

    GLFWwindow *createWindow(int width, int height, const std::string& title, GLFWmonitor *monitor, GLFWwindow *share);

    ///
    /// Getters and Setters
    ///
    [[nodiscard]] bool isInit() const { return initState; }
    GLFWwindow *getWindow() const { return window; }
};
