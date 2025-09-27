#pragma once

#include "types.h"

class GameSettings {
public:
    static void ClearGameSettingsChangedFlag(int pad);
    static void ApplyGameSettingsChanged(int pad);
    static void SetDefaultActionMapping(uchar, int, uchar);
    static int OldProfileVersionCallback(void*, unsigned char*, unsigned short, int);
};
