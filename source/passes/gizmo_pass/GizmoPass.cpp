//
// Created by voxed on 6/1/22.
//

#include "GizmoPass.h"

#include "gl/BufferObject.h"
#include "obj/OBJLoader.h"
#include "passes/common/visitors/CameraLocatorVisitor.h"
#include "passes/common/visitors/GeometryRendererVisitor.h"
#include "visitors/GizmoRendererVisitor.h"

#include <fstream>

using namespace vx::ember;

void GizmoPass::initialize() {
    std::ifstream vertexShaderStream("assets/light_gizmo_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)), std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/light_gizmo_shader.frag");
    std::string fragmentShaderSource(
        (std::istreambuf_iterator<char>(fragmentShaderStream)), std::istreambuf_iterator<char>());

    auto vertexShader = Shader::create("geometry shader", GL_VERTEX_SHADER, vertexShaderSource);
    auto fragmentShader = Shader::create("geometry shader", GL_FRAGMENT_SHADER, fragmentShaderSource);
    _program = Program::create({ vertexShader.get(), fragmentShader.get() });

    matrixUBO = BufferObject::create(sizeof(MatrixBlock), GL_MAP_WRITE_BIT);

    _sphereMesh = OBJLoader("assets/sphere.obj").mesh();

    _fb = Framebuffer::create();
}

void GizmoPass::render(Node& root) {

    CameraLocatorVisitor cameraLocator;
    root.accept(cameraLocator);

    if (cameraLocator.camera()) {
        auto block = matrixUBO->mapRange<MatrixBlock>(GL_MAP_WRITE_BIT);
        block->v = cameraLocator.camera()->viewMatrix();
        block->p = cameraLocator.camera()->projection((float)_width / (float)_height);
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, _width, _height);
    _fb->bind(GL_FRAMEBUFFER);

    _occluderDepthBuffer->get()->bind(1);

    matrixUBO->bind(GL_UNIFORM_BUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GizmoRendererVisitor gizmoRenderer(*_program, _sphereMesh, *_rsmCache, _bufferType);
    root.accept(gizmoRenderer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GizmoPass::resize(int width, int height) {
    _width = width;
    _height = height;

    _gizmoColorBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_RGBA16F, 1, GL_LINEAR, GL_LINEAR);
    _gizmoDepthBuffer = Texture::create(GL_TEXTURE_2D, width, height, GL_DEPTH_COMPONENT32, 1, GL_LINEAR, GL_LINEAR);

    _fb->bindTexture(*_gizmoColorBuffer, GL_COLOR_ATTACHMENT0, 0);
    _fb->bindTexture(*_gizmoDepthBuffer, GL_DEPTH_ATTACHMENT, 0);

    _program->bind();
    glUniform2f(1, (float)width, (float)height);
}

void GizmoPass::deinitialize() { }
std::unique_ptr<Texture>& GizmoPass::texture() { return _gizmoColorBuffer; }

GizmoPass::GizmoPass(RSMCache& rsmCache, std::unique_ptr<Texture>& occluderDepthBuffer)
    : _rsmCache(&rsmCache)
    , _occluderDepthBuffer(&occluderDepthBuffer)
    , _width(0)
    , _height(0)
    , _bufferType(NORMAL_BUFFER) { }

void GizmoPass::setBufferType(BufferType type) { _bufferType = type; }
