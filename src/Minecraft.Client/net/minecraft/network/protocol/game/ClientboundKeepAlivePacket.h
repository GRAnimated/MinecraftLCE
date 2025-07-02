#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundKeepAlivePacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundKeepAlivePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundKeepAlivePacket();

    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual EPacketType getPacketId() override;
    virtual void handle(PacketListener* listener) override;
    virtual int getEstimatedSize() override;
    virtual bool canBeInvalidated() override;
    virtual bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;
    virtual bool isAync() override;

    int mId;
};
