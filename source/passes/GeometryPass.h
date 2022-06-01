//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_GEOMETRYPASS_H
#define VX_EMBER_GEOMETRYPASS_H

#include "GeometryFramebuffer.h"
#include "Pass.h"
#include "gl/BufferObject.h"
#include "gl/Program.h"
#include "gl/Shader.h"
#include <GL/glew.h>
#include <memory>

namespace vx::ember {

class Node;

/**
 * This pass creates relevant G-buffers for shading.
 */
class GeometryPass : public Pass {
    std::unique_ptr<Program> _program;
    GeometryFramebuffer _fb;
    int _width, _height;
    std::shared_ptr<BufferObject> matrixUBO;

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

#endif // VX_EMBER_GEOMETRYPASS_H
