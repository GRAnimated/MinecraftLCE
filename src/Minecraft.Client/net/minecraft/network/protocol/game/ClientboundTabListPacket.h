#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <string>

class ClientboundTabListPacket : public Packet,
                                 public std::enable_shared_from_this<ClientboundTabListPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundTabListPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    std::wstring m_str18;
    std::wstring m_str38;
};
