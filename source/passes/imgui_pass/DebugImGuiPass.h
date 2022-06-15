//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_DEBUGIMGUIPASS_H
#define VX_EMBER_DEBUGIMGUIPASS_H

#include "core/Pass.h"

namespace vx::ember {

class DebugImGuiPass : public Pass {
    void initialize() override;

    void render(Node& root) override;

    void resize(int width, int height) override;

    void deinitialize() override;
};

}

#endif // VX_EMBER_DEBUGIMGUIPASS_H
