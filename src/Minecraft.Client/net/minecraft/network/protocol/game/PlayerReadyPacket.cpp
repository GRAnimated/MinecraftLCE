#include "PlayerReadyPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> PlayerReadyPacket::create() {
    return std::shared_ptr<Packet>(new PlayerReadyPacket());
}

PlayerReadyPacket::PlayerReadyPacket() {
    mPlayerId = 0;
    mReady = false;
}

PlayerReadyPacket::PlayerReadyPacket(unsigned int playerId, bool ready) {
    mPlayerId = playerId;
    mReady = ready;
}

int PlayerReadyPacket::getEstimatedSize() {
    return 5;
}

EPacketType PlayerReadyPacket::getPacketId() {
    return EPacketType::_PlayerReadyPacket;
}

void PlayerReadyPacket::read(DataInputStream* input) {
    mPlayerId = input->readInt();
    mReady = input->readBoolean();
}

void PlayerReadyPacket::write(DataOutputStream* output) {
    output->writeInt(mPlayerId);
    output->writeBoolean(mReady);
}

void PlayerReadyPacket::handle(PacketListener* listener) {
    listener->handlePlayerReady(shared_from_this());
}
