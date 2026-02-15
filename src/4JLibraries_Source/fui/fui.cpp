#include "fui/fui.h"

#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"

#include "fui/event/FJ_KeyboardEvent.h"
#include "fui/event/FJ_MouseMoveEvent.h"
#include "fui/fuiFile.h"
#include "fui/fuiTextureManager.h"
#include "fui/node/FJ_FuiNode.h"
#include "fui/node/FJ_FuiNodeStage.h"
#include <cstring>

fui* fui::sInstance;

// void fui::removeEventListenerForNode(FJ_FuiNode*) {
//     // STUB
// }
void fui::setScreenSize(float width, float height) {
    if (width == 1280 && height == 480)
        width = 640;

    this->m_screenWidth = width;
    this->m_screenHeight = height;
}

void fui::unloadScene(fuiFile* file) {
    if (!file)
        return;

    EnterCriticalSection(this->m_scenesMutex);
    delete file;

    for (auto it = this->m_scenes.begin(); it != this->m_scenes.end(); ++it) {
        if (*it == file) {
            m_scenes.erase(it);
            break;
        }
    }

    LeaveCriticalSection(this->m_scenesMutex);
}

void fui::setResolution(int res) {
    this->m_resolution = res;
    if (res) {
        this->setScreenSize(1920, 1080);
    } else {
        this->setScreenSize(1280, 720);
    }
}

int fui::getResolution() {
    return this->m_resolution;
}

void fui::render(fuiFile* file, float a1, float a2, float a3, float a4) {
    this->render(file, a1, a2, a3, a4, 1.0f, 1.0f);
}

void fui::render(fuiFile* file, float a1, float a2, float a3, float a4, float a5, float a6) {
    std::memset(this->m_atrix, 0, sizeof(mat4x4));
    this->m_atrix[0][0] = 1.0f;
    this->m_atrix[1][1] = 1.0f;
    this->m_atrix[2][2] = 1.0f;
    this->m_atrix[3][3] = 1.0f;

    Renderer* renderer = Renderer::sInstance;

    renderer->vtbl_7101130608_func_19();

    renderer->StateSetFaceCull(false);
    renderer->StateSetBlendEnable(true);
    renderer->StateSetBlendFunc(2, 6);

    renderer->StateSetAlphaTestEnable(false);
    renderer->StateSetDepthTestEnable(false);
    renderer->StateSetDepthMask(false);

    renderer->MatrixMode(1);
    renderer->MatrixSetIdentity();
    renderer->MatrixOrthogonal(0.0f, this->m_screenWidth, this->m_screenHeight, 0.0f, 1000.0f, 3000.0f);

    renderer->MatrixMode(0);
    renderer->MatrixSetIdentity();
    renderer->MatrixTranslate(this->m_unk5 - a1, this->m_unk6 - a2, -2000.0f);
    renderer->MatrixScale(a5, a6, 1);

    renderer->StateSetScissorRect(this->m_unk5, this->m_unk6, this->m_unk5 + a3, this->m_unk6 + a4);

    file->m_renderNodeStage->gather(this->m_boolIdk);

    this->preRender(file);

    file->m_renderNodeStage->render(nullptr, nullptr);
}

void fui::dispatchKeyboardEvent(fuiFile* file, bool state, int c) {
    FJ_FuiNode* node = file->m_data.m_fuiSymbol->m_stage;  // ???

    if (FJ_FuiNode* focus = static_cast<FJ_FuiNodeStage*>(node)->getFocus())
        node = focus;

    node->dispatchEvent(new FJ_KeyboardEvent(state, c, true, false));
}

// param names guessed
void fui::dispatchMouseMoveEvent(fuiFile* file, float x, float y) {
    FJ_FuiNode* node = file->m_data.m_fuiSymbol->m_stage;

    if (FJ_FuiNode* focus = static_cast<FJ_FuiNodeStage*>(node)->getFocus())
        node = focus;

    node->dispatchEvent(new FJ_MouseMoveEvent(x, y, true, false));
}

void fui::addDirectEventListener(const FJ_EventListener& listener) {
    this->removeDirectEventListener(listener);
    this->m_eventListeners.push_back(listener);
}

void fui::removeDirectEventListener(const FJ_EventListener& listener) {
    for (auto it = this->m_eventListeners.begin(); it != this->m_eventListeners.end(); ++it) {
        if (it->m_unk1 != listener.m_unk1 || it->m_unk3 != listener.m_unk3
            || it->m_target != listener.m_target)
            continue;

        this->m_eventListeners.erase(it);
        break;
    }
}

void fui::removeEventListenerForNode(FJ_FuiNode* node) {
    for (auto it = this->m_eventListeners.begin(); it != this->m_eventListeners.end();) {
        if (it->m_target != node) {
            ++it;
            continue;
        }

        it = this->m_eventListeners.erase(it);
    }
}

void fui::removeManagedTexture(fuiFile* file, fuiBitmap* texture) {
    this->m_textureManager->removeManagedTexture(file, texture);
}
