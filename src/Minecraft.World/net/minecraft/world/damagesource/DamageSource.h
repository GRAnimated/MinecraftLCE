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
    bool m_bypassArmour;
    bool m_bypassInvul;
    bool m_field0xa;
    float m_exhaustion;
    bool m_isFireSource;
    bool m_isExplosion;
    bool m_scalesWithDifficulty;
    bool m_isMagic;
    bool m_isProjectile;
    bool m_field0x15;
    ClientboundChatPacket::EChatPacketMessage m_field0x18;
    ClientboundChatPacket::EChatPacketMessage m_field0x1c;
};
