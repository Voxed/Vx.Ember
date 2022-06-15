//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_CAMERANODE_H
#define VX_EMBER_CAMERANODE_H

#include "SpatialNode.h"
#include <glm/mat4x4.hpp>

namespace vx::ember {

class NodeVisitor;

struct Perspective {
    float fov;
    float near;
    float far;
};

class CameraNode : public SpatialNode {
    bool _active = false;
    Perspective _perspective;

public:
    explicit CameraNode(Perspective perspective, std::string name = "CameraNode");

    [[nodiscard]] glm::mat4 projection(float aspect) const;

    [[nodiscard]] bool active() const;

    void setActive(bool active);

    [[nodiscard]] Perspective perspective() const;

    void setPerspective(Perspective perspective);

    void accept(NodeVisitor& visitor) override;

    glm::mat4 viewMatrix();
};

}

#endif // VX_EMBER_CAMERANODE_H
