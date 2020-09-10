#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imstb_truetype.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//===========================================================================================
// function prototypes
//===========================================================================================
void initialize_imgui(GLFWwindow* window);
static void glfw_error_callback(int error, const char* description);
void initialize_gl_loader();
GLFWwindow* create_window(unsigned int width, unsigned int height, const char* title);
void show_menu();
//===========================================================================================
// main programs
//===========================================================================================
static void glfw_error_callback(int error, const char* description) {
std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main(int, char**) {
    GLFWwindow* window = create_window(800, 400, "Next GIS");
    initialize_gl_loader();
    initialize_imgui(window);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        show_menu();
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* create_window(unsigned int width, unsigned int height, const char* title) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#endif
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
}

void initialize_gl_loader() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void initialize_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.Fonts->AddFontFromFileTTF("../misc/SourceSans-Regular.ttf", 20);
    // Setup style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void show_menu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::BeginMenu("Open Recent")) {
                ImGui::MenuItem("quadtree-py");
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save as")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Export")) {}
            if (ImGui::MenuItem("Exit")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Settings")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Vector")) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Raster")) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}