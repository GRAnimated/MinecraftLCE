#pragma once

#include "NX/Render/C4JRender.h"
#include "net/minecraft/client/ui/scene/UIScene.h"

class UILayer {
public:
    C4JRender::eViewportType getViewPort();
    void showComponent(int, EUIScene, bool);
    void addComponent(int, EUIScene, void*);
};
