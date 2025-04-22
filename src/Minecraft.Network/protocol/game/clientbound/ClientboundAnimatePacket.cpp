#include "Minecraft.Network/protocol/game/clientbound/ClientboundAnimatePacket.h"

#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> ClientboundAnimatePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAnimatePacket());
}

ClientboundAnimatePacket::ClientboundAnimatePacket() {
    dword_28 = -1;
    dword_2c = 0;
}

int ClientboundAnimatePacket::getEstimatedSize() {
    return 5;
}

EPacketType ClientboundAnimatePacket::getPacketId() {
    return EPacketType::_ClientboundAnimatePacket;
}

void ClientboundAnimatePacket::read(DataInputStream* input) {
    dword_28 = input->readInt();
    dword_2c = input->readByte();
}

void ClientboundAnimatePacket::write(DataOutputStream* output) {
    output->writeInt(dword_28);
    output->writeByte(dword_2c);
}

void ClientboundAnimatePacket::handle(PacketListener* listener) {
    listener->handleAnimate(shared_from_this());
}
