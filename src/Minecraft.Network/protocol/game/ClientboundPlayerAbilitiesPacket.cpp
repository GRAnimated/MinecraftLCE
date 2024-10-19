#include "Minecraft.Network/protocol/game/ClientboundPlayerAbilitiesPacket.h"

#include "Minecraft.Client/multiplayer/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.World/entity/player/Abilities.h"

std::shared_ptr<Packet> ClientboundPlayerAbilitiesPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerAbilitiesPacket());
}

ClientboundPlayerAbilitiesPacket::ClientboundPlayerAbilitiesPacket() : Packet() {
    mIsInvulnerable = false;
    mIsFlying = false;
    mIsEnableFly = false;
    mIsInstabuild = false;
    mFlyingSpeed = 0.0f;
    mWalkingSpeed = 0.0f;
    mIsEnableBuild = true;
    mPlayerId = 0;
}

ClientboundPlayerAbilitiesPacket::ClientboundPlayerAbilitiesPacket(Abilities* abilities, int playerId) : Packet() {
    setInvulnerable(abilities->mIsInvulnerable);
    setFlying(abilities->mIsFlying);
    setCanFly(abilities->mIsEnableFly);
    setInstabuild(abilities->mIsInstabuild);
    setFlyingSpeed(abilities->getFlyingSpeed());
    setWalkingSpeed(abilities->getWalkingSpeed());
    setCanBuild(abilities->mIsEnableBuild);
    mPlayerId = playerId;
}

EPacketType ClientboundPlayerAbilitiesPacket::getPacketId() {
    return EPacketType::_ClientboundPlayerAbilitiesPacket;
}

void ClientboundPlayerAbilitiesPacket::read(DataInputStream* input) {
    u8 flags = input->readByte();
    setInvulnerable(flags & 0x01);
    setFlying(flags & 0x02);
    setCanFly(flags & 0x04);
    setInstabuild(flags & 0x08);
    setCanBuild(flags & 0x10);
    setFlyingSpeed(input->readFloat());
    setWalkingSpeed(input->readFloat());
    mPlayerId = input->readInt();
}

void ClientboundPlayerAbilitiesPacket::write(DataOutputStream* output) {
    u8 flags = 0;
    if (isInvulnerable())
        flags |= 0x01;
    if (isFlying())
        flags |= 0x02;
    if (canFly())
        flags |= 0x04;
    if (canInstabuild())
        flags |= 0x08;
    if (canBuild())
        flags |= 0x10;
    output->writeByte(flags);
    output->writeFloat(mFlyingSpeed);
    output->writeFloat(mWalkingSpeed);
    output->writeInt(mPlayerId);
}

void ClientboundPlayerAbilitiesPacket::handle(PacketListener* listener) {
    listener->handlePlayerAbilities(this->shared_from_this());
}

int ClientboundPlayerAbilitiesPacket::getEstimatedSize() {
    return 13;
}

bool ClientboundPlayerAbilitiesPacket::canBeInvalidated() {
    return true;
}

bool ClientboundPlayerAbilitiesPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

void ClientboundPlayerAbilitiesPacket::setInvulnerable(bool invulnerable) {
    mIsInvulnerable = invulnerable;
}

void ClientboundPlayerAbilitiesPacket::setFlying(bool flying) {
    mIsFlying = flying;
}

void ClientboundPlayerAbilitiesPacket::setCanFly(bool canFly) {
    mIsEnableFly = canFly;
}

void ClientboundPlayerAbilitiesPacket::setInstabuild(bool instabuild) {
    mIsInstabuild = instabuild;
}

void ClientboundPlayerAbilitiesPacket::setFlyingSpeed(float flyingSpeed) {
    mFlyingSpeed = flyingSpeed;
}

void ClientboundPlayerAbilitiesPacket::setWalkingSpeed(float walkingSpeed) {
    mWalkingSpeed = walkingSpeed;
}

void ClientboundPlayerAbilitiesPacket::setCanBuild(bool canBuild) {
    mIsEnableBuild = canBuild;
}

bool ClientboundPlayerAbilitiesPacket::isInvulnerable() {
    return mIsInvulnerable;
}

bool ClientboundPlayerAbilitiesPacket::isFlying() {
    return mIsFlying;
}

bool ClientboundPlayerAbilitiesPacket::canFly() {
    return mIsEnableFly;
}

bool ClientboundPlayerAbilitiesPacket::canInstabuild() {
    return mIsInstabuild;
}

bool ClientboundPlayerAbilitiesPacket::canBuild() {
    return mIsEnableBuild;
}

float ClientboundPlayerAbilitiesPacket::getFlyingSpeed() {
    return mFlyingSpeed;
}

float ClientboundPlayerAbilitiesPacket::getWalkingSpeed() {
    return mWalkingSpeed;
}

int ClientboundPlayerAbilitiesPacket::getPlayerId() {
    return mPlayerId;
}
