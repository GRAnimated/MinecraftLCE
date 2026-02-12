#pragma once

#include "net/minecraft/network/protocol/Packet.h"
#include <memory>

class ClientboundAwardStatPacket : public Packet,
                                   public std::enable_shared_from_this<ClientboundAwardStatPacket> {
public:
    static std::shared_ptr<Packet> create();

    ClientboundAwardStatPacket();
    ClientboundAwardStatPacket(int stat, int unk);
    ~ClientboundAwardStatPacket() override;
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;
    bool isAync() override;

    arrayWithLength<unsigned char> getParamData();

private:
    int m_stat;
    arrayWithLength<unsigned char> m_data;
};
