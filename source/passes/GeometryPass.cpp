//
// Created by voxed on 5/20/22.
//

#include "GeometryPass.h"

#include <stdio.h>
#include <cmath>

using namespace vx::ember;

GeometryPass::GeometryPass() {

}

void GeometryPass::initialize() {
    printf("INITIALIZING GEO PASS\n");
}

void GeometryPass::render() {
    static double i;

    glClearColor(cos(i += 0.01), 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}
