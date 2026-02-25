#pragma once

#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/entity/Entity.h"
#include <memory>

class EntityDamageSource : public DamageSource {
public:
    EntityDamageSource(ClientboundChatPacket::EChatPacketMessage, ClientboundChatPacket::EChatPacketMessage,
                       std::shared_ptr<Entity> entity);
    ~EntityDamageSource() override;

    std::shared_ptr<Entity> getEntity() override;
    bool scalesWithDifficulty() override;
    std::shared_ptr<ClientboundChatPacket>
    getDeathMessagePacket(std::shared_ptr<LivingEntity> entity) override;
    Vec3* getSourcePosition() override;
    DamageSource* copy() override;

    EntityDamageSource* setThorns();

private:
    std::shared_ptr<Entity> m_entity;
    bool m_isThorns;
};
