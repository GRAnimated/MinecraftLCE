#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class DisconnectPacket : public Packet, public std::enable_shared_from_this<DisconnectPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum eDisconnectReason {
        _0 = 0,
        _2 = 2,
        _10 = 10,
        _11 = 11,
        _29 = 29,
    };

    DisconnectPacket();

    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual EPacketType getPacketId() override;
    virtual void handle(PacketListener* listener) override;
    virtual int getEstimatedSize() override;
    virtual bool canBeInvalidated() override;
    virtual bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

    eDisconnectReason mReason;
};
