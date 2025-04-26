#include "ClientboundOpenSignEditorPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundOpenSignEditorPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundOpenSignEditorPacket());
}

ClientboundOpenSignEditorPacket::ClientboundOpenSignEditorPacket() {}

EPacketType ClientboundOpenSignEditorPacket::getPacketId() {
    return EPacketType::_ClientboundOpenSignEditorPacket;
}

void ClientboundOpenSignEditorPacket::read(DataInputStream* input) {
    pos = input->readBlockPos();
}

void ClientboundOpenSignEditorPacket::write(DataOutputStream* output) {
    output->writeBlockPos(pos);
}

void ClientboundOpenSignEditorPacket::handle(PacketListener* listener) {
    listener->handleOpenSignEditor(shared_from_this());
}
