#pragma once

#include "net/minecraft/world/entity/mob/Monster.h"

class Silverfish : public Monster {
public:
    Silverfish(Level*);

    // possibly move this down the inheritance (Monster or lower)
    not_null_ptr<ItemInstance> getItemSlot(const EquipmentSlot*) override;
    HumanoidArm* getMainArm() override;

    char fill[82];  // correct that in the future as part of this probably should go to Monster
};
