//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_SHADER_H
#define VX_EMBER_SHADER_H

#include <string>
#include <GL/glew.h>

namespace vx::ember {

    enum ShaderType {
        FragmentShader = GL_FRAGMENT_SHADER,
        VertexShader = GL_VERTEX_SHADER,
        ComputeShader = GL_COMPUTE_SHADER
    };

    class Shader {
        GLuint _id;
    public:
        Shader(ShaderType type, std::string source);
        [[nodiscard]] GLuint id() const;
    };

}

#endif //VX_EMBER_SHADER_H
