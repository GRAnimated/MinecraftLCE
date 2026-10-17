#include "net/minecraft/client/ui/scene/control/UIControl_Label.h"

UIControl_Label::UIControl_Label() {
    m_byte68 = true;
}

bool UIControl_Label::setupControl(UIScene* scene, fuiRenderNode* node, const std::string& name) {
    setSettedUp(8);
    return UIControl_Base::setupControl(scene, node, name);
}

void UIControl_Label::ReInit() {
    UIControl::ReInit();
    if (m_byte68)
        init(m_uiString);
}
