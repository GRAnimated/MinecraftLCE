#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class FlexiblePacket : public Packet {
public:
    void read(DataInputStream* input) override;
    void write(DataOutputStream* output) override;
    int getEstimatedSize() override;

    std::vector<std::wstring> mStrings;  // 24b
    std::vector<int> mVarints;           // 48b
    std::vector<bool> mBools;            // 72b
    std::vector<float> mFloats;          // 96b
};
