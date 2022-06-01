//
// Created by voxed on 5/31/22.
//

#include "Texture.h"

void vx::ember::Texture::bind(GLuint unit) const {
    glBindTextureUnit(unit, _index);
}
