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

void processInput(GLFWwindow *window);

SimpleBoidSimulation *sim = nullptr;

int main(int argv, char **argc) { {
        MugEngine engine = MugEngine();
        engine.init();
        engine.createWindow(1000, 700, "Mugtree", nullptr, nullptr);
        engine.ClearColor = ColorRGBA{0.1, 0.1, 0.2, 1.0};
        GLFWwindow *window = engine.getWindow();
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

        //SimpleBoidSimulation boids(1000);
        //sim = &boids;
        GridBoidSimulation boids(100);
        boids.update();
        boids.startUpdateThread();


        while (!glfwWindowShouldClose(window)) {
            processInput(window);
            engine.BeginDraw();

            // inst.draw();
            //boids.update();
            boids.draw();
            engine.EndDraw();
        }
        boids.stopUpdateThread();
        sim = nullptr;
    }
    MugLogger::debug("Shutting down");
    glfwTerminate();
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
