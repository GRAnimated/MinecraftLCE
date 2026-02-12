#include "net/minecraft/network/protocol/game/ClientboundSetBorderPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetBorderPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetBorderPacket());
}

ClientboundSetBorderPacket::ClientboundSetBorderPacket() {}

EPacketType ClientboundSetBorderPacket::getPacketId() {
    return EPacketType::_ClientboundSetBorderPacket;
}

void ClientboundSetBorderPacket::read(DataInputStream* input) {
    m_dword28 = input->readInt();
    switch (m_dword28) {
    case 0:
        m_double40 = input->readDouble();
        break;
    case 1:
        m_double48 = input->readDouble();
        m_double40 = input->readDouble();
        m_qword50 = input->readVarLong();
        break;
    case 2:
        m_double30 = input->readDouble();
        m_double38 = input->readDouble();
        break;
    case 3:
        m_double30 = input->readDouble();
        m_double38 = input->readDouble();
        m_double48 = input->readDouble();
        m_double40 = input->readDouble();
        m_qword50 = input->readVarLong();
        m_dword2c = input->readVarInt();
        m_dword5c = input->readVarInt();
        m_dword58 = input->readVarInt();
        break;
    case 4:
        m_dword58 = input->readVarInt();
        break;
    case 5:
        m_dword5c = input->readVarInt();
        break;
    }
}

void ClientboundSetBorderPacket::write(DataOutputStream* output) {
    output->writeInt(m_dword28);
    switch (m_dword28) {
    case 0:
        output->writeDouble(m_double40);
        break;
    case 1:
        output->writeDouble(m_double48);
        output->writeDouble(m_double40);
        output->writeVarLong(m_qword50);
        break;
    case 2:
        output->writeDouble(m_double30);
        output->writeDouble(m_double38);
        break;
    case 3:
        output->writeDouble(m_double30);
        output->writeDouble(m_double38);
        output->writeDouble(m_double48);
        output->writeDouble(m_double40);
        output->writeVarLong(m_qword50);
        output->writeVarInt(m_dword2c);
        output->writeVarInt(m_dword5c);
        output->writeVarInt(m_dword58);
        break;
    case 4:
        output->writeVarInt(m_dword58);
        break;
    case 5:
        output->writeVarInt(m_dword5c);
        break;
    }
}

void ClientboundSetBorderPacket::handle(PacketListener* listener) {
    listener->handleSetBorder(shared_from_this());
}
