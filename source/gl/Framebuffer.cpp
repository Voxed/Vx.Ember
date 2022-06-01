//
// Created by voxed on 5/31/22.
//

#include "Framebuffer.h"
vx::ember::Framebuffer::Framebuffer() { glCreateFramebuffers(1, &_index); }
