//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_BUFFEROBJECT_H
#define VX_EMBER_BUFFEROBJECT_H

#include <GL/glew.h>
#include <functional>
#include <memory>
#include <spdlog/spdlog.h>

namespace vx::ember {

class VertexArrayObject;

class BufferObject {
    GLuint _index = 0;

    BufferObject(GLsizeiptr size, GLbitfield flags, void* initialData = nullptr);

public:
    ~BufferObject();

    /*
     * Allocate a buffer object with enough space to contain a type.
     */
    template <typename T> static std::unique_ptr<BufferObject> create(GLbitfield flags, T* initialData = nullptr) {
        return std::unique_ptr<BufferObject>(new BufferObject(sizeof(T), flags, (void*)initialData));
    }

    static std::unique_ptr<BufferObject> create(GLsizei size, GLbitfield flags, void* initialData = nullptr);

    std::shared_ptr<void> mapRange(GLintptr offset, GLsizeiptr length, GLbitfield access);

    /*
     * Automatically map the buffer to a data type. No typechecking.
     */
    template <typename T> std::shared_ptr<T> mapRange(GLbitfield access, GLintptr offset = 0) {
        void* data = glMapNamedBufferRange(_index, offset, sizeof(T), access);
        return std::static_pointer_cast<T>(std::shared_ptr<void>(data, [this](void*) { glUnmapNamedBuffer(_index); }));
    }

    void bind(GLenum target, GLuint index) const;

    void bind(GLenum target) const;

    friend VertexArrayObject;
};

}

#endif // VX_EMBER_BUFFEROBJECT_H
