#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class UpdateProgressPacket : public Packet, public std::enable_shared_from_this<UpdateProgressPacket> {
public:
    static std::shared_ptr<Packet> create();

    UpdateProgressPacket();
    UpdateProgressPacket(int progress);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;

    int mProgress;
};
