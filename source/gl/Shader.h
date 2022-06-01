//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_SHADER_H
#define VX_EMBER_SHADER_H

#include <GL/glew.h>
#include <string>

namespace vx::ember {

class Program;

class Shader {
    GLuint _index;

public:
    Shader(std::string name, GLenum type, std::string source);

    friend Program;
};

}

#endif // VX_EMBER_SHADER_H
