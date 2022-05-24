//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_WORLDMATRIXUPDATEVISITOR_H
#define VX_EMBER_WORLDMATRIXUPDATEVISITOR_H

#include <glm/ext/matrix_float4x4.hpp>
#include "NodeVisitor.h"
#include "NodeTraversalVisitor.h"

namespace vx::ember {

    class WorldMatrixUpdateVisitor : public NodeTraversalVisitor {
        glm::mat4 _worldMatrix;
        explicit WorldMatrixUpdateVisitor(glm::mat4 worldMatrix);
    public:
        WorldMatrixUpdateVisitor();

        void visit(CameraNode &cameraNode) override;

        void visit(SpatialNode &spatialNode) override;

        void visit(GeometryNode &geometryNode) override;
    };

}


#endif //VX_EMBER_WORLDMATRIXUPDATEVISITOR_H
