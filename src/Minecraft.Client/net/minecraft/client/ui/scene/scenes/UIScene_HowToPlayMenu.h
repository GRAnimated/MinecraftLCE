#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_ButtonList.h"

class UIScene_HowToPlayMenu : public UIScene {
    UIScene_HowToPlayMenu(int, void*, UILayer*);

    std::wstring getMoviePath() override;
    void updateTooltips() override;
    void updateComponents() override;
    void handleReload() override;
    void handleInput(int, int, bool, bool, bool, bool&) override;
    void handlePress(int, int) override;
    bool mapElementsAndNames() override;
    EUIScene getSceneType() override;

    void* qword108;
    UIControl_ButtonList uicontrol_list110;
    int dword200;
};
