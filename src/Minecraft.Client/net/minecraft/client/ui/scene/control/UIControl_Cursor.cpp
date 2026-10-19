#include "net/minecraft/client/ui/scene/control/UIControl_Cursor.h"

UIControl_Cursor::UIControl_Cursor() {}

// name guessed
bool UIControl_Cursor::setupControl(UIScene* scene, fuiRenderNode* node, const std::string& name) {
    setSettedUp(3);
    return UIControl_Base::setupControl(scene, node, name);
}
