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
    WorldMatrixUpdateVisitor(cameraNode.matrix() * _worldMatrix).traverse(cameraNode);
}

void WorldMatrixUpdateVisitor::visit(SpatialNode &spatialNode) {
    spatialNode._worldMatrix = _worldMatrix;
    WorldMatrixUpdateVisitor(spatialNode.matrix() * _worldMatrix).traverse(spatialNode);
}

void WorldMatrixUpdateVisitor::visit(GeometryNode &geometryNode) {
    geometryNode._worldMatrix = _worldMatrix;
    WorldMatrixUpdateVisitor(geometryNode.matrix() * _worldMatrix).traverse(geometryNode);
}

WorldMatrixUpdateVisitor::WorldMatrixUpdateVisitor() : _worldMatrix(1.0) {

}
