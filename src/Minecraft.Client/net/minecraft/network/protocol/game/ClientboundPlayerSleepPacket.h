#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/network/protocol/Packet.h"
#include <memory>

class Player;

class ClientboundPlayerSleepPacket : public Packet,
                                     public std::enable_shared_from_this<ClientboundPlayerSleepPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPlayerSleepPacket();
    ClientboundPlayerSleepPacket(std::shared_ptr<Player>, const BlockPos&);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getPlayerId();
    BlockPos getPos();

private:
    int m_playerId;
    BlockPos m_pos;
};
