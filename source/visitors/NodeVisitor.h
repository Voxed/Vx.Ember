//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_NODEVISITOR_H
#define VX_EMBER_NODEVISITOR_H

namespace vx::ember {

    class CameraNode;

    class NodeVisitor {
    public:
        virtual void visit(CameraNode &cameraNode) = 0;
    };

}

#endif //VX_EMBER_NODEVISITOR_H
