//
// Created by voxed on 5/24/22.
//

#include "PresentationPass.h"

#include "gl/Program.h"
#include "gl/Shader.h"

#include <fstream>

using namespace vx::ember;

void PresentationPass::initialize() {
    std::ifstream vertexShaderStream("assets/presentation_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)), std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/presentation_shader.frag");
    std::string fragmentShaderSource(
        (std::istreambuf_iterator<char>(fragmentShaderStream)), std::istreambuf_iterator<char>());

    auto vertexShader = Shader::create("presentation shader", GL_VERTEX_SHADER, vertexShaderSource);
    auto fragmentShader = Shader::create("presentation shader", GL_FRAGMENT_SHADER, fragmentShaderSource);
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
}

void PresentationPass::render(vx::ember::Node& root) {
    _program->bind();

    glUniform1i(0, _isCubemap);
    glUniform1i(1, _face);
    glUniform1i(2, _useGizmos);
    glUniform1i(3, _isArray);
    glUniform1i(4, _element);

    glUniform1i(5, _mixArray);
    glUniform1i(6, _mixArrayCount);

    glBindVertexArray(quadVao);

    if (_isCubemap) {
        _texture->bind(1);
    } else if (_isArray) {
        _texture->bind(3);
    } else {
        _texture->bind(0);
    }

    if (_useGizmos) {
        _gizmosTexture->bind(2);
    }

    glViewport(0, 0, _width, _height);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(0);
}

void PresentationPass::resize(int width, int height) {
    _width = width;
    _height = height;
}

void PresentationPass::deinitialize() { }

void PresentationPass::setTexture(Texture& texture) { _texture = &texture; }

void PresentationPass::setCubemap(bool cubemap) { _isCubemap = cubemap; }

void PresentationPass::setFace(int face) { _face = face; }
void PresentationPass::setGizmosTexture(Texture& texture) { _gizmosTexture = &texture; }
void PresentationPass::setGizmos(bool gizmos) { _useGizmos = gizmos; }
void PresentationPass::setArray(bool array) { _isArray = array; }
void PresentationPass::setElement(unsigned int element) { _element = element; }
void PresentationPass::setMixArray(bool mixArray) { _mixArray = mixArray; }
void PresentationPass::setMixArrayCount(unsigned int mixArrayCount) { _mixArrayCount = mixArrayCount; }
