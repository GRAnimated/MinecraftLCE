#pragma once

#include "../Packet.h"

class ServerboundClientCommandPacket : public Packet,
                                       public std::enable_shared_from_this<ServerboundClientCommandPacket> {
public:
    static std::shared_ptr<Packet> create();

    ServerboundClientCommandPacket();
    int getEstimatedSize() override;
    EPacketType getPacketId() override;
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    void handle(PacketListener* listener) override;

private:
    int commandId;
};
