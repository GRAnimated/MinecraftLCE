#include "Minecraft.Network/protocol/game/ServerboundUseItemPacket.h"

#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

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
