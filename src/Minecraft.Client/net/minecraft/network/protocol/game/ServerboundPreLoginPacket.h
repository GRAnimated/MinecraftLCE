#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <string>

// PACKET STUB
class ServerboundPreLoginPacket : public Packet,
                                  public std::enable_shared_from_this<ServerboundPreLoginPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundPreLoginPacket(const std::wstring &name);
    ServerboundPreLoginPacket();

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    short mProtocolVersion;
    std::wstring mName;
};
