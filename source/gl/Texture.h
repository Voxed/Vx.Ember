//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_TEXTURE_H
#define VX_EMBER_TEXTURE_H

#include <GL/glew.h>
namespace vx::ember {

class Framebuffer;

class Texture {

public:
    GLuint _index;

    Texture(GLenum target, int width, int height, GLint minFilter,
        GLint magFilter, GLenum internalFormat, int levels) {
        glCreateTextures(target, 1, &_index);
        glTextureParameteri(_index, GL_TEXTURE_MIN_FILTER, minFilter);
        glTextureParameteri(_index, GL_TEXTURE_MAG_FILTER, magFilter);
        glTextureStorage2D(_index, levels, internalFormat, width, height);
    }

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
