#include "fui/fuiRenderNodeTimeline.h"

void fuiRenderNodeTimeline::progogateBoundsFromChild() {
    fuiRenderNodeTimeline* cur = this;

    do {
        cur->updateBoundsLocal();

        fuiRenderNode* tl = cur->m_timeline;

        if (!tl)
            break;

        cur = tl->asTimeline();
    } while (cur);
}
