#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Touch.h"

class UIScene_Intro : public UIScene {
public:
    UIScene_Intro(int a1, void *a2, UILayer *layer);

    std::wstring getMoviePath() override;
    bool mapElementsAndNames() override;
    ~UIScene_Intro() override;
    EUIScene getSceneType() override;
    bool hasFocus(int) override;
    void handleGainFocus(bool focused) override;
    void handleInput(int, int, bool, bool, bool, bool&) override;
    void handleReload() override;
    void handleAnimationEnd() override;
    void handleTouchInput(unsigned int, int, int, int, bool, bool, bool) override;

    void setIntroPlatform();

    int mPadding;
    bool mUnk;
    bool mSkippable;
    UIControl_Touch *mTouchToSkip;
};
