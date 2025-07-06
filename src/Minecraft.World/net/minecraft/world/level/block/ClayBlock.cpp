#include "net/minecraft/world/level/block/ClayBlock.h"

#include "net/minecraft/world/item/Items.h"
#include "net/minecraft/world/level/material/Material.h"

ClayBlock::ClayBlock() : Block(Material::CLAY) {
    DerivedInit();
}

Item* ClayBlock::getResource(const BlockState* blockState, Random*, int) {
    return Items::CLAY_BALL;
}

int ClayBlock::getResourceCount(Random*) {
    return 4;
}
