#pragma once

#include "UIControl_Base.h"

class UIControl_Touch : public UIControl_Base {
public:
    void init(int);

    bool setupControl(UIScene *scene, fuiRenderNode *node, const std::string &name) override;
};
