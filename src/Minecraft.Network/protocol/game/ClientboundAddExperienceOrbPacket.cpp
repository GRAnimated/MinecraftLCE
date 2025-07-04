#include "ClientboundAddExperienceOrbPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundAddExperienceOrbPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAddExperienceOrbPacket());
}

ClientboundAddExperienceOrbPacket::ClientboundAddExperienceOrbPacket() {
    x = 0;
    z = 0;
    value = 0;
    y = 0;
    id = 0;
}

int ClientboundAddExperienceOrbPacket::getEstimatedSize() {
    return 18;
}

EPacketType ClientboundAddExperienceOrbPacket::getPacketId() {
    return EPacketType::_ClientboundAddExperienceOrbPacket;
}

void ClientboundAddExperienceOrbPacket::read(DataInputStream* input) {
    id = input->readInt();
    x = input->readInt();
    y = input->readInt();
    z = input->readInt();
    value = input->readShort();
}

void ClientboundAddExperienceOrbPacket::write(DataOutputStream* output) {
    output->writeInt(id);
    output->writeInt(x);
    output->writeInt(y);
    output->writeInt(z);
    output->writeShort(value);
}

void ClientboundAddExperienceOrbPacket::handle(PacketListener* listener) {
    listener->handleAddExperienceOrb(shared_from_this());
}

int ClientboundAddExperienceOrbPacket::getId() {
    return id;
}

int ClientboundAddExperienceOrbPacket::getX() {
    return x;
}

int ClientboundAddExperienceOrbPacket::getY() {
    return y;
}

int ClientboundAddExperienceOrbPacket::getZ() {
    return z;
}

int ClientboundAddExperienceOrbPacket::getValue() {
    return value;
}
