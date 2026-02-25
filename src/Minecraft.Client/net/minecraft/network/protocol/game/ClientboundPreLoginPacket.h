#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <string>

class ClientboundPreLoginPacket : public Packet,
                                  public std::enable_shared_from_this<ClientboundPreLoginPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPreLoginPacket();

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    PlayerUID* m_players;
    int m_playerCount;
    char m_unk1;
    int m_unk2;
    char m_mapName;  // not to be confused with world name, which I don't think is written here
    char m_unk3;
    char m_unk4;
    char m_unk5;
    char m_unk6;
    char m_unk7;
    char m_unk8;
    char m_unk9;
    char m_unk10;
    char m_unk11;
    char m_unk12;
    char m_unk13;
    char m_unk14;
    char m_unk15;
    int m_unk16;
    char m_unk17;
    int m_unk18;
    short m_protocolVersion;
    bool m_unk19;
    int m_unk20;
    std::wstring m_name;
};

ASSERT_SIZEOF(ClientboundPreLoginPacket, 0x78)
