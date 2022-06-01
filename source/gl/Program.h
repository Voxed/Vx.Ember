//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_PROGRAM_H
#define VX_EMBER_PROGRAM_H

#include "Shader.h"
#include <glm/matrix.hpp>
#include <string>
#include <vector>

namespace vx::ember {

enum LayoutPosition {
    // Attributes
    PositionLayoutPosition = 0,
    NormalLayoutPosition = 1,

    // Uniforms
    ModelMatrixLayoutPosition = 0,
    ViewMatrixLayoutPosition = 1,
    ProjectionMatrixLayoutPosition = 2,
};

struct MatrixBlock {
    glm::mat4 v;
    glm::mat4 p;
};

class Program {
    GLuint _program;

public:
    explicit Program(std::vector<Shader*> shaders);

    void bind();

    void setUniform(GLint location, glm::mat4 matrix) {
        glProgramUniformMatrix4fv(
            _program, location, 1, GL_FALSE, &matrix[0][0]);
    }

    /*void setModelMatrix(glm::mat4 modelMatrix);

    void setViewMatrix(glm::mat4 viewMatrix);

    void setProjectionMatrix(glm::mat4 projectionMatrix);*/
};

}

#endif // VX_EMBER_PROGRAM_H
