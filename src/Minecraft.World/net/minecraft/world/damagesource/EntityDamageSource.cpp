//
// Created by danil on 13.07.2025.
//

#include "EntityDamageSource.h"

// there's some wild shit going on with std::shared_ptr<Entity> mEntity
// it's getting referenced by 0x28 instead of 0x20
// i already tried using `unsigned short` for `EChatPacketMessage` enum, it fixes EntityDamageSource, but then
// it breaks DamageSource constructor
// i wish i knew why...

// NON_MATCHING | Score: 25 (lower is better)
// mEntity is located at 0x28 instead of 0x20, read above
EntityDamageSource::EntityDamageSource(ClientboundChatPacket::EChatPacketMessage unk0,
                                       ClientboundChatPacket::EChatPacketMessage unk1,
                                       std::shared_ptr<Entity> entity)
    : DamageSource(unk0, unk1) {
    this->mEntity = entity;
    this->field_0x30 = false;
}

// NON_MATCHING | Score: 10 (lower is better)
// mEntity is located at 0x28 instead of 0x20, read above
EntityDamageSource::~EntityDamageSource() {}

// NON_MATCHING | Score: 15 (lower is better)
// mEntity is located at 0x28 instead of 0x20, read above
std::shared_ptr<Entity> EntityDamageSource::getEntity() {
    return this->mEntity;
}

// NON_MATCHING | Score: 10 (lower is better)
// mEntity is located at 0x28 instead of 0x20, read above
bool EntityDamageSource::scalesWithDifficulty() {
    return this->mEntity && this->mEntity->isType(eLivingEntity) && !this->mEntity->isType(ePlayer);
}
// NON_MATCHING | Score: 10 (lower is better)
// mEntity is located at 0x28 instead of 0x20 and Vec3::newTemp is at wrong address
Vec3* EntityDamageSource::getSourcePosition() {
    return Vec3::newTemp(this->mEntity->mX, this->mEntity->mY, this->mEntity->mZ);
}
// NON_MATCHING | Score: 5 (lower is better)
// continue pulling 2 extra bytes offset out of your ass
DamageSource* EntityDamageSource::copy() {
    return new EntityDamageSource(*this);
}

EntityDamageSource* EntityDamageSource::setThorns() {
    this->mIsThorns = true;
    return this;
}
