//
// Created by voxed on 6/13/22.
//

#ifndef VX_EMBER_FRUSTUM_H
#define VX_EMBER_FRUSTUM_H

#include <array>
#include <glm/ext.hpp>

namespace vx::ember {

class Frustum {

    glm::vec4 _left;
    glm::vec4 _right;
    glm::vec4 _bottom;
    glm::vec4 _top;
    glm::vec4 _near;
    glm::vec4 _far;

    static bool intersectBoxPlane(glm::vec4 plane, std::array<glm::vec3, 2> box);

public:
    Frustum(glm::mat4 mat);

    bool intersectBox(std::array<glm::vec3, 2> box);
};

}

#endif // VX_EMBER_FRUSTUM_H
