#include "Minecraft.Network/protocol/game/serverbound/ServerboundContainerClosePacket.h"

#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> ServerboundContainerClosePacket::create() {
    return std::shared_ptr<Packet>(new ServerboundContainerClosePacket());
}

ServerboundContainerClosePacket::ServerboundContainerClosePacket() {}

EPacketType ServerboundContainerClosePacket::getPacketId() {
    return EPacketType::_ServerboundContainerClosePacket;
}

void ServerboundContainerClosePacket::read(DataInputStream* input) {
    containerId = input->readByte();
}

void ServerboundContainerClosePacket::write(DataOutputStream* output) {
    output->writeByte(containerId);
}

void ServerboundContainerClosePacket::handle(PacketListener* listener) {
    listener->handleContainerClose(shared_from_this());
}
