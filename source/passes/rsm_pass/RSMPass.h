//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_RSMPASS_H
#define VX_EMBER_RSMPASS_H

#include "core/Pass.h"
#include "gl/BufferObject.h"
#include "gl/Program.h"
#include "passes/common/RSMCache.h"
#include "passes/common/RSMFramebuffer.h"

#include <map>
#include <memory>

namespace vx::ember {

class PointLightNode;

class RSMPass : public Pass {
    std::unique_ptr<Program> _program;
    std::unique_ptr<BufferObject> matrixUBO;

    RSMCache _cache;

public:
    void initialize() override;

    void render(Node& root) override;

    void resize(int width, int height) override;

    void deinitialize() override;

    RSMCache& cache();
};

}

#endif // VX_EMBER_RSMPASS_H
