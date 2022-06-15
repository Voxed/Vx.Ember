//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_PASS_H
#define VX_EMBER_PASS_H

namespace vx::ember {

class Node;

class Pass {
public:
    virtual void initialize() = 0;

    virtual void render(Node& root) = 0;

    virtual void resize(int width, int height) = 0;

    virtual void deinitialize() = 0;
};

}

#endif // VX_EMBER_PASS_H
