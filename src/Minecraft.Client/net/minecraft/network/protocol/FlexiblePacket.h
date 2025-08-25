#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class FlexiblePacket : public Packet {
public:
    char fill[0x60];
};
