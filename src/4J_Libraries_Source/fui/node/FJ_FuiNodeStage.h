#pragma once

#include "4J_Libraries_Source/fui/node/FJ_FuiNode.h"

class FJ_FuiNodeStage : public FJ_FuiNode {
public:
    FJ_FuiNodeStage(fuiRenderNode*);

    void getStageHeight();
    void setFocus(FJ_FuiNode*);
    void getFocus();
    void removeFocus(FJ_FuiNode*);
};
