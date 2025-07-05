#pragma once

#include "Minecraft.Core/BlockPos.h"
#include "Minecraft.Core/Direction.h"
#include "Minecraft.Network/protocol/Packet.h"

class ServerboundAcceptTeleportationPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundAcceptTeleportationPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundAcceptTeleportationPacket();
    ServerboundAcceptTeleportationPacket(int id);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getId();

private:
    int mId;
};
