#include "4JLibraries_Source/fui/fui.h"

#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"

#include "4JLibraries_Source/fui/event/FJ_KeyboardEvent.h"
#include "4JLibraries_Source/fui/event/FJ_MouseMoveEvent.h"
#include "4JLibraries_Source/fui/fuiFile.h"
#include "4JLibraries_Source/fui/fuiTextureManager.h"
#include "4JLibraries_Source/fui/node/FJ_FuiNode.h"
#include "4JLibraries_Source/fui/node/FJ_FuiNodeStage.h"
#include <cstring>

fui* fui::sInstance;

// void fui::removeEventListenerForNode(FJ_FuiNode*) {
//     // STUB
// }
void fui::setScreenSize(float width, float height) {
    if (width == 1280 && height == 480)
        width = 640;

    this->mScreenWidth = width;
    this->mScreenHeight = height;
}

void fui::unloadScene(fuiFile* file) {
    if (!file)
        return;

    EnterCriticalSection(this->mScenesMutex);
    delete file;

    for (auto it = this->mScenes.begin(); it != this->mScenes.end(); ++it) {
        if (*it == file) {
            mScenes.erase(it);
            break;
        }
    }

    LeaveCriticalSection(this->mScenesMutex);
}

void fui::setResolution(int res) {
    this->mResolution = res;
    if (res) {
        this->setScreenSize(1920, 1080);
    } else {
        this->setScreenSize(1280, 720);
    }
}

int fui::getResolution() {
    return this->mResolution;
}

void fui::render(fuiFile* file, float a1, float a2, float a3, float a4) {
    this->render(file, a1, a2, a3, a4, 1.0f, 1.0f);
}

void fui::render(fuiFile* file, float a1, float a2, float a3, float a4, float a5, float a6) {
    std::memset(this->matrix, 0, sizeof(mat4x4));
    this->matrix[0][0] = 1.0f;
    this->matrix[1][1] = 1.0f;
    this->matrix[2][2] = 1.0f;
    this->matrix[3][3] = 1.0f;

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
    renderer->MatrixOrthogonal(0.0f, this->mScreenWidth, this->mScreenHeight, 0.0f, 1000.0f, 3000.0f);

    renderer->MatrixMode(0);
    renderer->MatrixSetIdentity();
    renderer->MatrixTranslate(this->mUnk5 - a1, this->mUnk6 - a2, -2000.0f);
    renderer->MatrixScale(a5, a6, 1);

    renderer->StateSetScissorRect(this->mUnk5, this->mUnk6, this->mUnk5 + a3, this->mUnk6 + a4);

    file->mRenderNodeStage->gather(this->mBoolIdk);

    this->preRender(file);

    file->mRenderNodeStage->render(nullptr, nullptr);
}

void fui::dispatchKeyboardEvent(fuiFile* file, bool state, int c) {
    FJ_FuiNode* node = file->mData.fuiSymbol->mStage;  // ???

    if (FJ_FuiNode* focus = static_cast<FJ_FuiNodeStage*>(node)->getFocus())
        node = focus;

    node->dispatchEvent(new FJ_KeyboardEvent(state, c, true, false));
}

// param names guessed
void fui::dispatchMouseMoveEvent(fuiFile* file, float x, float y) {
    FJ_FuiNode* node = file->mData.fuiSymbol->mStage;

    if (FJ_FuiNode* focus = static_cast<FJ_FuiNodeStage*>(node)->getFocus())
        node = focus;

    node->dispatchEvent(new FJ_MouseMoveEvent(x, y, true, false));
}

void fui::addDirectEventListener(const FJ_EventListener& listener) {
    this->removeDirectEventListener(listener);
    this->mEventListeners.push_back(listener);
}

void fui::removeDirectEventListener(const FJ_EventListener& listener) {
    for (auto it = this->mEventListeners.begin(); it != this->mEventListeners.end(); ++it) {
        if (it->unk1 != listener.unk1 || it->unk3 != listener.unk3 || it->mTarget != listener.mTarget)
            continue;

        this->mEventListeners.erase(it);
        break;
    }
}

void fui::removeEventListenerForNode(FJ_FuiNode* node) {
    for (auto it = this->mEventListeners.begin(); it != this->mEventListeners.end();) {
        if (it->mTarget != node) {
            ++it;
            continue;
        }

        it = this->mEventListeners.erase(it);
    }
}

void fui::removeManagedTexture(fuiFile* file, fuiBitmap* texture) {
    this->mTextureManager->removeManagedTexture(file, texture);
}
