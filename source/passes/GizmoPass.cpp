//
// Created by voxed on 6/1/22.
//

#include "GizmoPass.h"
#include "gl/BufferObject.h"
#include "obj/OBJLoader.h"
#include "visitors/CameraLocatorVisitor.h"
#include "visitors/GeometryRendererVisitor.h"
#include "visitors/GizmoRendererVisitor.h"
#include <fstream>
#include <utility>

using namespace vx::ember;

void GizmoPass::initialize() {
    std::ifstream vertexShaderStream("assets/light_gizmo_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)),
        std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/light_gizmo_shader.frag");
    std::string fragmentShaderSource(
        (std::istreambuf_iterator<char>(fragmentShaderStream)),
        std::istreambuf_iterator<char>());

    Shader vertexShader(
        "geometry shader", GL_VERTEX_SHADER, vertexShaderSource);
    Shader fragmentShader(
        "geometry shader", GL_FRAGMENT_SHADER, fragmentShaderSource);
    _program = std::make_unique<Program>(
        std::vector<Shader*> { &vertexShader, &fragmentShader });

    matrixUBO
        = std::make_shared<BufferObject>(sizeof(MatrixBlock), GL_MAP_WRITE_BIT);

    _sphereMesh = OBJLoader("assets/sphere.obj").mesh();
}

void GizmoPass::render(Node& root) {

    CameraLocatorVisitor cameraLocator;
    root.accept(cameraLocator);

    if (cameraLocator.camera()) {
        auto block = matrixUBO->mapRange<MatrixBlock>(GL_MAP_WRITE_BIT);
        block->v = cameraLocator.camera()->viewMatrix();
        block->p = cameraLocator.camera()->projection(
            (float)_width / (float)_height);
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, _width, _height);
    _fb.bind(GL_FRAMEBUFFER);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _geoPass->depthTexture());

    matrixUBO->bind(GL_UNIFORM_BUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GizmoRendererVisitor gizmoRenderer(*_program, _sphereMesh, _rsmPass);
    root.accept(gizmoRenderer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GizmoPass::resize(int width, int height) {
    _width = width;
    _height = height;

    _gizmoColorBuffer = Texture(
        GL_TEXTURE_2D, width, height, GL_LINEAR, GL_LINEAR, GL_RGBA16F, 1);
    _gizmoDepthBuffer = Texture(GL_TEXTURE_2D, width, height, GL_LINEAR,
        GL_LINEAR, GL_DEPTH_COMPONENT32, 1);

    _fb.bindTexture(*_gizmoColorBuffer, GL_COLOR_ATTACHMENT0, 0);
    _fb.bindTexture(*_gizmoDepthBuffer, GL_DEPTH_ATTACHMENT, 0);

    _program->bind();
    glUniform2f(1, (float)width, (float)height);
}

void GizmoPass::deinitialize() { }
GLuint GizmoPass::texture() { return _gizmoColorBuffer->_index; }

GizmoPass::GizmoPass(
    std::shared_ptr<RSMPass> rsmPass, std::shared_ptr<GeometryPass> geoPass)
    : _rsmPass(std::move(rsmPass))
    , _geoPass(std::move(geoPass)) { }
