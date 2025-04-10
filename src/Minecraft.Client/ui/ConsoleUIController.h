#pragma once
#include "Minecraft.Client/renderer/C4JRender.h"

class ConsoleUIController {
public:
    void updateViewportTouchOffset(C4JRender::eViewportType);
    bool IsReloadingSkin();
    int SetTooltips(unsigned int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int,
                    int, bool, bool);
};

extern ConsoleUIController gConsoleUIController;