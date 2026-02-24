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

    this->m_fuiFilePlatformSkin = nullptr;
    this->m_fuiFileSkinGraphics = nullptr;
    this->m_fuiFileSkinGraphicsHud = nullptr;
    this->m_fuiFileSkinGraphicsInGame = nullptr;
    this->m_qword13440 = nullptr;
    this->m_fuiFileSkinGraphicsLabels = nullptr;
    this->m_fuiFileSkinLabels = nullptr;
    this->m_fuiFileSkinInGame = nullptr;
    this->m_fuiFileSkinHud = nullptr;
    this->m_qword13468 = nullptr;
    this->m_fuiFileSkin = nullptr;
    this->m_fuiFilePlatformSkinHd = nullptr;
    this->m_fuiFileSkinHdGraphics = nullptr;
    this->m_fuiFileSkinHdGraphicsHud = nullptr;
    this->m_fuiFileSkinHdGraphicsInGame = nullptr;
    this->m_qword13498 = nullptr;
    this->m_fuiFileSkinHdGraphicsLabels = nullptr;
    this->m_fuiFileSkinHdLabels = nullptr;
    this->m_fuiFileSkinHdInGame = nullptr;
    this->m_fuiFileSkinHdHud = nullptr;
    this->m_qword134C0 = nullptr;
    this->m_fuiFileSkinHd = nullptr;

    this->m_byte134E8 = 0;
    this->m_byte134E9 = 0;
    this->m_byte134Ea = 0;
    this->m_byte134Eb = 0;
    this->m_byte134Ec = 0;
    this->m_dword134F0 = 0;
    this->m_dword134F8 = 0;
    this->m_hasSetupRenderPosition = 0;
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

void ConsoleUIController::setupRenderPosition(int x, int y) {
    this->m_hasSetupRenderPosition = true;
    this->m_renderPositionX = x;
    this->m_renderPositionY = y;

    fui::sInstance->setOrigin(x, y);
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

fuiFile *ConsoleUIController::loadSkin(const std::wstring &filename, const std::wstring &fallback, int isHd) {
    if (filename.empty() || !CConsoleMinecraftApp::sInstance.hasArchiveFile(filename, false))
        return nullptr;

    arrayWithLength<uchar> file = CConsoleMinecraftApp::sInstance.getArchiveFile(filename, false);
    fuiFile *f = fui::sInstance->load(file, false, isHd);

    delete file.m_data;

    return f;
}

void ConsoleUIController::loadSkins() {
    // I am so confused at why it was done in this way, but it only matches when I do this, so idk.
    // Maybe it was some jank ifdef spam here
    std::wstring platformSkin = L"";

    platformSkin = L"skinNX.fui";
    this->m_fuiFilePlatformSkin = this->loadSkin(platformSkin, L"platformskin.fui", 0);

    platformSkin = L"skinHDNX.fui";
    this->m_fuiFilePlatformSkinHd = this->loadSkin( platformSkin, L"platformskinHD.fui", 1);

    this->m_fuiFileSkinGraphics = this->loadSkin(L"skinGraphics.fui", L"skinGraphics.fui", 0);
    this->m_fuiFileSkinGraphicsHud = this->loadSkin(L"skinGraphicsHud.fui", L"skinGraphicsHud.fui", 0);
    this->m_fuiFileSkinGraphicsInGame = this->loadSkin(L"skinGraphicsInGame.fui", L"skinGraphicsInGame.fui", 0);
    this->m_fuiFileSkinGraphicsLabels = this->loadSkin(L"skinGraphicsLabels.fui", L"skinGraphicsLabels.fui", 0);
    this->m_fuiFileSkinLabels = this->loadSkin(L"skinLabels.fui", L"skinLabels.fui", 0);
    this->m_fuiFileSkinInGame = this->loadSkin(L"skinInGame.fui", L"skinInGame.fui", 0);
    this->m_fuiFileSkinHud = this->loadSkin(L"skinHud.fui", L"skinHud.fui", 0);
    this->m_fuiFileSkin = this->loadSkin(L"skin.fui", L"skin.fui", 0);
    this->m_fuiFileSkinHdGraphics = this->loadSkin(L"skinHDGraphics.fui", L"skinHDGraphics.fui", 1);
    this->m_fuiFileSkinHdGraphicsHud = this->loadSkin(L"skinHDGraphicsHud.fui", L"skinHDGraphicsHud.fui", 1);
    this->m_fuiFileSkinHdGraphicsInGame = this->loadSkin(L"skinHDGraphicsInGame.fui", L"skinHDGraphicsInGame.fui", 1);
    this->m_fuiFileSkinHdGraphicsLabels = this->loadSkin(L"skinHDGraphicsLabels.fui", L"skinHDGraphicsLabels.fui", 1);
    this->m_fuiFileSkinHdLabels = this->loadSkin(L"skinHDLabels.fui", L"skinHDLabels.fui", 1);
    this->m_fuiFileSkinHdInGame = this->loadSkin(L"skinHDInGame.fui", L"skinHDInGame.fui", 1);
    this->m_fuiFileSkinHdHud = this->loadSkin(L"skinHDHud.fui", L"skinHDHud.fui", 1);
    this->m_fuiFileSkinHd = this->loadSkin(L"skinHD.fui", L"skinHD.fui", 1);
}
