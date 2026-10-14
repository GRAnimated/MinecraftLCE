#pragma once

#include "fui/fuiRenderNode.h"

struct fuiRenderNodeStage : public fuiRenderNode {
    explicit fuiRenderNodeStage(fuiFile* file);
    ~fuiRenderNodeStage() override;
    void gather(bool) override;
    void preRender() override;
    void render(fuiRect*, fuiMatrix*) override;
    fuiRenderNode* findNode(const char*) override;
    float getStageHeight();
    float getStageWidth();
    void addChild(fuiRenderNode* node);

    fuiRenderNode* m_child;
};

static_assert(sizeof(fuiRenderNodeStage) == 0x108, "Original FUI stage layout");
