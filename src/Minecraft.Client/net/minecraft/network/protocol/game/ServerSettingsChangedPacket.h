#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerSettingsChangedPacket : public Packet,
                                       public std::enable_shared_from_this<ServerSettingsChangedPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerSettingsChangedPacket();
    ServerSettingsChangedPacket(char unk1, unsigned int unk2);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    char dword18;
    unsigned int dword1C;
};
