//
// Created by voxed on 5/24/22.
//

#include "Program.h"

using namespace vx::ember;

Program::Program(const std::vector<Shader*>& shaders) {
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

void Program::bind() const { glUseProgram(_program); }

std::unique_ptr<Program> Program::create(const std::vector<Shader*>& shaders) {
    return std::unique_ptr<Program>(new Program(shaders));
}

Program::~Program() { glDeleteProgram(_program); }

void Program::setUniform(GLint location, glm::mat4 matrix) const {
    glProgramUniformMatrix4fv(_program, location, 1, GL_FALSE, &matrix[0][0]);
}

void Program::setUniform(GLint location, glm::vec3 v) const { glProgramUniform3fv(_program, location, 1, (float*)&v); }
