//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_IMGUITREEVIEWVISITOR_H
#define VX_EMBER_IMGUITREEVIEWVISITOR_H

#include "core/NodeVisitor.h"

#include <string>

namespace vx::ember {

class ImGuiTreeViewVisitor : public NodeVisitor {
    static void parametersSpatialNode(SpatialNode& node);
    static void parametersCameraNode(CameraNode& node);
    static void parametersGeometryNode(GeometryNode& node);
    static void parametersPointLightNode(PointLightNode& node);

    bool imGuiTreeTraverseBegin(Node& node, const std::string& type);
    void imGuiTreeTraverseEnd(Node& node);

public:
    void visit(CameraNode& cameraNode) override;

    void visit(SpatialNode& spatialNode) override;

    void visit(Node& node) override;

    void visit(GeometryNode& geometryNode) override;

    void visit(PointLightNode& pointLightNode) override;
};

}

#endif // VX_EMBER_IMGUITREEVIEWVISITOR_H
