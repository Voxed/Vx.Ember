//
// Created by voxed on 6/14/22.
//

#include "LightPass.h"
#include "passes/common/visitors/CameraLocatorVisitor.h"
#include <fstream>

using namespace vx::ember;

LightPass::LightPass(RSMCache& cache, std::unique_ptr<Texture>& positionMap, std::unique_ptr<Texture>& normalMap,
    std::unique_ptr<Texture>& metallicMap, std::unique_ptr<Texture>& colorMap)
    : _cache(&cache)
    , _positionMap(&positionMap)
    , _normalMap(&normalMap)
    , _metallicMap(&metallicMap)
    , _colorMap(&colorMap) { }

void LightPass::initialize() {
    printf("ARRAY SIZE: %i\n", _lightMapCount);

    std::ifstream vertexShaderStream("assets/light_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)), std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/light_shader.frag");
    std::string fragmentShaderSource(
        (std::istreambuf_iterator<char>(fragmentShaderStream)), std::istreambuf_iterator<char>());

    auto vertexShader = Shader::create("light shader", GL_VERTEX_SHADER, vertexShaderSource);
    auto fragmentShader = Shader::create("light shader", GL_FRAGMENT_SHADER, fragmentShaderSource);
    _program = Program::create({ vertexShader.get(), fragmentShader.get() });

    glGenVertexArrays(1, &quadVao);
    glBindVertexArray(quadVao);

    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);

    std::vector<glm::vec3> quadVertices { { -1.0, -1.0, 0.0 }, { 1.0, -1.0, 0.0 }, { -1.0, 1.0, 0.0 },
        { -1.0, 1.0, 0.0 }, { 1.0, -1.0, 0.0 }, { 1.0, 1.0, 0.0 } };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), quadVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(PositionLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(PositionLayoutPosition);

    glBindVertexArray(0);

    _msFramebuffer = Framebuffer::create();
    //_framebuffer = Framebuffer::create();
}

void LightPass::render(Node& root) {
    _lightMapCount = _cache->size();

    CameraLocatorVisitor cameraLocator;
    root.accept(cameraLocator);
    glm::vec3 cam_ps
        = cameraLocator.camera()->worldMatrix() * cameraLocator.camera()->matrix() * glm::vec4(0.0, 0.0, 0.0, 1.0);

    _program->setUniform(1, cam_ps);

    for (int i = 0; i < _lightMapCount; i++) {
        _msFramebuffer->bindTexture(*_msLightMaps, GL_COLOR_ATTACHMENT0, 0, i);
        _msFramebuffer->bind(GL_FRAMEBUFFER);

        glClear(GL_COLOR_BUFFER_BIT);

        _positionMap->get()->bind(0);
        _normalMap->get()->bind(1);
        _metallicMap->get()->bind(2);
        _colorMap->get()->bind(3);

        _program->bind();

        glm::mat4 modelMatrix = _cache->getLight(i)->worldMatrix() * _cache->getLight(i)->matrix();
        glm::vec3 pos = modelMatrix * glm::vec4(0.0, 0.0, 0.0, 1.0);

        _program->setUniform(0, pos);
        _cache->get(i).depthTexture().bind(4);

        _cache->getLight(i)->ubo().bind(GL_UNIFORM_BUFFER, 1);

        glBindVertexArray(quadVao);

        glViewport(0, 0, _width, _height);
        glDisable(GL_DEPTH_TEST);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_DEPTH_TEST);

        glUseProgram(0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        //_msFramebuffer->blitColorAttachments(
        //    *_framebuffer, 0, 0, _width, _height, 0, 0, _width, _height, { GL_COLOR_ATTACHMENT0 }, GL_LINEAR);
    }
}

void LightPass::resize(int width, int height) {
    _width = width;
    _height = height;

    // TODO: Not 16, duh. dynamic?
    // TODO: > 16 crashes program? Whoops :/ (16*8 samples too much?)
    _msLightMaps = Texture::createMultisampled3D(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, width, height, 16, GL_RGBA32F, 8);
    //_msFramebuffer->bindTexture(*_msLightMaps, GL_COLOR_ATTACHMENT0, 0);

    //_lightMaps = Texture::create3D(GL_TEXTURE_2D_ARRAY, width, height, 32, GL_RGBA16F, 1);
}

void LightPass::deinitialize() { }

unsigned int LightPass::lightMapCount() const { return _lightMapCount; }

std::unique_ptr<Texture>& LightPass::lightMaps() { return _msLightMaps; }
