#include "ClientboundSetTimePacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetTimePacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetTimePacket());
}

ClientboundSetTimePacket::ClientboundSetTimePacket() : Packet() {
    m_gameTime = 0;
    m_dayTime = 0;
}

ClientboundSetTimePacket::ClientboundSetTimePacket(long long gameTime, long long dayTime, bool b) : Packet() {
    m_gameTime = gameTime;
    m_dayTime = dayTime;
}

EPacketType ClientboundSetTimePacket::getPacketId() {
    return EPacketType::_ClientboundSetTimePacket;
}

void ClientboundSetTimePacket::read(DataInputStream* input) {
    m_gameTime = input->readLong();
    m_dayTime = input->readLong();
}

void ClientboundSetTimePacket::write(DataOutputStream* output) {
    output->writeLong(m_gameTime);
    output->writeLong(m_dayTime);
}

void ClientboundSetTimePacket::handle(PacketListener* listener) {
    listener->handleSetTime(shared_from_this());
}

long long ClientboundSetTimePacket::getGameTime() {
    return m_gameTime;
}

long long ClientboundSetTimePacket::getDayTime() {
    return m_dayTime;
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
