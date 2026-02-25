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
    BlockPos m_pos;
    const Direction* m_face;
    InteractionHand::EInteractionHand m_hand;
    float m_clickX;
    float m_clickY;
    float m_clickZ;
};
