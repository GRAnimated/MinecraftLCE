#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/network/protocol/Packet.h"

class ClientboundTakeItemEntityPacket : public Packet,
                                        public std::enable_shared_from_this<ClientboundTakeItemEntityPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundTakeItemEntityPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getItemId();
    int getPlayerId();
    int getAmount();

private:
    int m_itemId;
    int m_playerId;
    int m_amount;
};
