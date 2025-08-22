#pragma once

#include "net/minecraft/network/protocol/Packet.h"

// PACKET STUB
class ClientboundMoveEntityPacket : public Packet,
                                    public std::enable_shared_from_this<ClientboundMoveEntityPacket> {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    class Pos;
    class Rot;
    class PosRot;
};

// PACKET STUB
class ClientboundMoveEntityPacket::Pos : public ClientboundMoveEntityPacket {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};

// PACKET STUB
class ClientboundMoveEntityPacket::Rot : public ClientboundMoveEntityPacket {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};

// PACKET STUB
class ClientboundMoveEntityPacket::PosRot : public ClientboundMoveEntityPacket {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};
