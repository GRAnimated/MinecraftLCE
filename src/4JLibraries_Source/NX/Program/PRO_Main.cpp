#include "InfoBarManager.h"
#include "NX/Platform.h"
#include "net/minecraft/core/System.h"
#include <cstring>
#include <new>

#include "Awards.h"
#include "NX/Render/RendererCore.h"
#include "NX/Thread/C4JThreadImpl.h"
#include "java/io/IntCache.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/client/CInput.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Compression.h"
#include "net/minecraft/client/GameSettings.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/renderer/texture/Textures.h"
#include "net/minecraft/client/renderer/vertex/Tesselator.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/sounds/SoundEngine.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/client/ui/scene/scenes/UIScene_AchievementsMenu.h"
#include "net/minecraft/core/profile/CProfile.h"
#include "net/minecraft/core/storage/CStorage.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/item/crafting/recipe/FireworksRecipe.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/chunk/storage/OldChunkStorage.h"
#include "net/minecraft/world/phys/Vec2.h"
#include "nn/fs.h"
#include "nn/nifm.h"
#include "nn/oe.h"
#include "nn/os.h"
#include "nn/time.h"

static nn::oe::PerformanceMode PERFORMANCE_MODE;
static nn::os::MessageQueueType* MESSAGE_QUEUE;
static u64* MESSAGE_QUEUE_BUFFER;
static nn::os::MutexType* MAIN_MUTEX;
static nn::os::MutexType* MAIN_MUTEX2;

static const char* what = "";

void sub_7100607FBC() {
    InitializeCriticalSection(MAIN_MUTEX);
}

