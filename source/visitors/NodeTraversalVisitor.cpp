//
// Created by voxed on 5/23/22.
//

#include "NodeTraversalVisitor.h"

#include "nodes/CameraNode.h"
#include "nodes/SpatialNode.h"
#include "nodes/Node.h"
#include "nodes/GeometryNode.h"

namespace vx::ember {

    void NodeTraversalVisitor::visit(vx::ember::CameraNode &cameraNode) {
        traverse(cameraNode);
    }

    void NodeTraversalVisitor::visit(vx::ember::SpatialNode &spatialNode) {
        traverse(spatialNode);
    }

    void NodeTraversalVisitor::visit(vx::ember::Node &node) {
        traverse(node);
    }

    void NodeTraversalVisitor::visit(GeometryNode &geometryNode) {
        traverse(geometryNode);
    }

}