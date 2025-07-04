#include "ClientboundSetCameraPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetCameraPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetCameraPacket());
}

ClientboundSetCameraPacket::ClientboundSetCameraPacket() {
    cameraId = 0;
}

EPacketType ClientboundSetCameraPacket::getPacketId() {
    return EPacketType::_ClientboundSetCameraPacket;
}

void ClientboundSetCameraPacket::read(DataInputStream* input) {
    cameraId = input->readVarInt();
}

void ClientboundSetCameraPacket::write(DataOutputStream* output) {
    output->writeVarInt(cameraId);
}

void ClientboundSetCameraPacket::handle(PacketListener* listener) {
    listener->handleSetCamera(shared_from_this());
}

int ClientboundSetCameraPacket::getCameraId() {
    return cameraId;
}
