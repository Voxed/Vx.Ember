//
// Created by voxed on 6/2/22.
//

#include "RSMCache.h"

using namespace vx::ember;

int RSMCache::size() { return (int)_cache.size(); }
std::string RSMCache::getName(int id) {
    auto it = _cache.begin();
    std::advance(it, id);
    return it->first->name();
}

RSMFramebuffer& RSMCache::get(PointLightNode* lightNode) { return _cache[lightNode]; }

RSMFramebuffer& RSMCache::get(int id) {
    auto it = _cache.begin();
    std::advance(it, id);
    return it->second;
}
PointLightNode* RSMCache::getLight(int id) {
    auto it = _cache.begin();
    std::advance(it, id);
    return it->first;
}
