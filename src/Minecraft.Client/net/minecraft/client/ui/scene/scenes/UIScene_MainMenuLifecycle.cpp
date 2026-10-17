#include "UIScene_MainMenu.h"
#include "net/minecraft/client/ui/scene/UILayer.h"
#include <type_traits>

// 0x71005d9034: remove both components before destroying controls and UIScene.
UIScene_MainMenu::~UIScene_MainMenu() {
    m_uiLayer->removeComponent(EUIComponent_Panorama);
    m_uiLayer->removeComponent(EUIComponent_Logo);
}

// 0x71005d9574, virtual slot 7 of the original main-menu vtable.
std::wstring UIScene_MainMenu::getMoviePath() {
    return L"MainMenu";
}

// 0x71006655e8, virtual slot 11 of the original main-menu vtable.
EUIScene UIScene_MainMenu::getSceneType() {
    return EUIScene_MainMenu;
}

static_assert(!std::is_abstract<UIScene_MainMenu>::value,
              "The original main-menu scene must be instantiable");
