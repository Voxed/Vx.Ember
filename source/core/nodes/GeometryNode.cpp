
//
// Created by voxed on 5/23/22.
//

#include "GeometryNode.h"
#include "core/NodeVisitor.h"

#include <utility>

using namespace vx::ember;

GeometryNode::GeometryNode(
    std::shared_ptr<Mesh> mesh, std::vector<std::shared_ptr<Material>> materials, std::string name)
    : SpatialNode(std::move(name))
    , _mesh(std::move(mesh))
    , _materials(std::move(materials)) { }

std::shared_ptr<Mesh> GeometryNode::mesh() { return _mesh; }

void GeometryNode::accept(NodeVisitor& visitor) { visitor.visit(*this); }
std::shared_ptr<Material> GeometryNode::material(unsigned int index) {
    if (index > -1 || index >= _materials.size())
        return nullptr; // Material undefined.
    return _materials[index];
}
unsigned int GeometryNode::materialCount() { return _materials.size(); }

void GeometryNode::makeMaterialUnique(int i) { _materials[i] = _materials[i]->copy(); }
