//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_GEOMETRYRENDERERVISITOR_H
#define VX_EMBER_GEOMETRYRENDERERVISITOR_H

#include "core/Material.h"
#include "core/visitors/NodeTraversalVisitor.h"
#include "gl/BufferObject.h"
#include "gl/Program.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

namespace vx::ember {

class GeometryRendererVisitor : public NodeTraversalVisitor {
    Program* _program;
    Material defaultMaterial
        = Material("", glm::vec4(1.0), glm::vec4(0.0), nullptr, 0.0, 0.5, 0.0, false, nullptr, nullptr, nullptr);
    glm::mat4 _vp;

public:
    explicit GeometryRendererVisitor(glm::mat4 vp, Program* program);

    void visit(GeometryNode& geometryNode) override;
};

}

#endif // VX_EMBER_GEOMETRYRENDERERVISITOR_H
