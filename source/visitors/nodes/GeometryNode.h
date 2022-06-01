//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_GEOMETRYNODE_H
#define VX_EMBER_GEOMETRYNODE_H

#include "Mesh.h"
#include "SpatialNode.h"
#include "StructStringBuilder.h"

namespace vx::ember {

class GeometryNode : public SpatialNode {
    std::shared_ptr<Mesh> _mesh;

public:
    explicit GeometryNode(
        std::shared_ptr<Mesh> mesh, std::string name = "GeometryNode");

    std::shared_ptr<Mesh> mesh();

    void accept(NodeVisitor& visitor) override;
};

}

#endif // VX_EMBER_GEOMETRYNODE_H
