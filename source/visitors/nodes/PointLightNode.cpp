//
// Created by voxed on 5/29/22.
//

#include "PointLightNode.h"

#include <utility>

#include "visitors/NodeVisitor.h"

using namespace vx::ember;

void PointLightNode::accept(NodeVisitor& visitor) { visitor.visit(*this); }

PointLightNode::PointLightNode(std::string name)
    : SpatialNode(std::move(name)) { }

glm::vec3 PointLightNode::color() { return _color; }

void PointLightNode::setColor(glm::vec3 color) { _color = color; }

float PointLightNode::intensity() { return _intensity; }

void PointLightNode::setIntensity(float intensity) { _intensity = intensity; }
