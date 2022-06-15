//
// Created by voxed on 5/23/22.
//

#include "NodeVisitor.h"
#include "core/nodes/Node.h"

namespace vx::ember {

void NodeVisitor::traverse(vx::ember::Node& node) {
    for (auto const& c : node.children()) {
        c->accept(*this);
    }
}

}
