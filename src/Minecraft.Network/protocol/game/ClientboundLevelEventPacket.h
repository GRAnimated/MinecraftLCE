#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundLevelEventPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundLevelEventPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundLevelEventPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getType();
    int getData();
    BlockPos getPos();
    bool isGlobalEvent();

private:
    int type;
    int data;
    BlockPos pos;
    bool globalEvent;
};
