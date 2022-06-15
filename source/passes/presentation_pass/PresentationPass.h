//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_PRESENTATIONPASS_H
#define VX_EMBER_PRESENTATIONPASS_H

#include "core/Pass.h"
#include "gl/Program.h"
#include "gl/Texture.h"

#include <GL/glew.h>

namespace vx::ember {

class PresentationPass : public Pass {
    GLuint quadVao;
    GLuint quadVbo;

    std::unique_ptr<Program> _program;

    Texture* _gizmosTexture;

    Texture* _texture;

    bool _isCubemap = false;
    bool _useGizmos = false;
    int _face = 0;
    int _width;
    int _height;

    bool _isArray = false;
    int _element = 0;

    bool _mixArray;
    unsigned int _mixArrayCount;

public:
    void setTexture(Texture& texture);

    void initialize() override;

    void render(Node& root) override;

    void resize(int width, int height) override;

    void deinitialize() override;

    void setCubemap(bool cubemap);
    void setFace(int face);

    void setGizmosTexture(Texture& texture);
    void setGizmos(bool gizmos);

    void setArray(bool array);
    void setElement(unsigned int element);

    void setMixArray(bool mixArray);
    void setMixArrayCount(unsigned int mixArrayCount);
};

}

#endif // VX_EMBER_PRESENTATIONPASS_H
