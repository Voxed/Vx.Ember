//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_MATRIXUPDATEPASS_H
#define VX_EMBER_MATRIXUPDATEPASS_H

#include "Pass.h"

namespace vx::ember {

    class MatrixUpdatePass : public Pass {
    public:
        void initialize() override;

        void render(Node& root) override;

        void resize(int width, int height) override;

        void deinitialize() override;
    };

}


#endif //VX_EMBER_MATRIXUPDATEPASS_H
