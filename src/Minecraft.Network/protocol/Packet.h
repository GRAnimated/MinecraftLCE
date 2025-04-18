#pragma once

#include "types.h"
#include "Minecraft.Network/PacketType.h"
#include <deque>
#include <memory>
// #include <iostream>
#include "Minecraft.Core/io/DataInputStream.h"

class DataInputStream;
class DataOutputStream;
class PacketListener;

class Packet {
public:
    static std::shared_ptr<Packet> readPacket(DataInputStream*, bool, unsigned int&, bool&);
    static void writePacket(std::shared_ptr<Packet>, DataOutputStream*, bool, unsigned int&);

    Packet();
    virtual ~Packet();
    virtual EPacketType getPacketId() = 0;
    virtual void read(DataInputStream* input) = 0;
    virtual void write(DataOutputStream* output) = 0;
    virtual void handle(PacketListener* listener);
    virtual int getEstimatedSize();
    virtual bool canBeInvalidated();
    virtual bool isInvalidatedBy(std::shared_ptr<Packet> packet);
    virtual bool isAync();
    virtual bool tryReplaceDuplicatePacket(std::deque<std::shared_ptr<Packet>>* duplicatePacket);

    std::wstring readUtf(DataInputStream *in, int length);

    long mCreatedTime;
    bool mShouldDelay;
};

ASSERT_SIZEOF(Packet, 0x18)