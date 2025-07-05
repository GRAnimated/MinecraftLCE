#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/InteractionHand.h"

class ServerboundUseItemOnPacket : public Packet,
                                   public std::enable_shared_from_this<ServerboundUseItemOnPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundUseItemOnPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    BlockPos getPos();
    const Direction* getFace();
    InteractionHand::EInteractionHand getHand();
    float getClickX();
    float getClickY();
    float getClickZ();

private:
    BlockPos pos;
    const Direction* face;
    InteractionHand::EInteractionHand hand;
    float clickX;
    float clickY;
    float clickZ;
};