void DefineActions() {
    GameSettings::SetDefaultActionMapping(0, 0, 2);
    GameSettings::SetDefaultActionMapping(0, 1, 12);
    GameSettings::SetDefaultActionMapping(0, 2, 11);
    GameSettings::SetDefaultActionMapping(0, 3, 10);
    GameSettings::SetDefaultActionMapping(0, 4, 9);
    GameSettings::SetDefaultActionMapping(0, 5, 4);
    GameSettings::SetDefaultActionMapping(0, 6, 1);
    GameSettings::SetDefaultActionMapping(0, 7, 13);
    GameSettings::SetDefaultActionMapping(0, 8, 3);
    GameSettings::SetDefaultActionMapping(0, 9, 14);
    GameSettings::SetDefaultActionMapping(0, 10, 5);
    GameSettings::SetDefaultActionMapping(0, 11, 6);
    GameSettings::SetDefaultActionMapping(0, 12, 7);
    GameSettings::SetDefaultActionMapping(0, 13, 8);
    GameSettings::SetDefaultActionMapping(0, 14, 0);
    GameSettings::SetDefaultActionMapping(0, 15, 0);
    GameSettings::SetDefaultActionMapping(0, 16, 10);
    GameSettings::SetDefaultActionMapping(0, 17, 9);
    GameSettings::SetDefaultActionMapping(0, 18, 11);
    GameSettings::SetDefaultActionMapping(0, 19, 1);
    GameSettings::SetDefaultActionMapping(0, 20, 3);
    GameSettings::SetDefaultActionMapping(0, 21, 1);
    GameSettings::SetDefaultActionMapping(0, 22, 3);
    GameSettings::SetDefaultActionMapping(0, 23, 1);
    GameSettings::SetDefaultActionMapping(0, 24, 4);
    GameSettings::SetDefaultActionMapping(1, 0, 9);
    GameSettings::SetDefaultActionMapping(1, 1, 11);
    GameSettings::SetDefaultActionMapping(1, 2, 12);
    GameSettings::SetDefaultActionMapping(1, 3, 5);
    GameSettings::SetDefaultActionMapping(1, 4, 6);
    GameSettings::SetDefaultActionMapping(1, 5, 4);
    GameSettings::SetDefaultActionMapping(1, 6, 1);
    GameSettings::SetDefaultActionMapping(1, 7, 14);
    GameSettings::SetDefaultActionMapping(1, 8, 3);
    GameSettings::SetDefaultActionMapping(1, 9, 10);
    GameSettings::SetDefaultActionMapping(1, 10, 5);
    GameSettings::SetDefaultActionMapping(1, 11, 6);
    GameSettings::SetDefaultActionMapping(1, 12, 7);
    GameSettings::SetDefaultActionMapping(1, 13, 8);
    GameSettings::SetDefaultActionMapping(1, 14, 0);
    GameSettings::SetDefaultActionMapping(1, 15, 0);
    GameSettings::SetDefaultActionMapping(1, 16, 6);
    GameSettings::SetDefaultActionMapping(1, 17, 6);
    GameSettings::SetDefaultActionMapping(1, 18, 12);
    GameSettings::SetDefaultActionMapping(1, 19, 1);
    GameSettings::SetDefaultActionMapping(1, 20, 3);
    GameSettings::SetDefaultActionMapping(1, 21, 1);
    GameSettings::SetDefaultActionMapping(1, 22, 3);
    GameSettings::SetDefaultActionMapping(1, 23, 1);
    GameSettings::SetDefaultActionMapping(1, 24, 4);
    GameSettings::SetDefaultActionMapping(2, 0, 12);
    GameSettings::SetDefaultActionMapping(2, 1, 11);
    GameSettings::SetDefaultActionMapping(2, 2, 2);
    GameSettings::SetDefaultActionMapping(2, 3, 5);
    GameSettings::SetDefaultActionMapping(2, 4, 6);
    GameSettings::SetDefaultActionMapping(2, 5, 4);
    GameSettings::SetDefaultActionMapping(2, 6, 1);
    GameSettings::SetDefaultActionMapping(2, 7, 10);
    GameSettings::SetDefaultActionMapping(2, 8, 3);
    GameSettings::SetDefaultActionMapping(2, 9, 14);
    GameSettings::SetDefaultActionMapping(2, 10, 5);
    GameSettings::SetDefaultActionMapping(2, 11, 6);
    GameSettings::SetDefaultActionMapping(2, 12, 7);
    GameSettings::SetDefaultActionMapping(2, 13, 8);
    GameSettings::SetDefaultActionMapping(2, 14, 0);
    GameSettings::SetDefaultActionMapping(2, 15, 0);
    GameSettings::SetDefaultActionMapping(2, 16, 5);
    GameSettings::SetDefaultActionMapping(2, 17, 6);
    GameSettings::SetDefaultActionMapping(2, 18, 2);
    GameSettings::SetDefaultActionMapping(2, 19, 1);
    GameSettings::SetDefaultActionMapping(2, 20, 3);
    GameSettings::SetDefaultActionMapping(2, 21, 1);
    GameSettings::SetDefaultActionMapping(2, 22, 3);
    GameSettings::SetDefaultActionMapping(2, 23, 1);
    GameSettings::SetDefaultActionMapping(2, 24, 4);
    CInput* localCInput = CInput::sInstance;
    for (int i = 0; i != 4; ++i) {
        if (localCInput->IsCircleCrossSwapped()) {
            localCInput->SetGameControllerTypeJoypadMaps(i, 0, 1);
            localCInput->SetGameControllerTypeJoypadMaps(i, 20, 1);
            localCInput->SetGameControllerTypeJoypadMaps(i, 1, 2);
            localCInput->SetGameControllerTypeJoypadMaps(i, 21, 2);
        } else {
            localCInput->SetGameControllerTypeJoypadMaps(i, 0, 2);
            localCInput->SetGameControllerTypeJoypadMaps(i, 20, 2);
            localCInput->SetGameControllerTypeJoypadMaps(i, 1, 1);
            localCInput->SetGameControllerTypeJoypadMaps(i, 21, 1);
        }
        localCInput->SetGameControllerTypeJoypadMaps(i, 2, 4);
        localCInput->SetGameControllerTypeJoypadMaps(i, 3, 8);
        localCInput->SetGameControllerTypeJoypadMaps(i, 4, 0x200400);
        localCInput->SetGameControllerTypeJoypadMaps(i, 5, 0x100800);
        localCInput->SetGameControllerTypeJoypadMaps(i, 7, 0x9000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 6, 0x6000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 8, 0x800000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 9, 0x400000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 10, 64);
        localCInput->SetGameControllerTypeJoypadMaps(i, 11, 128);
        localCInput->SetGameControllerTypeJoypadMaps(i, 18, 16);
        localCInput->SetGameControllerTypeJoypadMaps(i, 19, 32);
        localCInput->SetGameControllerTypeJoypadMaps(i, 14, 0x20000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 15, 0x10000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 16, 0x80000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 17, 0x40000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 32, 2);
        localCInput->SetGameControllerTypeJoypadMaps(i, 24, 0x200000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 25, 0x100000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 26, 0x8000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 27, 0x4000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 28, 0x80000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 29, 0x40000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 30, 0x20000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 31, 0x10000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 33, 0x800000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 34, 0x400000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 36, 64);
        localCInput->SetGameControllerTypeJoypadMaps(i, 35, 128);
        localCInput->SetGameControllerTypeJoypadMaps(i, 37, 8);
        localCInput->SetGameControllerTypeJoypadMaps(i, 22, 16);
        localCInput->SetGameControllerTypeJoypadMaps(i, 38, 1);

        if (i) {
            localCInput->SetGameControllerTypeJoypadMaps(i, 39, 256);
            localCInput->SetGameControllerTypeJoypadMaps(i, 41, 512);
            localCInput->SetGameControllerTypeJoypadMaps(i, 12, 512);
            localCInput->SetGameControllerTypeJoypadMaps(i, 13, 256);
        } else {
            localCInput->SetGameControllerTypeJoypadMaps(0, 39, 2048);
            localCInput->SetGameControllerTypeJoypadMaps(0, 41, 1024);
            localCInput->SetGameControllerTypeJoypadMaps(0, 12, 1024);
            localCInput->SetGameControllerTypeJoypadMaps(0, 13, 2048);
        }

        localCInput->SetGameControllerTypeJoypadMaps(i, 40, 4);
        localCInput->SetGameControllerTypeJoypadMaps(i, 23, 0x20);
        localCInput->SetGameControllerTypeJoypadMaps(i, 42, 0x1000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 43, 0x2000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 44, 0x400);
        localCInput->SetGameControllerTypeJoypadMaps(i, 45, 0x800);
        localCInput->SetGameControllerTypeJoypadMaps(i, 57, 0x1000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 58, 0x2000);
        localCInput->SetGameControllerTypeJoypadMaps(i, 59, 0x400);
        localCInput->SetGameControllerTypeJoypadMaps(i, 60, 0x800);
    }
}

