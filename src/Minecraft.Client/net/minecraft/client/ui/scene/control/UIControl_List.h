#pragma once
#include "Minecraft.Client/ui/scene/control/UIControl_Base.h"
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

    std::vector<UIControl_List::GenericPendingUpdate*> mGenericPendingUpdates;
    std::vector<int> mUIControlIDs;
    int dword98 = 0;
    int mListSize = 0;
    std::unordered_map<unsigned int, eUIControlType> mUIControlsTypes;
    std::unordered_map<unsigned int, bool> mUIControlsStates;
};