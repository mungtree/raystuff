#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class MugEngine {
private:
   bool initState = false;
    GLFWwindow* window = nullptr;

    void (*onErrorCb)(std::string error) = nullptr;
    void logError(std::string error);
public:
    int init();
    GLFWwindow* createWindow(int width, int height, std::string title, GLFWmonitor* monitor, GLFWwindow* share);

    void setErrorCallback(void (*callback)(std::string error)) {
        onErrorCb = callback;
    }

    ///
    /// Getters and Setters
    ///
    [[nodiscard]] bool isInit() const { return initState;}
    GLFWwindow* getWindow() const { return window; }
};