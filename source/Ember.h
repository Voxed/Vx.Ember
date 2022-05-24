//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_EMBER_H
#define VX_EMBER_EMBER_H

#include <vector>
#include "passes/Pass.h"
#include "visitors/nodes/Node.h"
#include <memory>

namespace vx::ember {

    class Ember {
        std::vector<std::shared_ptr<Pass>> _passes;
        std::unique_ptr<Node> _root;

    public:
        Ember();

        void addPass(std::shared_ptr<Pass> pass);

        void initialize();

        void render();

        void resize(int width, int height);

        void deinitialize();

        Node& root();
    };

}

#endif //VX_EMBER_EMBER_H
