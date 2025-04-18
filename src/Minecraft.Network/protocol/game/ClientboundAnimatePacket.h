#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ClientboundAnimatePacket : public Packet,
                                 public std::enable_shared_from_this<ClientboundAnimatePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundAnimatePacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int dword_28;
    int dword_2c;
};
