#include "TradeItemPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> TradeItemPacket::create() {
    return std::shared_ptr<Packet>(new TradeItemPacket());
}

TradeItemPacket::TradeItemPacket() {
    dword18 = 0;
    dword1C = 0;
}

EPacketType TradeItemPacket::getPacketId() {
    return EPacketType::_TradeItemPacket;
}

void TradeItemPacket::read(DataInputStream* input) {
    dword18 = input->readInt();
    dword1C = input->readInt();
}

void TradeItemPacket::write(DataOutputStream* output) {
    output->writeInt(dword18);
    output->writeInt(dword1C);
}

void TradeItemPacket::handle(PacketListener* listener) {
    listener->handleTradeItem(shared_from_this());
}
