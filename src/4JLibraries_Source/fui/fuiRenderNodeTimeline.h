#pragma once

#include "fui/fuiRenderNode.h"

struct fuiRenderNodeTimeline : public fuiRenderNode {
    void progogateBoundsFromChild();
    void updateBoundsLocal();

    int currentFrame();

    void *m_padding[7];
    int m_currentFrame;
};
