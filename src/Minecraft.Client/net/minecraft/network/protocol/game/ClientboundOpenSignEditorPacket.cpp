#include "ClientboundOpenSignEditorPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

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
