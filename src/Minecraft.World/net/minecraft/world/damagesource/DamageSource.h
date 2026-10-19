#pragma once

#include "net/minecraft/world/entity/Entity.h"
#include <memory>

class EntityDamageSource;
// name guessed
class DamageSource {
public:
    static DamageSource* BYPASS_ARMOUR;  // this name is wrong
    static DamageSource* IN_FIRE;
    static DamageSource* WITHER;
    static DamageSource* STARVE;
    static DamageSource* MAGIC;
    static DamageSource* POISON;
    static DamageSource* INSTANT_MAGIC;

    static DamageSource* CreateThorns(std::shared_ptr<Entity> entity);
    static EntityDamageSource* CreateIndirectMagic(std::shared_ptr<Entity> source,
                                                   std::shared_ptr<Entity> indirectSource,
                                                   DamageSource* baseSource);

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
    DamageSource* setFire();
    DamageSource* bypassArmour();
    DamageSource* bypassMagic();
    DamageSource* bypassInvul();
    DamageSource* setProjectile();
    DamageSource* setExplosion();
    DamageSource* setScalesWithDifficulty();

    bool isBypassArmour() const;
    bool isBypassMagic() const;
    bool isBypassInvul() const;
    bool isMagic() const;
    bool isFire() const;
    bool isExplosion() const;
    bool isProjectile() const;
    float getExhaustion() const;

protected:
    bool m_bypassArmour;
    bool m_bypassInvul;
    bool m_bypassMagic;
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

static_assert(sizeof(DamageSource) == 0x20, "DamageSource Switch layout");
