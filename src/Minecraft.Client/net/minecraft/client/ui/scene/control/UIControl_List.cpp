#include "Minecraft.Client/ui/scene/control/UIControl_List.h"

UIControl_List::UIControl_List() : UIControl_Base() {}

void UIControl_List::addElement(eUIControlType type, int id) {
    if (id < 0)
        id = this->mListSize;

    this->mListSize += 1;

    this->mUIControlsTypes[int(id)] = type;
    this->mUIControlsStates[int(id)] = true;

    this->mUIControlIDs.push_back(id);
}