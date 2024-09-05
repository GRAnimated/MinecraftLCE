#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundSetSpawnPositionPacket : public Packet, public std::enable_shared_from_this<ClientboundSetSpawnPositionPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetSpawnPositionPacket();
    void handle(PacketListener*) override;
    void read(DataInputStream*) override;
    void write(DataOutputStream*) override;
    int getEstimatedSize() override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet>) override;
    bool isAync() override;
    EPacketType getPacketId() override;

private:
    BlockPos mPos;
};
