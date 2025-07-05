#include "ClientboundSetHealthPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetHealthPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetHealthPacket());
}

ClientboundSetHealthPacket::ClientboundSetHealthPacket() {
    food = 0;
    dword18 = 0;
    dword1C = 0;
    health = 0.0;
    saturation = 0.0;
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
    dword18 = input->readByte() & 0xFF;
    dword1C = input->readVarInt();
    dword20 = input->readVarInt();
}

void ClientboundSetHealthPacket::write(DataOutputStream* output) {
    output->writeFloat(health);
    output->writeVarInt(food);
    output->writeFloat(saturation);
    output->writeByte(dword18);
    output->writeVarInt(dword1C);
    output->writeVarInt(dword20);
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
