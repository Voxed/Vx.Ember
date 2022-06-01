//
// Created by voxed on 5/29/22.
//

#include "RSMFramebuffer.h"
#include <vector>

using namespace vx::ember;

RSMFramebuffer::RSMFramebuffer() {
    _normalBuffer = std::make_shared<Texture>(
        Texture(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution,
            GL_LINEAR, GL_LINEAR, GL_RGBA16F, 1));

    _positionBuffer = std::make_shared<Texture>(
        Texture(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution,
            GL_LINEAR, GL_LINEAR, GL_RGBA16F, 1));

    _depthBuffer = std::make_shared<Texture>(
        Texture(GL_TEXTURE_CUBE_MAP, shadowResolution, shadowResolution,
            GL_LINEAR, GL_LINEAR, GL_DEPTH_COMPONENT32, 1));

    _framebuffer = Framebuffer();
}

void RSMFramebuffer::bind(GLint face) {
    _framebuffer->bind(GL_FRAMEBUFFER);

    _framebuffer->bindTexture(*_normalBuffer, GL_COLOR_ATTACHMENT0, 0,
        face - GL_TEXTURE_CUBE_MAP_POSITIVE_X);

    _framebuffer->bindTexture(*_positionBuffer, GL_COLOR_ATTACHMENT1, 0,
        face - GL_TEXTURE_CUBE_MAP_POSITIVE_X);

    std::vector<GLuint> drawBuffers { GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1 };

    _framebuffer->drawBuffers({ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 });

    _framebuffer->bindTexture(*_depthBuffer, GL_DEPTH_ATTACHMENT, 0,
        face - GL_TEXTURE_CUBE_MAP_POSITIVE_X);
}

std::shared_ptr<Texture> RSMFramebuffer::positionTexture() const {
    return _positionBuffer;
}

std::shared_ptr<Texture> RSMFramebuffer::depthTexture() const {
    return _depthBuffer;
}

std::shared_ptr<Texture> RSMFramebuffer::normalTexture() const {
    return _normalBuffer;
}

int RSMFramebuffer::height() const { return shadowResolution; }

int RSMFramebuffer::width() const { return shadowResolution; }
