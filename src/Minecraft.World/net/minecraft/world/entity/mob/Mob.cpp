#include "net/minecraft/world/entity/mob/Mob.h"

#include "NX/Platform.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/CensoredString.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/Level.h"
#include "types.h"
#include <memory>

#include "net/minecraft/world/entity/ai/control/JumpControl.h"
#include "net/minecraft/world/entity/ai/control/LookControl.h"
#include "net/minecraft/world/entity/ai/control/MoveControl.h"
#include "net/minecraft/world/entity/ai/sensing/Sensing.h"

Mob::Mob(Level* level) : LivingEntity(level) {
    MemSect(57);
    this->init();
    MemSect(0);

    MemSect(58);
    this->registerAttributes();
    MemSect(0);

    this->m_lookControl = new LookControl(this);
    this->m_moveControl = new MoveControl(this);
    this->m_jumpControl = new JumpControl(this);
    this->m_bodyRotationControl = nullptr;
    this->m_pathNavigation = nullptr;
    this->m_sensing = new Sensing(this);

    this->m_handDropChances[0] = 0.085f;
    this->m_handDropChances[1] = 0.085f;
    this->m_armorDropChances[0] = 0.085f;
    this->m_armorDropChances[1] = 0.085f;
    this->m_armorDropChances[2] = 0.085f;
    this->m_armorDropChances[3] = 0.085f;
}

void Mob::init() {
    this->m_ambientSoundTime = 0;
    this->m_xpReward = 0;
    this->m_dword760 = 0;
    this->m_target.reset();
    this->m_sensing = nullptr;
    this->m_nonNullListIdk = NonNullList<not_null_ptr<ItemInstance>>::withSize(5, ItemInstance::EMPTY);
    this->m_arrayOfFloats = arrayWithLength<float>(5, true);
    this->m_arrayOfFloats[0] = 0.0f;
    this->m_arrayOfFloats[1] = 0.0f;
    this->m_arrayOfFloats[2] = 0.0f;
    this->m_arrayOfFloats[3] = 0.0f;
    this->m_arrayOfFloats[4] = 0.0f;
    this->m_canPickUpLoot = false;
    this->m_persistenceRequired = false;
    this->m_censoredString = std::shared_ptr<CensoredString>(new CensoredString());
    this->m_lootTable = nullptr;
    this->m_lootTableSeed = 0;
    this->m_handItems = NonNullList<not_null_ptr<ItemInstance>>::withSize(2, ItemInstance::EMPTY);
    this->m_armorItems = NonNullList<not_null_ptr<ItemInstance>>::withSize(4, ItemInstance::EMPTY);
    this->m_leashInfoTag = nullptr;
    this->m_leashed = false;
    this->m_fieldE8 = this->m_fieldE8 | 2;
}
