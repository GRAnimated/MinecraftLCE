#pragma once

#include "net/minecraft/world/level/levelgen/feature/Feature.h"
#include <string>

class MonsterRoomFeature : public Feature {
public:
    MonsterRoomFeature();

    bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    std::wstring randomEntityId(Random&);
};
