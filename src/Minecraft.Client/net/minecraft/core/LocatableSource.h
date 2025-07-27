#pragma once

#include "net/minecraft/core/Location.h"
#include "net/minecraft/core/Source.h"

class BlockPos;
class Level;

class LocatableSource : public Source, public Location {
public:
    ~LocatableSource() override;

    virtual Level* getWorld() = 0;
    virtual BlockPos getPos() = 0;
};
