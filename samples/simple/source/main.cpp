//
// Created by voxed on 5/20/22.
//

#include "SampleBase.h"
#include "core/Ember.h"
#include "core/Mesh.h"
#include "core/Primitive.h"
#include "core/nodes/CameraNode.h"
#include "core/nodes/GeometryNode.h"
#include "core/nodes/PointLightNode.h"
#include "gltf/GLTFLoader.h"
#include "imgui.h"
#include "obj/OBJLoader.h"
#include "passes/geometry_pass/GeometryPass.h"
#include "passes/gizmo_pass/GizmoPass.h"
#include "passes/imgui_pass/DebugImGuiPass.h"
#include "passes/light_pass/LightPass.h"
#include "passes/matrix_update_pass/MatrixUpdatePass.h"
#include "passes/presentation_pass/PresentationPass.h"
#include "passes/rsm_pass/RSMPass.h"

using namespace vx::ember;

class Simple : public SampleBase {
    std::unique_ptr<Ember> ember;
    std::shared_ptr<CameraNode> cam;
    std::shared_ptr<GeometryNode> geo;

    std::shared_ptr<GeometryPass> geoPass;
    std::shared_ptr<RSMPass> lightPass;
    std::shared_ptr<PresentationPass> presentationPass;
    std::shared_ptr<GizmoPass> gizmoPass;
    std::shared_ptr<LightPass> realLightPass;

    glm::vec3 animation[5] = { glm::vec3(0.0, 1.0, 1.0), glm::vec3(3.0, 1.5, 0.0), glm::vec3(6.0, 4.0, 0.0),
        glm::vec3(-6.0, 4.0, 0.0), glm::vec3(-1.0, 2.0, 1.0) };
    glm::quat animation_rot[5] = { glm::quat(glm::vec3(0.0)), glm::quat(glm::vec3(0.0, 1.0, 0.0)),
        glm::quat(glm::vec3(0.0, 1.0, 0.0)), glm::quat(glm::vec3(0.0, -1.0, 0.0)), glm::quat(glm::vec3(0.0)) };
    size_t animation_length = 5;

    void createEmber() {
        ember = std::make_unique<Ember>();
        auto muPass = std::make_shared<MatrixUpdatePass>();
        ember->addPass(muPass);
        geoPass = std::make_shared<GeometryPass>();
        ember->addPass(geoPass);
        lightPass = std::make_shared<RSMPass>();
        ember->addPass(lightPass);

        gizmoPass = std::make_shared<GizmoPass>(lightPass->cache(), geoPass->depthTexture());
        ember->addPass(gizmoPass);

        realLightPass = std::make_shared<LightPass>(lightPass->cache(), geoPass->positionTexture(),
            geoPass->normalTexture(), geoPass->metallicRoughnessTexture(), geoPass->colorTexture());
        ember->addPass(realLightPass);

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
            GLTFLoader loader("assets/sponza/Sponza.gltf"); //"assets/complex.gltf");
            scene = loader.scene();
        }
        std::shared_ptr<Node> scene2;
        {
            GLTFLoader loader("assets/complex.gltf"); //"assets/complex.gltf");
            scene2 = loader.scene();
        }
        /*std::static_pointer_cast<CameraNode>(
            scene->findChild("Empty.002")[0]
                ->findChild("Camera")[0]
                ->findChild("Camera_Orientation")[0]
                ->findChild("Camera")[0])
            ->setActive(true);*/

        /*scene->findChild("Empty")[0]->addChild(
            std::make_shared<PointLightNode>("scene light"));*/

        ember->root().addChild(scene);
        // ember->root().addChild(scene2);

        geo = std::make_shared<GeometryNode>(suzanne, std::vector<std::shared_ptr<Material>>(), "suzanne");

        cam = std::make_shared<CameraNode>(Perspective { 1.57, 0.1f, 2000.0f });
        cam->setActive(true);
        auto group = std::make_shared<SpatialNode>();
        group->rotate(glm::vec3(0, 0, 0.0f));
        group->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        // group->addChild(geo);
        ember->root().addChild(group);

        ember->root().addChild(cam);

        ember->root().addChild(std::make_shared<PointLightNode>("test light"));
        ember->root().addChild(std::make_shared<PointLightNode>("test light2"));

        cam->setActive(true);
        cam->setPosition(glm::vec3(0.0, 1.0, 0.0f));
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

