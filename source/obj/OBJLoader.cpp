//
// Created by voxed on 6/1/22.
//

#include "OBJLoader.h"

#include "core/Mesh.h"
#include "core/Primitive.h"

#include <OBJ_Loader.h>
#include <glm/vec3.hpp>

using namespace vx::ember;

OBJLoader::OBJLoader(const std::filesystem::path& path) {
    objl::Loader _loader;

    _loader.LoadFile(path);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<unsigned int> indices = _loader.LoadedMeshes[0].Indices;

    for (const auto& v : _loader.LoadedMeshes[0].Vertices) {
        vertices.emplace_back(v.Position.X, v.Position.Y, v.Position.Z);
        normals.emplace_back(v.Normal.X, v.Normal.Y, v.Normal.Z);
        texCoords.emplace_back(v.TextureCoordinate.X, v.TextureCoordinate.Y);
    }

    std::shared_ptr<Primitive> prim
        = std::make_shared<Primitive>(vertices, normals, texCoords, std::vector<glm::vec4>(), indices, -1);

    _mesh = std::make_shared<Mesh>(std::vector<std::shared_ptr<Primitive>> { prim });
}

std::shared_ptr<Mesh> OBJLoader::mesh() { return _mesh; }
