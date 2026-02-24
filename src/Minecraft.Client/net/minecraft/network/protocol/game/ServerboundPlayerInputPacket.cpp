#include "net/minecraft/network/protocol/game/ServerboundPlayerInputPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ServerboundPlayerInputPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerInputPacket());
}

ServerboundPlayerInputPacket::ServerboundPlayerInputPacket() {
    m_xxa = 0.0f;
    m_zza = 0.0f;
    m_isJumping = false;
    m_isSneaking = false;
}

EPacketType ServerboundPlayerInputPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerInputPacket;
}

void ServerboundPlayerInputPacket::read(DataInputStream* input) {
    m_xxa = input->readFloat();
    m_zza = input->readFloat();
    u8 byte = input->readByte();
    m_isJumping = byte & 1;
    m_isSneaking = byte & 2;
}

void ServerboundPlayerInputPacket::write(DataOutputStream* output) {
    output->writeFloat(m_xxa);
    output->writeFloat(m_zza);

    // Logic copied from Java Edition, they suck!!!
    byte out = 0;
    if (m_isJumping) {
        out = ((out | true) ? 1 : 0);
    }
    if (m_isSneaking) {
        out = (out | 2);
    }

    output->writeByte(out);
}

void ServerboundPlayerInputPacket::handle(PacketListener* listener) {
    listener->handlePlayerInput(shared_from_this());
}

int ServerboundPlayerInputPacket::getEstimatedSize() {
    return 10;
}
