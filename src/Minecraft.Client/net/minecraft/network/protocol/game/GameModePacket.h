#pragma once

#include "net/minecraft/network/protocol/Packet.h"

// PACKET STUB
class GameModePacket : public Packet, public std::enable_shared_from_this<GameModePacket> {
public:
    enum EMessage {};

    class Data {
    public:
        virtual ~Data();
        virtual void ReadPacket(std::shared_ptr<GameModePacket>) = 0;
        virtual void WritePacket(std::shared_ptr<GameModePacket>) const = 0;
    };

    class EmptyData : public Data {
    public:
        EmptyData();

        void ReadPacket(std::shared_ptr<GameModePacket>) override;
        void WritePacket(std::shared_ptr<GameModePacket>) const override;
    };

    class AddAreaBoundsData : public Data {
    public:
        AddAreaBoundsData(int minX, int minY, int minZ, int maxX, int maxY, int maxZ);

        void ReadPacket(std::shared_ptr<GameModePacket>) override;
        void WritePacket(std::shared_ptr<GameModePacket>) const override;

        int mMinX;
        int mMinY;
        int mMinZ;
        int mMaxX;
        int mMaxY;
        int mMaxZ;
    };

    class LockPlayerLocation : public Data {
    public:
        LockPlayerLocation(bool lock);

        void ReadPacket(std::shared_ptr<GameModePacket>) override;
        void WritePacket(std::shared_ptr<GameModePacket>) const override;

        bool mLock;
    };

    static std::shared_ptr<Packet> create();
    static std::shared_ptr<GameModePacket> Create(EMessage, const Data&);

    // TODO: constructor(s)

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
};
