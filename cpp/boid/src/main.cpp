#include <filesystem>
#include <iostream>
#include <thread>

#include "MugEngine.hpp"
#include "SimpleBoidSimulation.h"
#include "render/simple/InstancedTriangles.h"
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

        auto instShader = MugShader::loadShaderNamed("res/shaders/simple", "instancedtri");
        if (instShader == nullptr) {
            MugLogger::error("Failed to load instanced shader");
            return -1;
        }

        SimpleTriangle tri = SimpleTriangle(SimplePoint(-0.5, -0.5), SimplePoint(0.5, -0.5), SimplePoint(0.0, 0.5));
        InstancedTriangles inst = InstancedTriangles(500);
        SimpleBoidSimulation boids(100);
        boids.update();
        inst.setShader(instShader);

        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            engine.BeginDraw();

            // inst.draw();
            // boids.update();
            boids.update();
            boids.draw();
            engine.EndDraw();
        }
    }
    MugLogger::debug("Shutting down");
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
