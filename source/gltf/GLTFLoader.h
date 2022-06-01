//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_GLTFLOADER_H
#define VX_EMBER_GLTFLOADER_H

#include "Mesh.h"
#include "Primitive.h"
#include "tiny_gltf.h"
#include "visitors/nodes/CameraNode.h"
#include "visitors/nodes/SpatialNode.h"

#include <filesystem>

#include <map>

namespace vx::ember {

class GLTFLoader {
    std::filesystem::path _path;

    std::shared_ptr<Node> _root;
    tinygltf::Model _model;

    std::map<int, std::shared_ptr<Node>> nodeCache;
    std::map<int, std::shared_ptr<CameraNode>> cameraCache;
    std::map<int, std::shared_ptr<Mesh>> meshCache;

    std::shared_ptr<Node> getNode(int id);
    std::shared_ptr<CameraNode> getCamera(int id);
    std::shared_ptr<Mesh> getMesh(int id);

public:
    explicit GLTFLoader(const std::filesystem::path& path);
    std::shared_ptr<Node> scene();
};

}

#endif // VX_EMBER_GLTFLOADER_H
