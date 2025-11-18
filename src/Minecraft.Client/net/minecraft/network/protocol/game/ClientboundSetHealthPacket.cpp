#include "ClientboundSetHealthPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetHealthPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetHealthPacket());
}

ClientboundSetHealthPacket::ClientboundSetHealthPacket() {
    health = 0.0;
    food = 0.0;
    saturation = 0.0;
    dword_28 = 0;
    dword_2C = -1;
}

int ClientboundSetHealthPacket::getEstimatedSize() {
    return 16;
}

EPacketType ClientboundSetHealthPacket::getPacketId() {
    return EPacketType::_ClientboundSetHealthPacket;
}

void ClientboundSetHealthPacket::read(DataInputStream* input) {
    health = input->readFloat();
    food = input->readVarInt();
    saturation = input->readFloat();
    dword_28 = input->readByte() & 0xFF;
    dword_2C = input->readVarInt();
    dword_30 = input->readVarInt();
}

void ClientboundSetHealthPacket::write(DataOutputStream* output) {
    output->writeFloat(health);
    output->writeVarInt(food);
    output->writeFloat(saturation);
    output->writeByte(dword_28);
    output->writeVarInt(dword_2C);
    output->writeVarInt(dword_30);
}

void ClientboundSetHealthPacket::handle(PacketListener* listener) {
    listener->handleSetHealth(shared_from_this());
}

bool ClientboundSetHealthPacket::canBeInvalidated() {
    return true;
}

bool ClientboundSetHealthPacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

float ClientboundSetHealthPacket::getHealth() {
    return health;
}

int ClientboundSetHealthPacket::getFood() {
    return food;
}

float ClientboundSetHealthPacket::getSaturation() {
    return saturation;
}
