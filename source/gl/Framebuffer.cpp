//
// Created by voxed on 5/31/22.
//

#include "Framebuffer.h"

using namespace vx::ember;

Framebuffer::Framebuffer()
    : _index(-1) {
    glCreateFramebuffers(1, &_index);
}

Framebuffer::~Framebuffer() { glDeleteFramebuffers(1, &_index); }

std::unique_ptr<Framebuffer> Framebuffer::create() { return std::unique_ptr<Framebuffer>(new Framebuffer); }

void Framebuffer::bindTexture(Texture& texture, GLenum attachment, GLint level, GLint layer) const {
    glNamedFramebufferTextureLayer(_index, attachment, texture._index, level, layer);
}

void Framebuffer::bindTexture(Texture& texture, GLenum attachment, GLint level) const {
    glNamedFramebufferTexture(_index, attachment, texture._index, level);
}

void Framebuffer::bind(GLenum target) const { glBindFramebuffer(target, _index); }

void Framebuffer::drawBuffers(std::vector<GLenum> buffs) {
    _drawBuffers = buffs;
    glNamedFramebufferDrawBuffers(_index, (GLsizei)buffs.size(), buffs.data());
}

void Framebuffer::blit(Framebuffer& to, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,
    GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
    glBlitNamedFramebuffer(_index, to._index, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void Framebuffer::blitColorAttachments(Framebuffer& to, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
    GLint dstY0, GLint dstX1, GLint dstY1, const std::vector<GLenum>& colorAttachments, GLenum filter) const {
    for (const auto& colorAttachment : colorAttachments) {
        glNamedFramebufferDrawBuffer(to._index, colorAttachment);
        glNamedFramebufferReadBuffer(_index, colorAttachment);

        blit(to, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, GL_COLOR_BUFFER_BIT, filter);
    }

    to.drawBuffers(to._drawBuffers); // reset draw buffers.
}
