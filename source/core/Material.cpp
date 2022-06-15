//
// Created by voxed on 6/6/22.
//

#include "Material.h"

#include <utility>

using namespace vx::ember;

Material::Material(std::string name, glm::vec4 baseColor, glm::vec4 emission, std::shared_ptr<Texture> baseColorTexture,
    float metallic, float roughness, float normalMapScale, bool doubleSided,
    std::shared_ptr<Texture> metallicRoughnessTexture, std::shared_ptr<Texture> normalMapTexture,
    std::shared_ptr<Texture> emissionMapTexture)
    : _baseColorTexture(std::move(baseColorTexture))
    , _baseColor(baseColor)
    , _metallicRoughnessTexture(std::move(metallicRoughnessTexture))
    , _normalMapTexture(std::move(normalMapTexture))
    , _emissionMapTexture(std::move(emissionMapTexture))
    , _name(name)
    , _normalMapScale(normalMapScale)
    , _roughness(roughness)
    , _emission(emission)
    , _metallic(metallic)
    , _doubleSided(doubleSided) {
    MaterialUniformBlock mub = { .baseColor = _baseColor,
        .emission = emission,
        .metallic = metallic,
        .roughness = roughness,
        .normalMapScale = normalMapScale,
        .hasBaseColorTexture = static_cast<unsigned int>(_baseColorTexture ? 1 : 0),
        .hasMetallicRoughnessTexture = static_cast<unsigned int>(_metallicRoughnessTexture ? 1 : 0),
        .hasNormalMapTexture = static_cast<unsigned int>(_normalMapTexture ? 1 : 0),
        .hasEmissionMapTexture = static_cast<unsigned int>(_emissionMapTexture ? 1 : 0) };
    _ubo = BufferObject::create(GL_MAP_WRITE_BIT, &mub);
}

void Material::bind(GLuint uboBinding, GLuint baseColorTextureBinding, GLuint metallicRoughnessTextureBinding,
    GLuint normalMapTextureBinding, GLuint emissionMapTextureBinding) {

    if (_baseColorTexture) {
        _baseColorTexture->bind(baseColorTextureBinding);
    }
    if (_metallicRoughnessTexture) {
        _metallicRoughnessTexture->bind(metallicRoughnessTextureBinding);
    }
    if (_normalMapTexture) {
        _normalMapTexture->bind(normalMapTextureBinding);
    }
    if (_emissionMapTexture) {
        _emissionMapTexture->bind(emissionMapTextureBinding);
    }
    if (!_doubleSided) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
    _ubo->bind(GL_UNIFORM_BUFFER, uboBinding);
}

std::string Material::name() { return _name; }
std::shared_ptr<Material> Material::copy() {
    return std::make_shared<Material>(_name, _baseColor, _emission, _baseColorTexture, _metallic, _roughness,
        _normalMapScale, _doubleSided, _metallicRoughnessTexture, _normalMapTexture, _emissionMapTexture);
}
glm::vec4 Material::baseColor() { return _baseColor; }
glm::vec4 Material::emission() { return _emission; }
float Material::roughness() const { return _roughness; }
float Material::normalMapScale() const { return _normalMapScale; }
float Material::metallic() const { return _metallic; }
bool Material::doubleSided() const { return _doubleSided; }

void Material::setBaseColor(glm::vec4 v) {
    _baseColor = v;
    _ubo->mapRange<MaterialUniformBlock>(GL_MAP_WRITE_BIT)->baseColor = _baseColor;
}
void Material::setEmission(glm::vec4 v) {
    _emission = v;
    _ubo->mapRange<MaterialUniformBlock>(GL_MAP_WRITE_BIT)->emission = _emission;
}
void Material::setRoughness(float v) {
    _roughness = v;
    _ubo->mapRange<MaterialUniformBlock>(GL_MAP_WRITE_BIT)->roughness = _roughness;
}
void Material::setNormalMapScale(float v) {
    _normalMapScale = v;
    _ubo->mapRange<MaterialUniformBlock>(GL_MAP_WRITE_BIT)->normalMapScale = _normalMapScale;
}
void Material::setMetallic(float v) {
    _metallic = v;
    _ubo->mapRange<MaterialUniformBlock>(GL_MAP_WRITE_BIT)->metallic = _metallic;
}
void Material::setDoubleSided(bool v) { _doubleSided = v; }
