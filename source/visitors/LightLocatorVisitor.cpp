//
// Created by voxed on 5/29/22.
//

#include "LightLocatorVisitor.h"

using namespace vx::ember;

void LightLocatorVisitor::visit(PointLightNode& pointLightNode) {
    _lights.push_back(&pointLightNode);
}

std::vector<PointLightNode*> LightLocatorVisitor::lights() { return _lights; }
