#include "Minecraft.Network/protocol/game/clientbound/ClientboundSetTimePacket.h"

#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"

std::shared_ptr<Packet> ClientboundSetTimePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetTimePacket());
}

ClientboundSetTimePacket::ClientboundSetTimePacket() : Packet() {
    mGameTime = 0;
    mDayTime = 0;
}

ClientboundSetTimePacket::ClientboundSetTimePacket(long long gameTime, long long dayTime, bool b) : Packet() {
    mGameTime = gameTime;
    mDayTime = dayTime;
}

EPacketType ClientboundSetTimePacket::getPacketId() {
    return EPacketType::_ClientboundSetTimePacket;
}

void ClientboundSetTimePacket::read(DataInputStream* input) {
    mGameTime = input->readLong();
    mDayTime = input->readLong();
}

void ClientboundSetTimePacket::write(DataOutputStream* output) {
    output->writeLong(mGameTime);
    output->writeLong(mDayTime);
}

void ClientboundSetTimePacket::handle(PacketListener* listener) {
    listener->handleSetTime(shared_from_this());
}

long long ClientboundSetTimePacket::getGameTime() {
    return mGameTime;
}

long long ClientboundSetTimePacket::getDayTime() {
    return mDayTime;
}

int ClientboundSetTimePacket::getEstimatedSize() {
    return 16;
}

bool ClientboundSetTimePacket::isInvalidatedBy(std::shared_ptr<Packet> packet) {
    return true;
}

bool ClientboundSetTimePacket::isAync() {
    return true;
}
