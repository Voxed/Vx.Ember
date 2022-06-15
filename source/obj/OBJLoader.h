//
// Created by voxed on 6/1/22.
//

#ifndef VX_EMBER_OBJLOADER_H
#define VX_EMBER_OBJLOADER_H

#include "core/Mesh.h"

#include <filesystem>

namespace vx::ember {

class OBJLoader {
    std::filesystem::path _path;
    std::shared_ptr<Mesh> _mesh;

public:
    explicit OBJLoader(const std::filesystem::path& path);
    std::shared_ptr<Mesh> mesh();
};

}

#endif // VX_EMBER_OBJLOADER_H
