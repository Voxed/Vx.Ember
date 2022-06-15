//
// Created by voxed on 6/14/22.
//

#ifndef VX_EMBER_LIGHTPASS_H
#define VX_EMBER_LIGHTPASS_H

#include "core/Pass.h"
#include "gl/Framebuffer.h"
#include "gl/Program.h"
#include "gl/Texture.h"
#include "passes/common/RSMCache.h"

namespace vx::ember {

class LightPass : public Pass {
    std::unique_ptr<Texture>* _positionMap;
    std::unique_ptr<Texture>* _normalMap;
    std::unique_ptr<Texture>* _metallicMap;
    std::unique_ptr<Texture>* _colorMap;

    std::unique_ptr<Texture> _msLightMaps;
    // std::unique_ptr<Texture> _lightMaps;
    std::unique_ptr<Framebuffer> _msFramebuffer;
    // std::unique_ptr<Framebuffer> _framebuffer;
    unsigned int _lightMapCount = 0;

    RSMCache* _cache;

    GLuint quadVao;
    GLuint quadVbo;

    std::unique_ptr<Program> _program;

    int _width = 0;
    int _height = 0;

public:
    explicit LightPass(RSMCache& cache, std::unique_ptr<Texture>& positionMap, std::unique_ptr<Texture>& normalMap,
        std::unique_ptr<Texture>& metallicMap, std::unique_ptr<Texture>& colorMap);

    void initialize() override;
    void render(Node& root) override;
    void resize(int width, int height) override;
    void deinitialize() override;

    [[nodiscard]] unsigned int lightMapCount() const;
    std::unique_ptr<Texture>& lightMaps();
};

}

#endif // VX_EMBER_LIGHTPASS_H
