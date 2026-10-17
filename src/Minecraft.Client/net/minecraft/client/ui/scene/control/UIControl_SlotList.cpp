#include "net/minecraft/client/ui/scene/control/UIControl_SlotList.h"

UIControl_SlotList::UIControl_SlotList() {
    m_dword68 = -1;
}

bool UIControl_SlotList::setupControl(UIScene* scene, fuiRenderNode* node, const std::string& name) {
    setSettedUp(16);
    bool found = UIControl_Base::setupControl(scene, node, name);
    m_dword68 = 0;
    return found;
}

void UIControl_SlotList::ReInit() {
    UIControl::ReInit();
    m_dword68 = -1;
}
