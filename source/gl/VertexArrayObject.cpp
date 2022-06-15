//
// Created by voxed on 5/31/22.
//

#include "VertexArrayObject.h"

using namespace vx::ember;

std::unique_ptr<VertexArrayObject> VertexArrayObject::create() {
    return std::unique_ptr<VertexArrayObject>(new VertexArrayObject);
}

VertexArrayObject::~VertexArrayObject() { glDeleteTextures(1, &_index); }

VertexArrayObject::VertexArrayObject() { glCreateVertexArrays(1, &_index); }

void VertexArrayObject::attribFormat(
    GLuint location, GLint count, GLenum type, GLboolean normalized, GLuint offset) const {
    glVertexArrayAttribFormat(_index, location, count, type, normalized, offset);
}

void VertexArrayObject::enableVertexArrayAttrib(GLuint location) const { glEnableVertexArrayAttrib(_index, location); }

void VertexArrayObject::setAttribBinding(GLuint location, GLuint binding) const {
    glVertexArrayAttribBinding(_index, location, binding);
}

void VertexArrayObject::bindVertexBuffer(
    GLuint binding, BufferObject& bufferObject, GLintptr offset, GLsizei stride) const {
    glVertexArrayVertexBuffer(_index, binding, bufferObject._index, offset, stride);
}

void VertexArrayObject::bind() const { glBindVertexArray(_index); }

void VertexArrayObject::setElementBuffer(BufferObject& bufferObject) const {
    glVertexArrayElementBuffer(_index, bufferObject._index);
}
