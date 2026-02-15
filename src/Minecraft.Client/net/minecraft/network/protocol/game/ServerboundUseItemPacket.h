#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/InteractionHand.h"

class ServerboundUseItemPacket : public Packet,
                                 public std::enable_shared_from_this<ServerboundUseItemPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundUseItemPacket();

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;

    InteractionHand::EInteractionHand m_hand = InteractionHand::MAIN_HAND;
};
