//
// Created by voxed on 5/20/22.
//

#include "CameraNode.h"

#include "visitors/NodeVisitor.h"

using namespace vx::ember;

void CameraNode::accept(vx::ember::NodeVisitor &visitor) {
    visitor.visit(*this);
}

