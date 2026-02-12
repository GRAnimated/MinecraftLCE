#include "net/minecraft/client/ui/scene/UIScene.h"

#include "4JLibraries_Source/fui/node/FJ_FuiNodeStage.h"
#include "NX/Platform.h"
#include "fui/fui.h"
#include "fui/fuiFile.h"
#include "fui/fuiRenderNode.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/scene/UILayer.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/sounds/SoundEvents.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include <string>
#include <utility>

const int dword_7100E23090[22]
    = {0, 7, 8, 9, 3, 4, 6, 5, 1, 2, 0xA, 0xB, 0x64, 0xC, 0x11, 0x12, 0x64, 0x64, 0x64, 0x64, 0, 7};

// It's matching but... some of those variable inits should be moved to header
UIScene::UIScene(int padID, UILayer* uiLayer) {
    this->m_padId = padID;
    this->m_qword30 = nullptr;
    this->m_fuiFile = nullptr;
    this->m_focusRelated = false;
    this->m_hideLowerScenes = false;
    this->m_byteE9 = false;
    this->m_hidden = false;
    this->m_boolAd = false;
    this->m_visible = true;
    this->m_byte96 = false;
    this->m_controlFocused = -1;
    this->m_controlChildFocus = 0;
    this->m_opacity = 1.0;
    this->m_isInitializedMovie = false;
    this->m_byteEa = true;
    this->m_dwordF8 = 0;
    this->m_uiLayer = uiLayer;
    this->m_backScene = nullptr;
    this->m_callbackUniqueId = nullptr;
    this->m_wstring8 = L"";
    this->m_bool28 = false;
}

void UIScene::customDrawFui(void* a1, const char* a2, fuiRect* a3) {
    ((UIScene*)a1)->customDraw(a2, a3);
}

void UIScene::initialiseMovie() {
    this->loadMovie();
    this->mapElementsAndNames();
    this->updateSafeZone();

    this->m_isInitializedMovie = true;
}

void UIScene::loadMovie() {
    EnterCriticalSection(&ConsoleUIController::unk_71017BE928);
    std::wstring moviePath = this->getMoviePath();

    fui* fui = fui::sInstance;

    int v3;
    if (fui->getResolution()) {
        moviePath.append(L"1080.fui");
        v3 = 0;
    } else {
        moviePath.append(L"720.fui");
        v3 = 1;
    }
    this->m_resType = v3;
    arrayWithLength<uchar> movieData = gConsoleUIController.getMovieData(moviePath.c_str());
    this->m_fuiFile = fui->load(movieData, true, fui->getResolution());

    this->m_fuiFile->getRootNode()->m_fuiNodeStage->setCallbackScene(this);
    this->m_fuiFile->setCustomDrawCallback(UIScene::customDrawFui, this);

    this->m_stageWidth = this->m_fuiFile->getStageWidth();
    this->m_stageHeight = this->m_fuiFile->getStageHeight();
    this->m_stageWidth2 = this->m_stageWidth;
    this->m_stageHeight2 = this->m_stageHeight;

    LeaveCriticalSection(&ConsoleUIController::unk_71017BE928);
}

void UIScene::navigateBack() {
    gConsoleUIController.PlayUISFX(SoundEvents::BACK);
    gConsoleUIController.NavigateBack(this->m_padId, false, EUIScene_DefaultMAYBE, (EUILayer)8);
}

void UIScene::sendInputToMovie(int key, bool a3, bool a4, bool a5) {
    if (this->m_fuiFile) {
        int elo = this->convertGameActionToFuiKeycode(key);
        fui::sInstance->dispatchKeyboardEvent(this->m_fuiFile, !a4, elo);
    }
}

bool UIScene::controlHasFocus(UIControl_Base* control) {
    return this->controlHasFocus(control->getControlID());
}

bool UIScene::controlHasFocus(int controlID) {
    return this->m_controlFocused == controlID;
}

void UIScene::addTimer(int id, int time) {
    this->m_timersMap[id] = _TimerInfo{time, (int)System::processTimeInMilliSecs() + time, true};
}

void UIScene::killTimer(int id) {
    if (auto elo = this->m_timersMap.find(id); elo != this->m_timersMap.end())
        elo->second.m_enabled = false;
}

bool UIScene::hasTimer(int id) {
    auto elo = this->m_timersMap.find(id);
    return elo != this->m_timersMap.end() && elo->second.m_enabled;
}

// Probably better way to do this but I'm lazy
void* UIScene::GetCallbackUniqueId() {
    void* ret = this->m_callbackUniqueId;
    if (!ret) {
        ret = gConsoleUIController.RegisterForCallbackId(this);
        this->m_callbackUniqueId = ret;
    }
    return ret;
}

// NON_MATCHING: this is junk impl just to match other func
void UIScene::customDrawSlotControlFui(fuiRect* rect, int, not_null_ptr<ItemInstance> item, float f, bool a,
                                       bool b, bool c) {
    rect->getHeight();
    item.reset();
    this->m_stageHeight = f;
    this->m_byteE9 = a;
    this->m_byteE9 = b;
    this->m_byteE9 = c;
}

int UIScene::convertGameActionToFuiKeycode(int gameAction) {
    return (unsigned int)gameAction <= 0x15 ? dword_7100E23090[gameAction] : 100;
}

bool UIScene::needsReloaded() {
    return !this->m_fuiFile && (!this->stealsFocus() || this->m_focusRelated);
}

