#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/entity/Entity.h"

class ClientboundRotateHeadPacket : public Packet,
                                    public std::enable_shared_from_this<ClientboundRotateHeadPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundRotateHeadPacket();
    ClientboundRotateHeadPacket(std::shared_ptr<Entity> entity, unsigned char yHeadRot);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;
    bool isAync() override;

    int getEntityId();
    unsigned char getYHeadRot();

private:
    int entityId;
    unsigned char mYHeadRot;
};
