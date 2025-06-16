#include "MugEngine.hpp"

#include "imgui/MugImGuiStuff.h"

void MugEngine::initImGui() {
    if (window == nullptr) {
        MugLogger::critical("No window for ImGui to initialize to.");
    }
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // IF using Docking Branch
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 5.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

MugEngine::MugEngine() = default;

int MugEngine::init() {
    if (isInit()) return 1;
    MugLogger::init();
    if (!glfwInit()) {
        MugLogger::critical("GLFW failed to initialize");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    initState = true;

    MugLogger::info("MugEngine Initialized!");
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *MugEngine::createWindow(int width, int height, const std::string &title, GLFWmonitor *monitor,
                                    GLFWwindow *share) {
    if (this->window != nullptr) {
        MugLogger::error("Window already created");
        return nullptr;
    }
    GLFWwindow *window = glfwCreateWindow(1920, 1080, title.c_str(), monitor, share);
    if (window == nullptr) {
        MugLogger::critical("Failed to create GLFW window");
        return nullptr;
    }
    this->window = window;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        MugLogger::critical("Failed to initialize GLAD");
    }
    initImGui();
    glfwSetWindowSize(window, width, height);
    return window;
}

void MugEngine::shutdown() {
    shaderManager.clearShaders();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void MugEngine::BeginDraw() {
    glClearColor(ClearColor.r, ClearColor.g, ClearColor.b, ClearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void MugEngine::EndDraw() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void MugEngine::BeginImGuiFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MugEngine::EndImGuiFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
