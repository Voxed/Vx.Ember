//
// Created by voxed on 5/29/22.
//

#include "RSMPass.h"

#include "core/nodes/Node.h"
#include "core/nodes/PointLightNode.h"
#include "passes/common/visitors/GeometryRendererVisitor.h"
#include "passes/common/visitors/LightLocatorVisitor.h"

#include <fstream>
#include <ranges>

using namespace vx::ember;

void RSMPass::initialize() {
    printf("INITIALIZING GEO PASS\n");

    std::ifstream vertexShaderStream("assets/rsl_shader.vert");
    std::string vertexShaderSource(
        (std::istreambuf_iterator<char>(vertexShaderStream)), std::istreambuf_iterator<char>());

    std::ifstream fragmentShaderStream("assets/rsl_shader.frag");
    std::string fragmentShaderSource(
        (std::istreambuf_iterator<char>(fragmentShaderStream)), std::istreambuf_iterator<char>());

    auto vertexShader = Shader::create("rsm shader", GL_VERTEX_SHADER, vertexShaderSource);
    auto fragmentShader = Shader::create("rsm shader", GL_FRAGMENT_SHADER, fragmentShaderSource);
    _program = Program::create({ vertexShader.get(), fragmentShader.get() });

    matrixUBO = BufferObject::create<MatrixBlock>(GL_MAP_WRITE_BIT);
}

void RSMPass::render(Node& root) {
    LightLocatorVisitor lightLocatorVisitor;
    root.accept(lightLocatorVisitor);
    std::vector<PointLightNode*> pointLights = lightLocatorVisitor.lights();

    for (auto& l : pointLights) {
        RSMFramebuffer& cache = _cache.get(l);

        for (int i = 0; i < 6; i++) {
            glm::vec3 position = (l->worldMatrix() * l->matrix() * glm::vec4(0.0, 0.0, 0.0, 1.0));

            float aspect = (float)cache.width() / (float)cache.height();
            float near = 0.01f;
            float far = 10.0f;
            glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, far);

            std::vector<glm::mat4> shadowTransforms;
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
            shadowTransforms.push_back(
                glm::lookAt(position, position + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

            {
                auto block = matrixUBO->mapRange<MatrixBlock>(GL_MAP_WRITE_BIT);

                block->v = shadowTransforms[i];
                block->p = shadowProj;
            }

            matrixUBO->bind(GL_UNIFORM_BUFFER, 0);

            _program->setUniform(1, position);

            glViewport(0, 0, cache.width(), cache.height());
            glEnable(GL_DEPTH_TEST);

            cache.bind(i);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            GeometryRendererVisitor geometryRenderer(shadowProj * shadowTransforms[i], _program.get());
            root.accept(geometryRenderer);
            
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            cache.depthTexture().generateMipmaps();
        }
    }
}

void RSMPass::resize(int width, int height) { }

void RSMPass::deinitialize() { }

RSMCache& RSMPass::cache() { return _cache; }
