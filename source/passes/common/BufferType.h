
//
// Created by voxed on 6/7/22.
//

#ifndef VX_EMBER_BUFFERTYPE_H
#define VX_EMBER_BUFFERTYPE_H

namespace vx::ember {

enum BufferType {
    NORMAL_BUFFER,
    COLOR_BUFFER,
    POSITION_BUFFER,
    DEPTH_BUFFER,
    METALLIC_ROUGHNESS_BUFFER,
    EMISSION_BUFFER
};

}

#endif // VX_EMBER_BUFFERTYPE_H