        const char* items[] = { "Normal Buffer", "Position Buffer", "Depth Buffer", "RSM Buffer", "Color Buffer",
            "Metallic Roughness Buffer", "Emission Buffer", "Light Buffer" };
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
        if (strcmp(current_item, "Normal Buffer") == 0 && geoPass->normalTexture()) {
            presentationPass->setTexture(*geoPass->normalTexture());
            presentationPass->setCubemap(false);
            presentationPass->setArray(false);

            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::NORMAL_BUFFER);
        }
        if (strcmp(current_item, "Position Buffer") == 0 && geoPass->positionTexture()) {
            presentationPass->setTexture(*geoPass->positionTexture());
            presentationPass->setCubemap(false);
            presentationPass->setArray(false);

            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::POSITION_BUFFER);
        }
        if (strcmp(current_item, "Depth Buffer") == 0 && geoPass->depthTexture()) {
            presentationPass->setTexture(*geoPass->depthTexture());
            presentationPass->setCubemap(false);
            presentationPass->setArray(false);

            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::DEPTH_BUFFER);
        }
        if (strcmp(current_item, "Color Buffer") == 0 && geoPass->colorTexture()) {
            presentationPass->setTexture(*geoPass->colorTexture());
            presentationPass->setCubemap(false);
            presentationPass->setArray(false);

            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::COLOR_BUFFER);
        }
        if (strcmp(current_item, "Metallic Roughness Buffer") == 0 && geoPass->metallicRoughnessTexture()) {
            presentationPass->setTexture(*geoPass->metallicRoughnessTexture());
            presentationPass->setCubemap(false);
            presentationPass->setArray(false);

            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::METALLIC_ROUGHNESS_BUFFER);
        }
        if (strcmp(current_item, "Emission Buffer") == 0 && geoPass->emissionBuffer()) {
            presentationPass->setTexture(*geoPass->emissionBuffer());
            presentationPass->setCubemap(false);
            presentationPass->setArray(false);

            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::EMISSION_BUFFER);
        }
        if (strcmp(current_item, "Light Buffer") == 0) {
            static int currentLightBuffer = 0;
            ImGui::SliderInt("Light Buffer Light", &currentLightBuffer, 0, realLightPass->lightMapCount() - 1);
            presentationPass->setTexture(*realLightPass->lightMaps());
            presentationPass->setCubemap(false);
            presentationPass->setArray(true);
            presentationPass->setElement(currentLightBuffer);
            static bool mixArray = false;
            ImGui::Checkbox("mix", &mixArray);
            presentationPass->setMixArray(mixArray);
            presentationPass->setMixArrayCount(realLightPass->lightMapCount());
            geoBuffer = true;
            gizmoPass->setBufferType(vx::ember::COLOR_BUFFER);
        }
        if (geoBuffer) {
            ImGui::Checkbox("Draw Gizmos", &drawGizmos);
            if (drawGizmos && gizmoPass->texture()) {
                presentationPass->setGizmosTexture(*gizmoPass->texture());
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
            if (currentRSM >= lightPass->cache().size()) {
                currentRSM = -1;
            }
            if (ImGui::BeginCombo("Light",
                    currentRSM == -1 ? "Select light source" : lightPass->cache().getName(currentRSM).c_str())) {
                for (int i = 0; i < lightPass->cache().size(); i++) {
                    bool is_selected = (currentRSM == i);
                    if (ImGui::Selectable(
                            (lightPass->cache().getName(i) + "##" + std::to_string(i)).c_str(), is_selected)) {
                        currentRSM = i;
                    }
                }
                ImGui::EndCombo();
            }
            if (currentRSM != -1) {
                ImGui::SliderInt("Cubemap face", &rsmFace, 0, 5);

                RSMFramebuffer& rsmCache = lightPass->cache().get(currentRSM);

                presentationPass->setCubemap(true);
                presentationPass->setArray(false);
                presentationPass->setFace(rsmFace);

                const char* items[] = {
                    /*"Normal Buffer", "Position Buffer",*/ "Depth Buffer" /*, "Color Buffer",
 "Metallic Roughness Buffer", "Emission Buffer"*/
                };
                static const char* current_item_rsm = "Depth Buffer";
                if (ImGui::BeginCombo("RSM Buffer", current_item_rsm)) {
                    for (auto& item : items) {
                        bool is_selected = (current_item_rsm == item);
                        if (ImGui::Selectable(item, is_selected)) {
                            current_item_rsm = item;
                        }
                    }
                    ImGui::EndCombo();
                }

                if (strcmp(current_item_rsm, "Normal Buffer") == 0) {
                    presentationPass->setTexture(rsmCache.normalTexture());
                }
                if (strcmp(current_item_rsm, "Position Buffer") == 0) {
                    presentationPass->setTexture(rsmCache.positionTexture());
                }
                if (strcmp(current_item_rsm, "Depth Buffer") == 0) {
                    presentationPass->setTexture(rsmCache.depthTexture());
                }
                if (strcmp(current_item_rsm, "Color Buffer") == 0) {
                    presentationPass->setTexture(rsmCache.colorTexture());
                }
                if (strcmp(current_item_rsm, "Metallic Roughness Buffer") == 0) {
                    presentationPass->setTexture(rsmCache.metallicRoughnessTexture());
                }
                if (strcmp(current_item_rsm, "Emission Buffer") == 0) {
                    presentationPass->setTexture(rsmCache.emissionTexture());
                }
            }
        }

        static float rotation;
        static float rotationX;

        /*auto empty = std::static_pointer_cast<SpatialNode>(
            ember->root().findChild("Scene")[0]->findChild("Empty.002")[0]);
*/
        ImGui::SliderFloat("Camera Rotate Y", &rotation, 0.0, 3.14 * 2.0);
        // cam->setRotation(glm::quat(glm::vec3(0)));
        // cam->rotate(glm::vec3(0, rotation, 0));

        static bool animateCamera = false;
        ImGui::Checkbox("ANIMATE CAMERA!!", &animateCamera);

        if (animateCamera) {
            double animation_time = fmod(glfwGetTime(), 1.0);

            animation_time = (cosf(animation_time * 3.14 + 3.14) + 1.0) / 2.0;

            unsigned int animation_frame = ((unsigned int)fmod(floor(glfwGetTime()), animation_length));

            cam->setPosition(glm::mix(
                animation[animation_frame], animation[(animation_frame + 1) % animation_length], animation_time));
            cam->setRotation(glm::slerp(animation_rot[animation_frame],
                animation_rot[(animation_frame + 1) % animation_length], (float)animation_time));
        } else {
            cam->setRotation({ 1.0, 0.0, 0.0, 0.0 });
        }

        cam->rotate({ 0.0, rotation, 0.0 });

        ImGui::End();

        ember->render();
    }

    void resize(int width, int height) override { ember->resize(width, height); }

    void deinitialize() override { ember->deinitialize(); }

public:
    Simple()
        : SampleBase(1280, 960, "Simple Sample") { }
};

int main() { Simple().start(); }
