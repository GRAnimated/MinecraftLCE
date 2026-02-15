#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/network/protocol/Packet.h"

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
    int m_type;
    int m_data;
    BlockPos m_pos;
    bool m_globalEvent;
};
