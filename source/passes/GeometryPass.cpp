//
// Created by voxed on 5/20/22.
//

#include "GeometryPass.h"

#include "visitors/CameraLocatorVisitor.h"
#include "visitors/GeometryRendererVisitor.h"
#include "visitors/nodes/Node.h"
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace vx::ember;

GeometryPass::GeometryPass() { }

void GeometryPass::initialize() {
    printf("INITIALIZING GEO PASS\n");

    std::ifstream vertexShaderStream("assets/geometry_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)),
        std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/geometry_shader.frag");
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
}

void GeometryPass::render(Node& root) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    _fb.bind();
    matrixUBO->bind(GL_UNIFORM_BUFFER, 0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GeometryRendererVisitor geometryRenderer(_program.get(), matrixUBO);
    root.accept(geometryRenderer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GeometryPass::deinitialize() { }

void GeometryPass::resize(int width, int height) {
    _width = width;
    _height = height;
    _fb.resize(width, height);
}

GLuint GeometryPass::normalTexture() { return _fb.normalTexture(); }

GLuint GeometryPass::depthTexture() { return _fb.depthTexture(); }

GLuint GeometryPass::positionTexture() { return _fb.positionTexture(); }
