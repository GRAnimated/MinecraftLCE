#include "ServerboundUseItemOnPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundUseItemOnPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundUseItemOnPacket());
}

ServerboundUseItemOnPacket::ServerboundUseItemOnPacket() {}

EPacketType ServerboundUseItemOnPacket::getPacketId() {
    return EPacketType::_ServerboundUseItemOnPacket;
}

void ServerboundUseItemOnPacket::read(DataInputStream* input) {
    pos = input->readBlockPos();
    face = Direction::from3DDataValue(input->readByte());
    hand = static_cast<InteractionHand::EInteractionHand>(input->readByte());
    clickX = input->readFloat();
    clickY = input->readFloat();
    clickZ = input->readFloat();
}

void ServerboundUseItemOnPacket::write(DataOutputStream* output) {
    output->writeBlockPos(pos);
    output->writeByte(face->get3DDataValue()); 
    output->writeByte(hand);
    output->writeFloat(clickX);
    output->writeFloat(clickY);
    output->writeFloat(clickZ);
}

void ServerboundUseItemOnPacket::handle(PacketListener* listener) {
    listener->handleUseItemOn(shared_from_this());
}

BlockPos ServerboundUseItemOnPacket::getPos() {
    return pos;
}

const Direction* ServerboundUseItemOnPacket::getFace() {
    return face;
}

InteractionHand::EInteractionHand ServerboundUseItemOnPacket::getHand() {
    return hand;
}

float ServerboundUseItemOnPacket::getClickX() {
    return clickX;
}

float ServerboundUseItemOnPacket::getClickY() {
    return clickY;
}

float ServerboundUseItemOnPacket::getClickZ() {
    return clickZ;
}
