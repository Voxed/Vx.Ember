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
};

struct MatrixBlock {
    glm::mat4 v;
    glm::mat4 p;
};

struct LightBlock {
    glm::vec3 color;
    float _dummy0;
    float intensity;
};

class Program {
    GLuint _program;

    explicit Program(const std::vector<Shader*>& shaders);

public:
    ~Program();

    static std::unique_ptr<Program> create(const std::vector<Shader*>& shaders);

    void bind() const;

    void setUniform(GLint location, glm::mat4 matrix) const;

    void setUniform(GLint location, glm::vec3 v) const;
};

}

#endif // VX_EMBER_PROGRAM_H
