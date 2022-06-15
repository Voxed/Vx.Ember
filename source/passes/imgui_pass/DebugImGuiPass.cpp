//
// Created by voxed on 5/29/22.
//

#include "DebugImGuiPass.h"

#include "core/nodes/Node.h"
#include "imgui.h"
#include "visitors/ImGuiTreeViewVisitor.h"

using namespace vx::ember;

void DebugImGuiPass::initialize() { }

void DebugImGuiPass::render(::Node& root) {
    ImGui::Begin("Vx::Ember Debug");

    ImGuiTreeViewVisitor treeViewVisitor;

    root.accept(treeViewVisitor);

    ImGui::End();
}

void DebugImGuiPass::resize(int width, int height) { }

void DebugImGuiPass::deinitialize() { }
