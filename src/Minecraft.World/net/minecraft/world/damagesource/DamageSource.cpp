#include "net/minecraft/world/damagesource/DamageSource.h"

#include "net/minecraft/world/damagesource/EntityDamageSource.h"
#include "net/minecraft/world/food/FoodConstants.h"

DamageSource::DamageSource(ClientboundChatPacket::EChatPacketMessage unk0,
                           ClientboundChatPacket::EChatPacketMessage unk1) {
    this->m_bypassMagic = false;
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

// name guessed
DamageSource* DamageSource::setFire() {
    m_isFireSource = true;
    return this;
}

DamageSource* DamageSource::bypassArmour() {
    m_bypassArmour = true;
    m_exhaustion = 0.0f;
    return this;
}

// name guessed
DamageSource* DamageSource::bypassMagic() {
    m_bypassMagic = true;
    m_exhaustion = 0.0f;
    return this;
}

// name guessed
DamageSource* DamageSource::bypassInvul() {
    m_bypassInvul = true;
    return this;
}

// name guessed
DamageSource* DamageSource::setProjectile() {
    m_isProjectile = true;
    return this;
}

// name guessed
DamageSource* DamageSource::setExplosion() {
    m_isExplosion = true;
    return this;
}

// name guessed
DamageSource* DamageSource::setScalesWithDifficulty() {
    m_scalesWithDifficulty = true;
    return this;
}

// name guessed
bool DamageSource::isBypassArmour() const {
    return m_bypassArmour;
}

// name guessed
bool DamageSource::isBypassMagic() const {
    return m_bypassMagic;
}

// name guessed
bool DamageSource::isMagic() const {
    return m_isMagic;
}

// name guessed
float DamageSource::getExhaustion() const {
    return m_exhaustion;
}

void DamageSource::GetBaseDamageSource() {}

DamageSource* DamageSource::CreateThorns(std::shared_ptr<Entity> entity) {
    const auto message = ClientboundChatPacket::EChatPacketMessage_PlayerWasKilledTryingToHurtSource;
    return (new EntityDamageSource(message, message, entity))->setThorns()->setMagic();
}

bool DamageSource::isBypassInvul() const {
    return this->m_bypassInvul;
}

// name guessed
bool DamageSource::isFire() const {
    return this->m_isFireSource;
}

bool DamageSource::isProjectile() const {
    return this->m_isProjectile;
}

// name guessed
bool DamageSource::isExplosion() const {
    return this->m_isExplosion;
}
