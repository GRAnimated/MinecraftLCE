#pragma once

#include "net/minecraft/world/entity/mob/PathfinderMob.h"
#include <memory>

class AgableMob : public PathfinderMob {
public:
    static EntityDataAccessor<bool>* BABY;
    static EntityDataAccessor<bool>* ADULT;  // why this adult shit

    static void staticCtor();

    AgableMob(Level*);

    void defineSynchedData() override;
    void setSize(float, float) override;
    void readAdditionalSaveData(CompoundTag*) override;
    void addAdditonalSaveData(CompoundTag*) override;
    void onSyncedDataUpdated(const EntityDataAccessor_Base*) override;
    bool isBaby() override;
    void aiStep() override;
    bool mobInteract(const std::shared_ptr<Player>&, InteractionHand::EInteractionHand) override;
    virtual std::shared_ptr<Entity> createChild() = 0;
    virtual int getAge();
    virtual void ageUp(int, bool);
    virtual void ageUp(int);
    virtual void setAge(int);
    virtual void grewUp();
    virtual void updateSize(bool);

    void internalSetSize(float scale);

    int m_age;
    int m_forcedAge;
    int m_forcedAgeTimer;
    float m_widthRatio;
    float m_heightRatio;
};
