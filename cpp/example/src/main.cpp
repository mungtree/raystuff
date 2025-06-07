#include <filesystem>
#include <iostream>
#include <thread>

#include "MugEngine.hpp"
#include "render/simple/SimpleTriangle.h"
#include "shaders/MugShader.hpp"

void processInput(GLFWwindow* window);

int main(int argv, char** argc) {
    {
        MugEngine engine = MugEngine();
        engine.init();
        engine.createWindow(800, 600, "Mugtree", nullptr, nullptr);
        GLFWwindow* window = engine.getWindow();
        auto path = std::filesystem::current_path();
        MugLogger::debug("Starting at: " + path.string());
        auto simpleShader = MugShader::loadShaderNamed("res/shaders/simple", "simpletri");
        if (simpleShader == nullptr) {
            MugLogger::error("Failed to load simple shader");
            return -1;
        }
        SimpleTriangle tri = SimpleTriangle(SimplePoint(-0.5, -0.5), SimplePoint(0.5, -0.5), SimplePoint(0.0, 0.5));


        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            engine.BeginDraw();

            simpleShader->bind();
            tri.draw();
            simpleShader->unbind();

            engine.EndDraw();
        }
        glfwTerminate();
    }
    MugLogger::debug("Shutting down");
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
