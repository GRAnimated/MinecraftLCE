#include "net/minecraft/client/ui/scene/scenes/UIScene_Intro.h"

#include "fui/fuiFile.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Touch.h"

// NON_MATCHING | Score: 935 (lower is better)
UIScene_Intro::UIScene_Intro(int a1, void* a2, UILayer* layer) : UIScene(a1, layer) {
    this->initialiseMovie();
    this->m_unk = false;
    this->m_skippable = false;
    this->setIntroPlatform();
    this->m_touchToSkip->init(0);
}

std::wstring UIScene_Intro::getMoviePath() {
    return L"Intro";
}

// NON_MATCHING | Score: 1139 (lower is better)
bool UIScene_Intro::mapElementsAndNames() {
    UIScene::mapElementsAndNames();

    this->m_touchToSkip->setupControl(this, this->getFuiFile()->getRootNode(), "TouchToSkip");
    this->m_uiControls.push_back(this->m_touchToSkip);

    return true;
}

EUIScene UIScene_Intro::getSceneType() {
    return EUIScene_Intro;
}

bool UIScene_Intro::hasFocus(int i) {
    return this->m_focusRelated;
}

void UIScene_Intro::handleGainFocus(bool focused) {
    if (this->m_skippable)
        gConsoleUIController.NavigateToScene(0, EUIScene_MainMenu, nullptr, static_cast<EUILayer>(6),
                                             static_cast<EUIGroup>(6));
}

void UIScene_Intro::handleReload() {
    setIntroPlatform();
}
