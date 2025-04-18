#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundContainerClosePacket : public Packet,
                                        public std::enable_shared_from_this<ServerboundContainerClosePacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundContainerClosePacket();
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int containerId;
};
