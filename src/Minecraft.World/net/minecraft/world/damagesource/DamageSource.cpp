#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/food/FoodConstants.h"

DamageSource::DamageSource(ClientboundChatPacket::EChatPacketMessage unk0,
                           ClientboundChatPacket::EChatPacketMessage unk1) {
    this->m_field0xa = false;
    this->m_bypassInvul = false;
    this->m_bypassArmour = false;
    this->m_exhaustion = FoodConstants::ExhaustionAttack();
    this->m_isFireSource = false;
    this->m_isExplosion = false;
    this->m_scalesWithDifficulty = false;
    this->m_isMagic = false;
    this->m_isProjectile = false;
    this->m_field0x15 = false;
    this->m_field0x18 = unk0;
    this->m_field0x1c = unk1;
}

std::shared_ptr<Entity> DamageSource::getDirectEntity() {
    return this->getEntity();
}

std::shared_ptr<Entity> DamageSource::getEntity() {
    return nullptr;
}

bool DamageSource::scalesWithDifficulty() {
    return this->m_scalesWithDifficulty;
}

Vec3* DamageSource::getSourcePosition() {
    return nullptr;
}

DamageSource* DamageSource::copy() {
    return new DamageSource(*this);
}

DamageSource* DamageSource::setMagic() {
    this->m_isMagic = true;
    return this;
}

bool DamageSource::isBypassInvul() const {
    return this->m_bypassInvul;
}

bool DamageSource::isFire() const {
    return this->m_isFireSource;
}

bool DamageSource::isProjectile() const {
    return this->m_isProjectile;
}

bool DamageSource::isExplosion() const {
    return this->m_isExplosion;
}
