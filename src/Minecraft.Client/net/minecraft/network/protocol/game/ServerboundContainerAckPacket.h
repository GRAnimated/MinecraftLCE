#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/network/protocol/Packet.h"

class ServerboundContainerAckPacket : public Packet,
                                      public std::enable_shared_from_this<ServerboundContainerAckPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundContainerAckPacket();
    ServerboundContainerAckPacket(int containerId, short uid, bool accepted);
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getContainerId();
    short getUid();

private:
    int mContainerId;
    short mUid;
    bool mAccepted;
};
