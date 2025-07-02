#include "Minecraft.Network/protocol/game/GetInfoPacket.h"

#include "Minecraft.Network/PacketListener.h"

// NON_MATCHING: Needs to set mCreatedTime and mShouldDelay to 0
std::shared_ptr<Packet> GetInfoPacket::create() {
    return std::shared_ptr<Packet>(new GetInfoPacket());
}

GetInfoPacket::GetInfoPacket() {}

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
