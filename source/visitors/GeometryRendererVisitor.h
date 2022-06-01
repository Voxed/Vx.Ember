//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_GEOMETRYRENDERERVISITOR_H
#define VX_EMBER_GEOMETRYRENDERERVISITOR_H

#include "NodeTraversalVisitor.h"
#include "gl/BufferObject.h"
#include "gl/Program.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

namespace vx::ember {

class GeometryRendererVisitor : public NodeTraversalVisitor {
    Program* _program;
    std::shared_ptr<BufferObject> _matrixUBO;

public:
    explicit GeometryRendererVisitor(
        Program* program, std::shared_ptr<BufferObject> matrixUBO);

    void visit(GeometryNode& geometryNode) override;
};

}

#endif // VX_EMBER_GEOMETRYRENDERERVISITOR_H
