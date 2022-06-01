//
// Created by voxed on 6/1/22.
//

#include "GizmoRendererVisitor.h"

#include "nodes/PointLightNode.h"
#include <utility>

using namespace vx::ember;

void GizmoRendererVisitor::visit(PointLightNode& pointLightNode) {
    glm::vec3 position = (pointLightNode.worldMatrix() * pointLightNode.matrix()
        * glm::vec4(0.0, 0.0, 0.0, 1.0));

    _rsmPass->rsm(&pointLightNode).normalTexture()->bind(0);

    _lightGizmoShader->setUniform(0, glm::translate(glm::mat4(1.0), position));

    _sphereMesh->primitives()[0]->render(*_lightGizmoShader);

    traverse(pointLightNode);
}

GizmoRendererVisitor::GizmoRendererVisitor(Program& lightGizmoShader,
    std::shared_ptr<Mesh> sphereMesh, std::shared_ptr<RSMPass> rsmPass)
    : _lightGizmoShader(&lightGizmoShader)
    , _sphereMesh(std::move(sphereMesh))
    , _rsmPass(std::move(rsmPass)) { }
