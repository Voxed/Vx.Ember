//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_GEOMETRYPASS_H
#define VX_EMBER_GEOMETRYPASS_H

#include "Pass.h"
#include <GL/glew.h>

namespace vx::ember {

    /**
     * This pass creates relevant G-buffers for shading.
     */
    class GeometryPass : public Pass {
    public:
        GeometryPass();

        void initialize() override;

        void render() override;

    };

}


#endif //VX_EMBER_GEOMETRYPASS_H
