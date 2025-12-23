#include "net/minecraft/world/entity/mob/AgableMob.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/client/particle/ParticleTypes.h"
#include "net/minecraft/network/syncher/EntityDataSerializers.h"
#include "net/minecraft/network/syncher/SynchedEntityData.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/mob/PathfinderMob.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/item/Items.h"
#include "types.h"

EntityDataAccessor<bool>* AgableMob::BABY;
EntityDataAccessor<bool>* AgableMob::ADULT;

void AgableMob::staticCtor() {
    AgableMob::BABY = SynchedEntityData::defineId(eAgableMob, ePathfinderMob,
                                                  EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
    AgableMob::ADULT = SynchedEntityData::defineId(eAgableMob, ePathfinderMob,
                                                   EntityDataSerializers::sBOOLEAN_EntityDataSerializer);
}

AgableMob::AgableMob(Level* level) : PathfinderMob(level) {
    this->mHeightRatio = 0;
    this->mForcedAgeTimer = 0;
    this->mWidthRatio = -1.0f;
    this->mAge = 0;
    this->mForcedAge = 0;
}

void AgableMob::defineSynchedData() {
    Mob::defineSynchedData();
    this->mEntityData->createDateItem(AgableMob::BABY, false);
    this->mEntityData->createDateItem(AgableMob::ADULT, false);
}

void AgableMob::setSize(float width, float height) {
    bool e = this->mWidthRatio > 0.0f;
    this->mWidthRatio = width;
    this->mHeightRatio = height;
    if (!e)
        this->internalSetSize(1.0);
}

void AgableMob::readAdditionalSaveData(CompoundTag* tag) {
    Mob::readAdditionalSaveData(tag);
    this->setAge(tag->getInt(L"Age"));
    this->mForcedAge = tag->getInt(L"ForcedAge");
}

void AgableMob::addAdditonalSaveData(CompoundTag* tag) {
    Mob::addAdditonalSaveData(tag);
    tag->putInt(L"Age", this->getAge());
    tag->putInt(L"ForcedAge", this->mForcedAge);
}

void AgableMob::onSyncedDataUpdated(const EntityDataAccessor_Base* accessor) {
    if (AgableMob::BABY->is(accessor)) {
        this->updateSize(this->isBaby());
    }
}

bool AgableMob::isBaby() {
    return this->getAge() < 0;
}

void AgableMob::aiStep() {
    Mob::aiStep();
    if (this->mLevel->mIsLocal) {
        if (this->mForcedAgeTimer > 0) {
            if (this->mForcedAgeTimer % 4 == 0) {
                this->mLevel->addParticle(
                    ParticleTypes::HAPPY_VILLAGER,
                    this->mX + (this->mRand->nextFloat() * this->mWidth * 2.0F) - this->mWidth,
                    this->mY + 0.5 + (this->mRand->nextFloat() * this->mHeight),
                    this->mZ + (this->mRand->nextFloat() * this->mWidth * 2.0F) - this->mWidth, 0.0, 0.0, 0.0,
                    arrayWithLength<int>());
            }

            --this->mForcedAgeTimer;
        }
    } else {
        int age = this->getAge();
        if (age < 0) {
            ++age;
            this->setAge(age);
            if (!age) {
                this->grewUp();
            }
        } else if (age > 0) {
            --age;
            this->setAge(age);
        }
    }
}

/*

TODO: implement SpawnEggItem then get to this!

bool AgableMob::mobInteract(const std::shared_ptr<Player>& player, InteractionHand::EInteractionHand hand) {
    not_null_ptr<ItemInstance> itemInst = player->getItemInHand(hand);
    Item* item = itemInst->getItem();
    if (item == Items::SPAWN_EGG
    }
}
*/

int AgableMob::getAge() {
    if (this->mLevel && !this->mLevel->mIsLocal) {
        return this->mAge;
    }

    if (this->mEntityData->get(ADULT)) {
        return 1;
    }

    return this->mEntityData->get(BABY) ? -1 : 0;
}

void AgableMob::ageUp(int seconds, bool forced) {
    int age = this->getAge();
    int oldAge = age;
    age += seconds * 20;
    if (age > 0) {
        if (oldAge < 0) {
            this->grewUp();
        }
        age = 0;
    }

    this->setAge(age);

    if (forced) {
        this->mForcedAge += age - oldAge;
        if (this->mForcedAgeTimer == 0) {
            this->mForcedAgeTimer = 40;
        }
    }

    if (this->getAge() == 0) {
        this->setAge(this->mForcedAge);
    }
}

void AgableMob::ageUp(int seconds) {
    this->ageUp(seconds, false);
}

void AgableMob::setAge(int age) {
    if (!this->mLevel || !this->mLevel->mIsLocal) {
        this->mEntityData->set(BABY, age < 0, true);
        this->mEntityData->set(ADULT, age > 0, true);
    }

    this->mAge = age;
    this->updateSize(this->isBaby());
}

void AgableMob::grewUp() {}

void AgableMob::updateSize(bool baby) {
    this->internalSetSize(baby ? 0.5f : 1.0f);
}

void AgableMob::internalSetSize(float scale) {
    Entity::setSize(this->mWidthRatio * scale, this->mHeightRatio * scale);
}
