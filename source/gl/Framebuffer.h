//
// Created by voxed on 5/31/22.
//

#ifndef VX_EMBER_FRAMEBUFFER_H
#define VX_EMBER_FRAMEBUFFER_H

#include "Texture.h"

#include <GL/glew.h>
#include <vector>

namespace vx::ember {

class Framebuffer {
    GLuint _index;
    std::vector<GLenum> _drawBuffers; // Keep track of draw buffers to allow
                                      // resetting after blit.

    Framebuffer();

public:
    ~Framebuffer();

    static std::unique_ptr<Framebuffer> create();

    void bindTexture(Texture& texture, GLenum attachment, GLint level, GLint layer) const;

    void bindTexture(Texture& texture, GLenum attachment, GLint level = 0) const;

    void bind(GLenum target) const;

    void blit(Framebuffer& to, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0,
        GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const;

    void blitColorAttachments(Framebuffer& to, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
        GLint dstY0, GLint dstX1, GLint dstY1, const std::vector<GLenum>& colorAttachment, GLenum filter) const;

    void drawBuffers(std::vector<GLenum> buffs);
};

}

#endif // VX_EMBER_FRAMEBUFFER_H
