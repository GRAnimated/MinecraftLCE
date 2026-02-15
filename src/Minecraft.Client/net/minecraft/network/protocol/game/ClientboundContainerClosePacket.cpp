#include "ClientboundContainerClosePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundContainerClosePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundContainerClosePacket());
}

ClientboundContainerClosePacket::ClientboundContainerClosePacket() {
    m_containerId = 0;
}

int ClientboundContainerClosePacket::getEstimatedSize() {
    return 1;
}

EPacketType ClientboundContainerClosePacket::getPacketId() {
    return EPacketType::_ClientboundContainerClosePacket;
}

void ClientboundContainerClosePacket::read(DataInputStream* input) {
    m_containerId = input->readByte();
}

void ClientboundContainerClosePacket::write(DataOutputStream* output) {
    output->writeByte(m_containerId);
}

void ClientboundContainerClosePacket::handle(PacketListener* listener) {
    listener->handleContainerClose(shared_from_this());
}
