#pragma once
#include "Minecraft.Client/renderer/C4JRender.h"
#include "Minecraft.Client/ui/scene/UIScene.h"

class ConsoleUIController {
public:
    void updateViewportTouchOffset(C4JRender::eViewportType);
    bool IsReloadingSkin();
    int SetTooltips(unsigned int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int,
                    int, bool, bool);
    // I don't know what it sets, and it seems that there's no such a thing on WiiU (not that it's inlined or something, it's just not there at all)
    void setUnk(bool);
    void init(int screenWidth, int screenHeight);
    int SetAchievementUnlocked();
    void TouchBoxRebuild(UIScene*);
    bool AnimateKeyPress(int, int, bool, bool, bool);
};

extern ConsoleUIController gConsoleUIController;