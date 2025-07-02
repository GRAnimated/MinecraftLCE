#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class UpdateProgressPacket : public Packet, public std::enable_shared_from_this<UpdateProgressPacket> {
public:
    static std::shared_ptr<Packet> create();

    UpdateProgressPacket();
    UpdateProgressPacket(int progress);

    virtual EPacketType getPacketId() override;
    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual void handle(PacketListener* listener) override;
    virtual int getEstimatedSize() override;

    int mProgress;
};
