#include "ClientboundContainerAckPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundContainerAckPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundContainerAckPacket());
}

ClientboundContainerAckPacket::ClientboundContainerAckPacket() {
    m_containerId = 0;
    m_uid = 0;
    m_accepted = false;
}

ClientboundContainerAckPacket::ClientboundContainerAckPacket(int containerId, short uid, bool accepted) {
    m_containerId = containerId;
    m_uid = uid;
    m_accepted = accepted;
}

int ClientboundContainerAckPacket::getEstimatedSize() {
    return 4;
}

EPacketType ClientboundContainerAckPacket::getPacketId() {
    return EPacketType::_ClientboundContainerAckPacket;
}

void ClientboundContainerAckPacket::read(DataInputStream* input) {
    m_containerId = static_cast<int>(input->readByte());
    m_uid = input->readShort();
    m_accepted = input->readByte() != 0;
}

void ClientboundContainerAckPacket::write(DataOutputStream* output) {
    output->writeByte(m_containerId);
    output->writeShort(m_uid);
    output->writeByte(static_cast<unsigned char>(m_accepted));
}

void ClientboundContainerAckPacket::handle(PacketListener* listener) {
    listener->handleContainerAck(shared_from_this());
}

int ClientboundContainerAckPacket::getContainerId() {
    return m_containerId;
}

short ClientboundContainerAckPacket::getUid() {
    return m_uid;
}

bool ClientboundContainerAckPacket::isAccepted() {
    return m_accepted;
}
