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

    PlayerUID *mPlayers;
    int mPlayerCount;
    char mUnk1;
    int mUnk2;
    char mMapName; // not to be confused with world name, which I don't think is written here
    char mUnk3;
    char mUnk4;
    char mUnk5;
    char mUnk6;
    char mUnk7;
    char mUnk8;
    char mUnk9;
    char mUnk10;
    char mUnk11;
    char mUnk12;
    char mUnk13;
    char mUnk14;
    char mUnk15;
    int mUnk16;
    char mUnk17;
    int mUnk18;
    short mProtocolVersion;
    bool mUnk19;
    int mUnk20;
    std::wstring mName;
};

ASSERT_SIZEOF(ClientboundPreLoginPacket, 0x78)
