#include "ClientboundPlayerSleepPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"
#include "net/minecraft/world/entity/player/Player.h"

std::shared_ptr<Packet> ClientboundPlayerSleepPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerSleepPacket());
}

ClientboundPlayerSleepPacket::ClientboundPlayerSleepPacket() : Packet() {
    m_playerId = 0;
    m_pos = BlockPos();
}

ClientboundPlayerSleepPacket::ClientboundPlayerSleepPacket(std::shared_ptr<Player> player,
                                                           const BlockPos& pos)
    : Packet() {
    m_playerId = player->getId();
    m_pos = pos;
}

EPacketType ClientboundPlayerSleepPacket::getPacketId() {
    return EPacketType::_ClientboundPlayerSleepPacket;
}

void ClientboundPlayerSleepPacket::read(DataInputStream* input) {
    m_playerId = input->readVarInt();
    m_pos = input->readBlockPos();
}

void ClientboundPlayerSleepPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_playerId);
    output->writeBlockPos(m_pos);
}

void ClientboundPlayerSleepPacket::handle(PacketListener* listener) {
    listener->handleEntityActionAtPosition(shared_from_this());
}

int ClientboundPlayerSleepPacket::getPlayerId() {
    return m_playerId;
}

BlockPos ClientboundPlayerSleepPacket::getPos() {
    return m_pos;
}
