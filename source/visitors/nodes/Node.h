//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_NODE_H
#define VX_EMBER_NODE_H

#include <vector>
#include <memory>
#include <span>

namespace vx::ember {

    class NodeVisitor;

    class Node {
        std::vector<std::shared_ptr<Node>> _children;

    public:
        void addChild(std::shared_ptr<Node> node);
        void removeChild(std::shared_ptr<Node> node);
        std::span<std::shared_ptr<Node>> children();

        virtual void accept(NodeVisitor &visitor);
    };

}

#endif //VX_EMBER_NODE_H
