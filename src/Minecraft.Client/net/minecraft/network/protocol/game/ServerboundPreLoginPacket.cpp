#include "ServerboundPreLoginPacket.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/SharedConstants.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundPreLoginPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPreLoginPacket());
}

ServerboundPreLoginPacket::ServerboundPreLoginPacket(const std::wstring& name) {
    this->mName = name;
    this->mProtocolVersion = 0;
}

ServerboundPreLoginPacket::ServerboundPreLoginPacket() {
    this->mName = L"";
    this->mProtocolVersion = 0;
}

EPacketType ServerboundPreLoginPacket::getPacketId() {
    return _ServerboundPreLoginPacket;
}

void ServerboundPreLoginPacket::read(DataInputStream* input) {
    this->mProtocolVersion = input->readShort();
    this->mName = this->readUtf(input, 0x20);
}

void ServerboundPreLoginPacket::write(DataOutputStream* output) {
    output->writeShort(SharedConstants::NETWORK_PROTOCOL_VERSION);
    this->writeUtf(this->mName, output);
}

void ServerboundPreLoginPacket::handle(PacketListener* listener) {
    listener->handlePreLogin(shared_from_this());
}