#include "net/minecraft/client/ui/ConsoleUIController.h"

#include "fui/fui.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "types.h"
#include <string>

// NON_MATCHING: TODO: finish this shit
ConsoleUIController::ConsoleUIController() {
    qword_71017BE950 = nullptr;
    this->m_qword8 = 0LL;
    this->m_qword13570 = 0LL;
    this->m_byte13598 = 0;
    this->m_byte418 = 0;
    this->m_qword420 = 0LL;
    this->m_qword428 = 0LL;
    this->m_qword430 = 0LL;
    this->m_qword438 = 0LL;
    this->m_qword410 = 0LL;
    this->m_byte419 = 1;
    InitializeCriticalSection(&m_mutex4);
    this->m_screenWidth = 1280.0f;
    this->m_screenHeight = 720.0f;
    this->m_byte41A = 0;
    this->m_preInited = 0;
    this->m_qword13420 = 0LL;
    this->m_qword13428 = 0LL;
    this->m_qword13430 = 0LL;
    this->m_qword13438 = 0LL;
    this->m_qword13440 = 0LL;
    this->m_qword13448 = 0LL;
    this->m_qword13450 = 0LL;
    this->m_qword13458 = 0LL;
    this->m_qword13460 = 0LL;
    this->m_qword13468 = 0LL;
    this->m_qword13470 = 0LL;
    this->m_qword13478 = 0LL;
    this->m_qword13480 = 0LL;
    this->m_qword13488 = 0LL;
    this->m_qword13490 = 0LL;
    this->m_qword13498 = 0LL;
    this->m_qword134A0 = 0LL;
    this->m_qword134A8 = 0LL;
    this->m_qword134B0 = 0LL;
    this->m_qword134B8 = 0LL;
    this->m_qword134C0 = 0LL;
    this->m_qword134C8 = 0LL;

    this->m_byte134E8 = 0;
    this->m_byte134E9 = 0;
    this->m_byte134Ea = 0;
    this->m_byte134Eb = 0;
    this->m_byte134Ec = 0;
    this->m_dword134F0 = 0;
    this->m_dword134F8 = 0;
    this->m_byte134Fc = 0;
    this->m_cipa = 0;
    this->m_dword1359C = 0;
    this->m_qword135A0 = 0LL;
    InitializeCriticalSection(&this->m_mutex1);
    InitializeCriticalSection(&this->m_mutex2);
    InitializeCriticalSection(&this->m_mutex6);
    InitializeCriticalSection(&this->m_mutex5);
    InitializeCriticalSection(&this->m_mutex3);
    this->m_byte1356C = 0;
    this->m_byte1340C = 0;
    this->m_byte13418 = 0;
    this->m_qword13410 = 0LL;
    this->m_viewportTouchOffset1 = 0;
    this->m_viewportTouchOffset2 = 0;

    this->m_flags = 0;
}

// NON_MATCHING: WiiU pseudocode looks completly different than Switch one, also pseudocode is 2 simple lines
// of code while asm shows it does have switch case like in WiiU
void ConsoleUIController::updateViewportTouchOffset(C4JRender::eViewportType) {
    this->m_viewportTouchOffset1 = this->getScreenWidth() * 0.25f;
    this->m_viewportTouchOffset2 = 0;
}

arrayWithLength<uchar> ConsoleUIController::getMovieData(const std::wstring& name) {
    long v4 = System::processTimeInMilliSecs() + 60000;

    if (auto search = m_cachedMovieDatas.find(name); search != m_cachedMovieDatas.end()) {
        search->second.m_time = v4;
        return search->second;
    } else {
        arrayWithLength<uchar> cipa = CConsoleMinecraftApp::sInstance.getArchiveFile(name, false);
        _CachedMovieData temp;
        temp.m_data = cipa.m_data;
        temp.m_length = cipa.m_length;
        temp.m_time = v4;
        m_cachedMovieDatas[name] = temp;
        return cipa;
    }
}

void ConsoleUIController::clearResolutionChangeDisableFlag(eRESOLUTION_DISABLE_FLAG flag) {
    this->m_flags &= ~(1 << flag);
}

void ConsoleUIController::setResolutionChangeDisableFlag(IUIController::eRESOLUTION_DISABLE_FLAG flag) {
    this->m_flags |= 1 << flag;
}

void ConsoleUIController::preInit(int screenWidth, int screenHeight) {
    this->m_screenWidth = screenWidth;
    this->m_screenHeight = screenHeight;
    this->m_preInited = true;
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
