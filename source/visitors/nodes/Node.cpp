//
// Created by voxed on 5/20/22.
//
#include "Node.h"

#include <utility>
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

Node::Node(std::string name) : _name(std::move(name)) {}

std::string Node::name() {
    return _name;
}

std::vector<std::shared_ptr<Node>> Node::findChild(std::string name) {
    std::vector<std::shared_ptr<Node>> matches;
    for(auto& child : _children) {
        if(child->_name == name)
            matches.push_back(child);
    }
    return matches;
}
