//
// Created by voxed on 5/20/22.
//

#include "Ember.h"

using namespace vx::ember;

Ember::Ember() {
    _root = std::make_unique<Node>("root");
}

void Ember::initialize() {
    std::for_each(_passes.begin(), _passes.end(), [](std::shared_ptr<Pass> &p) { p->initialize(); });
}

void Ember::render() {
    std::for_each(_passes.begin(), _passes.end(), [this](std::shared_ptr<Pass> &p) { p->render(*_root); });
}

void Ember::addPass(std::shared_ptr<Pass> pass) {
    _passes.push_back(pass);
}

Node &Ember::root() {
    return *_root;
}

void Ember::deinitialize() {
    std::for_each(_passes.begin(), _passes.end(), [](std::shared_ptr<Pass> &p) { p->deinitialize(); });
}

void Ember::resize(int width, int height) {
    std::for_each(_passes.begin(), _passes.end(), [width, height](std::shared_ptr<Pass> &p) { p->resize(width, height); });
}

