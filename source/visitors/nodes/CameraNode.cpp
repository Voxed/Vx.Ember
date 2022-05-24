//
// Created by voxed on 5/20/22.
//

#include "CameraNode.h"

#include "visitors/NodeVisitor.h"

using namespace vx::ember;

void CameraNode::accept(vx::ember::NodeVisitor &visitor) {
    visitor.visit(*this);
}

bool CameraNode::active() const {
    return _active;
}

void CameraNode::setActive(bool active) {
    _active = active;
}

glm::mat4 CameraNode::projection(float aspect) const {
    return glm::perspective(_fov, aspect, _near, _far);
}

CameraNode::CameraNode(float fov, float far, float near) : _fov(fov), _far(far), _near(near) {
}

