#pragma once

#include "net/minecraft/world/level/block/Block.h"

class FenceBlock : public Block {
public:
    FenceBlock(const std::wstring& type, Material* material);
    FenceBlock(const std::wstring& type, Material* material, const MaterialColor* color);
};
