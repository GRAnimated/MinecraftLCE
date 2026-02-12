#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/network/protocol/Packet.h"

class ServerboundAcceptTeleportationPacket
    : public Packet,
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
    int m_id;
};
