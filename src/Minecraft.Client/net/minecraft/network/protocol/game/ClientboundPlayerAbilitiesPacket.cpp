#include "ClientboundPlayerAbilitiesPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/world/entity/player/Abilities.h"

std::shared_ptr<Packet> ClientboundPlayerAbilitiesPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerAbilitiesPacket());
}

ClientboundPlayerAbilitiesPacket::ClientboundPlayerAbilitiesPacket() : Packet() {
    m_isInvulnerable = false;
    m_isFlying = false;
    m_isEnableFly = false;
    m_isInstabuild = false;
    m_flyingSpeed = 0.0f;
    m_walkingSpeed = 0.0f;
    m_isEnableBuild = true;
    m_playerId = 0;
}

ClientboundPlayerAbilitiesPacket::ClientboundPlayerAbilitiesPacket(Abilities* abilities, int playerId)
    : Packet() {
    setInvulnerable(abilities->m_isInvulnerable);
    setFlying(abilities->m_isFlying);
    setCanFly(abilities->m_isEnableFly);
    setInstabuild(abilities->m_isInstabuild);
    setFlyingSpeed(abilities->getFlyingSpeed());
    setWalkingSpeed(abilities->getWalkingSpeed());
    setCanBuild(abilities->m_isEnableBuild);
    m_playerId = playerId;
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
    m_playerId = input->readInt();
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
    output->writeFloat(m_flyingSpeed);
    output->writeFloat(m_walkingSpeed);
    output->writeInt(m_playerId);
}

void ClientboundPlayerAbilitiesPacket::handle(PacketListener* listener) {
    listener->handlePlayerAbilities(shared_from_this());
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
    m_isInvulnerable = invulnerable;
}

void ClientboundPlayerAbilitiesPacket::setFlying(bool flying) {
    m_isFlying = flying;
}

void ClientboundPlayerAbilitiesPacket::setCanFly(bool canFly) {
    m_isEnableFly = canFly;
}

void ClientboundPlayerAbilitiesPacket::setInstabuild(bool instabuild) {
    m_isInstabuild = instabuild;
}

void ClientboundPlayerAbilitiesPacket::setFlyingSpeed(float flyingSpeed) {
    m_flyingSpeed = flyingSpeed;
}

void ClientboundPlayerAbilitiesPacket::setWalkingSpeed(float walkingSpeed) {
    m_walkingSpeed = walkingSpeed;
}

void ClientboundPlayerAbilitiesPacket::setCanBuild(bool canBuild) {
    m_isEnableBuild = canBuild;
}

bool ClientboundPlayerAbilitiesPacket::isInvulnerable() {
    return m_isInvulnerable;
}

bool ClientboundPlayerAbilitiesPacket::isFlying() {
    return m_isFlying;
}

bool ClientboundPlayerAbilitiesPacket::canFly() {
    return m_isEnableFly;
}

bool ClientboundPlayerAbilitiesPacket::canInstabuild() {
    return m_isInstabuild;
}

bool ClientboundPlayerAbilitiesPacket::canBuild() {
    return m_isEnableBuild;
}

float ClientboundPlayerAbilitiesPacket::getFlyingSpeed() {
    return m_flyingSpeed;
}

float ClientboundPlayerAbilitiesPacket::getWalkingSpeed() {
    return m_walkingSpeed;
}

int ClientboundPlayerAbilitiesPacket::getPlayerId() {
    return m_playerId;
}
