//
// Created by voxed on 5/29/22.
//

#include "ImGuiTreeViewVisitor.h"

#include <utility>

#include "nodes/CameraNode.h"
#include "nodes/SpatialNode.h"
#include "nodes/Node.h"
#include "nodes/GeometryNode.h"

#include "imgui.h"

#include <sstream>

using namespace vx::ember;

void ImGuiTreeViewVisitor::parametersSpatialNode(SpatialNode &node) {
    ImGui::DragFloat3("scale", (float*) &node._scale, 0.01f);
    ImGui::DragFloat3("position", (float*) &node._position, 0.1f);
    ImGui::DragFloat4("rotation", (float*) &node._rotation, 0.01f);
}

void ImGuiTreeViewVisitor::parametersCameraNode(CameraNode &node) {
    ImGui::DragFloat("fov", &node._fov, 0.1f);
    ImGui::DragFloat("far", &node._far, 0.1f);
    ImGui::DragFloat("near", &node._near, 0.1f);
    ImGui::Checkbox("active", &node._active);

    parametersSpatialNode(node);
}

void ImGuiTreeViewVisitor::parametersGeometryNode(GeometryNode &node) {
    parametersSpatialNode(node);
}

bool ImGuiTreeViewVisitor::imGuiTreeTraverseBegin(Node &node, const std::string& type) {
    // Use node address as id. Should work.
    std::stringstream ss;
    ss << &node;
    std::string id = node.name() + " | " + type +  "##" + ss.str();
    return ImGui::TreeNode(id.c_str());
}

void ImGuiTreeViewVisitor::imGuiTreeTraverseEnd(Node &node) {
    if(ImGui::TreeNode("children")) {
        traverse(node);
        ImGui::TreePop();
    }
    ImGui::TreePop();
}

void ImGuiTreeViewVisitor::visit(CameraNode &cameraNode) {
    if (!imGuiTreeTraverseBegin(cameraNode, "CameraNode"))
        return;

    parametersCameraNode(cameraNode);

    imGuiTreeTraverseEnd(cameraNode);
}

void ImGuiTreeViewVisitor::visit(SpatialNode &spatialNode) {
    if (!imGuiTreeTraverseBegin(spatialNode, "SpatialNode"))
        return;

    parametersSpatialNode(spatialNode);

    imGuiTreeTraverseEnd(spatialNode);
}

void ImGuiTreeViewVisitor::visit(Node &node) {
    if (!imGuiTreeTraverseBegin(node, "Node"))
        return;
    imGuiTreeTraverseEnd(node);
}

void ImGuiTreeViewVisitor::visit(GeometryNode &geometryNode) {
    if (!imGuiTreeTraverseBegin(geometryNode, "GeometryNode"))
        return;

    parametersGeometryNode(geometryNode);

    imGuiTreeTraverseEnd(geometryNode);
}