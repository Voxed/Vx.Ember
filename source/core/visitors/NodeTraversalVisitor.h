//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_NODETRAVERSALVISITOR_H
#define VX_EMBER_NODETRAVERSALVISITOR_H

#include "core/NodeVisitor.h"

namespace vx::ember {

class NodeTraversalVisitor : public NodeVisitor {
public:
    void visit(CameraNode& cameraNode) override;

    void visit(SpatialNode& spatialNode) override;
    void visit(GeometryNode& geometryNode) override;

    void visit(Node& node) override;

    void visit(PointLightNode& pointLightNode) override;
};

}

#endif // VX_EMBER_NODETRAVERSALVISITOR_H
