//
// Created by voxed on 5/24/22.
//

#include "Shader.h"

#include "core/exceptions.h"

using namespace vx::ember;

static std::string shaderTypeString(GLenum type) {
    switch (type) {
    case GL_FRAGMENT_SHADER:
        return "Fragment";
    case GL_VERTEX_SHADER:
        return "Vertex";
    case GL_GEOMETRY_SHADER:
        return "Geometry";
    default:
        return "Undefined";
    }
}

Shader::Shader(const std::string& name, GLenum type, const std::string& source) {
    _index = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(_index, 1, &src, nullptr);

    glCompileShader(_index);
    GLint status;
    glGetShaderiv(_index, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        GLchar log[1024];
        glGetShaderInfoLog(_index, 1024, nullptr, log);

        throw ShaderCompileException(shaderTypeString(type), name, log);
    }
}
std::unique_ptr<Shader> Shader::create(const std::string& name, GLenum type, const std::string& source) {
    return std::unique_ptr<Shader>(new Shader(name, type, source));
}

Shader::~Shader() { glDeleteShader(_index); }
