//
// Created by voxed on 5/29/22.
//

#ifndef VX_EMBER_POINTLIGHTNODE_H
#define VX_EMBER_POINTLIGHTNODE_H

#include "SpatialNode.h"
#include "gl/BufferObject.h"
#include <optional>

namespace vx::ember {

class PointLightNode : public SpatialNode {
    glm::vec3 _color = glm::vec3(1.0);
    float _intensity = 1.0;

    std::unique_ptr<BufferObject> _ubo;

public:
    explicit PointLightNode(std::string name);

    void accept(NodeVisitor& visitor) override;

    glm::vec3 color();
    void setColor(glm::vec3 color);

    [[nodiscard]] float intensity() const;
    void setIntensity(float intensity);

    BufferObject& ubo();
};

}

#endif // VX_EMBER_POINTLIGHTNODE_H
