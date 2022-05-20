//
// Created by voxed on 5/20/22.
//

#include "Ember.h"

using namespace vx::ember;

void Ember::addPassInternal(Pass *pass) {
    _passes.push_back(std::unique_ptr<Pass>(pass));
}

void Ember::initialize() {
    std::for_each(_passes.begin(), _passes.end(), [](std::unique_ptr<Pass> &p) { p->initialize(); });
}

void Ember::render() {
    std::for_each(_passes.begin(), _passes.end(), [](std::unique_ptr<Pass> &p) { p->render(); });
}
