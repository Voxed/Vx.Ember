//
// Created by voxed on 6/1/22.
//

#ifndef VX_EMBER_GIZMORENDERERVISITOR_H
#define VX_EMBER_GIZMORENDERERVISITOR_H

#include "core/Mesh.h"
#include "core/visitors/NodeTraversalVisitor.h"
#include "gl/Program.h"
#include "passes/common/BufferType.h"
#include "passes/common/RSMCache.h"

#include <memory>

namespace vx::ember {

class GizmoRendererVisitor : public NodeTraversalVisitor {
    Program* _lightGizmoShader;
    std::shared_ptr<Mesh> _sphereMesh;
    RSMCache* _rsmCache;
    BufferType _bufferType;

public:
    GizmoRendererVisitor(
        Program& lightGizmoShader, std::shared_ptr<Mesh> sphereMesh, RSMCache& rsmCache, BufferType type);

    void visit(PointLightNode& pointLightNode) override;
};

}

#endif // VX_EMBER_GIZMORENDERERVISITOR_H
