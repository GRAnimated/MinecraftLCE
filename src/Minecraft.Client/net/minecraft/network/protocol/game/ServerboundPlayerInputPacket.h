#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include "types.h"

class ServerboundPlayerInputPacket : public Packet,
                                     public std::enable_shared_from_this<ServerboundPlayerInputPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundPlayerInputPacket();

    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    int getEstimatedSize() override;

private:
    float m_xxa;
    float m_zza;
    bool m_isJumping;
    bool m_isSneaking;
};

ASSERT_SIZEOF(ServerboundPlayerInputPacket, 0x38)
