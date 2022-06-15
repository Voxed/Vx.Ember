//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_VERTEXARRAYOBJECT_H
#define VX_EMBER_VERTEXARRAYOBJECT_H

#include "BufferObject.h"

#include <GL/glew.h>

namespace vx::ember {

class VertexArrayObject {
    VertexArrayObject();

public:
    ~VertexArrayObject();

    static std::unique_ptr<VertexArrayObject> create();

    void enableVertexArrayAttrib(GLuint location) const;

    void attribFormat(GLuint location, GLint count, GLenum type, GLboolean normalized, GLuint offset) const;

    void setAttribBinding(GLuint location, GLuint binding) const;

    void bindVertexBuffer(GLuint binding, BufferObject& bufferObject, GLintptr offset, GLsizei stride) const;

    void bind() const;

    void setElementBuffer(BufferObject& bufferObject) const;

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
