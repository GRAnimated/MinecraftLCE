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

    void* m_unk2;
    UIControl_Button m_buttons[8];
    UIControl m_timer;
    bool m_4e8;
    bool m_showUnlockFullGame;
    bool m_4ea;
    bool m_4eb;
    bool m_4ec;
    float m_width;
    float m_height;
    float m_scaledWidth;
    float m_scaledHeight;
    std::vector<std::wstring> m_splashes;
    std::wstring m_splashText;
    int m_530;
};
