//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_PRESENTATIONPASS_H
#define VX_EMBER_PRESENTATIONPASS_H

#include "GeometryPass.h"
#include "Pass.h"
#include "gl/Program.h"
#include "gl/Texture.h"
#include <GL/glew.h>

namespace vx::ember {

class PresentationPass : public Pass {
    GLuint quadVao;
    GLuint quadVbo;

    std::unique_ptr<Program> _program;

    std::shared_ptr<GeometryPass> _geoPass;

    GLuint _gizmosTexture;

    GLuint _texture;

    bool _isCubemap = false;
    bool _useGizmos = false;
    int _face = 0;
    int _width;
    int _height;

public:
    void setTexture(GLuint texture);

    void initialize() override;

    void render(Node& root) override;

    void resize(int width, int height) override;

    void deinitialize() override;

    void setCubemap(bool cubemap);
    void setFace(int face);

    void setGizmosTexture(GLuint texture);
    void setGizmos(bool gizmos);
};

}

#endif // VX_EMBER_PRESENTATIONPASS_H
