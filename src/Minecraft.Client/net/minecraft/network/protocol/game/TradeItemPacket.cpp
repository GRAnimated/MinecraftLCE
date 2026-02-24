#include "TradeItemPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> TradeItemPacket::create() {
    return std::shared_ptr<Packet>(new TradeItemPacket());
}

TradeItemPacket::TradeItemPacket() {
    m_dword18 = 0;
    m_dword1C = 0;
}

EPacketType TradeItemPacket::getPacketId() {
    return EPacketType::_TradeItemPacket;
}

void TradeItemPacket::read(DataInputStream* input) {
    m_dword18 = input->readInt();
    m_dword1C = input->readInt();
}

void TradeItemPacket::write(DataOutputStream* output) {
    output->writeInt(m_dword18);
    output->writeInt(m_dword1C);
}

void TradeItemPacket::handle(PacketListener* listener) {
    listener->handleTradeItem(shared_from_this());
}
