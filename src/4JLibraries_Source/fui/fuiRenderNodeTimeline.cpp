#include "fuiRenderNodeTimeline.h"

void fuiRenderNodeTimeline::progogateBoundsFromChild() {
    fuiRenderNodeTimeline* cur = this;

    do {
        cur->updateBoundsLocal();

        fuiRenderNode* tl = cur->mTimeline;

        if (!tl)
            break;

        cur = tl->asTimeline();
    } while (cur);
}
