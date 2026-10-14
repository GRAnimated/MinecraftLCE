#include "ServerboundPlayerAbilitiesPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/world/entity/player/Abilities.h"

std::shared_ptr<Packet> ServerboundPlayerAbilitiesPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerAbilitiesPacket());
}

ServerboundPlayerAbilitiesPacket::ServerboundPlayerAbilitiesPacket() : Packet() {
    m_isInvulnerable = false;
    m_isFlying = false;
    m_isEnableFly = false;
    m_isInstabuild = false;
    m_flyingSpeed = 0.0f;
    m_walkingSpeed = 0.0f;
}

ServerboundPlayerAbilitiesPacket::ServerboundPlayerAbilitiesPacket(Abilities* abilities) : Packet() {
    setInvulnerable(abilities->m_isInvulnerable);
    setFlying(abilities->m_isFlying);
    setCanFly(abilities->m_isEnableFly);
    setInstabuild(abilities->m_isInstabuild);
    setFlyingSpeed(abilities->getFlyingSpeed());
    setWalkingSpeed(abilities->getWalkingSpeed());
}

EPacketType ServerboundPlayerAbilitiesPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerAbilitiesPacket;
}

void ServerboundPlayerAbilitiesPacket::read(DataInputStream* input) {
    u8 flags = input->readByte();
    setInvulnerable(flags & 0x01);
    setFlying(flags & 0x02);
    setCanFly(flags & 0x04);
    setInstabuild(flags & 0x08);
    setFlyingSpeed(input->readFloat());
    setWalkingSpeed(input->readFloat());
}

void ServerboundPlayerAbilitiesPacket::write(DataOutputStream* output) {
    u8 flags = 0;
    if (isInvulnerable())
        flags |= 0x01;
    if (isFlying())
        flags |= 0x02;
    if (canFly())
        flags |= 0x04;
    if (canInstabuild())
        flags |= 0x08;
    output->writeByte(flags);
    output->writeFloat(m_flyingSpeed);
    output->writeFloat(m_walkingSpeed);
}

void ServerboundPlayerAbilitiesPacket::handle(PacketListener* listener) {
    listener->handlePlayerAbilities(shared_from_this());
}

void ServerboundPlayerAbilitiesPacket::setInvulnerable(bool value) {
    m_isInvulnerable = value;
}

void ServerboundPlayerAbilitiesPacket::setFlying(bool value) {
    m_isFlying = value;
}

void ServerboundPlayerAbilitiesPacket::setCanFly(bool value) {
    m_isEnableFly = value;
}

void ServerboundPlayerAbilitiesPacket::setInstabuild(bool value) {
    m_isInstabuild = value;
}

void ServerboundPlayerAbilitiesPacket::setFlyingSpeed(float value) {
    m_flyingSpeed = value;
}

void ServerboundPlayerAbilitiesPacket::setWalkingSpeed(float value) {
    m_walkingSpeed = value;
}

bool ServerboundPlayerAbilitiesPacket::isInvulnerable() {
    return m_isInvulnerable;
}

bool ServerboundPlayerAbilitiesPacket::isFlying() {
    return m_isFlying;
}

bool ServerboundPlayerAbilitiesPacket::canFly() {
    return m_isEnableFly;
}

bool ServerboundPlayerAbilitiesPacket::canInstabuild() {
    return m_isInstabuild;
}
