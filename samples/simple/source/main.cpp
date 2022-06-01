//
// Created by voxed on 5/20/22.
//

#include "Ember.h"
#include "Mesh.h"
#include "Primitive.h"
#include "SampleBase.h"
#include "gltf/GLTFLoader.h"
#include "imgui.h"
#include "obj/OBJLoader.h"
#include "passes/DebugImGuiPass.h"
#include "passes/GeometryPass.h"
#include "passes/GizmoPass.h"
#include "passes/MatrixUpdatePass.h"
#include "passes/PresentationPass.h"
#include "passes/RSMPass.h"
#include "visitors/nodes/CameraNode.h"
#include "visitors/nodes/GeometryNode.h"
#include "visitors/nodes/PointLightNode.h"

using namespace vx::ember;

class Simple : public SampleBase {
    std::unique_ptr<Ember> ember;
    std::shared_ptr<CameraNode> cam;
    std::shared_ptr<GeometryNode> geo;

    std::shared_ptr<GeometryPass> geoPass;
    std::shared_ptr<RSMPass> lightPass;
    std::shared_ptr<PresentationPass> presentationPass;
    std::shared_ptr<GizmoPass> gizmoPass;

    void createEmber() {
        ember = std::make_unique<Ember>();
        auto muPass = std::make_shared<MatrixUpdatePass>();
        ember->addPass(muPass);
        geoPass = std::make_shared<GeometryPass>();
        ember->addPass(geoPass);
        lightPass = std::make_shared<RSMPass>();
        ember->addPass(lightPass);

        gizmoPass = std::make_shared<GizmoPass>(lightPass, geoPass);
        ember->addPass(gizmoPass);

        presentationPass = std::make_shared<PresentationPass>();
        ember->addPass(presentationPass);

        ember->addPass(std::make_shared<DebugImGuiPass>());
        ember->initialize();
    }

    void initialize() override {
        createEmber();

        std::shared_ptr<Mesh> suzanne;

        suzanne = OBJLoader("assets/suzanne.obj").mesh();

        std::shared_ptr<Node> scene;
        {
            GLTFLoader loader("assets/complex.gltf");
            scene = loader.scene();
        }
        std::static_pointer_cast<CameraNode>(
            scene->findChild("Empty.002")[0]
                ->findChild("Camera")[0]
                ->findChild("Camera_Orientation")[0]
                ->findChild("Camera")[0])
            ->setActive(true);

        // scene->findChild("Empty")[0]->addChild(
        //     std::make_shared<PointLightNode>("scene light"));

        ember->root().addChild(scene);

        geo = std::make_shared<GeometryNode>(suzanne, "suzanne");

        cam = std::make_shared<CameraNode>(
            Perspective { 1.57, 0.01f, 1000.0f });
        auto group = std::make_shared<SpatialNode>();
        group->rotate(glm::vec3(0, 0, 0.0f));
        group->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        // group->addChild(geo);
        ember->root().addChild(group);

        ember->root().addChild(cam);

        ember->root().addChild(std::make_shared<PointLightNode>("test light"));

        cam->setActive(false);
        cam->setPosition(glm::vec3(0.0, 0.0, 3.35f));
    }

    void mainLoop() override {

        ImGui::Begin("Controls");

        static double previousTime = glfwGetTime();
        static int frameCount = 0;
        static int fps = 0;

        static bool drawGizmos = true;

        // Measure speed
        double currentTime = glfwGetTime();
        frameCount++;
        // If a second has passed.
        if (currentTime - previousTime >= 1.0) {
            // Display the frame count here any way you want.
            fps = frameCount;
            frameCount = 0;
            previousTime = currentTime;
        }

        ImGui::Text("%i", fps);

        const char* items[] = { "Normal Buffer", "Position Buffer",
            "Depth Buffer", "RSM Buffer" };
        static const char* current_item = "Normal Buffer";
        if (ImGui::BeginCombo("Present", current_item)) {
            for (auto& item : items) {
                bool is_selected = (current_item == item);
                if (ImGui::Selectable(item, is_selected)) {
                    current_item = item;
                }
            }
            ImGui::EndCombo();
        }

        bool geoBuffer = false;
        if (strcmp(current_item, "Normal Buffer") == 0) {
            presentationPass->setTexture(geoPass->normalTexture());
            presentationPass->setCubemap(false);
            geoBuffer = true;
        }
        if (strcmp(current_item, "Position Buffer") == 0) {
            presentationPass->setTexture(geoPass->positionTexture());
            presentationPass->setCubemap(false);
            geoBuffer = true;
        }
        if (strcmp(current_item, "Depth Buffer") == 0) {
            presentationPass->setTexture(geoPass->depthTexture());
            presentationPass->setCubemap(false);
            geoBuffer = true;
        }
        if (geoBuffer) {
            ImGui::Checkbox("Draw Gizmos", &drawGizmos);
            if (drawGizmos) {
                presentationPass->setGizmosTexture(gizmoPass->texture());
                presentationPass->setGizmos(true);
            } else {
                presentationPass->setGizmos(false);
            }
        } else {
            presentationPass->setGizmos(false);
        }
        if (strcmp(current_item, "RSM Buffer") == 0) {
            static int currentRSM = -1;
            static int rsmFace = 0;
            if (currentRSM >= lightPass->lightCount()) {
                currentRSM = -1;
            }
            if (ImGui::BeginCombo("Light",
                    currentRSM == -1
                        ? "Select light source"
                        : lightPass->lightName(currentRSM).c_str())) {
                for (int i = 0; i < lightPass->lightCount(); i++) {
                    bool is_selected = (currentRSM == i);
                    if (ImGui::Selectable(
                            (lightPass->lightName(i) + "##" + std::to_string(i))
                                .c_str(),
                            is_selected)) {
                        currentRSM = i;
                    }
                }
                ImGui::EndCombo();
            }
            if (currentRSM != -1) {
                ImGui::SliderInt("Cubemap face", &rsmFace, 0, 5);

                RSMFramebuffer& fb = lightPass->rsm(currentRSM);

                presentationPass->setTexture(fb.normalTexture()->_index);
                presentationPass->setCubemap(true);
                presentationPass->setFace(rsmFace);
            }
        }

        ImGui::End();

        auto empty = std::static_pointer_cast<SpatialNode>(
            ember->root().findChild("Scene")[0]->findChild("Empty.002")[0]);
        empty->setRotation(glm::quat(glm::vec3(0, glfwGetTime(), 0)));

        ember->render();
    }

    void resize(int width, int height) override {
        ember->resize(width, height);
    }

    void deinitialize() override { ember->deinitialize(); }

public:
    Simple()
        : SampleBase(1280, 960, "Simple Sample") { }
};

int main() { Simple().start(); }
