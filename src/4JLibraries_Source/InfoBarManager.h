#pragma once

#include "com/mojang/blaze3d/vertex/BufferBuilder.h"

class InfoBarManager {
public:
    enum eTimingCagegory {
        InitTicking = 0,
        ConsoleUIControllerTick = 6,
        ConsoleUIControllerRender = 7,
    };  // nice spelling

    static void StartTimingCategory(eTimingCagegory category);
    static void EndTimingCategory(eTimingCagegory category);

    void RenderQuad(float, float, float, float, unsigned int, BufferBuilder*);
    void Render(float, float);

    void SetCommandBufferSize(float);
};
