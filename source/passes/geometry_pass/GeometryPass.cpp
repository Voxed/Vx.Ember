//
// Created by voxed on 5/20/22.
//

#include "GeometryPass.h"

#include "core/nodes/Node.h"
#include "passes/common/visitors/CameraLocatorVisitor.h"
#include "passes/common/visitors/GeometryRendererVisitor.h"

#include <cstdio>
#include <fstream>
#include <string>

using namespace vx::ember;

void GeometryPass::initialize() {
    printf("INITIALIZING GEO PASS\n");

    std::ifstream vertexShaderStream("assets/geometry_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)), std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/geometry_shader.frag");
    std::string fragmentShaderSource(
        (std::istreambuf_iterator<char>(fragmentShaderStream)), std::istreambuf_iterator<char>());

    auto vertexShader = Shader::create("geometry shader", GL_VERTEX_SHADER, vertexShaderSource);
    auto fragmentShader = Shader::create("geometry shader", GL_FRAGMENT_SHADER, fragmentShaderSource);
    _program = Program::create({ vertexShader.get(), fragmentShader.get() });

    matrixUBO = BufferObject::create(sizeof(MatrixBlock), GL_MAP_WRITE_BIT);

    //_frameBuffer = Framebuffer::create();
    _msFrameBuffer = Framebuffer::create();
}

void GeometryPass::render(Node& root) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraLocatorVisitor cameraLocator;
    root.accept(cameraLocator);

    if (cameraLocator.camera()) {
        auto block = matrixUBO->mapRange<MatrixBlock>(GL_MAP_WRITE_BIT);
        block->v = cameraLocator.camera()->viewMatrix();
        block->p = cameraLocator.camera()->projection((float)_width / (float)_height);
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, _width, _height);
    _msFrameBuffer->bind(GL_FRAMEBUFFER);
    matrixUBO->bind(GL_UNIFORM_BUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GeometryRendererVisitor geometryRenderer(
        cameraLocator.camera()->projection((float)_width / (float)_height) * cameraLocator.camera()->viewMatrix(),
        _program.get());
    root.accept(geometryRenderer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /*_msFrameBuffer->blitColorAttachments(*_frameBuffer, 0, 0, _width, _height, 0, 0, _width, _height,
        { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
            GL_COLOR_ATTACHMENT4 },
        GL_LINEAR);

    _msFrameBuffer->blit(*_frameBuffer, 0, 0, _width, _height, 0, 0, _width, _height, GL_DEPTH_BUFFER_BIT,
    GL_NEAREST);
     */
}

void GeometryPass::deinitialize() { }

void GeometryPass::resize(int width, int height) {
    _width = width;
    _height = height;

    /*
    _normalBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_RGBA16F, 1, GL_LINEAR, GL_LINEAR);
    _positionBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_RGBA16F, 1, GL_LINEAR, GL_LINEAR);
    _colorBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_RGBA16F, 1, GL_LINEAR, GL_LINEAR);
    _metallicRoughnessTexture = Texture::create(GL_TEXTURE_2D, width, height, GL_RGBA16F, 1, GL_LINEAR, GL_LINEAR);
    _emissionBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_RGBA16F, 1, GL_LINEAR, GL_LINEAR);
    _depthBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_DEPTH_COMPONENT32, 1, GL_LINEAR, GL_LINEAR);

    _frameBuffer->bindTexture(*_depthBuffer, GL_DEPTH_ATTACHMENT, 0);
    _frameBuffer->bindTexture(*_normalBuffer, GL_COLOR_ATTACHMENT0, 0);
    _frameBuffer->bindTexture(*_positionBuffer, GL_COLOR_ATTACHMENT1, 0);
    _frameBuffer->bindTexture(*_colorBuffer, GL_COLOR_ATTACHMENT2, 0);
    _frameBuffer->bindTexture(*_metallicRoughnessTexture, GL_COLOR_ATTACHMENT3, 0);
    _frameBuffer->bindTexture(*_emissionBuffer, GL_COLOR_ATTACHMENT4, 0);
    _frameBuffer->drawBuffers({ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
        GL_COLOR_ATTACHMENT4 });
    */

    _msNormalBuffer
        = Texture::createMultisampled(GL_TEXTURE_2D_MULTISAMPLE, width, height, GL_RGBA16F, 8, GL_LINEAR, GL_LINEAR);
    _msPositionBuffer
        = Texture::createMultisampled(GL_TEXTURE_2D_MULTISAMPLE, width, height, GL_RGBA16F, 8, GL_LINEAR, GL_LINEAR);
    _msColorBuffer
        = Texture::createMultisampled(GL_TEXTURE_2D_MULTISAMPLE, width, height, GL_RGBA16F, 8, GL_LINEAR, GL_LINEAR);
    _msMetallicRoughnessTexture
        = Texture::createMultisampled(GL_TEXTURE_2D_MULTISAMPLE, width, height, GL_RGBA16F, 8, GL_LINEAR, GL_LINEAR);
    _msEmissionBuffer
        = Texture::createMultisampled(GL_TEXTURE_2D_MULTISAMPLE, width, height, GL_RGBA16F, 8, GL_LINEAR, GL_LINEAR);
    _msDepthBuffer = Texture::createMultisampled(
        GL_TEXTURE_2D_MULTISAMPLE, width, height, GL_DEPTH_COMPONENT32, 8, GL_LINEAR, GL_LINEAR);

    _msFrameBuffer->bindTexture(*_msDepthBuffer, GL_DEPTH_ATTACHMENT, 0);
    _msFrameBuffer->bindTexture(*_msNormalBuffer, GL_COLOR_ATTACHMENT0, 0);
    _msFrameBuffer->bindTexture(*_msPositionBuffer, GL_COLOR_ATTACHMENT1, 0);
    _msFrameBuffer->bindTexture(*_msColorBuffer, GL_COLOR_ATTACHMENT2, 0);
    _msFrameBuffer->bindTexture(*_msMetallicRoughnessTexture, GL_COLOR_ATTACHMENT3, 0);
    _msFrameBuffer->bindTexture(*_msEmissionBuffer, GL_COLOR_ATTACHMENT4, 0);
    _msFrameBuffer->drawBuffers({ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 });
}

std::unique_ptr<Texture>& GeometryPass::normalTexture() { return _msNormalBuffer; }

std::unique_ptr<Texture>& GeometryPass::depthTexture() { return _msDepthBuffer; }

std::unique_ptr<Texture>& GeometryPass::positionTexture() { return _msPositionBuffer; }

std::unique_ptr<Texture>& GeometryPass::colorTexture() { return _msColorBuffer; }

std::unique_ptr<Texture>& GeometryPass::metallicRoughnessTexture() { return _msMetallicRoughnessTexture; }
std::unique_ptr<Texture>& GeometryPass::emissionBuffer() { return _msEmissionBuffer; }
