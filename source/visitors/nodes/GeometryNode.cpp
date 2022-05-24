//
// Created by voxed on 5/23/22.
//

#include "GeometryNode.h"
#include "visitors/NodeVisitor.h"

#include <utility>

using namespace vx::ember;

GeometryNode::GeometryNode(std::shared_ptr<Mesh> mesh) : _mesh(std::move(mesh)) {

}

std::shared_ptr<Mesh> GeometryNode::mesh() {
    return _mesh;
}

void GeometryNode::accept(NodeVisitor &visitor) {
    visitor.visit(*this);
}
