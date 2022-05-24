//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_GEOMETRYRENDERERVISITOR_H
#define VX_EMBER_GEOMETRYRENDERERVISITOR_H

#include <glm/ext/matrix_float4x4.hpp>
#include "NodeTraversalVisitor.h"
#include "Program.h"

namespace vx::ember {

    class GeometryRendererVisitor : public NodeTraversalVisitor {
        Program* _program;
    public:
        explicit GeometryRendererVisitor(Program* program);

        void visit(GeometryNode &geometryNode) override;
    };

}


#endif //VX_EMBER_GEOMETRYRENDERERVISITOR_H
