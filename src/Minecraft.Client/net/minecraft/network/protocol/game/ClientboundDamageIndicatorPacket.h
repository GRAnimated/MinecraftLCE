#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <string>

class ClientboundDamageIndicatorPacket
    : public Packet,
      public std::enable_shared_from_this<ClientboundDamageIndicatorPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundDamageIndicatorPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    float getX();
    float getZ();
    bool isAllDirections();

private:
    float x;
    float z;
    bool allDirections;
};
