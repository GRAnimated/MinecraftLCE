#include "net/minecraft/world/item/DebugFourjItem.h"

#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/mob/Mob.h"
#include "net/minecraft/world/entity/player/Player.h"
#include <memory>

DebugFourjItem::DebugFourjItem() {}

bool DebugFourjItem::interactEnemy(not_null_ptr<ItemInstance> item, std::shared_ptr<Player> player,
                                   std::shared_ptr<LivingEntity> enemy,
                                   InteractionHand::EInteractionHand hand) {
    if (player->m_level->m_isLocal)
        return false;

    if (!enemy->isType(eMob))
        return false;

    std::shared_ptr<Mob> mob = std::dynamic_pointer_cast<Mob>(enemy);
    mob->setPersistenceRequired(!mob->isPersistenceRequired());
    return true;
}
