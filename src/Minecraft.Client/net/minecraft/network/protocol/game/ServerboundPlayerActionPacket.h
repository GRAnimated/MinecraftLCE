#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"
#include "Minecraft.Network/protocol/Packet.h"

class ServerboundPlayerActionPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundPlayerActionPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum eAction {
        StartDestroyBlock = 0,
        AbortDestroyBlock = 1,
        StopDestroyBlock = 2,
        DropAllItems = 3,
        DropItem = 4,
        ReleaseUseItem = 5,
        SwapHeldItems = 6,
    };

    ServerboundPlayerActionPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    BlockPos getPos();
    const Direction* getDirection();
    int getAction();
    int getUseTime();

private:
    BlockPos pos;
    const Direction* direction;
    int action;
    int useTime;
};
