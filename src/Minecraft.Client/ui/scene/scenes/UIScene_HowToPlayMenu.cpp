#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/resources/L10N.h"
#include "Minecraft.Client/ui/ConsoleUIController.h"
#include "Minecraft.Client/ui/scene/UILayer.h"
#include "Minecraft.Client/ui/scene/UIScene.h"
#include "Minecraft.Client/ui/scene/control/UIControl_List.h"
#include "Minecraft.Client/ui/scene/scenes/UIScene_HowToPlayMenu.h"
#include <string>

unsigned int dword_7101107860[30]{
    0xAD78575,  0x4E09B239, 0xA1BFE39A, 0xFE7EBCC1, 0x665939C3, 0xF451CA88, 0x1A5444F1, 0x5D603CEB,
    0xA89BCC3A, 0x9BFE8C42, 0xF8FE2A8A, 0xAE9EC2E0, 0xDC9BF801, 0x95EA9872, 0x6C8ABC81, 0x55175D0C,
    0xC5E8DA45, 0x68B19531, 0xCCD04093, 0xB54D580,  0x74C4B1E7, 0xB9C0E92,  0xC48A1DCF, 0x97D17F3B,
    0xD554B135, 0x7FF49BC,  0x90785456, 0x670457B6, 0x3FE78B47, 0xF3D9C148,
};

UIScene_HowToPlayMenu::UIScene_HowToPlayMenu(int padID, void* unk_unused, UILayer* uiLayer)
    : UIScene(padID, uiLayer) {
    this->initialiseMovie();
    this->uicontrol_list110.init(0);

    for (int i = 0LL; i != 30; ++i) {
        const wchar_t* v7 = L10N::GetString(dword_7101107860[i]);
        this->uicontrol_list110.addItem(v7, i);
    }

    this->doHorizontalResizeCheck();
    this->dword200 = 0;
    gConsoleUIController.TouchBoxRebuild(this);
}

std::wstring UIScene_HowToPlayMenu::getMoviePath() {
    if (CConsoleMinecraftApp::sInstance.GetLocalPlayerCount() >= 2)
        return L"HowToPlayMenuSplit";
    else
        return L"HowToPlayMenu";
}

void UIScene_HowToPlayMenu::updateTooltips() {
    gConsoleUIController.SetTooltips(this->mPadID, -1922882579, 1332465502, -1, -1, -1, -1, -1, -1, -1, -1,
                                     -1, -1, -1, -1, -1, -1, 0, 0);
}

// NON_MATCHING: somecrap with if, logic is the same
void UIScene_HowToPlayMenu::updateComponents() {
    if (!Minecraft::GetInstance()->mLevel)
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Panorama, true);
    else
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Panorama, false);

    if (CConsoleMinecraftApp::sInstance.GetLocalPlayerCount() == 1)
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Logo, true);
    else
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Logo, false);
}

// NON_MATCHING: idk personally
void UIScene_HowToPlayMenu::handleReload() {
    int i = 0;
    do {
        const wchar_t* v7 = L10N::GetString(dword_7101107860[i]);
        this->uicontrol_list110.addItem(v7, i);
        ++i;
    } while (i != 30);

    this->uicontrol_list110.setCurrentSelection(this->dword200, false, true);
    this->doHorizontalResizeCheck();
    gConsoleUIController.TouchBoxRebuild(this);
}
