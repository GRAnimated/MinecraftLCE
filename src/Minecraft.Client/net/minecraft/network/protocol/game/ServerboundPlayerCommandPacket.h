#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/network/protocol/Packet.h"

class ServerboundPlayerCommandPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundPlayerCommandPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum eAction {
        StartSneaking = 0,
        StopSneaking = 1,
        StopSleeping = 2,
        StopSprinting = 3,
        StartRidingJump = 4,
        StopRidingJump = 5,
        OpenInventory = 6,
        StartFallFlying = 7,
    };

    ServerboundPlayerCommandPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getAction();
    int getData();

private:
    int m_id;
    int m_action;
    int m_data;
};
