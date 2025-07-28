#pragma once

#include "net/minecraft/world/entity/Entity.h"
#include <memory>

class EntityDamageSource;
class DamageSource {
public:
    static DamageSource* BYPASS_ARMOUR;  // this name is wrong
    static DamageSource* IN_FIRE;
    static DamageSource* WITHER;

    static DamageSource* CreateThorns(std::shared_ptr<Entity> entity);

    DamageSource(ClientboundChatPacket::EChatPacketMessage, ClientboundChatPacket::EChatPacketMessage);
    virtual ~DamageSource() = default;

    virtual std::shared_ptr<Entity> getDirectEntity();
    virtual std::shared_ptr<Entity> getEntity();
    virtual bool scalesWithDifficulty();
    virtual std::shared_ptr<ClientboundChatPacket>
    getDeathMessagePacket(std::shared_ptr<LivingEntity> entity);
    virtual Vec3* getSourcePosition();
    virtual DamageSource* copy();
    virtual void GetBaseDamageSource();

    DamageSource* setMagic();

    bool isBypassInvul() const;
    bool isFire() const;
    bool isExplosion() const;
    bool isProjectile() const;

protected:
    bool mBypassArmour;
    bool mBypassInvul;
    bool field_0xa;
    float mExhaustion;
    bool mIsFireSource;
    bool mIsExplosion;
    bool mScalesWithDifficulty;
    bool mIsMagic;
    bool mIsProjectile;
    bool field_0x15;
    ClientboundChatPacket::EChatPacketMessage field_0x18;
    ClientboundChatPacket::EChatPacketMessage field_0x1c;
};
