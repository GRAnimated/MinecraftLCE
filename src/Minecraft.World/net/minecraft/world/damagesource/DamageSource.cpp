#include "net/minecraft/world/damagesource/DamageSource.h"
#include "net/minecraft/world/food/FoodConstants.h"

DamageSource::DamageSource(ClientboundChatPacket::EChatPacketMessage unk0,
                           ClientboundChatPacket::EChatPacketMessage unk1) {
    this->field_0xa = false;
    this->mBypassInvul = false;
    this->mBypassArmour = false;
    this->mExhaustion = FoodConstants::ExhaustionAttack();
    this->mIsFireSource = false;
    this->mIsExplosion = false;
    this->mScalesWithDifficulty = false;
    this->mIsThorns = false;
    this->mIsProjectile = false;
    this->field_0x15 = false;
    this->field_0x18 = unk0;
    this->field_0x1a = unk1;
}
std::shared_ptr<Entity> DamageSource::getDirectEntity() {
    return this->getEntity();
}
std::shared_ptr<Entity> DamageSource::getEntity() {
    return nullptr;
}
bool DamageSource::scalesWithDifficulty() {
    return this->mScalesWithDifficulty;
}
Vec3* DamageSource::getSourcePosition() {
    return nullptr;
}
// NON_MATCHING | Score: 10
// stop whining about std::shared_ptr<Entity> mEntity offset.
// also why is target using 'orr', but current is using 'mov'??
DamageSource* DamageSource::copy() {
    return new DamageSource(*this);
}
DamageSource* DamageSource::setMagic() {
    this->mIsMagic = true;
    return this;
}
bool DamageSource::isBypassInvul() const {
    return this->mBypassInvul;
}
bool DamageSource::isFire() const {
    return this->mIsFireSource;
}
bool DamageSource::isProjectile() const {
    return this->mIsProjectile;
}
bool DamageSource::isExplosion() const {
    return this->mIsExplosion;
}
