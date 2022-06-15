//
// Created by voxed on 5/29/22.
//

#include "RSMFramebuffer.h"

using namespace vx::ember;

RSMFramebuffer::RSMFramebuffer() {
    /*_normalBuffer = Texture::create(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution, GL_RGBA16F, 1, GL_LINEAR,
        GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    _positionBuffer = Texture::create(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution, GL_RGB32F, 1, GL_NEAREST,
        GL_NEAREST, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    _colorBuffer = Texture::create(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution, GL_RGBA16F, 1, GL_LINEAR,
        GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    _metallicRoughnessTexture = Texture::create(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution, GL_RGBA16F, 1,
        GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    _emissionBuffer = Texture::create(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution, GL_RGBA16F, 1, GL_LINEAR,
        GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);*/
    _depthBuffer = Texture::create(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution, GL_DEPTH_COMPONENT32, 4,
        GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    //_depthBuffer->setParameterf(GL_TEXTURE_MAX_ANISOTROPY, 8.0f);

    _framebuffer = Framebuffer::create();
    /*_framebuffer->drawBuffers({ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
       GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 });*/
}

void RSMFramebuffer::bind(GLint face) {
    _framebuffer->bind(GL_FRAMEBUFFER);

    //_framebuffer->bindTexture(*_normalBuffer, GL_COLOR_ATTACHMENT0, 0, face);
    //_framebuffer->bindTexture(*_positionBuffer, GL_COLOR_ATTACHMENT1, 0, face);
    _framebuffer->bindTexture(*_depthBuffer, GL_DEPTH_ATTACHMENT, 0, face);

    /*_framebuffer->bindTexture(*_colorBuffer, GL_COLOR_ATTACHMENT2, 0, face);
    _framebuffer->bindTexture(*_metallicRoughnessTexture, GL_COLOR_ATTACHMENT3, 0, face);
    _framebuffer->bindTexture(*_emissionBuffer, GL_COLOR_ATTACHMENT4, 0, face);*/
}

Texture& RSMFramebuffer::positionTexture() { return *_positionBuffer; }

Texture& RSMFramebuffer::depthTexture() { return *_depthBuffer; }

Texture& RSMFramebuffer::normalTexture() { return *_normalBuffer; }

int RSMFramebuffer::height() const { return shadowResolution; }

int RSMFramebuffer::width() const { return shadowResolution; }

Texture& RSMFramebuffer::colorTexture() { return *_colorBuffer; }
Texture& RSMFramebuffer::metallicRoughnessTexture() { return *_metallicRoughnessTexture; }
Texture& RSMFramebuffer::emissionTexture() { return *_emissionBuffer; }