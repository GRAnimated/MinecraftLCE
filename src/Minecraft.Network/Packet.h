#pragma once

#include <deque>
#include <memory>
#include "Minecraft.Network/PacketType.h"

class DataInputStream;
class DataOutputStream;
class PacketListener;

class Packet {
public:
    Packet();
    virtual ~Packet();
    virtual EPacketType getPacketId() = 0;
    virtual void read(DataInputStream*) = 0;
    virtual void write(DataOutputStream*) = 0;
    virtual void handle(PacketListener*);
    virtual int getEstimatedSize();
    virtual bool canBeInvalidated();
    virtual bool isInvalidatedBy(std::shared_ptr<Packet>);
    virtual bool isAync();
    virtual bool tryReplaceDuplicatePacket(std::deque<std::shared_ptr<Packet>>*);

    long mCreatedTime;
    bool field_10;
};