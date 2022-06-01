//
// Created by voxed on 5/29/22.
//

#include "ImGuiTreeViewVisitor.h"

#include <utility>

#include "nodes/CameraNode.h"
#include "nodes/GeometryNode.h"
#include "nodes/Node.h"
#include "nodes/PointLightNode.h"
#include "nodes/SpatialNode.h"

#include "imgui.h"

#include <sstream>

using namespace vx::ember;

void ImGuiTreeViewVisitor::parametersSpatialNode(SpatialNode& node) {
    glm::vec3 scale = node.scale();
    glm::vec3 position = node.position();
    glm::quat rotation = node.rotation();

    ImGui::DragFloat3("scale", (float*)&scale, 0.01f);
    ImGui::DragFloat3("position", (float*)&position, 0.1f);
    ImGui::DragFloat4("rotation", (float*)&rotation, 0.01f);

    node.setScale(scale);
    node.setPosition(position);
    node.setRotation(rotation);
}

void ImGuiTreeViewVisitor::parametersCameraNode(CameraNode& node) {
    Perspective perspective = node.perspective();
    bool active = node.active();

    ImGui::DragFloat("fov", &perspective.fov, 0.1f);
    ImGui::DragFloat("near", &perspective.near, 0.1f);
    ImGui::DragFloat("far", &perspective.far, 0.1f);
    ImGui::Checkbox("active", &active);

    node.setActive(active);
    node.setPerspective(perspective);
    node.setActive(active);

    parametersSpatialNode(node);
}

void ImGuiTreeViewVisitor::parametersGeometryNode(GeometryNode& node) {
    parametersSpatialNode(node);
}

bool ImGuiTreeViewVisitor::imGuiTreeTraverseBegin(
    Node& node, const std::string& type) {
    // Use node address as id. Should work.
    std::stringstream ss;
    ss << &node;
    std::string id = node.name() + " | " + type + "##" + ss.str();
    return ImGui::TreeNode(id.c_str());
}

void ImGuiTreeViewVisitor::imGuiTreeTraverseEnd(Node& node) {
    if (ImGui::TreeNode("children")) {
        traverse(node);
        ImGui::TreePop();
    }
    ImGui::TreePop();
}

void ImGuiTreeViewVisitor::visit(CameraNode& cameraNode) {
    if (!imGuiTreeTraverseBegin(cameraNode, "CameraNode"))
        return;

    parametersCameraNode(cameraNode);

    imGuiTreeTraverseEnd(cameraNode);
}

void ImGuiTreeViewVisitor::visit(SpatialNode& spatialNode) {
    if (!imGuiTreeTraverseBegin(spatialNode, "SpatialNode"))
        return;

    parametersSpatialNode(spatialNode);

    imGuiTreeTraverseEnd(spatialNode);
}

void ImGuiTreeViewVisitor::visit(Node& node) {
    if (!imGuiTreeTraverseBegin(node, "Node"))
        return;
    imGuiTreeTraverseEnd(node);
}

void ImGuiTreeViewVisitor::visit(GeometryNode& geometryNode) {
    if (!imGuiTreeTraverseBegin(geometryNode, "GeometryNode"))
        return;

    parametersGeometryNode(geometryNode);

    imGuiTreeTraverseEnd(geometryNode);
}

void ImGuiTreeViewVisitor::visit(PointLightNode& pointLightNode) {
    if (!imGuiTreeTraverseBegin(pointLightNode, "PointLightNode"))
        return;

    parametersPointLightNode(pointLightNode);

    imGuiTreeTraverseEnd(pointLightNode);
}

void ImGuiTreeViewVisitor::parametersPointLightNode(PointLightNode& node) {
    glm::vec3 color = node.color();
    float intensity = node.intensity();

    ImGui::ColorEdit3("color", (float*)&color);
    ImGui::DragFloat("intensity", &intensity, 0.01f);

    node.setColor(color);
    node.setIntensity(intensity);

    parametersSpatialNode(node);
}
