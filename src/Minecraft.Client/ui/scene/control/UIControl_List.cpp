#include "Minecraft.Client/ui/scene/control/UIControl_List.h"

UIControl_List::UIControl_List() : UIControl_Base() {}

// this is version with a lot of crap to brutly match target
void UIControl_List::addElement(eUIControlType type, int id) {
    int v6, v10 = id;
    if (id < 0)
        v6 = this->mListSize;
    else
        v6 = id;
    v10 = v6;
    this->mListSize += 1;

    int v9 = v6;
    this->mUIControlsTypes[v9] = type;
    int v8 = v10;
    this->mUIControlsStates[v8] = true;

    this->mUIControlIDs.push_back(v10);
}