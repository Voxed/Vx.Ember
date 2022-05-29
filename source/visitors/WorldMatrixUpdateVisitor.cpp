//
// Created by voxed on 5/24/22.
//

#include "WorldMatrixUpdateVisitor.h"

#include "nodes/CameraNode.h"
#include "nodes/GeometryNode.h"

using namespace vx::ember;

WorldMatrixUpdateVisitor::WorldMatrixUpdateVisitor(glm::mat4 worldMatrix) : _worldMatrix(worldMatrix) {

}

void WorldMatrixUpdateVisitor::visit(CameraNode &cameraNode) {
    cameraNode._worldMatrix = _worldMatrix;
    WorldMatrixUpdateVisitor(_worldMatrix * cameraNode.matrix()).traverse(cameraNode);
}

void WorldMatrixUpdateVisitor::visit(SpatialNode &spatialNode) {
    spatialNode._worldMatrix = _worldMatrix;
    WorldMatrixUpdateVisitor(_worldMatrix * spatialNode.matrix()).traverse(spatialNode);
}

void WorldMatrixUpdateVisitor::visit(GeometryNode &geometryNode) {
    geometryNode._worldMatrix = _worldMatrix;
    WorldMatrixUpdateVisitor(_worldMatrix * geometryNode.matrix()).traverse(geometryNode);
}

WorldMatrixUpdateVisitor::WorldMatrixUpdateVisitor() : _worldMatrix(1.0) {

}
