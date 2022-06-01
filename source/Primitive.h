//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_PRIMITIVE_H
#define VX_EMBER_PRIMITIVE_H

#include "gl/BufferObject.h"
#include "gl/VertexArrayObject.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <optional>
#include <span>
#include <vector>

namespace vx::ember {

class Program;

class Primitive {
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec3> _normals;
    std::vector<unsigned int> _indices;

    GLuint vao;
    GLuint nbo;
    GLuint ibo;

    std::optional<VertexArrayObject> _vao;
    std::optional<BufferObject> _vbo;
    std::optional<BufferObject> _nbo;
    std::optional<BufferObject> _ibo;

public:
    Primitive(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
        std::vector<unsigned int> indices);

    std::span<glm::vec3> vertices();

    std::span<glm::vec3> normals();

    std::span<unsigned int> indices();

    void render(Program& program);
};

}

#endif // VX_EMBER_PRIMITIVE_H
