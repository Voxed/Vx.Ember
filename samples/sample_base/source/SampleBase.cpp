//
// Created by voxed on 5/20/22.
//

#include <cstdio>
#include "SampleBase.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

SampleBase::SampleBase(int width, int height, const char *name) : _width(width), _height(height) {
    glfwInit();

    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    glewExperimental = 1;
    glewInit();

    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0,0,width,height);
        auto* sampleBase = static_cast<SampleBase *>(glfwGetWindowUserPointer(window));
        sampleBase->resize(width, height);
    });
}

void SampleBase::exit() {
    _running = false;
}

void SampleBase::start() {
    initialize();
    resize(_width, _height);
    while (!glfwWindowShouldClose(window) && _running) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        mainLoop();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    deinitialize();

    glfwDestroyWindow(window);
    glfwTerminate();
}
