//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_SAMPLEBASE_H
#define VX_EMBER_SAMPLEBASE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class SampleBase {
    GLFWwindow *window;
    bool _running = true;
    int _width, _height;

    virtual void initialize() = 0;

    virtual void mainLoop() = 0;

    virtual void resize(int width, int height) = 0;

    virtual void deinitialize() = 0;

public:
    SampleBase(int width, int height, const char *name);

    void exit();

    void start();
};


#endif //VX_EMBER_SAMPLEBASE_H
