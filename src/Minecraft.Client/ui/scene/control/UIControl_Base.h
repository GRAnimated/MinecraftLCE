#pragma once

#include "Minecraft.Client/ui/scene/control/UIControl.h"
#include "Minecraft.Client/ui/scene/control/UIString.h"

class UIControl_Base : public UIControl {
public:
    UIControl_Base();

    UIString mUIString;
};