#pragma once

#include "4JLibraries_Source/fui/fuiRenderNode.h"

struct fuiRenderNodeTimeline : public fuiRenderNode {
    void progogateBoundsFromChild();
    void updateBoundsLocal();
};
