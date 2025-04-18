#include "Minecraft.Network/PacketListener.h"
#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/protocol/game/ServerboundPlayerInputPacket.h"

std::shared_ptr<Packet> ServerboundPlayerInputPacket::create() {
    return std::shared_ptr<Packet>(new ServerboundPlayerInputPacket());
}

ServerboundPlayerInputPacket::ServerboundPlayerInputPacket() {
    xxa = 0.0f;
    zza = 0.0f;
    isJumping = false;
    isSneaking = false;
}

EPacketType ServerboundPlayerInputPacket::getPacketId() {
    return EPacketType::_ServerboundPlayerInputPacket;
}

void ServerboundPlayerInputPacket::read(DataInputStream* input) {
    xxa = input->readFloat();
    zza = input->readFloat();
    u8 byte = input->readByte();
    isJumping = byte & 1;
    isSneaking = byte & 2;
}

void ServerboundPlayerInputPacket::write(DataOutputStream* output) {
    output->writeFloat(xxa);
    output->writeFloat(zza);

    // Logic copied from Java Edition, they suck!!!
    byte out = 0;
    if (isJumping) {
        out = ((out | true) ? 1 : 0);
    }
    if (isSneaking) {
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
