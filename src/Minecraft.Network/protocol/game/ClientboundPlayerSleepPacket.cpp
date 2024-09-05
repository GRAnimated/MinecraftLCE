#include "Minecraft.Network/protocol/game/ClientboundPlayerSleepPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundPlayerSleepPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerSleepPacket());
}

ClientboundPlayerSleepPacket::ClientboundPlayerSleepPacket() : Packet() {
    field_28 = 0;
    mPos = BlockPos();
}

void ClientboundPlayerSleepPacket::handle(PacketListener* listener) {
    listener->handleEntityActionAtPosition(this->shared_from_this());
}

void ClientboundPlayerSleepPacket::read(DataInputStream* input) {
    field_28 = input->readVarInt();
    mPos = input->readBlockPos();
}

void ClientboundPlayerSleepPacket::write(DataOutputStream* output) {
    output->writeVarInt(field_28);
    output->writeBlockPos(mPos);
}

EPacketType ClientboundPlayerSleepPacket::getPacketId() {
    return EPacketType::_ClientboundPlayerSleepPacket;
}