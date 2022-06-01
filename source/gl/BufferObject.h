//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_BUFFEROBJECT_H
#define VX_EMBER_BUFFEROBJECT_H

#include <GL/glew.h>
#include <functional>
#include <memory>

namespace vx::ember {

class VertexArrayObject;

class BufferObject {
    GLuint _index = 0;

public:
    BufferObject(
        GLsizeiptr size, GLbitfield flags, void* initialData = nullptr) {
        glCreateBuffers(1, &_index);
        glNamedBufferStorage(_index, size, initialData, flags);
    }

    /*
     * Allocate a buffer object with enough space to contain a type.
     */
    template <typename T>
    static BufferObject allocate(GLbitfield flags, T* initialData = nullptr) {
        return { sizeof(T), flags, (void*)initialData };
    }

    /*
     * Allocate a buffer object pointer with enough space to contain a type.
     */
    template <typename T>
    static std::shared_ptr<BufferObject> allocatePtr(
        GLbitfield flags, T* initialData = nullptr) {
        return std::make_shared<BufferObject>(
            sizeof(T), flags, (void*)initialData);
    }

    std::shared_ptr<void> mapRange(
        GLintptr offset, GLsizeiptr length, GLbitfield access) {
        void* data = glMapNamedBufferRange(_index, offset, length, access);
        return { data, [this](void*) { glUnmapNamedBuffer(_index); } };
    }

    /*
     * Automatically map the buffer to a data type. No typechecking.
     */
    template <typename T>
    std::shared_ptr<T> mapRange(GLbitfield access, GLintptr offset = 0) {
        void* data = glMapNamedBufferRange(_index, offset, sizeof(T), access);
        return std::static_pointer_cast<T>(std::shared_ptr<void>(
            data, [this](void*) { glUnmapNamedBuffer(_index); }));
    }

    void bind(GLenum target, GLuint index) const {
        glBindBufferBase(target, index, _index);
    }

    void bind(GLenum target) const { glBindBuffer(target, _index); }

    friend VertexArrayObject;
};

}

#endif // VX_EMBER_BUFFEROBJECT_H
