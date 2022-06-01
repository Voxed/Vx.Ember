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

Primitive::Primitive(std::vector<glm::vec3> vertices,
    std::vector<glm::vec3> normals, std::vector<unsigned int> indices)
    : _vertices(std::move(vertices))
    , _normals(std::move(normals))
    , _indices(std::move(indices)) {
    _vao = VertexArrayObject();

    _vbo = BufferObject(sizeof(glm::vec3) * _vertices.size(), GL_MAP_WRITE_BIT,
        _vertices.data());
    _vao->enableVertexArrayAttrib(PositionLayoutPosition);
    _vao->attribFormat(PositionLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0);
    _vao->setAttribBinding(PositionLayoutPosition, 0);
    _vao->bindVertexBuffer(0, *_vbo, 0, sizeof(glm::vec3));

    _nbo = BufferObject(
        sizeof(glm::vec3) * _normals.size(), GL_MAP_WRITE_BIT, _normals.data());
    _vao->enableVertexArrayAttrib(NormalLayoutPosition);
    _vao->attribFormat(NormalLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0);
    _vao->setAttribBinding(NormalLayoutPosition, 1);
    _vao->bindVertexBuffer(1, *_nbo, 0, sizeof(glm::vec3));

    _ibo = BufferObject(sizeof(unsigned int) * _indices.size(),
        GL_MAP_WRITE_BIT, _indices.data());
    _vao->setElementBuffer(*_ibo);
}

void Primitive::render(Program& program) {
    program.bind();
    _vao->bind();

    // glDrawArrays(GL_TRIANGLES, 0, 1000);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
}
