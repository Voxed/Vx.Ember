//
// Created by voxed on 5/20/22.
//

#include "Primitive.h"
#include "gl/Program.h"

#include <utility>

using namespace vx::ember;

std::span<glm::vec3> Primitive::vertices() { return _vertices; }

std::span<glm::vec3> Primitive::normals() { return _normals; }

std::span<unsigned int> Primitive::indices() { return _indices; }

Primitive::Primitive(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
    std::vector<glm::vec2> textureCoords, std::vector<glm::vec4> tangents, std::vector<unsigned int> indices,
    unsigned int materialIndex)
    : _vertices(std::move(vertices))
    , _normals(std::move(normals))
    , _indices(std::move(indices))
    , _textureCoords(std::move(textureCoords))
    , _tangents(std::move(tangents))
    , _materialIndex(materialIndex) {
    _vao = VertexArrayObject::create();

    _vbo = BufferObject::create((GLsizei)sizeof(glm::vec3) * _vertices.size(), GL_MAP_WRITE_BIT, _vertices.data());
    _vao->enableVertexArrayAttrib(PositionLayoutPosition);
    _vao->attribFormat(PositionLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0);
    _vao->setAttribBinding(PositionLayoutPosition, 0);
    _vao->bindVertexBuffer(0, *_vbo, 0, sizeof(glm::vec3));

    _nbo = BufferObject::create((GLsizei)sizeof(glm::vec3) * _normals.size(), GL_MAP_WRITE_BIT, _normals.data());
    _vao->enableVertexArrayAttrib(NormalLayoutPosition);
    _vao->attribFormat(NormalLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0);
    _vao->setAttribBinding(NormalLayoutPosition, 1);
    _vao->bindVertexBuffer(1, *_nbo, 0, sizeof(glm::vec3));

    _tbo = BufferObject::create(
        (GLsizei)sizeof(glm::vec2) * _textureCoords.size(), GL_MAP_WRITE_BIT, _textureCoords.data());
    _vao->enableVertexArrayAttrib(2);
    _vao->attribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
    _vao->setAttribBinding(2, 2);
    _vao->bindVertexBuffer(2, *_tbo, 0, sizeof(glm::vec2));

    _tabo = BufferObject::create((GLsizei)sizeof(glm::vec4) * _tangents.size(), GL_MAP_WRITE_BIT, _tangents.data());
    _vao->enableVertexArrayAttrib(3);
    _vao->attribFormat(3, 4, GL_FLOAT, GL_FALSE, 0);
    _vao->setAttribBinding(3, 3);
    _vao->bindVertexBuffer(3, *_tabo, 0, sizeof(glm::vec4));

    _ibo = BufferObject::create((GLsizei)sizeof(unsigned int) * _indices.size(), GL_MAP_WRITE_BIT, _indices.data());
    _vao->setElementBuffer(*_ibo);

    _bounds = { glm::vec3(std::numeric_limits<float>::infinity()), glm::vec3(-std::numeric_limits<float>::infinity()) };
    for (const auto& v : _vertices) {
        _bounds = { glm::min(v, _bounds[0]), glm::max(v, _bounds[1]) };
    }
}

void Primitive::render(Program& program) {
    program.bind();
    _vao->bind();

    // glDrawArrays(GL_TRIANGLES, 0, 1000);
    glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, 0);
}

unsigned int Primitive::materialIndex() const { return _materialIndex; }

std::array<glm::vec3, 2> Primitive::bounds() { return _bounds; }
