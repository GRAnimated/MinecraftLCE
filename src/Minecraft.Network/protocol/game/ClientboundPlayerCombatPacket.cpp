#include "Minecraft.Network/protocol/game/ClientboundPlayerCombatPacket.h"

#include "Minecraft.Core/io/DataInputStream.h"
#include "Minecraft.Core/io/DataOutputStream.h"
#include "Minecraft.Network/PacketListener.h"

std::shared_ptr<Packet> ClientboundPlayerCombatPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerCombatPacket());
}

ClientboundPlayerCombatPacket::ClientboundPlayerCombatPacket() {}

EPacketType ClientboundPlayerCombatPacket::getPacketId() {
    return EPacketType::_ClientboundPlayerCombatPacket;
}

void ClientboundPlayerCombatPacket::read(DataInputStream* input) {
    event = input->readInt();

    if (event == 1) {
        duration = input->readVarInt();
        killerId = input->readInt();
        return;
    }

    if (event == 2) {
        playerId = input->readVarInt();
        killerId = input->readInt();
        message = readUtf(input, 0x7FFF);
    }
}

void ClientboundPlayerCombatPacket::write(DataOutputStream* output) {
    output->writeInt(event);

    if (event == 1) {
        output->writeVarInt(duration);
        output->writeInt(killerId);
        return;
    }

    if (event == 2) {
        output->writeVarInt(playerId);
        output->writeInt(killerId);
        writeUtf(message, output);
    }
}

void ClientboundPlayerCombatPacket::handle(PacketListener* listener) {
    listener->handlePlayerCombat(shared_from_this());
}
