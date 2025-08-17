#pragma once

#include "fui/fuiRenderNode.h"

class fuiRenderNodeStage : public fuiRenderNode {
public:
    explicit fuiRenderNodeStage(fuiFile* file);
    float getStageHeight();
    float getStageWidth();
    void addChild(fuiRenderNode* node);

    fuiRenderNode* child;
};
