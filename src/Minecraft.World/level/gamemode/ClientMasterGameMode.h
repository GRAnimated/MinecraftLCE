#pragma once

#include "types.h"
#include "Minecraft.World/level/gamemode/CommonMasterGameMode.h"

class ClientMasterGameMode : public CommonMasterGameMode {
public:
    ClientMasterGameMode();

    bool IsRoundRestarting();

    unsigned char size[0x2E0];
};

ASSERT_SIZEOF(ClientMasterGameMode, 0x2E0)
