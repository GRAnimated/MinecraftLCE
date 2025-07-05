#include "ServerboundChatPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ServerboundChatPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundChatPacket());
}

ServerboundChatPacket::ServerboundChatPacket() {}

EPacketType ServerboundChatPacket::getPacketId() {
    return EPacketType::_ServerboundChatPacket;
}

void ServerboundChatPacket::read(DataInputStream* input) {
    message = Packet::readUtf(input, 256);
}

void ServerboundChatPacket::write(DataOutputStream* output) {
    Packet::writeUtf(message, output);
}

void ServerboundChatPacket::handle(PacketListener* listener) {
    listener->handleChat(shared_from_this());
}
