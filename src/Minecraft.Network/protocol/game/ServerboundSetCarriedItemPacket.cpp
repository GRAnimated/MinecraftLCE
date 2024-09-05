#include "Minecraft.Network/protocol/game/ServerboundSetCarriedItemPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundSetCarriedItemPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundSetCarriedItemPacket());
}

ServerboundSetCarriedItemPacket::ServerboundSetCarriedItemPacket() : Packet() {}

void ServerboundSetCarriedItemPacket::handle(PacketListener* listener) {
    listener->handleSetCarriedItem(this->shared_from_this());
}

void ServerboundSetCarriedItemPacket::read(DataInputStream* input) {
    field_28 = input->readShort();
}

void ServerboundSetCarriedItemPacket::write(DataOutputStream* output) {
    output->writeShort(field_28);
}

EPacketType ServerboundSetCarriedItemPacket::getPacketId() {
    return EPacketType::_ServerboundSetCarriedItemPacket;
}
