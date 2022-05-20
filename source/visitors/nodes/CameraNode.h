//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_CAMERANODE_H
#define VX_EMBER_CAMERANODE_H

#include "Node.h"

namespace vx::ember {

    class NodeVisitor;

    class CameraNode : public Node {
    public:
        void accept(NodeVisitor &visitor) override;
    };

}

#endif //VX_EMBER_CAMERANODE_H
