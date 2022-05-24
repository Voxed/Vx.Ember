//
// Created by voxed on 5/24/22.
//

#include "Shader.h"

using namespace vx::ember;

Shader::Shader(ShaderType type, std::string source) {
    _id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(_id, 1, &src, nullptr);

    glCompileShader(_id);
    GLint status;
    glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
        GLchar log[1024];
        glGetShaderInfoLog(_id, 1024, nullptr, log);

        printf("FAILED TO COMPILE SHADER:\n %s\n", log);
    }
}

GLuint Shader::id() const {
    return _id;
}
