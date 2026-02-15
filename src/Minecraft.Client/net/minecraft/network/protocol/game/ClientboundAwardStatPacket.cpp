#include "net/minecraft/network/protocol/game/ClientboundAwardStatPacket.h"
#include "net/minecraft/world/ArrayWithLength.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundAwardStatPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAwardStatPacket());
}

ClientboundAwardStatPacket::ClientboundAwardStatPacket() {}

ClientboundAwardStatPacket::ClientboundAwardStatPacket(int stat, int unk) {
    m_stat = stat;
    m_data = arrayWithLength<unsigned char>(4, true);
    int* data = (int*)m_data.m_data;
    *data = unk;
}

ClientboundAwardStatPacket::~ClientboundAwardStatPacket() {
    if (m_data.m_data) {
        delete[] m_data.m_data;
        m_data.m_data = nullptr;
    }
}

int ClientboundAwardStatPacket::getEstimatedSize() {
    return 6;
}

EPacketType ClientboundAwardStatPacket::getPacketId() {
    return EPacketType::_ClientboundAwardStatPacket;
}

void ClientboundAwardStatPacket::read(DataInputStream* input) {
    m_stat = input->readInt();

    int size = input->readInt();
    if (size < 1)
        return;

    m_data = arrayWithLength<unsigned char>(size, true);

    input->readFully(m_data);
}

void ClientboundAwardStatPacket::write(DataOutputStream* output) {
    output->writeInt(m_stat);
    output->writeInt(m_data.m_length);
    if (m_data.m_length > 0) {
        output->writeBytes(m_data);
    }
}

void ClientboundAwardStatPacket::handle(PacketListener* listener) {
    listener->handleAwardStat(shared_from_this());
    m_data.m_data = nullptr;
}

bool ClientboundAwardStatPacket::isAync() {
    return true;
}

arrayWithLength<unsigned char> ClientboundAwardStatPacket::getParamData() {
    return m_data;
}
