//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_RSMPASS_H
#define VX_EMBER_RSMPASS_H

#include "Pass.h"

#include "GeometryFramebuffer.h"
#include "RSMFramebuffer.h"
#include "gl/BufferObject.h"
#include "gl/Program.h"
#include <map>
#include <memory>

namespace vx::ember {

class PointLightNode;

class RSMPass : public Pass {
    std::unique_ptr<Program> _program;
    std::map<PointLightNode*, RSMFramebuffer> _lightCache;
    std::shared_ptr<BufferObject> matrixUBO;

public:
    void initialize() override;

    void render(Node& root) override;

    void resize(int width, int height) override;

    void deinitialize() override;

    int lightCount();
    std::string lightName(int id);
    RSMFramebuffer& rsm(PointLightNode* lightNode);
    RSMFramebuffer& rsm(int id);
};

}

#endif // VX_EMBER_RSMPASS_H
