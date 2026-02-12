#include "ServerboundContainerAckPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundContainerAckPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundContainerAckPacket());
}

ServerboundContainerAckPacket::ServerboundContainerAckPacket() {}

ServerboundContainerAckPacket::ServerboundContainerAckPacket(int containerId, short uid, bool accepted) {
    m_containerId = containerId;
    m_uid = uid;
    m_accepted = accepted;
}

EPacketType ServerboundContainerAckPacket::getPacketId() {
    return EPacketType::_ServerboundContainerAckPacket;
}

void ServerboundContainerAckPacket::read(DataInputStream* input) {
    m_containerId = static_cast<int>(input->readByte());
    m_uid = input->readShort();
    m_accepted = input->readBoolean();
}

void ServerboundContainerAckPacket::write(DataOutputStream* output) {
    output->writeByte(m_containerId);
    output->writeShort(m_uid);
    output->writeBoolean(m_accepted);
}

void ServerboundContainerAckPacket::handle(PacketListener* listener) {
    listener->handleContainerAck(shared_from_this());
}

int ServerboundContainerAckPacket::getContainerId() {
    return m_containerId;
}

short ServerboundContainerAckPacket::getUid() {
    return m_uid;
}
