#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundAddExperienceOrbPacket
    : public Packet,
      public std::enable_shared_from_this<ClientboundAddExperienceOrbPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundAddExperienceOrbPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getId();
    int getX();
    int getY();
    int getZ();
    int getValue();

private:
    int id;
    int x;
    int y;
    int z;
    int value;
};
