#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class GetInfoPacket : public Packet, public std::enable_shared_from_this<GetInfoPacket> {
public:
    static std::shared_ptr<Packet> create();

    GetInfoPacket();
    virtual EPacketType getPacketId() override;
    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual void handle(PacketListener* listener) override;
    virtual int getEstimatedSize() override;
};
