#include "NX/Platform.h"
#include "fui/fui.h"
#include "fui/fuiFile.h"
#include "fui/fuiRenderNode.h"
#include "fui/node/document/menu/FJ_Panorama.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/scene/scenes/component/UIComponent_Panorama.h"
#include "net/minecraft/world/level/Level.h"
#include "net/minecraft/world/level/dimension/Dimension.h"
#include "net/minecraft/world/level/dimension/DimensionType.h"
#include "net/minecraft/world/level/storage/LevelData.h"
void UIComponent_Panorama::tick() {
    if (this->hasMovie()) {
        Minecraft *mc = Minecraft::GetInstance();

        EnterCriticalSection(&mc->m_criticalSection);
        if (mc->m_level && mc->m_level->m_dimension->getType() == DimensionType::OVERWORLD && mc->m_level->getLevelData()->getDayTime() % 24000 > 14000) {
            this->setPanorama(false);
        } else {
            this->setPanorama(true);
        }
        LeaveCriticalSection(&mc->m_criticalSection);

        this->m_currentFrame = reinterpret_cast<FJ_Panorama*>(this->m_fuiFile->getRootNode()->m_fuiNodeStage)->GetCurrentFrame();
        this->UIScene::tick();
    }
}

// NON_MATCHING | Difference: 4036
void UIComponent_Panorama::render(int i1, int i2, C4JRender::eViewportType viewportType) {
    if (!this->m_unk || viewportType - 1 > 3) {
        UIScene::render(i1, i2, viewportType);
        return;
    }

    if (viewportType == C4JRender::eViewportType_Bottom) {
        g_consoleUIController.setupRenderPosition(0.0f, g_consoleUIController.getScreenHeight() * 0.5f);
        fui::sInstance->render(this->m_fuiFile, 0.0f, 0.0f, i1, g_consoleUIController.getScreenHeight());
        return;
    }

    if (viewportType == C4JRender::eViewportType_Right) {
        g_consoleUIController.setupRenderPosition(g_consoleUIController.getScreenWidth() * 0.5f, 0.0f);
        fui::sInstance->render(this->m_fuiFile, 0.0f, 0.0f, i1, g_consoleUIController.getScreenHeight());
        return;
    }

    g_consoleUIController.setupRenderPosition(0.0f, 0.0f);

    if (viewportType > C4JRender::eViewportType_Right) {
        fui::sInstance->render(this->m_fuiFile, 0.0f, 0.0f, g_consoleUIController.getScreenWidth(), g_consoleUIController.getScreenHeight(), 0.5f, 0.5f);
        return;
    }

    fui::sInstance->render(this->m_fuiFile, 0.0f, 0.0f, g_consoleUIController.getScreenWidth(), g_consoleUIController.getScreenHeight(), 0.5f, 0.5f);
}