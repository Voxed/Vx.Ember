//
// Created by voxed on 5/29/22.
//

#include "GeometryFramebuffer.h"
#include <vector>

using namespace vx::ember;

void GeometryFramebuffer::resize(int width, int height) {
    _width = width;
    _height = height;

    glGenTextures(1, &_normalBuffer);
    glBindTexture(GL_TEXTURE_2D, _normalBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &_positionBuffer);
    glBindTexture(GL_TEXTURE_2D, _positionBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA,
        GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &_depthBuffer);
    glBindTexture(GL_TEXTURE_2D, _depthBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glGenFramebuffers(1, &_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    // bind texture as colour attachment
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _normalBuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
        _positionBuffer, 0);
    std::vector<GLuint> drawBuffers { GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, drawBuffers.data());
    // bind the texture as depth attchment
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthBuffer, 0);
}

void GeometryFramebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

GLuint GeometryFramebuffer::positionTexture() const { return _positionBuffer; }

GLuint GeometryFramebuffer::depthTexture() const { return _depthBuffer; }

GLuint GeometryFramebuffer::normalTexture() const { return _normalBuffer; }