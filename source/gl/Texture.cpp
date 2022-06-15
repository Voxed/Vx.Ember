//
// Created by voxed on 5/31/22.
//

#include "Texture.h"

using namespace vx::ember;

void Texture::bind(GLuint unit) const { glBindTextureUnit(unit, _index); }

Texture::Texture(GLenum target, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT)
    : _index(-1) {
    glCreateTextures(target, 1, &_index);
    if (minFilter >= 0)
        glTextureParameteri(_index, GL_TEXTURE_MIN_FILTER, minFilter);
    if (magFilter >= 0)
        glTextureParameteri(_index, GL_TEXTURE_MAG_FILTER, magFilter);
    if (wrapS >= 0)
        glTextureParameteri(_index, GL_TEXTURE_WRAP_S, wrapS);
    if (wrapT >= 0)
        glTextureParameteri(_index, GL_TEXTURE_WRAP_T, wrapT);
    // glTextureStorage2D(_index, levels, internalFormat, width, height);
}

std::unique_ptr<Texture> Texture::create(GLenum target, int width, int height, GLenum internalFormat, int levels,
    GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) {
    auto* t = new Texture(target, minFilter, magFilter, wrapS, wrapT);
    glTextureStorage2D(t->_index, levels, internalFormat, width, height);
    return std::unique_ptr<Texture>(t);
}

// Note: Multisampled textures use identical sample points which might be bad. From what I understand it's important
// to have the same samples on all G-Buffers
std::unique_ptr<Texture> Texture::createMultisampled(GLenum target, int width, int height, GLenum internalFormat,
    GLsizei samples, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) {
    auto* t = new Texture(target, minFilter, magFilter, wrapS, wrapT);
    glTextureStorage2DMultisample(t->_index, samples, internalFormat, width, height, GL_TRUE);
    return std::unique_ptr<Texture>(t);
}

std::unique_ptr<Texture> Texture::createMultisampled3D(GLenum target, int width, int height, int depth,
    GLenum internalFormat, GLsizei samples, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) {
    auto* t = new Texture(target, minFilter, magFilter, wrapS, wrapT);
    glTextureStorage3DMultisample(t->_index, samples, internalFormat, width, height, depth, GL_TRUE);
    return std::unique_ptr<Texture>(t);
}

std::unique_ptr<Texture> Texture::create3D(GLenum target, int width, int height, int depth, GLenum internalFormat,
    GLsizei levels, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapT) {
    auto* t = new Texture(target, minFilter, magFilter, wrapS, wrapT);
    glTextureStorage3D(t->_index, levels, internalFormat, width, height, depth);
    return std::unique_ptr<Texture>(t);
}

Texture::~Texture() { glDeleteTextures(1, &_index); }

void Texture::subImage2D(const Image& image, GLint level, GLint xoffset, GLint yoffset) const {
    glTextureSubImage2D(_index, level, xoffset, yoffset, image.width(), image.height(), image.format(), image.type(),
        image.data().data());
}
void Texture::setParameter(GLenum parameter, GLint value) const { glTextureParameteri(_index, parameter, value); }
void Texture::setParameterf(GLenum parameter, GLfloat value) const { glTextureParameterf(_index, parameter, value); }
void Texture::generateMipmaps() const { glGenerateTextureMipmap(_index); }