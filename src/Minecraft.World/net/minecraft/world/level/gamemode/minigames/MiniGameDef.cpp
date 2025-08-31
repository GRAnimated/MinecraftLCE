#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

#include "net/minecraft/client/CMinecraftApp.h"

// NON_MATCHING: TODO: implement this (now it's random stuff just to match other shit)
void MiniGameDef::SetLootSet(int lootSetId) const {
    CConsoleMinecraftApp::sInstance.SetRichPresenceContext(lootSetId, lootSetId);
}
