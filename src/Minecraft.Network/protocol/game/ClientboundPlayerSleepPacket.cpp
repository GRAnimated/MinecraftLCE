#include "ClientboundPlayerSleepPacket.h"

#include "Minecraft.World/entity/player/Player.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

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
