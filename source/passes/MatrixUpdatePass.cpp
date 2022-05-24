//
// Created by voxed on 5/24/22.
//

#include "MatrixUpdatePass.h"
#include "visitors/WorldMatrixUpdateVisitor.h"
#include "visitors/nodes/Node.h"

using namespace vx::ember;

void vx::ember::MatrixUpdatePass::initialize() {

}

void MatrixUpdatePass::render(Node &root) {
    WorldMatrixUpdateVisitor worldMatrixUpdateVisitor;
    root.accept(worldMatrixUpdateVisitor);
}

void MatrixUpdatePass::resize(int width, int height) {

}

void MatrixUpdatePass::deinitialize() {

}
