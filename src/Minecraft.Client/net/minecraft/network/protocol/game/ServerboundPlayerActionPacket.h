#pragma once

#include "net/minecraft/network/protocol/Packet.h"

class ServerboundPlayerActionPacket : public Packet {
public:
    int getAction();  // TODO: Find return type
};
