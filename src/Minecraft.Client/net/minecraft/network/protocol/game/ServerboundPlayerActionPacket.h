#pragma once

#include "Minecraft.Network/protocol/Packet.h"

class ServerboundPlayerActionPacket : public Packet {
public:
    int getAction();  // TODO: Find return type
};
