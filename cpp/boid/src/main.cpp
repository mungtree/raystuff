#include <filesystem>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "GridBoidSimulation.h"
#include "MugEngine.hpp"
#include "SimpleBoidSimulation.h"
#include "render/simple/InstancedTriangles.h"
#include "render/simple/SimpleTriangle.h"
#include "shaders/MugShader.hpp"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


void processInput(GLFWwindow *window);

AbstractBoidSimulator *sim = nullptr;

int main(int argv, char **argc) {
    MugEngine engine = MugEngine();
    engine.init();
    engine.createWindow(1000, 700, "Mugtree", nullptr, nullptr);
    engine.ClearColor = ColorRGBA{0.1, 0.1, 0.2, 1.0};
    GLFWwindow *window = engine.getWindow();

    auto path = std::filesystem::current_path();
    MugLogger::debug("Starting at: " + path.string());

    auto instShader = MugShader::loadShaderNamed("res/shaders/simple", "instancedtri");
    if (instShader == nullptr) {
        MugLogger::error("Failed to load instanced shader");
        return -1;
    }

    //SimpleBoidSimulation boids(1000);
    GridBoidSimulation boids(10000);
    sim = &boids;
    boids.update();
    boids.startUpdateThread();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        engine.BeginDraw();

        engine.BeginImGuiFrame();
        boids.drawImGui();
        engine.EndImGuiFrame();

        boids.draw();
        engine.EndDraw();
    }
    boids.stopUpdateThread();
    sim = nullptr;
    engine.shutdown();
    MugLogger::debug("Shutting down");

    return 0;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (sim != nullptr) {
            sim->resetBoids();
        }
    }
}
