//
// Created by voxed on 5/20/22.
//
#include "Node.h"
#include "visitors/NodeVisitor.h"

using namespace vx::ember;

void Node::addChild(std::shared_ptr<Node> node) {
    _children.push_back(node);
}

void Node::accept(NodeVisitor &visitor) {
    visitor.visit(*this);
}

std::span<std::shared_ptr<Node>> Node::children() {
    return _children;
}

void Node::removeChild(std::shared_ptr<Node> node) {
    _children.erase(std::remove(_children.begin(), _children.end(), node), _children.end());
}
