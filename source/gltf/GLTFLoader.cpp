//
// Created by voxed on 5/29/22.
//

#include "GLTFLoader.h"

#include "core/exceptions.h"
#include "core/nodes/GeometryNode.h"

#include <ranges>

#include <fstream>
#include <stb_image.h>

using namespace vx::ember;

std::shared_ptr<Node> GLTFLoader::getNode(int id) {
    if (!nodeCache.contains(id)) {
        tinygltf::Node& gltfNode = _model.nodes[id];
        auto node = std::make_shared<SpatialNode>(gltfNode.name);
        if (!gltfNode.matrix.empty())
            throw InvalidModelException(_path, "Loader does not currently support raw matrix loading.");
        if (!gltfNode.translation.empty())
            node->setPosition(glm::vec3(gltfNode.translation[0], gltfNode.translation[1], gltfNode.translation[2]));
        if (!gltfNode.rotation.empty())
            node->setRotation(
                glm::quat(gltfNode.rotation[3], gltfNode.rotation[0], gltfNode.rotation[1], gltfNode.rotation[2]));
        if (!gltfNode.scale.empty())
            node->setScale(glm::vec3(gltfNode.scale[0], gltfNode.scale[1], gltfNode.scale[2]));
        if (gltfNode.camera != -1) {
            node->addChild(getCamera(gltfNode.camera));
        }
        if (gltfNode.mesh != -1) {
            auto meshAndMaterials = getMesh(gltfNode.mesh);
            node->addChild(std::make_shared<GeometryNode>(
                meshAndMaterials.first, meshAndMaterials.second, _model.meshes[gltfNode.mesh].name));
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
            throw InvalidModelException(_path, "Only perspective cameras are supported at this time.");
        tinygltf::PerspectiveCamera& perspective = gltfCam.perspective;

        auto camera = std::make_shared<CameraNode>(
            Perspective { (float)perspective.yfov, (float)perspective.znear, (float)perspective.zfar }, gltfCam.name);
        cameraCache[id] = camera;
    }

    return cameraCache[id];
}

std::pair<std::shared_ptr<Mesh>, std::vector<std::shared_ptr<Material>>> GLTFLoader::getMesh(int id) {
    // Temporary super blender-dependent code.
    if (!meshCache.contains(id)) {
        tinygltf::Mesh& gltfMesh = _model.meshes[id];
        std::vector<std::shared_ptr<Material>> fMaterials;
        std::vector<std::shared_ptr<Primitive>> fPrimitives;
        for (auto& primitive : gltfMesh.primitives) {
            auto& indices = _model.accessors[primitive.indices];
            std::vector<unsigned int> fIndices;
            {
                auto& view = _model.bufferViews[indices.bufferView];
                auto data = getBuffer(view.buffer);

                size_t stride = view.byteStride;
                if (stride == 0)
                    stride = sizeof(unsigned short);
                for (int i = 0; i < indices.count; i++) {
                    auto* f = (unsigned short*)&data->at(view.byteOffset + indices.byteOffset + i * stride);
                    fIndices.push_back(*f);
                }
            }
            auto& vertices = _model.accessors[primitive.attributes["POSITION"]];
            std::vector<glm::vec3> fVertices;
            {
                auto& view = _model.bufferViews[vertices.bufferView];
                auto data = getBuffer(view.buffer);

                size_t stride = view.byteStride;
                if (stride == 0)
                    stride = sizeof(glm::vec3);
                for (int i = 0; i < vertices.count; i++) {
                    auto* f = (glm::vec3*)&data->at(view.byteOffset + vertices.byteOffset + i * stride);
                    fVertices.push_back(*f);
                }
            }
            auto& normals = _model.accessors[primitive.attributes["NORMAL"]];
            std::vector<glm::vec3> fNormals;
            {
                auto& view = _model.bufferViews[normals.bufferView];
                auto data = getBuffer(view.buffer);

                size_t stride = view.byteStride;
                if (stride == 0)
                    stride = sizeof(glm::vec3);
                for (int i = 0; i < normals.count; i++) {
                    auto* f = (glm::vec3*)&data->at(view.byteOffset + normals.byteOffset + i * stride);
                    fNormals.push_back(*f);
                }
            }

            auto& tangents = _model.accessors[primitive.attributes["TANGENT"]];
            std::vector<glm::vec4> fTangents;
            {
                auto& view = _model.bufferViews[tangents.bufferView];
                auto data = getBuffer(view.buffer);

                size_t stride = view.byteStride;
                if (stride == 0)
                    stride = sizeof(glm::vec4);
                for (int i = 0; i < tangents.count; i++) {
                    auto* f = (glm::vec4*)&data->at(view.byteOffset + tangents.byteOffset + i * stride);
                    fTangents.push_back(*f);
                }
            }

            auto& texCoords = _model.accessors[primitive.attributes["TEXCOORD_0"]];
            std::vector<glm::vec2> fTexCoords;
            {
                auto& view = _model.bufferViews[texCoords.bufferView];
                auto data = getBuffer(view.buffer);

                size_t stride = view.byteStride;
                if (stride == 0)
                    stride = sizeof(glm::vec2);
                for (int i = 0; i < texCoords.count; i++) {
                    auto* f = (glm::vec2*)&data->at(view.byteOffset + texCoords.byteOffset + i * stride);
                    fTexCoords.push_back(*f);
                }
            }

            std::shared_ptr<Material> mat;
            unsigned int materialIndex = -1;
            if (primitive.material > -1) {
                mat = getMaterial(primitive.material);
                auto itr = std::find(fMaterials.begin(), fMaterials.end(), mat);
                if (itr == fMaterials.cend()) {
                    fMaterials.push_back(mat);
                    materialIndex = fMaterials.size() - 1;
                } else {
                    materialIndex = std::distance(fMaterials.begin(), itr);
                }
            }

            auto primitive2
                = std::make_shared<Primitive>(fVertices, fNormals, fTexCoords, fTangents, fIndices, materialIndex);
            fPrimitives.push_back(primitive2);
        }

        meshCache[id] = std::make_shared<Mesh>(fPrimitives);
        meshBaseMaterialCache[id] = fMaterials;
    }

    return { meshCache[id], meshBaseMaterialCache[id] };
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
        throw InvalidModelException(path, "A default scene is required for GLTF loading.");

    tinygltf::Scene& scene = _model.scenes[_model.defaultScene];

    _root = std::make_shared<Node>(scene.name);

    for (int id : scene.nodes) {
        _root->addChild(getNode(id));
    }
}

std::shared_ptr<Node> GLTFLoader::scene() { return _root; }

std::shared_ptr<Material> GLTFLoader::getMaterial(int id) {
    if (!materialCache.contains(id)) {
        std::shared_ptr<Texture> baseColorTexture;
        std::shared_ptr<Texture> metallicRoughnessTexture;
        std::shared_ptr<Texture> normalMapTexture;
        std::shared_ptr<Texture> emissionMapTexture;
        tinygltf::Material& gltfMat = _model.materials[id];
        if (gltfMat.pbrMetallicRoughness.baseColorTexture.index > -1) {
            baseColorTexture = getTexture(gltfMat.pbrMetallicRoughness.baseColorTexture.index);
        }
        if (gltfMat.pbrMetallicRoughness.metallicRoughnessTexture.index > -1) {
            metallicRoughnessTexture = getTexture(gltfMat.pbrMetallicRoughness.metallicRoughnessTexture.index);
        }
        if (gltfMat.normalTexture.index > -1) {
            normalMapTexture = getTexture(gltfMat.normalTexture.index);
        }
        if (gltfMat.emissiveTexture.index > -1) {
            emissionMapTexture = getTexture(gltfMat.emissiveTexture.index);
        }
        materialCache[id] = std::make_shared<Material>(gltfMat.name,
            glm::vec4(gltfMat.pbrMetallicRoughness.baseColorFactor[0], gltfMat.pbrMetallicRoughness.baseColorFactor[1],
                gltfMat.pbrMetallicRoughness.baseColorFactor[2], gltfMat.pbrMetallicRoughness.baseColorFactor[3]),
            glm::vec4(gltfMat.emissiveFactor[0], gltfMat.emissiveFactor[1], gltfMat.emissiveFactor[2],
                gltfMat.emissiveFactor[3]),
            baseColorTexture, gltfMat.pbrMetallicRoughness.metallicFactor, gltfMat.pbrMetallicRoughness.roughnessFactor,
            gltfMat.normalTexture.scale, gltfMat.doubleSided, metallicRoughnessTexture, normalMapTexture,
            emissionMapTexture);
    }

    return materialCache[id];
}

std::shared_ptr<Texture> GLTFLoader::getTexture(int index) {
    if (!textureCache.contains(index)) {
        tinygltf::Texture& gltfTex = _model.textures[index];
        std::shared_ptr<Image> img = getImage(gltfTex.source);
        GLint wrapS, wrapT, magFilter, minFilter;

        if (gltfTex.sampler > -1) {
            tinygltf::Sampler sampler = _model.samplers[gltfTex.sampler];
            switch (sampler.wrapS) {
            case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
                wrapS = GL_CLAMP_TO_EDGE;
                break;
            case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
                wrapS = GL_MIRRORED_REPEAT;
                break;
            case TINYGLTF_TEXTURE_WRAP_REPEAT:
                wrapS = GL_REPEAT;
                break;
            }
            switch (sampler.wrapT) {
            case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
                wrapT = GL_CLAMP_TO_EDGE;
                break;
            case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
                wrapT = GL_MIRRORED_REPEAT;
                break;
            case TINYGLTF_TEXTURE_WRAP_REPEAT:
                wrapT = GL_REPEAT;
                break;
            }
            switch (sampler.magFilter) {
            case TINYGLTF_TEXTURE_FILTER_LINEAR:
                magFilter = GL_LINEAR;
                break;
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
                magFilter = GL_LINEAR_MIPMAP_LINEAR;
                break;
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
                magFilter = GL_LINEAR_MIPMAP_NEAREST;
                break;
            case TINYGLTF_TEXTURE_FILTER_NEAREST:
                magFilter = GL_NEAREST;
                break;
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
                magFilter = GL_NEAREST_MIPMAP_LINEAR;
                break;
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
                magFilter = GL_NEAREST_MIPMAP_NEAREST;
                break;
            }
            switch (sampler.minFilter) {
            case TINYGLTF_TEXTURE_FILTER_LINEAR:
                minFilter = GL_LINEAR;
                break;
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
                minFilter = GL_LINEAR_MIPMAP_LINEAR;
                break;
            case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:
                minFilter = GL_LINEAR_MIPMAP_NEAREST;
                break;
            case TINYGLTF_TEXTURE_FILTER_NEAREST:
                minFilter = GL_NEAREST;
                break;
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:
                minFilter = GL_NEAREST_MIPMAP_LINEAR;
                break;
            case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:
                minFilter = GL_NEAREST_MIPMAP_NEAREST;
                break;
            }
        }

        textureCache[index] = Texture::create(
            GL_TEXTURE_2D, img->width(), img->height(), GL_RGBA16, 8, minFilter, magFilter, wrapS, wrapT);

        textureCache[index]->setParameterf(GL_TEXTURE_MAX_ANISOTROPY, 16.0f);

        textureCache[index]->subImage2D(*img);
        textureCache[index]->generateMipmaps();
    }
    return textureCache[index];
}
std::shared_ptr<Image> GLTFLoader::getImage(int index) {
    if (!imageCache.contains(index)) {
        tinygltf::Image& gltfImg = _model.images[index];
        stbi_uc* stbData;
        int width, height, channels;
        if (!gltfImg.uri.empty()) {
            printf("Loading image %s\n", (_path.parent_path() / gltfImg.uri).c_str());
            stbData = stbi_load((_path.parent_path() / gltfImg.uri).c_str(), &width, &height, &channels, 4);
            printf("size: %i, max_size: %zu\n", abs(width) * abs(height) * 4, std::vector<unsigned char>().max_size());
        } else {
            auto& view = _model.bufferViews[gltfImg.bufferView];
            auto& buffer = _model.buffers[view.buffer];

            auto data = std::vector<unsigned char>(
                buffer.data.begin() + view.byteOffset, buffer.data.begin() + view.byteOffset + view.byteLength);

            stbData = stbi_load_from_memory(data.data(), data.size(), &width, &height, &channels, 4);
        }
        imageCache[index]
            = std::make_shared<Image>(width, height, stbData, GL_RGBA, GL_UNSIGNED_BYTE, abs(width) * abs(height) * 4);
    }
    return imageCache[index];
}
std::shared_ptr<std::vector<char>> GLTFLoader::getBuffer(int index) {
    if (!bufferCache.contains(index)) {
        auto& buffer = _model.buffers[index];
        if (buffer.data.empty()) {
            std::ifstream file((_path.parent_path() / buffer.uri).string(), std::ios::binary);

            auto v = std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            bufferCache[index] = std::make_shared<std::vector<char>>(v);

            printf("%s loaded buffer %zu\n", (_path.parent_path() / buffer.uri).c_str(), v.size());
            printf("LOADING FILE no file\n");
        } else {
            printf("LOADING FILE\n");
            bufferCache[index] = std::make_shared<std::vector<char>>(buffer.data.begin(), buffer.data.end());
        }
    }
    return bufferCache[index];
}
