#pragma once
#include "fuiRenderNode.h"

class fuiRenderNodeStage : public fuiRenderNode {
public:
    fuiRenderNodeStage(fuiFile *);
    float getStageHeight();
    float getStageWidth();
};