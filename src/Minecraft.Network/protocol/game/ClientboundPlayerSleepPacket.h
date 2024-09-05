#pragma once

#include <memory>
#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Network/PacketType.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundPlayerSleepPacket : public Packet, public std::enable_shared_from_this<ClientboundPlayerSleepPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPlayerSleepPacket();
    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    EPacketType getPacketId() override;

private:
    int field_28;
    BlockPos mPos;
};