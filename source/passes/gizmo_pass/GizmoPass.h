//
// Created by voxed on 6/1/22.
//

#ifndef VX_EMBER_GIZMOPASS_H
#define VX_EMBER_GIZMOPASS_H

#include "core/Mesh.h"
#include "core/Pass.h"
#include "gl/BufferObject.h"
#include "gl/Framebuffer.h"
#include "gl/Program.h"
#include "gl/Texture.h"
#include "passes/common/BufferType.h"
#include "passes/common/RSMCache.h"

#include <memory>
#include <optional>

namespace vx::ember {

class GizmoPass : public Pass {
    std::unique_ptr<Program> _program;
    int _width, _height;
    std::unique_ptr<BufferObject> matrixUBO;
    std::unique_ptr<Framebuffer> _fb;
    std::unique_ptr<Texture> _gizmoColorBuffer;
    std::unique_ptr<Texture> _gizmoDepthBuffer;
    std::shared_ptr<Mesh> _sphereMesh;

    // Inputs :)
    std::unique_ptr<Texture>* _occluderDepthBuffer;
    RSMCache* _rsmCache;
    BufferType _bufferType;

public:
    explicit GizmoPass(RSMCache& rsmPass, std::unique_ptr<Texture>& occluderDepthBuffer);

    void initialize() override;
    void render(Node& root) override;
    void resize(int width, int height) override;
    void deinitialize() override;

    std::unique_ptr<Texture>& texture();
    void setBufferType(BufferType type);
};

}

#endif // VX_EMBER_GIZMOPASS_H
