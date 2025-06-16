#include "Minecraft.World/eINSTANCEOF.h"
#include "Minecraft.World/entity/mob/Mob.h"
#include "Minecraft.World/entity/player/Player.h"
#include "Minecraft.World/item/DebugFourjItem.h"
#include <memory>

DebugFourjItem::DebugFourjItem() {}

DebugFourjItem::~DebugFourjItem() {}

bool DebugFourjItem::interactEnemy(not_null_ptr<ItemInstance> item, std::shared_ptr<Player> player,
                                   std::shared_ptr<LivingEntity> enemy,
                                   InteractionHand::EInteractionHand hand) {
    if (player->mLevel->mIsLocal)
        return false;

    if (!enemy->isType(eMob))
        return false;

    std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(enemy);
    mob->setPersistenceRequired(!mob->isPersistenceRequired());
    return true;
}