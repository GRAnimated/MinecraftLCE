#include "Minecraft.Network/protocol/game/ServerboundSwingPacket.h"

#include "Minecraft.Client/multiplayer/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> ServerboundSwingPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundSwingPacket());
}

ServerboundSwingPacket::ServerboundSwingPacket() : Packet() {
    mInteractionHand = (InteractionHand::EInteractionHand)0;
}

ServerboundSwingPacket::ServerboundSwingPacket(InteractionHand::EInteractionHand interactionHand) : Packet() {
    mInteractionHand = interactionHand;
}

EPacketType ServerboundSwingPacket::getPacketId() {
    return EPacketType::_ServerboundSwingPacket;
}

void ServerboundSwingPacket::read(DataInputStream* input) {
    mInteractionHand = (InteractionHand::EInteractionHand)input->read();
}

// NON_MATCHING: game uses LDRB while decomp uses LDR
void ServerboundSwingPacket::write(DataOutputStream* output) {
    output->write(mInteractionHand);
}

void ServerboundSwingPacket::handle(PacketListener* listener) {
    listener->handleAnimate(shared_from_this());
}

InteractionHand::EInteractionHand ServerboundSwingPacket::getHand() {
    return mInteractionHand;
}
