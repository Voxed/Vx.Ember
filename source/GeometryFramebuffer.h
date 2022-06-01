//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_GEOMETRYFRAMEBUFFER_H
#define VX_EMBER_GEOMETRYFRAMEBUFFER_H

#include <GL/glew.h>

namespace vx::ember {

class GeometryFramebuffer {
    int _width, _height;

    GLuint _depthBuffer;
    GLuint _normalBuffer;
    GLuint _positionBuffer;

    GLuint _framebuffer;

    bool _initialized = false;

public:
    void resize(int width, int height);
    void bind();

    [[nodiscard]] GLuint normalTexture() const;
    [[nodiscard]] GLuint depthTexture() const;
    [[nodiscard]] GLuint positionTexture() const;
};

}

#endif // VX_EMBER_GEOMETRYFRAMEBUFFER_H
