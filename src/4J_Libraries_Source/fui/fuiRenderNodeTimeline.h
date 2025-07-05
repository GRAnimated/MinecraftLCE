#pragma once
#include "fuiRenderNode.h"

class fuiRenderNodeTimeline : public fuiRenderNode {
public:
    void progogateBoundsFromChild();
    void updateBoundsLocal();
};