#pragma once

#include "Minecraft.World/level/gamemode/GameMode.h"

class Tutorial;

class MultiPlayerGameMode : public GameMode {
public:
    Tutorial* getTutorial();
};