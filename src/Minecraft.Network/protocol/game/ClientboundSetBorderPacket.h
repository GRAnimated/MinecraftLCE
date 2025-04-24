#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class Item;

class ClientboundSetBorderPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundSetBorderPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetBorderPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int dword_28;
    int dword_2c;
    double double_30;
    double double_38;
    double double_40;
    double double_48;
    long qword_50;
    int dword_58;
    int dword_5c;
};
