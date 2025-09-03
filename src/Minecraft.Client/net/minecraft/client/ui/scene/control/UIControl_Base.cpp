#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"

UIControl_Base::UIControl_Base() : UIControl() {
    this->mBoolIdk2 = false;
    this->mControlID = 0;
}

UIControl_Base::~UIControl_Base() {}

bool UIControl_Base::setupControl(UIScene* scene, fuiRenderNode* renderNode, const std::string& name) {
    return UIControl::setupControl(scene, renderNode, name);
}

void UIControl_Base::tick() {
    UIControl::tick();
    if (this->mUIString.needsUpdating() || this->mBoolIdk2) {
        this->setLabel(this->mUIString, true, true);
        this->mUIString.setUpdated();
    }
}

bool UIControl_Base::hasFocus() {
    return this->mParentUIScene->controlHasFocus(this);
}

// uhhh, maybe not
// void UIControl_Base::setLabel(UIString, bool, bool) {}
// void UIControl_Base::setAllPossibleLabels(int, uint, wchar_t* [256]) {}
