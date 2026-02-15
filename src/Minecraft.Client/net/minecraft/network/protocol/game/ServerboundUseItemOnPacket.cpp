#include "ServerboundUseItemOnPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundUseItemOnPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundUseItemOnPacket());
}

ServerboundUseItemOnPacket::ServerboundUseItemOnPacket() {}

EPacketType ServerboundUseItemOnPacket::getPacketId() {
    return EPacketType::_ServerboundUseItemOnPacket;
}

void ServerboundUseItemOnPacket::read(DataInputStream* input) {
    m_pos = input->readBlockPos();
    m_face = Direction::from3DDataValue(input->readByte());
    m_hand = static_cast<InteractionHand::EInteractionHand>(input->readByte());
    m_clickX = input->readFloat();
    m_clickY = input->readFloat();
    m_clickZ = input->readFloat();
}

void ServerboundUseItemOnPacket::write(DataOutputStream* output) {
    output->writeBlockPos(m_pos);
    output->writeByte(m_face->get3DDataValue());
    output->writeByte(m_hand);
    output->writeFloat(m_clickX);
    output->writeFloat(m_clickY);
    output->writeFloat(m_clickZ);
}

void ServerboundUseItemOnPacket::handle(PacketListener* listener) {
    listener->handleUseItemOn(shared_from_this());
}

BlockPos ServerboundUseItemOnPacket::getPos() {
    return m_pos;
}

const Direction* ServerboundUseItemOnPacket::getFace() {
    return m_face;
}

InteractionHand::EInteractionHand ServerboundUseItemOnPacket::getHand() {
    return m_hand;
}

float ServerboundUseItemOnPacket::getClickX() {
    return m_clickX;
}

float ServerboundUseItemOnPacket::getClickY() {
    return m_clickY;
}

float ServerboundUseItemOnPacket::getClickZ() {
    return m_clickZ;
}
