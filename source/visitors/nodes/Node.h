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
    class ImGuiTreeViewVisitor;

    class Node {
        std::vector<std::shared_ptr<Node>> _children;
        std::string _name;

    public:
        explicit Node(std::string name = "Node");

        void addChild(std::shared_ptr<Node> node);
        void removeChild(std::shared_ptr<Node> node);
        std::vector<std::shared_ptr<Node>> findChild(std::string name);
        std::span<std::shared_ptr<Node>> children();
        std::string name();

        virtual void accept(NodeVisitor &visitor);

        friend ImGuiTreeViewVisitor;
    };

}

#endif //VX_EMBER_NODE_H
