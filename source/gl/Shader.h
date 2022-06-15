//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_SHADER_H
#define VX_EMBER_SHADER_H

#include <GL/glew.h>
#include <memory>
#include <string>

namespace vx::ember {

class Program;

class Shader {
    GLuint _index;

    Shader(const std::string& name, GLenum type, const std::string& source);

public:
    ~Shader();

    static std::unique_ptr<Shader> create(const std::string& name, GLenum type, const std::string& source);

    friend Program;
};

}

#endif // VX_EMBER_SHADER_H
