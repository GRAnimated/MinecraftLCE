#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/network/protocol/Packet.h"

class ClientboundBlockDestructionPacket
    : public Packet,
      public std::enable_shared_from_this<ClientboundBlockDestructionPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundBlockDestructionPacket();
    ClientboundBlockDestructionPacket(int id, const BlockPos& pos, int progress);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getId();
    BlockPos getPos();
    int getProgress();

private:
    int m_id;
    BlockPos m_pos;
    int m_progress;
};
