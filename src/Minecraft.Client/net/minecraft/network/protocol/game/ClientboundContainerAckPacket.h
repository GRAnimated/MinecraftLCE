#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/network/protocol/Packet.h"

class ClientboundContainerAckPacket : public Packet,
                                      public std::enable_shared_from_this<ClientboundContainerAckPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundContainerAckPacket();
    ClientboundContainerAckPacket(int containerId, short uid, bool accepted);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getContainerId();
    short getUid();
    bool isAccepted();

private:
    int mContainerId;
    short mUid;
    bool mAccepted;
};
