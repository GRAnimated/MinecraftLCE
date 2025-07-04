#include "ClientboundAddGlobalEntityPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Util/Mth.h"

std::shared_ptr<Packet> ClientboundAddGlobalEntityPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundAddGlobalEntityPacket());
}

ClientboundAddGlobalEntityPacket::ClientboundAddGlobalEntityPacket() {
    id = -1;
    y = 0;
    z = 0;
    x = 0;
    type = 0;
}

ClientboundAddGlobalEntityPacket::ClientboundAddGlobalEntityPacket(std::shared_ptr<Entity> entity) {
    id = entity->getId();
    x = Mth::floor(entity->mX * 32.0);
    y = Mth::floor(entity->mY * 32.0);
    z = Mth::floor(entity->mZ * 32.0);
    type = (entity->GetType() == 0xB000001);
}

int ClientboundAddGlobalEntityPacket::getEstimatedSize() {
    return 17;
}

EPacketType ClientboundAddGlobalEntityPacket::getPacketId() {
    return EPacketType::_ClientboundAddGlobalEntityPacket;
}

void ClientboundAddGlobalEntityPacket::read(DataInputStream* input) {
    id = input->readInt();
    type = input->readByte();
    x = input->readInt();
    y = input->readInt();
    z = input->readInt();
}

void ClientboundAddGlobalEntityPacket::write(DataOutputStream* output) {
    output->writeInt(id);
    output->writeByte(type);
    output->writeInt(x);
    output->writeInt(y);
    output->writeInt(z);
}

void ClientboundAddGlobalEntityPacket::handle(PacketListener* listener) {
    listener->handleAddGlobalEntity(shared_from_this());
}

int ClientboundAddGlobalEntityPacket::getId() {
    return id;
}

int ClientboundAddGlobalEntityPacket::getX() {
    return x;
}

int ClientboundAddGlobalEntityPacket::getY() {
    return y;
}

int ClientboundAddGlobalEntityPacket::getZ() {
    return z;
}

int ClientboundAddGlobalEntityPacket::getType() {
    return type;
}
