//
// Created by voxed on 5/23/22.
//

#include "GeometryRendererVisitor.h"

#include "core/nodes/CameraNode.h"
#include "core/nodes/GeometryNode.h"
#include "passes/common/Frustum.h"

using namespace vx::ember;

GeometryRendererVisitor::GeometryRendererVisitor(glm::mat4 vp, Program* program)
    : _program(program)
    , _vp(vp) { }

void GeometryRendererVisitor::visit(vx::ember::GeometryNode& geometryNode) {
    glm::mat4 model = geometryNode.worldMatrix() * geometryNode.matrix();
    Frustum f(_vp * model);

    _program->setUniform(0, model);

    for (const auto& prim : geometryNode.mesh()->primitives()) {
        if (!f.intersectBox(prim->bounds())) // Frustum culling
            continue;

        if (geometryNode.material(prim->materialIndex()))
            geometryNode.material(prim->materialIndex())->bind(1, 2, 3, 0, 1);
        else
            defaultMaterial.bind(1, 2, 3, 0, 1);
        prim->render(*_program);
    }

    traverse(geometryNode);
}
