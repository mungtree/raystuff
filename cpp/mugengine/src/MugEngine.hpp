#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "util/MugLogger.hpp"
#include "util/RGBAColor.h"

class MugEngine {
private:
    MugLogger logger;
    bool initState = false;
    GLFWwindow *window = nullptr;
public:
/// Public Variables
    ColorRGBA ClearColor{0.2f,  0.3f, 0.3f, 1.0f};


#pragma region Initialization

    MugEngine();
    int init();
    GLFWwindow *createWindow(int width, int height, const std::string& title, GLFWmonitor *monitor, GLFWwindow *share);

#pragma  endregion

#pragma region Drawing

    void BeginDraw();
    void EndDraw();

#pragma endregion

#pragma region Getters/Setters

    [[nodiscard]] bool isInit() const { return initState; }
    [[nodiscard]] GLFWwindow *getWindow() const { return window; }

#pragma endregion
};
