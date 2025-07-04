#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundContainerButtonClickPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundContainerButtonClickPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundContainerButtonClickPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getContainerId();
    int getButtonId();

private:
    int containerId;
    int buttonId;
};
