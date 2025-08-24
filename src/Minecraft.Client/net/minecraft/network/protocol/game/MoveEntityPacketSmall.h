#pragma once

#include "net/minecraft/network/protocol/Packet.h"

// PACKET STUB
class MoveEntityPacketSmall : public Packet, public std::enable_shared_from_this<MoveEntityPacketSmall> {
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
class MoveEntityPacketSmall::Pos : public MoveEntityPacketSmall {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};

// PACKET STUB
class MoveEntityPacketSmall::Rot : public MoveEntityPacketSmall {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};

// PACKET STUB
class MoveEntityPacketSmall::PosRot : public MoveEntityPacketSmall {
public:
    static std::shared_ptr<Packet> create();

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};
