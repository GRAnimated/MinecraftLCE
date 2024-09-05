#pragma once

#include "Minecraft.Network/PacketType.h"
#include "Minecraft.Network/protocol/Packet.h"

class VotePacket : public Packet, public std::enable_shared_from_this<VotePacket> {
public:
    static std::shared_ptr<Packet> create();

    VotePacket();
    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    int getEstimatedSize() override;
    EPacketType getPacketId() override;

private:
    int field_28 = -1;
    unsigned char field_2C = -1;
    int field_30 = -1;
    int field_34 = -1;
};