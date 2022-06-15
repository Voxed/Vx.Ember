//
// Created by voxed on 6/1/22.
//

#include "GizmoRendererVisitor.h"

#include "core/nodes/PointLightNode.h"

#include <utility>

using namespace vx::ember;

void GizmoRendererVisitor::visit(PointLightNode& pointLightNode) {
    glm::vec3 position = (pointLightNode.worldMatrix() * pointLightNode.matrix() * glm::vec4(0.0, 0.0, 0.0, 1.0));

    RSMFramebuffer& cache = _rsmCache->get(&pointLightNode);

    /*switch (_bufferType) {
    case NORMAL_BUFFER:
        cache.normalTexture().bind(0);
        break;
    case POSITION_BUFFER:
        cache.positionTexture().bind(0);
        break;
    case COLOR_BUFFER:
        cache.colorTexture().bind(0);
        break;
    case EMISSION_BUFFER:
        cache.emissionTexture().bind(0);
        break;
    case METALLIC_ROUGHNESS_BUFFER:
        cache.metallicRoughnessTexture().bind(0);
        break;
    case DEPTH_BUFFER:
        cache.depthTexture().bind(0);
        break;
    }*/
    cache.depthTexture().bind(0);

    _lightGizmoShader->setUniform(0, glm::translate(glm::mat4(1.0), position));

    pointLightNode.ubo().bind(GL_UNIFORM_BUFFER, 1);

    _sphereMesh->primitives()[0]->render(*_lightGizmoShader);

    traverse(pointLightNode);
}

GizmoRendererVisitor::GizmoRendererVisitor(
    Program& lightGizmoShader, std::shared_ptr<Mesh> sphereMesh, RSMCache& rsmCache, BufferType type)
    : _lightGizmoShader(&lightGizmoShader)
    , _sphereMesh(std::move(sphereMesh))
    , _rsmCache(&rsmCache)
    , _bufferType(type) { }
