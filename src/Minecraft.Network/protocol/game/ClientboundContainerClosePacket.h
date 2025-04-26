#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ClientboundContainerClosePacket : public Packet,
                                        public std::enable_shared_from_this<ClientboundContainerClosePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundContainerClosePacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int containerId;
};
