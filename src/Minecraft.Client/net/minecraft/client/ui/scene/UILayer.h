#pragma once
#include "Minecraft.Client/renderer/C4JRender.h"
#include "Minecraft.Client/ui/scene/UIScene.h"

class UILayer {
public:
    C4JRender::eViewportType getViewPort();
    void showComponent(int, EUIScene, bool);
};