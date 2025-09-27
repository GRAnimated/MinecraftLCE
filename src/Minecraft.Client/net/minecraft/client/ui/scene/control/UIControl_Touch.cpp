#include "UIControl_Touch.h"

bool UIControl_Touch::setupControl(UIScene* scene, fuiRenderNode* node, const std::string& name) {
    this->setSettedUp(20);
    return UIControl_Base::setupControl(scene, node, name);
}