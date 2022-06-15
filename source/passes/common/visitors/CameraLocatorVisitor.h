//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_CAMERALOCATORVISITOR_H
#define VX_EMBER_CAMERALOCATORVISITOR_H

#include "core/nodes/CameraNode.h"
#include "core/visitors/NodeTraversalVisitor.h"
#include <optional>

namespace vx::ember {

class CameraLocatorVisitor : public NodeTraversalVisitor {
    CameraNode* _camera = nullptr;

public:
    void visit(CameraNode& cameraNode) override;

    CameraNode* camera();
};

}

#endif // VX_EMBER_CAMERALOCATORVISITOR_H
