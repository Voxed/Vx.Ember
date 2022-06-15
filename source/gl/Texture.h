//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_TEXTURE_H
#define VX_EMBER_TEXTURE_H

#include "core/Image.h"
#include <GL/glew.h>
#include <algorithm>
#include <memory>

namespace vx::ember {

class Framebuffer;

class Texture {
    GLuint _index;

    explicit Texture(GLenum target, GLint minFilter = -1, GLint magFilter = -1, GLint wrapS = -1, GLint wrapT = -1);

public:
    ~Texture();

    static std::unique_ptr<Texture> create(GLenum target, int width, int height, GLenum internalFormat, int levels,
        GLint minFilter = -1, GLint magFilter = -1, GLint wrapS = -1, GLint wrapT = -1);

    static std::unique_ptr<Texture> createMultisampled(GLenum target, int width, int height, GLenum internalFormat,
        GLsizei samples, GLint minFilter = -1, GLint magFilter = -1, GLint wrapS = -1, GLint wrapT = -1);

    static std::unique_ptr<Texture> create3D(GLenum target, int width, int height, int depth, GLenum internalFormat,
        GLsizei levels, GLint minFilter = -1, GLint magFilter = -1, GLint wrapS = -1, GLint wrapT = -1);

    static std::unique_ptr<Texture> createMultisampled3D(GLenum target, int width, int height, int depth,
        GLenum internalFormat, GLsizei samples, GLint minFilter = -1, GLint magFilter = -1, GLint wrapS = -1,
        GLint wrapT = -1);

    void setParameter(GLenum, GLint) const;
    void setParameterf(GLenum, GLfloat) const;

    void generateMipmaps() const;

    void subImage2D(const Image& image, GLint level = 0, GLint xoffset = 0, GLint yoffset = 0) const;

    void bind(GLuint unit) const;

    friend Framebuffer;
};

/*
 *     glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_normalBuffer);

// glGenTextures(1, &_normalBuffer);
// glBindTexture(GL_TEXTURE_CUBE_MAP, _normalBuffer);
glTextureParameteri(_normalBuffer, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTextureParameteri(_normalBuffer, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTextureStorage2D(
    _normalBuffer, 1, GL_RGBA16F, shadowResolution, shadowResolution);
for (int i = 0; i < 6; i++)
    glTextureSubImage3D(_normalBuffer, 0, 0, 0, i, shadowResolution,
        shadowResolution, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

*/

}

#endif // VX_EMBER_TEXTURE_H
