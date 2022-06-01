//
// Created by voxed on 5/24/22.
//

#include "WorldMatrixUpdateVisitor.h"

#include "nodes/CameraNode.h"
#include "nodes/GeometryNode.h"
#include "visitors/nodes/PointLightNode.h"

using namespace vx::ember;

WorldMatrixUpdateVisitor::WorldMatrixUpdateVisitor(
    glm::mat4 worldMatrix, glm::quat worldRotation)
    : _worldMatrix(worldMatrix)
    , _worldRotation(worldRotation) { }

void WorldMatrixUpdateVisitor::visit(CameraNode& cameraNode) {
    cameraNode._worldMatrix = _worldMatrix;
    cameraNode._worldRotation = _worldRotation;
    WorldMatrixUpdateVisitor(_worldMatrix * cameraNode.matrix(),
        _worldRotation * cameraNode.rotation())
        .traverse(cameraNode);
}

void WorldMatrixUpdateVisitor::visit(SpatialNode& spatialNode) {
    spatialNode._worldMatrix = _worldMatrix;
    spatialNode._worldRotation = _worldRotation;
    WorldMatrixUpdateVisitor(_worldMatrix * spatialNode.matrix(),
        _worldRotation * spatialNode.rotation())
        .traverse(spatialNode);
}

void WorldMatrixUpdateVisitor::visit(GeometryNode& geometryNode) {
    geometryNode._worldMatrix = _worldMatrix;
    geometryNode._worldRotation = _worldRotation;
    WorldMatrixUpdateVisitor(_worldMatrix * geometryNode.matrix(),
        _worldRotation * geometryNode.rotation())
        .traverse(geometryNode);
}

WorldMatrixUpdateVisitor::WorldMatrixUpdateVisitor()
    : _worldMatrix(1.0)
    , _worldRotation(1.0, 0.0, 0.0, 0.0) { }

void WorldMatrixUpdateVisitor::visit(PointLightNode& pointLightNode) {
    pointLightNode._worldMatrix = _worldMatrix;
    pointLightNode._worldRotation = _worldRotation;
    WorldMatrixUpdateVisitor(_worldMatrix * pointLightNode.matrix(),
        _worldRotation * pointLightNode.rotation())
        .traverse(pointLightNode);
}
