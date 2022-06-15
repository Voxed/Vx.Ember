//
// Created by voxed on 5/23/22.
//

#include "CameraLocatorVisitor.h"

namespace vx::ember {

void CameraLocatorVisitor::visit(vx::ember::CameraNode& cameraNode) {
    if (cameraNode.active())
        _camera = &cameraNode;
    traverse(cameraNode);
}

CameraNode* CameraLocatorVisitor::camera() { return _camera; }

}