//
// Created by voxed on 5/20/22.
//

#include "SpatialNode.h"
#include "core/NodeVisitor.h"
#include <glm/gtx/quaternion.hpp>
#include <utility>

using namespace vx::ember;

void SpatialNode::accept(vx::ember::NodeVisitor& visitor) { visitor.visit(*this); }

glm::vec3 SpatialNode::position() { return _position; }

void SpatialNode::setPosition(glm::vec3 position) { _position = position; }

glm::quat SpatialNode::rotation() { return _rotation; }

void SpatialNode::setRotation(glm::quat rotation) { _rotation = rotation; }

glm::mat4 SpatialNode::matrix() {
    return glm::translate(glm::mat4(1.0f), _position) * glm::toMat4(_rotation) * glm::scale(glm::mat4(1.0f), _scale);
}

void SpatialNode::rotate(glm::vec3 euler) { _rotation = glm::quat(euler) * _rotation; }

void SpatialNode::lookAt(glm::vec3 direction) {
    float directionLength = glm::length(direction);

    if (directionLength <= 0.0001)
        _rotation = glm::quat(1, 0, 0, 0); // Just return identity

    direction /= directionLength;

    if (glm::abs(glm::dot(direction, glm::vec3(0, 1, 0))) > .9999f) {
        _rotation = glm::quatLookAt(direction, glm::normalize(glm::vec3(0.001, 1, 0)));
    } else {
        _rotation = glm::quatLookAt(direction, glm::vec3(0, 1, 0));
    }
}

glm::mat4 SpatialNode::worldMatrix() { return _worldMatrix; }

SpatialNode::SpatialNode(std::string name)
    : Node(std::move(name)) { }

glm::vec3 SpatialNode::scale() { return _scale; }

void SpatialNode::setScale(glm::vec3 scale) { _scale = scale; }
