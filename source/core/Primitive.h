//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_PRIMITIVE_H
#define VX_EMBER_PRIMITIVE_H

#include "Material.h"
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
    std::vector<glm::vec2> _textureCoords;
    std::vector<glm::vec4> _tangents;
    std::vector<unsigned int> _indices;

    std::unique_ptr<VertexArrayObject> _vao;
    std::unique_ptr<BufferObject> _vbo;
    std::unique_ptr<BufferObject> _nbo;
    std::unique_ptr<BufferObject> _tbo;
    std::unique_ptr<BufferObject> _tabo;
    std::unique_ptr<BufferObject> _ibo;

    std::array<glm::vec3, 2> _bounds;

    unsigned int _materialIndex;

public:
    Primitive(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> _textureCoords,
        std::vector<glm::vec4> tangents, std::vector<unsigned int> indices, unsigned int materialIndex);

    std::span<glm::vec3> vertices();

    std::span<glm::vec3> normals();

    std::span<unsigned int> indices();

    std::array<glm::vec3, 2> bounds();

    void render(Program& program);

    [[nodiscard]] unsigned int materialIndex() const;
};

}

#endif // VX_EMBER_PRIMITIVE_H
