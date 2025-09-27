#include "net/minecraft/client/ui/scene/scenes/UIScene_AchievementsMenu.h"

const AwardInfo* UIScene_AchievementsMenu::GetInfo(int idx) {
    return &Awards::sAwards[idx];
}
