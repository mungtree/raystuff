#include <iostream>
#include "MugEngine.hpp"

void logError(std::string error) {
    std::cerr << "[MugEngine]\t" << error << std::endl;
}

void processInput(GLFWwindow* window);

int main(int argv, char** argc) {
    MugEngine engine = MugEngine();
    engine.init();
    engine.createWindow(800, 600, "Mugtree", nullptr, nullptr);
    GLFWwindow* window = engine.getWindow();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        engine.BeginDraw();

        engine.EndDraw();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
