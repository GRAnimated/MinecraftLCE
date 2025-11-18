#pragma once

#include "fui/fuiRenderNode.h"

struct fuiRenderNodeTimeline : public fuiRenderNode {
    void progogateBoundsFromChild();
    void updateBoundsLocal();
};
