//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_WORLDMATRIXUPDATEVISITOR_H
#define VX_EMBER_WORLDMATRIXUPDATEVISITOR_H

#include "NodeTraversalVisitor.h"
#include "NodeVisitor.h"
#include <glm/ext.hpp>
#include <glm/ext/matrix_float4x4.hpp>

namespace vx::ember {

class WorldMatrixUpdateVisitor : public NodeTraversalVisitor {
    glm::mat4 _worldMatrix;
    glm::quat _worldRotation;
    explicit WorldMatrixUpdateVisitor(
        glm::mat4 worldMatrix, glm::quat worldRotation);

public:
    WorldMatrixUpdateVisitor();

    void visit(CameraNode& cameraNode) override;

    void visit(SpatialNode& spatialNode) override;

    void visit(GeometryNode& geometryNode) override;

    void visit(PointLightNode& pointLightNode) override;
};

}

#endif // VX_EMBER_WORLDMATRIXUPDATEVISITOR_H
