//
// Created by voxed on 5/20/22.
//

#include "CameraNode.h"
#include <glm/gtx/quaternion.hpp>

#include "visitors/NodeVisitor.h"

using namespace vx::ember;

void CameraNode::accept(vx::ember::NodeVisitor& visitor) {
    visitor.visit(*this);
}

glm::mat4 CameraNode::projection(float aspect) const {
    return glm::perspective(
        _perspective.fov, aspect, _perspective.near, _perspective.far);
}

CameraNode::CameraNode(Perspective perspective, std::string name)
    : _perspective(perspective)
    , SpatialNode(name) { }

bool CameraNode::active() const { return _active; }

void CameraNode::setActive(bool active) { _active = active; }

Perspective CameraNode::perspective() const { return _perspective; }

void CameraNode::setPerspective(Perspective perspective) {
    _perspective = perspective;
}
glm::mat4 CameraNode::viewMatrix() {
    glm::vec3 position
        = (worldMatrix() * matrix() * glm::vec4(0.0, 0.0, 0.0, 1.0));

    return glm::inverse(
        glm::translate(glm::mat4(1.0), position) * glm::toMat4(_worldRotation));
}
