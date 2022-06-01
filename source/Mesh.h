//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_MESH_H
#define VX_EMBER_MESH_H

#include "Primitive.h"
#include <memory>
#include <vector>

namespace vx::ember {

class Program;

class Mesh {
    std::vector<std::shared_ptr<Primitive>> _primitives;

public:
    explicit Mesh(std::vector<std::shared_ptr<Primitive>> primitives);

    std::span<std::shared_ptr<Primitive>> primitives();

    explicit operator std::string() const {
        return "Mesh <" + std::to_string(_primitives.size()) + ">";
    }
};

}

#endif // VX_EMBER_MESH_H
