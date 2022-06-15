//
// Created by voxed on 6/13/22.
//

#include "Frustum.h"

using namespace vx::ember;

Frustum::Frustum(glm::mat4 mat) {
    for (int i = 4; i--;)
        _left[i] = mat[i][3] + mat[i][0];
    for (int i = 4; i--;)
        _right[i] = mat[i][3] - mat[i][0];
    for (int i = 4; i--;)
        _bottom[i] = mat[i][3] + mat[i][1];
    for (int i = 4; i--;)
        _top[i] = mat[i][3] - mat[i][1];
    for (int i = 4; i--;)
        _near[i] = mat[i][3] + mat[i][2];
    for (int i = 4; i--;)
        _far[i] = mat[i][3] - mat[i][2];
}

bool Frustum::intersectBox(std::array<glm::vec3, 2> box) {
    return intersectBoxPlane(_left, box) || intersectBoxPlane(_right, box) || intersectBoxPlane(_top, box)
        || intersectBoxPlane(_bottom, box) || intersectBoxPlane(_far, box) || intersectBoxPlane(_near, box);
}

bool Frustum::intersectBoxPlane(glm::vec4 plane, std::array<glm::vec3, 2> box) {
    glm::vec3 vPos;
    glm::vec3 vNeg;

    vPos.x = (plane.x >= 0) ? box[1].x : box[0].x;
    vPos.y = (plane.y >= 0) ? box[1].y : box[0].y;
    vPos.z = (plane.z >= 0) ? box[1].z : box[0].z;
    vNeg.x = (plane.x <= 0) ? box[1].x : box[0].x;
    vNeg.y = (plane.y <= 0) ? box[1].y : box[0].y;
    vNeg.z = (plane.z <= 0) ? box[1].z : box[0].z;

    return !(
        ((glm::dot(glm::vec3(plane), vPos) + plane.w) <= 0) && ((glm::dot(glm::vec3(plane), vNeg) + plane.w) <= 0));
}
