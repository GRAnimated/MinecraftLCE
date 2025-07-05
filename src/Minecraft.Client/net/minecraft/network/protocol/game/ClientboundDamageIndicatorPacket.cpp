#include "ClientboundDamageIndicatorPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundDamageIndicatorPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundDamageIndicatorPacket());
}

ClientboundDamageIndicatorPacket::ClientboundDamageIndicatorPacket() {
    x = 0.0;
    z = 0.0;
    allDirections = true;
}

int ClientboundDamageIndicatorPacket::getEstimatedSize() {
    return 9;
}

EPacketType ClientboundDamageIndicatorPacket::getPacketId() {
    return EPacketType::_ClientboundDamageIndicatorPacket;
}

void ClientboundDamageIndicatorPacket::read(DataInputStream* input) {
    x = input->readFloat();
    z = input->readFloat();
    allDirections = input->readBoolean();
}

void ClientboundDamageIndicatorPacket::write(DataOutputStream* output) {
    output->writeFloat(x);
    output->writeFloat(z);
    output->writeBoolean(allDirections);
}

void ClientboundDamageIndicatorPacket::handle(PacketListener* listener) {
    listener->handleDamageIndicator(shared_from_this());
}

float ClientboundDamageIndicatorPacket::getX() {
    return x;
}

float ClientboundDamageIndicatorPacket::getZ() {
    return z;
}

bool ClientboundDamageIndicatorPacket::isAllDirections() {
    return allDirections;
}
