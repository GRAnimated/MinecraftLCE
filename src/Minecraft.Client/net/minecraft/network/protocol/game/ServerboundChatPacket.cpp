#include "ServerboundChatPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundChatPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundChatPacket());
}

ServerboundChatPacket::ServerboundChatPacket() {}

EPacketType ServerboundChatPacket::getPacketId() {
    return EPacketType::_ServerboundChatPacket;
}

void ServerboundChatPacket::read(DataInputStream* input) {
    m_essage = Packet::readUtf(input, 256);
}

void ServerboundChatPacket::write(DataOutputStream* output) {
    Packet::writeUtf(m_essage, output);
}

void ServerboundChatPacket::handle(PacketListener* listener) {
    listener->handleChat(shared_from_this());
}
