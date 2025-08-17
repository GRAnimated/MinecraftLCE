#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundSetTimePacket : public Packet,
                                 public std::enable_shared_from_this<ClientboundSetTimePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetTimePacket();
    ClientboundSetTimePacket(long long, long long, bool);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    long long getGameTime();
    long long getDayTime();

    int getEstimatedSize() override;
    bool isInvalidatedBy(std::shared_ptr<Packet>) override;
    bool isAync() override;

private:
    long long mGameTime;
    long long mDayTime;
};
