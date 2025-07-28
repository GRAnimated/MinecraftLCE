#pragma once

#include "net/minecraft/core/BlockPos.h"

class MutableBlockPos : public BlockPos {
public:
    MutableBlockPos(int, int, int);
    MutableBlockPos(const BlockPos&);

    void setX(int);
    void setY(int);
    void setZ(int);

    MutableBlockPos* set(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
        return this;
    }

    void set(const BlockPos&);
};
