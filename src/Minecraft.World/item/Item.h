#pragma once
#include <Minecraft.World/level/block/Block.h>

class Item {
    public:
    int getId();
    bool canBeDepleted();
    static Item* byId(int id);
    static void registerBlock(Block* block);
};