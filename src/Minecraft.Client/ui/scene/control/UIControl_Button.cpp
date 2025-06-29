#include "4J_Libraries_Source/fui/fuiRenderNode.h"
#include "4J_Libraries_Source/fui/node/FJ_FuiNodeStage.h"
#include "Minecraft.Client/ui/scene/control/UIControl.h"
#include "Minecraft.Client/ui/scene/control/UIControl_Base.h"
#include "Minecraft.Client/ui/scene/control/UIControl_Button.h"
#include "../../../../4J_Libraries_Source/fui/node/control/FJ_Button.h"

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