#pragma once

#include "fui/node/FJ_FuiNode.h"

class FJ_FuiNodeStage : public FJ_FuiNode {
public:
    FJ_FuiNodeStage(fuiRenderNode*);

    float getStageWidth();
    float getStageHeight();
    void setFocus(FJ_FuiNode* node);
    FJ_FuiNode* getFocus();
    void removeFocus(FJ_FuiNode* node);

    FJ_FuiNode* mFocusedNode;
    void* mIdk;
};
