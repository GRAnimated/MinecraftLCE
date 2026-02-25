#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class FlexiblePacket : public Packet {
public:
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    int getEstimatedSize() override;

    std::vector<std::wstring> m_strings;  // 24b
    std::vector<int> m_varints;           // 48b
    std::vector<bool> m_bools;            // 72b
    std::vector<float> m_floats;          // 96b
};
