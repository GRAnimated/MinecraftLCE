#include "net/minecraft/world/damagesource/EntityDamageSource.h"

EntityDamageSource::EntityDamageSource(ClientboundChatPacket::EChatPacketMessage unk0,
                                       ClientboundChatPacket::EChatPacketMessage unk1,
                                       std::shared_ptr<Entity> entity)
    : DamageSource(unk0, unk1) {
    this->m_entity = entity;
    this->m_isThorns = false;
}

EntityDamageSource::~EntityDamageSource() {}

std::shared_ptr<Entity> EntityDamageSource::getEntity() {
    return this->m_entity;
}

bool EntityDamageSource::scalesWithDifficulty() {
    return this->m_entity && this->m_entity->isType(eLivingEntity) && !this->m_entity->isType(ePlayer);
}

Vec3* EntityDamageSource::getSourcePosition() {
    return Vec3::newTemp(this->m_entity->m_x, this->m_entity->m_y, this->m_entity->m_z);
}

DamageSource* EntityDamageSource::copy() {
    return new EntityDamageSource(*this);
}

EntityDamageSource* EntityDamageSource::setThorns() {
    this->m_isThorns = true;
    return this;
}
