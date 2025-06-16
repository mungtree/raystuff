#include <filesystem>
#include <iostream>
#include <thread>

#include "MugEngine.hpp"
#include "render/simple/MugInstanceTriangleFan.h"
#include "render/simple/SimpleTriangle.h"
#include "shaders/MugShader.hpp"

void processInput(GLFWwindow* window);

int main(int argv, char** argc) {
    {
        MugEngine& engine = MugEngine::getInstance();
        engine.init();
        engine.createWindow(800, 600, "Mugtree", nullptr, nullptr);
        GLFWwindow* window = engine.getWindow();

        MugInstanceTriangleFan circ = MugInstanceTriangleFan(1, 100);

        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            engine.BeginDraw();

            engine.BeginImGuiFrame();
            engine.EndImGuiFrame();

            circ.draw();

            engine.EndDraw();
        }
        engine.shutdown();
    }
    MugLogger::debug("Shutting down");
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
