#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class Item;

class ClientboundSetBorderPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundSetBorderPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetBorderPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int m_dword28;
    int m_dword2c;
    double m_double30;
    double m_double38;
    double m_double40;
    double m_double48;
    long m_qword50;
    int m_dword58;
    int m_dword5c;
};
