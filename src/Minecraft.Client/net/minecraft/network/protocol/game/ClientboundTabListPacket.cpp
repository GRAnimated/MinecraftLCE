#include "ClientboundTabListPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundTabListPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundTabListPacket());
}

ClientboundTabListPacket::ClientboundTabListPacket() {}

EPacketType ClientboundTabListPacket::getPacketId() {
    return EPacketType::_ClientboundTabListPacket;
}

void ClientboundTabListPacket::read(DataInputStream* input) {
    m_str18 = Packet::readUtf(input, 0x7FFF);
    m_str38 = Packet::readUtf(input, 0x7FFF);
}

void ClientboundTabListPacket::write(DataOutputStream* output) {
    Packet::writeUtf(m_str18, output);
    Packet::writeUtf(m_str38, output);
}

void ClientboundTabListPacket::handle(PacketListener* listener) {}
