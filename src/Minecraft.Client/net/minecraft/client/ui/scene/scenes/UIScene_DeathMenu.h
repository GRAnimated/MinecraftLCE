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

    char m_gap108[4];
    bool m_byte10C;
    bool m_bool10D;
    bool m_bool10E;
    UIControl_Button m_respawnButton;
    UIControl_Button m_exitGameButton;
    UIControl_Label m_titleLabel;
    UIControl_Label m_deathMessageLabel;
    UIControl_Label m_extraMessageLabel;
};
