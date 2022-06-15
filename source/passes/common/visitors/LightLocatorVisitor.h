//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_LIGHTLOCATORVISITOR_H
#define VX_EMBER_LIGHTLOCATORVISITOR_H

#include "core/visitors/NodeTraversalVisitor.h"
#include <memory>
#include <vector>

namespace vx::ember {

class PointLightNode;

class LightLocatorVisitor : public NodeTraversalVisitor {
    std::vector<PointLightNode*> _lights;

public:
    void visit(PointLightNode& pointLightNode) override;

    std::vector<PointLightNode*> lights();
};

}

#endif // VX_EMBER_LIGHTLOCATORVISITOR_H
