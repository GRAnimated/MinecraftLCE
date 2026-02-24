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
    this->m_heightRatio = 0;
    this->m_forcedAgeTimer = 0;
    this->m_widthRatio = -1.0f;
    this->m_age = 0;
    this->m_forcedAge = 0;
}

void AgableMob::defineSynchedData() {
    Mob::defineSynchedData();
    this->m_entityData->createDateItem(AgableMob::BABY, false);
    this->m_entityData->createDateItem(AgableMob::ADULT, false);
}

void AgableMob::setSize(float width, float height) {
    bool e = this->m_widthRatio > 0.0f;
    this->m_widthRatio = width;
    this->m_heightRatio = height;
    if (!e)
        this->internalSetSize(1.0);
}

void AgableMob::readAdditionalSaveData(CompoundTag* tag) {
    Mob::readAdditionalSaveData(tag);
    this->setAge(tag->getInt(L"Age"));
    this->m_forcedAge = tag->getInt(L"ForcedAge");
}

void AgableMob::addAdditonalSaveData(CompoundTag* tag) {
    Mob::addAdditonalSaveData(tag);
    tag->putInt(L"Age", this->getAge());
    tag->putInt(L"ForcedAge", this->m_forcedAge);
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
    if (this->m_level->m_isLocal) {
        if (this->m_forcedAgeTimer > 0) {
            if (this->m_forcedAgeTimer % 4 == 0) {
                this->m_level->addParticle(
                    ParticleTypes::HAPPY_VILLAGER,
                    this->m_x + (this->m_rand->nextFloat() * this->m_width * 2.0F) - this->m_width,
                    this->m_y + 0.5 + (this->m_rand->nextFloat() * this->m_height),
                    this->m_z + (this->m_rand->nextFloat() * this->m_width * 2.0F) - this->m_width, 0.0, 0.0,
                    0.0, arrayWithLength<int>());
            }

            --this->m_forcedAgeTimer;
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
    if (this->m_level && !this->m_level->m_isLocal) {
        return this->m_age;
    }

    if (this->m_entityData->get(ADULT)) {
        return 1;
    }

    return this->m_entityData->get(BABY) ? -1 : 0;
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
        this->m_forcedAge += age - oldAge;
        if (this->m_forcedAgeTimer == 0) {
            this->m_forcedAgeTimer = 40;
        }
    }

    if (this->getAge() == 0) {
        this->setAge(this->m_forcedAge);
    }
}

void AgableMob::ageUp(int seconds) {
    this->ageUp(seconds, false);
}

void AgableMob::setAge(int age) {
    if (!this->m_level || !this->m_level->m_isLocal) {
        this->m_entityData->set(BABY, age < 0, true);
        this->m_entityData->set(ADULT, age > 0, true);
    }

    this->m_age = age;
    this->updateSize(this->isBaby());
}

void AgableMob::grewUp() {}

void AgableMob::updateSize(bool baby) {
    this->internalSetSize(baby ? 0.5f : 1.0f);
}

void AgableMob::internalSetSize(float scale) {
    Entity::setSize(this->m_widthRatio * scale, this->m_heightRatio * scale);
}
