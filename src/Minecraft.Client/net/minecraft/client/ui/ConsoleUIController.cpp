#include "net/minecraft/client/ui/ConsoleUIController.h"

#include "4JLibraries_Source/fui/fui.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"
#include <string>

// NON_MATCHING: TODO: finish this shit
ConsoleUIController::ConsoleUIController() {
    qword_71017BE950 = nullptr;
    this->qword8 = 0LL;
    this->qword13570 = 0LL;
    this->byte13598 = 0;
    this->byte418 = 0;
    this->qword420 = 0LL;
    this->qword428 = 0LL;
    this->qword430 = 0LL;
    this->qword438 = 0LL;
    this->qword410 = 0LL;
    this->byte419 = 1;
    InitializeCriticalSection(&mMutex4);
    this->mScreenWidth = 1280.0f;
    this->mScreenHeight = 720.0f;
    this->byte41A = 0;
    this->mPreInited = 0;
    this->qword13420 = 0LL;
    this->qword13428 = 0LL;
    this->qword13430 = 0LL;
    this->qword13438 = 0LL;
    this->qword13440 = 0LL;
    this->qword13448 = 0LL;
    this->qword13450 = 0LL;
    this->qword13458 = 0LL;
    this->qword13460 = 0LL;
    this->qword13468 = 0LL;
    this->qword13470 = 0LL;
    this->qword13478 = 0LL;
    this->qword13480 = 0LL;
    this->qword13488 = 0LL;
    this->qword13490 = 0LL;
    this->qword13498 = 0LL;
    this->qword134A0 = 0LL;
    this->qword134A8 = 0LL;
    this->qword134B0 = 0LL;
    this->qword134B8 = 0LL;
    this->qword134C0 = 0LL;
    this->qword134C8 = 0LL;

    this->byte134E8 = 0;
    this->byte134E9 = 0;
    this->byte134EA = 0;
    this->byte134EB = 0;
    this->byte134EC = 0;
    this->dword134F0 = 0;
    this->dword134F8 = 0;
    this->byte134FC = 0;
    this->cipa = 0;
    this->dword1359C = 0;
    this->qword135A0 = 0LL;
    InitializeCriticalSection(&this->mMutex1);
    InitializeCriticalSection(&this->mMutex2);
    InitializeCriticalSection(&this->mMutex6);
    InitializeCriticalSection(&this->mMutex5);
    InitializeCriticalSection(&this->mMutex3);
    this->byte1356C = 0;
    this->byte1340C = 0;
    this->byte13418 = 0;
    this->qword13410 = 0LL;
    this->mViewportTouchOffset1 = 0;
    this->mViewportTouchOffset2 = 0;

    this->mFlags = 0;
}

// NON_MATCHING: WiiU pseudocode looks completly different than Switch one, also pseudocode is 2 simple lines
// of code while asm shows it does have switch case like in WiiU
void ConsoleUIController::updateViewportTouchOffset(C4JRender::eViewportType) {
    this->mViewportTouchOffset1 = this->getScreenWidth() * 0.25f;
    this->mViewportTouchOffset2 = 0;
}

arrayWithLength<uchar> ConsoleUIController::getMovieData(const std::wstring& name) {
    long v4 = System::processTimeInMilliSecs() + 60000;

    if (auto search = mCachedMovieDatas.find(name); search != mCachedMovieDatas.end()) {
        search->second.time = v4;
        return search->second;
    } else {
        arrayWithLength<uchar> cipa = CConsoleMinecraftApp::sInstance.getArchiveFile(name, false);
        _CachedMovieData temp;
        temp.data = cipa.data;
        temp.length = cipa.length;
        temp.time = v4;
        mCachedMovieDatas[name] = temp;
        return cipa;
    }
}

void ConsoleUIController::clearResolutionChangeDisableFlag(eRESOLUTION_DISABLE_FLAG flag) {
    this->mFlags &= ~(1 << flag);
}

void ConsoleUIController::setResolutionChangeDisableFlag(IUIController::eRESOLUTION_DISABLE_FLAG flag) {
    this->mFlags |= 1 << flag;
}

void ConsoleUIController::preInit(int screenWidth, int screenHeight) {
    this->mScreenWidth = screenWidth;
    this->mScreenHeight = screenHeight;
    this->mPreInited = true;
}

void ConsoleUIController::init(int screenWidth, int screenHeight) {
    if (screenWidth == 1920 && screenHeight == 1080)
        fui::sInstance->setResolution(1);
    else
        fui::sInstance->setResolution(0);
    this->preInit(screenWidth, screenHeight);
    this->postInit();
}

void ConsoleUIController::ShowUIDebugMarketingGuide(bool) {}
void ConsoleUIController::SetIgnoreAutosaveMenuDisplayed(int, bool) {}
void ConsoleUIController::RefreshTooltips(unsigned) {}
void ConsoleUIController::UpdateSelectedItemPos(unsigned) {}
void ConsoleUIController::HandleTMSDLCFileRetrieved(int) {}
void ConsoleUIController::SetEmptyQuadrantLogo(int) {}
void ConsoleUIController::ShowOtherPlayersBaseScene(unsigned, bool) {}
void ConsoleUIController::ShowAutosaveCountdownTimer(bool shown) {}
void ConsoleUIController::UpdateAutosaveCountdownTimer(unsigned) {}
