#include "net/minecraft/client/ui/scene/control/UIControl_ButtonList.h"

UIControl_ButtonList::UIControl_ButtonList() : UIControl_List() {}

bool UIControl_ButtonList::setupControl(UIScene* scene, fuiRenderNode* node, const std::string& name) {
    setSettedUp(22);
    return UIControl_List::setupControl(scene, node, name);
}
