#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Button.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Label.h"
#include <cstdint>

class UIScene_DeathMenu : public UIScene {
public:
    UIScene_DeathMenu(int, void*, UILayer*);

    std::wstring getMoviePath() override;
    bool mapElementsAndNames() override;
    ~UIScene_DeathMenu() override;
    EUIScene getSceneType() override;
    void tick() override;
    void updateTooltips() override;
    void handleTimerComplete(int) override;
    void handleInput(int, int, bool, bool, bool, bool&) override;
    void handlePress(int, int) override;

    char gap108[4];
    bool byte10C;
    bool bool10D;
    bool bool10E;
    UIControl_Button mRespawnButton;
    UIControl_Button mExitGameButton;
    UIControl_Label mTitleLabel;
    UIControl_Label mDeathMessageLabel;
    UIControl_Label mExtraMessageLabel;
};