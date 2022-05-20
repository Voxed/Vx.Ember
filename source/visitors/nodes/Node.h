//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_NODE_H
#define VX_EMBER_NODE_H

namespace vx::ember {

    class NodeVisitor;

    class Node {
    public:
        virtual void accept(NodeVisitor &visitor) = 0;
    };

}

#endif //VX_EMBER_NODE_H
