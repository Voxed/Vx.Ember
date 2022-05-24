//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_PROGRAM_H
#define VX_EMBER_PROGRAM_H

#include <string>
#include <vector>
#include "Shader.h"
#include <glm/matrix.hpp>

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

    class Program {
        GLuint _program;
    public:
        explicit Program(std::vector<Shader> shaders);

        void bind();

        void setModelMatrix(glm::mat4 modelMatrix);

        void setViewMatrix(glm::mat4 viewMatrix);

        void setProjectionMatrix(glm::mat4 projectionMatrix);
    };

}


#endif //VX_EMBER_PROGRAM_H
