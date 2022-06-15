//
// Created by voxed on 5/31/22.
//

#include "BufferObject.h"

using namespace vx::ember;

BufferObject::BufferObject(GLsizeiptr size, GLbitfield flags, void* initialData) {
    glCreateBuffers(1, &_index);
    glNamedBufferStorage(_index, size, initialData, flags);
}

BufferObject::~BufferObject() { glDeleteBuffers(1, &_index); }
std::unique_ptr<BufferObject> BufferObject::create(GLsizei size, GLbitfield flags, void* initialData) {
    return std::unique_ptr<BufferObject>(new BufferObject(size, flags, (void*)initialData));
}

std::shared_ptr<void> BufferObject::mapRange(GLintptr offset, GLsizeiptr length, GLbitfield access) {
    void* data = glMapNamedBufferRange(_index, offset, length, access);
    return { data, [this](void*) { glUnmapNamedBuffer(_index); } };
}

void BufferObject::bind(GLenum target, GLuint index) const { glBindBufferBase(target, index, _index); }

void BufferObject::bind(GLenum target) const { glBindBuffer(target, _index); }
