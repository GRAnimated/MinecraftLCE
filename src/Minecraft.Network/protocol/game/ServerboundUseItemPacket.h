#pragma once

#include "Minecraft.Network/protocol/Packet.h"
#include "Minecraft.World/InteractionHand.h"

class ServerboundUseItemPacket : public Packet, public std::enable_shared_from_this<ServerboundUseItemPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundUseItemPacket();

    virtual EPacketType getPacketId() override;
    virtual void read(DataInputStream* input) override;
    virtual void write(DataOutputStream* output) override;
    virtual void handle(PacketListener* listener) override;
    virtual int getEstimatedSize() override;

    InteractionHand::EInteractionHand mHand = InteractionHand::MAIN_HAND;
};
