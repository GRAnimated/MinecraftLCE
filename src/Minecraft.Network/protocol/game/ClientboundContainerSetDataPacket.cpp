#include "ClientboundContainerSetDataPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundContainerSetDataPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundContainerSetDataPacket());
}

ClientboundContainerSetDataPacket::ClientboundContainerSetDataPacket() {
    containerId = 0;
    value = 0;
    id = -1;
}

int ClientboundContainerSetDataPacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundContainerSetDataPacket::getPacketId() {
    return EPacketType::_ClientboundContainerSetDataPacket;
}

void ClientboundContainerSetDataPacket::read(DataInputStream* input) {
    containerId = static_cast<int>(input->readUnsignedByte());
    id = input->readShort();
    value = input->readShort();
}

void ClientboundContainerSetDataPacket::write(DataOutputStream* output) {
    output->writeByte(containerId);
    output->writeShort(id);
    output->writeShort(value);
}

void ClientboundContainerSetDataPacket::handle(PacketListener* listener) {
    listener->handleContainerSetData(shared_from_this());
}

int ClientboundContainerSetDataPacket::getContainerId() {
    return containerId;
}

int ClientboundContainerSetDataPacket::getId() {
    return id;
}

int ClientboundContainerSetDataPacket::getValue() {
    return value;
}
