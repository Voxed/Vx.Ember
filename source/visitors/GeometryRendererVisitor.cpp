//
// Created by voxed on 5/23/22.
//

#include "GeometryRendererVisitor.h"

#include "nodes/GeometryNode.h"
#include "nodes/CameraNode.h"

using namespace vx::ember;

GeometryRendererVisitor::GeometryRendererVisitor(Program *program) : _program(program) {

}

void GeometryRendererVisitor::visit(vx::ember::GeometryNode &geometryNode) {
    _program->setModelMatrix(geometryNode.worldMatrix() * geometryNode.matrix());

    for(const auto& prim : geometryNode.mesh()->primitives()) {
        prim->render(*_program);
    }

    traverse(geometryNode);
}