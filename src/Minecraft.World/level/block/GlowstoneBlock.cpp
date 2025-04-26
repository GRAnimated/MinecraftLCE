#include "Minecraft.World/level/block/GlowstoneBlock.h"

#include "Minecraft.World/item/Items.h"
#include "Minecraft.World/level/material/MaterialColor.h"
#include "Minecraft.Util/Mth.h"

Glowstoneblock::Glowstoneblock(Material* material) : Block(material) {
    DerivedInit();
}

MaterialColor* Glowstoneblock::getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                           const BlockPos& pos) {
    return MaterialColor::SAND;
}

int Glowstoneblock::getResourceCount(Random* random) {
    return random->nextInt(3) + 2;
}

Item* Glowstoneblock::getResource(const BlockState* blockState, Random*, int) {
    return Items::GLOWSTONE_DUST;
}

int Glowstoneblock::getResourceCountForLootBonus(int offset, Random* random) {
    int count = getResourceCount(random);
    return Mth::clamp(random->nextInt(offset + 1) + count, 1, 4);
}
