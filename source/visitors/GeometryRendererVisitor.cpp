//
// Created by voxed on 5/23/22.
//

#include "GeometryRendererVisitor.h"

#include <utility>

#include "nodes/CameraNode.h"
#include "nodes/GeometryNode.h"

using namespace vx::ember;

GeometryRendererVisitor::GeometryRendererVisitor(
    Program* program, std::shared_ptr<BufferObject> matrixUBO)
    : _program(program)
    , _matrixUBO(std::move(matrixUBO)) { }

void GeometryRendererVisitor::visit(vx::ember::GeometryNode& geometryNode) {
    _program->setUniform(0, geometryNode.worldMatrix() * geometryNode.matrix());

    for (const auto& prim : geometryNode.mesh()->primitives()) {
        prim->render(*_program);
    }

    traverse(geometryNode);
}
