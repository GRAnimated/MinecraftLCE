#pragma once

#include "types.h"

// TODO: Go through UIScenes and grab those
enum eGameSetting { eGameSetting_CustomSkinAnimation = 25 };

class GameSettings {
public:
    static void ClearGameSettingsChangedFlag(int pad);
    static void ApplyGameSettingsChanged(int pad);
    static void SetDefaultActionMapping(uchar, int, uchar);
    static int OldProfileVersionCallback(void*, unsigned char*, unsigned short, int);
    static int GetGameSettings(eGameSetting);
};
