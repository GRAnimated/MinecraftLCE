#pragma once

#include "4JLibraries_Source/fui/fuiRenderNode.h"

struct fuiRenderNodeStage : public fuiRenderNode {
    explicit fuiRenderNodeStage(fuiFile* file);
    float getStageHeight();
    float getStageWidth();
    void addChild(fuiRenderNode* node);

    fuiRenderNode* child;
};
