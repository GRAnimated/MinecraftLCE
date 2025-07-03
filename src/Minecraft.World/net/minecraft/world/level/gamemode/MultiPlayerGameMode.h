#pragma once

#include "net/minecraft/world/level/gamemode/GameMode.h"

class Tutorial;

class MultiPlayerGameMode : public GameMode {
public:
    Tutorial* getTutorial();
};
