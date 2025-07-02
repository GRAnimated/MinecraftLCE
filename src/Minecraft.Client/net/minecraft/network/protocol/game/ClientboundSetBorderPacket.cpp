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
    dword_28 = input->readInt();
    switch (dword_28) {
    case 0:
        double_40 = input->readDouble();
        break;
    case 1:
        double_48 = input->readDouble();
        double_40 = input->readDouble();
        qword_50 = input->readVarLong();
        break;
    case 2:
        double_30 = input->readDouble();
        double_38 = input->readDouble();
        break;
    case 3:
        double_30 = input->readDouble();
        double_38 = input->readDouble();
        double_48 = input->readDouble();
        double_40 = input->readDouble();
        qword_50 = input->readVarLong();
        dword_2c = input->readVarInt();
        dword_5c = input->readVarInt();
        dword_58 = input->readVarInt();
        break;
    case 4:
        dword_58 = input->readVarInt();
        break;
    case 5:
        dword_5c = input->readVarInt();
        break;
    }
}

void ClientboundSetBorderPacket::write(DataOutputStream* output) {
    output->writeInt(dword_28);
    switch (dword_28) {
    case 0:
        output->writeDouble(double_40);
        break;
    case 1:
        output->writeDouble(double_48);
        output->writeDouble(double_40);
        output->writeVarLong(qword_50);
        break;
    case 2:
        output->writeDouble(double_30);
        output->writeDouble(double_38);
        break;
    case 3:
        output->writeDouble(double_30);
        output->writeDouble(double_38);
        output->writeDouble(double_48);
        output->writeDouble(double_40);
        output->writeVarLong(qword_50);
        output->writeVarInt(dword_2c);
        output->writeVarInt(dword_5c);
        output->writeVarInt(dword_58);
        break;
    case 4:
        output->writeVarInt(dword_58);
        break;
    case 5:
        output->writeVarInt(dword_5c);
        break;
    }
}

void ClientboundSetBorderPacket::handle(PacketListener* listener) {
    listener->handleSetBorder(shared_from_this());
}
