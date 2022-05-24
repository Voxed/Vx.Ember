//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_GEOMETRYPASS_H
#define VX_EMBER_GEOMETRYPASS_H

#include "Pass.h"
#include "Shader.h"
#include "Program.h"
#include <GL/glew.h>
#include <memory>

namespace vx::ember {

    class Node;

    /**
     * This pass creates relevant G-buffers for shading.
     */
    class GeometryPass : public Pass {
        std::unique_ptr<Program> _program;
        int _width, _height;

        GLuint depthBuffer;
        GLuint normalBuffer;
        GLuint positionBuffer;

        GLuint framebuffer;

    public:
        GeometryPass();

        void initialize() override;

        void render(Node& root) override;

        void resize(int width, int height) override;

        void deinitialize() override;

        GLuint normalTexture();
        GLuint depthTexture();
        GLuint positionTexture();
    };

}


#endif //VX_EMBER_GEOMETRYPASS_H
