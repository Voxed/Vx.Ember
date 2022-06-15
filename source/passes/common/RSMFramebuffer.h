//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_RSMFRAMEBUFFER_H
#define VX_EMBER_RSMFRAMEBUFFER_H

#include "gl/Framebuffer.h"
#include "gl/Texture.h"

#include <GL/glew.h>
#include <memory>
#include <optional>

namespace vx::ember {

class RSMFramebuffer {
    std::unique_ptr<Texture> _depthBuffer;
    std::unique_ptr<Texture> _normalBuffer;
    std::unique_ptr<Texture> _positionBuffer;
    std::unique_ptr<Texture> _colorBuffer;
    std::unique_ptr<Texture> _metallicRoughnessTexture;
    std::unique_ptr<Texture> _emissionBuffer;

    std::unique_ptr<Framebuffer> _framebuffer;

    const int shadowResolution = 1024;
    const int shadowSamples = 1;

public:
    RSMFramebuffer();

    void bind(GLint face);

    Texture& normalTexture();
    Texture& depthTexture();
    Texture& positionTexture();

    Texture& colorTexture();
    Texture& metallicRoughnessTexture();
    Texture& emissionTexture();

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
};

}

#endif // VX_EMBER_RSMFRAMEBUFFER_H
