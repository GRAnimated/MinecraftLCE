#include "ClientboundSetExperiencePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetExperiencePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetExperiencePacket());
}

ClientboundSetExperiencePacket::ClientboundSetExperiencePacket() {
    m_experienceProgress = 0.0;
    m_experienceLevel = 0;
    m_totalExperience = 0;
}

EPacketType ClientboundSetExperiencePacket::getPacketId() {
    return EPacketType::_ClientboundSetExperiencePacket;
}

void ClientboundSetExperiencePacket::read(DataInputStream* input) {
    m_experienceProgress = input->readFloat();
    m_totalExperience = input->readVarInt();
    m_experienceLevel = input->readVarInt();
}

void ClientboundSetExperiencePacket::write(DataOutputStream* output) {
    output->writeFloat(m_experienceProgress);
    output->writeVarInt(m_totalExperience);
    output->writeVarInt(m_experienceLevel);
}

void ClientboundSetExperiencePacket::handle(PacketListener* listener) {
    listener->handleSetExperience(shared_from_this());
}

bool ClientboundSetExperiencePacket::canBeInvalidated() {
    return true;
}

bool ClientboundSetExperiencePacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

float ClientboundSetExperiencePacket::getExperienceProgress() {
    return m_experienceProgress;
}

int ClientboundSetExperiencePacket::getTotalExperience() {
    return m_totalExperience;
}

int ClientboundSetExperiencePacket::getExperienceLevel() {
    return m_experienceLevel;
}
