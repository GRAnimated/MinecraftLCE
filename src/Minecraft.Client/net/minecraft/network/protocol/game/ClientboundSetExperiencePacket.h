#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ClientboundSetExperiencePacket : public Packet,
                                       public std::enable_shared_from_this<ClientboundSetExperiencePacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundSetExperiencePacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    bool canBeInvalidated() override;
    bool isInvalidatedBy(std::shared_ptr<Packet> packet) override;

    float getExperienceProgress();
    int getTotalExperience();
    int getExperienceLevel();

private:
    float experienceProgress;
    int experienceLevel;
    int totalExperience;
};
