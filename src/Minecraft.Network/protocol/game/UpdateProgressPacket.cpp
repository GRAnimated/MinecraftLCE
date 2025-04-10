#include "Minecraft.Client/multiplayer/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/protocol/game/UpdateProgressPacket.h"

std::shared_ptr<Packet> UpdateProgressPacket::create() {
    return std::shared_ptr<Packet>(new UpdateProgressPacket());
}

UpdateProgressPacket::UpdateProgressPacket() : Packet() {
    mProgress = 0;
}

UpdateProgressPacket::UpdateProgressPacket(int progress) : Packet() {
    mProgress = progress;
}

EPacketType UpdateProgressPacket::getPacketId() {
    return EPacketType::_UpdateProgressPacket;
}

void UpdateProgressPacket::read(DataInputStream* input) {
    mProgress = input->readByte();
}

void UpdateProgressPacket::write(DataOutputStream* output) {
    output->writeByte(mProgress);
}

void UpdateProgressPacket::handle(PacketListener* listener) {
    listener->handleUpdateProgress(this->shared_from_this());
}

int UpdateProgressPacket::getEstimatedSize() {
    return 1;
}
