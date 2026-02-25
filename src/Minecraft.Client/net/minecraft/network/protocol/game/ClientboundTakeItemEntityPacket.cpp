#include "ClientboundTakeItemEntityPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundTakeItemEntityPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundTakeItemEntityPacket());
}

ClientboundTakeItemEntityPacket::ClientboundTakeItemEntityPacket() {
    m_playerId = -1;
    m_itemId = -1;
    m_amount = -1;
}

EPacketType ClientboundTakeItemEntityPacket::getPacketId() {
    return EPacketType::_ClientboundTakeItemEntityPacket;
}

void ClientboundTakeItemEntityPacket::read(DataInputStream* input) {
    m_itemId = input->readVarInt();
    m_playerId = input->readVarInt();
    m_amount = input->readVarInt();
}

void ClientboundTakeItemEntityPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_itemId);
    output->writeVarInt(m_playerId);
    output->writeVarInt(m_amount);
}

void ClientboundTakeItemEntityPacket::handle(PacketListener* listener) {
    listener->handleTakeItemEntity(shared_from_this());
}

int ClientboundTakeItemEntityPacket::getItemId() {
    return m_itemId;
}

int ClientboundTakeItemEntityPacket::getPlayerId() {
    return m_playerId;
}

int ClientboundTakeItemEntityPacket::getAmount() {
    return m_amount;
}
