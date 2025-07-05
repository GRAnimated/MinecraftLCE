#pragma once

#include "fui/fuiRenderNode.h"

class fuiRenderNodeTimeline : public fuiRenderNode {
public:
    void progogateBoundsFromChild();
    void updateBoundsLocal();
};
