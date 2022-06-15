//
// Created by voxed on 5/29/22.
//

#include "PointLightNode.h"

#include <utility>

#include "core/NodeVisitor.h"
#include "gl/Program.h"

using namespace vx::ember;

void PointLightNode::accept(NodeVisitor& visitor) { visitor.visit(*this); }

PointLightNode::PointLightNode(std::string name)
    : SpatialNode(std::move(name)) {
    _ubo = BufferObject::create<LightBlock>(GL_MAP_WRITE_BIT);
    auto lightBlock = _ubo->mapRange<LightBlock>(GL_MAP_WRITE_BIT);
    lightBlock->color = _color;
    lightBlock->intensity = _intensity;
}

glm::vec3 PointLightNode::color() { return _color; }

void PointLightNode::setColor(glm::vec3 color) {
    if (_color != color) {
        _color = color;
        auto m = _ubo->mapRange<LightBlock>(GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        m->intensity = _intensity;
        m->color = _color;
    }
}

float PointLightNode::intensity() const { return _intensity; }

void PointLightNode::setIntensity(float intensity) {
    if (_intensity != intensity) {
        _intensity = intensity;
        auto m = _ubo->mapRange<LightBlock>(GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        m->intensity = _intensity;
        m->color = _color;
    }
}

BufferObject& PointLightNode::ubo() { return *_ubo; }