void PopupToast() {
    gConsoleUIController.SetAchievementUnlocked();
}

bool unk() {
    return false;
}

int dword_7100D6B4AC;
unsigned int dword_71017C0AB0;
unsigned int unk_71017C17BC;

void nullsub_833() {}

// NON_MATCHING: Incomplete
extern "C" void nnMain() {
    sub_7100607FBC();
    nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode_Normal, 0x20004);
    PERFORMANCE_MODE = nn::oe::GetPerformanceMode();
    nn::oe::SetPerformanceModeChangedNotificationEnabled(true);
    nn::oe::SetFocusHandlingMode(nn::oe::FocusHandlingMode_NoSuspend);
    nn::oe::SetResumeNotificationEnabled(true);
    nullsub_833();
    nn::nifm::Initialize();
    nn::time::Initialize();
    nn::oe::Initialize();

    size_t cacheSize;
    nn::fs::QueryMountRomCacheSize(&cacheSize);
    void* cache = operator new[](cacheSize, std::nothrow_t());
    nn::fs::MountRom("GAME", cache, cacheSize);
    nn::os::InitializeMessageQueue(MESSAGE_QUEUE, MESSAGE_QUEUE_BUFFER, 3);

    InitializeCriticalSection(MAIN_MUTEX2);
    C4JThreadImpl::SetMainThreadID();

    Compression::CreateNewThreadStorage();
    Renderer::sInstance->Initialise();
    CProfile::sInstance->AwardManagerOnCreate();

    CInput::sInstance->Initialise(1, 61, 23);
    DefineActions();
    CInput::sInstance->SetJoypadMapArraySetupComplete();
    CInput::sInstance->SetKeyRepeatRate(0.3f, 0.2f);
    CInput::sInstance->SetDeadzoneAndMovementRange(0, 20000, 0x7FFF);

    CConsoleMinecraftApp::sInstance.loadMediaArchive();
    CConsoleMinecraftApp::sInstance.InitialiseDLCInfo();

    if (!CConsoleMinecraftApp::sInstance.ReadProductCodes())
        CConsoleMinecraftApp::sInstance.FatalLoadError(L"ReadProductCodes");  // string from wii u

    L10N::loadStringTable();
    CInput::sInstance->SetCircleCrossSwapped(true);
    int screenType = 1;  // TODO: shove function that gets screenType, haven't done it so far because i'm
                         // unsure on how to name that func
    gConsoleUIController.setResolutionChangeDisableFlag(IUIController::eRESOLUTION_DISABLE_FLAG::FLAG_0);

    int screenWidth, screenHeight;
    if (screenType == 1) {
        screenHeight = 1080;
        screenWidth = 1920;
    } else {
        screenWidth = 1280;
        screenHeight = 720;
    }

    gConsoleUIController.init(screenWidth, screenHeight);
    CConsoleMinecraftApp::sInstance.CommerceInit();
    CConsoleMinecraftApp::sInstance.initTime();
    // funny thing is that all args seems to be unused
    // note: first 2 dwords correspond to constant empty string generated by compiler -Dexrn
    CProfile::sInstance->Initialise(L"", L"", 33, 5, 4, &unk_71017C17BC, 7776, &dword_71017C0AB0);
    CProfile::sInstance->SetSignInChoicesCallback(CConsoleMinecraftApp::RequestSignInUIChoices);
    CProfile::sInstance->SetOnAwardHandler(PopupToast, nullptr);
    RegisterAwardsWithProfileManager();
    // It is unknown what the function provided at the end of this call is. Looks more like what a branch
    // would lead to as it's stored inside this method. It originally called for bool * in that area.
    CStorage::sInstance->Init(0, L10N::GetString(StringIDs::NewWorld), "savegame.dat", 51000000,
                              CConsoleMinecraftApp::DisplaySavingMessageNX, &CConsoleMinecraftApp::sInstance,
                              what, nullptr);
    CProfile::sInstance->SetSignInChangeCallback(CMinecraftApp::SignInChangeCallback,
                                                 &CConsoleMinecraftApp::sInstance);
    CProfile::sInstance->SetProfileReadErrorCallback(CMinecraftApp::ProfileReadErrorCallback,
                                                     &CConsoleMinecraftApp::sInstance);
    CStorage::sInstance->InitialiseProfileData(33, 5, 4, &unk_71017C17BC, 7776, &dword_71017C0AB0);
    CStorage::sInstance->SetDefaultOptionsCallback(CMinecraftApp::DefaultOptionsCallback,
                                                   &CConsoleMinecraftApp::sInstance);
    CStorage::sInstance->SetOptionsDataCallback(CMinecraftApp::OptionsDataCallback,
                                                &CConsoleMinecraftApp::sInstance);
    CStorage::sInstance->SetOldProfileVersionCallback(GameSettings::OldProfileVersionCallback,
                                                      &CConsoleMinecraftApp::sInstance);
    CStorage::sInstance->field_198();
    CStorage::sInstance->SetGameSaveFolderPrefix("");
    CStorage::sInstance->SetMaxSaves(99);

    arrayWithLength<unsigned char> img1;
    arrayWithLength<unsigned char> img2;
    auto saveThumbnail
        = CConsoleMinecraftApp::sInstance.getArchiveFile(L"DefaultSaveThumbnail64x64.png", false);

    CStorage::sInstance->SetDefaultImages(
        img1.data, img1.length, img2.data, img2.length, saveThumbnail.data,
        saveThumbnail.length);  // TODO: the last 0 is meant to be something else... dunno what
    CStorage::sInstance->SetIncompleteSaveCallback(CConsoleMinecraftApp::Callback_SaveGameIncomplete,
                                                   &CConsoleMinecraftApp::sInstance);

    delete img1.data;
    delete img2.data;
    delete saveThumbnail.data;

    CStorage::sInstance->SetSaveTitle(L"Default Save");
    CStorage::sInstance->SetOpenDirFn(OpenDir);
    CStorage::sInstance->SetReadDirFn(ReadDir);
    CStorage::sInstance->SetCloseDirFn(CloseDir);
    CStorage::sInstance->SetDLCPackageRoot("DLCDrive");
    Tesselator::CreateNewThreadStorage(0x100000);
    AABB::CreateNewThreadStorage();
    Vec3::CreateNewThreadStorage();
    phys::Vec2::CreateNewThreadStorage();
    IntCache::CreateNewThreadStorage();
    OldChunkStorage::CreateNewThreadStorage();
    Level::enableLightingCache();
    Block::CreateNewThreadStorage();
    FireworksRecipe::CreateNewThreadStorage();
    Minecraft::main();
    CConsoleMinecraftApp::sInstance.InitGameSettings();
    CStorage::sInstance->ReadFromProfile(0, 0);
    CProfile::sInstance->SetUpsellCallback(CMinecraftApp::UpsellReturnedCallback,
                                           &CConsoleMinecraftApp::sInstance);
    CConsoleMinecraftApp::sInstance.InitialiseTips();
    CGameNetworkManager::sInstance.Initialise();
    CGameNetworkManager::sInstance.SetLocalGame(true);
    // 3 unk methods go here
    // TODO: some weird notification stuff

    Renderer::sInstance->StartFrame();
    CConsoleMinecraftApp::sInstance.UpdateTime();
    PIXBeginNamedEvent(0, "Input manager tick");
    CInput::sInstance->Tick();
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0, "Profile manager tick");
    CProfile::sInstance->Tick();
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0, "Storage manager tick");
    CStorage::sInstance->Tick();
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0, "Render manager tick");
    Renderer::sInstance->Tick();
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0, "Sentient tick");
    PIXEndNamedEvent();
    PIXBeginNamedEvent(0.0, "Network manager do work #1");
    CGameNetworkManager::sInstance.DoWork();
    PIXEndNamedEvent();

    int primaryPad;
    bool isPaused;
    if (CConsoleMinecraftApp::sInstance.GetGameStarted()) {
        Minecraft::GetInstance()->run_middle();
        if (CGameNetworkManager::sInstance.IsLocalGame()
            && CGameNetworkManager::sInstance.GetPlayerCount() == 1) {
            primaryPad = CProfile::sInstance->GetPrimaryPad();
            isPaused = gConsoleUIController.IsPauseMenuDisplayed(primaryPad);
        } else {
            isPaused = false;
        }
        CConsoleMinecraftApp::sInstance.SetAppPaused(isPaused);
    } else {
        Renderer::sInstance->SetClearColour(new float[2]);
        Renderer::sInstance->Clear(2);
        Minecraft::GetInstance()->mSoundEngine->tick(nullptr, 0);
        Minecraft::GetInstance()->mTextures->tick(true, false, false);
        IntCache::Reset();
        if (CConsoleMinecraftApp::sInstance.GetReallyChangingSessionType())
            Minecraft::sInstance->tickAllConnections();
    }
    Minecraft::sInstance->mSoundEngine->playMusicTick();
    CConsoleMinecraftApp::sInstance.GetCommerceInstance()->tick();
    InfoBarManager::StartTimingCategory(InfoBarManager::eTimingCagegory::ConsoleUIControllerTick);
    gConsoleUIController.tick();
    InfoBarManager::EndTimingCategory(InfoBarManager::eTimingCagegory::ConsoleUIControllerTick);
    Renderer::sInstance->vtbl_7101130608_func_17();
    InfoBarManager::StartTimingCategory(InfoBarManager::eTimingCagegory::ConsoleUIControllerRender);
    gConsoleUIController.render();
    InfoBarManager::EndTimingCategory(InfoBarManager::eTimingCagegory::ConsoleUIControllerRender);
    InfoBarManager::EndTimingCategory(InfoBarManager::eTimingCagegory::InitTicking);
    PIXBeginNamedEvent(0.0, "Frame present");
    Renderer::sInstance->Present();
    PIXEndNamedEvent();
    Renderer::sInstance->Set_matrixDirty();
    gConsoleUIController.CheckMenuDisplayed();

    PIXBeginNamedEvent(0.0, "Profile load check");
    if (CInput::sControllers) {
        if (CInput::sControllers & 1) {
            void* padData = CStorage::sInstance->GetGameDefinedProfileData(0);
            GameSettings::ClearGameSettingsChangedFlag(0);
            GameSettings::ApplyGameSettingsChanged(0);
            Minecraft::GetInstance()->mStatsCounters[0]->clear();
            Minecraft::GetInstance()->mStatsCounters[0]->parse(padData);
        }
        if (CInput::sControllers & 2) {
            void* padData = CStorage::sInstance->GetGameDefinedProfileData(1);
            GameSettings::ClearGameSettingsChangedFlag(1);
            GameSettings::ApplyGameSettingsChanged(1);
            Minecraft::GetInstance()->mStatsCounters[1]->clear();
            Minecraft::GetInstance()->mStatsCounters[1]->parse(padData);
        }
        if (CInput::sControllers & 4) {
            void* padData = CStorage::sInstance->GetGameDefinedProfileData(2);
            GameSettings::ClearGameSettingsChangedFlag(2);
            GameSettings::ApplyGameSettingsChanged(2);
            Minecraft::GetInstance()->mStatsCounters[2]->clear();
            Minecraft::GetInstance()->mStatsCounters[2]->parse(padData);
        }
        if (CInput::sControllers & 8) {
            void* padData = CStorage::sInstance->GetGameDefinedProfileData(3);
            GameSettings::ClearGameSettingsChangedFlag(3);
            GameSettings::ApplyGameSettingsChanged(3);
            Minecraft::GetInstance()->mStatsCounters[3]->clear();
            Minecraft::GetInstance()->mStatsCounters[3]->parse(padData);
        }
    }
    PIXEndNamedEvent();

    PIXBeginNamedEvent(0.0, "Network manager do work #2");
    CGameNetworkManager::sInstance.DoWork();
    PIXEndNamedEvent();

    CConsoleMinecraftApp::sInstance.HandleXuiActions();
    if (CProfile::sInstance->IsFullVersion()) {
        if (!CConsoleMinecraftApp::sHideTrialTimer) {
            gConsoleUIController.ShowTrialTimer(false);
            CConsoleMinecraftApp::sHideTrialTimer = true;
        }
        Vec3::resetPool();
    } else {
        if (!CConsoleMinecraftApp::sInstance.GetGameStarted())
            Vec3::resetPool();
        if (CConsoleMinecraftApp::sInstance.IsAppPaused())
            CConsoleMinecraftApp::sInstance.UpdateTrialPausedTimer();
        primaryPad = CProfile::sInstance->GetPrimaryPad();
        gConsoleUIController.UpdateTrialTimer(primaryPad);
        Vec3::resetPool();
    }
}
