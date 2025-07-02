#include "ServerboundUseItemPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundUseItemPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundUseItemPacket());
}

ServerboundUseItemPacket::ServerboundUseItemPacket() : Packet() {}

EPacketType ServerboundUseItemPacket::getPacketId() {
    return EPacketType::_ServerboundUseItemPacket;
}

void ServerboundUseItemPacket::read(DataInputStream* input) {
    mHand = (InteractionHand::EInteractionHand)input->readByte();
}

void ServerboundUseItemPacket::write(DataOutputStream* output) {
    output->writeByte(mHand);
}

void ServerboundUseItemPacket::handle(PacketListener* listener) {
    listener->handleUseItem(shared_from_this());
}

int ServerboundUseItemPacket::getEstimatedSize() {
    return 1;
}
