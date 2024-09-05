#include "Minecraft.Network/protocol/game/ClientboundSetTimePacket.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetTimePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetTimePacket());
}

ClientboundSetTimePacket::ClientboundSetTimePacket() : Packet() {
    field_28 = 0;
    field_30 = 0;
}

void ClientboundSetTimePacket::handle(PacketListener* listener) {
    listener->handleSetTime(this->shared_from_this());
}

void ClientboundSetTimePacket::read(DataInputStream* input) {
    field_28 = input->readLong();
    field_30 = input->readLong();
}

void ClientboundSetTimePacket::write(DataOutputStream* output) {
    output->writeLong(field_28);
    output->writeLong(field_30);
}

int ClientboundSetTimePacket::getEstimatedSize() {
    return 16;
}

bool ClientboundSetTimePacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

bool ClientboundSetTimePacket::isAync() {
    return true;
}
