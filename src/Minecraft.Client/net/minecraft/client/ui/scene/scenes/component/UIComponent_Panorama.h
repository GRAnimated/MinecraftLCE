#pragma once
#include "net/minecraft/client/ui/scene/UIScene.h"

class UIComponent_Panorama : public UIScene {
    void tick() override;
    void render(int i1, int i2, C4JRender::eViewportType viewportType) override;

    void setPanorama(bool daytime);

    int padding;
    bool m_unk;
    int m_currentFrame;
};
