#include "net/minecraft/world/item/ShovelItem.h"

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/sounds/SoundEvents.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/material/Material.h"
#include "types.h"

arrayWithLength<Block*> ShovelItem::DIGGABLES = arrayWithLength<Block*>(12, true);

void ShovelItem::staticCtor() {
    DIGGABLES[0] = Blocks::CLAY;
    DIGGABLES[1] = Blocks::DIRT;
    DIGGABLES[2] = Blocks::FARMLAND;
    DIGGABLES[3] = Blocks::GRASS;
    DIGGABLES[4] = Blocks::GRAVEL;
    DIGGABLES[5] = Blocks::MYCELIUM;
    DIGGABLES[6] = Blocks::SAND;
    DIGGABLES[7] = Blocks::SNOW;
    DIGGABLES[8] = Blocks::SNOW_LAYER;
    DIGGABLES[9] = Blocks::SOUL_SAND;
    DIGGABLES[10] = Blocks::GRASS_PATH;
    DIGGABLES[11] = Blocks::CONCRETE_POWDER;
}

ShovelItem::ShovelItem(const Item::Tier* tier) : DiggerItem(1, -3, tier, DIGGABLES) {}

// NON_MATCHING: ifs bullshit, function is weird overall, as doing the same thing as Java does, doesn't match
// much
ActionResultType ShovelItem::useOn(std::shared_ptr<Player> player, Level* level, const BlockPos& pos,
                                   InteractionHand::EInteractionHand hand, const Direction* direction, float,
                                   float, float, bool idk) {
    not_null_ptr<ItemInstance> shovel = player->getItemInHand(hand);

    if (player->mayUseItemAt(pos.relative(direction), direction, shovel)) {
        Block* block = level->getBlockState(pos)->getBlock();
        if (Direction::DOWN != direction) {
            if (level->getBlockState(pos.above())->getMaterial() == Material::AIR) {
                if (block == Blocks::GRASS && !idk) {
                    level->playSound(player, pos, SoundEvents::SHOVEL_FLATTEN, SoundSource::BLOCKS, 1.0f,
                                     1.0f, 16.0f);
                    if (!level->mIsLocal) {
                        level->setBlock(pos, Blocks::GRASS_PATH->defaultBlockState(), 11, false);
                        shovel->hurtAndBreak(1, player);
                    }

                    return ActionResultType::SUCCESS;
                }
            } else {  // if you remove this else it's matching less, so this function probably needs complete
                      // overhaul
                return ActionResultType::PASS;
            }
        }

        return ActionResultType::PASS;
    }

    return ActionResultType::FAIL;
}

bool ShovelItem::canDestroySpecial(const BlockState* state) {
    Block* block = state->getBlock();
    return block == Blocks::SNOW_LAYER || block == Blocks::SNOW;
}
