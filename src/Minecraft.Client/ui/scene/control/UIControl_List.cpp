#include "Minecraft.Client/ui/scene/control/UIControl_List.h"

UIControl_List::UIControl_List() : UIControl_Base() {}

// NON_MATCHING: idk, the for loop is constructed weirdly
UIControl_List::~UIControl_List() {
    for (GenericPendingUpdate* update : mGenericPendingUpdates) {
        delete update;
    }
}

void UIControl_List::addElement(eUIControlType type, int id) {
    if (id < 0)
        id = this->mListSize;

    this->mListSize += 1;

    this->mUIControlsTypes[id] = type;
    this->mUIControlsStates[id] = true;

    this->mUIControlIDs.push_back(id);
}