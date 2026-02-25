#include "ClientboundSetCameraPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundSetCameraPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundSetCameraPacket());
}

ClientboundSetCameraPacket::ClientboundSetCameraPacket() {
    m_cameraId = 0;
}

EPacketType ClientboundSetCameraPacket::getPacketId() {
    return EPacketType::_ClientboundSetCameraPacket;
}

void ClientboundSetCameraPacket::read(DataInputStream* input) {
    m_cameraId = input->readVarInt();
}

void ClientboundSetCameraPacket::write(DataOutputStream* output) {
    output->writeVarInt(m_cameraId);
}

void ClientboundSetCameraPacket::handle(PacketListener* listener) {
    listener->handleSetCamera(shared_from_this());
}

int ClientboundSetCameraPacket::getCameraId() {
    return m_cameraId;
}
