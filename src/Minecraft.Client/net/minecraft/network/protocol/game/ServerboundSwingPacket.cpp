#include "ServerboundSwingPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

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

void ServerboundSwingPacket::write(DataOutputStream* output) {
    output->write((unsigned char)mInteractionHand);
}

void ServerboundSwingPacket::handle(PacketListener* listener) {
    listener->handleAnimate(shared_from_this());
}

InteractionHand::EInteractionHand ServerboundSwingPacket::getHand() {
    return mInteractionHand;
}
