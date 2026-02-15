#include "net/minecraft/network/protocol/game/UpdateProgressPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> UpdateProgressPacket::create() {
    return std::shared_ptr<Packet>(new UpdateProgressPacket());
}

UpdateProgressPacket::UpdateProgressPacket() : Packet() {
    m_progress = 0;
}

UpdateProgressPacket::UpdateProgressPacket(int progress) : Packet() {
    m_progress = progress;
}

EPacketType UpdateProgressPacket::getPacketId() {
    return EPacketType::_UpdateProgressPacket;
}

void UpdateProgressPacket::read(DataInputStream* input) {
    m_progress = input->readByte();
}

void UpdateProgressPacket::write(DataOutputStream* output) {
    output->writeByte(m_progress);
}

void UpdateProgressPacket::handle(PacketListener* listener) {
    listener->handleUpdateProgress(this->shared_from_this());
}

int UpdateProgressPacket::getEstimatedSize() {
    return 1;
}
