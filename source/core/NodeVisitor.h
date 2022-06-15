//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_NODEVISITOR_H
#define VX_EMBER_NODEVISITOR_H

namespace vx::ember {

class CameraNode;

class SpatialNode;

class Node;

class GeometryNode;

class PointLightNode;

class NodeVisitor {
protected:
public:
    void traverse(Node& node);

    virtual void visit(CameraNode& cameraNode) = 0;

    virtual void visit(SpatialNode& spatialNode) = 0;

    virtual void visit(Node& node) = 0;

    virtual void visit(GeometryNode& geometryNode) = 0;

    virtual void visit(PointLightNode& pointLightNode) = 0;
};
}

#endif // VX_EMBER_NODEVISITOR_H
