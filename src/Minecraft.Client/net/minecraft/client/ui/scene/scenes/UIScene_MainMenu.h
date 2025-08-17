#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Button.h"
#include "net/minecraft/core/storage/C4JStorage.h"

class UIScene_MainMenu : public UIScene {
public:
    UIScene_MainMenu(int a1, void* a2, UILayer* layer);

    bool mapElementsAndNames() override;
    void handleUnlockFullVersion() override;
    void customDraw(const char*, fuiRect*) override;
    void handleInput(int, int, bool, bool, bool, bool&) override;
    bool hasFocus(int) override;
    void handleReload() override;
    void updateComponents() override;
    void tick() override;
    void customDrawSplash(fuiRect*);

    void RunAction(int);

    static int MustSignInReturned(void*, int, C4JStorage::EMessageResult);

    void* unk2;
    UIControl_Button mButtons[8];
    UIControl mTimer;
    bool _4e8;
    bool mShowUnlockFullGame;
    bool _4ea;
    bool _4eb;
    bool _4ec;
    float mWidth;
    float mHeight;
    float mScaledWidth;
    float mScaledHeight;
    std::vector<std::wstring> mSplashes;
    std::wstring mSplashText;
    int _530;
};
