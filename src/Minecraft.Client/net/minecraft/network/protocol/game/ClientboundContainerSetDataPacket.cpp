#include "ClientboundContainerSetDataPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundContainerSetDataPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundContainerSetDataPacket());
}

ClientboundContainerSetDataPacket::ClientboundContainerSetDataPacket() {
    m_containerId = 0;
    m_value = 0;
    m_id = -1;
}

int ClientboundContainerSetDataPacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundContainerSetDataPacket::getPacketId() {
    return EPacketType::_ClientboundContainerSetDataPacket;
}

void ClientboundContainerSetDataPacket::read(DataInputStream* input) {
    m_containerId = static_cast<int>(input->readUnsignedByte());
    m_id = input->readShort();
    m_value = input->readShort();
}

void ClientboundContainerSetDataPacket::write(DataOutputStream* output) {
    output->writeByte(m_containerId);
    output->writeShort(m_id);
    output->writeShort(m_value);
}

void ClientboundContainerSetDataPacket::handle(PacketListener* listener) {
    listener->handleContainerSetData(shared_from_this());
}

int ClientboundContainerSetDataPacket::getContainerId() {
    return m_containerId;
}

int ClientboundContainerSetDataPacket::getId() {
    return m_id;
}

int ClientboundContainerSetDataPacket::getValue() {
    return m_value;
}
