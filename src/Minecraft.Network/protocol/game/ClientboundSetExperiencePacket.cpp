#include "ClientboundSetExperiencePacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetExperiencePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetExperiencePacket());
}

ClientboundSetExperiencePacket::ClientboundSetExperiencePacket() {
    experienceProgress = 0.0;
    experienceLevel = 0;
    totalExperience = 0;
}

EPacketType ClientboundSetExperiencePacket::getPacketId() {
    return EPacketType::_ClientboundSetExperiencePacket;
}

void ClientboundSetExperiencePacket::read(DataInputStream* input) {
    experienceProgress = input->readFloat();
    totalExperience = input->readVarInt();
    experienceLevel = input->readVarInt();
}

void ClientboundSetExperiencePacket::write(DataOutputStream* output) {
    output->writeFloat(experienceProgress);
    output->writeVarInt(totalExperience);
    output->writeVarInt(experienceLevel);
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
    return experienceProgress;
}

int ClientboundSetExperiencePacket::getTotalExperience() {
    return totalExperience;
}

int ClientboundSetExperiencePacket::getExperienceLevel() {
    return experienceLevel;
}
