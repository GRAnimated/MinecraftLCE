#include "ClientboundPlayerSleepPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/world/entity/player/Player.h"

std::shared_ptr<Packet> ClientboundPlayerSleepPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerSleepPacket());
}

ClientboundPlayerSleepPacket::ClientboundPlayerSleepPacket() : Packet() {
    mPlayerId = 0;
    mPos = BlockPos();
}

ClientboundPlayerSleepPacket::ClientboundPlayerSleepPacket(std::shared_ptr<Player> player,
                                                           const BlockPos& pos)
    : Packet() {
    mPlayerId = player->getId();
    mPos = pos;
}

EPacketType ClientboundPlayerSleepPacket::getPacketId() {
    return EPacketType::_ClientboundPlayerSleepPacket;
}

void ClientboundPlayerSleepPacket::read(DataInputStream* input) {
    mPlayerId = input->readVarInt();
    mPos = input->readBlockPos();
}

void ClientboundPlayerSleepPacket::write(DataOutputStream* output) {
    output->writeVarInt(mPlayerId);
    output->writeBlockPos(mPos);
}

void ClientboundPlayerSleepPacket::handle(PacketListener* listener) {
    listener->handleEntityActionAtPosition(shared_from_this());
}

int ClientboundPlayerSleepPacket::getPlayerId() {
    return mPlayerId;
}

BlockPos ClientboundPlayerSleepPacket::getPos() {
    return mPos;
}
