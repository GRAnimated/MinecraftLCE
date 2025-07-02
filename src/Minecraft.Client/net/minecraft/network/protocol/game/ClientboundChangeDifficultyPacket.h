#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class Difficulty;

class ClientboundChangeDifficultyPacket
    : public Packet,
      public std::enable_shared_from_this<ClientboundChangeDifficultyPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundChangeDifficultyPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    Difficulty* difficulty;
    void* unused;
};
