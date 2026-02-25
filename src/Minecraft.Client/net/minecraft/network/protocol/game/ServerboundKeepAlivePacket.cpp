#include "ServerboundKeepAlivePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundKeepAlivePacket::create() {
    return std::shared_ptr<Packet>(new ServerboundKeepAlivePacket());
}

ServerboundKeepAlivePacket::ServerboundKeepAlivePacket() : Packet() {
    m_id = 0;
}

void ServerboundKeepAlivePacket::handle(PacketListener* listener) {
    listener->handleKeepAlive(shared_from_this());
}

void ServerboundKeepAlivePacket::read(DataInputStream* input) {
    m_id = input->readVarInt();
}

void ServerboundKeepAlivePacket::write(DataOutputStream* output) {
    output->writeVarInt(m_id);
}

EPacketType ServerboundKeepAlivePacket::getPacketId() {
    return EPacketType::_ServerboundKeepAlivePacket;
}
