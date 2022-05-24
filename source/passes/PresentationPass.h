//
// Created by voxed on 5/24/22.
//

#ifndef VX_EMBER_PRESENTATIONPASS_H
#define VX_EMBER_PRESENTATIONPASS_H

#include <GL/glew.h>
#include "Pass.h"
#include "Program.h"
#include "GeometryPass.h"

namespace vx::ember {

    class PresentationPass : public Pass {
        GLuint quadVao;
        GLuint quadVbo;

        std::unique_ptr<Program> _program;

        std::shared_ptr<GeometryPass> _geoPass;

        GLuint _texture;

    public:
        void setTexture(GLuint texture);

        void initialize() override;

        void render(Node &root) override;

        void resize(int width, int height) override;

        void deinitialize() override;
    };

}


#endif //VX_EMBER_PRESENTATIONPASS_H
