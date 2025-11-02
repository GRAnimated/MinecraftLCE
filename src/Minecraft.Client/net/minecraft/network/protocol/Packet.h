#pragma once

#include "net/minecraft/network/PacketType.h"
#include "types.h"
#include <deque>
#include <memory>
#include <unordered_map>
#include <unordered_set>
// #include <iostream>
#include "java/io/DataInputStream.h"
#include "unordered_map"
#include "unordered_set"

class DataInputStream;
class DataOutputStream;
class PacketListener;

class Packet {
public:
    static std::unordered_map<int, std::shared_ptr<Packet> (*)()> sPackets;
    static std::unordered_set<int> sPackets1;
    static std::unordered_set<int> sPackets2;
    static std::unordered_set<int> sPackets3;

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

    /** Reads a length-prefixed UTF16 string
     * @param in The input stream to read from
     * @param maxLength The maximum allowed length of the string you want to read
     */
    static std::wstring readUtf(DataInputStream* in, int maxLength);
    static void writeUtf(const std::wstring& str, DataOutputStream* out);

    static std::unordered_map<int, std::shared_ptr<Packet> (*)()> sPacketsMap;
    static std::unordered_set<int> sPacketsMap1;
    static std::unordered_set<int> sPacketsMap2;
    static std::unordered_set<int> sPacketsMap3;

    static void staticCtor();
    static void map(int, bool, bool, bool, bool, const std::type_info&, std::shared_ptr<Packet> (*)(),
                    std::wstring);

    long long mCreatedTime;  // seems to be longlong judging by class size on wii u
    bool mShouldDelay;
};

ASSERT_SIZEOF(Packet, 0x18)
