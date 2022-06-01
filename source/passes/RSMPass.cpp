//
// Created by voxed on 5/29/22.
//

#include "RSMPass.h"
#include "visitors/GeometryRendererVisitor.h"
#include "visitors/LightLocatorVisitor.h"
#include "visitors/nodes/Node.h"
#include "visitors/nodes/PointLightNode.h"

#include <fstream>
#include <initializer_list>
#include <ranges>

using namespace vx::ember;

void RSMPass::initialize() {
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

    matrixUBO = BufferObject::allocatePtr<MatrixBlock>(GL_MAP_WRITE_BIT);
}

void RSMPass::render(Node& root) {
    LightLocatorVisitor lightLocatorVisitor;
    root.accept(lightLocatorVisitor);
    std::vector<PointLightNode*> pointLights = lightLocatorVisitor.lights();

    for (auto& l : pointLights) {
        if (!_lightCache.contains(l))
            _lightCache[l];

        RSMFramebuffer& cache = _lightCache[l];

        for (int i = 0; i < 6; i++) {
            glm::vec3 position = (l->worldMatrix() * l->matrix()
                * glm::vec4(0.0, 0.0, 0.0, 1.0));

            float aspect = (float)cache.width() / (float)cache.height();
            float near = 0.01f;
            float far = 25.0f;
            glm::mat4 shadowProj
                = glm::perspective(glm::radians(90.0f), aspect, near, far);

            std::vector<glm::mat4> shadowTransforms;
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0),
                    glm::vec3(0.0, -1.0, 0.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0),
                    glm::vec3(0.0, -1.0, 0.0)));
            shadowTransforms.push_back(glm::lookAt(position,
                position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0),
                    glm::vec3(0.0, 0.0, -1.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0),
                    glm::vec3(0.0, -1.0, 0.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0),
                    glm::vec3(0.0, -1.0, 0.0)));
            ;

            {
                auto block = matrixUBO->mapRange<MatrixBlock>(GL_MAP_WRITE_BIT);

                block->v = shadowTransforms[i];
                block->p = shadowProj;
            }

            matrixUBO->bind(GL_UNIFORM_BUFFER, 0);

            glViewport(0, 0, cache.width(), cache.height());
            glEnable(GL_DEPTH_TEST);

            cache.bind(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            GeometryRendererVisitor geometryRenderer(_program.get(), matrixUBO);
            root.accept(geometryRenderer);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
    }
}

void RSMPass::resize(int width, int height) { }

void RSMPass::deinitialize() { }

int RSMPass::lightCount() { return _lightCache.size(); }

std::string RSMPass::lightName(int id) {
    auto it = _lightCache.begin();
    std::advance(it, id);
    return it->first->name();
}

RSMFramebuffer& RSMPass::rsm(int id) {
    auto it = _lightCache.begin();
    std::advance(it, id);
    return it->second;
}
RSMFramebuffer& RSMPass::rsm(PointLightNode* lightNode) {
    return _lightCache[lightNode];
}
