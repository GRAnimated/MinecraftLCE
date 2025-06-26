#pragma once

#include "../event/FJ_EventListener.h"
#include "../event/FJ_Event.h"
#include "../fuiRenderNodeStage.h"
#include <vector>

class fuiRenderNode;
class FJ_FuiNodeStage;
class UIScene;
class FJ_Base;
class FJ_List;
class FJ_List_MenuButton;
class FJ_List_ListButton;
class FJ_List_ListButtonPlayerList;
class FJ_Button;
class FJ_Document;

class FJ_FuiNode {
public:
    FJ_FuiNode(fuiRenderNode*);

    virtual ~FJ_FuiNode();
    virtual void ASConstructor();
    virtual void setX(float);
    virtual void setY(float);
    virtual void setHeight(float);
    virtual void setVisible(bool);
    virtual int getType();

    void setScaleX(float sX);
    void setScaleY(float sY);

    int getTabIndex();
    FJ_FuiNodeStage* getStage();

    void setCallbackScene(UIScene*);
    void dispatchEvent(FJ_Event* event);

    FJ_Base* asFJ_Base();
    FJ_List* asFJ_List();
    FJ_List_MenuButton* asFJ_List_MenuButton();
    FJ_List_ListButton* asFJ_List_ListButton();
    FJ_List_ListButtonPlayerList* asFJ_List_ListButtonPlayerList();
    FJ_Document* asFJ_Document();
    FJ_Button* asFJ_Button();

    bool isFJ_Document();

    fuiRenderNode* mRenderNode;
    int mTabIndex;
    std::vector<FJ_EventListener> mEventListeners;
    UIScene* mCallbackScene;
};
