//
// Created by voxed on 5/20/22.
//

#include "Ember.h"
#include "SampleBase.h"
#include "passes/GeometryPass.h"
#include "visitors/nodes/CameraNode.h"
#include "Primitive.h"
#include "Mesh.h"
#include "visitors/nodes/GeometryNode.h"
#include "passes/MatrixUpdatePass.h"
#include "passes/PresentationPass.h"
#include "imgui.h"
#include <OBJ_Loader.h>

using namespace vx::ember;

class Simple : public SampleBase {
    std::unique_ptr<Ember> ember;
    std::shared_ptr<CameraNode> cam;
    std::shared_ptr<GeometryNode> geo;

    std::shared_ptr<GeometryPass> geoPass;
    std::shared_ptr<PresentationPass> presentationPass;

    void createEmber() {
        ember = std::make_unique<Ember>();
        auto muPass = std::make_shared<MatrixUpdatePass>();
        ember->addPass(muPass);
        geoPass = std::make_shared<GeometryPass>();
        ember->addPass(geoPass);
        presentationPass = std::make_shared<PresentationPass>();
        ember->addPass(presentationPass);
        ember->initialize();
    }

    void initialize() override {
        createEmber();

        std::shared_ptr<Mesh> suzanne;

        {
            using namespace objl;
            using vx::ember::Mesh;
            Loader loader;
            loader.LoadFile("assets/suzanne.obj");
            loader.LoadedMeshes[0].Vertices;

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> normals;
            std::vector<unsigned int> indices = loader.LoadedMeshes[0].Indices;

            for (const auto &v: loader.LoadedMeshes[0].Vertices) {
                vertices.emplace_back(v.Position.X, v.Position.Y, v.Position.Z);
                normals.emplace_back(v.Normal.X, v.Normal.Y, v.Normal.Z);
            }

            std::shared_ptr<Primitive> prim = std::make_shared<Primitive>(
                    vertices, normals, indices
            );

            suzanne = std::make_shared<Mesh>(std::vector<std::shared_ptr<Primitive>>{prim});
        }

        geo = std::make_shared<GeometryNode>(suzanne);

        cam = std::make_shared<CameraNode>(70.0f, 1000.0f, 0.01f);
        auto group = std::make_shared<SpatialNode>();
        group->rotate(glm::vec3(0, 0, 0.0f));
        group->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        group->addChild(geo);
        ember->root().addChild(group);

        ember->root().addChild(cam);

        cam->setActive(true);
    }

    void mainLoop() override {

        ImGui::Begin("Controls");

        const char *items[] = {"Normal Buffer", "Position Buffer", "Depth Buffer"};
        static const char *current_item = "Normal Buffer";
        if (ImGui::BeginCombo("##combo",
                              current_item)) {
            for (auto &item: items) {
                bool is_selected = (current_item ==
                                    item);
                if (ImGui::Selectable(item, is_selected)) {
                    current_item = item;
                }
            }
            ImGui::EndCombo();
        }


        if (strcmp(current_item, "Normal Buffer") == 0) {
            presentationPass->setTexture(geoPass->normalTexture());
        }
        if (strcmp(current_item, "Position Buffer") == 0) {
            presentationPass->setTexture(geoPass->positionTexture());
        }
        if (strcmp(current_item, "Depth Buffer") == 0) {
            presentationPass->setTexture(geoPass->depthTexture());
        }

        ember->render();
        geo->setPosition(glm::vec3(0.0, 0, 0.0f));
        cam->setPosition(glm::vec3(0.0, 0.0, 3.35f));
        ImGui::End();

    }

    void resize(int width, int height) override {
        ember->resize(width, height);
    }

    void deinitialize() override {
        ember->deinitialize();
    }

public:
    Simple() : SampleBase(640, 480, "Simple Sample") {}

};

int main() {
    Simple().start();
}

