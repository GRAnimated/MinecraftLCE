#include "ServerboundContainerButtonClickPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundContainerButtonClickPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundContainerButtonClickPacket());
}

ServerboundContainerButtonClickPacket::ServerboundContainerButtonClickPacket() {}

int ServerboundContainerButtonClickPacket::getEstimatedSize() {
    return 2;
}

EPacketType ServerboundContainerButtonClickPacket::getPacketId() {
    return EPacketType::_ServerboundContainerButtonClickPacket;
}

void ServerboundContainerButtonClickPacket::read(DataInputStream* input) {
    m_containerId = static_cast<int>(input->readByte());
    m_buttonId = static_cast<int>(input->readByte());
}

void ServerboundContainerButtonClickPacket::write(DataOutputStream* output) {
    output->writeByte(m_containerId);
    output->writeByte(m_buttonId);
}

void ServerboundContainerButtonClickPacket::handle(PacketListener* listener) {
    listener->handleContainerButtonClick(shared_from_this());
}

int ServerboundContainerButtonClickPacket::getContainerId() {
    return m_containerId;
}

int ServerboundContainerButtonClickPacket::getButtonId() {
    return m_buttonId;
}
