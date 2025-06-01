#pragma once

#include "Minecraft.World/level/gamemode/CommonMasterGameMode.h"

class ClientMasterGameMode : public CommonMasterGameMode {
public:
    bool IsRoundRestarting();
};