//
// Created by voxed on 6/1/22.
//

#ifndef VX_EMBER_GIZMOPASS_H
#define VX_EMBER_GIZMOPASS_H

#include "GeometryPass.h"
#include "Mesh.h"
#include "Pass.h"
#include "RSMPass.h"
#include "gl/BufferObject.h"
#include "gl/Framebuffer.h"
#include "gl/Program.h"
#include "gl/Texture.h"
#include <memory>
#include <optional>

namespace vx::ember {

class GizmoPass : public Pass {
    std::unique_ptr<Program> _program;
    int _width, _height;
    std::shared_ptr<BufferObject> matrixUBO;
    Framebuffer _fb;
    std::optional<Texture> _gizmoColorBuffer;
    std::optional<Texture> _gizmoDepthBuffer;
    std::shared_ptr<Mesh> _sphereMesh;

    std::shared_ptr<RSMPass> _rsmPass;
    std::shared_ptr<GeometryPass> _geoPass;

public:
    explicit GizmoPass(std::shared_ptr<RSMPass> rsmPass,
        std::shared_ptr<GeometryPass> geoPass);

    void initialize() override;
    void render(Node& root) override;
    void resize(int width, int height) override;
    void deinitialize() override;

    GLuint texture();
};

}

#endif // VX_EMBER_GIZMOPASS_H
