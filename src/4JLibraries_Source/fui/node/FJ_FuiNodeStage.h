#pragma once

#include "fui/node/FJ_FuiNode.h"

class FJ_FuiNodeStage : public FJ_FuiNode {
public:
    FJ_FuiNodeStage(fuiRenderNode*);

    void getStageHeight();
    void setFocus(FJ_FuiNode*);
    void getFocus();
    void removeFocus(FJ_FuiNode*);

    void* mIdk;
    FJ_FuiNode* mfocusedFJ_FuiNode;
};
