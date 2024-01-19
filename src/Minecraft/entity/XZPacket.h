#pragma once

#include "Minecraft.Network/Packet.h"

class XZPacket : Packet {
public:
    XZPacket();
    XZPacket(char field_28, int x, int z);

    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    int getEstimatedSize() override;

    void* field_18 = nullptr;
    void* field_20 = nullptr;
    char field_28 = 0;
    int x = 0;
    int z = 0;
};