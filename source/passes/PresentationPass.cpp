//
// Created by voxed on 5/24/22.
//

#include <fstream>
#include <memory>
#include <utility>
#include "PresentationPass.h"
#include "Shader.h"
#include "Program.h"

using namespace vx::ember;

void PresentationPass::initialize() {
    std::ifstream vertexShaderStream("assets/presentation_shader.vert");
    std::string vertexShaderSource((std::istreambuf_iterator<char>(vertexShaderStream)),
                                   std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/presentation_shader.frag");
    std::string fragmentShaderSource((std::istreambuf_iterator<char>(fragmentShaderStream)),
                                     std::istreambuf_iterator<char>());

    Shader vertexShader(VertexShader, vertexShaderSource);
    Shader fragmentShader(FragmentShader, fragmentShaderSource);
    _program = std::make_unique<Program>(std::vector<Shader>{vertexShader, fragmentShader});

    glGenVertexArrays(1, &quadVao);
    glBindVertexArray(quadVao);

    glGenBuffers(1, &quadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);

    std::vector<glm::vec3> quadVertices{
            {-1.0, -1.0, 0.0},
            { 1.0, -1.0, 0.0},
            {-1.0,  1.0, 0.0},
            {-1.0,  1.0, 0.0},
            { 1.0, -1.0, 0.0},
            { 1.0,  1.0, 0.0}
    };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), quadVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(PositionLayoutPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(PositionLayoutPosition);

    glBindVertexArray(0);
}

void PresentationPass::render(vx::ember::Node &root) {
    _program->bind();

    glBindVertexArray(quadVao);

    glBindTexture(GL_TEXTURE_2D, _texture);
    glActiveTexture(GL_TEXTURE0);

    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(0);
}

void PresentationPass::resize(int width, int height) {

}

void PresentationPass::deinitialize() {

}

void PresentationPass::setTexture(GLuint texture) {
    _texture = texture;
}
