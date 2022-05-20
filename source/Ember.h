//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_EMBER_H
#define VX_EMBER_EMBER_H

#include <vector>
#include "passes/Pass.h"
#include <memory>

namespace vx::ember {

    class Ember {
        std::vector<std::unique_ptr<Pass>> _passes;

        void addPassInternal(Pass *pass);

    public:
        template<typename T>
        T &addPass(T pass) {
            T *ptr = new T(pass);
            addPassInternal(ptr);
            return *ptr;
        }

        void initialize();

        void render();
    };

}

#endif //VX_EMBER_EMBER_H
