//
// Created by voxed on 5/24/22.
//

#include "Program.h"
#include <glm/ext.hpp>

using namespace vx::ember;

Program::Program(std::vector<Shader*> shaders) {
    _program = glCreateProgram();
    for (const auto& shader : shaders) {
        glAttachShader(_program, shader->_index);
    }
    glLinkProgram(_program);

    GLint status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        GLchar log[1024];
        glGetProgramInfoLog(_program, 1024, nullptr, log);

        printf("FAILED TO LINK PROGRAM:\n %s\n", log);
    }
}

void Program::bind() { glUseProgram(_program); }