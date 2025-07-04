#pragma once

#include "Minecraft.Network/protocol/Packet.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/level/Level.h"
#include "Minecraft.World/phys/Vec3.h"
#include "Minecraft.World/InteractionHand.h"

class ServerboundMovePlayerPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundMovePlayerPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundMovePlayerPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    double getX(double x);
    double getY(double y);
    double getZ(double z);
    float getYRot(float yRot);
    float getXRot(float xRot);
    bool isOnGround();

    class Pos;
    class Rot;
    class PosRot;

protected:
    double mX;
    double mY;
    double mZ;
    float mYRot;
    float mXRot;
    bool onGround;
    bool hasPos;
    bool hasRot;
    bool bool3B;
};

class ServerboundMovePlayerPacket::Pos : public ServerboundMovePlayerPacket {
public:
    Pos();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
};

class ServerboundMovePlayerPacket::Rot : public ServerboundMovePlayerPacket {
public:
    Rot();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
};

class ServerboundMovePlayerPacket::PosRot : public ServerboundMovePlayerPacket {
public:
    PosRot();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
};
