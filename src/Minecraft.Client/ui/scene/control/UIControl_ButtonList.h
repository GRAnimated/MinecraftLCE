#pragma once
#include "Minecraft.Client/ui/scene/control/UIControl_List.h"
#include <string>

class UIControl_ButtonList : public UIControl_List {
public:
    UIControl_ButtonList();

    void addItem(std::wstring const&, int);
};