#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_List.h"

class UIControl_MultiList : public UIControl_List {
public:
    UIControl_MultiList();

    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
    void setAllPossibleLabels(int, uint, wchar_t* [256]) override;

    void AddNewSlider(const std::wstring& text, int id, int minValue, int maxValue, int defaultVal, bool unk,
                      int incr, int incr2);
};

static_assert(sizeof(UIControl_MultiList) == 0xf0, "UIControl_MultiList Switch layout");
