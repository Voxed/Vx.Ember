//
// Created by voxed on 6/2/22.
//

#ifndef VX_EMBER_RSMCACHE_H
#define VX_EMBER_RSMCACHE_H

#include "RSMFramebuffer.h"
#include "core/nodes/PointLightNode.h"

#include <map>

namespace vx::ember {

class RSMCache {
    std::map<PointLightNode*, RSMFramebuffer> _cache;

public:
    int size();
    std::string getName(int id);

    RSMFramebuffer& get(PointLightNode* lightNode);
    RSMFramebuffer& get(int id);
    PointLightNode* getLight(int id);
};

}

#endif // VX_EMBER_RSMCACHE_H
