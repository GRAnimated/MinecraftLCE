#include "fui/fui.h"

#include "NX/Platform.h"
#include "NX/Renderer.h"

#include "event/FJ_KeyboardEvent.h"
#include "event/FJ_MouseMoveEvent.h"
#include "fui/fuiFile.h"
#include "fui/fuiTextureManager.h"
#include "fui/node/FJ_FuiNode.h"
#include "node/FJ_FuiNodeStage.h"
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

// NON_MATCHING | Score: 2521 (lower is better)
// I think our mData struct is fucked since fuiSymbol has NO vftable...
// and the pseudocode shows it trying to make calls to it's vftable.
void fui::render(fuiFile* file, float a1, float a2, float a3, float a4) {
    float unk1 = 1;
    float unk2 = 1;
    float unk3 = 1;

    std::memset(this, 0, 0x40);  // what is this even doing???

    this->mUnk1 = 1;
    this->mUnk2 = 1;
    this->mUnk3 = 1;
    this->mUnk4 = 1;

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
    renderer->MatrixScale(unk3, unk2, 1.0f);

    renderer->StateSetScissorRect(this->mUnk5, this->mUnk6, this->mUnk5 + a3, this->mUnk6 + a4);

    //  (*(void (__fastcall **)(fuiSymbol *, _QWORD))(*(_QWORD *)file->mData.fuiSymbol + 24LL))(
    // file->mData.fuiSymbol,
    // (unsigned __int8)this->padding2[288]);

    this->preRender(file);

    /*
    (*(void (__fastcall **)(fuiSymbol *, _QWORD, _QWORD))(*(_QWORD *)file->mData.fuiSymbol + 40LL))(
    file->mData.fuiSymbol,
    0LL,
    0LL);
    */
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
