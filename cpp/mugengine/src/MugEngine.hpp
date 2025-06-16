#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "shaders/ShaderManager.h"

#include "util/MugLogger.hpp"
#include "util/RGBAColor.h"

class MugEngine {
private:

    static MugEngine* mugEngineInstance;
    MugLogger logger;
    bool initState = false;
    GLFWwindow *window = nullptr;
    ShaderManager shaderManager;

    void initImGui();

    MugEngine(MugEngine const&) = delete;
    void operator= (MugEngine const&) = delete;
public:
    /// Public Variables
    ColorRGBA ClearColor{0.2f,  0.3f, 0.3f, 1.0f};

#pragma region Static
public:
    static MugEngine& getInstance() {
        static MugEngine instance;
        return instance;
    }


#pragma endregion



#pragma region Initialization
    MugEngine();
    int init();
    GLFWwindow *createWindow(int width, int height, const std::string& title, GLFWmonitor *monitor, GLFWwindow *share);
    void shutdown();
#pragma  endregion

#pragma region Drawing

    void BeginDraw();
    void EndDraw();

    void BeginImGuiFrame();
    void EndImGuiFrame();

#pragma endregion

#pragma region Getters/Setters

    [[nodiscard]] bool isInit() const { return initState; }
    [[nodiscard]] GLFWwindow *getWindow() const { return window; }
    [[nodiscard]] ShaderManager& getShaderManager() { return shaderManager; }
#pragma endregion
};
