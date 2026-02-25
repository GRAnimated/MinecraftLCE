#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <string>

class Item;

class ClientboundPlayerCombatPacket : public Packet,
                                      public std::enable_shared_from_this<ClientboundPlayerCombatPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundPlayerCombatPacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int m_event;
    int m_playerId;
    int m_killerId;
    int m_duration;
    std::wstring m_essage;
};
