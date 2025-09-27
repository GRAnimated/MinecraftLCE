#pragma once

#include "Awards.h"
#include "net/minecraft/client/ui/scene/UIScene.h"

class UIScene_AchievementsMenu : public UIScene {
public:
    static const AwardInfo *GetInfo(int idx);
};

