#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/level/border/WorldBorder.h"

class Item;

class ClientboundSetBorderPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundSetBorderPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum class Type : int { SET_SIZE, LERP_SIZE, SET_CENTER, SET_ALL, SET_WARNING_TIME, SET_WARNING_BLOCKS };

    ClientboundSetBorderPacket();

    // appears to not exist???
    ClientboundSetBorderPacket(WorldBorder* border, ClientboundSetBorderPacket::Type type) DELETE_UNUSED;

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    void applyChanges(WorldBorder* border);

private:
    Type m_updateType;
    int m_absoluteMaxSize;
    double m_centerX;
    double m_centerZ;
    double m_size;
    double m_newSize;
    long m_lerpTime;
    int m_warningTime;
    int m_warningBlocks;
};
