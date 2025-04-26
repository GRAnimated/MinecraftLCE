#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Network/protocol/Packet.h"
#include <memory>

class Player;

class ClientboundPlayerSleepPacket : public Packet,
                                     public std::enable_shared_from_this<ClientboundPlayerSleepPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPlayerSleepPacket();
    ClientboundPlayerSleepPacket(std::shared_ptr<Player>, BlockPos const&);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getPlayerId();
    BlockPos getPos();

private:
    int mPlayerId;
    BlockPos mPos;
};
