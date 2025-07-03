#pragma once

#include "types.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/entity/projectile/Arrow.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include <memory>

class TippableArrow : public Arrow {
public:
    TippableArrow(Level*, std::shared_ptr<LivingEntity>);

    void setEffectsFromItem(const not_null_ptr<ItemInstance>&);
};
