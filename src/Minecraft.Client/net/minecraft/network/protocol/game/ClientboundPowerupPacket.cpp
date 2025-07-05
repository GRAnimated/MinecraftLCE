#include "ClientboundPowerupPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundPowerupPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPowerupPacket());
}

ClientboundPowerupPacket::ClientboundPowerupPacket() {
    powerupID = -1;
    powerupTime = -1;
}

int ClientboundPowerupPacket::getEstimatedSize() {
    return 2;
}

EPacketType ClientboundPowerupPacket::getPacketId() {
    return EPacketType::_ClientboundPowerupPacket;
}

void ClientboundPowerupPacket::read(DataInputStream* input) {
    powerupID = input->readInt();
    powerupTime = input->readInt();
}

void ClientboundPowerupPacket::write(DataOutputStream* output) {
    output->writeInt(powerupID);
    output->writeInt(powerupTime);
}

void ClientboundPowerupPacket::handle(PacketListener* listener) {
    listener->handlePowerup(shared_from_this());
}

int ClientboundPowerupPacket::getPowerupID() {
    return powerupID;
}

int ClientboundPowerupPacket::getPowerupTime() {
    return powerupTime;
}
