#include "PlayerReadyPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> PlayerReadyPacket::create() {
    return std::shared_ptr<Packet>(new PlayerReadyPacket());
}

PlayerReadyPacket::PlayerReadyPacket() {
    m_playerId = 0;
    m_ready = false;
}

PlayerReadyPacket::PlayerReadyPacket(unsigned int playerId, bool ready) {
    m_playerId = playerId;
    m_ready = ready;
}

int PlayerReadyPacket::getEstimatedSize() {
    return 5;
}

EPacketType PlayerReadyPacket::getPacketId() {
    return EPacketType::_PlayerReadyPacket;
}

void PlayerReadyPacket::read(DataInputStream* input) {
    m_playerId = input->readInt();
    m_ready = input->readBoolean();
}

void PlayerReadyPacket::write(DataOutputStream* output) {
    output->writeInt(m_playerId);
    output->writeBoolean(m_ready);
}

void PlayerReadyPacket::handle(PacketListener* listener) {
    listener->handlePlayerReady(shared_from_this());
}
