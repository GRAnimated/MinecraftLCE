#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Network/protocol/Packet.h"

class ClientboundSetSpawnPositionPacket
    : public Packet,
      public std::enable_shared_from_this<ClientboundSetSpawnPositionPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetSpawnPositionPacket();
    ClientboundSetSpawnPositionPacket(int, int, int);
    ClientboundSetSpawnPositionPacket(BlockPos const&);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getEstimatedSize() override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet>) override;
    bool isAync() override;

private:
    BlockPos mPos;
};
