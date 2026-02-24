#include "ClientboundGameEventPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundGameEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundGameEventPacket());
}

ClientboundGameEventPacket::ClientboundGameEventPacket() {
    m_event = 0;
    m_param = 0.0;
    m_playerIndex = -1;
}

int ClientboundGameEventPacket::getEstimatedSize() {
    return 3;
}

EPacketType ClientboundGameEventPacket::getPacketId() {
    return EPacketType::_ClientboundGameEventPacket;
}

void ClientboundGameEventPacket::read(DataInputStream* input) {
    m_event = static_cast<int>(input->readUnsignedByte());
    m_param = input->readFloat();
    m_playerIndex = input->readInt();
}

void ClientboundGameEventPacket::write(DataOutputStream* output) {
    output->writeByte(m_event);
    output->writeFloat(m_param);
    output->writeInt(m_playerIndex);
}

void ClientboundGameEventPacket::handle(PacketListener* listener) {
    listener->handleGameEvent(shared_from_this());
}

int ClientboundGameEventPacket::getEvent() {
    return m_event;
}

float ClientboundGameEventPacket::getParam() {
    return m_param;
}

int ClientboundGameEventPacket::getPlayerIndex() {
    return m_playerIndex;
}
