//
// Created by voxed on 5/20/22.
//

#ifndef VX_EMBER_PASS_H
#define VX_EMBER_PASS_H

namespace vx::ember {

    class Pass {
    public:
        virtual void initialize() = 0;

        virtual void render() = 0;
    };

}

#endif //VX_EMBER_PASS_H
