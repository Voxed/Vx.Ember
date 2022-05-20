//
// Created by voxed on 5/20/22.
//

#include "Ember.h"
#include "SampleBase.h"
#include "passes/GeometryPass.h"

using namespace vx::ember;

class Simple : public SampleBase {
    std::unique_ptr<Ember> ember;

    void createEmber() {
        ember = std::make_unique<Ember>();
        GeometryPass &geoPass = ember->addPass(GeometryPass());
        ember->initialize();
    }

    void initialize() override {
        createEmber();
    }

    void mainLoop() override {
        ember->render();
    }

public:
    Simple() : SampleBase(640, 480, "Simple Sample") {}

};

int main() {
    Simple base;
    base.start();
}

