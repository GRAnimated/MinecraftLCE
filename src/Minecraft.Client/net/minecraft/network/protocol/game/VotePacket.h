#pragma once

#include "net/minecraft/network/PacketType.h"
#include "net/minecraft/network/protocol/Packet.h"

class VotePacket : public Packet, public std::enable_shared_from_this<VotePacket> {
public:
    static std::shared_ptr<Packet> create();

    VotePacket();

    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;
    EPacketType getPacketId() override;

private:
    int field_28 = -1;
    unsigned char field_2C = -1;
    int field_30 = -1;
    int field_34 = -1;
};