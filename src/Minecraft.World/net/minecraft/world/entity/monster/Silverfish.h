#pragma once

#include "net/minecraft/world/entity/mob/Monster.h"

class Silverfish : public Monster {
public:
    Silverfish(Level*);

    // possibly move this down the inheritance (Monster or lower)
    void setItemSlot(const EquipmentSlot*, not_null_ptr<ItemInstance>) override;
    not_null_ptr<ItemInstance> getItemSlot(const EquipmentSlot*) override;
    HumanoidArm* getMainArm() override;

    char m_fill[0x24];  // correct that in the future as part of this probably should go to Monster
};
