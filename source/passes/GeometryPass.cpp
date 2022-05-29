//
// Created by voxed on 5/20/22.
//

#include "GeometryPass.h"

#include <stdio.h>
#include <cmath>
#include "visitors/nodes/Node.h"
#include "visitors/CameraLocatorVisitor.h"
#include "visitors/GeometryRendererVisitor.h"
#include <string>
#include <fstream>

using namespace vx::ember;

GeometryPass::GeometryPass() {

}

void GeometryPass::initialize() {
    printf("INITIALIZING GEO PASS\n");

    std::ifstream vertexShaderStream("assets/geometry_shader.vert");
    std::string vertexShaderSource((std::istreambuf_iterator<char>(vertexShaderStream)),
                                   std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/geometry_shader.frag");
    std::string fragmentShaderSource((std::istreambuf_iterator<char>(fragmentShaderStream)),
                                     std::istreambuf_iterator<char>());

    Shader vertexShader(VertexShader, vertexShaderSource);
    Shader fragmentShader(FragmentShader, fragmentShaderSource);
    _program = std::make_unique<Program>(std::vector<Shader>{vertexShader, fragmentShader});
}

void GeometryPass::render(Node &root) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CameraLocatorVisitor cameraLocator;
    root.accept(cameraLocator);

    if (cameraLocator.camera()) {
        _program->setViewMatrix(glm::inverse(cameraLocator.camera()->worldMatrix() * cameraLocator.camera()->matrix()));
        _program->setProjectionMatrix(cameraLocator.camera()->projection((float) _width / (float) _height));
    }


    glEnable(GL_DEPTH_TEST);

    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GeometryRendererVisitor geometryRenderer(_program.get());
    root.accept(geometryRenderer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GeometryPass::deinitialize() {

}

void GeometryPass::resize(int width, int height) {
    _width = width;
    _height = height;

    glGenTextures(1, &normalBuffer);
    glBindTexture(GL_TEXTURE_2D, normalBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &positionBuffer);
    glBindTexture(GL_TEXTURE_2D, positionBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &depthBuffer);
    glBindTexture(GL_TEXTURE_2D, depthBuffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    //bind texture as colour attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, normalBuffer, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, positionBuffer, 0);
    std::vector<GLuint> drawBuffers{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, drawBuffers.data());
    //bind the texture as depth attchment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthBuffer, 0);
}

GLuint GeometryPass::normalTexture() {
    return normalBuffer;
}

GLuint GeometryPass::depthTexture() {
    return depthBuffer;
}

GLuint GeometryPass::positionTexture() {
    return positionBuffer;
}
