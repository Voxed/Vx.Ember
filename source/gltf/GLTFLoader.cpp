//
// Created by voxed on 5/29/22.
//

#include "GLTFLoader.h"

using namespace vx::ember;

#include "exceptions.h"
#include "visitors/nodes/GeometryNode.h"
#include <ranges>

std::shared_ptr<Node> GLTFLoader::getNode(int id) {
    if (!nodeCache.contains(id)) {
        tinygltf::Node& gltfNode = _model.nodes[id];
        auto node = std::make_shared<SpatialNode>(gltfNode.name);
        if (!gltfNode.matrix.empty())
            throw InvalidModelException(
                _path, "Loader does not currently support raw matrix loading.");
        if (!gltfNode.translation.empty())
            node->setPosition(glm::vec3(gltfNode.translation[0],
                gltfNode.translation[1], gltfNode.translation[2]));
        if (!gltfNode.rotation.empty())
            node->setRotation(
                glm::quat(gltfNode.rotation[3], gltfNode.rotation[0],
                    gltfNode.rotation[1], gltfNode.rotation[2]));
        if (gltfNode.camera != -1) {
            node->addChild(getCamera(gltfNode.camera));
        }
        if (gltfNode.mesh != -1) {
            node->addChild(std::make_shared<GeometryNode>(
                getMesh(gltfNode.mesh), _model.meshes[gltfNode.mesh].name));
        }
        for (int n : gltfNode.children) {
            node->addChild(getNode(n));
        }
        nodeCache[id] = node;
    }

    return nodeCache[id];
}

std::shared_ptr<CameraNode> GLTFLoader::getCamera(int id) {
    if (!cameraCache.contains(id)) {
        tinygltf::Camera& gltfCam = _model.cameras[id];
        if (gltfCam.type != "perspective")
            throw InvalidModelException(
                _path, "Only perspective cameras are supported at this time.");
        tinygltf::PerspectiveCamera& perspective = gltfCam.perspective;

        auto camera = std::make_shared<CameraNode>(
            Perspective { (float)perspective.yfov, (float)perspective.znear,
                (float)perspective.zfar },
            gltfCam.name);
        cameraCache[id] = camera;
    }

    return cameraCache[id];
}

std::shared_ptr<Mesh> GLTFLoader::getMesh(int id) {
    // Temporary super blender-dependent code.
    if (!meshCache.contains(id)) {
        tinygltf::Mesh& gltfMesh = _model.meshes[id];

        std::vector<std::shared_ptr<Primitive>> fPrimitives;
        for (auto& primitive : gltfMesh.primitives) {
            auto& indices = _model.accessors[primitive.indices];
            std::vector<unsigned int> fIndices;
            {
                auto& view = _model.bufferViews[indices.bufferView];
                auto& buffer = _model.buffers[view.buffer];

                fIndices = std::vector<unsigned int>(
                    (unsigned short*)&(
                        *(buffer.data.begin() + view.byteOffset)),
                    (unsigned short*)&(*(buffer.data.begin() + view.byteOffset
                        + view.byteLength)));
            }
            auto& vertices = _model.accessors[primitive.attributes["POSITION"]];
            std::vector<glm::vec3> fVertices;
            {
                auto& view = _model.bufferViews[vertices.bufferView];
                auto& buffer = _model.buffers[view.buffer];

                fVertices = std::vector<glm::vec3>(
                    (glm::vec3*)&(*(buffer.data.begin() + view.byteOffset)),
                    (glm::vec3*)&(*(buffer.data.begin() + view.byteOffset
                        + view.byteLength)));
            }
            auto& normals = _model.accessors[primitive.attributes["NORMAL"]];
            std::vector<glm::vec3> fNormals;
            {
                auto& view = _model.bufferViews[normals.bufferView];
                auto& buffer = _model.buffers[view.buffer];

                fNormals = std::vector<glm::vec3>(
                    (glm::vec3*)&(*(buffer.data.begin() + view.byteOffset)),
                    (glm::vec3*)&(*(buffer.data.begin() + view.byteOffset
                        + view.byteLength)));
            }
            auto primtive
                = std::make_shared<Primitive>(fVertices, fNormals, fIndices);
            fPrimitives.push_back(primtive);
        }

        meshCache[id] = std::make_shared<Mesh>(fPrimitives);
    }

    return meshCache[id];
}

GLTFLoader::GLTFLoader(const std::filesystem::path& path) {

    if (!exists(path))
        throw FileNotFoundException(path);

    _path = path;

    std::string error;
    std::string warning;

    tinygltf::TinyGLTF tinyGLTF;
    tinyGLTF.LoadASCIIFromFile(&_model, &error, &warning, path);

    if (_model.defaultScene == -1)
        throw InvalidModelException(
            path, "A default scene is required for GLTF loading.");

    tinygltf::Scene& scene = _model.scenes[_model.defaultScene];

    _root = std::make_shared<Node>(scene.name);

    for (int id : scene.nodes) {
        _root->addChild(getNode(id));
    }
}

std::shared_ptr<Node> GLTFLoader::scene() { return _root; }