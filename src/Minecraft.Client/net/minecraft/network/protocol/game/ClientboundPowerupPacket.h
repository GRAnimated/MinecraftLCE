#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ClientboundPowerupPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundPowerupPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPowerupPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getPowerupID();
    int getPowerupTime();

private:
    int powerupID;
    int powerupTime;
};
