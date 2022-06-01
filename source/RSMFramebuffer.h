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
    std::shared_ptr<Texture> _depthBuffer;
    std::shared_ptr<Texture> _normalBuffer;
    std::shared_ptr<Texture> _positionBuffer;

    std::optional<Framebuffer> _framebuffer;

    bool _initialized = false;

    const int shadowResolution = 512;

public:
    RSMFramebuffer();

    void bind(GLint face);

    [[nodiscard]] std::shared_ptr<Texture> normalTexture() const;
    [[nodiscard]] std::shared_ptr<Texture> depthTexture() const;
    [[nodiscard]] std::shared_ptr<Texture> positionTexture() const;

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
};

}

#endif // VX_EMBER_RSMFRAMEBUFFER_H
