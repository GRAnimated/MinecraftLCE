#include "net/minecraft/client/ui/scene/control/UIControl_MultiList.h"

UIControl_MultiList::UIControl_MultiList() {}

// name guessed
bool UIControl_MultiList::setupControl(UIScene* scene, fuiRenderNode* node, const std::string& name) {
    setSettedUp(28);
    return UIControl_List::setupControl(scene, node, name);
}
