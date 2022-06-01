//
// Created by voxed on 6/1/22.
//

#ifndef VX_EMBER_GIZMORENDERERVISITOR_H
#define VX_EMBER_GIZMORENDERERVISITOR_H

#include "Mesh.h"
#include "NodeTraversalVisitor.h"
#include "gl/Program.h"
#include "passes/RSMPass.h"
#include <memory>
namespace vx::ember {

class GizmoRendererVisitor : public NodeTraversalVisitor {
    Program* _lightGizmoShader;
    std::shared_ptr<Mesh> _sphereMesh;
    std::shared_ptr<RSMPass> _rsmPass;

public:
    GizmoRendererVisitor(Program& lightGizmoShader,
        std::shared_ptr<Mesh> sphereMesh, std::shared_ptr<RSMPass> rsmPass);

    void visit(PointLightNode& pointLightNode) override;
};

}

#endif // VX_EMBER_GIZMORENDERERVISITOR_H
