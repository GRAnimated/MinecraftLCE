#pragma once

#include "net/minecraft/client/ui/scene/control/UIControl_Base.h"
#include <unordered_map>
#include <vector>

class UIControl_List : public UIControl_Base {
public:
    class GenericPendingUpdate {
    public:
        virtual void nullsub_795();
        virtual ~GenericPendingUpdate();
        virtual void virtual_void_0() = 0;
    };

    UIControl_List();
    ~UIControl_List();

    void addElement(eUIControlType, int);
    void init(int);
    void setCurrentSelection(int, bool, bool);

    std::vector<UIControl_List::GenericPendingUpdate*> m_genericPendingUpdates;
    std::vector<int> m_uiControlIDs;
    int m_dword98 = 0;
    int m_listSize = 0;
    std::unordered_map<unsigned int, eUIControlType> m_uiControlsTypes;
    std::unordered_map<unsigned int, bool> m_uiControlsStates;
};
