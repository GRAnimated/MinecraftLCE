#include "net/minecraft/world/food/FoodConstants.h"

#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

float FoodConstants::ExhaustionAttack() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionAttack(0.1);
        }
    }
    return 0.1;
}

float FoodConstants::ExhaustionDrop() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionDrop(4);
        }
    }
    return 4;
}

int FoodConstants::ExhaustionHeal() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionHeal(6);
        }
    }
    return 6;
}

float FoodConstants::ExhaustionIdle() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionIdle(0);
        }
    }
    return 0;
}

float FoodConstants::ExhaustionJump() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionJump(0.05);
        }
    }
    return 0.05;
}

float FoodConstants::ExhaustionMine() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionMine(0.005);
        }
    }
    return 0.005;
}

float FoodConstants::ExhaustionSneak() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionSneak(0);
        }
    }
    return 0;
}

float FoodConstants::ExhaustionSprint() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionSprint(0.1);
        }
    }
    return 0.1;
}

float FoodConstants::ExhaustionSprintJump() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionSprintJump(0.2);
        }
    }
    return 0.2;
}

float FoodConstants::ExhaustionSwim() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionSwim(0.01);
        }
    }
    return 0.01;
}

float FoodConstants::ExhaustionWalk() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getExhaustionWalk(0);
        }
    }
    return 0;
}

int FoodConstants::HealLevel() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getHealLevel(18);
        }
    }
    return 18;
}

int FoodConstants::HealthTickCount() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getHealthTickCount(80);
        }
    }
    return 80;
}

int FoodConstants::HealthTickCountSaturated() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getHealthTickCountSaturated(10);
        }
    }
    return 10;
}

int FoodConstants::MaxFood() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getMaxFood(20);
        }
    }
    return 20;
}

float FoodConstants::MaxSaturation() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getMaxSaturation(20);
        }
    }
    return 20;
}

float FoodConstants::SprintLevel() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getSprintLevel(6);
        }
    }
    return 6;
}

float FoodConstants::StartSaturation() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getStartSaturation(5);
        }
    }
    return 5;
}

int FoodConstants::StarveLevel() {
    Minecraft* minecraft = Minecraft::GetInstance();
    if (minecraft != nullptr) {
        MiniGameDef* miniGame = minecraft->GetMiniGame();
        if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
            return miniGame->getStarveLevel(0);
        }
    }
    return 0;
}
