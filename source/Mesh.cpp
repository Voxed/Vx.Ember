//
// Created by voxed on 5/20/22.
//

#include "Mesh.h"

#include <utility>

using namespace vx::ember;

Mesh::Mesh(std::vector<std::shared_ptr<Primitive>> primitives) : _primitives(std::move(primitives)) {

}

std::span<std::shared_ptr<Primitive>> Mesh::primitives() {
    return _primitives;
}
