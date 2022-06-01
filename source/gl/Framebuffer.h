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

public:
    Framebuffer();

    void bindTexture(
        Texture& texture, GLenum attachment, GLint level, GLint layer) const {
        glNamedFramebufferTextureLayer(
            _index, attachment, texture._index, level, layer);
    }

    void bindTexture(Texture& texture, GLenum attachment, GLint level) const {
        glNamedFramebufferTexture(_index, attachment, texture._index, level);
    }

    void bind(GLenum target) const { glBindFramebuffer(target, _index); }

    void drawBuffers(std::vector<GLenum> buffs) const {
        glNamedFramebufferDrawBuffers(_index, buffs.size(), buffs.data());
    }
};

}

#endif // VX_EMBER_FRAMEBUFFER_H
