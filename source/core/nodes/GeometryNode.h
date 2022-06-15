//
// Created by voxed on 5/23/22.
//

#ifndef VX_EMBER_GEOMETRYNODE_H
#define VX_EMBER_GEOMETRYNODE_H

#include "SpatialNode.h"
#include "core/Mesh.h"

namespace vx::ember {

class GeometryNode : public SpatialNode {
    std::shared_ptr<Mesh> _mesh;
    std::vector<std::shared_ptr<Material>> _materials;

public:
    explicit GeometryNode(std::shared_ptr<Mesh> mesh, std::vector<std::shared_ptr<Material>> materials,
        std::string name = "GeometryNode");

    std::shared_ptr<Mesh> mesh();

    void accept(NodeVisitor& visitor) override;

    std::shared_ptr<Material> material(unsigned int index);
    unsigned int materialCount();
    void makeMaterialUnique(int i);
};

}

#endif // VX_EMBER_GEOMETRYNODE_H
