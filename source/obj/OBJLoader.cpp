//
// Created by voxed on 6/1/22.
//

#include "OBJLoader.h"
#include "Mesh.h"
#include "Primitive.h"
#include <glm/vec3.hpp>

using namespace vx::ember;

#include <OBJ_Loader.h>

OBJLoader::OBJLoader(const std::filesystem::path& path) {
    objl::Loader _loader;

    _loader.LoadFile(path);
    _loader.LoadedMeshes[0].Vertices;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices = _loader.LoadedMeshes[0].Indices;

    for (const auto& v : _loader.LoadedMeshes[0].Vertices) {
        vertices.emplace_back(v.Position.X, v.Position.Y, v.Position.Z);
        normals.emplace_back(v.Normal.X, v.Normal.Y, v.Normal.Z);
    }

    std::shared_ptr<Primitive> prim
        = std::make_shared<Primitive>(vertices, normals, indices);

    _mesh = std::make_shared<Mesh>(
        std::vector<std::shared_ptr<Primitive>> { prim });
}

std::shared_ptr<Mesh> OBJLoader::mesh() { return _mesh; }
