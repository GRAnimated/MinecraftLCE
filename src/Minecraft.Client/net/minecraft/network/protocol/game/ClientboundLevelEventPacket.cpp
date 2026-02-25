#include "ClientboundLevelEventPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundLevelEventPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundLevelEventPacket());
}

ClientboundLevelEventPacket::ClientboundLevelEventPacket() {
    m_type = 0;
    m_data = 0;
    m_pos = BlockPos::BlockPos();
}

int ClientboundLevelEventPacket::getEstimatedSize() {
    return 21;
}

EPacketType ClientboundLevelEventPacket::getPacketId() {
    return EPacketType::_ClientboundLevelEventPacket;
}

void ClientboundLevelEventPacket::read(DataInputStream* input) {
    m_type = input->readInt();
    m_pos = input->readBlockPos();
    m_data = input->readInt();
    m_globalEvent = input->readBoolean();
}

void ClientboundLevelEventPacket::write(DataOutputStream* output) {
    output->writeInt(m_type);
    output->writeBlockPos(m_pos);
    output->writeInt(m_data);
    output->writeBoolean(m_globalEvent);
}

void ClientboundLevelEventPacket::handle(PacketListener* listener) {
    listener->handleLevelEvent(shared_from_this());
}

int ClientboundLevelEventPacket::getType() {
    return m_type;
}

int ClientboundLevelEventPacket::getData() {
    return m_data;
}

BlockPos ClientboundLevelEventPacket::getPos() {
    return m_pos;
}

bool ClientboundLevelEventPacket::isGlobalEvent() {
    return m_globalEvent;
}
