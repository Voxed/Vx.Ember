//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_CAMERANODE_H
#define VX_EMBER_CAMERANODE_H

#include "SpatialNode.h"
#include "StructStringBuilder.h"
#include <glm/mat4x4.hpp>

namespace vx::ember {

    class NodeVisitor;

    class CameraNode : public SpatialNode {
        bool _active = false;
        float _fov;
        float _far;
        float _near;

    public:
        CameraNode(float fov, float far, float near, std::string name = "CameraNode");

        [[nodiscard]] bool active() const;
        [[nodiscard]] glm::mat4 projection(float aspect) const;

        void setActive(bool active);

        void accept(NodeVisitor &visitor) override;

        explicit operator std::string() const {
            return StructStringBuilder("CameraNode")
                    .addField("active", _active)
                    .build();
        }

        friend ImGuiTreeViewVisitor;
    };

}

#endif //VX_EMBER_CAMERANODE_H
