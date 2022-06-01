//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_VERTEXARRAYOBJECT_H
#define VX_EMBER_VERTEXARRAYOBJECT_H

#include "BufferObject.h"
#include <GL/glew.h>

namespace vx::ember {

class VertexArrayObject {

public:
    VertexArrayObject() { glCreateVertexArrays(1, &_index); }

    void enableVertexArrayAttrib(GLuint location) const {
        glEnableVertexArrayAttrib(_index, location);
    }

    void attribFormat(GLuint location, GLint count, GLenum type,
        GLboolean normalized, GLuint offset) const {
        glVertexArrayAttribFormat(
            _index, location, count, type, normalized, offset);
    }

    void setAttribBinding(GLuint location, GLuint binding) const {
        glVertexArrayAttribBinding(_index, location, binding);
    }

    void bindVertexBuffer(GLuint binding, BufferObject& bufferObject,
        GLintptr offset, GLsizei stride) const {
        glVertexArrayVertexBuffer(
            _index, binding, bufferObject._index, offset, stride);
    }

    void bind() const { glBindVertexArray(_index); }

    void setElementBuffer(BufferObject& bufferObject) const {
        glVertexArrayElementBuffer(_index, bufferObject._index);
    }
    GLuint _index = 0;
};

/**
 * glEnableVertexArrayAttrib(vao, PositionLayoutPosition);
glVertexArrayAttribFormat(
    vao, PositionLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0);
glVertexArrayAttribBinding(vao, PositionLayoutPosition, 0);
glVertexArrayVertexBuffer(vao, 0, _vbo->index(), 0, sizeof(glm::vec3));
 */

}

#endif // VX_EMBER_VERTEXARRAYOBJECT_H
