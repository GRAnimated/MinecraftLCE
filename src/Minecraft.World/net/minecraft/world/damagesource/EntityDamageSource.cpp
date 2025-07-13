#include "net/minecraft/world/damagesource/EntityDamageSource.h"

EntityDamageSource::EntityDamageSource(ClientboundChatPacket::EChatPacketMessage unk0,
                                       ClientboundChatPacket::EChatPacketMessage unk1,
                                       std::shared_ptr<Entity> entity)
    : DamageSource(unk0, unk1) {
    this->mEntity = entity;
    this->mIsThorns = false;
}

EntityDamageSource::~EntityDamageSource() {}

std::shared_ptr<Entity> EntityDamageSource::getEntity() {
    return this->mEntity;
}

bool EntityDamageSource::scalesWithDifficulty() {
    return this->mEntity && this->mEntity->isType(eLivingEntity) && !this->mEntity->isType(ePlayer);
}

Vec3* EntityDamageSource::getSourcePosition() {
    return Vec3::newTemp(this->mEntity->mX, this->mEntity->mY, this->mEntity->mZ);
}

DamageSource* EntityDamageSource::copy() {
    return new EntityDamageSource(*this);
}

EntityDamageSource* EntityDamageSource::setThorns() {
    this->mIsThorns = true;
    return this;
}
