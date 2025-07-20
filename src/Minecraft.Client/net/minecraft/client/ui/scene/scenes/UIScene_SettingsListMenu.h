#pragma once

#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_MultiList.h"

class UIScene_SettingsListMenu : public UIScene {
public:
    char gap108[8];
    UIControl_MultiList mSettingsList;
    char gap200[112];
    int mSettingsTab;
    char mInLevel;
    char mPlayerPad;
    char mPlayerHost;
    char byte277;
    char gap278[9216];
    wchar_t wchar2678;
    char gap267C[1020];
    wchar_t wchar2A78;
    char gap2A7C[1020];
    wchar_t wchar2E78;
    char gap2E7C[1020];
    wchar_t wchar3278;
};
