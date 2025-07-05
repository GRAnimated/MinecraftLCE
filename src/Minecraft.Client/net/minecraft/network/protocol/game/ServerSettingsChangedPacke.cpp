#include "ServerSettingsChangedPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerSettingsChangedPacket::create() {
    return std::shared_ptr<Packet>(new ServerSettingsChangedPacket());
}

ServerSettingsChangedPacket::ServerSettingsChangedPacket() {
    dword18 = 0;
    dword1C = 1;
}

ServerSettingsChangedPacket::ServerSettingsChangedPacket(char unk1, unsigned int unk2) {
    dword18 = unk1;
    dword1C = unk2;
}

int ServerSettingsChangedPacket::getEstimatedSize() {
    return 2;
}

EPacketType ServerSettingsChangedPacket::getPacketId() {
    return EPacketType::_ServerSettingsChangedPacket;
}

void ServerSettingsChangedPacket::read(DataInputStream* input) {
    dword18 = input->readByte();
    dword1C = input->readInt();
}

void ServerSettingsChangedPacket::write(DataOutputStream* output) {
    output->writeByte(dword18);
    output->writeInt(dword1C);
}

void ServerSettingsChangedPacket::handle(PacketListener* listener) {
    listener->handleServerSettingsChanged(shared_from_this());
}
