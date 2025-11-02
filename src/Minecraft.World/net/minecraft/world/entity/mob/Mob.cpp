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

    this->mLookControl = new LookControl(this);
    this->mMoveControl = new MoveControl(this);
    this->mJumpControl = new JumpControl(this);
    this->mBodyRotationControl = nullptr;
    this->mPathNavigation = nullptr;
    this->mSensing = new Sensing(this);

    this->mHandDropChances[0] = 0.085f;
    this->mHandDropChances[1] = 0.085f;
    this->mArmorDropChances[0] = 0.085f;
    this->mArmorDropChances[1] = 0.085f;
    this->mArmorDropChances[2] = 0.085f;
    this->mArmorDropChances[3] = 0.085f;
}

void Mob::init() {
    this->mAmbientSoundTime = 0;
    this->mXpReward = 0;
    this->dword760 = 0;
    this->mTarget.reset();
    this->mSensing = nullptr;
    this->mNonNullListIdk = NonNullList<not_null_ptr<ItemInstance>>::withSize(5, ItemInstance::EMPTY);
    this->mArrayOfFloats = arrayWithLength<float>(5, true);
    this->mArrayOfFloats[0] = 0.0f;
    this->mArrayOfFloats[1] = 0.0f;
    this->mArrayOfFloats[2] = 0.0f;
    this->mArrayOfFloats[3] = 0.0f;
    this->mArrayOfFloats[4] = 0.0f;
    this->mCanPickUpLoot = false;
    this->mPersistenceRequired = false;
    this->mCensoredString = std::shared_ptr<CensoredString>(new CensoredString());
    this->mLootTable = nullptr;
    this->mLootTableSeed = 0;
    this->mHandItems = NonNullList<not_null_ptr<ItemInstance>>::withSize(2, ItemInstance::EMPTY);
    this->mArmorItems = NonNullList<not_null_ptr<ItemInstance>>::withSize(4, ItemInstance::EMPTY);
    this->mLeashInfoTag = nullptr;
    this->mLeashed = false;
    this->field_e8 = this->field_e8 | 2;
}
