#include "net/minecraft/client/ui/scene/control/UIControl_Button.h"

#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_Button.h"
#include "fui/node/FJ_FuiNodeStage.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"

UIControl_Button::UIControl_Button() : UIControl_Base() {
    this->mEnabled = true;
}

bool UIControl_Button::setupControl(UIScene* scene, fuiRenderNode* renderNode, const std::string& name) {
    this->setSettedUp(1);
    return UIControl_Base::setupControl(scene, renderNode, name);
}

void UIControl_Button::tick() {
    UIControl_Base::tick();
    if (this->mCouldBeEnabled)
        this->setEnable(this->mEnabled, 1);
}

void UIControl_Button::ReInit() {
    UIControl::ReInit();
    this->init(this->mUIString, this->mControlID);
}

void UIControl_Button::setFocus(bool focus) {
    if (this->mFocused != focus) {
        this->mFocused = focus;

        this->mFuiRenderNode->mFuiNodeStage->asFJ_Button()->ChangeState(focus ? 1 : 2);
    }
}
