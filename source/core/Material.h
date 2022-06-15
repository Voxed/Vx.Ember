//
// Created by voxed on 6/6/22.
//

#ifndef VX_EMBER_MATERIAL_H
#define VX_EMBER_MATERIAL_H

#include "gl/BufferObject.h"
#include "gl/Texture.h"
#include <glm/vec4.hpp>
#include <memory>

namespace vx::ember {

struct MaterialUniformBlock {
    glm::vec4 baseColor;
    glm::vec4 emission;
    float metallic;
    float roughness;
    float normalMapScale;
    unsigned int hasBaseColorTexture;
    unsigned int hasMetallicRoughnessTexture;
    unsigned int hasNormalMapTexture;
    unsigned int hasEmissionMapTexture;
};

class Material {
    std::shared_ptr<Texture> _baseColorTexture;
    glm::vec4 _baseColor;
    glm::vec4 _emission;
    float _roughness;
    float _normalMapScale;
    float _metallic;
    std::unique_ptr<BufferObject> _ubo;
    std::shared_ptr<Texture> _metallicRoughnessTexture;
    std::shared_ptr<Texture> _normalMapTexture;
    std::shared_ptr<Texture> _emissionMapTexture;
    std::string _name;
    bool _doubleSided;

public:
    explicit Material(std::string name, glm::vec4 baseColor, glm::vec4 emission,
        std::shared_ptr<Texture> baseColorTexture, float metallic, float roughness, float normalMapScale,
        bool doubleSided, std::shared_ptr<Texture> metallicRoughnessTexture, std::shared_ptr<Texture> normalMapTexture,
        std::shared_ptr<Texture> emissionMapTexture);

    void bind(GLuint uboBinding, GLuint baseColorTextureBinding, GLuint metallicRoughnessTextureBinding,
        GLuint normalMapTextureBinding, GLuint emissionMapTextureBinding);

    std::shared_ptr<Material> copy();

    std::string name();

    glm::vec4 baseColor();
    glm::vec4 emission();
    [[nodiscard]] float roughness() const;
    [[nodiscard]] float normalMapScale() const;
    [[nodiscard]] float metallic() const;
    [[nodiscard]] bool doubleSided() const;

    void setBaseColor(glm::vec4 v);
    void setEmission(glm::vec4 v);
    void setRoughness(float v);
    void setNormalMapScale(float v);
    void setMetallic(float v);
    void setDoubleSided(bool v);
};

}

#endif // VX_EMBER_MATERIAL_H
