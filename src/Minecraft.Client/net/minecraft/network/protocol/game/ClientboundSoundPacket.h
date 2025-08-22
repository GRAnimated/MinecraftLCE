#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class SoundEvent;

class ClientboundSoundPacket : public Packet, public std::enable_shared_from_this<ClientboundSoundPacket> {
public:
    static std::shared_ptr<Packet> create();

    enum ESoundInstances {
        _0 = 0,
        _1 = 1,
    };

    ClientboundSoundPacket(ESoundInstances, const SoundEvent*, float, float, bool, int);

    ~ClientboundSoundPacket() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;

    void* size[6];
};
