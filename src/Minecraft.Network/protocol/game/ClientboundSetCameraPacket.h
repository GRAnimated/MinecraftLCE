#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ClientboundSetCameraPacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundSetCameraPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetCameraPacket();
    ClientboundSetCameraPacket(char unk1, unsigned int unk2);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getCameraId();

private:
    int cameraId;
};
