#pragma once

#include "net/minecraft/core/Direction.h"
#include "net/minecraft/world/entity/Entity.h"
#include <memory>
class DamageSource {
public:
    static DamageSource* BYPASS_ARMOUR;  // this name is wrong
    static DamageSource* IN_FIRE;
    static DamageSource* WITHER;

    static DamageSource* CreateThorns(std::shared_ptr<Entity>);

    virtual ~DamageSource();
    virtual Direction* getDirectionEntity();
    virtual Entity* getEntity();
    virtual void scalesWithDifficulty();
    virtual void getDeathMessagePacket(std::shared_ptr<LivingEntity>);
    virtual void getSourcePosition();
    virtual void copy();
    virtual void GetBaseDamageSource();

    bool isBypassInvul() const;
    bool isFire() const;
    bool isProjectile() const;
    bool isExplosion() const;
};