#include "ClientboundContainerClosePacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundContainerClosePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundContainerClosePacket());
}

ClientboundContainerClosePacket::ClientboundContainerClosePacket() {
    containerId = 0;
}

int ClientboundContainerClosePacket::getEstimatedSize() {
    return 1;
}

EPacketType ClientboundContainerClosePacket::getPacketId() {
    return EPacketType::_ClientboundContainerClosePacket;
}

void ClientboundContainerClosePacket::read(DataInputStream* input) {
    containerId = input->readByte();
}

void ClientboundContainerClosePacket::write(DataOutputStream* output) {
    output->writeByte(containerId);
}

void ClientboundContainerClosePacket::handle(PacketListener* listener) {
    listener->handleContainerClose(shared_from_this());
}
