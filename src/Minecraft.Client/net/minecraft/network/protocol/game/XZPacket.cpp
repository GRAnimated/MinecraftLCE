#include "net/minecraft/network/protocol/game/XZPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> XZPacket::create() {
    return std::shared_ptr<Packet>(new XZPacket());
}

XZPacket::XZPacket() : Packet() {}

XZPacket::XZPacket(char field_28, int x, int z) : Packet(), m_field28(field_28), m_x(x), m_z(z) {}

EPacketType XZPacket::getPacketId() {
    return EPacketType::_XZPacket;
}

void XZPacket::read(DataInputStream* input) {
    m_field28 = input->readChar();
    m_x = input->readInt();
    m_z = input->readInt();
}

void XZPacket::write(DataOutputStream* output) {
    output->writeChar(m_field28);
    output->writeInt(m_x);
    output->writeInt(m_z);
}

void XZPacket::handle(PacketListener* listener) {
    listener->handleXZ(shared_from_this());
}

int XZPacket::getEstimatedSize() {
    return 10;
}