bool UIScene::hasMovie() {
    return this->m_fuiFile != nullptr;
}

void UIScene::updateSafeZone() {
    double v1 = 0.0, v2 = 0.0, v4 = 0.0, v5 = 0.0;

    switch (this->m_uiLayer->getViewPort()) {
    case C4JRender::eViewportType_Top:
        v1 = this->getSafeZoneHalfHeight();
        v4 = v5 = v2;
        break;
    case C4JRender::eViewportType_Bottom:
        v2 = this->getSafeZoneHalfHeight();
        v4 = v5 = v1;
        break;
    case C4JRender::eViewportType_Left:
        v4 = this->getSafeZoneHalfWidth();
        v2 = v5 = v1;
        break;
    case C4JRender::eViewportType_Right:
        v5 = this->getSafeZoneHalfWidth();
        v2 = v1;
        v4 = v1;
        break;
    case C4JRender::eViewportType_TopLeft:
        v1 = this->getSafeZoneHalfHeight();
        v4 = this->getSafeZoneHalfWidth();
        v5 = v2;
        break;
    case C4JRender::eViewportType_TopRight:
        v1 = this->getSafeZoneHalfHeight();
        v5 = this->getSafeZoneHalfWidth();
        v4 = v2;
        break;
    case C4JRender::eViewportType_BottomLeft:
        v2 = this->getSafeZoneHalfHeight();
        v4 = this->getSafeZoneHalfWidth();
        v5 = v1;
        break;
    case C4JRender::eViewportType_BottomRight:
        v2 = this->getSafeZoneHalfHeight();
        v5 = this->getSafeZoneHalfWidth();
        v4 = v1;
        break;
    default:
        v1 = this->getSafeZoneHalfHeight();
        v2 = this->getSafeZoneHalfHeight();
        v4 = this->getSafeZoneHalfWidth();
        v5 = this->getSafeZoneHalfWidth();
        break;
    }

    this->setSafeZone(v1, v2, v4, v5);
}

void UIScene::updateViewportTouchOffset() {
    C4JRender::eViewportType viewPortType = this->m_uiLayer->getViewPort();
    gConsoleUIController.updateViewportTouchOffset(viewPortType);
}

bool UIScene::mapElementsAndNames() {
    return true;
}

int UIScene::getSubSceneType() const {
    return 0;
}

void UIScene::tick() {
    if (!this->m_hidden) {
        if (this->m_hideLowerScenes)
            this->m_byte96 = 1;

        this->tickTimers();

        // had to do it hacky way as idk how to force compiler to output same thing it does in target, unless
        // that's how it looked in source
        for (auto i = this->m_uiControls.begin(); i != this->m_uiControls.end(); ++i) {
            UIControl* uiControl = *i;
            uiControl->tick();
        }

        this->m_hideLowerScenes = true;
    }
}

void UIScene::handleTimerComplete(int) {}

bool UIScene::stealsFocus() {
    return true;
}

bool UIScene::hasFocus(int padID) {
    return this->m_focusRelated && this->m_padId == padID;
}

void UIScene::updateTooltips() {
    if (!gConsoleUIController.IsReloadingSkin()) {
        gConsoleUIController.SetTooltips(this->m_padId, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                         -1, -1, -1, 0, 0);
    }
}

void UIScene::updateComponents() {}
void UIScene::handleGainFocus(bool) {}
void UIScene::handleLoseFocus() {}

bool UIScene::hidesLowerScenes() {
    return this->m_hideLowerScenes;
}

bool UIScene::blocksInput() {
    return false;
}

void* UIScene::GetMainPanel() {
    return nullptr;
}

void UIScene::render(int a2, int a3, C4JRender::eViewportType viewPortType) {
    if (!this->m_hidden && this->m_hideLowerScenes) {
        if (this->m_fuiFile) {
            gConsoleUIController.setupRenderPosition(viewPortType);
            fui::sInstance->render(this->m_fuiFile, 0.0f, 0.0f, a2, a3);
        }
    }
}

void UIScene::customDraw(const char*, fuiRect*) {}
void UIScene::handleInput(int, int, bool, bool, bool, bool&) {}
void UIScene::handleDestroy() {}
void UIScene::handlePreUnloadForReload() {}
void UIScene::handlePreReload() {}
void UIScene::handleReload() {}
void UIScene::handlePress(int, int) {}
void UIScene::handleFocusChange(int, int) {}
void UIScene::handleInitFocus(int, int) {}
void UIScene::handleCheckboxElementToggled(int, int, bool) {}
void UIScene::handleSliderMove(int, int) {}
void UIScene::handleSliderElementMove(int, int, int) {}
void UIScene::handleAnimationEnd() {}
void UIScene::handleSelectionChanged(int) {}
void UIScene::handleRequestMoreData(int, bool) {}
void UIScene::handleTouchBoxRebuild() {}
void UIScene::HandleDLCMountingComplete() {}
void UIScene::HandleDLCInstalled() {}
void UIScene::HandleDLCLicenseChange() {}
void UIScene::HandleTMSBanFileRetrieved() {}
void UIScene::HandleMessage(EUIMessage, void*) {}
void UIScene::HandleSaveDeviceRemoved(int) {}
void UIScene::handleUnlockFullVersion() {}
void UIScene::handleTouchInput(unsigned int, int, int, int, bool, bool, bool) {}

bool UIScene::isReadyToDelete() {
    return true;
}
