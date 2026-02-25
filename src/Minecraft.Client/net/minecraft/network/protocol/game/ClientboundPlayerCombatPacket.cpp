#include "net/minecraft/network/protocol/game/ClientboundPlayerCombatPacket.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/network/PacketListener.h"

std::shared_ptr<Packet> ClientboundPlayerCombatPacket::create() {
    return std::shared_ptr<Packet>(new ClientboundPlayerCombatPacket());
}

ClientboundPlayerCombatPacket::ClientboundPlayerCombatPacket() {}

EPacketType ClientboundPlayerCombatPacket::getPacketId() {
    return EPacketType::_ClientboundPlayerCombatPacket;
}

void ClientboundPlayerCombatPacket::read(DataInputStream* input) {
    m_event = input->readInt();

    if (m_event == 1) {
        m_duration = input->readVarInt();
        m_killerId = input->readInt();
        return;
    }

    if (m_event == 2) {
        m_playerId = input->readVarInt();
        m_killerId = input->readInt();
        m_essage = readUtf(input, 0x7FFF);
    }
}

void ClientboundPlayerCombatPacket::write(DataOutputStream* output) {
    output->writeInt(m_event);

    if (m_event == 1) {
        output->writeVarInt(m_duration);
        output->writeInt(m_killerId);
        return;
    }

    if (m_event == 2) {
        output->writeVarInt(m_playerId);
        output->writeInt(m_killerId);
        writeUtf(m_essage, output);
    }
}

void ClientboundPlayerCombatPacket::handle(PacketListener* listener) {
    listener->handlePlayerCombat(shared_from_this());
}
