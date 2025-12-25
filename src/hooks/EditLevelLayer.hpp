#pragma once
#include <Geode/modify/EditLevelLayer.hpp>

class $modify(HookedEditLevelLayer, EditLevelLayer) {
    bool init(GJGameLevel* level);
};
