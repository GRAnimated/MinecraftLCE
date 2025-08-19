#pragma once

#include "net/minecraft/world/level/block/Block.h"

class ThinFenceBlock : public Block {
public:
    ThinFenceBlock(const std::wstring&, const std::wstring&, Material*, bool);
};
