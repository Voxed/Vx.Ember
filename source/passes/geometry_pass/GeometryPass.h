//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_GEOMETRYPASS_H
#define VX_EMBER_GEOMETRYPASS_H

#include "core/Pass.h"
#include "gl/BufferObject.h"
#include "gl/Framebuffer.h"
#include "gl/Program.h"
#include "gl/Shader.h"
#include "gl/Texture.h"

#include <GL/glew.h>
#include <memory>
#include <optional>

namespace vx::ember {

class Node;

/**
 * This pass creates relevant G-buffers for shading.
 */
class GeometryPass : public Pass {
    std::unique_ptr<Program> _program;
    int _width, _height;
    std::unique_ptr<BufferObject> matrixUBO;
    
    std::unique_ptr<Texture> _msDepthBuffer;
    std::unique_ptr<Texture> _msNormalBuffer;
    std::unique_ptr<Texture> _msPositionBuffer;
    std::unique_ptr<Texture> _msColorBuffer;
    std::unique_ptr<Texture> _msMetallicRoughnessTexture;
    std::unique_ptr<Texture> _msEmissionBuffer;
    std::unique_ptr<Framebuffer> _msFrameBuffer;

public:
    void initialize() override;

    void render(Node& root) override;

    void resize(int width, int height) override;

    void deinitialize() override;

    std::unique_ptr<Texture>& normalTexture();
    std::unique_ptr<Texture>& depthTexture();
    std::unique_ptr<Texture>& positionTexture();
    std::unique_ptr<Texture>& colorTexture();
    std::unique_ptr<Texture>& metallicRoughnessTexture();
    std::unique_ptr<Texture>& emissionBuffer();
};

}

#endif // VX_EMBER_GEOMETRYPASS_H
