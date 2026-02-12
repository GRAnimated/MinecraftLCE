#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/network/protocol/Packet.h"

class ClientboundOpenSignEditorPacket : public Packet,
                                        public std::enable_shared_from_this<ClientboundOpenSignEditorPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundOpenSignEditorPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    BlockPos m_pos;
};
