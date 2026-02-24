#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "net/minecraft/world/entity/Entity.h"

class ClientboundEntityEventPacket : public Packet,
                                     public std::enable_shared_from_this<ClientboundEntityEventPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundEntityEventPacket();
    ClientboundEntityEventPacket(std::shared_ptr<Entity> entity, unsigned char eventId, int data);
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

    int getEntityId();
    unsigned char getEventId();
    int getData();

private:
    int m_entityId;
    unsigned char m_eventId;
    int m_data;
};
