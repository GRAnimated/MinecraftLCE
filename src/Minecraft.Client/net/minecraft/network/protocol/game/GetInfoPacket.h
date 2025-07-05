#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class GetInfoPacket : public Packet, public std::enable_shared_from_this<GetInfoPacket> {
public:
    static std::shared_ptr<Packet> create();

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;
};
