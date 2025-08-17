#include "net/minecraft/client/ui/scene/scenes/UIScene_HowToPlayMenu.h"

#include "fui/fuiFile.h"
#include "fui/fuiRenderNode.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/client/ui/scene/UILayer.h"
#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/sounds/SoundEvent.h"
#include <cstdint>
#include <string>

unsigned int dword_7101107860[30]{
    StringIDs::WhatSNew,        StringIDs::Basics,
    StringIDs::Multiplayer,     StringIDs::Hud,
    StringIDs::BattleMiniGame,  StringIDs::TumbleMiniGame,
    StringIDs::GlideMiniGame_1, StringIDs::CreativeMode,
    StringIDs::Inventory_1,     StringIDs::Chests,
    StringIDs::Crafting_1,      StringIDs::Furnace_1,
    StringIDs::Dispenser_1,     StringIDs::Brewing_2,
    StringIDs::Enchantment,     StringIDs::Anvil,
    StringIDs::FarmingAnimals,  StringIDs::BreedingAnimals,
    StringIDs::Trading,         StringIDs::Horses,
    StringIDs::Beacons,         StringIDs::Fireworks,
    StringIDs::Banners,         StringIDs::Hoppers,
    StringIDs::Droppers,        StringIDs::NetherPortal,
    StringIDs::TheEnd_2,        StringIDs::EndCities,
    StringIDs::Elytra,          StringIDs::HostAndPlayerOptions,
};

int dword_71011078D8[30]{0,    1,    2,    3,    4,    5,    6,    7,    8,    9,
                         0xC,  0xE,  0xF,  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                         0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};

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
    gConsoleUIController.SetTooltips(this->mPadID, StringIDs::Select, StringIDs::Back_1, -1, -1, -1, -1, -1,
                                     -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0);
}

void UIScene_HowToPlayMenu::updateComponents() {
    if (!Minecraft::GetInstance()->mLevel) {
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Panorama, true);
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Logo, true);
    } else {
        this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Panorama, false);
        if (CConsoleMinecraftApp::sInstance.GetLocalPlayerCount() == 1)
            this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Logo, true);
        else
            this->mUILayer->showComponent(this->mPadID, EUIScene::UIComponent_Logo, false);
    }
}

void UIScene_HowToPlayMenu::handleReload() {
    for (int index = 0; index < 30; ++index) {
        const wchar_t* str = L10N::GetString(dword_7101107860[index]);
        this->uicontrol_list110.addItem(str, index);
    }

    this->uicontrol_list110.setCurrentSelection(this->dword200, false, true);
    this->doHorizontalResizeCheck();
    gConsoleUIController.TouchBoxRebuild(this);
}

void UIScene_HowToPlayMenu::handleInput(int a2, int key, bool a4, bool a5, bool a6, bool& a7) {
    gConsoleUIController.AnimateKeyPress(this->mPadID, key, a4, a5, a6);

    if (key == 4 || key == 5 || key == 8 || key == 9) {
        this->sendInputToMovie(key, false, a5, false);
        return;
    }

    if (key == 20) {
        this->sendInputToMovie(key, false, a5, false);
        return;
    }

    if (key == 21 && a5) {
        this->navigateBack();
        return;
    }
}

void UIScene_HowToPlayMenu::handlePress(int a2, int a3) {
    if (!a2) {
        this->dword200 = a3;
        gConsoleUIController.PlayUISFX(SoundEvent::UI_PRESS);
        gConsoleUIController.NavigateToScene(
            this->mPadID, EUIScene::UIScene_HowToPlay,
            // idk why they do this int16_t cast, or maybe there's something wrong with my code but it
            //                                                                    matches so I'm happy
            (unsigned int*)(0x80000000 | ((dword_71011078D8[a3] << 16) | static_cast<int16_t>(this->mPadID))),
            (EUILayer)6, (EUIGroup)6);
    }
}

bool UIScene_HowToPlayMenu::mapElementsAndNames() {
    fuiRenderNode* node = this->getFuiFile()->getRootNode();
    this->uicontrol_list110.setupControl(this, node, "HowToList");
    this->mUIControls.push_back(&this->uicontrol_list110);
    return true;
}

EUIScene UIScene_HowToPlayMenu::getSceneType() {
    return EUIScene::UIScene_HowToPlayMenu;
}
