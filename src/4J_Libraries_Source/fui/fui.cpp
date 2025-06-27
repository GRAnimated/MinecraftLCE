#include "4J_Libraries_Source/fui/fui.h"

#include "event/FJ_KeyboardEvent.h"
#include "event/FJ_MouseMoveEvent.h"
#include "fuiFile.h"
#include "fuiTextureManager.h"
#include "node/FJ_FuiNode.h"
#include "node/FJ_FuiNodeStage.h"

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

void fui::dispatchKeyboardEvent(fuiFile *file, bool unk, int c) {
    FJ_FuiNode *node = file->mData.fuiSymbol->mStage; // ???

    if (FJ_FuiNode* focus = static_cast<FJ_FuiNodeStage*>(node)->getFocus())
        node = focus;

    node->dispatchEvent(new FJ_KeyboardEvent(unk, c, true, false));
}

// param names guessed
void fui::dispatchMouseMoveEvent(fuiFile* file, float x, float y) {
    FJ_FuiNode* node = file->mData.fuiSymbol->mStage;

    if (FJ_FuiNode* focus = static_cast<FJ_FuiNodeStage*>(node)->getFocus())
        node = focus;

    node->dispatchEvent(new FJ_MouseMoveEvent(true, false, x, y));
}

void fui::addDirectEventListener(const FJ_EventListener &listener) {
    this->removeDirectEventListener(listener);
    this->mEventListeners.push_back(listener);
}

void fui::removeDirectEventListener(const FJ_EventListener&listener) {
    for (auto it = this->mEventListeners.begin(); it != this->mEventListeners.end(); ++it) {
        if (it->unk1 != listener.unk1 ||
            it->unk3 != listener.unk3 ||
            it->unk2 != listener.unk2) continue;

        this->mEventListeners.erase(it);
        break;
    }
}

void fui::removeManagedTexture(fuiFile *file, fuiBitmap *texture) {
    this->mTextureManager->removeManagedTexture(file, texture);
}