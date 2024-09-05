#include "Minecraft.Network/protocol/game/ServerboundSwingPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundSwingPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundSwingPacket());
}

ServerboundSwingPacket::ServerboundSwingPacket() : Packet() {
    field_28 = 0;
}

void ServerboundSwingPacket::handle(PacketListener* listener) {
    listener->handleAnimate(this->shared_from_this());
}

void ServerboundSwingPacket::read(DataInputStream* input) {
    field_28 = input->read();
}

// NON_MATCHING: game uses LDRB while decomp uses LDR
void ServerboundSwingPacket::write(DataOutputStream* output) {
    output->write(field_28);
}

EPacketType ServerboundSwingPacket::getPacketId() {
    return EPacketType::_ServerboundSwingPacket;
}
