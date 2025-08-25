#include "DearImKit/init/init.h"

#include <filesystem>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"

#include "DearImKit/panel_manager/panel_manager.h"

const int START_WINDOW_WIDTH = 800;
const int START_WINDOW_HEIGHT = 600;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void runRenderingFunctions() {
    DearImKit::detail::Render();
}

void initImGuiFrames() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void initImGuiIniFile(const std::string& app_name) {
#ifdef _WIN32
    const char* base = getenv("APPDATA");
    std::filesystem::path config = std::filesystem::path(base) / app_name;
#else
    const char* base = getenv("XDG_CONFIG_HOME");
    std::filesystem::path config = base ? std::filesystem::path(base) : std::filesystem::path(getenv("HOME")) / ".config";
    config /= app_name;
#endif

    std::filesystem::create_directories(config);
    static std::string ini_file = (config / "imgui.ini").string();
    ImGui::GetIO().IniFilename = ini_file.c_str();
}

int DearImKit::SetupApp(std::string app_name, std::function<void(void)> at_start, std::function<void(void)> during_loop, const std::tuple<float, float, float, float>& background_color) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* p_window = glfwCreateWindow(START_WINDOW_WIDTH, START_WINDOW_HEIGHT, "Main", nullptr, nullptr);
    if (p_window == nullptr) {
        std::cout << "Failed to initialize window" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(p_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    initImGuiIniFile(app_name);

    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(p_window, true);
    ImGui_ImplOpenGL3_Init();

    glViewport(0, 0, START_WINDOW_WIDTH, START_WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(p_window, ::framebufferSizeCallback);

    at_start();

    while (!glfwWindowShouldClose(p_window)) {
        auto [r, g, b, a] = background_color;
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        initImGuiFrames();

        during_loop();
        runRenderingFunctions();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(p_window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

int DearImKit::SetupApp(std::string app_name, std::function<void(void)> at_start, const std::tuple<float, float, float, float>& background_color) {
    return DearImKit::SetupApp(app_name, at_start, []() {}, background_color);
}