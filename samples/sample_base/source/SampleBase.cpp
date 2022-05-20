//
// Created by voxed on 5/20/22.
//

#include "SampleBase.h"

SampleBase::SampleBase(int width, int height, const char *name) {
    glfwInit();

    window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = 1;
    glewInit();

    glfwSwapInterval(1);
}

void SampleBase::exit() {
    _running = false;
}

void SampleBase::start() {
    initialize();

    while (!glfwWindowShouldClose(window) && _running) {
        glfwPollEvents();
        mainLoop();
        glfwSwapBuffers(window);
    }
}
