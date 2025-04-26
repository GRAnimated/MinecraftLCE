#include <cstring>
#include <new>

#include "Minecraft.Client/C4JThreadImpl.h"
#include "Minecraft.Client/CGameNetworkManager.h"
#include "Minecraft.Client/CInput.h"
#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/Compression.h"
#include "Minecraft.Client/GameSettings.h"
#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/renderer/Renderer.h"
#include "Minecraft.Client/renderer/Tesselator.h"
#include "Minecraft.Client/resources/L10N.h"
#include "Minecraft.Client/ui/ConsoleUIController.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/entity/Entity.h"
#include "Minecraft.World/item/crafting/recipe/FireworksRecipe.h"
#include "Minecraft.World/level/biome/Biome.h"
#include "Minecraft.World/level/block/Block.h"
#include "Minecraft.World/level/chunk/storage/OldChunkStorage.h"
#include "Minecraft.World/phys/Vec2.h"
#include "Minecraft.Core/io/IntCache.h"
#include "Minecraft.Core/profile/CProfile.h"
#include "Minecraft.Core/storage/CStorage.h"
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

// NON_MATCHING: Incomplete
extern "C" void nnMain() {
    sub_7100607FBC();
    nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode_Normal, 0x20004);
    PERFORMANCE_MODE = nn::oe::GetPerformanceMode();
    nn::oe::SetPerformanceModeChangedNotificationEnabled(true);
    nn::oe::SetFocusHandlingMode(0);
    nn::oe::SetResumeNotificationEnabled(true);
    // nullsub_833();
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
    int screenType = 1;  // shove function that gets screenType, haven't done it so far because i'm unsure
                         // on how to name that func
    gConsoleUIController.setUnk(false);

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
    // It is unknown what the function provided at the end of this call is. Looks more like what a branch
    // would lead to as it's stored inside this method. It originally called for bool * in that area.
    CStorage::sInstance->Init(0, L10N::GetString(3232918502), "savegame.dat", 51000000,
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
    CGameNetworkManager::sInstance->Initialise();
    CGameNetworkManager::sInstance->SetLocalGame(true);
}
