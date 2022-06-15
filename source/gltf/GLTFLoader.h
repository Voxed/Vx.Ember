//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_GLTFLOADER_H
#define VX_EMBER_GLTFLOADER_H

#include "core/Mesh.h"
#include "core/Primitive.h"
#include "core/nodes/CameraNode.h"
#include "core/nodes/SpatialNode.h"
#include "tiny_gltf.h"

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
    std::map<int, std::vector<std::shared_ptr<Material>>> meshBaseMaterialCache;
    std::map<int, std::shared_ptr<Material>> materialCache;
    std::map<int, std::shared_ptr<Texture>> textureCache;
    std::map<int, std::shared_ptr<Image>> imageCache;
    std::map<int, std::shared_ptr<std::vector<char>>> bufferCache;

    std::shared_ptr<Node> getNode(int id);
    std::shared_ptr<CameraNode> getCamera(int id);
    std::pair<std::shared_ptr<Mesh>, std::vector<std::shared_ptr<Material>>> getMesh(int id);
    std::shared_ptr<Material> getMaterial(int id);
    std::shared_ptr<Texture> getTexture(int index);
    std::shared_ptr<Image> getImage(int index);
    std::shared_ptr<std::vector<char>> getBuffer(int index);

public:
    explicit GLTFLoader(const std::filesystem::path& path);
    std::shared_ptr<Node> scene();
};

}

#endif // VX_EMBER_GLTFLOADER_H
