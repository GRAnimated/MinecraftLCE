#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <string>

class ServerboundChatPacket : public Packet, public std::enable_shared_from_this<ServerboundChatPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundChatPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    std::wstring message;
};
