#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/InteractionHand.h"

class ServerboundSwingPacket : public Packet, public std::enable_shared_from_this<ServerboundSwingPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundSwingPacket();
    ServerboundSwingPacket(InteractionHand::EInteractionHand interactionHand);

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    InteractionHand::EInteractionHand getHand();

private:
    InteractionHand::EInteractionHand m_interactionHand;
};
