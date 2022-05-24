//
// Created by voxed on 5/24/22.
//

#include "Program.h"
#include <glm/ext.hpp>

using namespace vx::ember;

Program::Program(std::vector<Shader> shaders) {
    _program = glCreateProgram();
    for(const auto& shader : shaders) {
        glAttachShader(_program, shader.id());
    }
    glLinkProgram(_program);

    GLint status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    if(status != GL_TRUE) {
        GLchar log[1024];
        glGetProgramInfoLog(_program, 1024, nullptr, log);

        printf("FAILED TO LINK PROGRAM:\n %s\n", log);
    }
}

void Program::bind() {
    glUseProgram(_program);
}

void Program::setViewMatrix(glm::mat4 viewMatrix) {
    bind();
    glUniformMatrix4fv(ViewMatrixLayoutPosition, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

void Program::setProjectionMatrix(glm::mat4 projectionMatrix) {
    bind();
    glUniformMatrix4fv(ProjectionMatrixLayoutPosition, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void Program::setModelMatrix(glm::mat4 modelMatrix) {
    bind();
    glUniformMatrix4fv(ModelMatrixLayoutPosition, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
