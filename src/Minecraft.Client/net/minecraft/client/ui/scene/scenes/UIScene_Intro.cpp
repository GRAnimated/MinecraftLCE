#include "UIScene_Intro.h"
#include "fui/fuiFile.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Touch.h"

UIScene_Intro::UIScene_Intro(int a1, void* a2, UILayer* layer) : UIScene(a1, layer) {
    this->initialiseMovie();
    this->mUnk = false;
    this->mSkippable = false;
    this->setIntroPlatform();
    this->mTouchToSkip->init(0);
}

std::wstring UIScene_Intro::getMoviePath() {
    return L"Intro";
}
bool UIScene_Intro::mapElementsAndNames() {
    UIScene::mapElementsAndNames();

    this->mTouchToSkip->setupControl(this, this->getFuiFile()->getRootNode(), "TouchToSkip");
    this->mUIControls.push_back(this->mTouchToSkip);

    return true;
}

EUIScene UIScene_Intro::getSceneType() {
    return EUIScene_Intro;
}

bool UIScene_Intro::hasFocus(int i) {
    return this->mFocusRelated;
}

void UIScene_Intro::handleGainFocus(bool focused) {
    if (this->mSkippable)
        gConsoleUIController.NavigateToScene(0, EUIScene_MainMenu, nullptr, static_cast<EUILayer>(6),
                                             static_cast<EUIGroup>(6));
}

void UIScene_Intro::handleReload() {
    setIntroPlatform();
}
