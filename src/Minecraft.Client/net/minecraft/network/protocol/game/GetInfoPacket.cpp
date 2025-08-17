#include "net/minecraft/network/protocol/game/GetInfoPacket.h"

#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> GetInfoPacket::create() {
    return std::shared_ptr<Packet>(new GetInfoPacket());
}

EPacketType GetInfoPacket::getPacketId() {
    return EPacketType::_GetInfoPacket;
}

void GetInfoPacket::read(DataInputStream* input) {}

void GetInfoPacket::write(DataOutputStream* output) {}

void GetInfoPacket::handle(PacketListener* listener) {
    listener->handleGetInfo(shared_from_this());
}

int GetInfoPacket::getEstimatedSize() {
    return 0;
}
