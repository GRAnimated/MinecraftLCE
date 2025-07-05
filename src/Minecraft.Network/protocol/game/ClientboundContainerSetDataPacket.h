#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundContainerSetDataPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundContainerSetDataPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundContainerSetDataPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getContainerId();
    int getId();
    int getValue();

private:
    int containerId;
    int id;
    int value;
};
