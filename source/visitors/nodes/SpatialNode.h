//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_SPATIALNODE_H
#define VX_EMBER_SPATIALNODE_H

#include "Node.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace vx::ember {

class NodeVisitor;
class WorldMatrixUpdateVisitor;
class ImGuiTreeViewVisitor;
class CameraLocatorVisitor;

class SpatialNode : public Node {
protected:
    glm::vec3 _position = glm::vec3(0.0);
    glm::quat _rotation = glm::quat(1, 0, 0, 0);
    glm::vec3 _scale = glm::vec3(1.0);
    glm::mat4 _worldMatrix = glm::mat4(1.0);
    glm::quat _worldRotation = glm::quat(1.0, 0.0, 0.0, 0.0);

public:
    explicit SpatialNode(std::string name = "SpatialNode");

    void accept(NodeVisitor& visitor) override;

    glm::vec3 position();
    void setPosition(glm::vec3 position);

    glm::vec3 scale();
    void setScale(glm::vec3 scale);

    glm::quat rotation();
    void setRotation(glm::quat rotation);
    void rotate(glm::vec3 euler);
    virtual void lookAt(glm::vec3 target);

    glm::mat4 matrix();
    glm::mat4 worldMatrix();

    friend WorldMatrixUpdateVisitor;
};

}

#endif // VX_EMBER_SPATIALNODE_H
