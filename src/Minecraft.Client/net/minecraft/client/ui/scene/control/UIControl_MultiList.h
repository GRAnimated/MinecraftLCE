#include "net/minecraft/client/ui/scene/control/UIControl_List.h"

class UIControl_MultiList : public UIControl_List {
public:
    void AddNewSlider(const std::wstring& text, int id, int minValue, int maxValue, int defaultVal, bool unk,
                      int incr, int incr2);
};