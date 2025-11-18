#pragma once

#include "fui/node/control/slider/FJ_Slider.h"

#include <string>

class fuiRenderNode;
class FJ_FuiNode;

/// STUB CLASS FOR FJ_Factory::initialise
class FJ_Slider_Small : public FJ_Slider {
public:
    static std::string sName;

    static FJ_FuiNode* Create(fuiRenderNode*);
};
