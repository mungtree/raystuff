#include <iostream>
#include "mugengine.hpp"

void processInput(GLFWwindow* window);

int main(int argv, char** argc) {
    MugEngine engine = MugEngine();
    engine.init();
    engine.createWindow(800, 600, "Mugtree", nullptr, nullptr);
    GLFWwindow* window = engine.getWindow();

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}
