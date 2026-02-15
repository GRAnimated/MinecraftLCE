#include "net/minecraft/client/ui/scene/control/UIControl_List.h"

UIControl_List::UIControl_List() : UIControl_Base() {}

// NON_MATCHING: idk, the for loop is constructed weirdly
UIControl_List::~UIControl_List() {
    for (GenericPendingUpdate* update : m_genericPendingUpdates) {
        delete update;
    }
}

void UIControl_List::addElement(eUIControlType type, int id) {
    if (id < 0)
        id = this->m_listSize;

    this->m_listSize += 1;

    this->m_uiControlsTypes[id] = type;
    this->m_uiControlsStates[id] = true;

    this->m_uiControlIDs.push_back(id);
}
