#pragma once

#include "../Packet.h"

class ServerboundPlayerActionPacket : public Packet {
public:
    int getAction();  // TODO: Find return type
};
