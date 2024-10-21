#pragma once

#include <vector>
#include "4J_Libraries_Source/fui/node/FJ_EventListener.h"

class fuiRenderNode;
class FJ_FuiNodeStage;
class UIScene;

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

    int getTabIndex();
    FJ_FuiNodeStage* getStage();

    void setCallbackScene(UIScene*);

    fuiRenderNode* mRenderNode;
    int mTabIndex;
    std::vector<FJ_EventListener> mEventListeners;
    UIScene* mCallbackScene;
};
