#pragma once

#include "fui/fuiRenderNode.h"
#include <string>
#include <vector>

struct fuiTimelineObject {
    unsigned int m_depth;
    fuiObject* m_object;
};

struct fuiFrameAction {
    int m_frame;
    int m_action;
    std::string m_argument;
};

struct fuiRenderNodeTimeline : public fuiRenderNode {
    fuiRenderNodeTimeline(fuiRenderNode*, fuiRenderNode*, fuiObject*, unsigned int, unsigned char, fuiRGBA*,
                          unsigned char, bool, fuiFile*);
    ~fuiRenderNodeTimeline() override;
    void shutdown() override;
    void gather(bool) override;
    void preRender() override;
    void render(fuiRect*, fuiMatrix*) override;
    void handleAddedToStage() override;
    fuiRenderNode* findNode(const char*) override;
    fuiRenderNode* getNodeFromPath(const char*) override;
    void generateGlobalMatrix() override;
    void progogateBoundsFromChild();
    void updateBoundsLocal();
    void expandBoundsFromChild(fuiRect&);
    void setPlaying(bool);
    void setFrame(unsigned int);

    std::vector<fuiRenderNode*> m_children;
    std::vector<fuiTimelineObject> m_objects;
    fuiRenderNode* m_mask;
    int m_frame;
    int m_nextFrame;
    std::vector<fuiFrameAction> m_frameActions;
};

static_assert(sizeof(fuiFrameAction) == 0x20, "Original FUI frame action layout");
static_assert(sizeof(fuiRenderNodeTimeline) == 0x158, "Original FUI timeline layout");
static_assert(offsetof(fuiRenderNodeTimeline, m_children) == 0x100, "Original FUI child list");
static_assert(offsetof(fuiRenderNodeTimeline, m_frame) == 0x138, "Original FUI frame state");
