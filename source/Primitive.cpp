//
// Created by voxed on 5/20/22.
//

#include "Primitive.h"
#include "Program.h"

#include <utility>

using namespace vx::ember;

std::span<glm::vec3> Primitive::vertices() {
    return _vertices;
}

std::span<glm::vec3> Primitive::normals() {
    return _normals;
}

std::span<unsigned int> Primitive::indices() {
    return _indices;
}

Primitive::Primitive(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                     std::vector<unsigned int> indices) : _vertices(std::move(vertices)), _normals(std::move(normals)),
                                                          _indices(std::move(indices)) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_vertices.size(), _vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(PositionLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(PositionLayoutPosition);

    glGenBuffers(1, &nbo);
    glBindBuffer(GL_ARRAY_BUFFER, nbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*_normals.size(), _normals.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(NormalLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(NormalLayoutPosition);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*_indices.size(), _indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Primitive::render(Program& program) {
    program.bind();
    glBindVertexArray(vao);
    //glDrawArrays(GL_TRIANGLES, 0, 1000);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, (void*)0);
}
